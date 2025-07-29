import argparse
import math
import io
import os
import re
import sys
from concurrent.futures import ProcessPoolExecutor
from itertools import zip_longest, product
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Tuple

import numpy as np
import polars as pl
from rich.live import Live

# Ensure stdout is flushed line-by-line
if isinstance(sys.stdout, io.TextIOWrapper):
    sys.stdout.reconfigure(line_buffering=True)

DEFAULT_WORKERS = int(
    os.environ.get(
        "SLURM_CPUS_PER_TASK",
        os.environ.get("SLURM_CPUS_ON_NODE", os.cpu_count() or 1),
    )
)

KNOWN_METADATA = {"assoc", "rank", "size", "lbound", "entries"}

POLARS_SCHEMA = {
    "timestep": pl.Int64,
    "got_file": pl.Utf8,
    "want_file": pl.Utf8,
    "variable": pl.Utf8,
    "status": pl.Utf8,
    "max_abs": pl.Float64,
    "max_rel": pl.Float64,
}


def discover_timesteps(root: Path) -> List[int]:
    ts_set: set[int] = set()
    pat = re.compile(r"_(\d+)\.got$")
    for p in root.glob("*.got"):
        if m := pat.search(p.name):
            ts_set.add(int(m.group(1)))
    for p in root.glob("*.want"):
        if m := pat.search(p.name):
            ts_set.add(int(m.group(1)))
    return sorted(ts_set)


def find_comparable_files_at_timestep(prefix: str, timestep: int, root: Path) -> List[Tuple[Path, Path]]:
    pairs: List[Tuple[Path, Path]] = []
    for want in root.glob(f"{prefix}.*_{timestep}.want"):
        got = want.with_suffix(".got")
        if not got.is_file():
            print(f"⚠️  Skipping {want}: matching {got} not found")
            continue
        pairs.append((got, want))
    return sorted(pairs, key=lambda x: (x[0].name, x[1].name))


def _stream_lines(path: Path) -> Iterable[str]:
    with path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            ls = line.rstrip("\n\r")
            if ls.strip():
                yield ls


def compare_pair(
    got: Path,
    want: Path,
    abs_tol: np.float64 = np.finfo(np.float64).eps,
    rel_tol: np.float64 = np.finfo(np.float64).eps,
    verbose: bool = True,
) -> Tuple[Optional[str], Dict[str, Dict[str, Any]]]:
    per_var: Dict[str, Dict[str, Any]] = {}
    current_var: str = got.stem.removeprefix(f"{got.stem.split('.')[0]}.")

    with Live(refresh_per_second=4) as live:
        if verbose:
            live.update(f"Comparing {got} vs. {want}")

        for got_line, want_line in zip_longest(_stream_lines(got), _stream_lines(want)):
            if got_line is None or want_line is None:
                msg = "Different number of lines ❌"
                if verbose:
                    print(msg)
                return msg, per_var

            if got_line.startswith("# ") or want_line.startswith("# "):
                if got_line != want_line:
                    msg = f"Different text ({got_line} vs. {want_line}) ❌"
                    if verbose:
                        print(msg)
                    return msg, per_var
                tag = got_line.lstrip("# ").strip().split()[0]
                if tag and tag not in KNOWN_METADATA:
                    per_var.setdefault(tag, {"ok": True, "max_abs": 0.0, "max_rel": 0.0})
                    current_var = tag
                    if verbose:
                        live.update(f"Checking: {current_var}")
                continue

            if got_line == want_line:
                continue

            try:
                got_num = float(got_line)
                want_num = float(want_line)
            except ValueError:
                msg = f"Non-numeric data for `{current_var}` ({got_line} & {want_line}) ❌"
                if verbose:
                    print(msg)
                return msg, per_var

            abs_diff = abs(got_num - want_num)
            scale = max([abs(got_num), abs(want_num), abs_tol])
            rel_diff = abs_diff / scale

            stats = per_var.setdefault(current_var, {"ok": True, "max_abs": 0.0, "max_rel": 0.0})
            stats["max_abs"] = max(stats["max_abs"], abs_diff)
            stats["max_rel"] = max(stats["max_rel"], rel_diff)
            if not math.isclose(got_num, want_num, rel_tol=rel_tol, abs_tol=abs_tol):
                stats["ok"] = False

    ok = all(v["ok"] for v in per_var.values())
    msg = None if ok else "Numerical differences found ❌"
    if msg and verbose:
        print(msg)
    return msg, per_var


def make_comparison_for_timestep(prefix: str, ts: int, root: Path) -> Tuple[str, int, pl.DataFrame]:
    T = pl.DataFrame(schema=POLARS_SCHEMA)
    fpairs = find_comparable_files_at_timestep(prefix, ts, root)
    for got, want in fpairs:
        err, per_var = compare_pair(got, want)
        if not err:
            print(f"{got.name} vs. {want.name} : No numerical differences found ✅")
        else:
            print(f"{got.name} vs. {want.name} : {err}")
        for var, st in per_var.items():
            status = "OK" if st["ok"] else "DIFF"
            if status == "DIFF":
                print(f"  {var}: {status} | max_abs={st['max_abs']} | max_rel={st['max_rel']}")
            T.extend(
                pl.DataFrame(
                    {
                        "timestep": ts,
                        "got_file": got.name,
                        "want_file": want.name,
                        "variable": var,
                        "status": status,
                        "max_abs": st["max_abs"],
                        "max_rel": st["max_rel"],
                    },
                    schema=POLARS_SCHEMA,
                )
            )
        sys.stdout.flush()
    return prefix, ts, T


def wrapper(args: Tuple[str, int, str]) -> Tuple[str, int, pl.DataFrame]:
    prefix, ts, root_str = args
    return make_comparison_for_timestep(prefix, ts, Path(root_str))


if __name__ == "__main__":
    argp = argparse.ArgumentParser(description="Compare `.got` and `.want` files for numerical differences.")
    argp.add_argument(
        "-r",
        "--root",
        type=str,
        default=".",
        help="Root directory for the got and want files.",
    )
    argp.add_argument(
        "timesteps",
        type=str,
        nargs="?",
        default="",
        help="Comma-separated list of timesteps. If omitted, all timesteps are processed.",
    )
    args = argp.parse_args()

    root = Path(args.root)
    print(f"Looking at: {root}")

    timesteps = [ts.strip() for ts in args.timesteps.split(",") if ts.strip()]
    assert all(ts.isdigit() for ts in timesteps)
    timesteps = [int(ts) for ts in timesteps]
    if not timesteps:
        timesteps = discover_timesteps(root)
    print(f"Comparing for timesteps: {timesteps}")
    print(f"Will use {DEFAULT_WORKERS} workers.")

    prefixes = ["prepre", "prepost", "corpre", "corpost"]

    with ProcessPoolExecutor(max_workers=DEFAULT_WORKERS) as ex:
        task_args = [(p, ts, str(root)) for p, ts in product(prefixes, timesteps)]
        for pref, ts, T in ex.map(wrapper, task_args):
            csvpath = root.joinpath(f"numeric_differences_prefix={pref}_ts={ts}.csv")
            print(f"Saving to: {csvpath}")
            T = T.sort(["got_file", "variable"])
            T.write_csv(csvpath, float_precision=None)

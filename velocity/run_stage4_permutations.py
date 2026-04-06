#!/usr/bin/env python3
"""
Generate all valid layout permutation configs, compile, and run.

Five groups:
  cv  COMPUTE_VERT   binary [0,1,2] or [1,0,2]
  ch  COMPUTE_HORIZ  binary [0,1,2] or [1,0,2]
  f   FIELDS         binary [0,1,2] or [1,0,2]
  s   STENCIL        binary [0,1,2] or [1,0,2]
  n   CONN           all 6 permutations of [0,1,2]

Total: 2 x 2 x 2 x 2 x 6 - 1 = 95 configs.
Each config compiles to 4 executables: {ms|mu} x {wnuma|wonuma}.
Output files are named {config}_{shuffled|unshuffled}_{wnuma|wonuma}_step{N}.txt
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path

from sc26_layout.permute_stage4 import PERMUTE_CONFIGS

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

STAGE    = os.getenv("_STAGE", "5")
BEVERIN  = os.getenv("BEVERIN", "0") == "1"

COMPILE_CMD    = f"python -m utils.stages.compile_gpu_stage{STAGE}_v2"
EXE_TEMPLATE   = f"./velocity_gpu.stage{STAGE}_standalone_release_permuted"
EXE_UNPERMUTED = f"./velocity_gpu.stage{STAGE}_standalone"
OUT_DIR        = Path(f"{'beverin_' if BEVERIN else 'daint_'}full_permutations_{STAGE}")

# Internal suffix → human label mapping
_SHUFFLE_VARIANTS = [
    ("ms", "shuffled"),
    ("mu", "unshuffled"),
]

_NUMA_VARIANTS = [
    ("_wnuma",  "wnuma"),
    ("_wonuma", "wonuma"),
]

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def ensure_out_dir():
    OUT_DIR.mkdir(exist_ok=True)


def compile_config(name: str) -> bool:
    """Compile all 4 variants (ms/mu x wnuma/wonuma) for *name*."""
    cmd = f"{COMPILE_CMD} --compile --optimize --permutations {name}"
    print(f"[compile] {cmd}")
    ret = subprocess.run(cmd, shell=True)
    if ret.returncode != 0:
        print(f"[compile] FAILED for {name} (rc={ret.returncode})", file=sys.stderr)
    return ret.returncode == 0


def _exe(name: str, shuffle_suffix: str, numa_suffix: str) -> str:
    """Return the executable path for config *name*, shuffle suffix, and numa suffix."""
    return EXE_TEMPLATE + f"_{name}_{shuffle_suffix}{numa_suffix}"


def _exe_unpermuted(numa_suffix: str) -> str:
    """Return the unpermuted executable path for a numa variant."""
    release = os.getenv('_RELEASE', '0').lower() in ('1', 'true', 'yes')
    opt = "release" if release else "debug"
    return f"./velocity_gpu.stage{STAGE}_standalone_{opt}_unpermuted{numa_suffix}"


def _out_file(name: str, shuffle_label: str, numa_label: str) -> Path:
    """Return the output txt path."""
    return OUT_DIR / f"{name}_{shuffle_label}_{numa_label}.txt"


def compile_unpermuted() -> bool:
    cmd = f"{COMPILE_CMD} --compile --optimize --unpermuted"
    print(f"[compile] {cmd}")
    ret = subprocess.run(cmd, shell=True)
    if ret.returncode != 0:
        print(f"[compile] FAILED for unpermuted (rc={ret.returncode})", file=sys.stderr)
    return ret.returncode == 0


def run_config(name: str, shuffle_suffix: str, shuffle_label: str,
               numa_suffix: str, numa_label: str,
               reps: int = 100, ncu: bool = False) -> bool:
    ensure_out_dir()
    exe = _exe(name, shuffle_suffix, numa_suffix)

    if not os.path.exists(exe):
        print(f"[run] SKIP {exe} (not found)", file=sys.stderr)
        return False

    for step in [7, 9]:
        out_file = OUT_DIR / f"{name}_{shuffle_label}_{numa_label}_step{step}.txt"
        print(f"[run] {exe} step={step} -> {out_file}")
        with open(out_file, "w") as f:
            ret = subprocess.run(
                [exe, str(step), f"--reps={reps}"],
                stdout=f, stderr=subprocess.STDOUT,
            )
        if ret.returncode != 0:
            print(f"[run] FAILED for {name}/{shuffle_label}/{numa_label}/step{step} "
                  f"(rc={ret.returncode})", file=sys.stderr)
            return False

        if ncu:
            ncu_report = OUT_DIR / f"ncu_{name}_{shuffle_label}_{numa_label}_step{step}"
            ncu_log    = OUT_DIR / f"ncu_{name}_{shuffle_label}_{numa_label}_step{step}.txt"
            print(f"[ncu] {name}/{shuffle_label}/{numa_label}/step{step} -> {ncu_report}.ncu-rep")
            ncu_cmd = [
                "ncu", "--set", "full",
                "--import-source", "yes",
                "--clock-control", "none",
                "-f", "-o", str(ncu_report),
                exe, str(step), f"--reps={reps}",
            ]
            with open(ncu_log, "w") as f:
                subprocess.run(ncu_cmd, stdout=f, stderr=subprocess.STDOUT)

    return True


def run_unpermuted(reps: int = 100, ncu: bool = False):
    ensure_out_dir()
    for numa_suffix, numa_label in _NUMA_VARIANTS:
        exe = _exe_unpermuted(numa_suffix)
        if not os.path.exists(exe):
            print(f"[run] SKIP {exe} (not found)", file=sys.stderr)
            continue

        for step in [7, 9]:
            out_file = OUT_DIR / f"unpermuted_{numa_label}_step{step}.txt"
            print(f"[run] {exe} step={step} -> {out_file}")
            with open(out_file, "w") as f:
                ret = subprocess.run(
                    [exe, str(step), f"--reps={reps}"],
                    stdout=f, stderr=subprocess.STDOUT,
                )
            if ret.returncode != 0:
                print(f"[run] unpermuted/{numa_label} FAILED step={step} "
                      f"(rc={ret.returncode})", file=sys.stderr)

            if ncu:
                ncu_report = OUT_DIR / f"ncu_unpermuted_{numa_label}_step{step}"
                ncu_log    = OUT_DIR / f"ncu_unpermuted_{numa_label}_step{step}.txt"
                ncu_cmd = [
                    "ncu", "--set", "full",
                    "--import-source", "yes",
                    "--clock-control", "none",
                    "-f", "-o", str(ncu_report),
                    exe, str(step), f"--reps={reps}",
                ]
                with open(ncu_log, "w") as f:
                    subprocess.run(ncu_cmd, stdout=f, stderr=subprocess.STDOUT)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    # Named aliases excluded from the default sweep
    _NAMED = {"index_only", "nlev_first"}
    all_names = [k for k in PERMUTE_CONFIGS if k not in _NAMED]

    ap = argparse.ArgumentParser(description="Run stage-4 layout permutation sweep")
    ap.add_argument("--configs", type=str, default=None,
                    help="Comma-separated config names (default: all 95 sweep configs)")
    ap.add_argument("--unpermuted", action="store_true", default=False,
                    help="Also compile and run the unpermuted baseline")
    ap.add_argument("--reps",         type=int,  default=3)
    ap.add_argument("--ncu",          action="store_true", help="Run Nsight Compute")
    ap.add_argument("--compile-only", action="store_true")
    ap.add_argument("--run-only",     action="store_true")
    ap.add_argument("--dry-run",      action="store_true",
                    help="Print what would be compiled/run without doing it")
    ap.add_argument("--list",         action="store_true",
                    help="List all available config names and exit")
    args = ap.parse_args()

    if args.list:
        print("Sweep configs:")
        for name in all_names:
            if name in _NAMED:
                continue
            if "cv0" in name:
                continue
            pm = PERMUTE_CONFIGS[name]["permute_map"]
            print(f"  {name:40s}  ({len(pm):2d} arrays permuted)")
        print(f"\nNamed configs:")
        for name in _NAMED:
            if name not in PERMUTE_CONFIGS:
                continue
            if "cv0" in name:
                continue
            pm = PERMUTE_CONFIGS[name]["permute_map"]
            print(f"  {name:40s}  ({len(pm):2d} arrays permuted)")
        sweep_count = sum(1 for n in all_names if n not in _NAMED and "cv0" not in n)
        named_count = sum(1 for n in _NAMED if n in PERMUTE_CONFIGS and "cv0" not in n)
        print(f"\nSweep total : {sweep_count} configs")
        print(f"Named total : {named_count} configs")
        return

    # Resolve selection
    if args.configs:
        selected = []
        for c in args.configs.split(","):
            c = c.strip()
            if c not in PERMUTE_CONFIGS:
                print(f"Unknown config: {c}", file=sys.stderr)
                print(f"Use --list to see available configs", file=sys.stderr)
                sys.exit(1)
            selected.append(c)
    elif args.unpermuted:
        selected = []   # --unpermuted alone: skip sweep entirely
    else:
        selected = all_names

    # Summary
    n_exes = len(selected) * len(_SHUFFLE_VARIANTS) * len(_NUMA_VARIANTS)
    print(f"{'=' * 60}")
    print(f"Layout permutation sweep: {len(selected)} configs  "
          f"({n_exes} executables)")
    if args.unpermuted:
        print(f"  + unpermuted baseline ({len(_NUMA_VARIANTS)} variants)")
    print(f"Output directory: {OUT_DIR}/")
    print(f"{'=' * 60}")
    for name in selected:
        pm = PERMUTE_CONFIGS[name]["permute_map"]
        for shuf_suffix, shuf_label in _SHUFFLE_VARIANTS:
            for numa_suffix, numa_label in _NUMA_VARIANTS:
                exe = _exe(name, shuf_suffix, numa_suffix)
                out = _out_file(name, shuf_label, numa_label)
                print(f"  {name:40s}  [{shuf_label:10s} {numa_label:6s}]  "
                      f"exe={exe}")
    print()

    if args.dry_run:
        return

    ensure_out_dir()

    # Unpermuted baseline
    if args.unpermuted:
        print(f"\n{'=' * 60}")
        print(f"Unpermuted baseline")
        print(f"{'=' * 60}")
        if not args.run_only:
            compile_unpermuted()
        if not args.compile_only:
            run_unpermuted(reps=args.reps, ncu=args.ncu)

    # Each permuted config
    for name in selected:
        print(f"\n{'=' * 60}")
        print(f"Config: {name}")
        print(f"{'=' * 60}")

        if not args.run_only:
            # Check if all 4 executables already exist
            all_exist = all(
                os.path.exists(_exe(name, shuf_suffix, numa_suffix))
                for shuf_suffix, _ in _SHUFFLE_VARIANTS
                for numa_suffix, _ in _NUMA_VARIANTS
            )
            if all_exist:
                print(f"[skip] {name}: all executables already exist")
            else:
                ok = compile_config(name)
                if not ok:
                    print(f"[skip] {name}: compile failed, skipping run")
                    continue

        if not args.compile_only:
            for shuf_suffix, shuf_label in _SHUFFLE_VARIANTS:
                for numa_suffix, numa_label in _NUMA_VARIANTS:
                    run_config(name, shuf_suffix, shuf_label,
                               numa_suffix, numa_label,
                               reps=args.reps, ncu=args.ncu)

    # Final summary
    if not args.compile_only and not args.dry_run:
        print(f"\n{'=' * 60}")
        print(f"Done. Results in {OUT_DIR}/")
        for f in sorted(OUT_DIR.glob("*.txt")):
            print(f"  {f}")


if __name__ == "__main__":
    main()
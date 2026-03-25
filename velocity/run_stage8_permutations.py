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
Each config compiles to 2 executables: _ms (map-shuffled) and _mu (map-unshuffled).
Output files are named {config}_{ms|mu}.txt  →  displayed as shuffled/unshuffled.
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path

from sc26_layout.permute_stage8 import PERMUTE_CONFIGS

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

STAGE    = os.getenv("_STAGE", "8")
BEVERIN  = os.getenv("BEVERIN", "0") == "1"
LOWERED = os.getenv("_REDUCE_BITWIDTH_TRANSFORMATION", "0") == "1"
LOWERED_PREFIX = "lowered_" if LOWERED else ""
LOWERED_SUFFIX = "_lowered" if LOWERED else ""
COMPILE_CMD    = f"python -m utils.stages.compile_gpu_stage{STAGE}"


EXE_TEMPLATE   = f"./velocity_gpu{LOWERED_SUFFIX}.stage{STAGE}_standalone_release_permuted"
EXE_UNPERMUTED = f"./velocity_gpu{LOWERED_SUFFIX}.stage{STAGE}_standalone_release_unpermuted{LOWERED_SUFFIX}"
OUT_DIR        = Path(f"{'beverin_' if BEVERIN else 'daint_'}{LOWERED_PREFIX}full_permutations_{STAGE}")

# Internal suffix → human label mapping
_SHUFFLE_VARIANTS = [
    ("ms", "shuffled"),
    ("mu", "unshuffled"),
]

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def ensure_out_dir():
    OUT_DIR.mkdir(exist_ok=True)


def compile_config(name: str) -> bool:
    """Compile both ms and mu variants for *name* in one call."""
    cmd = f"{COMPILE_CMD} --compile --permutations {name}"
    print(f"[compile] {cmd}")
    ret = subprocess.run(cmd, shell=True)
    if ret.returncode != 0:
        print(f"[compile] FAILED for {name} (rc={ret.returncode})", file=sys.stderr)
    return ret.returncode == 0


def _exe(name: str, suffix: str) -> str:
    """Return the executable path for config *name* and shuffle suffix *suffix*."""
    return EXE_TEMPLATE + f"_{name}_{suffix}{LOWERED_SUFFIX}"


def _out_file(name: str, label: str) -> Path:
    """Return the output txt path: {name}_{label}.txt  (label = shuffled|unshuffled)."""
    return OUT_DIR / f"{name}_{label}.txt"


def compile_unpermuted() -> bool:
    cmd = f"{COMPILE_CMD} --compile --unpermuted"
    print(f"[compile] {cmd}")
    ret = subprocess.run(cmd, shell=True)
    if ret.returncode != 0:
        print(f"[compile] FAILED for unpermuted (rc={ret.returncode})", file=sys.stderr)
    return ret.returncode == 0


def run_config(name: str, suffix: str, label: str, reps: int = 100, ncu: bool = False) -> bool:
    ensure_out_dir()
    exe = _exe(name, suffix)

    for step in [7, 9]:
        out_file = OUT_DIR / f"{name}_{label}_step{step}.txt"
        print(f"[run] {exe} step={step} -> {out_file}")
        with open(out_file, "w") as f:
            ret = subprocess.run(
                [exe, str(step), f"--reps={reps}"],
                stdout=f, stderr=subprocess.STDOUT,
            )
        if ret.returncode != 0:
            print(f"[run] FAILED for {name}/{label}/step{step} (rc={ret.returncode})",
                  file=sys.stderr)
            return False

        if ncu:
            ncu_report = OUT_DIR / f"ncu_{name}_{label}_step{step}"
            ncu_log    = OUT_DIR / f"ncu_{name}_{label}_step{step}.txt"
            print(f"[ncu] {name}/{label}/step{step} -> {ncu_report}.ncu-rep")
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
    for step in [7, 9]:
        out_file = OUT_DIR / f"unpermuted_step{step}.txt"
        print(f"[run] {EXE_UNPERMUTED} step={step} -> {out_file}")
        with open(out_file, "w") as f:
            ret = subprocess.run(
                [EXE_UNPERMUTED, str(step), f"--reps={reps}"],
                stdout=f, stderr=subprocess.STDOUT,
            )
        if ret.returncode != 0:
            print(f"[run] unpermuted FAILED step={step} (rc={ret.returncode})",
                  file=sys.stderr)

        if ncu:
            ncu_report = OUT_DIR / f"ncu_unpermuted_step{step}"
            ncu_log    = OUT_DIR / f"ncu_unpermuted_step{step}.txt"
            ncu_cmd = [
                "ncu", "--set", "full",
                "--import-source", "yes",
                "--clock-control", "none",
                "-f", "-o", str(ncu_report),
                EXE_UNPERMUTED, str(step), f"--reps={reps}",
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

    ap = argparse.ArgumentParser(description="Run stage-8 layout permutation sweep")
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
        #selected = [n for n in all_names if "cv0" not in n]


    # Summary
    print(f"{'=' * 60}")
    print(f"Layout permutation sweep: {len(selected)} configs  "
          f"({len(selected) * 2} executables)")
    if args.unpermuted:
        print(f"  + unpermuted baseline")
    print(f"Output directory: {OUT_DIR}/")
    print(f"{'=' * 60}")
    for name in selected:
        pm = PERMUTE_CONFIGS[name]["permute_map"]
        for suffix, label in _SHUFFLE_VARIANTS:
            exe      = _exe(name, suffix)
            out_file = _out_file(name, label)
            print(f"  {name:40s}  [{label:10s}]  exe={exe}  out={out_file}")
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
            # Check if both executables already exist
            both_exist = all(
                os.path.exists(_exe(name, suffix))
                for suffix, _ in _SHUFFLE_VARIANTS
            )
            if both_exist:
                print(f"[skip] {name}: both executables already exist")
            else:
                ok = compile_config(name)
                if not ok:
                    print(f"[skip] {name}: compile failed, skipping run")
                    continue

        if not args.compile_only:
            for suffix, label in _SHUFFLE_VARIANTS:
                run_config(name, suffix, label, reps=args.reps, ncu=args.ncu)

    # Final summary
    if not args.compile_only and not args.dry_run:
        print(f"\n{'=' * 60}")
        print(f"Done. Results in {OUT_DIR}/")
        for f in sorted(OUT_DIR.glob("*.txt")):
            print(f"  {f}")


if __name__ == "__main__":
    main()
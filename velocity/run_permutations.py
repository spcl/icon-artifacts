#!/usr/bin/env python3
"""
Generate all valid layout permutation configs, compile, and run.

Compute arrays (z_ekinh, z_kin_hor_e): [0,1,2] or [1,0,2]
Edge arrays (edge_idx, edge_blk): any permutation of [0,1,2]  (tied together)
BLN array (e_bln_c_s): any permutation of [0,1,2]  (independent)

Total: 2 x 6 x 6 - 1 (identity) = 71 configs
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path

# ---------------------------------------------------------------------------
# Import configs from the same place permute_single_map_gpu uses them
# ---------------------------------------------------------------------------

from sc26_layout.extract_gpu_kernel import PERMUTE_CONFIGS

# ---------------------------------------------------------------------------
# Constants
# ---------------------------------------------------------------------------

STAGE = os.getenv("_STAGE", "6")  # default to stage 6, can be overridden with env var
BEVERIN = os.getenv("BEVERIN", "0") == "1"
SUFFIX = os.getenv("_SUFFIX", "")

V2 = os.getenv("V2", "0") == "1"
if V2:
    V2STAGE = str(int(STAGE)-1)
    COMPILE_CMD = f"python -m utils.stages.compile_gpu_stage{STAGE}_v2"
else:
    COMPILE_CMD = f"python -m utils.stages.compile_gpu_stage{STAGE}"

EXE_TEMPLATE = f"./velocity_gpu.stage{STAGE}_standalone_release_permuted"
EXE_UNPERMUTED = f"./velocity_gpu.stage{STAGE}_standalone_release_unpermuted"

OUT_DIR = Path(f"{'beverin_' if BEVERIN else 'daint_'}{SUFFIX}permutations_{STAGE}")


# ---------------------------------------------------------------------------
# Compile & run helpers
# ---------------------------------------------------------------------------

def ensure_out_dir():
    OUT_DIR.mkdir(exist_ok=True)


def compile_config(name):
    cmd = f"{COMPILE_CMD} --optimize --compile --permutations {name}"
    print(f"[compile] {cmd}")
    ret = subprocess.run(cmd, shell=True)
    if ret.returncode != 0:
        print(f"[compile] FAILED for {name} (rc={ret.returncode})", file=sys.stderr)
    return ret.returncode == 0

def run_config(name, shuffle_label, reps=100, ncu=False):
    ensure_out_dir()
    full_name = f"{name}_{shuffle_label}"
    exe = EXE_TEMPLATE + f"_{full_name}"
    out_file = OUT_DIR / f"{full_name}.txt"

    print(f"[run] {exe} -> {out_file}")
    with open(out_file, "w") as f:
        ret = subprocess.run(
            [exe] + (["9", f"--reps={reps}"] if reps > 1 else []),
            stdout=f, stderr=subprocess.STDOUT,
        )
    if ret.returncode != 0:
        print(f"[run] FAILED for {full_name} (rc={ret.returncode})", file=sys.stderr)
        return False

    if ncu:
        ncu_report = OUT_DIR / f"ncu_{full_name}"
        ncu_log = OUT_DIR / f"ncu_{full_name}.txt"
        print(f"[ncu] {full_name} -> {ncu_report}.ncu-rep")
        ncu_cmd = [
            "ncu", "--set", "full",
            "--import-source", "yes",
            "--clock-control", "none",
            "-f", "-o", str(ncu_report),
            exe, "9", f"--reps={reps}",
        ]
        with open(ncu_log, "w") as f:
            subprocess.run(ncu_cmd, stdout=f, stderr=subprocess.STDOUT)

    return True


def compile_unpermuted():
    cmd = f"{COMPILE_CMD} --optimize --compile --permutations 'c012_e012_b021' --unpermuted"
    print(f"[compile] {cmd}")
    ret = subprocess.run(cmd, shell=True)
    if ret.returncode != 0:
        print(f"[compile] FAILED for unpermuted (rc={ret.returncode})", file=sys.stderr)
    return ret.returncode == 0


def run_unpermuted(reps=1, ncu=False):
    ensure_out_dir()
    out_file = OUT_DIR / "unpermuted.txt"

    print(f"[run] {EXE_UNPERMUTED} -> {out_file}")
    with open(out_file, "w") as f:
        ret = subprocess.run(
            [EXE_UNPERMUTED] + (["9", f"--reps={reps}"] if reps > 1 else []),
            stdout=f, stderr=subprocess.STDOUT,
        )
    if ret.returncode != 0:
        print(f"[run] unpermuted FAILED (rc={ret.returncode})", file=sys.stderr)

    if ncu:
        ncu_report = OUT_DIR / "ncu_unpermuted"
        ncu_log = OUT_DIR / "ncu_unpermuted.txt"
        print(f"[ncu] unpermuted -> {ncu_report}.ncu-rep")
        ncu_cmd = [
            "ncu", "--set", "full",
            "--import-source", "yes",
            "--clock-control", "none",
            "-f", "-o", str(ncu_report),
            EXE_UNPERMUTED, "9", f"--reps={reps}",
        ]
        with open(ncu_log, "w") as f:
            subprocess.run(ncu_cmd, stdout=f, stderr=subprocess.STDOUT)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    all_names = list(PERMUTE_CONFIGS.keys())

    ap = argparse.ArgumentParser(description="Run layout permutation sweep")
    ap.add_argument("--configs", type=str, default=None,
                    help="Comma-separated config names (default: all 71)")
    ap.add_argument("--unpermuted", action="store_true", default=False,
                    help="Also compile and run the unpermuted baseline")
    ap.add_argument("--reps", type=int, default=3)
    ap.add_argument("--ncu", action="store_true", help="Run Nsight Compute")
    ap.add_argument("--compile-only", action="store_true")
    ap.add_argument("--run-only", action="store_true")
    ap.add_argument("--dry-run", action="store_true",
                    help="Print configs without compiling or running")
    ap.add_argument("--list", action="store_true",
                    help="List all available config names and exit")
    args = ap.parse_args()

    if args.list:
        for name in all_names:
            pm = PERMUTE_CONFIGS[name]["permute_map"]
            print(f"  {name:30s}  ({len(pm)} arrays permuted)")
        print(f"\nTotal: {len(all_names)} configs")
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
    else:
        selected = all_names

    # Summary
    print(f"{'=' * 60}")
    print(f"Layout permutation sweep: {len(selected)} configs")
    if args.unpermuted:
        print(f"  + unpermuted baseline")
    print(f"Output directory: {OUT_DIR}/")
    print(f"{'=' * 60}")
    for name in selected:
        pm = PERMUTE_CONFIGS[name]["permute_map"]
        print(f"  {name:30s}  ({len(pm)} arrays permuted)")
    print()

    if args.dry_run:
        return

    ensure_out_dir()

    # Unpermuted baseline (compile + run first so it's available for comparison)
    if args.unpermuted:
        print(f"\n{'=' * 60}")
        print(f"Unpermuted baseline")
        print(f"{'=' * 60}")
        if not args.run_only:
            compile_unpermuted()
        if not args.compile_only:
            run_unpermuted(reps=args.reps, ncu=args.ncu)

    # Each permuted config
    #raise Exception(selected)
    for name in selected:
        print(f"\n{'=' * 60}")
        print(f"Config: {name}")
        print(f"{'=' * 60}")

        if not args.run_only:
            # compile_config produces both shuffled and unshuffled
            ok = compile_config(name)
            if not ok:
                print(f"[skip] {name}: compile failed, skipping run")
                continue
            exe_s = EXE_TEMPLATE + f"_{name}_shuffled"
            exe_u = EXE_TEMPLATE + f"_{name}_unshuffled"
            if os.path.exists(exe_s) and os.path.exists(exe_u):
                print(f"[skip] {name}: executables already exist")
                ok = True
            else:
                ok = compile_config(name)
            if not ok:
                print(f"[skip] {name}: compile failed, skipping run")
                continue

        if not args.compile_only:
            for shuffle_label in ["shuffled", "unshuffled"]:
                run_config(name, shuffle_label, reps=args.reps, ncu=args.ncu)

    # Final summary
    if not args.compile_only and not args.dry_run:
        print(f"\n{'=' * 60}")
        print(f"Done. Results in {OUT_DIR}/")
        for f in sorted(OUT_DIR.glob("*.txt")):
            print(f"  {f}")


if __name__ == "__main__":
    main()
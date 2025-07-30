import dace
from dace import SDFG
from dace.sdfg.state import LoopRegion
from dace.transformation.interstate.loop_to_map import LoopToMap
from stages import common
from utils.codegen_from_sdfg import ArtifactMode, OptimizationMode
from utils.gpu_offloading_wo_host_dev_copies import (
    gpu_offloading_wo_host_dev_copies,
)
from utils.set_transient_storage_to_persistent import (
    set_transient_storage_to_persistent,
    check_transients_in_nsdfgs,
    clean_view_descs,
)
from utils.profiling_patches import (
    insert_timers_for_profiling,
    insert_synchronization_for_profiling,
)
from utils.assignment_and_copy_kernel_to_memset_and_memcpy import (
    AssignmentAndCopyKernelToMemsetAndMemcpy,
)

from utils.int64_to_int32 import int64_to_int32 as int64_to_int32

import argparse


STAGE_ID = 3


def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""

    # === Sub-Phase 1: Offloading ===
    # Add GPU copy-in and copy-out to the flattener/copy-in and deflattener/copy-out states
    # add_gpu_copies_to_flattener(g)
    # Perform the offloading with the assumption that all kernels purely run on the GPU
    # Also adds copies to flatten nodes
    # Replaces the velocity tendencies tasklet accordingly
    gpu_offloading_wo_host_dev_copies(g)
    g.validate()
    # === Sub-Phase 1: Offloading ===

    # === Sub-Phase 2: Allocation Optimizations ===
    clean_view_descs(g)
    g.validate()
    set_transient_storage_to_persistent(g)
    g.validate()
    check_transients_in_nsdfgs(g)
    g.validate()
    # === Sub-Phase 2: Allocation Optimizations ===

    # === Sub-Phase 3: Post-GPU Optimizations ===
    # Catch kernels that can be replaced with memset and memcpy
    AssignmentAndCopyKernelToMemsetAndMemcpy().apply_pass(g, {})
    g.validate()
    # Make sure all connector types match with parent SDFG's symbol and data types, propagate inwards
    # Also make all int64 symbols and top-level transients into int32
    # I verbose print indicates that DyCore SDFGs are not plagued by the int64 vs int32 symbol typecasts
    # and this function takes quite a while, so it can be later disabled
    # And it can break codege
    # int64_to_int32(g)
    g.validate()
    # === Sub-Phase 3: Post-GPU Optimizations ===

    # === Sub-Phase 4: Bitwidth Lowering Transformations ===
    # === Sub-Phase 4: Bitwidth Lowering Transformations ===

    # === Sub-Phase 5: Profiling Patches (Make sure this is the last phase) ===
    insert_synchronization_for_profiling(g)
    g.validate()
    insert_timers_for_profiling(g)
    g.validate()
    # === Sub-Phase 5: Profiling Patches (Make sure this is the last phase) ===

    return g


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument("--optimize", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument("--codegen", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument("--compile", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument(
        "--mode",
        type=ArtifactMode,
        choices=list(ArtifactMode),
        required=False,
        default=ArtifactMode.EXEC,
        help="Select the mode: static, shared, or exec",
    )
    argp.add_argument(
        "--release",
        action=argparse.BooleanOptionalAction,
        default=False,
        help="Enable release mode optimizations and hardening.",
    )
    args = argp.parse_args()
    if not args.optimize and not args.codegen and not args.compile:
        args.optimize, args.codegen, args.compile = True, True, True

    names = common.sdfg_names()

    if args.optimize:
        sdfgs = {}
        for name in names:
            infile = common.stage_input(name, STAGE_ID)
            outfile = common.stage_output(name, STAGE_ID)

            print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")

            g = SDFG.from_file(infile)
            g.name = name
            g.validate()

            g = optimization_action(g)

            g.save(outfile, compress=True)
            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfgs[name] = g

    if args.codegen:
        # Read back the written files as we prepare for compilation.
        sdfgs = {name: SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        print(f"Stage #{STAGE_ID}: Generating code for {len(sdfgs)} SDFGs")
        common.codegen_action(STAGE_ID, sdfgs)

    if args.compile:
        print(f"Stage #{STAGE_ID}: Compiling SDFGs")
        common.compile_action(STAGE_ID, args.mode, OptimizationMode.RELEASE if args.release else OptimizationMode.DEBUG)


if __name__ == "__main__":
    main()

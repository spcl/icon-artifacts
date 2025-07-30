from dace import SDFG
from dace.transformation.dataflow import MapCollapse
from dace.transformation.passes.constant_propagation import ConstantPropagation
from stages import common
from utils.codegen_from_sdfg import ArtifactMode
from dace.transformation.interstate import InlineSDFG
from utils.count import count_map_dimensions
from utils.count import count_uncollapsed_maps
from utils.conditional_pruning import cleanup_conditionals

from utils.clean_unused_data_from_nsdfg_connectors import (
    clean_unused_data_from_nsdfg,
    clean_unused_symbols_from_nsdfg,
)
from utils.manual_fixes import move_range_if_inside
import argparse
from utils.map_condition_swap import move_if_to_innermost_map
from utils.move_for_cfg_inside_map import move_for_cfg_inside_map_pass
from utils.move_if_cfg_inside_map import move_if_cfg_inside_map_pass
from utils.specialize_scalar import specialize_scalar
from utils.state_fusion_without_copyin_and_copyout import state_fusion_without_copyin_and_copyout
STAGE_ID = 2

def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    # === Sub-Phase 0: Try to const-eval branch conditions ===
    cleanup_conditionals(g)
    # === Sub-Phase 0: Try to const-eval branch conditions ===

    # === Sub-Phase 1: Move Loops inside Maps ===
    # If we have `nlev [ nproma ]` where nlev is a loop and nproma is a map,
    # make it into `nproma [ nlev ]` where nlev is a loop and nproma is a map
    # This should work, as nproma is independent already the dependency can be only
    # due to nlev, otherwise both would be loop
    num_applied = move_for_cfg_inside_map_pass(g)
    g.validate()
    # It was written fastly, it generates unnecessary maps
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    print(f"Stage #{STAGE_ID}: Moved {num_applied} for loops inside maps")
    # === Sub-Phase 1: Move Loops inside Maps ===

    # === Sub-Phase 2: Specialize nlev and nlevp1 ===
    # Specialize some scalars
    specialize_scalar(g, "nlevp1", 91)
    g.validate()
    specialize_scalar(g, "nlev", 90)
    g.validate()
    # Constprop with the new constants
    ConstantPropagation().apply_pass(g, {})
    state_fusion_without_copyin_and_copyout(g)
    # === Sub-Phase 2: Specialize nlev and nlevp1  ===

    # === Sub-Phase 3: Clean Unused Data and Symbols From NSDFGs ===
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    # Move if condition inside a map if it has a parent map to enable collapsing
    move_if_to_innermost_map(g)
    g.validate()
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    # === Sub-Phase 3: Clean Unused Data and Symbols From NSDFGs ===

    # === Sub-Phase 4: InlineSDFG + MapCollapse For GPU Offloading ===
    for _ in range(3): # TODO: Maybe 2 is enough
        g.apply_transformations_repeated(
            InlineSDFG
        )
        g.apply_transformations_repeated(
            MapCollapse
        )
    count_map_dimensions(g)
    count_uncollapsed_maps(g, verbose=False, use_assert=True)
    # === Sub-Phase 4: InlineSDFG + MapCollapse For GPU Offloading  ===

    # === Sub-Phase 5: Clean Again ===
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    # === Sub-Phase 5: Clean Again ===


    # === Sub-Phase 6: Move ifs inside maps to enable more state fusion ===
    # Fused states as this transformation requires the body to have only one state
    # TODO: Make this pass be more selective (like a pass a list where we know the maps become fusable if we do it)
    state_fusion_without_copyin_and_copyout(g)
    g.validate()
    # In combination with predictor-pre this crashes. Skip for predictor pre. TODO: Fix it for predictor-pre
    if "predictor_pre" in g.name:
        print(f"Stage #{STAGE_ID}: Skipping moving ifs inside maps for {g.name} as it is predictor-pre. See TODOs.")
        num_applied = 0
    else:
        num_applied = move_if_cfg_inside_map_pass(g, verbose=True)
        print(f"Stage #{STAGE_ID}: Moved {num_applied} ifs inside maps")
    g.validate()
    # === Sub-Phase 6: Move ifs inside maps to enable more state fusion  ===


    # === Sub-Phase 7: Move to Range If Inside ===
    # If pattern is Map -> NSDFG -> IF -> State (Map)
    # and inside'maps range depend on the if above
    # (that either of the value is the range of the inner map, then move in the if)
    # Handles a very specific pattern:
    # Map -> if 1 = range1, if2 = range 2 -> Map (range)
    # We make it into Map -> Map (max(range1, range2)) -> every thread checks the condition
    if "predictor_pre" in g.name:
        move_range_if_inside(g, "_for_it_101")
    g.validate()
    g.reset_cfg_list()
    g.reset_sdfg_list()
    # === Sub-Phase 7: Move to Range If Inside ===

    # === Sub-Phase 8: Re-collapse After Manual Improvements ===
    # Also do MapFusion, StateFusion etc.
    g.apply_transformations_repeated(
        InlineSDFG
    )
    g.validate()
    g.apply_transformations_repeated(
        MapCollapse
    )
    g.reset_cfg_list()
    g.reset_sdfg_list()
    g.validate()
    # TODO: MapFusion here
    count_map_dimensions(g)
    count_uncollapsed_maps(g, verbose=False, use_assert=True)
    state_fusion_without_copyin_and_copyout(g)
    g.validate()
    # === Sub-Phase 8: Re-collapse After Manual Improvements ===

    return g


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument(
        "--optimize", action=argparse.BooleanOptionalAction, default=False
    )
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
        sdfgs = {
            name: SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names
        }
        print(f"Stage #{STAGE_ID}: Generating code for {len(sdfgs)} SDFGs")
        common.codegen_action(STAGE_ID, sdfgs)

    if args.compile:
        print(f"Stage #{STAGE_ID}: Compiling SDFGs")
        common.compile_action(STAGE_ID, args.mode)


if __name__ == "__main__":
    main()

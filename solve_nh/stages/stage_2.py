import dace
from dace import SDFG
from dace.sdfg.state import LoopRegion
from dace.transformation.dataflow import MapCollapse
from dace.transformation.interstate.loop_to_map import LoopToMap
from stages import common
from utils.codegen_from_sdfg import ArtifactMode
from dace.transformation.interstate import InlineSDFG
from utils.count import count_map_dimensions
from utils.count import count_uncollapsed_maps

from utils.clean_unused_data_from_nsdfg_connectors import (
    clean_unused_data_from_nsdfg,
    clean_unused_symbols_from_nsdfg,
)
from utils.manual_fixes import move_range_if_inside
import argparse


STAGE_ID = 2

def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    # === Sub-Phase 1: Clean Unused Data and Symbols From NSDFGs ===
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    # === Sub-Phase 1: Clean Unused Data and Symbols From NSDFGs ===

    # === Sub-Phase 2: InlineSDFG + MapCollapse For GPU Offloading ===
    for _ in range(3): # TODO: Maybe 2 is enough
        g.apply_transformations_repeated(
            InlineSDFG
        )
        g.apply_transformations_repeated(
            MapCollapse
        )
    count_map_dimensions(g)
    count_uncollapsed_maps(g, verbose=False, use_assert=True)
    # === Sub-Phase 2: InlineSDFG + MapCollapse For GPU Offloading  ===

    # === Sub-Phase 3: Clean Again ===
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    # === Sub-Phase 3: Clean Again ===

    # === Sub-Phase 4: Move to Range If Inside ===
    # If pattern is Map -> NSDFG -> IF -> State (Map)
    # and inside'maps range depend on the if above
    # (that either of the value is the range of the inner map, then move in the if)
    if "predictor_pre" in g.name:
        move_range_if_inside(g, "_for_it_101")
    # === Sub-Phase 4: Move to Range If Inside ===

    # === Sub-Phase 5: Re-collapse After Manual Improvements ===
    g.apply_transformations_repeated(
        InlineSDFG
    )
    g.apply_transformations_repeated(
        MapCollapse
    )
    count_map_dimensions(g)
    count_uncollapsed_maps(g, verbose=False, use_assert=True)
    # === Sub-Phase 5: Re-collapse After Manual Improvements ===

    # === Sub-Phase 6: Remaining Loops To Sequential Maps ===
    # For simplicity of implementation in later stages, convert remaining loops to sequential maps
    # Breaks validation: TODO make GPU offloading work with parent loops
    #iterator_names = set()
    #for node, graph in g.all_nodes_recursive():
    #    if isinstance(node, LoopRegion):
    #        it_var = node.loop_variable
    #        iterator_names.add(it_var)
    #        LoopToMap.apply_to(sdfg=graph.sdfg, loop=node, permissive=True, options={"ballin": True})
    #
    #for n, graph in g.all_nodes_recursive():
    #    if isinstance(n, dace.sdfg.nodes.MapEntry):
    #        if len(n.map.params) == 1 and n.map.params[0] in iterator_names:
    #            n.map.schedule = dace.dtypes.ScheduleType.Sequential
    #            n.map.unroll = False
    #
    #for n, graph in g.all_nodes_recursive():
    #    if isinstance(n, dace.sdfg.nodes.MapEntry):
    #        params = n.map.params
    #        has_loop_it_names = any([(p in iterator_names) for p in params])
    #        if has_loop_it_names:
    #            assert len(params) == 1, (
    #                f"Expected only one loop iterator name in map {n.map.name}, got {params}"
    #            )
    #            assert n.map.schedule == dace.dtypes.ScheduleType.Sequential, (
    #                f"Expected map {n.map.name} to be sequential, got {n.map.schedule}"
    #            )
    # === Sub-Phase 6: Remaining Loops To Sequential Maps ===

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

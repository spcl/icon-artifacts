import dace
from dace import SDFG
from utils.inject_velocity_shim import inject_velocity_shim
from stages import common
from utils.codegen_from_sdfg import Mode

import argparse

from dace.transformation.interstate import ContinueToCondition, LoopToMap
from dace.transformation.passes import (
    StructToContainerGroups,
    SymbolPropagation,
    ConstantPropagation,
)

from utils.count import count_loops
from utils.clean_partial_view_towers import (
    clean_partial_view_towers,
    clean_trivial_view_pattern,
)
from utils.add_missing_symbols import (
    add_missing_symbols_to_nsdfgs,
    add_missing_data_and_symbols_to_all_nsdfgs
)
from utils.promote_function_access_in_map_range_to_symbol import (
    promote_function_access_in_map_range_to_symbol,
)
from utils.loop_locality import make_array_loop_local
from utils.state_fusion_without_copyin_and_copyout import state_fusion_without_copyin_and_copyout
from utils.post_stage1_fixes import post_stage1_fixes
from utils.reinject_velocity_tasklet import reinject_velocity_shim
STAGE_ID = 1


def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    # === Sub-Phase 1: Flattening ===
    g.apply_transformations_repeated(ContinueToCondition)
    clean_partial_view_towers(g)
    StructToContainerGroups(
        validate=False,
        save_steps=False,
        verbose=False,
        simplify=False,
        interface_with_struct_copy=True,
        interface_to_gpu=False,
        clean_trivial_views=True,
        shallow_copy=False,
        shallow_copy_to_gpu=False,
        taskloop=False,
        dont_prune_unused_containers=True,
    ).apply_pass(g, {})
    clean_trivial_view_pattern(g)
    reinject_velocity_shim(g)
    g.validate()
    # Until this point we numerically validate
    # === Sub-Phase 1: Flattening ===

    # === Sub-Phase 2: Simplify and Patch ===
    # Simplify results with NestedSDFGs having missing symbols
    g.simplify(skip=["ArrayElimination", "FuseStates", "DeadDataflowElimination"], validate=False)
    # Add missing symbols and data to NSDFGs to make it valid
    add_missing_data_and_symbols_to_all_nsdfgs(g)
    g.validate()
    # === Sub-Phase 2: Simplify and Patch ===

    # === Sub-Phase 3: SymbolPropagation + Simplify + FuseState Without CopyIn/CopyOut ===
    # Until this point we numerically validate
    SymbolPropagation().apply_pass(g, {})
    g.validate()
    # Until this point we numerically validate
    g.simplify(skip=["ArrayElimination", "FuseStates", "DeadDataflowElimination"], validate=False)
    # Do not fuse the copy-in or the copy-out state (flatten/deflatten access nodes being fused with the rest of the maps make
    # offloading much harder)
    state_fusion_without_copyin_and_copyout(g)
    g.validate()
    # === Sub-Phase 3: SymbolPropagation + Simplify + FuseState Without CopyIn/CopyOut ===

    # === Sub-Phase 4: ConstantPropagation ===
    ConstantPropagation().apply_pass(g, {})
    g.validate()
    # === Sub-Phase 4: ConstantPropagation ===

    # === Sub-Phase 5: Loop Preprocessing ===
    # Ensure loop locality for ballin LoopToMap
    if g.name == "solve_nh_predictor_pre":
        make_array_loop_local(g, "z_ddt_vn_ray", "FOR_l_1156_c_1156")
    elif g.name == "solve_nh_corrector_pre":
        make_array_loop_local(g, "z_ddt_vn_ray", "FOR_l_1712_c_1712")
    g.validate()
    # === Sub-Phase 5: Loop Preprocessing ===

    # === Sub-Phase 6: LoopToMap + LoopToMap-Patches ===
    g.apply_transformations_repeated(
        LoopToMap, permissive=True, options={"ballin": True}
    )
    # Map ranges have expressions such nflatlev(jg - 1) as Sympy expresses array accesses as functions
    # This function promotes this to nflatlev_sym_0 = nflatlev[jg - 1] in the previous interstate (or
    # creates it), adds to NestedSDFG through an inconnector and updates map range to use nflatlev_sym_0
    promote_function_access_in_map_range_to_symbol(g)

    # Do not add missing symbols to NSDFGs before promiting nflatlev access to
    # data access, otherwise nflatlev will be registered as a symbol already
    add_missing_data_and_symbols_to_all_nsdfgs(g)

    #add_missing_symbols_to_nsdfgs(g)
    g.validate()
    # === Sub-Phase 6: LoopToMap + LoopToMap-Patches ===


    # === Sub-Phase 7: Last Simplify + StateFusion ===
    # One final simplify to fuse states (there are many 2-state NestedSDFGs where first state and iedge are empty)
    g.simplify(skip=["ArrayElimination", "FuseStates", "DeadDataflowElimination"], validate=False)

    # Do not fuse the copy-in or the copy-out state (flatten/deflatten access nodes being fused with the rest of the maps make
    # offloading much harder)
    state_fusion_without_copyin_and_copyout(g)

    g.validate()
    count_loops(g, verbose=False, use_assert=True)
    # === Sub-Phase 7: Last Simplify + StateFusion ===

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
        type=Mode,
        choices=list(Mode),
        required=False,
        default=Mode.EXEC,
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

import dace
from dace import SDFG
from dace.sdfg.state import LoopRegion
from dace.transformation.passes.scalar_to_symbol import ScalarToSymbolPromotion
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
    promote_function_access_in_loop_range_to_symbol
)
from utils.loop_locality import make_array_loop_local
from utils.state_fusion_without_copyin_and_copyout import state_fusion_without_copyin_and_copyout
from utils.post_stage1_fixes import post_stage1_fixes
from utils.reinject_velocity_tasklet import reinject_velocity_shim

from utils.transify_kernel_scalars import (
    transify_kernel_scalars,
    transify_targeted_scalar,
    retransify_scalar_with_local_prefix,
)

from utils.add_data_preserver_tasklets import add_data_preserver_tasklets

from utils.manual_fixes import (
    connect_ishift_to_map,
)

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

    # === Sub-Phase 6: Loop Preprocessing ===
    # Map ranges have expressions such nflatlev(jg - 1) as Sympy expresses array accesses as functions
    # This function promotes this to nflatlev_sym_0 = nflatlev[jg - 1] in the previous interstate (or
    # creates it), adds to NestedSDFG through an inconnector and updates map range to use nflatlev_sym_0
    promote_function_access_in_loop_range_to_symbol(g, g)
    # Replace non-transient scalars that could be transients with transient thread-local scalars to enable more loops to become maps
    # Might need to extend this
    thread_local_scalar_candidates = {
        "lvn_pos",
        "z_ddt_vn_apc",
        "z_b",
        "z_w_expl",
        "z_c",
        "z_theta_v_pr_ic",
        "zf",
        "z_ddt_vn_ray",
        "z_q",
        "ikp1",
        "ilc0",
        "ishift",
        "z_ntdistv_bary_2",
        "z_exner_ic",
        "z_w_concorr_mc_m0",
        "z_ddt_vn_pgr",
        "z_d_vn_dmp",
        "ibc0",
        "nlen_gradp",
        "distv_bary_2",
        "z_gamma",
        "z_theta_tavg",
        "z_w_concorr_mc_m2",
        "z_flxdiv_mass",
        "z_theta2",
        "z_ntdistv_bary_1",
        "z_theta_v_pr_mc",
        "z_w_concorr_mc_m1",
        "z_a",
        "ic",
        "z_d_vn_iau",
        "z_g",
        "z_rho_tavg",
        "z_rho_tavg_m1",
        "ikp2",
        "z_w_backtraj",
        "z_theta1",
        "z_ddt_vn_cor",
        "z_theta_tavg_m1",
        "distv_bary_1",
        "z_ddt_vn_dyn",
        "z_theta_v_pr_mc_m2",
        "z_contr_w_fl_l",
        "z_graddiv2_vn",
        "z_theta_v_pr_mc_m1",
        "je",
        "jb",
        "jc",
        "i_startidx",
        "i_endidx",
    }
    # First fuse as much as possible, as the heuristic to detect a scalar as transient
    # is based on the number of accesses to it, and if the states are not fused, it might have
    # in-degree = 0 in state 1 but only written to state 0
    state_fusion_without_copyin_and_copyout(g)
    transify_targeted_scalar(g, thread_local_scalar_candidates)
    # === Sub-Phase 6: Loop Preprocessing ===

    # === Sub-Phase 7: LoopToMap + LoopToMap-Patches ===
    g.apply_transformations_repeated(
        LoopToMap, permissive=False, options={"ballin": False}
    )
    count_loops(g, verbose=True, use_assert=False)

    # Do not add missing symbols to NSDFGs before promiting nflatlev access to
    # data access, otherwise nflatlev will be registered as a symbol already
    # add_missing_data_and_symbols_to_all_nsdfgs(g)
    # add_missing_symbols_to_nsdfgs(g)

    # Manually checked loops that can become maps:
    # SDFG Name | Loop Variable | Loop Label
    # TODO: Probably no nproma map should be left.
    manual_loop_to_map = {
        # solve_nh_corrector_post - Stage #1
        # ("corrector_post", "_for_it_0", "FOR_l_1784_c_1784"),    # Can't
        ("corrector_post", "_for_it_15", "FOR_l_1840_c_1840"),     # OK - no-read-write conflict
        # ("corrector_post", "_for_it_19", "FOR_l_1866_c_1866"),   # Can't
        # ("corrector_post", "_for_it_25", "FOR_l_1896_c_1896"),   # Can't
        # ("corrector_post", "_for_it_43", "FOR_l_1962_c_1962"),   # Can't
        ("corrector_post", "_for_it_44", "FOR_l_1963_c_1963"),     # OK - scalar
        # ("corrector_post", "_for_it_45", "FOR_l_1974_c_1974"),   # Can't
        ("corrector_post", "_for_it_47", "FOR_l_1980_c_1980"),     # OK
        ("corrector_post", "_for_it_56", "FOR_l_2015_c_2015"),     # OK - scalar
        ("corrector_post", "_for_it_57", "FOR_l_2016_c_2016"),     # OK - scalar
        # ("corrector_post", "_for_it_62", "FOR_l_2050_c_2050"),   # Can't - BLK

        # solve_nh_corrector_pre - Stage #1
        # ("corrector_pre", "_for_it_44", "FOR_l_1570_c_1570"),    # Can't (scalar, 2->3 dim array)
        # ("corrector_pre", "_for_it_45", "FOR_l_1572_c_1572"),    # Can't (actual dep)
        # ("corrector_pre", "_for_it_46", "FOR_l_1573_c_1573"),    # Can't - BLK
        # ("corrector_pre", "_for_it_47", "FOR_l_1597_c_1597"),    # Can't - BLK
        # ("corrector_pre", "_for_it_50", "FOR_l_1610_c_1610"),    # Can't - BLK
        ("corrector_pre", "_for_it_57", "FOR_l_1654_c_1654"),      # OK - scalar
        ("corrector_pre", "_for_it_58", "FOR_l_1655_c_1655"),      # OK - scalar
        ("corrector_pre", "_for_it_59", "FOR_l_1669_c_1669"),      # OK - scalar
        ("corrector_pre", "_for_it_60", "FOR_l_1670_c_1670"),      # OK - scalar
        ("corrector_pre", "_for_it_61", "FOR_l_1682_c_1682"),      # OK - scalar
        ("corrector_pre", "_for_it_62", "FOR_l_1683_c_1683"),      # OK - scalar

        # solve_nh_predictor_post - Stage #1
        # ("predictor_post", "_for_it_0", "FOR_l_1253_c_1253"),    # Can't
        # ("predictor_post", "_for_it_11", "FOR_l_1297_c_1297"),   # Can't
        # ("predictor_post", "_for_it_13", "FOR_l_1310_c_1310"),   # Can't
        # ("predictor_post", "_for_it_19", "FOR_l_1339_c_1339"),   # Can't
        # ("predictor_post", "_for_it_36", "FOR_l_1403_c_1403"),   # Can't
        # ("predictor_post", "_for_it_37", "FOR_l_1404_c_1404"),   # OK - Is Already A Map
        # ("predictor_post", "_for_it_38", "FOR_l_1415_c_1415"),   # Can't
        ("predictor_post", "_for_it_40", "FOR_l_1421_c_1421"),     # OK
        ("predictor_post", "_for_it_47", "FOR_l_1448_c_1448"),     # OK
        # ("predictor_post", "_for_it_53", "FOR_l_1473_c_1473"),   # Can't
        ("predictor_post", "_for_it_60", "FOR_l_1500_c_1500"),     # OK

        # solve_nh_predictor_pre - Stage #1
        # ("predictor_pre", "_for_it_66", "FOR_l_956_c_956"),      # Can't
        # ("predictor_pre", "_for_it_76", "FOR_l_990_c_990"),      # Can't
        # ("predictor_pre", "_for_it_81", "FOR_l_1017_c_1017"),    # Can't - BLK
        # ("predictor_pre", "_for_it_84", "FOR_l_1050_c_1050"),    # Can't - BLK
        # ("predictor_pre", "_for_it_85", "FOR_l_1053_c_1053"),    # Can't - BLK
        # ("predictor_pre", "_for_it_86", "FOR_l_1054_c_1054"),    # Can't - BLK
        # ("predictor_pre", "_for_it_89", "FOR_l_1079_c_1079"),    # Can't - BLK
        ("predictor_pre", "_for_it_99", "FOR_l_1110_c_1110"),      # OK - scalar
        ("predictor_pre", "_for_it_100", "FOR_l_1116_c_1116"),     # OK - scalar
        ("predictor_pre", "_for_it_101", "FOR_l_1126_c_1126"),     # OK - Parent map of _for_it102
        ("predictor_pre", "_for_it_102", "FOR_l_1133_c_1133"),     # OK - Read-write subsets the same
        # ("predictor_pre", "_for_it_103", "FOR_l_1139_c_1139"),   # Can't - BLK
        # ("predictor_pre", "_for_it_110", "FOR_l_1168_c_1168"),   # Can't - BLK
        # ("predictor_pre", "_for_it_113", "FOR_l_1184_c_1184"),   # Can't
    }
    manually_transformed_count = 0
    for sdfg_name, loop_var, loop_label in manual_loop_to_map:
        if sdfg_name in g.name:
            for node, graph in g.all_nodes_recursive():
                if isinstance(node, LoopRegion) and node.loop_variable == loop_var:
                    assert node.label == loop_label
                    print(f"Stage #{STAGE_ID}: Converting {sdfg_name} loop {loop_label} to map")
                    LoopToMap.apply_to(sdfg=graph.sdfg, loop=node, permissive=True, options={"ballin": True})
                    manually_transformed_count += 1
    g.validate()

    retransify_scalar_with_local_prefix(g, g)
    g.validate()

    count_loops(g, verbose=True, use_assert=False)
    print(f"Stage #{STAGE_ID}: Manually transformed {manually_transformed_count} loops to maps for {g.name}")
    # === Sub-Phase 7: LoopToMap + LoopToMap-Patches ===


    # === Sub-Phase 7: Last Simplify + StateFusion ===
    # Simplify removes input scalars that are accessed only on interstate edges `je_local`, `jb_local` completely,
    # Adding a tasklet that reads these scalars to an useless tasklet can prevent their removal
    # In an SDFG (that has a parent nsdfg node), for all non-transient scalars that are not accessed through an access node -> add a preserver tasklet
    # Try to just skip in ScalarToSymbolPromotion using a skip list
    # add_data_preserver_tasklets(g)
    g.validate()

    # One final simplify to fuse states (there are many 2-state NestedSDFGs where first state and iedge are empty)
    # Even with side-effects on tasklet ScalarToSymbolPromotion removes "je_local" and then their parent array.
    # Call that separately
    g.simplify(skip=["ArrayElimination", "FuseStates", "DeadDataflowElimination", "ScalarToSymbolPromotion"], validate=False)
    ScalarToSymbolPromotion().apply_pass(g, {
        "transients_only": True,
        "ignore": {
            "je_local",
            "jb_local",
            "i_startidx_local",
            "i_endidx_local",
            "je",
            "jb",
            "i_startidx",
            "i_endidx",
        }
    })
    # Simplify results in missing symbols in NestedSDFGs
    # add_missing_data_and_symbols_to_all_nsdfgs(g)
    g.validate()

    # Do not fuse the copy-in or the copy-out state (flatten/deflatten access nodes being fused with
    # the rest of the maps, as it makes offloading much harder)
    state_fusion_without_copyin_and_copyout(g)
    g.validate()

    count_loops(g, verbose=False, use_assert=True)
    # === Sub-Phase 7: Last Simplify + StateFusion ===

    # === Sub-Phase 8: Post Simplify Manual Fixes ===
    if "predictor_pre" in g.name:
        connect_ishift_to_map(g, "_state_l1132_c1132")
    # === Sub-Phase 8: Post Simplify Manual Fixes ===

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

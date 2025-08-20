import warnings
import dace
from dace import SDFG
from dace.sdfg.state import LoopRegion
from dace.transformation.passes.scalar_to_symbol import ScalarToSymbolPromotion
from stages import common
from utils.codegen_from_sdfg import ArtifactMode
from utils.specialize_scalar import specialize_scalar
from dace.transformation.interstate.loop_unroll import LoopUnroll
from dace.transformation.dataflow import MapUnroll

import argparse
import warnings

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
    transify_targeted_array,
    transify_targeted_scalar_general_version,
    identify_persistent_scalars_with_writes
)

from utils.add_data_preserver_tasklets import add_data_preserver_tasklets
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.properties import CodeBlock

from utils.manual_fixes import (
    connect_ishift_to_map,
)

STAGE_ID = 1


def pray_that_startblk_endblk_values_are_correct(g: SDFG):
    """
    The line numbers are based on (and near, but slightly off from) the icon-clone that we have.
# PREPRE
801: i_startblk=1, i_endblk=1
1158: i_startblk=1, i_endblk=1
1219: i_startblk=2, i_endblk=2
1234: i_startblk=1, i_endblk=2
1348: NEVER HAPPENS ???
1422: i_startblk=1, i_endblk=2
1921: NEVER HAPPENS ???

# PREPOST
2440: i_startblk=1, i_endblk=2
2745: i_startblk=1, i_endblk=1
2871: i_startblk=1, i_endblk=1
3369: NEVER HAPPENS ???

# CORPRE
4027: i_startblk=1, i_endblk=1
4384: NEVER HAPPENS ???
4445: NEVER HAPPENS ???
4460: NEVER HAPPENS ???
4610: i_startblk=1, i_endblk=2
4648: i_startblk=1, i_endblk=2
5147: NEVER HAPPENS ???

# CORPOST
5664: i_startblk=1, i_endblk=2
5969: NEVER HAPPENS ???
6095: i_startblk=1, i_endblk=1
6593: NEVER HAPPENS ???
6959: NEVER HAPPENS ???

# DOES NOT MATTER; AFTER CORPOST
6995: i_startblk=1, i_endblk=1
    """
    # PREPRE BLK LOOPS: [(LoopRegion (FOR_l_956_c_956), '_for_it_66'), (LoopRegion (FOR_l_1017_c_1017), '_for_it_81'), (LoopRegion (FOR_l_114_c_114), '_for_it_1_0_0'), (LoopRegion (FOR_l_114_c_114_0), '_for_it_1_0_1'), (LoopRegion (FOR_l_471_c_471), '_for_it_10_0'), (LoopRegion (FOR_l_1050_c_1050), '_for_it_84'), (LoopRegion (FOR_l_1079_c_1079), '_for_it_89'), (LoopRegion (FOR_l_1139_c_1139), '_for_it_103'), (LoopRegion (FOR_l_1168_c_1168), '_for_it_110')]
    # FOR_l_114_c_114: CALLED IN SUBROUTINE, PROBABLY RELATED TO LINE: 1219
    # FOR_l_114_c_114_0: CALLED IN SUBROUTINE, PROBABLY RELATED TO LINE: 1219
    # FOR_l_471_c_471: CALLED IN SUBROUTINE, PROBABLY RELATED TO LINE: 1219
    PREPRE = {
        "_for_it_66": (1, 1), # LINE: 801
        "_for_it_81": (1, 1), # LINE: 1158
        "_for_it_84": (1, 2), # LINE: 1234
        "_for_it_89": (1, 2), # LINE: 1422
        "_for_it_103": (1, 2), # LINE: 1422
        # "_for_it_110": LINE: 1921, NEVER HAPPENS
    }
    # PREPOST BLK LOOPS: [(LoopRegion (FOR_l_1254_c_1254), '_for_it_0'), (LoopRegion (FOR_l_1311_c_1311), '_for_it_13'), (LoopRegion (FOR_l_1340_c_1340), '_for_it_17'), (LoopRegion (FOR_l_1474_c_1474), '_for_it_51')]
    PREPOST = {
        "_for_it_0": (1, 2), # LINE: 2440
        "_for_it_13": (1, 1), # LINE: 2745
        "_for_it_17": (1, 1), # LINE: 2871
        # "_for_it_51": LINE: 3369, NEVER HAPPENS
    }
    # CORPRE BLK LOOPS: [(LoopRegion (FOR_l_1571_c_1571), '_for_it_44'), (LoopRegion (FOR_l_1598_c_1598), '_for_it_47'), (LoopRegion (FOR_l_1611_c_1611), '_for_it_50')]
    CORPRE = {
        "_for_it_44": (1, 1), # LINE: 4027
        "_for_it_47": (1, 2), # LINE: 4610
        "_for_it_50": (1, 2), # LINE: 4648
    }
    # CORPOST BLK LOOPS: [(LoopRegion (FOR_l_1786_c_1786), '_for_it_0'), (LoopRegion (FOR_l_1868_c_1868), '_for_it_19'), (LoopRegion (FOR_l_1898_c_1898), '_for_it_23'), (LoopRegion (FOR_l_2052_c_2052), '_for_it_60')]
    CORPOST = {
        "_for_it_0": (1, 2), # LINE: 5664
        # "_for_it_19": # LINE: 5969, NEVER HAPPENS
        "_for_it_23": (1, 1), # LINE: 6095
        "_for_it_60": (1, 1), # LINE: 6095
    }
    ITERATOR_TO_START_END_BLK = {
        "predictor_pre": PREPRE,
        "predictor_post": PREPOST,
        "corrector_pre": CORPRE,
        "corrector_post": CORPOST,
    }

    HACKS = singular(v for k, v in ITERATOR_TO_START_END_BLK.items() if k in g.name)
    for n, st in g.all_nodes_recursive():
        if not isinstance(n, LoopRegion) or n.loop_variable not in HACKS:
            continue
        startblk, endblk = HACKS[n.loop_variable]
        assert n.init_statement.as_string == f"{n.loop_variable} = i_startblk"
        assert n.loop_condition.as_string == f"({n.loop_variable} <= i_endblk)"
        n.init_statement = CodeBlock(f"{n.loop_variable} = {startblk}")
        n.loop_condition = CodeBlock(f"({n.loop_variable} <= {endblk})")

    # g.apply_transformations_repeated(LoopUnroll)


def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    # === Sub-Phase 1: Flattening ===
    g.apply_transformations_repeated(ContinueToCondition)
    # Frontend generates invalid view towers, if final view is a struct then that view node should not exist, clean
    clean_partial_view_towers(g)
    # Flatten all structs to SOA, also generates code necessary for shallow copy in ICON
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
    # Flattening transformation can result with DataContainer -> View -> X where View covers the DataContainer fully
    # This is usuless while also breaking many many transformations, so clean it up
    clean_trivial_view_pattern(g)
    # Replave velocity tendencies tasklet to use the flattened names
    reinject_velocity_shim(g)
    g.validate()
    # Until this point we numerically validate
    # === Sub-Phase 1: Flattening ===

    pray_that_startblk_endblk_values_are_correct(g)
    for scalar_name, scalar_value in {
        "nlevp1": 91,
        "nlev": 90,
        "jg": 1,
        "__CG_global_data__m_rayleigh_type": 2,
        "__CG_global_data__m_divdamp_type": 32,
        "__CG_global_data__m_is_iau_active": 0,
        "__CG_global_data__m_igradp_method": 3,
        "__CG_global_data__m_itime_scheme": 4,
        "__CG_global_data__m_iadv_rhotheta": 2,
        "__CG_global_data__m_l_limited_area": 0,
        "__CG_global_data__m_l_vert_nested": 0,
    }.items():
        specialize_scalar(g, scalar_name, scalar_value)
        g.validate()
    # Constprop with the new constants
    ConstantPropagation().apply_pass(g, {})


    # === Sub-Phase 2: Simplify and Patch ===
    # Simplify results with NestedSDFGs having missing symbols
    g.simplify(skip=["ArrayElimination", "FuseStates", "DeadDataflowElimination"], validate=False)
    # Add missing symbols and data to NSDFGs to make it valid, many transformations forget to update the symbols in the nested
    # SDFGs
    add_missing_data_and_symbols_to_all_nsdfgs(g)
    g.validate()
    # === Sub-Phase 2: Simplify and Patch ===

    # === Sub-Phase 3: SymbolPropagation + Simplify + FuseState Without CopyIn/CopyOut ===
    # Until this point we numerically validate
    SymbolPropagation().apply_pass(g, {})
    g.validate()
    # Until this point we numerically validate
    # ArrayElimination, FuseStates and DeadDataflowElimination are the ones that almost always break
    g.simplify(skip=["ArrayElimination", "FuseStates", "DeadDataflowElimination"], validate=False)
    # Do not fuse the copy-in or the copy-out state (flatten/deflatten access nodes being fused with the rest of the maps make
    # offloading much harder)
    # State fusion tends to behave well if we exclude the states that copy-in structs to flattened types and copy-out flattened types to structs
    state_fusion_without_copyin_and_copyout(g)
    g.validate()
    # === Sub-Phase 3: SymbolPropagation + Simplify + FuseState Without CopyIn/CopyOut ===

    # === Sub-Phase 4: ConstantPropagation ===
    # ConstantPropagation works nicely after cleaning
    ConstantPropagation().apply_pass(g, {})
    g.validate()
    # === Sub-Phase 4: ConstantPropagation ===

    # === Sub-Phase 5: Loop Preprocessing ===
    # Ensure loop locality for ballin LoopToMap
    # These scalars where omp private (...) and should be like that
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
    # All the names above are scalars that can become thread-local
    state_fusion_without_copyin_and_copyout(g)
    transify_targeted_scalar(g, thread_local_scalar_candidates)

    SCALARS_ON_INTERFACE = identify_persistent_scalars_with_writes(g)
    print(f"Stage #{STAGE_ID}: Transifying {len(SCALARS_ON_INTERFACE)} scalars on interface: {SCALARS_ON_INTERFACE}")
    transify_targeted_scalar_general_version(g, SCALARS_ON_INTERFACE)

    thread_local_array_candidates = {
        "__CG_p_nh_prog_nnew__m_w",
        "__CG_p_nh__CG_diag__m_mass_fl_e",
        "__CG_p_nh_prog_nnew__m_rho",
        "__CG_p_nh_prog_nnew__m_exner",
        "z_theta_v_pr_ic",
        "__CG_p_nh__CG_diag__m_theta_v_ic",
        "__CG_p_nh_prog_nnew__m_theta_v",
        "z_exner_ic",
        "z_theta_v_pr_ic",
        "__CG_p_nh__CG_diag__m_grf_bdy_mflx",
    }
    # TODO: This prevents new loops from becoming maps
    # transify_targeted_array(g, thread_local_array_candidates)
    # Also it seems like it did not change the performance
    # === Sub-Phase 6: Loop Preprocessing ===

    # === Sub-Phase 7: LoopToMap + LoopToMap-Patches ===
    # Never set ballin to True
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
    # No nproma map should be left.
    # LoopToMap does not catch many loops, force them to beecome maps this is the set
    manual_loop_to_map = {
        # solve_nh_corrector_post - Stage #1
        # ("corrector_post", "_for_it_0", "FOR_l_1784_c_1784"),    # Can't
        ("corrector_post", "_for_it_15", "FOR_l_1842_c_1842"),     # OK - no-read-write conflict
        ("corrector_post", "_for_it_19", "FOR_l_1868_c_1868"),
        ("corrector_post", "_for_it_20", "FOR_l_1870_c_1870"),   # Can't
        ("corrector_post", "_for_it_21", "FOR_l_1871_c_1871"),   # Can't
        ("corrector_post", "_for_it_22", "FOR_l_1872_c_1872"),   # Can't
        ("corrector_post", "_for_it_23", "FOR_l_1898_c_1898"),
        # ("corrector_post", "_for_it_25", "FOR_l_1896_c_1896"),   # Can't
        ("corrector_post", "_for_it_42", "FOR_l_1965_c_1965"),     # OK - scalar
        # ("corrector_post", "_for_it_43", "FOR_l_1962_c_1962"),   # Can't
        # ("corrector_post", "_for_it_45", "FOR_l_1974_c_1974"),   # Can't
        ("corrector_post", "_for_it_45", "FOR_l_1982_c_1982"),     # OK
        ("corrector_post", "_for_it_54", "FOR_l_2017_c_2017"),     # OK - scalar
        ("corrector_post", "_for_it_55", "FOR_l_2018_c_2018"),     # OK - scalar
        # ("corrector_post", "_for_it_62", "FOR_l_2050_c_2050"),   # Can't - BLK

        # solve_nh_corrector_pre - Stage #1
        # ("corrector_pre", "_for_it_44", "FOR_l_1570_c_1570"),    # Can't (scalar, 2->3 dim array)
        # ("corrector_pre", "_for_it_45", "FOR_l_1572_c_1572"),    # Can't (actual dep)
        # ("corrector_pre", "_for_it_46", "FOR_l_1573_c_1573"),    # Can't - BLK
        ("corrector_pre", "_for_it_47", "FOR_l_1598_c_1598"),
        # ("corrector_pre", "_for_it_50", "FOR_l_1610_c_1610"),    # Can't - BLK
        ("corrector_pre", "_for_it_57", "FOR_l_1655_c_1655"),      # OK - scalar
        ("corrector_pre", "_for_it_50", "FOR_l_1611_c_1611"),
        ("corrector_pre", "_for_it_58", "FOR_l_1656_c_1656"),      # OK - scalar
        ("corrector_pre", "_for_it_59", "FOR_l_1670_c_1670"),      # OK - scalar
        ("corrector_pre", "_for_it_60", "FOR_l_1671_c_1671"),      # OK - scalar
        ("corrector_pre", "_for_it_61", "FOR_l_1683_c_1683"),      # OK - scalar
        ("corrector_pre", "_for_it_62", "FOR_l_1684_c_1684"),      # OK - scalar

        # solve_nh_predictor_post - Stage #1
        ("predictor_post", "_for_it_0", "FOR_l_1253_c_1253"),
        # ("predictor_post", "_for_it_11", "FOR_l_1297_c_1297"),   # Can't
        # ("predictor_post", "_for_it_13", "FOR_l_1310_c_1310"),   # Can't
        # ("predictor_post", "_for_it_19", "FOR_l_1339_c_1339"),   # Can't
        # ("predictor_post", "_for_it_36", "FOR_l_1403_c_1403"),   # Can't
        # ("predictor_post", "_for_it_37", "FOR_l_1404_c_1404"),   # OK - Is Already A Map
        # ("predictor_post", "_for_it_38", "FOR_l_1415_c_1415"),   # Can't
        ("predictor_post", "_for_it_38", "FOR_l_1422_c_1422"),     # OK
        ("predictor_post", "_for_it_45", "FOR_l_1449_c_1449"),     # OK
        ("predictor_post", "_for_it_51", "FOR_l_1474_c_1474"),
        # ("predictor_post", "_for_it_53", "FOR_l_1473_c_1473"),   # Can't
        ("predictor_post", "_for_it_58", "FOR_l_1501_c_1501"),     # OK
        ("predictor_post", "_for_it_14", "FOR_l_1313_c_1313"),     # OK - OpenACC pragma kernel
        ("predictor_post", "_for_it_15", "FOR_l_1314_c_1314"),     # OK - OpenACC pragma kernel
        ("predictor_post", "_for_it_16", "FOR_l_1320_c_1320"),     # OK - OpenACC pragma kernel
        ("predictor_post", "_for_it_17", "FOR_l_1340_c_1340"),

        # solve_nh_predictor_pre - Stage #1
        ("predictor_pre", "_for_it_66", "FOR_l_956_c_956"),
        # ("predictor_pre", "_for_it_76", "FOR_l_990_c_990"),      # Can't
        # ("predictor_pre", "_for_it_81", "FOR_l_1017_c_1017"),    # Can't - BLK
        # ("predictor_pre", "_for_it_84", "FOR_l_1050_c_1050"),    # Can't - BLK
        # ("predictor_pre", "_for_it_85", "FOR_l_1053_c_1053"),    # Can't - BLK
        # ("predictor_pre", "_for_it_86", "FOR_l_1054_c_1054"),    # Can't - BLK
        ("predictor_pre", "_for_it_89", "FOR_l_1079_c_1079"),
        ("predictor_pre", "_for_it_99", "FOR_l_1110_c_1110"),      # OK - scalar
        ("predictor_pre", "_for_it_100", "FOR_l_1116_c_1116"),     # OK - scalar
        ("predictor_pre", "_for_it_101", "FOR_l_1126_c_1126"),     # OK - Parent map of _for_it102
        ("predictor_pre", "_for_it_102", "FOR_l_1133_c_1133"),     # OK - Read-write subsets the same
        # ("predictor_pre", "_for_it_103", "FOR_l_1139_c_1139"),   # Can't - BLK
        # ("predictor_pre", "_for_it_110", "FOR_l_1168_c_1168"),   # Can't - BLK
        # ("predictor_pre", "_for_it_113", "FOR_l_1184_c_1184"),   # Can't
    }
    # Loop that forces LoopToMap (by permissive=True and balling=True)
    manually_transformed_count = 0
    expected_transformed_count = 0
    for sdfg_name, loop_var, loop_label in manual_loop_to_map:
        if sdfg_name not in g.name:
            continue
        expected_transformed_count += 1
        for node, graph in g.all_nodes_recursive():
            if not isinstance(node, LoopRegion) or node.loop_variable != loop_var:
                continue
            if node.label != loop_label:
                warnings.warn(f"Stage #{STAGE_ID}: {sdfg_name} loop {loop_label} label mismatch")
            print(f"Stage #{STAGE_ID}: Converting {sdfg_name} loop {loop_label} to map")
            LoopToMap.apply_to(sdfg=graph.sdfg, loop=node, permissive=True, options={"ballin": True})
            manually_transformed_count += 1
    g.validate()

    # Tries to make some scalars into thread-loacl
    retransify_scalar_with_local_prefix(g, g)
    g.validate()

    count_loops(g, verbose=True, use_assert=False)
    print(f"Stage #{STAGE_ID}: Manually transformed {manually_transformed_count} out of {expected_transformed_count} loops to maps for {g.name}")
    # === Sub-Phase 7: LoopToMap + LoopToMap-Patches ===


    # === Sub-Phase 8: Last Simplify + StateFusion ===
    # Simplify removes input scalars that are accessed only on interstate edges `je_local`, `jb_local` completely,
    # Adding a tasklet that reads these scalars to an useless tasklet can prevent their removal
    # In an SDFG (that has a parent nsdfg node), for all non-transient scalars that are not accessed through an access node -> add a preserver tasklet
    # Try to just skip in ScalarToSymbolPromotion using a skip list
    # add_data_preserver_tasklets(g)
    g.validate()

    # One final simplify to fuse states (there are many 2-state NestedSDFGs where first state and iedge are empty)
    # Even with side-effects on tasklet ScalarToSymbolPromotion removes "je_local" and then their parent array.
    # Call that separately
    # Since everything is a map, simplify does much more but it also breaks more
    g.simplify(skip=["ArrayElimination", "FuseStates", "DeadDataflowElimination", "ScalarToSymbolPromotion"], validate=False)
    # These are the symbols that need to be excluded, otherswise scalar to symbol creates invalid SDFGs
    ScalarToSymbolPromotion().apply_pass(g, {
        "transients_only": True,
        "ignore": {
            "je_local",
            "jb_local"
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
    # === Sub-Phase 8: Last Simplify + StateFusion ===

    # === Sub-Phase 9: Post Simplify Manual Fixes ===
    # This map, (if it still exists after transify) prevents map collapse, manually massage it
    if "predictor_pre" in g.name:
        # TODO make it to a pass that detects AN1 -> tasklet (out = in) -> AN2 -> mapEntry -> nestedSDFG
        # Replaces it with AN1 -> MapEntry -> NestedSDFG
        connect_ishift_to_map(g, "_state_l1132_c1132")
    # === Sub-Phase 9: Post Simplify Manual Fixes ===

    # g.apply_transformations_repeated(MapUnroll)

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

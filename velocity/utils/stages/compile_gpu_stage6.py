import argparse
import dace
from dace.codegen.control_flow import CodeBlock, ConditionalBlock, ControlFlowRegion
from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.passes.to_gpu import ToGPU
import utils.config as config
import utils.stages.common as common
from utils.add_gpu_copies_to_flattener import add_gpu_copies_to_flattener
from utils.find import find_node_by_name
from utils.move_ifs_inside_maps import move_ifs_inside_maps
from utils.move_lib_schedules import move_lib_schedules
from utils.pre_gpu_fixes import pre_gpu_fix
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
from utils.remove_unused_inconnectors_from_nestedsdfg import remove_unused_inconnectors_from_nestedsdfg
from utils.segmented_reduction import to_segmented_reduction
from utils.rm_segmented_reduce import rm_segmented_reduce
from utils.profiling_patches import insert_timers_for_profiling, insert_synchronization_for_profiling, insert_event_timers_for_profiling
import copy
import os

STAGE_ID = 6

def merge_its9_10_and_its15(sdfg: dace.SDFG):
    s1 = {
        (n, g) for n, g in sdfg.all_nodes_recursive() if isinstance(n, dace.nodes.MapEntry)
        and "_for_it_9" in n.map.params and "_for_it_10" in n.map.params
    }
    if len(s1) == 0:
        return
    mapentry1, state1 = s1.pop()
    s2 = {
        (n, g) for n, g in sdfg.all_nodes_recursive() if isinstance(n, dace.nodes.MapEntry)
        and "_for_it_15" in n.map.params
    }
    if len(s2) == 0:
        return
    mapentry2, state2 = s2.pop()

    # Extend nlev range to be 1 more
    mrange = mapentry1.map.range
    mrange1 = mapentry1.map.range[1]
    mrange = dace.subsets.Range([(1, 90, 1), (mrange1[0], mrange1[1], mrange1[2])])
    mapentry1.map.range = mrange

    # Find tasklet and change tasklet code
    mapexit1 = state1.exit_node(mapentry1)
    mapexit2 = state2.exit_node(mapentry2)
    body1_nodes = list(state1.all_nodes_between(mapentry1, mapexit1))
    body2_nodes = list(state2.all_nodes_between(mapentry2, mapexit2))
    body1_edges = list(state1.all_edges(*body1_nodes))
    body2_edges = list(state2.all_edges(*body2_nodes))

    condition = "_for_it_9 == 1"

    # Create branch
    inside_sdfg = dace.SDFG("sdfg_fused_it_9_10_15")
    cb = ConditionalBlock("cb_fused_it_9_10_15", sdfg=inside_sdfg, parent=None)
    cfg_true = ControlFlowRegion("cfg_true_fused_it_9_10_15", sdfg=inside_sdfg, parent=cb)
    cfg_false = ControlFlowRegion("cfg_false_fused_it_9_10_15", sdfg=inside_sdfg, parent=cb)


    syms = ['__f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8', '__f2dace_SOA_vn_d_0_s_p_prog_7', '__f2dace_SOA_vt_d_2_s_p_diag_9', '__f2dace_SOA_vn_ie_d_0_s_p_diag_9', '__f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8', '__f2dace_OA_z_vt_ie_d_1_s', '__f2dace_SOA_vn_ie_d_2_s_p_diag_9', '__f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8', '__f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8', '__f2dace_OA_z_kin_hor_e_d_1_s', '__f2dace_SOA_vt_d_0_s_p_diag_9', '__f2dace_OA_z_kin_hor_e_d_0_s', '__f2dace_SOA_vn_d_2_s_p_prog_7', '__f2dace_OA_z_vt_ie_d_2_s', '_for_it_6', '__f2dace_OA_z_kin_hor_e_d_2_s', '__f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8', '__f2dace_SOA_vn_d_1_s_p_prog_7', '__f2dace_OA_z_vt_ie_d_0_s', '_for_it_15', '__f2dace_SOA_vt_d_1_s_p_diag_9', '__f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8', '__f2dace_SOA_vn_ie_d_1_s_p_diag_9', '_for_it_10']
    for sym in syms:
        if sym in sdfg.symbols:
            inside_sdfg.add_symbol(sym, sdfg.symbols[sym])
        else:
            inside_sdfg.add_symbol(sym, dace.int32)

    # Wire up branches first
    cb.add_branch(CodeBlock(condition), cfg_true)
    cb.add_branch(None, cfg_false)

    # Then add states inside the regions
    state_true = cfg_true.add_state("state_true_fused_it_9_10_15", is_start_block=True)
    state_false = cfg_false.add_state("state_false_fused_it_9_10_15", is_start_block=True)

    # Add the ConditionalBlock as the start node of inside_sdfg
    inside_sdfg.add_node(cb, is_start_block=True)

    inside_sdfg.validate()

    in_data1 = {ie.data.data for ie in state1.in_edges(mapentry1)}
    in_data2 = {ie.data.data for ie in state2.in_edges(mapentry2)}
    out_data1 = {oe.data.data for oe in state1.out_edges(mapexit1)}
    out_data2 = {oe.data.data for oe in state2.out_edges(mapexit2)}

    in_data = in_data1.union(in_data2)
    out_data = out_data1.union(out_data2)
    for d in in_data.union(out_data):
        cdesc = copy.deepcopy(state1.sdfg.arrays[d])
        cdesc.transient = False
        inside_sdfg.add_datadesc(d, cdesc)

    sdfg = state1.sdfg

    #assert in_data1 == in_data2, f"{in_data1},\n{in_data2}"
    #assert out_data1 == out_data2, f"{out_data1},\n{out_data2}"

    nsdfg = state1.add_nested_sdfg(inside_sdfg, state1, inputs=in_data, outputs=out_data2)

    # Connect new nested SDFG
    added_arrays = set()
    for oe in state1.out_edges(mapentry1):
        if oe.data.data in added_arrays:
            continue
        state1.add_edge(oe.src, oe.src_conn, nsdfg, oe.data.data,
            dace.memlet.Memlet.from_array(oe.data.data,
                state1.sdfg.arrays[oe.data.data]))
        added_arrays.add(oe.data.data)

    added_out_arrays = set()
    for ie in state1.in_edges(mapexit1):
        arrname = ie.data.data
        print(ie, arrname in added_out_arrays)
        if arrname in added_out_arrays:
            continue
        print(ie.src, ie.src_conn, ie.dst, ie.dst_conn, arrname)
        state1.add_edge(
            nsdfg,
            arrname,
            ie.dst,
            ie.dst_conn,
            dace.memlet.Memlet.from_array(arrname, state2.sdfg.arrays[arrname]),
        )
        added_out_arrays.add(arrname)

    # Add missing ones
    for d in in_data2 - in_data1:
        an = state1.add_access(d)
        state1.add_edge(an, None, mapentry1, f"IN_{an.data}", dace.memlet.Memlet.from_array(
            an.data, state1.sdfg.arrays[an.data]
        ))
        state1.add_edge(mapentry1, f"OUT_{an.data}", nsdfg, an.data, dace.memlet.Memlet.from_array(
            an.data, state1.sdfg.arrays[an.data]
        ))
        mapentry1.add_in_connector(f"IN_{an.data}")
        mapentry1.add_out_connector(f"OUT_{an.data}")

    for d in out_data2 - out_data1:
        an = state1.add_access(d)
        state1.add_edge(mapexit1, f"OUT_{an.data}", an, None, dace.memlet.Memlet.from_array(
            an.data, state1.sdfg.arrays[an.data]
        ))
        state1.add_edge(nsdfg, an.data, mapexit1, f"IN_{an.data}", dace.memlet.Memlet.from_array(
            an.data, state1.sdfg.arrays[an.data]
        ))
        mapexit1.add_in_connector(f"IN_{an.data}")
        mapexit1.add_out_connector(f"OUT_{an.data}")

    nmap1 = dict()
    for n in body1_nodes:
        nc = copy.deepcopy(n)
        state_true.add_node(nc)
        if isinstance(n, dace.nodes.AccessNode):
            cdesc = copy.deepcopy(state1.sdfg.arrays[n.data])
            inside_sdfg.add_datadesc(
                n.data, cdesc
            )
        nmap1[n] = nc
    for e in body1_edges:
        if e.src not in nmap1:
            src = state_true.add_access(e.data.data)
            src_conn = None
        else:
            src = nmap1[e.src]
            src_conn = e.src_conn
        if e.dst not in nmap1:
            dst = state_true.add_access(e.data.data)
            dst_conn = None
        else:
            dst = nmap1[e.dst]
            dst_conn = e.dst_conn
        state_true.add_edge(src, src_conn, dst, dst_conn, copy.deepcopy(e.data))
    
    nmap2 = dict()
    for n in body2_nodes:
        nc = copy.deepcopy(n)
        state_false.add_node(nc)
        if isinstance(n, dace.nodes.AccessNode):
            cdesc = copy.deepcopy(state2.sdfg.arrays[n.data])
            inside_sdfg.add_datadesc(
                n.data, cdesc
            )
        nmap2[n] = nc
    for e in body2_edges:
        if e.src not in nmap2:
            src = state_false.add_access(e.data.data)
            src_conn = None
        else:
            src = nmap2[e.src]
            src_conn = e.src_conn
        if e.dst not in nmap2:
            dst = state_false.add_access(e.data.data)
            dst_conn = None
        else:
            dst = nmap2[e.dst]
            dst_conn = e.dst_conn
        state_false.add_edge(src, src_conn, dst, dst_conn, copy.deepcopy(e.data))

    for n in body1_nodes:
        if n == nsdfg:
            continue
        state1.remove_node(n)
    for n in body2_nodes:
        state2.remove_node(n)
    state2.remove_node(mapentry2)
    state2.remove_node(mapexit2)

    for n in state2.nodes():
        if state2.in_degree(n) == 0 and state2.out_degree(n) == 0:
            state2.remove_node(n)

    inside_sdfg.replace_dict({"_for_it_15": "_for_it_10"})

    inside_sdfg.save("inside.sdfg")

    sdfg.validate()



def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    add_gpu_copies_to_flattener(sdfg)
    sdfg.validate()

    state = {s for s in sdfg.all_states() if s.label.startswith("entry_interface")}.pop()
    sdfg.add_state_before(state, "predom_ei", is_start_block=True )
    state.sdfg = sdfg
    state.parent_graph = sdfg
    pre_gpu_fix(sdfg)

    sdfg.validate()
    move_ifs_inside_maps(sdfg)
    flatten_lib, _ = find_node_by_name(sdfg, "flatten")
    deflatten_lib, _ = find_node_by_name(sdfg, "deflatten")

    # Do not merge I guess
    #merge_its9_10_and_its15(sdfg)

    sdfg.validate()
    ToGPU(verbose=config.verbose, cpu_library_nodes=[flatten_lib, deflatten_lib], exclude=["vcflmax"]).apply_pass(sdfg, {})
    sdfg.validate()

    prune_unused_inputs_outputs(sdfg)
    GPUKernelLaunchRestructure().apply_pass(sdfg, {})
    prune_unused_inputs_outputs(sdfg)
    move_lib_schedules(sdfg, dace.dtypes.ScheduleType.GPU_Device)
    to_segmented_reduction(sdfg)

    for arrname, arr in sdfg.arrays.items():
        if arr.transient:
            if arr.storage == dace.dtypes.StorageType.GPU_Global:
                arr.lifetime = dace.dtypes.AllocationLifetime.SDFG

    for e, graph in sdfg.all_edges_recursive():
        if e.data is not None and hasattr(e.data, "data") and (e.data.data == "gpu_out_val_0" or e.data.data == "out_val_0"):
            sb = dace.subsets.Range.from_string("2*_for_it_35 - 2")
            if sb == e.data.subset:
                e.data.subset = dace.subsets.Range.from_string("_for_it_35 - 1")
    sdfg.validate()
    # TODO: Make sure this does not break numerical validation
    rm_segmented_reduce(sdfg)
    # Rm segmented reduce results with trivial if conditions
    # propagate_if_cond(sdfg, sdfg, None, None, True)
    remove_unused_inconnectors_from_nestedsdfg(sdfg)
    sdfg.simplify()
    sdfg.validate()

    # Transformation does not detect anything, check
    # setzero_to_memset(sdfg)
    sdfg.validate()
    for arr_name, arr in sdfg.arrays.items():
        if "maxvcfl_arr" in arr_name:
            if "gpu" in arr_name:
                arr.storage = dace.dtypes.StorageType.GPU_Global
            else:
                arr.storage = dace.dtypes.StorageType.CPU_Heap
            arr.lifetime = dace.dtypes.AllocationLifetime.SDFG
    sdfg.validate()



    return sdfg

import sys

def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--optimize', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--compile', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--unpermuted', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--permutations', type=str, default=None,
                      help='Comma-separated config names from PERMUTE_CONFIGS (default: single_map)')
    args = argp.parse_args()
    if not args.optimize and not args.compile:
        args.optimize, args.compile = True, True
    names = common.sdfg_names()
    if args.optimize:
        for name in names:
            infile = common.stage_input(name, STAGE_ID)
            outfile = common.stage_output(name, STAGE_ID)
            print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")
            sdfg = dace.SDFG.from_file(infile)
            sdfg.name = name
            sdfg.validate()
            sdfg = optimization_action(sdfg)
            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfg.save(outfile, compress=True)
    if args.compile:
        from sc26_layout.extract_gpu_kernel import permute_single_map_gpu, PERMUTE_CONFIGS

        if args.permutations:
            config_names = [c.strip() for c in args.permutations.split(",")]
        else:
            config_names = ["single_map"]

        for config_name in config_names:
            if config_name not in PERMUTE_CONFIGS:
                print(f"Unknown config: {config_name}. Available: {list(PERMUTE_CONFIGS.keys())}")
                sys.exit(1)

            for shuffle_map in [True, False]:
                shuffle_label = "shuffled" if shuffle_map else "unshuffled"
                print(f"=== Compiling permuted config: {config_name} ({shuffle_label}) ===")
                sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
                nsdfgs = {}
                for name, sdfg in sdfgs.items():
                    sdfg = permute_single_map_gpu(sdfg, config_name=config_name, shuffle_map=shuffle_map)
                    insert_synchronization_for_profiling(sdfg)
                    sdfg.validate()
                    nsdfgs[name] = sdfg
                suffix = f"_permuted_{config_name}_{shuffle_label}"
                #BEVERIN = os.getenv("BEVERIN", "0") == "1"
                #tblock_dim = "32,16,1" if not BEVERIN else "64,8,1"
                tblock_dim = "32, 4, 1"
                common.compile_action(STAGE_ID, nsdfgs, False, None, False,
                    name_suffix=suffix, main_name="main_per.cu", tblock_dim=tblock_dim,
                    stage_suffix=suffix)

    if args.unpermuted:
        from sc26_layout.extract_gpu_kernel import add_timer_single_map_gpu

        print(f"=== Compiling unpermuted baseline ===")
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            sdfg = add_timer_single_map_gpu(sdfg)
            insert_synchronization_for_profiling(sdfg)
            sdfg.validate()
            nsdfgs[name] = sdfg
        #BEVERIN = os.getenv("BEVERIN", "0") == "1"
        #tblock_dim = "32,16,1" if not BEVERIN else "64,8,1"
        tblock_dim = "32, 4, 1"
        common.compile_action(STAGE_ID, nsdfgs, False, None, False,
            name_suffix="_unpermuted", main_name="main_per.cu", tblock_dim=tblock_dim,
            stage_suffix="_unpermuted")

if __name__ == "__main__":
    main()

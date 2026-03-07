import typing
import dace
from dace.transformation.layout.permute_dimensions import PermuteDimensions
from dace.sdfg.construction_utils import move_state_after, move_state_before


def _rm_map(state: dace.SDFGState, entry_node: dace.nodes.MapEntry):
    exit_node = state.exit_node(entry_node)
    in_neighbors = {e.src for e in state.in_edges(entry_node)}
    out_neighbors = {e.dst for e in state.out_edges(exit_node)}

    for n in state.all_nodes_between(entry_node, exit_node):
        state.remove_node(n)
    
    state.remove_node(entry_node)
    state.remove_node(exit_node)

    for u in in_neighbors:
        if state.degree(u) == 0:
            state.remove_node(u)
    for v in out_neighbors:
        if state.degree(v) == 0:
            state.remove_node(v)

def delete_all_maps_except(
    sdfg: dace.SDFG,
    map_iterators: set[str],
    return_set: set[str],
):
    map, state = None, None
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry) and n in g.nodes():
            if map_iterators.intersection(set(n.map.params)) == set():
                # Remove map and all nodes in it
                _rm_map(g, n)
            else:
                #assert ((map is None and state is None) or (map == n and state == g)), f"Multiple maps with iterators {map_iterators} found."
                if return_set.intersection(set(n.map.params)) == return_set:
                    assert (map is None and state is None) or (map == n and state == g), f"Multiple maps with iterators {return_set} found."
                    map = n
                    state = g
    return map, state

def find_map_state(sdfg: dace.SDFG, map_iterators: set[str]) -> typing.Tuple[dace.SDFGState, dace.SDFG]:
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry) and all(it in map_iterators for it in n.map.params):
            return g, g.parent_graph
    raise ValueError(f"Map with iterators {map_iterators} not found.")

def add_timer_around_gpu(sdfg: dace.SDFG, state: dace.SDFGState):
    clock_in = sdfg.add_state_before(state, "clock_in")
    clock_out = sdfg.add_state_after(state, "clock_out")

    ct1 = dace.nodes.Tasklet(
        "c1", inputs={}, outputs={},
        code="gpu_timer_split();",
        language=dace.dtypes.Language.CPP,
        side_effects=True,
        code_global="""
static void gpu_timer_split() {
    static cudaEvent_t start, stop;
    static bool is_first_call = true;

    if (is_first_call) {
        // Initialize events on the first call
        cudaDeviceSynchronize();

        is_first_call = false;
        std::cout << "[Timer] Start recorded..." << std::endl;

        cudaEventCreate(&start);
        cudaEventCreate(&stop);

        // Record the start point on the default stream
        cudaEventRecord(start, 0);
    } else {
        // Record the stop point
        cudaEventRecord(stop, 0);

        // Wait for the GPU to actually reach the stop event
        cudaEventSynchronize(stop);

        float milliseconds = 0;
        cudaEventElapsedTime(&milliseconds, start, stop);

        std::cout << "[Timer] Elapsed time: " << milliseconds << " ms" << std::endl;

        // Clean up and reset for potential future use
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
        is_first_call = true; 
    }
}
"""
    )
    ct2 = dace.nodes.Tasklet(
        "c1", inputs={}, outputs={},
        code="gpu_timer_split();",
        language=dace.dtypes.Language.CPP,
        code_global="",
        side_effects=True,
    )

    clock_in.add_node(ct1)
    clock_out.add_node(ct2)

    return clock_in, clock_out


def add_symbols(sdfg: dace.SDFG):
    symlist = [
        "__f2dace_A_z_kin_hor_e_d_0_s",
        "__f2dace_A_z_kin_hor_e_d_1_s",
        "__f2dace_A_z_kin_hor_e_d_2_s",
        "__f2dace_A_z_vt_ie_d_0_s",
        "__f2dace_A_z_vt_ie_d_1_s",
        "__f2dace_A_z_vt_ie_d_2_s",
        "__f2dace_A_z_w_concorr_me_d_0_s",
        "__f2dace_A_z_w_concorr_me_d_1_s",
        "__f2dace_A_z_w_concorr_me_d_2_s",
        "__f2dace_OA_z_kin_hor_e_d_0_s",
        "__f2dace_OA_z_kin_hor_e_d_1_s",
        "__f2dace_OA_z_kin_hor_e_d_2_s",
        "__f2dace_OA_z_vt_ie_d_0_s",
        "__f2dace_OA_z_vt_ie_d_1_s",
        "__f2dace_OA_z_vt_ie_d_2_s",
        "__f2dace_OA_z_w_concorr_me_d_0_s",
        "__f2dace_OA_z_w_concorr_me_d_1_s",
        "__f2dace_OA_z_w_concorr_me_d_2_s",
        "dt_linintp_ubc",
        "dtime",
        "istep",
        "ldeepatmo",
        "lvn_only",
        "ntnd"
    ]
    new_start = sdfg.add_state_before(sdfg.start_block, "sym_force_use", True)
    sname, sdesc = sdfg.add_scalar("dummy_symbol_sum", dtype=dace.float64, transient=True, storage=dace.StorageType.Register)

    inputs = {sym for sym in symlist if sym in sdfg.arrays}


    tstr = "_out = " + " + ".join(f"_in_{inp}" for inp in inputs) + "+" + " + ".join(f"{sym}" for sym in symlist if sym not in inputs) 
    new_tasklet = new_start.add_tasklet("sym_force_use", {"_in_" + str(inp) for inp in inputs}, {"_out"}, tstr, side_effects=True)

    for sym in symlist:
        if sym in sdfg.arrays:
            an = new_start.add_access(sym)
            new_start.add_edge(an, None, new_tasklet, "_in_" + sym, dace.Memlet(f"{sym}[0]"))
        else:
            # Some symbols are defined (bruh)
            if sym not in sdfg.symbols:
                sdfg.add_symbol(sym, dace.int32, False)

    new_start.add_edge(new_tasklet, "_out", new_start.add_access(sname), None, dace.Memlet(f"{sname}[0]"))

def add_print_after_gpu(sdfg: dace.SDFG, state: dace.SDFGState, array_name: str = "z_ekinh", permuted: bool = False):
    """Print 8 hardcoded elements of array_name in a state before `state`."""

    # (nproma, nlev, nblocks) — nblocks=0, nlev<90, nproma<20000
    indices = [
        (0, 0, "(_for_it_22-1)"),
        (1, 1, "(_for_it_22-1)"),
        (10, 5, "(_for_it_22-1)"),
        (100, 10, "(_for_it_22-1)"),
        (500, 45, "(_for_it_22-1)"),
        (1000, 10, "(_for_it_22-1)"),
        (5000, 45, "(_for_it_22-1)"),
        (7000, 60, "(_for_it_22-1)"),
    ]

    print_state = sdfg.add_state_after(state, "print_values")

    inp_set = {f"_in_{i}" for i in range(len(indices))}
    code_lines = ["#pragma omp critical", "{"]
    code_lines.append(f'printf("[Print] {array_name}:\\n");')
    for i, (np_i, nl_i, nb_i) in enumerate(indices):
        if permuted:
            code_lines.append(f'printf("  [{nl_i},{np_i},{nb_i}] = %.17e\\n", _in_{i});')
        else:
            code_lines.append(f'printf("  [{np_i},{nl_i},{nb_i}] = %.17e\\n", _in_{i});')
    code_lines.append("fflush(stdout);")
    code_lines.append("}")

    tasklet = dace.nodes.Tasklet(
        "print_elems", inputs=inp_set, outputs={},
        code="\n".join(code_lines),
        language=dace.dtypes.Language.CPP,
        code_global='#include <cstdio>',
        side_effects=True,
    )

    copy_state = sdfg.add_state_before(print_state, "copy_for_print")
    an_copy = copy_state.add_access("gpu_" + array_name)
    an2_copy = copy_state.add_access(array_name)
    if array_name not in sdfg.arrays:
        ddesc = copy.deepcopy(sdfg.arrays["gpu_" + array_name])
        ddesc.storage = dace.StorageType.CPU_Heap
        ddesc.transient = True
        sdfg.add_datadesc(
            array_name,
            ddesc,
            False
        )
    copy_state.add_edge(an_copy, None, an2_copy, None, dace.Memlet.from_array("gpu_" + array_name, sdfg.arrays["gpu_" + array_name]))

    print_state.add_node(tasklet)

    an = print_state.add_access(array_name)
    for i, (np_i, nl_i, nb_i) in enumerate(indices):
        if permuted:
            # permute_map [1, 0, 2]: original [d0,d1,d2] -> permuted [d1,d0,d2]
            idx = f"{nl_i}, {np_i}, {nb_i}"
        else:
            idx = f"{np_i}, {nl_i}, {nb_i}"

        print_state.add_edge(
            an, None, tasklet, f"_in_{i}",
            dace.Memlet(f"{array_name}[{idx}]")
        )


def permute_single_map_gpu(sdfg: dace.SDFG):
    map, state =delete_all_maps_except(
        sdfg,
        {"_for_it_23", "_for_it_22", "_for_it_24"},
        {"_for_it_23", "_for_it_24"},
    )
    assert map is not None
    assert state is not None
    sdfg.save("extracted.sdfgz", compress=True)

    PermuteDimensions(
        permute_map={
            "gpu_z_ekinh": [1, 0, 2],
            "gpu_z_kin_hor_e": [1, 0, 2],
            "gpu___CG_p_int__m_e_bln_c_s": [1, 0, 2],
            "gpu___CG_p_patch__CG_cells__m_edge_idx": [2, 0, 1],
            "gpu___CG_p_patch__CG_cells__m_edge_blk": [2, 0, 1],
            "gpu_z_w_con_c": [1, 0],
            "gpu___CG_p_prog__m_w": [1, 0, 2],
        },
        add_permute_maps=True,
        column_major=True,
    ).apply_pass(sdfg, {})

    inverse_permute_map={
        "gpu_z_ekinh": [1, 0, 2],
        "gpu_z_kin_hor_e": [1, 0, 2],
        "gpu___CG_p_int__m_e_bln_c_s": [1, 0, 2],
        "gpu___CG_p_patch__CG_cells__m_edge_idx": [1, 2, 0],
        "gpu___CG_p_patch__CG_cells__m_edge_blk": [1, 2, 0],
        "gpu_z_w_con_c": [1, 0],
        "gpu___CG_p_prog__m_w": [1, 0, 2],
    }

    sdfg.save("post_transform.sdfgz", compress=True)
    sdfg.validate()

    permute_in_state = {s for s in sdfg.all_states() if s.label == "permute_in"}.pop()
    permute_out_state = {s for s in sdfg.all_states() if s.label == "permute_out"}.pop()

    entry_interface_state = {s for s in sdfg.all_states() if s.label == "entry_interface"}.pop()
    exit_interface_state = {s for s in sdfg.all_states() if s.label == "block" and "deflatten" in {n.label for n in s.nodes()} }.pop()

    move_state_after(sdfg, permute_in_state, entry_interface_state)
    move_state_before(sdfg, permute_out_state, exit_interface_state)

    # Change names back in interface states
    for s in {entry_interface_state, exit_interface_state}:
        for e in s.edges():
            if e.data.data is not None and e.data.data.startswith("permuted_"):
                e.data.data = e.data.data.removeprefix("permuted_")
                if e.data.data in inverse_permute_map:
                                        
                    # Permute the memlet subset with the inverse
                    new_subset = []
                    permute_indices = inverse_permute_map[e.data.data]
                    for i in range(len(permute_indices)):
                        new_subset.append(e.data.subset[permute_indices[i]])
                    e.data.subset = dace.subsets.Range(new_subset)

        for n in s.data_nodes():
            if n.data is not None and n.data.startswith("permuted_"):
                n.data = n.data.removeprefix("permuted_")

    sdfg.save("moved.sdfgz", compress=True)
    sdfg.validate()

    mstate, parent_sdfg = find_map_state(sdfg, {"_for_it_23", "_for_it_24"})
    assert mstate is not None
    timer_state_before, timer_state_after = add_timer_around_gpu(parent_sdfg, mstate)
    add_print_after_gpu(parent_sdfg, timer_state_after, "z_ekinh", True)

    from dace.transformation.dataflow import MapDimShuffle

    MapDimShuffle().apply_to(sdfg=state.sdfg, map_entry=map, options={"parameters": ["_for_it_24", "_for_it_23"]})

    add_symbols(sdfg)
    sdfg.save("permuted.sdfgz", compress=True)
    sdfg.validate()
    return sdfg




def add_timer_single_map_gpu(sdfg: dace.SDFG):
    mstate, parent_sdfg = find_map_state(sdfg, {"_for_it_23", "_for_it_24"})
    map, state = delete_all_maps_except(
        sdfg,
        {"_for_it_23", "_for_it_22", "_for_it_24"},
        {"_for_it_23", "_for_it_24"},
    )
    assert mstate is not None
    timer_state_before, timer_state_after = add_timer_around_gpu(parent_sdfg, mstate)
    add_print_after_gpu(parent_sdfg, timer_state_after, "z_ekinh", False)
    add_symbols(sdfg)

    sdfg.save("with_timer.sdfgz", compress=True)
    sdfg.validate()
    return sdfg

import copy

if __name__ == "__main__":
    sdfg = dace.SDFG.from_file("../codegen/gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_stage6.sdfgz")
    old = copy.deepcopy(sdfg)
    permuted_sdfg = permute_single_map_gpu(sdfg)
    permuted_sdfg.name = "permuted_" + sdfg.name
    #permuted_sdfg.compile()
    add_timer_single_map_gpu(old)
    #old.compile()
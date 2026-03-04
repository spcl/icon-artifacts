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
    map_iterators: set[str]
):
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry) and n in g.nodes():
            if map_iterators.intersection(set(n.map.params)) == set():
                # Remove map and all nodes in it
                _rm_map(g, n)


def find_map_state(sdfg: dace.SDFG, map_iterators: set[str]) -> typing.Tuple[dace.SDFGState, dace.SDFG]:
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry) and all(it in map_iterators for it in n.map.params):
            return g, g.parent_graph
    raise ValueError(f"Map with iterators {map_iterators} not found.")

def add_timer_around(sdfg: dace.SDFG, state: dace.SDFGState, host: bool = False):
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
        cudaEventCreate(&start);
        cudaEventCreate(&stop);

        // Record the start point on the default stream
        cudaEventRecord(start, 0);
        
        is_first_call = false;
        std::cout << "[Timer] Start recorded..." << std::endl;
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
""" if host is False else
"""
static void gpu_timer_split() {
    static std::chrono::high_resolution_clock::time_point start;
    static bool is_first_call = true;
    if (is_first_call) {
        cudaDeviceSynchronize();
        start = std::chrono::high_resolution_clock::now();
        is_first_call = false;
        std::cout << "[Timer] Start recorded..." << std::endl;
    } else {
        cudaDeviceSynchronize();
        auto stop = std::chrono::high_resolution_clock::now();
        double milliseconds = std::chrono::duration<double, std::milli>(stop - start).count();
        std::cout << "[Timer] Elapsed time: " << milliseconds << " ms" << std::endl;
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


def permute_single_map(sdfg: dace.SDFG, host:bool=False):
    delete_all_maps_except(
        sdfg,
        {"_for_it_23", "_for_it_22"},
    )

    PermuteDimensions(
        permute_map={
            "z_ekinh": [1, 0, 2],
            "z_kin_hor_e": [1, 0, 2],
            "__GG_p_int__m_e_bln_c_s": [1, 0, 2],
            "__CG_p_patch__CG_cells__m_edge_idx": [2, 0, 1],
            "__CG_p_patch__CG_cells__m_edge_blk": [2, 0, 1],
        },
        add_permute_maps=True,
        column_major=True,
    ).apply_pass(sdfg, {})

    permute_in_state = {s for s in sdfg.all_states() if s.label == "permute_in"}.pop()
    permute_out_state = {s for s in sdfg.all_states() if s.label == "permute_out"}.pop()

    entry_interface_state = {s for s in sdfg.all_states() if s.label == "entry_interface"}.pop()
    exit_interface_state = {s for s in sdfg.all_states() if s.label == "block" and "deflatten" in {n.label for n in s.nodes()} }.pop()

    move_state_after(sdfg, permute_in_state, entry_interface_state)
    move_state_before(sdfg, permute_out_state, exit_interface_state)

    # Change names back in interface states
    permuted_names = {
        "permuted_z_ekinh",
        "permuted_z_kin_hor_e",
        "permuted___GG_p_int__m_e_bln_c_s",
        "permuted___CG_p_patch__CG_cells__m_edge_idx",
        "permuted___CG_p_patch__CG_cells__m_edge_blk",
    }
    for s in {entry_interface_state, exit_interface_state}:
        for e in s.edges():
            if e.data.data in permuted_names:
                e.data.data = e.data.data.removeprefix("permuted_")
        for n in s.data_nodes():
            if n.data in permuted_names:
                n.data = n.data.removeprefix("permuted_")

    sdfg.save("moved.sdfgz", compress=True)
    sdfg.validate()

    mstate, parent_sdfg = find_map_state(sdfg, {"_for_it_23", "_for_it_24"})
    assert mstate is not None
    add_timer_around(parent_sdfg, mstate, host)
    sdfg.save("permuted.sdfgz", compress=True)

    return sdfg

def add_timer_single_map(sdfg: dace.SDFG, host:bool=False):
    mstate, parent_sdfg = find_map_state(sdfg, {"_for_it_23", "_for_it_24"})
    assert mstate is not None
    add_timer_around(parent_sdfg, mstate, host)
    sdfg.save("with_timer.sdfgz", compress=True)
    return sdfg

if __name__ == "__main__":
    sdfg = dace.SDFG.from_file("../codegen/gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_stage5.sdfgz")
    permuted_sdfg = permute_single_map(sdfg)
    add_timer_single_map(sdfg)
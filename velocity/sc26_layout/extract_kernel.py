import typing
import dace
from dace.transformation.layout.permute_dimensions import PermuteDimensions
from dace.sdfg.construction_utils import move_state_after, move_state_before

from sc26_layout.extract_gpu_kernel import CPU_PERMUTE_CONFIGS

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

def add_timer_around(sdfg: dace.SDFG, state: dace.SDFGState, host: bool = False):
    clock_in = sdfg.add_state_before(state, "clock_in")
    clock_out = sdfg.add_state_after(state, "clock_out")

    ct1 = dace.nodes.Tasklet(
        "c1", inputs={}, outputs={},
        code="cpu_timer_split();",
        language=dace.dtypes.Language.CPP,
        side_effects=True,
        code_global=f"""

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>

static constexpr int FLUSH_N        = 8192*4;
static constexpr int FLUSH_STEPS    = 20;

static double* flush_A = nullptr;
static double* flush_B = nullptr;

static void jacobi2d_cpu(const double* __restrict__ src,
                         double* __restrict__ dst,
                         int N)
{{
    for (int i = 1; i < N - 1; ++i) {{
        for (int j = 1; j < N - 1; ++j) {{
            dst[i * N + j] = 0.25 * (src[(i - 1) * N + j] +
                                      src[(i + 1) * N + j] +
                                      src[i * N + (j - 1)] +
                                      src[i * N + (j + 1)]);
        }}
    }}
}}

static void jacobi2d_init_cpu(double* A, int N)
{{
    for (int i = 0; i < N * N; ++i) {{
        int r = i / N;
        int c = i % N;
        A[i] = (r == 0 || r == N - 1 || c == 0 || c == N - 1) ? 1.0 : 0.0;
    }}
}}

static void flush_all_caches()
{{
    size_t total = (size_t)FLUSH_N * FLUSH_N;
    size_t bytes = total * sizeof(double);

    if (!flush_A) {{
        flush_A = (double*)malloc(bytes);
        flush_B = (double*)malloc(bytes);
    }}

    jacobi2d_init_cpu(flush_A, FLUSH_N);
    jacobi2d_init_cpu(flush_B, FLUSH_N);

    double* src = flush_A;
    double* dst = flush_B;

    for (int step = 0; step < FLUSH_STEPS; ++step) {{
        jacobi2d_cpu(src, dst, FLUSH_N);
        double* tmp = src;
        src = dst;
        dst = tmp;
    }}

    srand(42);
    int spots[4][2];
    for (int k = 0; k < 4; ++k) {{
        spots[k][0] = 1 + rand() % (FLUSH_N - 2);
        spots[k][1] = 1 + rand() % (FLUSH_N - 2);
    }}

    double hash = 0.0;
    for (int k = 0; k < 4; ++k) {{
        hash += src[spots[k][0] * FLUSH_N + spots[k][1]];
    }}

    static bool printed = false;
    if (!printed) {{
        std::cout << "[flush] jacobi2d hash = " << hash << std::endl;
        printed = true;
    }}
}}


static void cpu_timer_split() {{
    static std::chrono::high_resolution_clock::time_point t_start;
    static bool is_first_call = true;

    if (is_first_call) {{
        is_first_call = false;
        flush_all_caches();

        std::cout << "[Timer] Start recorded..." << std::endl;

        t_start = std::chrono::high_resolution_clock::now();
    }} else {{
        auto t_stop = std::chrono::high_resolution_clock::now();

        double milliseconds = std::chrono::duration<double, std::milli>(t_stop - t_start).count();

        std::cout << "[Timer] Elapsed time: " << milliseconds << " ms" << std::endl;

        flush_all_caches();

        is_first_call = true;
    }}
}}
"""
    )
    ct2 = dace.nodes.Tasklet(
        "c1", inputs={}, outputs={},
        code="cpu_timer_split();",
        language=dace.dtypes.Language.CPP,
        code_global="",
        side_effects=True,
    )

    clock_in.add_node(ct1)
    clock_out.add_node(ct2)

    return clock_in, clock_out


def add_symbols(sdfg: dace.SDFG):
    symlist = [
        "__f2dace_A_z_kin_hor_e_d_0_s", "__f2dace_A_z_kin_hor_e_d_1_s",
        "__f2dace_A_z_kin_hor_e_d_2_s", "__f2dace_A_z_vt_ie_d_0_s",
        "__f2dace_A_z_vt_ie_d_1_s",     "__f2dace_A_z_vt_ie_d_2_s",
        "__f2dace_A_z_w_concorr_me_d_0_s", "__f2dace_A_z_w_concorr_me_d_1_s",
        "__f2dace_A_z_w_concorr_me_d_2_s", "__f2dace_OA_z_kin_hor_e_d_0_s",
        "__f2dace_OA_z_kin_hor_e_d_1_s", "__f2dace_OA_z_kin_hor_e_d_2_s",
        "__f2dace_OA_z_vt_ie_d_0_s",    "__f2dace_OA_z_vt_ie_d_1_s",
        "__f2dace_OA_z_vt_ie_d_2_s",    "__f2dace_OA_z_w_concorr_me_d_0_s",
        "__f2dace_OA_z_w_concorr_me_d_1_s", "__f2dace_OA_z_w_concorr_me_d_2_s",
        "dt_linintp_ubc", "dtime", "istep", "ldeepatmo", "lvn_only", "ntnd",
    ]
    new_start = sdfg.add_state_before(sdfg.start_block, "sym_force_use", True)
    sname, _ = sdfg.add_scalar("dummy_symbol_sum", dtype=dace.float64,
                                transient=True, storage=dace.StorageType.Register)
    inputs = {sym for sym in symlist if sym in sdfg.arrays}
    tstr = (
        "_out = "
        + " + ".join(f"_in_{inp}" for inp in inputs)
        + " + "
        + " + ".join(sym for sym in symlist if sym not in inputs)
    )
    new_tasklet = new_start.add_tasklet(
        "sym_force_use", {"_in_" + s for s in inputs}, {"_out"}, tstr,
        side_effects=True)
    for sym in symlist:
        if sym in sdfg.arrays:
            an = new_start.add_access(sym)
            new_start.add_edge(an, None, new_tasklet, "_in_" + sym,
                               dace.Memlet(f"{sym}[0]"))
        elif sym not in sdfg.symbols:
            sdfg.add_symbol(sym, dace.int32, False)
    new_start.add_edge(new_tasklet, "_out", new_start.add_access(sname), None,
                       dace.Memlet(f"{sname}[0]"))

def add_print_after(sdfg: dace.SDFG, state: dace.SDFGState, array_name: str = "z_ekinh", permuted: bool = False, host: bool = True):
    """Print 8 hardcoded elements of array_name in a state before `state`."""

    # (nproma, nlev, nblocks) — nblocks=0, nlev<90, nproma<20000
    indices = [
        (0, 0, "(_for_it_22-1)"),
        (1, 1, "(_for_it_22-1)"),
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

    if host:
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
    else:
        copy_state = sdfg.add_state_before(print_state, "copy_for_print")
        an_copy = copy_state.add_access(array_name)
        raise Exception("Not implemented yet")

def add_print_before(sdfg: dace.SDFG, state: dace.SDFGState, array_name: str = "z_kin_hor_e", permuted: bool = False):
    """Print 8 hardcoded elements of array_name in a state before `state`."""

    # (nproma, nlev, nblocks) — nblocks=0, nlev<90, nproma<20000
    indices = [
        (0, 0, "(_for_it_22-1)"),
        (1, 1, "(_for_it_22-1)"),
    ]

    print_state = sdfg.add_state_before(state, "print_values")

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



def permute_single_map(sdfg: dace.SDFG, host:bool=True, config_name: str = "single_map", shuffle_map: bool = True):
    map, state =delete_all_maps_except(
        sdfg,
        {"_for_it_23", "_for_it_22", "_for_it_24"},
        {"_for_it_23", "_for_it_24"},
    )
    assert map is not None
    assert state is not None
    sdfg.save("extracted.sdfgz", compress=True)

    cfg = CPU_PERMUTE_CONFIGS[config_name]
    pmap = cfg["permute_map"]
    inverse_pmap = cfg["inverse_permute_map"]
    PermuteDimensions(
        permute_map=pmap,
        add_permute_maps=True,
        column_major=True,
    ).apply_pass(sdfg, {})

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
        for n in s.data_nodes():
            if n.data is not None and n.data.startswith("permuted_"):
                n.data = n.data.removeprefix("permuted_")

    sdfg.save("moved.sdfgz", compress=True)
    sdfg.validate()

    mstate, parent_sdfg = find_map_state(sdfg, {"_for_it_23", "_for_it_24"})
    assert mstate is not None
    timer_state_before, timer_state_after = add_timer_around(parent_sdfg, mstate, host)
    add_print_before(parent_sdfg, timer_state_before, "z_kin_hor_e", True)
    add_print_after(parent_sdfg, timer_state_after, "z_ekinh", True, host)

    from dace.transformation.dataflow import MapDimShuffle

    if shuffle_map:
        MapDimShuffle().apply_to(sdfg=state.sdfg, map_entry=map, options={"parameters": ["_for_it_24", "_for_it_23"]})

    add_symbols(sdfg)
    sdfg.save("permuted.sdfgz", compress=True)

    return sdfg




def add_timer_single_map(sdfg: dace.SDFG, host:bool=True):
    mstate, parent_sdfg = find_map_state(sdfg, {"_for_it_23", "_for_it_24"})
    map, state = delete_all_maps_except(
        sdfg,
        {"_for_it_23", "_for_it_22", "_for_it_24"},
        {"_for_it_23", "_for_it_24"},
    )
    assert mstate is not None
    timer_state_before, timer_state_after = add_timer_around(parent_sdfg, mstate, host)
    add_print_before(parent_sdfg, timer_state_before, "z_kin_hor_e", False)
    add_print_after(parent_sdfg, timer_state_after, "z_ekinh", False, host)
    add_symbols(sdfg)

    sdfg.save("with_timer.sdfgz", compress=True)
    return sdfg

import copy

if __name__ == "__main__":
    sdfg = dace.SDFG.from_file("../codegen/gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_stage5.sdfgz")
    old = copy.deepcopy(sdfg)
    permuted_sdfg = permute_single_map(sdfg)
    permuted_sdfg.name = "permuted_" + sdfg.name
    #permuted_sdfg.compile()
    add_timer_single_map(old)
    #old.compile()


"""
[Timer] Elapsed time: 37.035 ms
[Print] z_ekinh:
  [0,0,(_for_it_22-1)] = 1.70281939464071198e-04
  [1,1,(_for_it_22-1)] = 3.12412518946396899e-03
  [10,5,(_for_it_22-1)] = 1.45012788975412751e-02
  [100,10,(_for_it_22-1)] = 1.01763123945524558e+01
  [500,45,(_for_it_22-1)] = 2.17530906554460245e+02
  [1000,10,(_for_it_22-1)] = 2.09384216311808700e+02
  [5000,45,(_for_it_22-1)] = 2.00852264216740394e+02
  [7000,60,(_for_it_22-1)] = 2.88105312640896614e+02
"""
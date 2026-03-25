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

def add_timer_around_gpu(sdfg: dace.SDFG, state: dace.SDFGState, root_sdfg: dace.SDFG):
    clock_in = sdfg.add_state_before(state, "clock_in")
    clock_out = sdfg.add_state_after(state, "clock_out")

    ct1 = dace.nodes.Tasklet(
        "c1", inputs={}, outputs={},
        code="gpu_timer_split(__state);",
        language=dace.dtypes.Language.CPP,
        side_effects=True,
        code_global=f"""

#include <iostream>
#include <cuda_runtime.h>
#include <cstdlib>
#include <cstdio>

static constexpr int FLUSH_N        = 8192*4;
static constexpr int FLUSH_STEPS    = 20;
static constexpr int FLUSH_BLOCK_X  = 32;
static constexpr int FLUSH_BLOCK_Y  = 8;

static double* flush_A = nullptr;
static double* flush_B = nullptr;

static __global__ void jacobi2d_kernel(const double* __restrict__ src,
                                       double* __restrict__ dst,
                                       int N)
{{
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;

    if (i >= 1 && i < N - 1 && j >= 1 && j < N - 1) {{
        dst[i * N + j] = 0.25 * (src[(i - 1) * N + j] +
                                  src[(i + 1) * N + j] +
                                  src[i * N + (j - 1)] +
                                  src[i * N + (j + 1)]);
    }}
}}

static __global__ void jacobi2d_init_kernel(double* A, int N)
{{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int total = N * N;
    for (int i = idx; i < total; i += gridDim.x * blockDim.x) {{
        int r = i / N;
        int c = i % N;
        // Boundary = 1.0, interior = 0.0
        A[i] = (r == 0 || r == N - 1 || c == 0 || c == N - 1) ? 1.0 : 0.0;
    }}
}}

static void flush_all_caches()
{{
    size_t bytes = (size_t)FLUSH_N * FLUSH_N * sizeof(double);

    if (!flush_A) {{
        cudaMalloc(&flush_A, bytes);
        cudaMalloc(&flush_B, bytes);
    }}

    // Initialise both arrays
    int init_threads = 256;
    int init_blocks  = (FLUSH_N * FLUSH_N + init_threads - 1) / init_threads;
    jacobi2d_init_kernel<<<init_blocks, init_threads>>>(flush_A, FLUSH_N);
    jacobi2d_init_kernel<<<init_blocks, init_threads>>>(flush_B, FLUSH_N);
    cudaDeviceSynchronize();

    // Run 20 Jacobi steps – ping-pong between A and B
    dim3 block(FLUSH_BLOCK_X, FLUSH_BLOCK_Y);
    dim3 grid((FLUSH_N + block.x - 1) / block.x,
              (FLUSH_N + block.y - 1) / block.y);

    double* src = flush_A;
    double* dst = flush_B;

    for (int step = 0; step < FLUSH_STEPS; ++step) {{
        jacobi2d_kernel<<<grid, block>>>(src, dst, FLUSH_N);
        // Swap
        double* tmp = src;
        src = dst;
        dst = tmp;
    }}
    cudaDeviceSynchronize();

    // Print hash: sum of 4 deterministic "random" elements
    // Picks corners of the interior region so the value is non-trivial.
    // Generate 4 random interior points
    srand(42);  // fixed seed for reproducibility
    int spots[4][2];
    for (int k = 0; k < 4; ++k) {{
        spots[k][0] = 1 + rand() % (FLUSH_N - 2);
        spots[k][1] = 1 + rand() % (FLUSH_N - 2);
    }}

    double hash = 0.0;
    for (int k = 0; k < 4; ++k) {{
        double val;
        // After the loop, `src` points to the last written buffer
        cudaMemcpy(&val, src + spots[k][0] * FLUSH_N + spots[k][1],
                   sizeof(double), cudaMemcpyDeviceToHost);
        hash += val;
    }}
    // Print only on first call so it doesn't spam timing runs
    static bool printed = false;
    if (!printed) {{
        std::cout << "[flush] jacobi2d hash = " << hash << std::endl;
        printed = true;
    }}
}}


static void gpu_timer_split({root_sdfg.label}_state_t* __state) {{
    static cudaEvent_t start, stop;
    static bool is_first_call = true;
    cudaStream_t stream = __state->gpu_context->streams[0];

    if (is_first_call) {{
        // Initialize events on the first call
        cudaDeviceSynchronize();
        cudaStreamSynchronize(stream);

        is_first_call = false;
        cudaDeviceSynchronize();
        flush_all_caches();
        cudaDeviceSynchronize();

        std::cout << "[Timer] Start recorded..." << std::endl;
        // Flush L2 before measurement

        cudaEventCreate(&start);
        cudaEventCreate(&stop);

        // Record the start point on the default stream
        cudaEventRecord(start, stream);
    }} else {{
        // Record the stop point
        cudaEventRecord(stop, stream);

        // Wait for the GPU to actually reach the stop event
        cudaEventSynchronize(stop);

        float milliseconds = 0;
        cudaEventElapsedTime(&milliseconds, start, stop);

        std::cout << "[Timer] Elapsed time: " << milliseconds << " ms" << std::endl;

        // Flush L2 before measurement
        cudaDeviceSynchronize();
        flush_all_caches();
        cudaDeviceSynchronize();
        
        // Clean up and reset for potential future use
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
        is_first_call = true; 
    }}
}}
"""
    )
    ct2 = dace.nodes.Tasklet(
        "c1", inputs={}, outputs={},
        code="gpu_timer_split(__state);",
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

def add_print_after_gpu(sdfg: dace.SDFG, state: dace.SDFGState,
                        array_name: str = "z_ekinh", permuted: bool = False):
    """Print 8 hardcoded elements of array_name in a state before `state`."""

    # (nproma, nlev, nblocks) — nblocks=0, nlev<90, nproma<20000
    indices = [
        (0, 0, "(_for_it_22-1)"),
        (1, 1, "(_for_it_22-1)"),
        (4, 4, "(_for_it_22-1)"),
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
        code_lines.append(f'printf("start_block = %d, end_block = %d\\n", i_startblk_var_146, i_endblk_var_147);')
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

def _inverse_perm(p):
    inv = [0] * len(p)
    for i, v in enumerate(p):
        inv[v] = i
    return inv

def _make_config(permute_map):
    return {
        "permute_map": permute_map,
        "inverse_permute_map": {k: _inverse_perm(v) for k, v in permute_map.items()},
    }

# The 5 arrays that matter
_EKINH   = "gpu_z_ekinh"
_KINHOR  = "gpu_z_kin_hor_e"
_EBLN    = "gpu___CG_p_int__m_e_bln_c_s"
_EIDX    = "gpu___CG_p_patch__CG_cells__m_edge_idx"
_EBLK    = "gpu___CG_p_patch__CG_cells__m_edge_blk"

_ALL5    = [_EKINH, _KINHOR, _EBLN, _EIDX, _EBLK]
_COMPUTE = [_EKINH, _KINHOR]               # output/intermediate fields
_CONN    = [_EBLN, _EIDX, _EBLK]           # connectivity/index arrays

def _uniform(arrays, perm):
    """Same permutation for all listed arrays."""
    return _make_config({a: perm for a in arrays})
_EKINH   = "gpu_z_ekinh"
_KINHOR  = "gpu_z_kin_hor_e"
_EBLN    = "gpu___CG_p_int__m_e_bln_c_s"
_EIDX    = "gpu___CG_p_patch__CG_cells__m_edge_idx"
_EBLK    = "gpu___CG_p_patch__CG_cells__m_edge_blk"

_COMPUTE = [_EKINH, _KINHOR]
_EDGE    = [_EIDX, _EBLK]



def _inverse_perm(p):
    inv = [0] * len(p)
    for i, v in enumerate(p):
        inv[v] = i
    return inv

def _make_config(permute_map):
    return {
        "permute_map": permute_map,
        "inverse_permute_map": {k: _inverse_perm(v) for k, v in permute_map.items()},
    }


PERMUTE_CONFIGS = {
    # =========================================================================
    # compute=[0,1,2] (identity), sweep edge and bln independently
    # =========================================================================

    # edge=[0,1,2], bln varies
    "c012_e012_b021": _make_config({
        _EBLN: [0, 2, 1],
    }),
    "c012_e012_b102": _make_config({
        _EBLN: [1, 0, 2],
    }),
    "c012_e012_b120": _make_config({
        _EBLN: [1, 2, 0],
    }),
    "c012_e012_b201": _make_config({
        _EBLN: [2, 0, 1],
    }),
    "c012_e012_b210": _make_config({
        _EBLN: [2, 1, 0],
    }),

    # edge=[0,2,1]
    "c012_e021_b012": _make_config({
        **{a: [0, 2, 1] for a in _EDGE},
    }),
    "c012_e021_b021": _make_config({
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c012_e021_b102": _make_config({
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c012_e021_b120": _make_config({
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c012_e021_b201": _make_config({
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c012_e021_b210": _make_config({
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[1,0,2]
    "c012_e102_b012": _make_config({
        **{a: [1, 0, 2] for a in _EDGE},
    }),
    "c012_e102_b021": _make_config({
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c012_e102_b102": _make_config({
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c012_e102_b120": _make_config({
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c012_e102_b201": _make_config({
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c012_e102_b210": _make_config({
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[1,2,0]
    "c012_e120_b012": _make_config({
        **{a: [1, 2, 0] for a in _EDGE},
    }),
    "c012_e120_b021": _make_config({
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c012_e120_b102": _make_config({
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c012_e120_b120": _make_config({
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c012_e120_b201": _make_config({
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c012_e120_b210": _make_config({
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[2,0,1]
    "c012_e201_b012": _make_config({
        **{a: [2, 0, 1] for a in _EDGE},
    }),
    "c012_e201_b021": _make_config({
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c012_e201_b102": _make_config({
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c012_e201_b120": _make_config({
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c012_e201_b201": _make_config({
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c012_e201_b210": _make_config({
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[2,1,0]
    "c012_e210_b012": _make_config({
        **{a: [2, 1, 0] for a in _EDGE},
    }),
    "c012_e210_b021": _make_config({
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c012_e210_b102": _make_config({
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c012_e210_b120": _make_config({
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c012_e210_b201": _make_config({
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c012_e210_b210": _make_config({
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # =========================================================================
    # compute=[1,0,2], sweep edge and bln independently
    # =========================================================================

    # edge=[0,1,2], bln varies
    "c102_e012_b012": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
    }),
    "c102_e012_b021": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        _EBLN: [0, 2, 1],
    }),
    "c102_e012_b102": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        _EBLN: [1, 0, 2],
    }),
    "c102_e012_b120": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        _EBLN: [1, 2, 0],
    }),
    "c102_e012_b201": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        _EBLN: [2, 0, 1],
    }),
    "c102_e012_b210": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[0,2,1]
    "c102_e021_b012": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [0, 2, 1] for a in _EDGE},
    }),
    "c102_e021_b021": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c102_e021_b102": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c102_e021_b120": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c102_e021_b201": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c102_e021_b210": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [0, 2, 1] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[1,0,2]
    "c102_e102_b012": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 0, 2] for a in _EDGE},
    }),
    "c102_e102_b021": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c102_e102_b102": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c102_e102_b120": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c102_e102_b201": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c102_e102_b210": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 0, 2] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[1,2,0]
    "c102_e120_b012": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 2, 0] for a in _EDGE},
    }),
    "c102_e120_b021": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c102_e120_b102": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c102_e120_b120": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c102_e120_b201": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c102_e120_b210": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [1, 2, 0] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[2,0,1]
    "c102_e201_b012": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 0, 1] for a in _EDGE},
    }),
    "c102_e201_b021": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c102_e201_b102": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c102_e201_b120": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c102_e201_b201": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c102_e201_b210": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 0, 1] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),

    # edge=[2,1,0]
    "c102_e210_b012": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 1, 0] for a in _EDGE},
    }),
    "c102_e210_b021": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [0, 2, 1],
    }),
    "c102_e210_b102": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [1, 0, 2],
    }),
    "c102_e210_b120": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [1, 2, 0],
    }),
    "c102_e210_b201": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [2, 0, 1],
    }),
    "c102_e210_b210": _make_config({
        **{a: [1, 0, 2] for a in _COMPUTE},
        **{a: [2, 1, 0] for a in _EDGE},
        _EBLN: [2, 1, 0],
    }),
}

CPU_PERMUTE_CONFIGS = dict()
for conf, d in PERMUTE_CONFIGS.items():
    pmap = {k.replace("gpu_", ""): v for k,v in d["permute_map"].items()}
    ipmap = {k.replace("gpu_", "") for k,v in d["inverse_permute_map"].items()}

    nd = {
        "permute_map": pmap,
        "inverse_permute_map": ipmap,
    }
    CPU_PERMUTE_CONFIGS[conf] = nd


def permute_single_map_gpu(sdfg: dace.SDFG,
                           config_name: str = "single_map",
                           shuffle_map: bool = True):
    cfg = PERMUTE_CONFIGS[config_name]
    map, state =delete_all_maps_except(
        sdfg,
        {"_for_it_23", "_for_it_22", "_for_it_24"},
        {"_for_it_23", "_for_it_24"},
    )
    assert map is not None
    assert state is not None
    #sdfg.save("extracted.sdfgz", compress=True)

    PermuteDimensions(
        permute_map=cfg["permute_map"],
        add_permute_maps=True,
        column_major=True,
    ).apply_pass(sdfg, {})

    inverse_permute_map = cfg["inverse_permute_map"]

    #sdfg.save("post_transform.sdfgz", compress=True)
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

    #sdfg.save("moved.sdfgz", compress=True)
    sdfg.validate()

    mstate, parent_sdfg = find_map_state(sdfg, {"_for_it_23", "_for_it_24"})
    assert mstate is not None
    timer_state_before, timer_state_after = add_timer_around_gpu(parent_sdfg, mstate, sdfg)
    add_print_after_gpu(parent_sdfg, timer_state_after, "z_ekinh", True)

    from dace.transformation.dataflow import MapDimShuffle

    if shuffle_map:
        MapDimShuffle().apply_to(sdfg=state.sdfg, map_entry=map, options={"parameters": ["_for_it_24", "_for_it_23"]})

    add_symbols(sdfg)
    #sdfg.save("permuted.sdfgz", compress=True)
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
    timer_state_before, timer_state_after = add_timer_around_gpu(parent_sdfg, mstate, sdfg)
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
import dace
import copy
from typing import Set
from dace.properties import CodeBlock
from dace.codegen.control_flow import ConditionalBlock, ContinueBlock, ControlFlowBlock, ControlFlowRegion
from dace.sdfg import InterstateEdge
import dace.sdfg.utils as sdutil
import re

c = 0
def _add_copy_map(state: dace.SDFGState, src_arr_name:str, src_arr:dace.data.Data, dst_arr_name:str, dst_arr:dace.data.Data,
                  dtype):
    """
    Add a copy map to the given state in the SDFG.
    """
    assert src_arr.shape == dst_arr.shape, "Source and destination arrays must have the same shape."
    # Create a new map node
    map_ranges = []
    for dim, size in reversed(list(enumerate(src_arr.shape))):
        map_ranges.append((f"i{dim}", f"0:{size}"))
    access_str = f", ".join([str(s) for s, _ in reversed(map_ranges)])

    map_entry, map_exit = state.add_map(name=f"copy_map_{src_arr_name}_to_{dst_arr_name}", ndrange=map_ranges)

    if dst_arr.storage == dace.dtypes.StorageType.GPU_Global:
        map_entry.map.schedule = dace.ScheduleType.GPU_Device
    else:
        map_entry.map.schedule = dace.ScheduleType.CPU_Multicore

    # Add access nodes for source and destination arrays
    src_access = state.add_access(src_arr_name)
    dst_access = state.add_access(dst_arr_name)

    # Add edges from the map to the access nodes, care about the connector
    state.add_edge(src_access, None, map_entry, f"IN_{src_arr_name}", dace.memlet.Memlet.from_array(src_arr_name, src_arr))
    state.add_edge(map_exit, f"OUT_{dst_arr_name}", dst_access, None, dace.memlet.Memlet.from_array(dst_arr_name, dst_arr))
    map_entry.add_in_connector(f"IN_{src_arr_name}", dtype=src_arr.dtype)
    map_entry.add_out_connector(f"OUT_{src_arr_name}", dtype=dtype)
    map_exit.add_in_connector(f"IN_{dst_arr_name}", dtype=dtype)
    map_exit.add_out_connector(f"OUT_{dst_arr_name}", dtype=dtype)

    # Add a tasklet that perfmorms the type cast
    tasklet = state.add_tasklet(
        name=f"copy_{src_arr_name}_to_{dst_arr_name}",
        inputs={"in"},
        outputs={"out"},
        code=f"out = static_cast<{dtype.ctype}>(in);",
        language=dace.Language.CPP)

    state.add_edge(map_entry, f"OUT_{src_arr_name}", tasklet, "in", dace.Memlet(expr=f"{src_arr_name}[{access_str}]"))
    state.add_edge(tasklet, "out", map_exit, f"IN_{dst_arr_name}", dace.Memlet(expr=f"{dst_arr_name}[{access_str}]"))

def _repl_on_interstate_edges(sdfg: dace.SDFG, repl_dict: dict):
    for edge, graph in sdfg.all_edges_recursive():
        # print(type(edge)) -> Should be MulticonnectorEdge or so
        if edge.data is not None and isinstance(edge.data, InterstateEdge):
            for key, value in repl_dict.items():
                if key in edge.data.assignments:
                    _v = edge.data.assignments[key]
                    edge.data.assignments[value] = _v
            for key, value in repl_dict.items():
                if key in edge.data.assignments.values():
                    edge.data.assignments[key].replace(key, value)

def _lower_bidth_of_arrays_recursive(sdfg: dace.SDFG, array_names: Set[str], suffix: str, new_dtype: dace.dtypes.typeclass,
                                     ):
    if suffix == "int32":
        return
    repl_dict = {array_name: array_name + "_" + suffix for array_name in array_names}
    # Repl datadesc names
    for name in array_names:
        if name in sdfg.arrays:
            new_name = f"{name}_{suffix}"
            copy_desc = copy.deepcopy(sdfg.arrays[name])
            copy_desc.dtype = new_dtype
            copy_desc.lifetime = dace.AllocationLifetime.Persistent
            sdfg.remove_data(name, validate=False)
            sdfg.add_datadesc(new_name, copy_desc, find_new_name=False)
            sdfg.replace_dict(repldict=repl_dict)
    # Repl in and out connectors of NSDFG node
    nsdfgs = set()
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                conn_pair = set()
                for in_conn in node.in_connectors:
                    if in_conn in array_names:
                        new_in_conn = f"{in_conn}_{suffix}"
                        old_in_conn = in_conn
                        for ie in state.in_edges_by_connector(node, in_conn):
                            ie.dst_conn = new_in_conn
                        conn_pair.add((old_in_conn, new_in_conn))
                for old_in_conn, new_in_conn in conn_pair:
                    node.remove_in_connector(old_in_conn)
                    node.add_in_connector(new_in_conn)
                conn_pair.clear()
                for out_conn in node.out_connectors:
                    if out_conn in array_names:
                        new_out_conn = f"{out_conn}_{suffix}"
                        old_out_conn = out_conn
                        for oe in state.out_edges_by_connector(node, out_conn):
                            oe.src_conn = new_out_conn
                        conn_pair.add((old_out_conn, new_out_conn))
                for old_in_conn, new_in_conn in conn_pair:
                    node.remove_out_connector(old_out_conn)
                    node.add_out_connector(new_out_conn)
                nsdfgs.add(node.sdfg)
    # Now do the same replacedment in the NSDFG
    for nsdfg in nsdfgs:
        _lower_bidth_of_arrays_recursive(nsdfg, array_names, suffix, new_dtype)

    # Repl_dict does not work on nested SDFGs
    _repl_on_interstate_edges(sdfg, repl_dict)

def _insert_lower_bidth_of_arrays_recursive(cfg: ControlFlowRegion, array_names: Set[str], suffix: str, new_dtype: dace.dtypes.typeclass,
                                     ):
    if suffix == "int32":
        return
    repl_dict = {array_name: array_name + "_" + suffix for array_name in array_names}
    # Repl datadesc names
    for name in array_names:
        if name in cfg.sdfg.arrays:
            new_name = f"{name}_{suffix}"
            copy_desc = copy.deepcopy(cfg.sdfg.arrays[name])
            copy_desc.dtype = new_dtype
            copy_desc.lifetime = dace.AllocationLifetime.Persistent
            #sdfg.remove_data(name, validate=False)
            cfg.sdfg.add_datadesc(new_name, copy_desc, find_new_name=False)
            cfg.replace_dict(repl=repl_dict)
    # Repl in and out connectors of NSDFG node
    nsdfgs = set()
    for state in cfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                conn_pair = set()
                for in_conn in node.in_connectors:
                    if in_conn in array_names:
                        new_in_conn = f"{in_conn}_{suffix}"
                        old_in_conn = in_conn
                        for ie in state.in_edges_by_connector(node, in_conn):
                            ie.dst_conn = new_in_conn
                        conn_pair.add((old_in_conn, new_in_conn))
                for old_in_conn, new_in_conn in conn_pair:
                    node.remove_in_connector(old_in_conn)
                    node.add_in_connector(new_in_conn)
                conn_pair.clear()
                for out_conn in node.out_connectors:
                    if out_conn in array_names:
                        new_out_conn = f"{out_conn}_{suffix}"
                        old_out_conn = out_conn
                        for oe in state.out_edges_by_connector(node, out_conn):
                            oe.src_conn = new_out_conn
                        conn_pair.add((old_out_conn, new_out_conn))
                for old_in_conn, new_in_conn in conn_pair:
                    node.remove_out_connector(old_out_conn)
                    node.add_out_connector(new_out_conn)
                nsdfgs.add(node.sdfg)
    # Now do the same replacedment in the NSDFG
    for nsdfg in nsdfgs:
        _lower_bidth_of_arrays_recursive(nsdfg, array_names, suffix, new_dtype)

    # Repl_dict does not work on nested SDFGs
    _repl_on_interstate_edges(cfg, repl_dict)

def _fix_nsdfg_connectors(sdfg: dace.SDFG):
    # A -(edge)-> B where B is nested SDFG
    # if edge.data is not same as edge.dst_conn (or vice verse for outgoing) then change connector name and them replace stuff in the nsdfg
    # Recursively go deeper
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                repl_dict = dict()
                for ie in state.in_edges(node):
                    if ie.data is not None:
                        if ie.data.data != ie.dst_conn:
                            old_dst_conn = ie.dst_conn
                            ie.dst_conn = ie.data.data
                            node.remove_in_connector(old_dst_conn)
                            node.add_in_connector(ie.dst_conn, force=True)
                            repl_dict[old_dst_conn] = ie.dst_conn
                for oe in state.out_edges(node):
                    if oe.data is not None:
                        if oe.data.data != oe.src_conn:
                            old_src_conn = oe.src_conn
                            oe.src_conn = oe.data.data
                            node.remove_out_connector(old_src_conn)
                            node.add_out_connector(oe.src_conn, force=True)
                            repl_dict[old_src_conn] = oe.src_conn
                node.sdfg.replace_dict(repl_dict)
                #_repl_on_interstate_edges(node.sdfg, repl_dict)
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                _fix_nsdfg_connectors(node.sdfg)

def decrease_bitwidth_of_const_arrays(sdfg: dace.SDFG, array_names: Set[str], enable_uint16: bool = True,
                                      enable_int64: bool = False, nproma_name: str = None, assume_can_lower: bool = False):
    if assume_can_lower:
        assert enable_uint16 
        assert not enable_int64
        decrease_bitwidth_of_const_arrays_no_branching(
            sdfg, array_names,nproma_name
        )
   
    _fix_nsdfg_connectors(sdfg)
    sdfg.validate()
    global c
    # Not all arrays might be in use, filter the set again
    new_array_names = set()
    for name in array_names:
        if name in sdfg.arrays:
            # Filter for dtype = int64 or = int32
            if sdfg.arrays[name].dtype == dace.int64 or sdfg.arrays[name].dtype == dace.int32:
                new_array_names.add(name)

    array_names = new_array_names

    # 1. Ensure all arrays are constant arrays
    # If they are transient initializating them once is OK
    arrays_with_num_writes = {name: 0 for name in array_names}
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode) and node.data in array_names:
            if graph.in_degree(node) > 0 and any(ie.data is not None for ie in graph.in_edges(node)):
                arrays_with_num_writes[node.data] += 1

    assert all(arrays_with_num_writes[name] <= 1 for name in array_names), \
        "All arrays must be constant arrays, i.e. written to at most once."

    # Duplicate NSDFG regions - one with original names and then replace the accesses with fp16 or fp32
    if enable_int64:
        copy_int64 = copy.deepcopy(sdfg)
        sdutil.set_nested_sdfg_parent_references(copy_int64)
    copy_int32 = copy.deepcopy(sdfg)
    sdutil.set_nested_sdfg_parent_references(copy_int32)
    if enable_uint16:
        copy_uint16 = copy.deepcopy(sdfg)
        sdutil.set_nested_sdfg_parent_references(copy_uint16)

    sdfgs_and_suffixes = [
                        (copy_int32, "int32", dace.dtypes.int32)]
    if enable_uint16:
        sdfgs_and_suffixes.append((copy_uint16, "uint16", dace.dtypes.uint16))
    if enable_int64:
        sdfgs_and_suffixes.append((copy_int64, "int64", dace.dtypes.int64))
    if enable_int64:
        copy_body_int64 = list(copy_int64.bfs_nodes(copy_int64.start_block))[1]
    copy_body_int32 = list(copy_int32.bfs_nodes(copy_int32.start_block))[1]
    if enable_uint16:
        copy_body_uint16 = list(copy_uint16.bfs_nodes(copy_uint16.start_block))[1]

    # Replace all arrays with the corresponding bitwidth suffix
    for copy_sdfg, suffix, dtype in sdfgs_and_suffixes:
        if suffix != "int32":
            _lower_bidth_of_arrays_recursive(copy_sdfg, array_names, suffix, dtype)
        #copy_sdfg.save("decreased_bitwidth_" + suffix + ".sdfg")
        copy_sdfg.validate()

    # Combine all SDFGs into one within an if statement
    # After all the arrays are defined (HACK: between 1st and 2nd state right for velocity, TODO: general version)
    # run the kernel to detect to bitwidth necessary for int arrays
    # Write copy kernels that copy from higher bithwidth to lower bitwidth

    # Up this point it is velocity tendencies specific.
    # We would need to find the point where all arrays have been defined
    new_sdfg = copy.deepcopy(sdfg)
    sdutil.set_nested_sdfg_parent_references(new_sdfg)
    assert len(new_sdfg.nodes()) == 3 and len(list(new_sdfg.all_states())) == 3, f"Expected 3 nodes, got {len(new_sdfg.nodes())} and {len(list(new_sdfg.all_states()))} states got : {new_sdfg.nodes()}, {new_sdfg.all_states()}."
    copy_in, body, copy_out = list(new_sdfg.bfs_nodes(new_sdfg.start_block))[:3]
    #all_edges = new_sdfg.out_edges(copy_in) + new_sdfg.in_edges(copy_out)
    assert len(new_sdfg.out_edges(copy_in)) + len(new_sdfg.in_edges(copy_out)) == 2, f"{new_sdfg.out_edges(copy_in)},{new_sdfg.in_edges(copy_out)}"
    #new_edge_data = all_edges[0].data.assignments + all_edges[1].data.assignments
    #new_sdfg.add_edge(src=copy_in, dst=copy_out, data=InterstateEdge(assignments=new_edge_data))
    #check_state = new_sdfg.add_state_after(new_sdfg.start_state, "check_bitwidth")

    # Add int16, int32 suffixed version of arrays to the SDFG
    suffix_and_dtypes = [("int32", dace.dtypes.int32)]
    if enable_uint16:
        suffix_and_dtypes.append(("uint16", dace.dtypes.uint16))
    if enable_int64:
        suffix_and_dtypes.append(("int64", dace.dtypes.int64))
    def add_datadesc_rec(sdfg: dace.SDFG, suffix_and_dtypes):
        for suffix, dtype in suffix_and_dtypes:
            if suffix == "int32":
                continue
            for name in array_names:
                new_name = f"{name}_{suffix}"
                if new_name not in new_sdfg.arrays:
                    copy_desc = copy.deepcopy(new_sdfg.arrays[name])
                    copy_desc.dtype = dtype
                    copy_desc.lifetime = dace.AllocationLifetime.Persistent
                    print(f"Adding array {new_name} with dtype {copy_desc.dtype} to SDFG.")
                    new_sdfg.add_datadesc(new_name, copy_desc, find_new_name=False)
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    # Add the new arrays to the nested SDFG
                    add_datadesc_rec(node.sdfg, suffix_and_dtypes)
    add_datadesc_rec(sdfg, suffix_and_dtypes)


    #raise Exception("This is a hacky solution, please fix it later.")

    # CopyIn -> CheckBitwidth + CopyBitwidth -> AssignBitwidth -> Body -> CopyOut
    # IfCFG to CheckBitwidth
    # new_sdfg.save("s1.sdfgz", compress=True)
    # Read int into a symbol
    new_sdfg.add_symbol("bitwidth_check_done_sym", dace.int32)
    new_sdfg.add_symbol("bitwidth_sym", dace.int32)
    new_sdfg.add_scalar("bitwidth_check_done", dtype=dace.int32,
                        transient=True, storage=dace.StorageType.CPU_Heap,
                        lifetime=dace.AllocationLifetime.Persistent)
    new_sdfg.add_scalar("bitwidth_scalar", dtype=dace.int32,
                        transient=True, storage=dace.StorageType.CPU_Heap,
                        lifetime=dace.AllocationLifetime.Persistent)

    # If call == 0 (check has not been done yet), check the required bitwidth of int arrays (will take max)
    check_if = ConditionalBlock(label="check_bitwidth_cond", sdfg=new_sdfg, parent=new_sdfg)
    check_cfg = ControlFlowRegion(label="check_bitwidth_cfg", sdfg=check_if.sdfg, parent=check_if)
    check_state = dace.SDFGState(label="extract_state", sdfg=check_if.sdfg)
    check_cfg.add_node(check_state)
    new_sdfg.add_node(check_if)
    check_if.add_branch(condition=CodeBlock(code="bitwidth_check_done_sym == 0"), branch=check_cfg)

    # The check pattern to fill is the following:
    """
    #if defined(DACE_VELOCITY_DEBUG)
    int32_t check_bounds_on_device_{c}(const int64_t* h_input, const int64_t* h_output, int64_t size, const std::string& array_name);
    #else
    int32_t check_bounds_on_device_{c}(const int64_t* h_input, const int64_t* h_output, int64_t size);
    #endif
    """

    """
    for (arr_name, arr) in sdfg.arrays.items(){
        if (bitwidth_scalar != 64){
            #if defined(DACE_VELOCITY_DEBUG)
            bitwidth_scalar = check_bounds_on_device_{c}(<array.name>, <array.shape>, "<array.name>");
            #else
            bitwidth_scalar = check_bounds_on_device_{c}(<array.name>, <array.shape>);
            #endif
        }
    }
    """
    tasklet_code = " int32_t _internal_bitwidth_scalar = -1;\n"
    for arr_name in array_names:
        arr = new_sdfg.arrays[arr_name]
        arr.total_size
        tasklet_code += f"""
        if (_internal_bitwidth_scalar != 64){{ // TODO: Replace 64 with 32
            #if defined(DACE_VELOCITY_DEBUG)
            _internal_bitwidth_scalar = check_bounds_on_device_{c}({arr_name}, {arr.total_size} * sizeof({arr.dtype.ctype}), "{arr_name}");
            #else
            _internal_bitwidth_scalar = check_bounds_on_device_{c}({arr_name}, {arr.total_size} * sizeof({arr.dtype.ctype}));
            #endif
        }}

"""
    runtime_array_check_global_code = f"""
#include <cuda_runtime.h>
#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <limits>
#if defined(DACE_VELOCITY_DEBUG)
#include <thrust/device_ptr.h>
#include <thrust/extrema.h>
#include <thrust/execution_policy.h>
#endif

template <typename T>
__device__ __inline__ int32_t check_bounds(T val) {{
    if (val >= 0 && val <= static_cast<T>(std::numeric_limits<uint16_t>::max())) {{
        return 16;
    }} else if (val >= static_cast<T>(std::numeric_limits<int16_t>::min()) &&
                val <= static_cast<T>(std::numeric_limits<int16_t>::max())) {{
        return 24;
    }} else {{
        return 32;
    }}
}}

template <typename T>
void check_bounds_with_thrust_{c}(const T* d_input, int32_t size, const std::string& array_name) {{
    thrust::device_ptr<const T> dev_ptr(d_input);

    auto min_it = thrust::min_element(thrust::device, dev_ptr, dev_ptr + size);
    auto max_it = thrust::max_element(thrust::device, dev_ptr, dev_ptr + size);

    T h_min, h_max;
    cudaMemcpy(&h_min, min_it.get(), sizeof(T), cudaMemcpyDeviceToHost);
    cudaMemcpy(&h_max, max_it.get(), sizeof(T), cudaMemcpyDeviceToHost);

    printf("For array %s: (min: %d, max: %d)\\n", array_name.c_str(), static_cast<int32_t>(h_min), static_cast<int32_t>(h_max));
}}

template <typename T>
__global__ void check_bounds_kernel_{c}(const T* __restrict__ input, int32_t size, int32_t* __restrict__ result) {{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= size) return;

    int32_t required_bits = check_bounds(input[idx]);
    if (required_bits == 16){{
        result[0] = 1;
    }} else if (required_bits == 24){{
        result[1] = 1;
    }}else if (required_bits == 32){{
        result[2] = 1;
    }}
}}


template <typename T>
int32_t check_bounds_on_device_{c}(const T* d_input, int32_t size,
#if defined(DACE_VELOCITY_DEBUG)
const std::string& array_name
#endif
) {{
    int32_t* d_result = nullptr;
    int32_t* h_result = new int32_t[3]; // Initialize results for 16, 32, and 64 bits
    h_result[0] = -1; // 16 bits
    h_result[1] = -1; // 24 bits
    h_result[2] = -1; // 32 bits
    int32_t threads = 256;
    int32_t blocks = (size + threads - 1) / threads;

    // Allocate device memory
    cudaError_t err = cudaMalloc((void**)&d_result, sizeof(int32_t) * 3);
    if (err != cudaSuccess) {{
        printf("cudaMalloc error: %s\\n", cudaGetErrorString(err));
        delete[] h_result;
        throw std::runtime_error("Failed to allocate device memory");
    }}

    // Initialize device memory to zero
    err = cudaMemset(d_result, 0, sizeof(int32_t) * 3);
    if (err != cudaSuccess) {{
        printf("cudaMemset error: %s\\n", cudaGetErrorString(err));
        cudaFree(d_result);
        delete[] h_result;
        throw std::runtime_error("Failed to initialize device memory");
    }}

    // Launch kernel
    check_bounds_kernel_{c}<<<blocks, threads>>>(d_input, size, d_result);

    // Check for kernel launch errors
    err = cudaGetLastError();
    if (err != cudaSuccess) {{
        printf("Kernel launch error: %s\\n", cudaGetErrorString(err));
        cudaFree(d_result);
        delete[] h_result;
        throw std::runtime_error("Kernel launch failed");
    }}

    // Wait for kernel to complete
    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {{
        printf("cudaDeviceSynchronize error: %s\\n", cudaGetErrorString(err));
        cudaFree(d_result);
        delete[] h_result;
        throw std::runtime_error("Kernel execution failed");
    }}

    // Copy results back
    err = cudaMemcpy(h_result, d_result, sizeof(int32_t) * 3, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {{
        printf("cudaMemcpy error: %s\\n", cudaGetErrorString(err));
        cudaFree(d_result);
        delete[] h_result;
        throw std::runtime_error("Failed to copy results from device");
    }}

    int32_t num_bits = 16;
    if (h_result[2] == 1) {{
        num_bits = 32;
    }} else if (h_result[1] == 1) {{
        num_bits = 24;
    }} else if (h_result[0] == 1) {{
        num_bits = 16;
    }} else {{
        num_bits = -1;
        throw std::runtime_error("No valid bounds found for " +
        #if defined(DACE_VELOCITY_DEBUG)
        array_name +
        #endif
        " the input values." + "{{i16,ui16,i32}}: " + ", " + std::to_string(h_result[0]) + ", " + std::to_string(h_result[1]) + ", " + std::to_string(h_result[2]));
    }}

    #if defined(DACE_VELOCITY_DEBUG)
    printf("Bitwidth for %s: %d bits {{%d, %d, %d}}\\n", array_name.c_str(), num_bits, h_result[0], h_result[1], h_result[2]);
    check_bounds_with_thrust_{c}(d_input, size, array_name);
    #endif

    cudaFree(d_result);
    delete[] h_result;

    return num_bits == 24 ? 32 : num_bits; // Return 32 for 24 bits as well;
}}
"""
    tasklet_code += "_out_bitwidth_check_done = 1;\n _out_bitwidth_scalar = _internal_bitwidth_scalar;\n"
    """
    _t = check_state.add_tasklet(
        name="check_bitwidth_tasklet",
        inputs={"_in_" + array_name for array_name in array_names},
        outputs={"_out_bitwidth_scalar", "_out_bitwidth_check_done"},
        code=tasklet_code,
        language=dace.dtypes.Language.CPP,
        code_global=runtime_array_check_global_code
    )
    """
    t = check_state.add_tasklet(
        name="check_bitwidth_tasklet",
        inputs={"_in_" + nproma_name},
        outputs={"_out_bitwidth_scalar", "_out_bitwidth_check_done"},
        code=f"""
        if (_in_{nproma_name} <= static_cast<int>(std::numeric_limits<uint16_t>::max())){{
            _out_bitwidth_scalar = 16;
        }} else {{
            _out_bitwidth_scalar = 32;
        }}
        _out_bitwidth_check_done = 1;
        #if defined(DACE_VELOCITY_DEBUG)
        printf("Bitwidth for {nproma_name}: %d bits\\n", _out_bitwidth_scalar);
        #endif
        """,
        language=dace.dtypes.Language.CPP,
        code_global=f"""
#include <limits>
#include <stdio.h>
        """,
    )

    c += 1
    # All connectors for the check. Input: all arrays we use, output: bitwidth_scalar
    #for arr_name in array_names:
    #    an = check_state.add_access(arr_name)
    #    check_state.add_edge(an, None, t, "_in_" + arr_name, dace.Memlet.from_array(arr_name, new_sdfg.arrays[arr_name]))
    an_nproma = check_state.add_access(nproma_name)
    check_state.add_edge(an_nproma, None, t, "_in_" + nproma_name, dace.Memlet.from_array(nproma_name, new_sdfg.arrays[nproma_name]))
    an = check_state.add_access("bitwidth_scalar")
    an2 = check_state.add_access("bitwidth_check_done")
    check_state.add_edge(t, "_out_bitwidth_scalar", an, None, dace.Memlet.from_array("bitwidth_scalar", new_sdfg.arrays["bitwidth_scalar"]))
    check_state.add_edge(t, "_out_bitwidth_check_done", an2, None, dace.Memlet.from_array("bitwidth_check_done", new_sdfg.arrays["bitwidth_check_done"]))

    # Add a CFG to copy all arrrays to the correct bitwidth
    """
        copy_bit = ConditionalBlock(label="copy_bit", sdfg=check_cfg.sdfg, parent=check_cfg)
        copy_cfg_i16 = ControlFlowRegion(label="copy_bit_cfg_i16", sdfg=copy_bit.sdfg, parent=copy_bit)
        copy_state_i16 = dace.SDFGState(label="copy_i16", sdfg=copy_bit.sdfg)

    """

    copy_bit = ConditionalBlock(label="copy_bit", sdfg=check_cfg.sdfg, parent=check_cfg)
    if enable_uint16:
        copy_cfg_i16 = ControlFlowRegion(label="copy_bit_cfg_i16", sdfg=copy_bit.sdfg, parent=copy_bit)
    copy_cfg_i32 = ControlFlowRegion(label="copy_bit_cfg_i32", sdfg=copy_bit.sdfg, parent=copy_bit)
    if enable_int64:
        copy_cfg_i64 = ControlFlowRegion(label="copy_bit_cfg_i64", sdfg=copy_bit.sdfg, parent=copy_bit)
    # Copy over only the needed body state
    if enable_uint16:
        copy_state_i16 = dace.SDFGState(label="copy_i16", sdfg=copy_bit.sdfg)
    copy_state_i32 = dace.SDFGState(label="copy_i32", sdfg=copy_bit.sdfg)
    if enable_int64:
        copy_state_i64 = dace.SDFGState(label="copy_i64", sdfg=copy_bit.sdfg)
    if enable_uint16:
        copy_cfg_i16.add_node(copy_state_i16, is_start_block=True)
    copy_cfg_i32.add_node(copy_state_i32, is_start_block=True)
    if enable_int64:
        copy_cfg_i64.add_node(copy_state_i64, is_start_block=True)
    if enable_uint16 and enable_int64:
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=copy_cfg_i16)
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32"), branch=copy_cfg_i32)
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=copy_cfg_i64)
    elif enable_uint16:
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=copy_cfg_i16)
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 64"), branch=copy_cfg_i32)
    elif enable_int64:
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 16"), branch=copy_cfg_i32)
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=copy_cfg_i64)
    else:
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym <= 64"), branch=copy_cfg_i32)
    check_cfg.add_node(copy_bit, is_start_block=False)
    check_cfg.add_edge(check_state, copy_bit, dace.InterstateEdge(assignments={"bitwidth_sym": "bitwidth_scalar"}))
    # First add the array names for all bitwidthness
    copy_list = [(copy_int32, dace.int32)]
    if enable_uint16:
        copy_list.append((copy_uint16, dace.uint16))
    if enable_int64:
        copy_list.append((copy_int64, dace.int16))
    """
    for _sdfg, _dtype in copy_list:
        for arr_name, arr in _sdfg.arrays.items():
            if arr_name not in new_sdfg.arrays:
                narr = copy.deepcopy(arr)
                narr.dtype = _dtype
                new_sdfg.add_datadesc(arr_name, narr, find_new_name=False)
    """
    # Add copy-in maps for all data
    ll = [(copy_state_i32, dace.dtypes.int32, "int32")]
    if enable_uint16:
        ll.append((copy_state_i16, dace.dtypes.uint16, "uint16"))
    if enable_int64:
        ll.append((copy_state_i64, dace.dtypes.int64, "int64"))
    for state, dst_dtype, suffix in ll:
        if suffix == "int32":
            continue
        for arr_name in array_names:
            assert new_sdfg.arrays[arr_name].storage == new_sdfg.arrays[f"{arr_name}_{suffix}"].storage
            _add_copy_map(state, src_arr_name=arr_name,
                          src_arr=new_sdfg.arrays[arr_name],
                          dst_arr_name=f"{arr_name}_{suffix}",
                          dst_arr=new_sdfg.arrays[f"{arr_name}_{suffix}"],
                          dtype=dst_dtype)
    if enable_uint16:
        copy_state_i16.validate()
    copy_state_i32.validate()
    if enable_int64:
        copy_state_i64.validate()

    # Always read the value from the scalar
    for oe in new_sdfg.out_edges(copy_in):
        copy_edata = copy.deepcopy(oe.data)
        copy_edata.assignments["bitwidth_check_done_sym"] = "bitwidth_check_done"
        new_sdfg.add_edge(copy_in, check_if, copy_edata)
        new_sdfg.remove_edge(oe)
    for ie in new_sdfg.in_edges(copy_out):
        copy_edata = copy.deepcopy(ie.data)
        copy_edata.assignments["bitwidth_check_done_sym"] = "bitwidth_check_done"
        new_sdfg.add_edge(check_if, copy_out, copy_edata)
        new_sdfg.remove_edge(ie)
    new_sdfg.remove_node(body)
    # new_sdfg.save("n1.sdfgz", compress=True)

    switch_bit = ConditionalBlock(label="switch_bit", sdfg=new_sdfg, parent=new_sdfg)
    if enable_uint16:
        switch_cfg_i16 = ControlFlowRegion(label="switch_bit_cfg_i16", sdfg=switch_bit.sdfg, parent=switch_bit)
    switch_cfg_i32 = ControlFlowRegion(label="switch_bit_cfg_i32", sdfg=switch_bit.sdfg, parent=switch_bit)
    if enable_int64:
        switch_cfg_i64 = ControlFlowRegion(label="switch_bit_cfg_i64", sdfg=switch_bit.sdfg, parent=switch_bit)
    # Copy over only the needed body state
    if enable_uint16:
        switch_state_i16 = copy_body_uint16 #dace.SDFGState(label="switch_i16", sdfg=switch_bit.sdfg)
    switch_state_i32 = copy_body_int32 #dace.SDFGState(label="switch_i32", sdfg=switch_bit.sdfg)
    if enable_int64:
        switch_state_i64 = copy_body_int64 #dace.SDFGState(label="switch_i64", sdfg=switch_bit.sdfg)
    # Copy over needed arrays
    if enable_uint16:
        switch_state_i16.validate()
    switch_state_i32.validate()
    if enable_int64:
        switch_state_i64.validate()

    if enable_uint16:
        switch_cfg_i16.add_node(switch_state_i16)
    switch_cfg_i32.add_node(switch_state_i32)
    if enable_int64:
        switch_cfg_i64.add_node(switch_state_i64)
    new_sdfg.add_node(switch_bit)
    if enable_uint16 and enable_int64:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=switch_cfg_i16)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32"), branch=switch_cfg_i32)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=switch_cfg_i64)
    elif enable_uint16:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=switch_cfg_i16)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 64"), branch=switch_cfg_i32)
    elif enable_int64:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 16"), branch=switch_cfg_i32)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=switch_cfg_i64)
    else:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym <= 64"), branch=switch_cfg_i32)
    for oe in new_sdfg.out_edges(check_if):
        copy_edata = copy.deepcopy(oe.data)
        copy_edata.assignments = {"bitwidth_sym": "bitwidth_scalar"}
        new_sdfg.add_edge(check_if, switch_bit, copy_edata)
    for ie in new_sdfg.in_edges(copy_out):
        copy_edata = copy.deepcopy(ie.data)
        new_sdfg.add_edge(switch_bit, copy_out, copy_edata)
        new_sdfg.remove_edge(ie)
    sdutil.set_nested_sdfg_parent_references(new_sdfg)
    if enable_uint16:
        switch_state_i16.validate()
    switch_state_i32.validate()
    if enable_int64:
        switch_state_i64.validate()

    #new_sdfg.save("decreased_bitwidth.sdfgz", compress=True)
    for state in new_sdfg.all_states():
        state.validate()

    """
    for state in new_sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                sdutil.set_nested_sdfg_parent_references(node.sdfg)
    """

    new_sdfg.append_init_code(f"__state->__0_bitwidth_check_done = 0;\n")
    new_sdfg.append_init_code(f"__state->__0_bitwidth_scalar = -1;\n")
    #new_sdfg.global_code["frame"] += CodeBlock(code="0")
    #new_sdfg.global_code["frame"] += CodeBlock(code="-1")  # Default to 64 bit
    #new_sdfg.save("n2.sdfgz", compress=True)
    new_sdfg.validate()

    def _check_data_desc(sdfg: dace.SDFG):
        for array_name, array in sdfg.arrays.items():
            if "uint16" in array_name:
                if array.dtype != dace.uint16:
                    array.dtype = dace.uint16
                assert array.dtype == dace.uint16, f"Array {array_name} has dtype {array.dtype}, expected uint16."
            elif "int32" in array_name:
                if array.dtype != dace.int32:
                    array.dtype = dace.int32
                assert array.dtype == dace.int32, f"Array {array_name} has dtype {array.dtype}, expected int32."
            elif "int64" in array_name:
                if array.dtype != dace.int64:
                    array.dtype = dace.int64
                assert array.dtype == dace.int64, f"Array {array_name} has dtype {array.dtype}, expected int64."
            else:
                assert array.dtype != dace.uint16, f"Array {array_name} has dtype {array.dtype}, expected not uint16."
                assert array.dtype != dace.int64, f"Array {array_name} has dtype {array.dtype}, expected not int64."
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    _check_data_desc(node.sdfg)
    _check_data_desc(new_sdfg)

    """
    def _update_connector_types(sdfg: dace.SDFG):
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    inner_sdfg = node.sdfg
                    for in_conn, in_type in list(node.in_connectors.items()):
                        needed_in_type = inner_sdfg.arrays[in_conn].dtype
                        if in_type != needed_in_type:
                            print(f"Updating in connector {in_conn} type from {in_type} to {needed_in_type}.")
                            node.remove_in_connector(in_conn)
                            o = node.add_in_connector(in_conn, dtype=needed_in_type, force=True)
                            print(node.in_connectors[in_conn], node.in_connectors[in_conn].type)
                            assert o
                            #node.in_connectors[in_conn] = needed_in_type
                    for out_conn, out_type in list(node.out_connectors.items()):
                        needed_out_type = inner_sdfg.arrays[out_conn].dtype
                        if out_type != needed_out_type:
                            print(f"Updating out connector {out_conn} type from {out_type} to {needed_out_type}.")
                            node.remove_out_connector(out_conn)
                            o = node.add_out_connector(out_conn, dtype=needed_out_type, force=True)
                            print(node.out_connectors[out_conn], node.out_connectors[out_conn].type)
                            assert o
                            #node.out_connectors[out_conn] = needed_out_type

                    _update_connector_types(node.sdfg)
    """
    #_update_connector_types(new_sdfg)

    c += 1

    return new_sdfg


def force_decrease_bitwidth_of_nblk_arrays(sdfg: dace.SDFG, multi_val_array_names: Set[str],
                                           single_val_array_names: Set[str]) -> dace.SDFG:
    new_multi_val_array_names = set()
    for array_name in multi_val_array_names:
        if array_name not in sdfg.arrays:
            print(f"Array {array_name} not found in SDFG, skipping.")
        else:
            new_multi_val_array_names.add(array_name)
    multi_val_array_names = new_multi_val_array_names
    new_single_val_array_names = set()
    for array_name in single_val_array_names:
        if array_name not in sdfg.arrays:
            print(f"Array {array_name} not found in SDFG, skipping.")
        else:
            new_single_val_array_names.add(array_name)
    single_val_array_names = new_single_val_array_names
    new_sdfg = copy.deepcopy(sdfg)
    sdutil.set_nested_sdfg_parent_references(new_sdfg)

    # Right now we have 4 top level nodes
    # copy-in
    top_level_nodes = list(new_sdfg.bfs_nodes(new_sdfg.start_block))
    assert len(top_level_nodes) == 4, f"Expected 4 top level nodes, got {len(top_level_nodes)}: {top_level_nodes}"

    copy_in, lower_index_arrays, body, copy_out = top_level_nodes[:4]
    # Will add a second lowering block, but in body all occurences of multi-val need to change
    # All single_val arrays need to be replaced with constants
    repl_dict = {array_name: array_name + "_uint8" for array_name in multi_val_array_names}
    _insert_lower_bidth_of_arrays_recursive(body, multi_val_array_names, "uint8", dace.uint8)
    _fix_nsdfg_connectors(new_sdfg)
    #body.replace_dict(repl_dict)
    #_repl_on_interstate_edges(body, repl_dict)
    # Add the new arrays (array names have changed)
    #for array_name in multi_val_array_names:
    #    newdesc = copy.deepcopy(new_sdfg.arrays[array_name])
    #    newdesc.dtype = dace.uint16
    #    newdesc.lifetime = dace.AllocationLifetime.Persistent
    #    new_sdfg.add_datadesc(
    #        f"{array_name}_uint16",
    #        newdesc,
    #        find_new_name=False
    #    )
    #    # Update new one for correct dtype and lifetime
    #    #new_sdfg.arrays[array_name + "_uint16"].dtype = dace.uint16
    #    #new_sdfg.arrays[array_name + "_uint16"].lifetime = dace.AllocationLifetime.Persistent
    new_sdfg.validate()

    # Do something similar for single_val_arrays, due to initial copy-in and copy-out can't remove
    # the arrays, but can replace all occurences with the symbolized version, remove usage of arrays within does nodes
    # =============================
    """
    # Instead of a constant with value 1, just write 1
    for array_name in single_val_array_names:
        new_sdfg.add_symbol(
            name=f"{array_name}_constsym",
            stype=dace.int32,
            find_new_name=False,
        )
        new_sdfg.add_constant(
            name=f"{array_name}_constsym",
            value=1,
        )
        for node, graph in body.all_nodes_recursive():
            if isinstance(node, dace.nodes.NestedSDFG):
                node.sdfg.add_symbol(
                    name=f"{array_name}_constsym",
                    stype=dace.int32,
                    find_new_name=False,
                )
                if graph.parent_graph is not None:
                    node.symbol_mapping[f"{array_name}_constsym"] = f"{array_name}_constsym"
    """
    """
    for node, graph in body.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG) and graph.parent_graph is not None:
            try:
                node.sdfg.validate()
            except Exception as e:
                print(f"Validation failed for nested SDFG {node.sdfg.name}: {e}")
                node.sdfg.save(f"inv.sdfgz", compress=True)
                raise Exception(e)
    new_sdfg.validate()
    """

    for array_name in single_val_array_names:
        for edge, graph in body.all_edges_recursive():
            if isinstance(edge.data, dace.InterstateEdge):
                pass
            elif isinstance(edge.data, dace.Memlet):
                if edge.data.data == array_name:
                    graph.remove_edge(edge)
                    edge.src.remove_out_connector(edge.src_conn)
                    edge.dst.remove_in_connector(edge.dst_conn)
        for node, graph in body.all_nodes_recursive():
            if isinstance(node, dace.nodes.AccessNode):
                if node.data == array_name:
                    graph.remove_node(node)
            if isinstance(node, dace.nodes.NestedSDFG) and graph.parent_graph is not None:
                if array_name in node.sdfg.arrays and node.sdfg.arrays[array_name].transient is False:
                    node.sdfg.remove_data(array_name, False)

    # Now go through all interstate edges if we see a const array
    # of form <array_name>[...] then replace it with <array_name>_constsym

    for array_name in single_val_array_names:
        for edge, graph in body.all_edges_recursive():
            if isinstance(edge.data, dace.InterstateEdge):
                if array_name in edge.data.assignments:
                    val = edge.data.assignments[array_name]
                    if isinstance(val, str):
                        valstr = val
                    elif isinstance(val, CodeBlock):
                        valstr = val.as_string
                    else:
                        raise ValueError(f"Unexpected value {val} for assignment {array_name} in edge {edge}.")
                    valstr = replace_array_with_constsym(valstr, array_name)
                    edge.data.assignments[array_name] = valstr if isinstance(val, str) else CodeBlock(code=valstr)
                for key, val in edge.data.assignments.items():
                    valstr = val if isinstance(val, str) else val.as_string
                    if array_name in valstr:
                        valstr = replace_array_with_constsym(valstr, array_name)
                        edge.data.assignments[key] = valstr if isinstance(val, str) else CodeBlock(code=valstr)

    def reinsert_symbols_to_nsdfg_rec(graph: dace.SDFG):
        # Why would this happen? This is a workaround for the issue where nested SDFGs do not have their symbols properly assigned.
        for state in graph.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    child_sdfg = node.sdfg
                    connectors = node.in_connectors.keys() | node.out_connectors.keys()
                    symbols = sdfg.free_symbols
                    #if symbol_mapping is None:
                    #    symbol_mapping = {s: s for s in symbols}
                    #    node.symbol_mapping = symbol_mapping

                    # Validate missing symbols
                    missing_symbols = [s for s in symbols if s not in node.symbol_mapping]
                    if missing_symbols:
                        # If symbols are missing, try to get them from the parent SDFG
                        assert isinstance(state, dace.SDFGState), "State should be an SDFGState."
                        parent_mapping = {s: s for s in missing_symbols if s in state.symbols_defined_at(node)}
                        node.symbol_mapping.update(parent_mapping)
                        missing_symbols = [s for s in symbols if s not in node.symbol_mapping]
                    #if missing_symbols:
                    #    raise ValueError('Missing symbols on nested SDFG "%s": %s' % (node.sdfg.name, missing_symbols))
                    if missing_symbols:
                        for missing_symbol in missing_symbols:
                            #child_sdfg.add_symbol(missing_symbol, node.sdfg.symbols[missing_symbol] if missing_symbol in node.sdfg.symbols else dace.int32)
                            #node.symbol_mapping[missing_symbol] = missing_symbol
                            #print("Symbols", symbols)
                            #print("Missing symbols", missing_symbols)
                            child_sdfg.remove_symbol(missing_symbol, force=True)
                            #node.symbol_mapping[missing_symbol] = missing_symbol
                            #node.sdfg.add_symbol(missing_symbol, dace.int32)  # Default to int32, can be changed later
    reinsert_symbols_to_nsdfg_rec(new_sdfg)

    new_sdfg.save("a.sdfgz", compress=True)
    for node, graph in body.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG) and graph.parent_graph is not None:
            try:
                node.sdfg.validate()
            except Exception as e:
                print(f"Validation failed for nested SDFG {node.sdfg.name}: {e}")
                node.sdfg.save(f"inv.sdfgz", compress=True)
                raise Exception(e)
    new_sdfg.validate()

    #raise Exception("This is a hacky solution, please fix it later.")

    # ===============================

    nblks_c = "p_patch->nblks_c"
    nblks_v = "p_patch->nblks_v"
    nblks_e = "p_patch->nblks_e"
    first_block = new_sdfg.start_block
    assert isinstance(first_block, dace.SDFGState)
    first_state = first_block

    t = first_state.add_tasklet(
        name="assert_nblks",
        inputs=set(),
        outputs=set(),
        code="""
        if (p_patch->nblks_c != 1){
            throw std::runtime_error("Expected exactly 1 for nblk_c, got " + std::to_string(p_patch->nblks_c));
        }
        if (p_patch->nblks_v != 1){
            throw std::runtime_error("Expected exactly 1 for nblk_v, got " + std::to_string(p_patch->nblks_v));
        }
        if (p_patch->nblks_e != 2){
            throw std::runtime_error("Expected exactly 2 for nblk_e, got " + std::to_string(p_patch->nblks_e));
        }
""",
        language=dace.dtypes.Language.CPP,
        code_global="""
#include <stdexcept>
#include <string>
""",
        side_effects=True
    )
    an = first_state.add_access("p_patch")
    first_state.add_edge(an, None, t, None, dace.Memlet(None))
    first_state.validate()

    # Single val arrays are always 1

    # Multi val arrays are always 1 or 2, we need to copy them over
    new_sdfg.add_scalar("nblk_lowering_done", dtype=dace.int32,
                        storage=dace.StorageType.CPU_Heap,
                        lifetime=dace.AllocationLifetime.Persistent,
                        transient=True)
    new_sdfg.add_symbol("nblk_lowering_done_sym", dace.int32)
    new_sdfg.append_init_code(f"__state->__0_nblk_lowering_done = 0;\n")

    lower_blk_bits_if = ConditionalBlock(label="lower_blk_cond", sdfg=new_sdfg, parent=new_sdfg)
    lower_blk_bits_cfg = ControlFlowRegion(label="lower_blk_cfg", sdfg=lower_blk_bits_if.sdfg, parent=lower_blk_bits_if)
    lower_blk_bits_state = dace.SDFGState(label="lower_blk", sdfg=lower_blk_bits_cfg.sdfg)
    lower_blk_bits_cfg.add_node(lower_blk_bits_state, is_start_block=True)
    lower_blk_bits_if.add_branch(condition=CodeBlock(code="nblk_lowering_done_sym == 0"), branch=lower_blk_bits_cfg)

    new_sdfg.add_node(lower_blk_bits_if, is_start_block=False)
    oes = new_sdfg.out_edges(first_state)
    for oe in new_sdfg.out_edges(first_state):
        oe_data = copy.deepcopy(oe.data)
        oe_data.assignments["nblk_lowering_done_sym"] = "nblk_lowering_done"
        new_sdfg.add_edge(first_state, lower_blk_bits_if, oe_data)
        new_sdfg.add_edge(lower_blk_bits_if, oe.dst, InterstateEdge())
    for oe in oes:
        new_sdfg.remove_edge(oe)

    #sdfg.save("b.sdfgz", compress=True)


    for array_name in multi_val_array_names:
        _add_copy_map(
            lower_blk_bits_state,
            src_arr_name=array_name,
            src_arr=new_sdfg.arrays[array_name],
            dst_arr_name=f"{array_name}_uint8",
            dst_arr=new_sdfg.arrays[array_name + "_uint8"],
            dtype=dace.dtypes.uint8
        )

    # Write one to check done
    t2 = lower_blk_bits_state.add_tasklet(
        name="set_nblk_lowering_done",
        inputs=set(),
        outputs={"_out_nblk_lowering_done"},
        code="_out_nblk_lowering_done = 1;",
        language=dace.dtypes.Language.CPP,
        code_global="",
        side_effects=True
    )
    an = lower_blk_bits_state.add_access("nblk_lowering_done")
    lower_blk_bits_state.add_edge(t2, "_out_nblk_lowering_done", an, None, dace.Memlet.from_array("nblk_lowering_done", new_sdfg.arrays["nblk_lowering_done"]))

    an_counter = {array_name: 0 for array_name in single_val_array_names}
    for node, graph in new_sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode):
            if node.data in single_val_array_names:
                an_counter[node.data] += 1
    #print(an_counter)
    #raise Exception(an_counter)
    return new_sdfg


def replace_array_with_constsym(text: str, array_name: str) -> str:
    """
    Replace array_name[...] with array_name_constsym, properly counting brackets.

    Args:
        text: The string to process
        array_name: The array name to replace

    Returns:
        Modified string with replacements
    """
    result = []
    i = 0

    while i < len(text):
        # Look for array_name followed by '['
        if text[i:i+len(array_name)] == array_name and i + len(array_name) < len(text) and text[i + len(array_name)] == '[':
            # Found array_name[, now find the matching closing bracket
            start_pos = i
            bracket_pos = i + len(array_name)  # Position of the opening '['
            bracket_count = 1
            j = bracket_pos + 1

            # Count brackets to find the matching closing bracket
            while j < len(text) and bracket_count > 0:
                if text[j] == '[':
                    bracket_count += 1
                elif text[j] == ']':
                    bracket_count -= 1
                j += 1

            if bracket_count == 0:
                # Found matching closing bracket, replace the entire expression
                result.append(f"1")
                i = j  # Skip past the closing bracket
            else:
                # No matching closing bracket found, just append the character
                result.append(text[i])
                i += 1
        else:
            result.append(text[i])
            i += 1

    return ''.join(result)

"""
sdfg: dace.SDFG, array_names: Set[str], enable_uint16: bool = True,
                                      enable_int64: bool = False, nproma_name: str = None, assume_can_lower: bool = False
"""
def decrease_bitwidth_of_const_arrays_no_branching(
    sdfg: dace.SDFG,
    array_names: Set[str],
    nproma_name: str,
):
       
    _fix_nsdfg_connectors(sdfg)
    sdfg.validate()
    global c
    # Not all arrays might be in use, filter the set again
    new_array_names = set()
    for name in array_names:
        if name in sdfg.arrays:
            # Filter for dtype = int64 or = int32
            if sdfg.arrays[name].dtype == dace.int64 or sdfg.arrays[name].dtype == dace.int32:
                new_array_names.add(name)

    array_names = new_array_names

    # 1. Ensure all arrays are constant arrays
    # If they are transient initializating them once is OK
    arrays_with_num_writes = {name: 0 for name in array_names}
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode) and node.data in array_names:
            if graph.in_degree(node) > 0 and any(ie.data is not None for ie in graph.in_edges(node)):
                arrays_with_num_writes[node.data] += 1

    assert all(arrays_with_num_writes[name] <= 1 for name in array_names), \
        "All arrays must be constant arrays, i.e. written to at most once."

    # Duplicate NSDFG regions - one with original names and then replace the accesses with fp16 or fp32
    copy_uint16 = copy.deepcopy(sdfg)
    sdutil.set_nested_sdfg_parent_references(copy_uint16)

    sdfgs_and_suffixes = [(copy_uint16, "uint16", dace.dtypes.uint16),]
    copy_body_uint16 = list(copy_uint16.bfs_nodes(copy_uint16.start_block))[1]

    # Replace all arrays with the corresponding bitwidth suffix
    for copy_sdfg, suffix, dtype in sdfgs_and_suffixes:
        _lower_bidth_of_arrays_recursive(copy_sdfg, array_names, suffix, dtype)
        copy_sdfg.validate()

    # Up this point it is velocity tendencies specific.
    # We would need to find the point where all arrays have been defined
    new_sdfg = copy.deepcopy(sdfg)
    sdutil.set_nested_sdfg_parent_references(new_sdfg)
    assert len(new_sdfg.nodes()) == 3 and len(list(new_sdfg.all_states())) == 3, f"Expected 3 nodes, got {len(new_sdfg.nodes())} and {len(list(new_sdfg.all_states()))} states got : {new_sdfg.nodes()}, {new_sdfg.all_states()}."
    copy_in, body, copy_out = list(new_sdfg.bfs_nodes(new_sdfg.start_block))[:3]
    #all_edges = new_sdfg.out_edges(copy_in) + new_sdfg.in_edges(copy_out)
    assert len(new_sdfg.out_edges(copy_in)) + len(new_sdfg.in_edges(copy_out)) == 2, f"{new_sdfg.out_edges(copy_in)},{new_sdfg.in_edges(copy_out)}"
    #new_edge_data = all_edges[0].data.assignments + all_edges[1].data.assignments
    #new_sdfg.add_edge(src=copy_in, dst=copy_out, data=InterstateEdge(assignments=new_edge_data))
    #check_state = new_sdfg.add_state_after(new_sdfg.start_state, "check_bitwidth")

    # Add int16, int32 suffixed version of arrays to the SDFG
    suffix_and_dtypes = [("uint16", dace.dtypes.uint16),]

    def add_datadesc_rec(sdfg: dace.SDFG, suffix_and_dtypes):
        for suffix, dtype in suffix_and_dtypes:
            if suffix == "int32":
                continue
            for name in array_names:
                new_name = f"{name}_{suffix}"
                if new_name not in new_sdfg.arrays:
                    copy_desc = copy.deepcopy(new_sdfg.arrays[name])
                    copy_desc.dtype = dtype
                    copy_desc.lifetime = dace.AllocationLifetime.Persistent
                    print(f"Adding array {new_name} with dtype {copy_desc.dtype} to SDFG.")
                    new_sdfg.add_datadesc(new_name, copy_desc, find_new_name=False)
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    # Add the new arrays to the nested SDFG
                    add_datadesc_rec(node.sdfg, suffix_and_dtypes)
    add_datadesc_rec(sdfg, suffix_and_dtypes)

    c += 1


    copy_state_i16 = dace.SDFGState(label="copy_i16", sdfg=new_sdfg)
    new_sdfg.add_state(copy_state_i16, is_start_block=True)

    """
    ll = [(copy_state_u16, dace.dtypes.uint16, "uint16")]
    if enable_uint16:
        ll.append((copy_state_i16, dace.dtypes.uint16, "uint16"))
    if enable_int64:
        ll.append((copy_state_i64, dace.dtypes.int64, "int64"))
    for state, dst_dtype, suffix in ll:
        if suffix == "int32":
            continue
        for arr_name in array_names:
            assert new_sdfg.arrays[arr_name].storage == new_sdfg.arrays[f"{arr_name}_{suffix}"].storage
            _add_copy_map(state, src_arr_name=arr_name,
                          src_arr=new_sdfg.arrays[arr_name],
                          dst_arr_name=f"{arr_name}_{suffix}",
                          dst_arr=new_sdfg.arrays[f"{arr_name}_{suffix}"],
                          dtype=dst_dtype)
    if enable_uint16:
        copy_state_i16.validate()
    copy_state_i32.validate()
    if enable_int64:
        copy_state_i64.validate()

    # Always read the value from the scalar
    for oe in new_sdfg.out_edges(copy_in):
        copy_edata = copy.deepcopy(oe.data)
        copy_edata.assignments["bitwidth_check_done_sym"] = "bitwidth_check_done"
        new_sdfg.add_edge(copy_in, check_if, copy_edata)
        new_sdfg.remove_edge(oe)
    for ie in new_sdfg.in_edges(copy_out):
        copy_edata = copy.deepcopy(ie.data)
        copy_edata.assignments["bitwidth_check_done_sym"] = "bitwidth_check_done"
        new_sdfg.add_edge(check_if, copy_out, copy_edata)
        new_sdfg.remove_edge(ie)
    new_sdfg.remove_node(body)
    # new_sdfg.save("n1.sdfgz", compress=True)

    switch_bit = ConditionalBlock(label="switch_bit", sdfg=new_sdfg, parent=new_sdfg)
    if enable_uint16:
        switch_cfg_i16 = ControlFlowRegion(label="switch_bit_cfg_i16", sdfg=switch_bit.sdfg, parent=switch_bit)
    switch_cfg_i32 = ControlFlowRegion(label="switch_bit_cfg_i32", sdfg=switch_bit.sdfg, parent=switch_bit)
    if enable_int64:
        switch_cfg_i64 = ControlFlowRegion(label="switch_bit_cfg_i64", sdfg=switch_bit.sdfg, parent=switch_bit)
    # Copy over only the needed body state
    if enable_uint16:
        switch_state_i16 = copy_body_uint16 #dace.SDFGState(label="switch_i16", sdfg=switch_bit.sdfg)
    switch_state_i32 = copy_body_int32 #dace.SDFGState(label="switch_i32", sdfg=switch_bit.sdfg)
    if enable_int64:
        switch_state_i64 = copy_body_int64 #dace.SDFGState(label="switch_i64", sdfg=switch_bit.sdfg)
    # Copy over needed arrays
    if enable_uint16:
        switch_state_i16.validate()
    switch_state_i32.validate()
    if enable_int64:
        switch_state_i64.validate()

    if enable_uint16:
        switch_cfg_i16.add_node(switch_state_i16)
    switch_cfg_i32.add_node(switch_state_i32)
    if enable_int64:
        switch_cfg_i64.add_node(switch_state_i64)
    new_sdfg.add_node(switch_bit)
    if enable_uint16 and enable_int64:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=switch_cfg_i16)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32"), branch=switch_cfg_i32)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=switch_cfg_i64)
    elif enable_uint16:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=switch_cfg_i16)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 64"), branch=switch_cfg_i32)
    elif enable_int64:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 16"), branch=switch_cfg_i32)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=switch_cfg_i64)
    else:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym <= 64"), branch=switch_cfg_i32)
    for oe in new_sdfg.out_edges(check_if):
        copy_edata = copy.deepcopy(oe.data)
        copy_edata.assignments = {"bitwidth_sym": "bitwidth_scalar"}
        new_sdfg.add_edge(check_if, switch_bit, copy_edata)
    for ie in new_sdfg.in_edges(copy_out):
        copy_edata = copy.deepcopy(ie.data)
        new_sdfg.add_edge(switch_bit, copy_out, copy_edata)
        new_sdfg.remove_edge(ie)
    sdutil.set_nested_sdfg_parent_references(new_sdfg)
    if enable_uint16:
        switch_state_i16.validate()
    switch_state_i32.validate()
    if enable_int64:
        switch_state_i64.validate()

    #new_sdfg.save("decreased_bitwidth.sdfgz", compress=True)
    for state in new_sdfg.all_states():
        state.validate()

    """
    for state in new_sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                sdutil.set_nested_sdfg_parent_references(node.sdfg)
    """

    new_sdfg.append_init_code(f"__state->__0_bitwidth_check_done = 0;\n")
    new_sdfg.append_init_code(f"__state->__0_bitwidth_scalar = -1;\n")
    #new_sdfg.global_code["frame"] += CodeBlock(code="0")
    #new_sdfg.global_code["frame"] += CodeBlock(code="-1")  # Default to 64 bit
    #new_sdfg.save("n2.sdfgz", compress=True)
    new_sdfg.validate()

    def _check_data_desc(sdfg: dace.SDFG):
        for array_name, array in sdfg.arrays.items():
            if "uint16" in array_name:
                if array.dtype != dace.uint16:
                    array.dtype = dace.uint16
                assert array.dtype == dace.uint16, f"Array {array_name} has dtype {array.dtype}, expected uint16."
            elif "int32" in array_name:
                if array.dtype != dace.int32:
                    array.dtype = dace.int32
                assert array.dtype == dace.int32, f"Array {array_name} has dtype {array.dtype}, expected int32."
            elif "int64" in array_name:
                if array.dtype != dace.int64:
                    array.dtype = dace.int64
                assert array.dtype == dace.int64, f"Array {array_name} has dtype {array.dtype}, expected int64."
            else:
                assert array.dtype != dace.uint16, f"Array {array_name} has dtype {array.dtype}, expected not uint16."
                assert array.dtype != dace.int64, f"Array {array_name} has dtype {array.dtype}, expected not int64."
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    _check_data_desc(node.sdfg)
    _check_data_desc(new_sdfg)

    """
    def _update_connector_types(sdfg: dace.SDFG):
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    inner_sdfg = node.sdfg
                    for in_conn, in_type in list(node.in_connectors.items()):
                        needed_in_type = inner_sdfg.arrays[in_conn].dtype
                        if in_type != needed_in_type:
                            print(f"Updating in connector {in_conn} type from {in_type} to {needed_in_type}.")
                            node.remove_in_connector(in_conn)
                            o = node.add_in_connector(in_conn, dtype=needed_in_type, force=True)
                            print(node.in_connectors[in_conn], node.in_connectors[in_conn].type)
                            assert o
                            #node.in_connectors[in_conn] = needed_in_type
                    for out_conn, out_type in list(node.out_connectors.items()):
                        needed_out_type = inner_sdfg.arrays[out_conn].dtype
                        if out_type != needed_out_type:
                            print(f"Updating out connector {out_conn} type from {out_type} to {needed_out_type}.")
                            node.remove_out_connector(out_conn)
                            o = node.add_out_connector(out_conn, dtype=needed_out_type, force=True)
                            print(node.out_connectors[out_conn], node.out_connectors[out_conn].type)
                            assert o
                            #node.out_connectors[out_conn] = needed_out_type

                    _update_connector_types(node.sdfg)
    """
    #_update_connector_types(new_sdfg)

    c += 1
    """
    return new_sdfg
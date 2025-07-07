import dace
import copy
from typing import Set
from dace.properties import CodeBlock
from dace.codegen.control_flow import ConditionalBlock, ContinueBlock, ControlFlowBlock, ControlFlowRegion
import dace.sdfg.utils as sdutil

c = 0
def _add_copy_map(state: dace.SDFGState, src_arr_name:str, src_arr:dace.data.Data, dst_arr_name:str, dst_arr:dace.data.Data,
                  ):
    """
    Add a copy map to the given state in the SDFG.
    """
    assert src_arr.shape == dst_arr.shape, "Source and destination arrays must have the same shape."
    # Create a new map node
    map_ranges = dict()
    for dim, size in enumerate(src_arr.shape):
        map_ranges[f"i{dim}"] = f"0:{size}"

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
    map_entry.add_in_connector(f"IN_{src_arr_name}")
    map_entry.add_out_connector(f"OUT_{src_arr_name}")
    map_exit.add_in_connector(f"IN_{dst_arr_name}")
    map_exit.add_out_connector(f"OUT_{dst_arr_name}")

    # Add a tasklet that perfmorms the type cast
    tasklet = state.add_tasklet(
        name=f"copy_{src_arr_name}_to_{dst_arr_name}",
        inputs={"in"},
        outputs={"out"},
        code=f"out = static_cast<{dst_arr.dtype.ctype}>(in);",
        language=dace.Language.CPP)

    access_str = f", ".join([str(s) for s in map_ranges.keys()])
    state.add_edge(map_entry, f"OUT_{src_arr_name}", tasklet, "in", dace.Memlet(expr=f"{src_arr_name}[{access_str}]"))
    state.add_edge(tasklet, "out", map_exit, f"IN_{dst_arr_name}", dace.Memlet(expr=f"{dst_arr_name}[{access_str}]"))

def _lower_bidth_of_arrays_recursive(sdfg: dace.SDFG, array_names: Set[str], suffix: str, new_dtype: dace.dtypes.typeclass,
                                     ):
    repl_dict = {array_name: array_name + "_" + suffix for array_name in array_names}
    # Repl datadesc names
    for name in array_names:
        if name in sdfg.arrays:
            new_name = f"{name}_{suffix}"
            copy_desc = copy.deepcopy(sdfg.arrays[name])
            copy_desc.dtype = new_dtype
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

def decrease_bitwidth_of_const_arrays(sdfg: dace.SDFG, array_names: Set[str], enable_int16: bool = True,
                                      enable_int64: bool = False,):
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
    if enable_int16:
        copy_int16 = copy.deepcopy(sdfg)
        sdutil.set_nested_sdfg_parent_references(copy_int16)

    sdfgs_and_suffixes = [
                        (copy_int32, "int32", dace.dtypes.int32)]
    if enable_int16:
        sdfgs_and_suffixes.append((copy_int16, "int16", dace.dtypes.int16))
    if enable_int64:
        sdfgs_and_suffixes.append((copy_int64, "int64", dace.dtypes.int64))
    if enable_int64:
        copy_body_int64 = list(copy_int64.bfs_nodes(copy_int64.start_block))[1]
    copy_body_int32 = list(copy_int32.bfs_nodes(copy_int32.start_block))[1]
    if enable_int16:
        copy_body_int16 = list(copy_int16.bfs_nodes(copy_int16.start_block))[1]

    # Replace all arrays with the corresponding bitwidth suffix
    for copy_sdfg, suffix, dtype in sdfgs_and_suffixes:
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
    check_if.add_branch(condition=CodeBlock(code="bitwidth_check_done_sym == 1"), branch=check_cfg)

    # The check pattern to fill is the following:
    """
    #ifndef NDEBUG
    int32_t check_bounds_on_device(const int64_t* h_input, const int64_t* h_output, int64_t size, const std::string& array_name);
    #else
    int32_t check_bounds_on_device(const int64_t* h_input, const int64_t* h_output, int64_t size);
    #endif
    """

    """
    for (arr_name, arr) in sdfg.arrays.items(){
        if (bitwidth_scalar != 64){
            #ifndef NDEBUG
            bitwidth_scalar = check_bounds_on_device(<array.name>, <array.shape>, "<array.name>");
            #else
            bitwidth_scalar = check_bounds_on_device(<array.name>, <array.shape>);
            #endif
        }
    }
    """
    tasklet_code = " int32_t _internal_bitwidth_scalar = -1;\n"
    for arr_name in array_names:
        arr = new_sdfg.arrays[arr_name]
        arr.total_size
        tasklet_code += f"""
        if (_internal_bitwidth_scalar != 64){{
            #ifndef NDEBUG
            _internal_bitwidth_scalar = check_bounds_on_device({arr_name}, {arr.total_size} * sizeof({arr.dtype.ctype}), "{arr_name}");
            #else
            _internal_bitwidth_scalar = check_bounds_on_device({arr_name}, {arr.total_size} * sizeof({arr.dtype.ctype}));
            #endif
        }}

"""
    tasklet_code += "_out_bitwidth_check_done = 1;\n _out_bitwidth_scalar = _internal_bitwidth_scalar;\n"
    t = check_state.add_tasklet(
        name="check_bitwidth_tasklet",
        inputs={"_in_" + array_name for array_name in array_names},
        outputs={"_out_bitwidth_scalar", "_out_bitwidth_check_done"},
        code=tasklet_code,
        language=dace.dtypes.Language.CPP,
        code_global=f"""
#include <cuda_runtime.h>
#include <stdint.h>
#include <stdio.h>
#include <stdexcept>

__device__ __inline__ int32_t check_bounds(int32_t val) {{
    if (val >= INT16_MIN && val <= INT16_MAX) {{
        return 16;
    }} else if (val >= INT32_MIN && val <= INT32_MAX) {{
        return 32;
    }} else {{
        return 64;
    }}
}}

__global__ void check_bounds_kernel(const int32_t* __restrict__ input, int32_t size, int32_t* __restrict__ result) {{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= size) return;

    int32_t required_bits = check_bounds(input[idx]);
    if (required_bits == 16){{
        result[0] = 1;
    }} else if (required_bits == 32){{
        result[1] = 1;
    }} else if (required_bits == 64){{
        result[2] = 1;
    }}
}}

#ifndef NDEBUG
int32_t check_bounds_on_device_{c}(const int32_t* h_input, int32_t size, const std::string& array_name) {{
    int32_t* d_input;
    int32_t* d_result;
    int32_t h_result[3] = {{0, 0, 0}}; // Initialize results for 16, 32, and 64 bits
    int32_t threads = 256;
    int32_t blocks = (size + threads - 1) / threads;

    cudaMalloc((void**)&d_result, sizeof(int32_t) * 3);
    check_bounds_kernel<<<blocks, threads>>>(d_input, size, d_result);
    cudaMemcpy(h_result, d_result, sizeof(int32_t) * 3, cudaMemcpyDeviceToHost);

    int32_t num_bits = 16;
    if (h_result[2] == 1) {{
        num_bits = 64;
    }} else if (h_result[1] == 1) {{
        num_bits = 32;
    }} else if (h_result[0] == 1) {{
        num_bits = 16;
    }} else {{
        num_bits = -1;
        throw std::runtime_error("No valid bounds found for " + array_name + " the input values.");
    }}


    printf("(DEBUG) Input size: %lld, Required bits: %d\\n", size, num_bits);

    cudaFree(d_result);

    return num_bits;
}}
#else
int32_t check_bounds_on_device_{c}(const int32_t* h_input, int32_t size) {{
    int32_t* d_input;
    int32_t* d_result;
    int32_t h_result[3] = {{0, 0, 0}}; // Initialize results for 16, 32, and 64 bits
    int32_t threads = 256;
    int32_t blocks = (size + threads - 1) / threads;

    cudaMalloc((void**)&d_result, sizeof(int32_t) * 3);
    check_bounds_kernel<<<blocks, threads>>>(d_input, size, d_result);
    cudaMemcpy(h_result, d_result, sizeof(int32_t) * 3, cudaMemcpyDeviceToHost);

    int32_t num_bits = 16;
    if (h_result[2] == 1) {{
        num_bits = 64;
    }} else if (h_result[1] == 1) {{
        num_bits = 32;
    }} else if (h_result[0] == 1) {{
        num_bits = 16;
    }} else {{
        num_bits = -1;
        throw std::runtime_error("No valid bounds found for the input values.");
    }}


    printf("DEBUG Input size: %lld, Required bits: %d\n", size, num_bits);

    cudaFree(d_result);

    return num_bits;
}}
#endif
"""
    )
    c += 1
    # All connectors for the check. Input: all arrays we use, output: bitwidth_scalar
    for arr_name in array_names:
        an = check_state.add_access(arr_name)
        check_state.add_edge(an, None, t, "_in_" + arr_name, dace.Memlet.from_array(arr_name, new_sdfg.arrays[arr_name]))
    an = check_state.add_access("bitwidth_scalar")
    an2 = check_state.add_access("bitwidth_check_done")
    check_state.add_edge(t, "_out_bitwidth_scalar", an, None, dace.Memlet.from_array("bitwidth_scalar", new_sdfg.arrays["bitwidth_scalar"]))
    check_state.add_edge(t, "_out_bitwidth_check_done", an2, None, dace.Memlet.from_array("bitwidth_check_done", new_sdfg.arrays["bitwidth_check_done"]))

    # Add a CFG to copy all arrrays to the correct bitwidth
    copy_bit = ConditionalBlock(label="copy_bit", sdfg=check_cfg.sdfg, parent=check_cfg)
    if enable_int16:
        copy_cfg_i16 = ControlFlowRegion(label="copy_bit_cfg_i16", sdfg=copy_bit.sdfg, parent=copy_bit)
    copy_cfg_i32 = ControlFlowRegion(label="copy_bit_cfg_i32", sdfg=copy_bit.sdfg, parent=copy_bit)
    if enable_int64:
        copy_cfg_i64 = ControlFlowRegion(label="copy_bit_cfg_i64", sdfg=copy_bit.sdfg, parent=copy_bit)
    # Copy over only the needed body state
    if enable_int16:
        copy_state_i16 = dace.SDFGState(label="copy_i16", sdfg=copy_bit.sdfg)
    copy_state_i32 = dace.SDFGState(label="copy_i32", sdfg=copy_bit.sdfg)
    if enable_int64:
        copy_state_i64 = dace.SDFGState(label="copy_i64", sdfg=copy_bit.sdfg)
    if enable_int16:
        copy_cfg_i16.add_node(copy_state_i16, is_start_block=True)
    copy_cfg_i32.add_node(copy_state_i32, is_start_block=True)
    if enable_int64:
        copy_cfg_i64.add_node(copy_state_i64, is_start_block=True)
    if enable_int16 and enable_int64:
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=copy_cfg_i16)
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32"), branch=copy_cfg_i32)
        copy_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=copy_cfg_i64)
    elif enable_int16:
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
    copy_list = [copy_int32]
    if enable_int16:
        copy_list.append(copy_int16)
    if enable_int64:
        copy_list.append(copy_int64)
    for _sdfg in copy_list:
        for arr_name, arr in _sdfg.arrays.items():
            if arr_name not in new_sdfg.arrays:
                new_sdfg.add_datadesc(arr_name, copy.deepcopy(arr), find_new_name=False)

    # Add copy-in maps for all data
    ll = [(copy_state_i32, dace.dtypes.int32, "int32")]
    if enable_int16:
        ll.append((copy_state_i16, dace.dtypes.int16, "int16"))
    if enable_int64:
        ll.append((copy_state_i64, dace.dtypes.int64, "int64"))
    for state, dst_dtype, suffix in ll:
        for arr_name in array_names:
            assert new_sdfg.arrays[arr_name].storage == new_sdfg.arrays[f"{arr_name}_{suffix}"].storage
            _add_copy_map(state, src_arr_name=arr_name,
                          src_arr=new_sdfg.arrays[arr_name],
                          dst_arr_name=f"{arr_name}_{suffix}",
                          dst_arr=new_sdfg.arrays[f"{arr_name}_{suffix}"])
    if enable_int16:
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
    #new_sdfg.save("n1.sdfgz", compress=True)

    switch_bit = ConditionalBlock(label="switch_bit", sdfg=new_sdfg, parent=new_sdfg)
    if enable_int16:
        switch_cfg_i16 = ControlFlowRegion(label="switch_bit_cfg_i16", sdfg=switch_bit.sdfg, parent=switch_bit)
    switch_cfg_i32 = ControlFlowRegion(label="switch_bit_cfg_i32", sdfg=switch_bit.sdfg, parent=switch_bit)
    if enable_int64:
        switch_cfg_i64 = ControlFlowRegion(label="switch_bit_cfg_i64", sdfg=switch_bit.sdfg, parent=switch_bit)
    # Copy over only the needed body state
    if enable_int16:
        switch_state_i16 = copy_body_int16 #dace.SDFGState(label="switch_i16", sdfg=switch_bit.sdfg)
    switch_state_i32 = copy_body_int32 #dace.SDFGState(label="switch_i32", sdfg=switch_bit.sdfg)
    if enable_int64:
        switch_state_i64 = copy_body_int64 #dace.SDFGState(label="switch_i64", sdfg=switch_bit.sdfg)
    # Copy over needed arrays
    if enable_int16:
        switch_state_i16.validate()
    switch_state_i32.validate()
    if enable_int64:
        switch_state_i64.validate()

    if enable_int16:
        switch_cfg_i16.add_node(switch_state_i16)
    switch_cfg_i32.add_node(switch_state_i32)
    if enable_int64:
        switch_cfg_i64.add_node(switch_state_i64)
    new_sdfg.add_node(switch_bit)
    if enable_int16 and enable_int64:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=switch_cfg_i16)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32"), branch=switch_cfg_i32)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=switch_cfg_i64)
    elif enable_int16:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 16"), branch=switch_cfg_i16)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 64"), branch=switch_cfg_i32)
    elif enable_int64:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 32 or bitwidth_sym == 16"), branch=switch_cfg_i32)
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym == 64"), branch=switch_cfg_i64)
    else:
        switch_bit.add_branch(condition=CodeBlock(code="bitwidth_sym <= 64"), branch=switch_cfg_i32)
    for oe in new_sdfg.out_edges(check_if):
        copy_edata = copy.deepcopy(oe.data)
        copy_edata.assignments = dict()
        new_sdfg.add_edge(check_if, switch_bit, copy_edata)
    for ie in new_sdfg.in_edges(copy_out):
        copy_edata = copy.deepcopy(ie.data)
        new_sdfg.add_edge(switch_bit, copy_out, copy_edata)
        new_sdfg.remove_edge(ie)
    sdutil.set_nested_sdfg_parent_references(new_sdfg)
    if enable_int16:
        switch_state_i16.validate()
    switch_state_i32.validate()
    if enable_int64:
        switch_state_i64.validate()

    for state in new_sdfg.all_states():
        state.validate()

    """
    for state in new_sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                sdutil.set_nested_sdfg_parent_references(node.sdfg)
    """

    new_sdfg.save("n2.sdfgz", compress=True)
    new_sdfg.validate()

    return new_sdfg

import dace

def make_flattened_data_to_non_transient_cpu_input(sdfg: dace.SDFG):
    flattener_node = None
    flattener_state = None
    deflattener_node = None
    deflattener_state = None

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.LibraryNode) and node.label == "flatten":
                flattener_node = node
                flattener_state = state
            elif isinstance(node, dace.nodes.LibraryNode) and node.label == "deflatten":
                deflattener_node = node
                deflattener_state = state

    assert flattener_node is not None, "Flatten node not found in the SDFG."
    assert deflattener_node is not None, "Deflatten node not found in the SDFG."
    assert flattener_state is not None, "Flatten state not found in the SDFG."
    assert deflattener_state is not None, "Deflatten state not found in the SDFG."

    flatten_in_struct_accesses = [ie.src for ie in flattener_state.in_edges(flattener_node)]
    flatten_out_data_accesses = [oe.dst for oe in flattener_state.out_edges(flattener_node)]
    flatten_data = [n.data for n in flatten_out_data_accesses] + [n.data for n in flatten_in_struct_accesses]

    for access in flatten_out_data_accesses:
        if flattener_state.out_degree(access) == 0:
            flattener_state.remove_node(access)
    for access in flatten_in_struct_accesses:
        if flattener_state.in_degree(access) == 0:
            flattener_state.remove_node(access)

    flattener_state.remove_node(flattener_node)

    for data_name in flatten_data:
        assert data_name in sdfg.arrays, f"Data {data_name} not found in SDFG arrays."
        sdfg.arrays[data_name].transient = False

    deflatten_in_accesses = [ie.src for ie in deflattener_state.in_edges(deflattener_node)]
    deflatten_out_accesses = [oe.dst for oe in deflattener_state.out_edges(deflattener_node)]
    deflatten_data = [n.data for n in deflatten_out_accesses] + [n.data for n in deflatten_in_accesses]

    for access in deflatten_out_accesses:
        if deflattener_state.out_degree(access) == 0:
            deflattener_state.remove_node(access)
    for access in deflatten_in_accesses:
        if deflattener_state.in_degree(access) == 0:
            deflattener_state.remove_node(access)

    deflattener_state.remove_node(deflattener_node)

    for data_name in deflatten_data:
        assert data_name in sdfg.arrays, f"Data {data_name} not found in SDFG arrays."
        sdfg.arrays[data_name].transient = False

    sdfg.save(sdfg.name + "_flattened_data_to_cpu_input.sdfg")

def make_flattened_data_to_non_transient_gpu_input(sdfg: dace.SDFG):
    flattener_node = None
    flattener_state = None
    deflattener_node = None
    deflattener_state = None

    for state in sdfg.all_states():
        for node in state.nodes():
            if node.label == "shallow_flatten":
                flattener_node = node
                flattener_state = state
            elif node.label == "shallow_deflatten":
                deflattener_node = node
                deflattener_state = state

    assert flattener_node is not None, "Flatten node not found in the SDFG."
    assert deflattener_node is not None, "Deflatten node not found in the SDFG."
    assert flattener_state is not None, "Flatten state not found in the SDFG."
    assert deflattener_state is not None, "Deflatten state not found in the SDFG."
    assert flattener_state.out_degree(flattener_node) == 0
    assert deflattener_state.out_degree(deflattener_node) == 0

    flatten_accesses = [ie.src for ie in flattener_state.in_edges(flattener_node)] + [oe.dst for oe in flattener_state.out_edges(flattener_node)]
    flatten_data = [n.data for n in flatten_accesses if isinstance(n, dace.nodes.AccessNode)]


    for access in flatten_accesses:
        if flattener_state.in_degree(access) == 0:
            flattener_state.remove_node(access)

    flattener_state.remove_node(flattener_node)

    for data_name in flatten_data:
        assert data_name in sdfg.arrays, f"Data {data_name} not found in SDFG arrays."
        sdfg.arrays[data_name].transient = False

    deflatten_accesses = [ie.src for ie in deflattener_state.in_edges(deflattener_node)] + [oe.dst for oe in deflattener_state.out_edges(deflattener_node)]
    deflatten_data = [n.data for n in deflatten_accesses if isinstance(n, dace.nodes.AccessNode)]

    for access in deflatten_accesses:
        if deflattener_state.in_degree(access) == 0:
            deflattener_state.remove_node(access)

    deflattener_state.remove_node(deflattener_node)

    for data_name in deflatten_data:
        assert data_name in sdfg.arrays, f"Data {data_name} not found in SDFG arrays."
        sdfg.arrays[data_name].transient = False


    arr_to_rm = set()
    for arr_name, arr in sdfg.arrays.items():
        if arr_name.startswith("gpu___CG") and isinstance(arr, dace.data.Array) and (not arr_name.endswith("uint8") and not arr_name.endswith("uint16")):
            if arr.transient is True:
                #arr.transient = False
                #print("Warning: GPU array", arr_name, "is transient, and not used, but make it non-transient still.")
                print("Warning: GPU array", arr_name, "is transient, and not used: delete.")
                arr_to_rm.add(arr_name)
    for arr_name in arr_to_rm:
        sdfg.remove_data(arr_name, validate=True)

    # sdfg.save(sdfg.name + "_flattened_data_to_gpu_input.sdfg")


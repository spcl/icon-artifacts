import dace
import copy

def add_gpu_copies_to_flattener(sdfg: dace.SDFG):
    flattener_lib_node, flattener_state = None, None
    deflattener_lib_node, deflattener_state = None, None

    for state in sdfg.all_states():
        for node in state.nodes():
            if node.label == "flatten" and isinstance(node, dace.sdfg.nodes.LibraryNode):
                flattener_lib_node = node
                flattener_state = state
            elif node.label == "deflatten" and isinstance(node, dace.sdfg.nodes.LibraryNode):
                deflattener_lib_node = node
                deflattener_state = state

    assert flattener_lib_node is not None, "Flattener library node not found in the SDFG."
    assert deflattener_lib_node is not None, "Deflatten library node not found in the SDFG."

    for oe in flattener_state.out_edges(flattener_lib_node):
        assert oe.src == flattener_lib_node, "Output edge source is not the flattener library node."
        dst_node = oe.dst
        edges_to_add = set()
        if (
            isinstance(dst_node, dace.sdfg.nodes.AccessNode) and
            dst_node.data in sdfg.arrays and
            isinstance(sdfg.arrays[dst_node.data], dace.data.Array) and
            not isinstance(sdfg.arrays[dst_node.data], dace.data.View) and
            not isinstance(sdfg.arrays[dst_node.data], dace.data.Scalar) and
            not isinstance(sdfg.arrays[dst_node.data], dace.data.Structure)
        ):
            arr = sdfg.arrays[dst_node.data]
            if arr.storage != dace.dtypes.StorageType.GPU_Global:
                copy_arr = copy.deepcopy(arr)
                copy_arr.storage = dace.dtypes.StorageType.GPU_Global
                sdfg.add_datadesc("gpu_" + dst_node.data, copy_arr)
                an = flattener_state.add_access("gpu_" + dst_node.data)
                edges_to_add.add((dst_node, None, an, None, dace.memlet.Memlet.from_array(dst_node.data, arr)))

        for e_data in edges_to_add:
            flattener_state.add_edge(*e_data)

    for ie in deflattener_state.in_edges(deflattener_lib_node):
        assert ie.dst == deflattener_lib_node, "Output edge source is not the flattener library node."
        src_node = ie.src
        edges_to_add = set()
        if (
            isinstance(src_node, dace.sdfg.nodes.AccessNode) and
            src_node.data in sdfg.arrays and
            isinstance(sdfg.arrays[src_node.data], dace.data.Array) and
            not isinstance(sdfg.arrays[src_node.data], dace.data.View) and
            not isinstance(sdfg.arrays[src_node.data], dace.data.Scalar) and
            not isinstance(sdfg.arrays[src_node.data], dace.data.Structure)
        ):
            arr = sdfg.arrays[src_node.data]
            if arr.storage != dace.dtypes.StorageType.GPU_Global:
                copy_arr = copy.deepcopy(arr)
                copy_arr.storage = dace.dtypes.StorageType.GPU_Global
                assert "gpu_" + src_node.data in sdfg.arrays
                #sdfg.add_datadesc("gpu_" + src_node.data, copy_arr)
                an = deflattener_state.add_access("gpu_" + src_node.data)
                edges_to_add.add((an, None, src_node, None, dace.memlet.Memlet.from_array("gpu_" + src_node.data, copy_arr)))

        for e_data in edges_to_add:
            deflattener_state.add_edge(*e_data)

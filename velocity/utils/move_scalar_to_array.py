import dace

def move_scalar_to_array(root:dace.SDFG, name:str):
    assert name in root.arrays, f"Array {name} not found in SDFG"
    assert isinstance(root.arrays[name], dace.data.Scalar), f"Array {name} is not a scalar"


    scalar_desc = root.arrays[name]
    root.remove_data(name, False)

    array_desc = dace.data.Array(
        dtype=scalar_desc.dtype,
        shape=(1,),
        transient=scalar_desc.transient,
        location=scalar_desc.location,
        strides=(1,),
        lifetime=scalar_desc.lifetime,
        storage=dace.dtypes.StorageType.Default,
    )

    root.add_datadesc(name, array_desc)

    for state in root.all_states():
        for edge in state.edges():
            if edge.data is not None and edge.data.data == name:
                edge.data = dace.memlet.Memlet.from_array(
                    dataname=name,
                    datadesc=array_desc, # Since scalar it will be len1 1D array
                )

    # Recursive to sub SDFGs
    for state in root.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                if (name in node.sdfg.arrays):
                    assert (name in node.in_connectors or name in node.out_connectors)
                    move_scalar_to_array(node.sdfg, name)

    for parent, arr_name, arr in root.arrays_recursive():
        if arr_name == name:
            assert isinstance(arr, dace.data.Array)
            assert parent is not None
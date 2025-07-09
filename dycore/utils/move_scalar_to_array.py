import dace

def move_scalar_to_array(root:dace.SDFG, name:str, double_size:bool=False):
    assert name in root.arrays, f"Array {name} not found in SDFG"
    assert isinstance(root.arrays[name], dace.data.Scalar), f"Array {name} is not a scalar"


    scalar_desc = root.arrays[name]
    root.remove_data(name, False)

    array_desc = dace.data.Array(
        dtype=scalar_desc.dtype,
        shape=(1,) if not double_size else (2, ),
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



def _tmp_difcoef(sdfg:dace.SDFG):
    for s in sdfg.all_states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.MapEntry):
                ins = [v for v in s.in_edges(n) if isinstance(v.src, dace.nodes.AccessNode) and v.src.data == "difcoef"]
                #print(ins)
                if len(ins) > 0:
                    assert len(ins) == 1
                    inan = ins[0].src
                    ies = [e for e in s.in_edges(n) if e.src == inan]
                    for ie in ies:
                        s.remove_edge(ie)
                        ie.dst.remove_in_connector(ie.dst_conn)
                        oes = [oe for oe in s.out_edges(ie.dst) if oe.src_conn == ie.dst_conn.replace("IN_", "OUT_")]
                        ie.dst.remove_out_connector(ie.dst_conn.replace("IN_", "OUT_"))
                        for oe in oes:
                            s.remove_edge(oe)
                            oe.dst.remove_in_connector(oe.dst_conn)
                            oe.dst.sdfg.arrays[oe.dst_conn].transient = True

                    outs = [v for v in s.out_edges(s.exit_node(n)) if isinstance(v.dst, dace.nodes.AccessNode) and v.dst.data == "difcoef"]
                    if len(outs) > 0:
                        assert len(outs) == 1
                        outan = outs[0].dst
                        oes = [e for e in s.out_edges(s.exit_node(n)) if e.dst == outan]
                        for oe in oes:
                            s.remove_edge(oe)
                            oe.src.remove_out_connector(oe.src_conn)
                            ies = [ie for ie in s.in_edges(oe.src) if ie.dst_conn == oe.src_conn.replace("OUT_", "IN_")]
                            oe.src.remove_in_connector(oe.src_conn.replace("OUT_", "IN_"))
                            for ie in ies:
                                s.remove_edge(ie)
                                ie.src.remove_out_connector(ie.src_conn)
                                ie.src.sdfg.arrays[ie.src_conn].transient = True
                        s.remove_node(outan)
                    s.remove_node(inan)
    # rm difcoef if not access node
    difaccessed = False
    for s in sdfg.all_states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.AccessNode) and n.data == "difcoef":
                difaccessed = True
                break
    if not difaccessed:
        sdfg.remove_data("difcoef", True)
    for s in sdfg.all_states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                _tmp_difcoef(n.sdfg)


"""
def _tmp_difcoef(root:dace.SDFG, name:str):
    assert name == 'difcoef'
    assert name in root.arrays, f"Array {name} not found in SDFG"
    assert isinstance(root.arrays[name], dace.data.Scalar), f"Array {name} is not a scalar"

    for n, graph in root.all_nodes_recursive():
        if (graph.sdfg != root and
            isinstance(n, dace.nodes.AccessNode) and
            n.data == name and
            name in graph.sdfg.arrays and
            isinstance(graph.sdfg.arrays[name], dace.data.Scalar) and
            graph.sdfg.arrays[name].transient == False and
            graph.in_degree(n) > 0):
            graph.sdfg.add_scalar(
                name="_tmp_" + name,
                dtype=graph.sdfg.arrays[name].dtype,
                transient=True,
                storage=dace.dtypes.StorageType.Register,
            )
            n.data = "_tmp_" + name
            parent_nsdfg_node = graph.sdfg.parent_nsdfg_node
            parent_graphs = [g for v, g in root.all_nodes_recursive() if v == parent_nsdfg_node]
            assert len(parent_graphs) == 1
            parent_graph = parent_graphs[0]
            for oe in parent_graph.out_edges(parent_nsdfg_node):
                if oe.data.data == name:
                    oe2s = list(parent_graph.out_edges_by_connector(oe.dst, oe.dst_conn.replace("IN_", "OUT_")))
                    assert len(oe2s) == 1
                    oe2 = oe2s[0]

                    parent_graph.remove_edge(oe)
                    parent_graph.remove_edge(oe2)
                    oe.dst.remove_in_connector(oe.dst_conn)
                    oe.dst.remove_out_connector(oe.dst_conn.replace("IN_", "OUT_"))
                    parent_graph.remove_node(oe2.dst)
                    return
"""
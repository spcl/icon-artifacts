import dace

def specialize_scalar_copy(sdfg: dace.SDFG):
    for s, g in sdfg.all_nodes_recursive():
        if isinstance(s, dace.SDFGState):
            for e in s.edges():
                src = e.src
                dst = e.dst
                if (isinstance(src, dace.nodes.AccessNode) and isinstance(dst, dace.nodes.AccessNode) and
                    e.data is not None and e.data.data is not None and (e.data.data == src.data or e.data.data)
                    and isinstance(g.sdfg.arrays[src.data], dace.data.Scalar) and isinstance(g.sdfg.arrays[dst.data], dace.data.Scalar)):
                    # Scalar -> Scalar copy
                    t = s.add_tasklet(
                        f"copy_{src.data}_{dst.data}",
                        {"_in"},
                        {"_out"},
                        f"_out = _in",
                    )
                    t.add_in_connector("_in")
                    t.add_out_connector("_out")
                    s.add_edge(src, "_in", t, "_in", dace.Memlet.from_array(src.data, g.sdfg.arrays[src.data]))
                    s.add_edge(t, "_out", dst, "_out", dace.Memlet.from_array(dst.data, g.sdfg.arrays[dst.data]))
                    s.remove_edge(e)

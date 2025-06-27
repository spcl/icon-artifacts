import dace
import copy

from dace.sdfg.propagation import propagate_memlets_sdfg

def add_map_inside(state: dace.SDFGState, map_entry: dace.nodes.MapEntry,
                   new_map_param_range_dict: dict, new_map_schedule: dace.ScheduleType,
                   new_map_name: str):
    new_map_entry, new_map_exit = state.add_map(
        name=new_map_name,
        ndrange=new_map_param_range_dict,
        schedule=new_map_schedule,
    )
    map_exit = state.exit_node(map_entry)

    # Get unique data elements
    edges_to_rm = set()
    edges_to_add = set()

    for oe in state.out_edges(map_entry):
        edges_to_rm.add(oe)
    # Inputs from parent map should be made unique
    for out_conn in map_entry.out_connectors:
        edges = list(state.out_edges_by_connector(map_entry, out_conn))
        assert len(edges) > 0
        oe = edges[0]
        src_conn = oe.src_conn
        assert "OUT_" in src_conn
        dst_conn = src_conn.replace("OUT_", "IN_")
        new_map_entry.add_in_connector(dst_conn)
        edges_to_add.add((oe.src, oe.src_conn, new_map_entry, dst_conn, dace.memlet.Memlet.from_array(
            dataname=oe.data.data,
            datadesc=state.sdfg.arrays[oe.data.data],
        )))
    # Outputs continuing to everyone
    for oe in state.out_edges(map_entry):
        src_conn = oe.src_conn
        assert "OUT_" in src_conn
        dst_conn = src_conn.replace("OUT_", "IN_")
        new_map_entry.add_out_connector(src_conn)
        edges_to_add.add((new_map_entry, src_conn, oe.dst, oe.dst_conn, copy.deepcopy(oe.data)))

    for ie in state.in_edges(map_exit):
        edges_to_rm.add(ie)
    for in_conn in map_exit.in_connectors:
        edges = list(state.in_edges_by_connector(map_exit, in_conn))
        assert len(edges) > 0
        ie = edges[0]
        assert "IN_" in ie.dst_conn
        dst_conn = ie.dst_conn
        src_conn = dst_conn.replace("IN_", "OUT_")
        new_map_exit.add_in_connector(dst_conn)
        edges_to_add.add((new_map_exit, src_conn, ie.dst, ie.dst_conn, dace.memlet.Memlet.from_array(
            dataname=ie.data.data,
            datadesc=state.sdfg.arrays[ie.data.data],
        )))
    for ie in state.in_edges(map_exit):
        dst_conn = ie.dst_conn
        src_conn = dst_conn.replace("IN_", "OUT_")
        new_map_exit.add_out_connector(src_conn)
        edges_to_add.add((ie.src, ie.src_conn, new_map_exit, dst_conn, copy.deepcopy(ie.data)))

    assert len(edges_to_rm) > 0
    for edge in edges_to_rm:
        state.remove_edge(edge)
    for edge in edges_to_add:
        state.add_edge(*edge)

    return new_map_entry, new_map_exit

def reinsert_symbols_to_nsdfg(graph: dace.SDFGState):
    # Why would this happen? This is a workaround for the issue where nested SDFGs do not have their symbols properly assigned.
    for node, parent_graph in graph.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG):
            child_sdfg = node.sdfg
            connectors = node.in_connectors.keys() | node.out_connectors.keys()
            symbols = set(k for k in node.sdfg.free_symbols if k not in connectors)
            missing_symbols = [s for s in symbols if s not in node.symbol_mapping]
            if missing_symbols:
                for missing_symbol in missing_symbols:
                    #child_sdfg.add_symbol(missing_symbol, node.sdfg.symbols[missing_symbol] if missing_symbol in node.sdfg.symbols else dace.int32)
                    #node.symbol_mapping[missing_symbol] = missing_symbol
                    print("Symbols", symbols)
                    print("Missing symbols", missing_symbols)
                    child_sdfg.save("c.sdfgz", compress=True)
                    child_sdfg.remove_symbol(missing_symbol)

def reshape_kernels(sdfg: dace.SDFG, unroll_inner_map: bool):
    map_entries = [(node, graph) for node,graph in sdfg.all_nodes_recursive() if isinstance(node, dace.nodes.MapEntry)]

    gid = 0
    for map_entry, graph in map_entries:
        if len(map_entry.map.range) != 2:
            continue
        if map_entry.map.schedule != dace.ScheduleType.GPU_Device:
            continue
        # Otherwise we are in a kernel and we can do this.
        # We have kernels of form:
        # [j=0:nlev, i=0:nproma]
        # [Nested SDFG]
        #
        # These kernels are ran from an outer map of form
        # [k=0:nblks]
        #
        # The new kernel will look as follows:
        # [i=0:nproma: _=0:32] @ GPU_Device # 0:32 is for DaCe codegen to work to generate 32 threads per column (nlev)
        # [tidx=0:32] @ GPU_ThreadBlock # is to generate tidx for the next iteration
        # [j=tidx:nlev:32] @ Sequential
        # TODO: Extension every thread computes 2 consecutive elements of the column
        # Prob. Not very good idea because nlev is not contigously stored

        tblock_size = 31  # This is the number of threads per block, can be changed if needed. (range is inclusive in sympy)
        nlev_range = map_entry.map.range[0]
        nlev_param = map_entry.map.params[0]
        nproma_range = map_entry.map.range[1]
        nproma_param = map_entry.map.params[1]
        tid_symbol_name = "_column_tidx"
        tid_symbol = dace.symbol(tid_symbol_name)
        nlev_b, nlev_e, nlev_s = nlev_range
        assert nlev_s == 1

        # Rm the nlev range from the map entry, and add a 0:block_size range
        map_entry.map.range = [(nproma_range), (0, tblock_size, 1)]
        map_entry.map.params = [nproma_param, "__tblock_size_to_warp_size_gen"]

        new_nlev_range = dace.subsets.Range([(tid_symbol + nlev_b, nlev_e, tblock_size+1)])
        tblock_range = dace.subsets.Range([(0, tblock_size, 1)])

        # Add thread block map inside the kernel/device map [0:tblock_size]
        tblock_map_entry, tblock_map_exit = add_map_inside(
            graph,
            map_entry,
            new_map_param_range_dict={tid_symbol_name: tblock_range},
            new_map_schedule=dace.ScheduleType.GPU_ThreadBlock,
            new_map_name=f"ColumnThreadBlockMap_{gid}",
        )

        sdfg.save("b.sdfgz", compress=True)

        assert tblock_map_entry in graph.nodes()

        # Add sequential map inside the thread block map [tidx:nlev:tblock_size]
        seq_map_entry, seq_map_exit = add_map_inside(
            graph,
            tblock_map_entry,
            new_map_param_range_dict={nlev_param: new_nlev_range},
            new_map_schedule=dace.ScheduleType.Sequential,
            new_map_name=f"ColumnSequentialMap_{gid}",
        )
        if unroll_inner_map:
            seq_map_entry.map.unroll = True

        gid += 1

    propagate_memlets_sdfg(sdfg)

    # Why does this error happen again, I do not change nested SDFGs?
    reinsert_symbols_to_nsdfg(sdfg)
    sdfg.validate()


def reshape_kernels_w_coarsening(sdfg: dace.SDFG, x_coarsening: int, y_coarsening: int,
                                 x_block_size: int, y_block_size: int, unroll_x: bool, unroll_y: bool,
                                 unroll_x_factor: int | None, unroll_y_factor: int | None):
    # We have kernels of form:
    # [j=0:nlev, i=0:nproma]
    # [Nested SDFG]
    #
    # These kernels are ran from an outer map of form
    # [k=0:nblks]
    #
    # The new kernel will look as follows:
    # tblock.x, tblock,y = e.g. 32, 4
    # nlev_coarsening = e.g. 2
    # [k=0:nlev/(tblock.y*nlev_coarsening), i=0:nproma/tblock.x:] @ GPU_Device # 0:32 is for DaCe codegen to work to generate 32 threads per column (nlev)
    # [tidy=0:tblock.y, tidx=0:tblock.x] @ GPU_ThreadBlock # is to generate tidx for the next iteration
    # [j=k:Min(nlev, k+tblock.y*nlev_coarsening):tblock.y] @ Sequential
    # TODO: Extension every thread computes 2 consecutive elements of the column
    # Prob. Not very good idea because nlev is not contigously stored
    map_entries = [(node, graph) for node,graph in sdfg.all_nodes_recursive() if isinstance(node, dace.nodes.MapEntry)]

    gid = 0
    for map_entry, graph in map_entries:
        if len(map_entry.map.range) != 2:
            continue
        if map_entry.map.schedule != dace.ScheduleType.GPU_Device:
            continue
        # Otherwise we are in a kernel and we can do this.
        # We have kernels of form:
        # [j=0:nlev, i=0:nproma]
        # [Nested SDFG]
        #
        # These kernels are ran from an outer map of form
        # [k=0:nblks]
        #
        # The new kernel will look as follows:
        # [_i=0:nproma/4: _y=0:4, _x=0:128] @ GPU_Device # 0:32 is for DaCe codegen to work to generate 32 threads per column (nlev)
        # [tidy=0:4, tidx=0:128] @ GPU_ThreadBlock # is to generate tidx for the next iteration
        # [i=_i:_i+4, j=tidx:nlev:32] @ Sequential
        # TODO: Extension every thread computes 2 consecutive elements of the column
        # Prob. Not very good idea because nlev is not contigously stored

        tblock_size_x = x_block_size   # This is the number of threads per block, can be changed if needed. (range is inclusive in sympy)
        tblock_size_y = y_block_size
        nlev_range = map_entry.map.range[0]
        nlev_param = map_entry.map.params[0]
        nlev_param_sym = dace.symbol(nlev_param)
        nproma_range = map_entry.map.range[1]
        nproma_param = map_entry.map.params[1]
        nproma_param_sym = dace.symbol(nproma_param)
        tidy_symbol_name = "_column_tidy"
        tidy_symbol = dace.symbol(tidy_symbol_name)
        tidx_symbol_name = "_row_tidx"
        tidx_symbol = dace.symbol(tidx_symbol_name)
        nlev_b, nlev_e, nlev_s = nlev_range
        nproma_b, nproma_e, nproma_s = nproma_range
        assert nlev_s == 1

        glob_y_step = y_coarsening * tblock_size_y
        glob_x_step = x_coarsening * tblock_size_x
        # Rm the nlev range from the map entry, and add a 0:block_size range
        # [start_idx:end_idx:1] -> [start_idx:end_idx:(tblock_x*x_coarsening)]
        coarsened_nproma_range = (nproma_b, nproma_e, glob_x_step)
        coarsened_nlev_range = (nlev_b, nlev_e, glob_y_step)
        assert nproma_s == 1
        map_entry.map.range = [(coarsened_nlev_range), (coarsened_nproma_range)]
        map_entry.map.params = ["_y", "_x"]
        _y_symbol = dace.symbol("_y")
        _x_symbol = dace.symbol("_x")

        if y_coarsening > 1:
            min_expr_y = dace.symbolic.sympy.Min(nlev_e, tidy_symbol + _y_symbol + tblock_size_y * y_coarsening)
            step_expr_y = tblock_size_y
        else:
            min_expr_y = dace.symbolic.sympy.Min(nlev_e, tidy_symbol + _y_symbol + y_coarsening)
            step_expr_y = 1
        min_expr_x = dace.symbolic.sympy.Min(nproma_e, tidx_symbol + _x_symbol + x_coarsening)
        # X-range is coarsened contiguously, Y-range is coarsened in steps of tblock_size_y
        new_inner_map_range = dace.subsets.Range([(tidy_symbol + _y_symbol, min_expr_y, step_expr_y),
                                                  (tidx_symbol + _x_symbol, min_expr_x, 1)])
        tblock_range = dace.subsets.Range([(0, tblock_size_y - 1, 1), (0, tblock_size_x - 1, 1)])

        # Add thread block map inside the kernel/device map [0:tblock_size]
        tblock_map_entry, tblock_map_exit = add_map_inside(
            graph,
            map_entry,
            new_map_param_range_dict={tidy_symbol_name: tblock_range[0], tidx_symbol_name: tblock_range[1]},
            new_map_schedule=dace.ScheduleType.GPU_ThreadBlock,
            new_map_name=f"ColumnThreadBlockMap_{gid}",
        )

        sdfg.save("b.sdfgz", compress=True)

        assert tblock_map_entry in graph.nodes()

        # Add sequential map inside the thread block map [tidx:nlev:tblock_size]
        seq_map_entry, seq_map_exit = add_map_inside(
            graph,
            tblock_map_entry,
            new_map_param_range_dict={nlev_param: new_inner_map_range[0]},
            new_map_schedule=dace.ScheduleType.Sequential,
            new_map_name=f"ColumnSequentialMap_{gid}",
        )
        if unroll_y:
            seq_map_entry.map.unroll = True
        if unroll_y_factor is not None:
            seq_map_entry.map.unroll_factor = unroll_y_factor

        seq_map_entry2, seq_map_exit2 = add_map_inside(
            graph,
            seq_map_entry,
            new_map_param_range_dict={nproma_param: new_inner_map_range[1]},
            new_map_schedule=dace.ScheduleType.Sequential,
            new_map_name=f"ColumnSequentialMap_{gid}",
        )
        if unroll_x:
            seq_map_entry2.map.unroll = True
        if unroll_x_factor is not None:
            seq_map_entry2.map.unroll_factor = unroll_x_factor

        gid += 1

    propagate_memlets_sdfg(sdfg)

    # Why does this error happen again, I do not change nested SDFGs?
    reinsert_symbols_to_nsdfg(sdfg)
    sdfg.validate()
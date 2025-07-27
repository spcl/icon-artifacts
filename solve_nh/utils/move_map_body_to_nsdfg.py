import dace
import warnings
import copy


def move_map_body_to_nsdf(sdfg: dace.SDFG, state: dace.SDFGState, node: dace.nodes.MapEntry):
    map_inner_nodes = list(state.all_nodes_between(node, state.exit_node(node)))
    if (len(map_inner_nodes) != 1) or (
        len(map_inner_nodes) == 1 and not isinstance(map_inner_nodes[0], dace.nodes.NestedSDFG)
    ):
        map_inner_sdfg = dace.SDFG(
            name=f"{node.label}_inner_sdfg_{label_counter}",
        )
        map_inner_state = map_inner_sdfg.add_state(
            label=f"{node.label}_inner_state_{label_counter}",
            is_start_block=True
        )
        label_counter += 1
        srcs = {e.data.data for e in state.in_edges(node)}
        dsts = {e.data.data for e in state.out_edges(state.exit_node(node))}

        node_map = dict()
        # Use later for removing the original nodes
        all_inner_map_nodes = set(state.all_nodes_between(node, state.exit_node(node)))
        for nd in state.all_nodes_between(node, state.exit_node(node)):
            cpynd = copy.deepcopy(nd)
            node_map[nd] = cpynd
            map_inner_state.add_node(cpynd)
        for src in srcs.union(dsts):
            an = map_inner_state.add_access(src)
            node_map[src] = an
        for src in srcs.union(dsts):
            copydesc = copy.deepcopy(state.sdfg.arrays[src])
            copydesc.transient = False
            map_inner_sdfg.add_datadesc(
                name=src,
                datadesc=copydesc,
                find_new_name=False,
            )

        # Ad all edges using the node mapping
        for e in state.all_edges(*state.all_nodes_between(node, state.exit_node(node))):
            if e.src != node:
                src = node_map[e.src]
                src_conn = e.src_conn
            else:
                src = node_map[e.data.data]
                src_conn = None
            if e.dst != state.exit_node(node):
                dst = node_map[e.dst]
                dst_conn = e.dst_conn
            else:
                dst = node_map[e.data.data]
                dst_conn = None
            map_inner_state.add_edge(
                src, src_conn,
                dst, dst_conn,
                copy.deepcopy(e.data)
            )

        map_inner_nsdfg = state.add_nested_sdfg(
            sdfg=map_inner_sdfg,
            parent=state,
            inputs=srcs,
            outputs=dsts,
        )

        # Connections from map nsdfg
        for e in state.out_edges(node):
            state.add_edge(
                e.src,
                e.src_conn,
                map_inner_nsdfg,
                e.data.data,
                dace.memlet.Memlet.from_array(
                    e.data.data,
                    state.sdfg.arrays[e.data.data]
                )
            )
        for e in state.in_edges(state.exit_node(node)):
            state.add_edge(
                map_inner_nsdfg,
                e.data.data,
                e.dst,
                e.dst_conn,
                dace.memlet.Memlet.from_array(
                    e.data.data,
                    state.sdfg.arrays[e.data.data]
                )
            )

        # Remove all the original nodes
        for nd in all_inner_map_nodes:
            state.remove_node(nd)


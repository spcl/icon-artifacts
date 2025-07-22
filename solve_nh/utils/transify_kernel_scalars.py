import dace
from dace.sdfg.state import ControlFlowRegion, ConditionalBlock, LoopRegion
from .get_num_parent_map_scopes import get_num_parent_map_scopes
import copy
import typing
from utils.rename import rename_on_if, rename_on_for

def transify_kernel_scalars(sdfg: dace.SDFG, map_sched_type: dace.ScheduleType = dace.ScheduleType.GPU_Device):
    kernel_id = 0
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.MapEntry):
            # If the map is a kernel map, then we need to transify the scalars
            if node.map.schedule == map_sched_type and get_num_parent_map_scopes(sdfg, node, graph) == 0:
                out_data = {e.data.data for e in graph.out_edges(node) if e.data is not None and e.data.data is not None}
                inner_nodes = graph.all_nodes_between(node, graph.exit_node(node))
                transifies = any(isinstance(inner_node, dace.nodes.AccessNode) and inner_node.data not in out_data and not graph.sdfg.arrays[inner_node.data].transient and isinstance(graph.sdfg.arrays[inner_node.data], dace.data.Scalar) for inner_node in inner_nodes)
                if transifies:
                    kernel_id += 1
                name_mapping = dict()
                for inner_node in inner_nodes:
                    if (isinstance(inner_node, dace.nodes.AccessNode) and
                         inner_node.data not in out_data and
                         not graph.sdfg.arrays[inner_node.data].transient and
                         isinstance(graph.sdfg.arrays[inner_node.data], dace.data.Scalar)):
                            # If the access node is an output of the map, then we need to transify it
                            new_scalar_desc = copy.deepcopy(graph.sdfg.arrays[inner_node.data])
                            new_scalar_desc.transient = True
                            new_scalar_desc.storage = dace.dtypes.StorageType.Register
                            graph.sdfg.add_datadesc(f"{inner_node.data}_{kernel_id}", new_scalar_desc)
                            name_mapping[inner_node.data] = f"{inner_node.data}_{kernel_id}"
                for inner_node in inner_nodes:
                    if isinstance(inner_node, dace.nodes.AccessNode) and inner_node.data in name_mapping:
                        inner_node.data = name_mapping[inner_node.data]
                for edge in graph.all_edges(*inner_nodes):
                    if edge.data is not None and edge.data.data is not None:
                        if edge.data.data in name_mapping:
                            edge.data.data = name_mapping[edge.data.data]


def _find_parent_graph(sdfg: dace.SDFG, node: dace.nodes.Node):
    """Find the parent state of a node in a nested SDFG."""
    for n, g in sdfg.all_nodes_recursive():
        if n == node:
            return g
    raise ValueError(f"Node {node} not found in SDFG {sdfg.name}.")

def rm_connection_of_desc_to_nsdfg_node(nsdfg_node: dace.nodes.NestedSDFG, state: dace.SDFGState, desc_name: str):

    input_path = []
    output_path = []

    # Get in-edges in to the parent SDFG node
    if desc_name in nsdfg_node.in_connectors:
        cur_edge = next(iter(state.in_edges_by_connector(nsdfg_node, desc_name)))
        assert len(list(state.in_edges_by_connector(nsdfg_node, desc_name))) == 1, f"Multiple edges found for {nsdfg_node} with connector {desc_name}."
        while not isinstance(cur_edge.src, dace.nodes.AccessNode):
            input_path.append(cur_edge)
            cur_edge = next(iter(state.in_edges_by_connector(cur_edge.src, cur_edge.src_conn.replace("OUT_", "IN_"))))
        input_path.append(cur_edge)

    # Get out-edges out from the parent SDFG node
    if desc_name in nsdfg_node.out_connectors:
        cur_edge = next(iter(state.out_edges_by_connector(nsdfg_node, desc_name)))
        assert len(list(state.out_edges_by_connector(nsdfg_node, desc_name))) == 1, f"Multiple edges found for {nsdfg_node} with connector {desc_name}."
        while not isinstance(cur_edge.dst, dace.nodes.AccessNode):
            output_path.append(cur_edge)
            cur_edge = next(iter(state.out_edges_by_connector(cur_edge.dst, cur_edge.dst_conn.replace("IN_", "OUT_"))))
        output_path.append(cur_edge)

    # Remove all edges in the input and output paths
    for edge in input_path:
        state.remove_edge(edge)
        if edge.src_conn in edge.src.out_connectors:
            edge.src.remove_out_connector(edge.src_conn)
        if edge.dst_conn in edge.dst.in_connectors:
            edge.dst.remove_in_connector(edge.dst_conn)
        if edge == input_path[-1]:
            if state.degree(edge.src) == 0:
                state.remove_node(edge.src)
    for edge in output_path:
        state.remove_edge(edge)
        if edge.src_conn in edge.src.out_connectors:
            edge.src.remove_out_connector(edge.src_conn)
        if edge.dst_conn in edge.dst.in_connectors:
            edge.dst.remove_in_connector(edge.dst_conn)
        if edge == output_path[-1]:
            if state.degree(edge.dst) == 0:
                state.remove_node(edge.dst)

def rm_from_input_output(root: dace.SDFG, sub_sdfg: dace.SDFG, desc_name: str):
    sub_sdfg.remove_data(desc_name, True)
    parent_nsdfg_node = sub_sdfg.parent_nsdfg_node
    if parent_nsdfg_node is None:
        return
    parent_state = _find_parent_graph(root, parent_nsdfg_node)
    while parent_nsdfg_node is not None:
        rm_connection_of_desc_to_nsdfg_node(parent_nsdfg_node, parent_state, desc_name)
        parent_nsdfg_node = parent_state.sdfg.parent_nsdfg_node
        if parent_nsdfg_node is not None:
            parent_state = _find_parent_graph(root, parent_nsdfg_node)


def _get_bfs_states_list(cfg: LoopRegion):
    """Get a list of states in the BFS order."""
    nodes = list(cfg.bfs_nodes(cfg.start_block))

    # Assume Top-level Nodes are like these:
    # [CFG0, State0, CFG1]
    # Then this will expand it further:
    # [CFG0.0, State0.0, State0, State1.0, State1.1]
    # Until there are only states:
    # [State0.0.0, State0.0.1, State0.0, State0 State1.0, State1.1]
    # For IfCFG -> Do it for the branches left-to-right.

    len_changed = True
    while len_changed:
        new_nodes = []
        len_changed = False
        for i, node in enumerate(nodes):
            if isinstance(node, dace.SDFGState):
                new_nodes.append(node)
            elif isinstance(node, LoopRegion):
                nn = node.bfs_nodes(node.start_block)
                len_changed = True
                new_nodes += list(nn)
            elif isinstance(node, ConditionalBlock):
                bodies = []
                for _, body in node.branches:
                    bodies += list(body.bfs_nodes(body.start_block))
                new_nodes += list(bodies)
                len_changed = True
            else:
                raise ValueError(f"Unexpected node type {type(node)} in BFS traversal of LoopRegion.")
        nodes = new_nodes

    return nodes

def _is_always_write_first_impl_cfg(cfg: ControlFlowRegion, desc_name: str):
    for node in cfg.bfs_nodes(cfg.start_block):
        if isinstance(node, dace.SDFGState):
            val =_is_always_write_first_impl_state(node, desc_name)
            if val is not None:
                return val
        elif isinstance(node, ConditionalBlock):
            val = _is_always_write_first_impl_if(node, desc_name)
            if val is not None:
                return val
        else:
            val = _is_always_write_first_impl_cfg(node, desc_name)
            if val is not None:
                return val

    return None

def _is_always_write_first_impl_state(cfg: ControlFlowRegion, desc_name: str):
    assert isinstance(cfg, dace.SDFGState), f"Expected cfg to be a SDFGState, got {type(cfg)}."
    state = cfg
    snode = state.parent_graph
    has_desc_in_state = any([node.data == desc_name for node in state.nodes() if isinstance(node, dace.nodes.AccessNode)])

    if has_desc_in_state:
        always_write_first = all([(snode.in_degree(node) > 0) for node in snode.nodes() if isinstance(node, dace.nodes.AccessNode) and node.data == desc_name])
        return always_write_first

    return None


def _is_always_write_first_impl_if(cfg: ControlFlowRegion, desc_name: str):
    assert isinstance(cfg, ConditionalBlock), f"Expected cfg to be a ConditionalBlock, got {type(cfg)}."
    _is_write_first_vals = [_is_always_write_first_impl_cfg(body, desc_name) for _, body in cfg.branches]

    if all(v is None or v is True for v in _is_write_first_vals):
        return True

    return None

def is_always_write_first(cfg: ControlFlowRegion, desc_name: str):
    return _is_always_write_first_impl_cfg(cfg, desc_name)

def transify_targeted_scalar(sdfg: dace.SDFG, desc_candidate_names: typing.Set[str]):
    # Filter candidate names to only include scalars
    desc_names = set()
    for name in desc_candidate_names:
        if name in sdfg.arrays and isinstance(sdfg.arrays[name], dace.data.Scalar):
            desc_names.add(name)

    for snode, graph in sdfg.all_nodes_recursive():
        # Only apply to SDFGs of LoopRegions (OMP Private => Means the SDFG within a For CFG in SDFG)
        if isinstance(snode, LoopRegion):
            cfg = snode # snode.sdfg is the parent SDFG

            # cfg.all_control_flow_regions() -> should give states parent-first
            # all_nodes_are_states = all(isinstance(node, dace.SDFGState) for node in cfg.nodes())
            # if not all_nodes_are_states:
            #    continue

            path_graph = all(cfg.in_degree(node) <= 1 and cfg.out_degree(node) <= 1 for node in cfg.nodes())
            assert path_graph, "Only path graphs (all top level nodes have in_degree <= 1  and out_degree <= 1) are supported for transifying scalars in LoopRegions."

            # Build a replacement dictionary for the scalars
            replace_dict = dict()
            for desc_name in desc_names:
                # Check if the SDFG has the desc_name accessed in an access node
                has_desc = any([node.data == desc_name for state in snode.all_states() for node in state.nodes() if isinstance(node, dace.nodes.AccessNode)])
                # No access skip the rest
                if not has_desc:
                    continue

                # Need to be write-first always to be a real private/threadlocal scalar
                # BFS the states, the moment we see write-first or non-write-first access pattern then stop
                # As if in state 0, it is written first, it does not matter what happens in state 1

                # If CFG bfs recursively, what matters is the state
                # If IfBlock is encountered, ensure it is write-first in all branches (if not writes None is accepted too)
                desc_is_write_first = is_always_write_first(cfg, desc_name)

                # If None then this scalar is not used in the ForCFG
                # If true, then it can become a transient
                # If not write-first (e.g. read before completely writing to), then we can transify it
                if desc_is_write_first is not None and desc_is_write_first is True:
                    # Add the local transient to the SDFG
                    desc = snode.sdfg.arrays[desc_name]
                    name = desc_name + "_local"
                    if name not in snode.sdfg.arrays:
                        copydesc = copy.deepcopy(desc)
                        copydesc.transient = True
                        copydesc.storage = dace.dtypes.StorageType.Register
                        snode.sdfg.add_datadesc(name, copydesc)
                    # Add the name to the replacement dictionary
                    replace_dict[desc_name] = name

            # Replace the scalars in the SDFG
            cfg.replace_dict(repl=replace_dict)
            for src, dst in replace_dict.items():
                rename_on_if(cfg, src, dst)
                # rename_on_for(cfg, src, dst) # This is OK, no need to call again as the current f2dace commit replaces for loops
                # Repl-name might make the the transient local accesses to be-non transient due to name change on the data container
                if dst in snode.sdfg.arrays:
                    desc = snode.sdfg.arrays[dst]
                    assert isinstance(desc, dace.data.Scalar), f"Expected {dst} to be a scalar, got {type(desc)}."
                    if desc.transient is False:
                        desc.transient = True
                        desc.storage = dace.dtypes.StorageType.Register

def retransify_scalar_with_local_prefix(root: dace.SDFG, sdfg: dace.SDFG):
    for arr_name, arr_desc in sdfg.arrays.items():
        if (arr_name.endswith("_local") and isinstance(arr_desc, dace.data.Scalar) and
            not arr_name.startswith("i_startidx") and not arr_name.startswith("i_endidx") and
            not arr_name.startswith("je_") and not arr_name.startswith("jb_")):
            if arr_desc.transient is False:
                arr_desc.transient = True
                arr_desc.storage = dace.dtypes.StorageType.Register
            # Remove in and out connectors
            parent_nsdfg_node = sdfg.parent_nsdfg_node
            if parent_nsdfg_node is not None:
                parent_state = _find_parent_graph(root, parent_nsdfg_node)
                rm_connection_of_desc_to_nsdfg_node(parent_nsdfg_node, parent_state, arr_name)

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                retransify_scalar_with_local_prefix(root, node.sdfg)

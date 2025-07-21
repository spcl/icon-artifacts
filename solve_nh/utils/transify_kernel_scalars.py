import dace
from dace.sdfg.state import LoopRegion
from .get_num_parent_map_scopes import get_num_parent_map_scopes
import copy
import typing

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


def _find_parent_graph(sdfg:dace.SDFG, node:dace.nodes.Node):
    """Find the parent state of a node in a nested SDFG."""
    for n,g in sdfg.all_nodes_recursive():
        if n == node:
            return g
    raise ValueError(f"Node {node} not found in SDFG {sdfg.name}.")

def rm(nsdfg_node: dace.nodes.NestedSDFG, state: dace.SDFGState, desc_name: str):

    input_path = []
    output_path = []

    if desc_name in nsdfg_node.in_connectors:
        cur_edge = state.in_edges_by_connector(nsdfg_node, desc_name)[0]
        while not isinstance(cur_edge.src, dace.nodes.AccessNode):
            input_path.append(cur_edge)
            cur_edge = state.in_edges_by_connector(cur_edge.src, cur_edge.src_conn.replace("OUT_", "IN_"))[0]
        input_path.append(cur_edge)
    if desc_name in nsdfg_node.out_connectors:
        cur_edge = state.out_edges_by_connector(nsdfg_node, desc_name)[0]
        while not isinstance(cur_edge.dst, dace.nodes.AccessNode):
            output_path.append(cur_edge)
            cur_edge = state.out_edges_by_connector(cur_edge.dst, cur_edge.dst_conn.replace("IN_", "OUT_"))[0]
        output_path.append(cur_edge)

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
    parent_state = _find_parent_graph(root, parent_nsdfg_node)
    while parent_nsdfg_node is not None:
        rm(parent_nsdfg_node, parent_state, desc_name)
        parent_nsdfg_node = parent_state.sdfg.parent_nsdfg_node
        if parent_nsdfg_node is not None:
            parent_state = _find_parent_graph(root, parent_nsdfg_node)


def transify_targeted_scalar(sdfg: dace.SDFG, desc_names: typing.Set[str]):
    for snode, graph in sdfg.all_nodes_recursive():
        if isinstance(snode, dace.SDFGState):
            for desc_name in desc_names:
                has_desc = [node.data == desc_name for node in snode.nodes() if isinstance(node, dace.nodes.AccessNode)]
                if has_desc:
                    desc = graph.sdfg.arrays[desc_name]
                    name = "tmp_" + desc_name
                    if name not in graph.sdfg.arrays:
                        copydesc = copy.deepcopy(desc)
                        copydesc.transient = True
                        graph.sdfg.add_datadesc(name, copydesc)
                    for node in snode.nodes():
                        if isinstance(node, dace.nodes.AccessNode) and node.data == desc_name:
                            node.data = f"tmp_" + desc_name
                    for edge in snode.edges():
                        if edge.data is not None and edge.data.data == desc_name:
                            edge.data.data = f"tmp_" + desc_name


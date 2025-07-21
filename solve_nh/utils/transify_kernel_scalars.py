import dace
from .get_num_parent_map_scopes import get_num_parent_map_scopes
import copy

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

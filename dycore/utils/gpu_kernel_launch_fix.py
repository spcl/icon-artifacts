import dace
from utils import find_node_by_name
import copy

def wrap_reduction_and_T_l488_c488in_gpumap(sdfg: dace.SDFG):
    """
    Wraps the reduction and T_l488_c488 in a GPU map.
    Should be called after GPUKernelLaunchRestructure.
    """
    # Find the tasklet and reduction subgraph
    tasklet, parent = find_node_by_name(sdfg, "T_l488_c488")
    a = parent.sdfg.parent_nsdfg_node

    # Get the input and outputs of the map
    out_edges = parent.out_edges(tasklet)
    assert len(out_edges) == 1
    assert out_edges[0].data.data == "vcflmax"
    out_edge = out_edges[0]
    output_node = out_edge.dst

    in_edges = parent.in_edges(tasklet)
    assert len(in_edges) == 1
    assert in_edges[0].data.data == "maxvcfl"
    in_edge = in_edges[0]

    # Change the storage type for maxvcfl to GPU_Global
    sdfg.arrays["maxvcfl"].storage = dace.dtypes.StorageType.GPU_Global
    parent.parent.arrays["maxvcfl"].storage = dace.dtypes.StorageType.GPU_Global

    max_in_edges = parent.in_edges(in_edge.src)
    assert len(max_in_edges) == 1
    assert max_in_edges[0].data.data == "maxvcfl"
    max_in_edge = max_in_edges[0]
    assert isinstance(max_in_edge.src, dace.nodes.LibraryNode)
    lib_node = max_in_edge.src
    max_node = max_in_edge.dst
    inpu_in_edges = parent.in_edges(max_in_edge.src)
    assert len(inpu_in_edges) == 1
    assert inpu_in_edges[0].data.data == "maxvcfl_arr"
    inpu_in_edge = inpu_in_edges[0]
    assert isinstance(inpu_in_edge.src, dace.nodes.AccessNode)
    input_node = inpu_in_edge.src

    # Create a single ietarion map
    map_entry, map_exit = parent.add_map(
        "map_l488_c488",
        dict(i="0:1"),
        schedule=dace.ScheduleType.GPU_Device,
    )
    map_entry.add_in_connector("IN_1")
    map_exit.add_out_connector("OUT_2")
    map_entry.add_out_connector("OUT_1")
    map_exit.add_in_connector("IN_2")

    # Connect the input and output nodes to the map
    parent.add_edge(input_node, None, map_entry, "IN_1", copy.deepcopy(inpu_in_edge.data))
    parent.add_edge(map_exit, "OUT_2", output_node, None, copy.deepcopy(out_edge.data))
    parent.add_edge(map_entry, "OUT_1", lib_node, "in_arr", copy.deepcopy(inpu_in_edge.data))
    parent.add_edge(tasklet, "vcflmax_out_0", map_exit, "IN_2", copy.deepcopy(out_edge.data))

    parent.remove_edge(inpu_in_edge)
    parent.remove_edge(out_edge)


    # We also need to wrap the tasklet T_l462_c462 which initializes maxvcfl
    tasklet, parent = find_node_by_name(sdfg, "T_l462_c462")
    assert parent.in_degree(tasklet) == 0
    out_edges = parent.out_edges(tasklet)
    assert len(out_edges) == 1
    assert out_edges[0].data.data == "maxvcfl"
    out_edge = out_edges[0]
    output_node = out_edge.dst

    # Create a single ietarion map
    map_entry, map_exit = parent.add_map(
        "map_l462_c462",
        dict(i="0:1"),
        schedule=dace.ScheduleType.GPU_Device,
    )
    map_exit.add_out_connector("OUT_2")
    map_exit.add_in_connector("IN_2")

    # Add empty connection to the tasklet
    parent.add_edge(map_entry, None, tasklet, None, dace.Memlet())

    # Connect the output node to the map
    parent.add_edge(map_exit, "OUT_2", output_node, None, copy.deepcopy(out_edge.data))
    parent.add_edge(tasklet, "maxvcfl_out", map_exit, "IN_2", copy.deepcopy(out_edge.data))

    parent.remove_edge(out_edge)

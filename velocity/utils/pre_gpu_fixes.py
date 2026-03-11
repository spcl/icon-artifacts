import dace
from dace.sdfg.state import ConditionalBlock
from dace.transformation.dataflow.map_collapse import MapCollapse
from utils import find_node_by_name
from utils import MapStateFission
from dace.sdfg.utils import set_nested_sdfg_parent_references
from copy import deepcopy

def pre_gpu_fix(sdfg: dace.SDFG):
    step_1(sdfg)
    target_state = step_2(sdfg)
    step_3(sdfg, target_state)
    step_4(sdfg)

def step_4(sdfg: dace.SDFG):
    """
    Avoid out_val_0 having the same name in scalar and array form.
    """
    condblock, _ = find_node_by_name(sdfg, "Conditional_l_553_c_553")

    # Change condition in the conditional block
    assert isinstance(condblock, ConditionalBlock)
    block_state = condblock.parent_graph.parent

    # Find the nested SDFG in the state with one output
    for node in block_state.nodes():
        if isinstance(node, dace.nodes.NestedSDFG):
            if  len(node.out_connectors) == 1:
                nsdfg = node
            else:
                second_nsdfg = node
    inner_sdfg = condblock.parent_graph
    assert isinstance(nsdfg, dace.nodes.NestedSDFG)
    condblock.branches[0] = (dace.nodes.CodeBlock("(not ((out_val_0 == 0) == 1))"), condblock.branches[0][1])

    # Change the array out_val_0 to scalar_out_val_0
    #inner_sdfg.add_array("out_val_0", dtype=nsdfg.sdfg.arrays["out_val_0"].dtype, shape=nsdfg.sdfg.arrays["out_val_0"].shape, transient=False)
    #inner_sdfg.remove_data("out_val_0")
    #nsdfg.add_in_connector("out_val_0")
    #list(block_state.in_edges_by_connector(nsdfg, "out_val_0"))[0].dst_conn = "scalar_out_val_0"
    #nsdfg.remove_in_connector("out_val_0")

    # Second nsdfg
    #second_nsdfg.add_in_connector("scalar_out_val_0")
    #list(block_state.in_edges_by_connector(second_nsdfg, "out_val_0"))[0].dst_conn = "scalar_out_val_0"
    #second_nsdfg.remove_in_connector("out_val_0")
    for node in second_nsdfg.sdfg.nodes():
        if isinstance(node, ConditionalBlock):
            second_cond_block = node
            break
    #second_nsdfg.sdfg.add_scalar("scalar_out_val_0", dtype=second_nsdfg.sdfg.arrays["out_val_0"].dtype, transient=False)
    #second_nsdfg.sdfg.remove_data("out_val_0")
    second_cond_block.branches[0] = (dace.nodes.CodeBlock("((not ((out_val_0 == 0)==1)) and (_if_cond_18 == 1))"), second_cond_block.branches[0][1])

    sdfg.validate()
def step_1(sdfg: dace.SDFG):
    """

    """
    library_node_reduction, library_node_reduction_parent = find_node_by_name(sdfg, "reduce_sum_to_address")
    assert isinstance(library_node_reduction, dace.nodes.LibraryNode)

    # Get the library node's in edges
    in_edges = library_node_reduction_parent.in_edges(library_node_reduction)
    assert len(in_edges) == 2
    cfl_edge = in_edges[0] if in_edges[0].src.data == "cfl_clipping" else in_edges[1]
    cfl = cfl_edge.src
    assert cfl.data == "cfl_clipping"
    reduction_sum_size_edge = in_edges[0] if in_edges[0].src.data == "reduce_sum_to_address_size" else in_edges[1]
    reduction_sum_size = reduction_sum_size_edge.src
    assert reduction_sum_size.data == "reduce_sum_to_address_size"

    tasklet_before_reduction_edges = library_node_reduction_parent.in_edges(reduction_sum_size)[0]
    tasklet_before_reduction = tasklet_before_reduction_edges.src
    assert tasklet_before_reduction.label == "size_reduce_sum_to_address"

    # Get the library node's out edges
    out_edges = library_node_reduction_parent.out_edges(library_node_reduction)
    assert len(out_edges) == 1
    reduction_sum_edge = out_edges[0]
    reduction_sum = reduction_sum_edge.dst
    assert reduction_sum.data == "out_val_0"
    new_cfl = deepcopy(cfl)
    # Split into seprate state
    new_state = library_node_reduction_parent.sdfg.add_state_after(library_node_reduction_parent)
    new_state.add_nodes_from([library_node_reduction, new_cfl , reduction_sum_size, tasklet_before_reduction,reduction_sum])
    new_state.add_edge(new_cfl, cfl_edge.src_conn, cfl_edge.dst, cfl_edge.dst_conn, cfl_edge.data)
    new_state.add_edge(reduction_sum_size_edge.src, reduction_sum_size_edge.src_conn, reduction_sum_size_edge.dst, reduction_sum_size_edge.dst_conn, reduction_sum_size_edge.data)
    new_state.add_edge(tasklet_before_reduction_edges.src, tasklet_before_reduction_edges.src_conn, tasklet_before_reduction_edges.dst, tasklet_before_reduction_edges.dst_conn, tasklet_before_reduction_edges.data)
    new_state.add_edge(reduction_sum_edge.src, reduction_sum_edge.src_conn, reduction_sum_edge.dst, reduction_sum_edge.dst_conn, reduction_sum_edge.data)



    # remove things from the first state
    library_node_reduction_parent.remove_edge(cfl_edge)
    library_node_reduction_parent.remove_edge(reduction_sum_size_edge)
    library_node_reduction_parent.remove_edge(tasklet_before_reduction_edges)
    library_node_reduction_parent.remove_edge(reduction_sum_edge)
    library_node_reduction_parent.remove_nodes_from([reduction_sum_size, tasklet_before_reduction, library_node_reduction, reduction_sum])



    # Distribute the outer map and duplicate the inside
    outer_state = library_node_reduction_parent.sdfg.parent
    state_copy_1 = outer_state.parent_graph.add_state_after(outer_state)
    map_of_copies = {}
    # Copy all the elements of the state to the copy
    for node in outer_state.nodes():
        node_copy = deepcopy(node)
        map_of_copies[node] = node_copy
        state_copy_1.add_node(node_copy)

    for edge in outer_state.edges():
        src = edge.src
        dst = edge.dst
        src_copy = map_of_copies[src]
        dst_copy = map_of_copies[dst]
        state_copy_1.add_edge(src_copy, edge.src_conn, dst_copy, edge.dst_conn, deepcopy(edge.data))

    state_copy_2 = outer_state.parent_graph.add_state_after(state_copy_1)
    map_of_copies = {}
    # Copy all the elements of the state to the copy
    for node in outer_state.nodes():
        node_copy = deepcopy(node)
        map_of_copies[node] = node_copy
        state_copy_2.add_node(node_copy)

    for edge in outer_state.edges():
        src = edge.src
        dst = edge.dst
        src_copy = map_of_copies[src]
        dst_copy = map_of_copies[dst]
        state_copy_2.add_edge(src_copy, edge.src_conn, dst_copy, edge.dst_conn, deepcopy(edge.data))

    # ****** First state ******
    for node in outer_state.nodes():
        if isinstance(node, dace.nodes.NestedSDFG):
            for s in node.sdfg.nodes():
                if isinstance(s, dace.SDFGState):
                    if s.label != "single_state_body":
                        node.sdfg.remove_node(s)
                        # remove symbols if necessary
                        for symb in node.sdfg.free_symbols:
                            if symb not in node.symbol_mapping:
                                node.sdfg.remove_symbol(symb)
                elif isinstance(s, ConditionalBlock):
                    node.sdfg.remove_node(s)
                    for symb in node.sdfg.free_symbols:
                            if symb not in node.symbol_mapping:
                                node.sdfg.remove_symbol(symb)
                else:
                    raise ValueError("Unexpected node type")
        elif isinstance(node, dace.nodes.MapEntry) and "_for_it_38" in node.params:
            # Delete the map entry and exit nodes
            map_entry = node
            out_edges = outer_state.out_edges(map_entry)

            assert len(out_edges) == 2
            assert isinstance(out_edges[0].dst, dace.nodes.Tasklet)
            map_exit = outer_state.exit_node(map_entry)
            exit_out_edges = outer_state.out_edges(map_exit)
            assert len(exit_out_edges) == 1
            assert isinstance(exit_out_edges[0].dst, dace.nodes.AccessNode)
            outer_state.remove_node(exit_out_edges[0].dst)
            outer_state.remove_node(out_edges[0].dst)
            outer_state.remove_node(map_entry)
            outer_state.remove_node(map_exit)
        elif isinstance(node, dace.nodes.LibraryNode):
            in_edges = outer_state.in_edges(node)
            out_edges = outer_state.out_edges(node)
            assert len(in_edges) == 2
            assert len(out_edges) == 1
            assert isinstance(in_edges[0].src, dace.nodes.AccessNode)
            assert isinstance(in_edges[1].src, dace.nodes.AccessNode)
            assert isinstance(out_edges[0].dst, dace.nodes.AccessNode)
            reduce_node = in_edges[0].src if in_edges[0].src.data == "reduce_maxZ_to_scalar_size" else in_edges[1].src
            reduce_tasklet = outer_state.in_edges(reduce_node)[0].src
            assert isinstance(reduce_tasklet, dace.nodes.Tasklet)
            outer_state.remove_node(out_edges[0].dst)
            outer_state.remove_node(reduce_node)
            outer_state.remove_node(reduce_tasklet)
            outer_state.remove_node(node)
        elif isinstance(node, dace.nodes.MapEntry) and "_for_it_35" in node.params:
            # we need to change the output to only be out_val_0
            map_entry_it_35 = node

    # prune outputs
    map_exit = outer_state.exit_node(map_entry_it_35)
    out_edges = outer_state.out_edges(map_exit)
    # assert len(out_edges) == 3
    # remove all the target nodes
    for out_edge in out_edges:
        if out_edge.dst.data == "cfl_clipping":
            continue
        outer_state.remove_node(out_edge.dst)

    # remove all the in connectors
    in_edges = outer_state.in_edges(map_exit)
    nsdfg = in_edges[0].src
    assert isinstance(nsdfg, dace.nodes.NestedSDFG)
    for in_edge in in_edges:
        if in_edge.src_conn == "cfl_clipping":
            continue
        nsdfg.remove_out_connector(in_edge.src_conn)
        # need to also remove the array from the SDFG
        if in_edge.src_conn not in nsdfg.in_connectors:
            nsdfg.sdfg.remove_data(in_edge.src_conn)
        map_exit.remove_in_connector(in_edge.dst_conn)
        map_exit.remove_out_connector(in_edge.dst_conn.replace("IN_", "OUT_"))
        # remove the edges
        outer_state.remove_edge(in_edge)

    # prune inputs
    in_edges = outer_state.in_edges(map_entry_it_35)
    assert len(in_edges) == 5
    # remove all the source nodes
    no_remove = ["z_w_con_c", "cfl_w_limit", "__CG_p_metrics__m_ddqz_z_half", "cfl_clipping"]
    for in_edge in in_edges:
        if in_edge.src.data in no_remove:
            continue
        outer_state.remove_node(in_edge.src)

    out_edges = outer_state.out_edges(map_entry_it_35)
    assert len(out_edges) == 5
    for out_edge in out_edges:
        if out_edge.dst_conn in no_remove:
            continue
        nsdfg.remove_in_connector(out_edge.dst_conn)
        # need to also remove the array from the SDFG
        if out_edge.dst_conn not in nsdfg.out_connectors:
            nsdfg.sdfg.remove_data(out_edge.dst_conn)
        map_entry_it_35.remove_out_connector(out_edge.src_conn)
        map_entry_it_35.remove_in_connector(out_edge.src_conn.replace( "OUT_", "IN_"))
        # remove the edges
        outer_state.remove_edge(out_edge)

    # ****** Second state ******
    for node in state_copy_1.nodes():
        if isinstance(node, dace.nodes.NestedSDFG):
            for s in node.sdfg.nodes():
                if isinstance(s, dace.SDFGState):
                    if s.label != "block":
                        node.sdfg.remove_node(s)
                        # remove symbols if necessary
                        for symb in node.sdfg.free_symbols:
                            if symb not in node.symbol_mapping:
                                node.sdfg.remove_symbol(symb)
                elif isinstance(s, ConditionalBlock):
                    node.sdfg.remove_node(s)
                    for symb in node.sdfg.free_symbols:
                            if symb not in node.symbol_mapping:
                                node.sdfg.remove_symbol(symb)
                else:
                    raise ValueError("Unexpected node type")
        elif isinstance(node, dace.nodes.MapEntry) and "_for_it_38" in node.params:
            # Delete the map entry and exit nodes
            map_entry = node
            out_edges = state_copy_1.out_edges(map_entry)

            assert len(out_edges) == 2
            assert isinstance(out_edges[0].dst, dace.nodes.Tasklet)
            map_exit = state_copy_1.exit_node(map_entry)
            exit_out_edges = state_copy_1.out_edges(map_exit)
            assert len(exit_out_edges) == 1
            assert isinstance(exit_out_edges[0].dst, dace.nodes.AccessNode)
            state_copy_1.remove_node(exit_out_edges[0].dst)
            state_copy_1.remove_node(out_edges[0].dst)
            state_copy_1.remove_node(map_entry)
            state_copy_1.remove_node(map_exit)
        elif isinstance(node, dace.nodes.LibraryNode):
            in_edges = state_copy_1.in_edges(node)
            out_edges = state_copy_1.out_edges(node)
            assert len(in_edges) == 2
            assert len(out_edges) == 1
            assert isinstance(in_edges[0].src, dace.nodes.AccessNode)
            assert isinstance(in_edges[1].src, dace.nodes.AccessNode)
            assert isinstance(out_edges[0].dst, dace.nodes.AccessNode)
            reduce_node = in_edges[0].src if in_edges[0].src.data == "reduce_maxZ_to_scalar_size" else in_edges[1].src
            reduce_tasklet = state_copy_1.in_edges(reduce_node)[0].src
            assert isinstance(reduce_tasklet, dace.nodes.Tasklet)
            state_copy_1.remove_node(out_edges[0].dst)
            state_copy_1.remove_node(reduce_node)
            state_copy_1.remove_node(reduce_tasklet)
            state_copy_1.remove_node(node)
        elif isinstance(node, dace.nodes.MapEntry) and "_for_it_35" in node.params:
            # we need to change the output to only be out_val_0
            map_entry_it_35 = node

    # prune outputs
    map_exit = state_copy_1.exit_node(map_entry_it_35)
    out_edges = state_copy_1.out_edges(map_exit)
    # assert len(out_edges) == 4
    # remove all the target nodes
    for out_edge in out_edges:
        state_copy_1.remove_node(out_edge.dst)

    # remove all the in connectors
    in_edges = state_copy_1.in_edges(map_exit)
    nsdfg = in_edges[0].src
    assert isinstance(nsdfg, dace.nodes.NestedSDFG)
    for in_edge in in_edges:
        nsdfg.remove_out_connector(in_edge.src_conn)
        # need to also remove the array from the SDFG
        if in_edge.src_conn not in nsdfg.in_connectors:
            nsdfg.sdfg.remove_data(in_edge.src_conn)
        map_exit.remove_in_connector(in_edge.dst_conn)
        map_exit.remove_out_connector(in_edge.dst_conn.replace("IN_", "OUT_"))
        # remove the edges
        state_copy_1.remove_edge(in_edge)

    # create an array of size 1
    existing_array = nsdfg.sdfg.arrays["out_val_0"]
    new_array = dace.data.Array(dtype=existing_array.dtype, shape=existing_array.shape, transient=False, storage=dace.dtypes.StorageType.GPU_Global)
    nsdfg.sdfg.arrays["out_val_0"] = new_array
    #add out_val_0 to the map exit
    nsdfg.add_out_connector("out_val_0")
    map_exit.add_in_connector("IN_1")
    map_exit.add_out_connector("OUT_1")
    state_copy_1.add_edge(nsdfg, "out_val_0", map_exit, "IN_1", dace.Memlet(expr="out_val_0[_for_it_35 - 1]"))
    new_shape = ["89"]
    new_an = state_copy_1.add_array("out_val_0", dtype=nsdfg.sdfg.arrays["out_val_0"].dtype, shape=new_shape, transient=True, storage=dace.dtypes.StorageType.GPU_Global)
    # state_copy_1.add_node(new_an)
    state_copy_1.add_edge(map_exit, "OUT_1", new_an, None, dace.Memlet(expr="out_val_0[0:89]"))

    # prune inputs
    in_edges = state_copy_1.in_edges(map_entry_it_35)
    assert len(in_edges) == 5
    # remove all the source nodes
    for in_edge in in_edges:
        if in_edge.src.data == "cfl_clipping":
            continue
        state_copy_1.remove_node(in_edge.src)

    out_edges = state_copy_1.out_edges(map_entry_it_35)
    assert len(out_edges) == 5
    for out_edge in out_edges:
        if out_edge.dst_conn == "cfl_clipping":
            continue
        nsdfg.remove_in_connector(out_edge.dst_conn)
        # need to also remove the array from the SDFG
        if out_edge.dst_conn not in nsdfg.out_connectors:
            nsdfg.sdfg.remove_data(out_edge.dst_conn)
        map_entry_it_35.remove_out_connector(out_edge.src_conn)
        map_entry_it_35.remove_in_connector(out_edge.src_conn.replace( "OUT_", "IN_"))
        # remove the edges
        state_copy_1.remove_edge(out_edge)

    # ****** Third state ******
    for node in state_copy_2.nodes():
        if isinstance(node, dace.nodes.NestedSDFG):
            nsdfg = node
            for s in node.sdfg.nodes():
                if isinstance(s, dace.SDFGState):
                    if s.label == "block":
                        # Remove all the nodes inside
                        for n in s.nodes():
                            s.remove_node(n)
                    else:
                        node.sdfg.remove_node(s)

                elif isinstance(s, ConditionalBlock):
                    pass
                else:
                    raise ValueError("Unexpected node type")
            # remove symbols if necessary
            for symb in node.sdfg.free_symbols:
                if symb not in node.symbol_mapping:
                    node.sdfg.remove_symbol(symb)
        elif isinstance(node, dace.nodes.MapEntry) and "_for_it_35" in node.params:
            # Add out_val_0 to the map entry
            map_entry = node
            an = state_copy_2.add_access("out_val_0")
            nsdfg.sdfg.arrays["out_val_0"].transient = False
            nsdfg.sdfg.arrays["out_val_0"].storage = dace.dtypes.StorageType.GPU_Global
            map_entry.add_in_connector("IN_6")
            map_entry.add_out_connector("OUT_6")
            state_copy_2.add_edge(an, None, map_entry, "IN_6", dace.Memlet(expr="out_val_0[0:89]"))
            nsdfg.add_in_connector("out_val_0")
            state_copy_2.add_edge(map_entry, "OUT_6", nsdfg, "out_val_0", dace.Memlet(expr="out_val_0[_for_it_35 - 1]"))

    set_nested_sdfg_parent_references(sdfg)
    sdfg.validate()
    sdfg.reset_cfg_list()

    # assert False
    sdfg.validate()
    sdfg.apply_transformations_repeated(MapCollapse)

def step_2(sdfg: dace.SDFG):
    reduction, reduction_parent = find_node_by_name(sdfg, "reduce_scan")
    # Get the input
    in_edges = reduction_parent.in_edges(reduction)
    assert len(in_edges) == 2
    in_edge = in_edges[0] if in_edges[0].src.data == "cfl_clipping" else in_edges[1]
    assert in_edge.src.data == "cfl_clipping"
    reduction_sum_size_edge = in_edges[0] if in_edges[0].src.data == "reduce_scan_size_0" else in_edges[1]
    reduction_sum_size = reduction_sum_size_edge.src
    assert reduction_sum_size.data == "reduce_scan_size_0"
    # Get the output
    out_edges = reduction_parent.out_edges(reduction)
    assert len(out_edges) == 1
    out_edge = out_edges[0]
    assert out_edge.dst.data == "levmask"
    tasklet_before_reduction_edges = reduction_parent.in_edges(reduction_sum_size)[0]
    tasklet_before_reduction = tasklet_before_reduction_edges.src
    assert tasklet_before_reduction.label == "size_reduce_scan"

    # get the conditional block parent
    cond_block = reduction_parent.parent_graph.parent_graph
    parent_sdfg = reduction_parent.parent
    assert isinstance(parent_sdfg, dace.SDFG)

    # Duplicate the conditional block
    cond_block_copy = deepcopy(cond_block)
    parent_sdfg.add_node(cond_block_copy)
    cond_block.branches[0] = (dace.nodes.CodeBlock("(not ((out_val_0[_for_it_35 - 1] == 0) == 1))"), cond_block.branches[0][1])
    # assert False
    # Get the condition state
    cond_state_edge = parent_sdfg.in_edges(cond_block)[0]
    cond_state = cond_state_edge.src
    assert isinstance(cond_state, dace.SDFGState)
    parent_sdfg.add_edge(cond_state, cond_block_copy, deepcopy(cond_state_edge.data))

    for node in reduction_parent.nodes():
        if node not in [reduction, out_edge.dst, in_edge.src, reduction_sum_size, tasklet_before_reduction]:
             reduction_parent.remove_node(node)

    for node, parent in cond_block_copy.all_nodes_recursive():
        if isinstance(node, dace.nodes.LibraryNode):
            parent.remove_node(node)
        elif isinstance(node, dace.nodes.AccessNode) and (node.data == "levmask" or node.data == "reduce_scan_size_0"):
            parent.remove_node(node)
        elif isinstance(node, dace.nodes.Tasklet) and node.label == "size_reduce_scan":
            parent.remove_node(node)

    inside_state = list(cond_block_copy.all_states())
    assert len(inside_state) == 1
    inside_state = inside_state[0]
    inside_state_copy = deepcopy(inside_state)
    parent_sdfg.add_edge(cond_state, inside_state_copy, deepcopy(cond_state_edge.data))

    # Get the nested SDFG condition inside to change it
    for node, parent in inside_state_copy.all_nodes_recursive():
        if isinstance(node, ConditionalBlock) and len(node.branches) == 1:
            # print(f"Condition: {node.branches[0]}")
            # assert False
            new_condition = "(not ((clip_count == 0)==1)) and (_if_cond_18 == 1)"
            node.branches[0] = (dace.nodes.CodeBlock(new_condition), node.branches[0][1])
        if isinstance(node, dace.nodes.NestedSDFG):
            node.symbol_mapping["clip_count"] = "out_val_0"
    parent_sdfg.remove_node(cond_block_copy)
    set_nested_sdfg_parent_references(sdfg)
    sdfg.validate()
    return parent_sdfg.parent

def step_3(sdfg :dace.SDFG, target_state: dace.SDFGState):
    """
    """
    assert isinstance(target_state, dace.SDFGState)
    edge_map = {}
    for node in target_state.nodes():
        if node.label == "T_l546_c546":
            target_state.remove_node(node)
        # elif isinstance(node, dace.nodes.AccessNode) and node.data == "maxvcfl":
        #     target_state.remove_node(node)
        else:
            copy_node = deepcopy(node)
            target_state.add_node(copy_node)
            edge_map[node] = copy_node

    for edge in target_state.edges():
        src = edge.src
        dst = edge.dst
        src_copy = edge_map[src]
        dst_copy = edge_map[dst]
        target_state.add_edge(src_copy, edge.src_conn, dst_copy, edge.dst_conn, deepcopy(edge.data))

    i = 0
    for node in target_state.nodes():
        if isinstance(node, dace.nodes.NestedSDFG):
            if i==0:
                nsdfg_conditional = node
                outside_state = [n for n in node.sdfg.nodes() if isinstance(n, dace.SDFGState) and n.label == "block_0"][0]
                node.sdfg.remove_node(outside_state)
                i += 1
            else:
                nsdfg_map = node
                outside_block = [n for n in node.sdfg.nodes() if isinstance(n, ConditionalBlock)][0]
                node.sdfg.remove_node(outside_block)
                i += 1

    # put the clip count assignement inside the innermost map
    for edge, parent in nsdfg_map.sdfg.all_edges_recursive():
        if isinstance(edge.data, dace.sdfg.InterstateEdge) and len(edge.data.assignments) == 0 and isinstance(edge.dst, dace.SDFGState):
            parent.remove_node(edge.src)

        if isinstance(edge.data, dace.sdfg.InterstateEdge) and "_if_cond_18" in edge.data.assignments.keys():
            edge.data.assignments["clip_count"] = "out_val_0"

    set_nested_sdfg_parent_references(sdfg)
    for node in target_state.nodes():
        if isinstance(node, dace.nodes.MapEntry) and "_for_it_35" in node.map.params:
            in_edges = target_state.in_edges(node)
            for edge in in_edges:
                if edge.src.data == "cfl_w_limit":
                    target_state.remove_node(edge.src)
                    node.remove_in_connector(edge.dst_conn)
                    out_edge = list(target_state.out_edges_by_connector(node, edge.dst_conn.replace("IN_", "OUT_")))[0]
                    node.remove_out_connector(edge.dst_conn.replace("IN_", "OUT_"))
                    out_edge.dst.remove_in_connector(out_edge.dst_conn)
                    out_edge.dst.sdfg.remove_data(out_edge.dst_conn)
                    target_state.remove_edge(out_edge)
        if isinstance(node, dace.nodes.MapExit) and "_for_it_35" in node.map.params:
            # Get incoming edges to the exit
            in_edges = target_state.in_edges(node)
            nnode = in_edges[0].src
            assert isinstance(nnode, dace.nodes.NestedSDFG)
            if len(nnode.sdfg.nodes()) == 1:
                # State only
                for edge in in_edges:
                    out_edge = list(target_state.out_edges_by_connector(node, edge.dst_conn.replace("IN_", "OUT_")))[0]
                    if out_edge.dst.data == "levmask":
                            target_state.remove_node(out_edge.dst)
                            node.remove_in_connector(edge.dst_conn)
                            node.remove_out_connector(edge.dst_conn.replace("IN_", "OUT_"))
                            edge.src.remove_out_connector(edge.src_conn)
                            if out_edge.dst.data not in nnode.in_connectors:
                                edge.src.sdfg.remove_data(edge.src_conn)
                            target_state.remove_edge(edge)
            elif len(nnode.sdfg.nodes()) == 2:
                for edge in in_edges:
                    out_edge = list(target_state.out_edges_by_connector(node, edge.dst_conn.replace("IN_", "OUT_")))[0]
                    if out_edge.dst.data != "levmask":
                        delete_nodes = []
                        for e in target_state.out_edges(out_edge.dst):
                            delete_nodes = target_state.bfs_nodes(out_edge.dst)
                        target_state.remove_nodes_from(delete_nodes)
                        target_state.remove_node(out_edge.dst)
                        node.remove_in_connector(edge.dst_conn)
                        node.remove_out_connector(edge.dst_conn.replace("IN_", "OUT_"))
                        edge.src.remove_out_connector(edge.src_conn)
                        if out_edge.dst.data not in nnode.in_connectors:
                            edge.src.sdfg.remove_data(edge.src_conn)
                        target_state.remove_edge(edge)
            else:
                raise ValueError("Unexpected number of nodes in nested SDFG")

    map_state = nsdfg_map.sdfg.states()[0]
    for node in map_state.nodes():
        if isinstance(node, dace.nodes.MapEntry):
            an = map_state.add_access("out_val_0")
            node.add_in_connector("IN_5")
            node.add_out_connector("OUT_5")
            map_state.add_edge(an, None, node, "IN_5", dace.Memlet(expr="out_val_0[_for_it_35 - 1]"))
            map_nsdfg = map_state.out_edges(node)[0].dst
            assert isinstance(map_nsdfg, dace.nodes.NestedSDFG)
            map_nsdfg.add_in_connector("out_val_0")
            map_state.add_edge(node, "OUT_5", map_nsdfg, "out_val_0", dace.Memlet(expr="out_val_0[_for_it_35 - 1]"))

    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.AccessNode):
            if g.in_degree(n) == 0 and g.out_degree(n) == 0:
                g.remove_node(n)

    sdfg.reset_cfg_list()
    sdfg.save("x.sdfg")
    
    sdfg.simplify(validate=False)
    
    # sdfg.apply_transformations_repeated(MapCollapse, validate=False, permissive=True)
    target_state.parent_graph.apply_transformations_repeated(MapCollapse, validate=False, permissive=True)
    node, parent = find_node_by_name(sdfg, "T_l562_c562")
    #raise Exception("out_val_0" in nsdfg_map.sdfg.arrays)
    #parent.parent.add_scalar("out_val_0", dtype=dace.int32)
    import copy
    parent.parent.add_datadesc("out_val_0", copy.deepcopy(nsdfg_map.sdfg.arrays["out_val_0"]))
    sdfg.validate()
    # assert False


def make_arrays_persistent(sdfg: dace.SDFG):
    # Make stuff persistent
    move_persistent = ["gpu_levelmask", "gpu_maxvcfl_arr", "gpu_z_w_v",
                        "gpu_cfl_clipping", "gpu_z_w_con_c", "gpu_levmask",
                        "gpu_zeta", "gpu_z_w_con_c_full", "gpu_out_val_0",
                        "gpu_z_v_grad_w", "gpu_z_ekinh", "gpu_z_w_concorr_mc",
                        "vcflmax", "out_val_0"
                       ]
    for node, parent in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode) and node.data in move_persistent :
            parent.sdfg.arrays[node.data].lifetime = dace.dtypes.AllocationLifetime.Persistent
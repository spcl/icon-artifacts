import dace
from dace.sdfg.state import ConditionalBlock
from utils import find_node_by_name
from utils import MapStateFission
from dace.sdfg.utils import set_nested_sdfg_parent_references
from copy import deepcopy as dc

def pre_gpu_fix(sdfg: dace.SDFG):
    """
    
    """
    library_node_reduction, library_node_reduction_parnet = find_node_by_name(sdfg, "reduce_sum")
    assert isinstance(library_node_reduction, dace.nodes.LibraryNode)
    
    # Get the library node's in edges
    in_edges = library_node_reduction_parnet.in_edges(library_node_reduction)
    assert len(in_edges) == 2
    cfl_edge = in_edges[0] if in_edges[0].src.data == "cfl_clipping" else in_edges[1]
    cfl = cfl_edge.src
    assert cfl.data == "cfl_clipping"
    reduction_sum_size_edge = in_edges[0] if in_edges[0].src.data == "reduce_sum_size" else in_edges[1]
    reduction_sum_size = reduction_sum_size_edge.src
    assert reduction_sum_size.data == "reduce_sum_size"
    
    tasklet_before_reduction_edges = library_node_reduction_parnet.in_edges(reduction_sum_size)[0]
    tasklet_before_reduction = tasklet_before_reduction_edges.src
    assert tasklet_before_reduction.label == "size_reduce_sum"
    
    # Get the library node's out edges
    out_edges = library_node_reduction_parnet.out_edges(library_node_reduction)
    assert len(out_edges) == 1
    reduction_sum_edge = out_edges[0]
    reduction_sum = reduction_sum_edge.dst
    assert reduction_sum.data == "out_val_0"
    new_cfl = dc(cfl)
    # Split into seprate state
    new_state = library_node_reduction_parnet.sdfg.add_state_after(library_node_reduction_parnet)
    new_state.add_nodes_from([library_node_reduction, new_cfl , reduction_sum_size, tasklet_before_reduction,reduction_sum])
    new_state.add_edge(new_cfl, cfl_edge.src_conn, cfl_edge.dst, cfl_edge.dst_conn, cfl_edge.data)
    new_state.add_edge(reduction_sum_size_edge.src, reduction_sum_size_edge.src_conn, reduction_sum_size_edge.dst, reduction_sum_size_edge.dst_conn, reduction_sum_size_edge.data)
    new_state.add_edge(tasklet_before_reduction_edges.src, tasklet_before_reduction_edges.src_conn, tasklet_before_reduction_edges.dst, tasklet_before_reduction_edges.dst_conn, tasklet_before_reduction_edges.data)
    new_state.add_edge(reduction_sum_edge.src, reduction_sum_edge.src_conn, reduction_sum_edge.dst, reduction_sum_edge.dst_conn, reduction_sum_edge.data)
    
    
    # remove things from the first state
    library_node_reduction_parnet.remove_edge(cfl_edge)
    library_node_reduction_parnet.remove_edge(reduction_sum_size_edge)
    library_node_reduction_parnet.remove_edge(tasklet_before_reduction_edges)
    library_node_reduction_parnet.remove_edge(reduction_sum_edge)
    library_node_reduction_parnet.remove_nodes_from([reduction_sum_size, tasklet_before_reduction, library_node_reduction, reduction_sum])
    
    
    # Distribute the outer map and duplicate the inside
    outer_state = library_node_reduction_parnet.sdfg.parent
    state_copy_1 = outer_state.parent.add_state_after(outer_state)
    map_of_copies = {}
    # Copy all the elements of the state to the copy
    for node in outer_state.nodes():
        node_copy = dc(node)
        map_of_copies[node] = node_copy
        state_copy_1.add_node(node_copy)
    
    for edge in outer_state.edges():
        src = edge.src
        dst = edge.dst
        src_copy = map_of_copies[src]
        dst_copy = map_of_copies[dst]
        state_copy_1.add_edge(src_copy, edge.src_conn, dst_copy, edge.dst_conn, dc(edge.data))
        
    state_copy_2 = outer_state.parent.add_state_after(state_copy_1)
    map_of_copies = {}
    # Copy all the elements of the state to the copy
    for node in outer_state.nodes():
        node_copy = dc(node)
        map_of_copies[node] = node_copy
        state_copy_2.add_node(node_copy)
    
    for edge in outer_state.edges():
        src = edge.src
        dst = edge.dst
        src_copy = map_of_copies[src]
        dst_copy = map_of_copies[dst]
        state_copy_2.add_edge(src_copy, edge.src_conn, dst_copy, edge.dst_conn, dc(edge.data))
    
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
            reduce_node = in_edges[0].src if in_edges[0].src.data == "reduce_maxZ_size_0" else in_edges[1].src
            reduce_tasklet = outer_state.in_edges(reduce_node)[0].src
            assert isinstance(reduce_tasklet, dace.nodes.Tasklet)
            outer_state.remove_node(out_edges[0].dst)
            outer_state.remove_node(reduce_node)
            outer_state.remove_node(reduce_tasklet)
            outer_state.remove_node(node)
            
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
            reduce_node = in_edges[0].src if in_edges[0].src.data == "reduce_maxZ_size_0" else in_edges[1].src
            reduce_tasklet = state_copy_1.in_edges(reduce_node)[0].src
            assert isinstance(reduce_tasklet, dace.nodes.Tasklet)
            state_copy_1.remove_node(out_edges[0].dst)
            state_copy_1.remove_node(reduce_node)
            state_copy_1.remove_node(reduce_tasklet)
            state_copy_1.remove_node(node)
            
            
    # ****** Third state ******
    for node in state_copy_2.nodes():
        if isinstance(node, dace.nodes.NestedSDFG):
            for s in node.sdfg.nodes():
                if isinstance(s, dace.SDFGState):
                    node.sdfg.remove_node(s)
                    
                elif isinstance(s, ConditionalBlock):
                    pass
                else:
                    raise ValueError("Unexpected node type")
            # remove symbols if necessary
            for symb in node.sdfg.free_symbols:
                if symb not in node.symbol_mapping:
                    node.sdfg.remove_symbol(symb)
            
    set_nested_sdfg_parent_references(sdfg)
    sdfg.validate()
    sdfg.reset_cfg_list()
    # sdfg.save("debug.sdfg")
    # assert False
    
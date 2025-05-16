import dace
from dace.sdfg.state import ConditionalBlock
from dace.transformation.dataflow.map_collapse import MapCollapse
from utils import find_node_by_name
from utils import MapStateFission
from dace.sdfg.utils import set_nested_sdfg_parent_references
from copy import deepcopy as dc
from utils import prune_unused_inputs_outputs

def move_ifs_inside_maps(sdfg: dace.SDFG):
    map_for_44(sdfg)
    map_for_52(sdfg)
    
def map_for_44(sdfg: dace.SDFG):
    # Get the necessary nodes
    try:
        dif_local, dif_parent = find_node_by_name(sdfg, "tmp_call_10")
    except AssertionError:
        return
    conditional_block = dif_parent.parent_graph.parent_graph
    cond_in_edges = dif_parent.parent.in_edges(conditional_block)
    assert len(cond_in_edges) == 1
    innerstate_edge = cond_in_edges[0]
    assert "_if_cond_25" in innerstate_edge.data.assignments
    state_to_duplicate: dace.SDFGState = conditional_block.sdfg.parent
    out_cond_block = state_to_duplicate.parent_graph.parent_graph
    outerstate_edge = out_cond_block.sdfg.in_edges(out_cond_block)
    assert len(outerstate_edge) == 1
    outerstate_edge = outerstate_edge[0]
    assert "_if_cond_24" in outerstate_edge.data.assignments
    
    # Make the changes
    nodes_to_remove = []
    for node in out_cond_block.sdfg.nodes():
        nodes_to_remove.append(node)
        
    inner_nsdfg = [node for node in state_to_duplicate.nodes() if isinstance(node, dace.nodes.NestedSDFG)][0]
    inner_nsdfg.sdfg.add_symbol("_if_cond_24", dace.int32)
    inner_nsdfg.symbol_mapping["tmp_struct_symbol_13"] = "tmp_struct_symbol_13"
    # state_to_duplicate.parent.remove_symbol("_if_cond_24")
    # inner_nsdfg.sdfg.add_symbol("_if_cond_24", dace.int32)
    
    outermost_state = outerstate_edge.src.parent.parent
    outer_map_entry = [node for node in outermost_state.nodes() if isinstance(node, dace.nodes.MapEntry) and "_for_it_44" in node.map.params][0]
    outer_nsdfg: dace.nodes.NestedSDFG = outermost_state.out_edges(outer_map_entry)[0].dst
    out_edge = list(outermost_state.in_edges_by_connector(outer_nsdfg, "levmask"))[0]
    in_edge = list(outermost_state.in_edges_by_connector(outer_map_entry, out_edge.src_conn.replace("OUT_", "IN_")))[0]
    inner_map_entry = [node for node in state_to_duplicate.nodes() if isinstance(node, dace.nodes.MapEntry)][0]
    
    an = state_to_duplicate.add_access("levmask")
    conn_number = inner_map_entry.next_connector()
    assert inner_map_entry.add_in_connector(f"IN_{conn_number}")
    assert inner_map_entry.add_out_connector(f"OUT_{conn_number}")
    state_to_duplicate.add_edge(an, None, inner_map_entry, f"IN_{conn_number}", dc(in_edge.data))
    nsddfg = state_to_duplicate.out_edges(inner_map_entry)[0].dst
    assert nsddfg.add_in_connector("levmask")
    state_to_duplicate.add_edge(inner_map_entry, f"OUT_{conn_number}", nsddfg, "levmask", dc(out_edge.data))
    # Add memlet symbol
    
    outer_nsdfg.symbol_mapping["nrdmax_jg"] = "nrdmax_jg"
    inner_nsdfg.sdfg.add_datadesc("levmask", dc(state_to_duplicate.sdfg.arrays["levmask"]))
    # Add assignement
    innerstate_edge.data.assignments["_if_cond_24"] = outerstate_edge.data.assignments["_if_cond_24"]
    new_condition = "(_if_cond_24 == 1) and (_if_cond_25 == 1)"
    conditional_block.branches[0] = (dace.nodes.CodeBlock(new_condition), conditional_block.branches[0][1])
    dup_state = dc(state_to_duplicate)
    out_cond_block.sdfg.add_node(dup_state)
    out_cond_block.sdfg.remove_nodes_from(nodes_to_remove)
    set_nested_sdfg_parent_references(sdfg)
    sdfg.save("debug_move.sdfg")
    sdfg.validate()
    sdfg.simplify()
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.save("debug_move_1.sdfg")
    # assert False

def map_for_52(sdfg: dace.SDFG):
    # Get the necessary nodes
    try:
        dif_local, dif_parent = find_node_by_name(sdfg, "tmp_call_17")
    except AssertionError:
        return
    conditional_block = dif_parent.parent_graph.parent_graph
    cond_in_edges = dif_parent.parent.in_edges(conditional_block)
    assert len(cond_in_edges) == 1
    innerstate_edge = cond_in_edges[0]
    # assert "tmp_index_881" in innerstate_edge.data.assignments
    state_to_duplicate: dace.SDFGState = conditional_block.sdfg.parent
    out_cond_block = state_to_duplicate.parent_graph.parent_graph
    outerstate_edge = out_cond_block.sdfg.in_edges(out_cond_block)
    assert len(outerstate_edge) == 1
    outerstate_edge = outerstate_edge[0]
    assert "_if_cond_28" in outerstate_edge.data.assignments
    
    # Make the changes
    nodes_to_remove = []
    for node in out_cond_block.sdfg.nodes():
        nodes_to_remove.append(node)
        
    inner_nsdfg = [node for node in state_to_duplicate.nodes() if isinstance(node, dace.nodes.NestedSDFG)][0]
    inner_nsdfg.sdfg.add_symbol("_if_cond_28", dace.int32)
    # state_to_duplicate.parent.remove_symbol("_if_cond_28")
    inner_nsdfg.sdfg.add_symbol("_if_cond_28", dace.int32)
    
    outermost_state = outerstate_edge.src.parent.parent
    outer_map_entry = [node for node in outermost_state.nodes() if isinstance(node, dace.nodes.MapEntry) and "_for_it_52" in node.map.params][0]
    outer_nsdfg: dace.nodes.NestedSDFG = outermost_state.out_edges(outer_map_entry)[0].dst
    out_edge = list(outermost_state.in_edges_by_connector(outer_nsdfg, "levelmask"))[0]
    in_edge = list(outermost_state.in_edges_by_connector(outer_map_entry, out_edge.src_conn.replace("OUT_", "IN_")))[0]
    inner_map_entry = [node for node in state_to_duplicate.nodes() if isinstance(node, dace.nodes.MapEntry)][0]
    
    an = state_to_duplicate.add_access("levelmask")
    conn_number = inner_map_entry.next_connector()
    assert inner_map_entry.add_in_connector(f"IN_{conn_number}")
    assert inner_map_entry.add_out_connector(f"OUT_{conn_number}")
    state_to_duplicate.add_edge(an, None, inner_map_entry, f"IN_{conn_number}", dc(in_edge.data))
    nsddfg = state_to_duplicate.out_edges(inner_map_entry)[0].dst
    assert nsddfg.add_in_connector("levelmask")
    state_to_duplicate.add_edge(inner_map_entry, f"OUT_{conn_number}", nsddfg, "levelmask", dc(out_edge.data))
    # Add memlet symbol
    
    outer_nsdfg.symbol_mapping["nrdmax_jg"] = "nrdmax_jg"
    inner_nsdfg.sdfg.add_datadesc("levelmask", dc(state_to_duplicate.sdfg.arrays["levelmask"]))
    # Add assignement
    innerstate_edge.data.assignments["_if_cond_28"] = outerstate_edge.data.assignments["_if_cond_28"]
    new_condition = "(_if_cond_28 == 1) and (_if_cond_29 == 1)"
    conditional_block.branches[0] = (dace.nodes.CodeBlock(new_condition), conditional_block.branches[0][1])
    dup_state = dc(state_to_duplicate)
    out_cond_block.sdfg.add_node(dup_state)
    out_cond_block.sdfg.remove_nodes_from(nodes_to_remove)
    set_nested_sdfg_parent_references(sdfg)
    sdfg.save("debug_move.sdfg")
    sdfg.validate()
    sdfg.simplify()
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.save("debug_move_1.sdfg")
    # assert False


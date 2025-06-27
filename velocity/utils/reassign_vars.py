import dace

from dace.sdfg.state import ControlFlowRegion
from utils.rename_on_if import rename_on_if, rename_on_for, rename_on_map, rename_on_tasklet

def replace(sdfg: dace.SDFG, start_block, old_symbol_str: str, new_symbol_str: str):
    """
    Replace all occurrences of old_symbol with new_symbol in the SDFG starting from start_block.
    """
    assert isinstance(start_block, dace.SDFGState) or isinstance(start_block, ControlFlowRegion), "start_block must be a SDFGState or ControlFlowRegion."
    assert start_block in sdfg.bfs_nodes(source=start_block), "start_block must be a valid starting point in the SDFG."

    for node in sdfg.bfs_nodes(source=start_block):
        out_edges = sdfg.out_edges(node)

        # If an SDFG State just replace, if CFG ensure replacing only on out edges to not replace in edge twice
        if isinstance(start_block, dace.SDFGState):
            node.replace(old_symbol_str, new_symbol_str)
        else:
            for n in node.nodes():
                n.replace(old_symbol_str, new_symbol_str)
                for e in sdfg.out_edges(n):
                    e.data.replace(old_symbol_str, new_symbol_str)

        for out_edge in out_edges:
            out_edge.data.replace(old_symbol_str, new_symbol_str)

        # If condition bug
        rename_on_if(node, old_symbol_str, new_symbol_str, True, True)
        rename_on_for(node, old_symbol_str, new_symbol_str, True, True)
        rename_on_map(node, old_symbol_str, new_symbol_str, True, True)
        rename_on_tasklet(node, old_symbol_str, new_symbol_str, True)

def reassign_vars(sdfg: dace.SDFG):
    re_counter = 0
    current_symbols = set()
    # All top level blocks should have at max 1 incoming edge and 1 outgoing edge.
    for node in sdfg.bfs_nodes(source=sdfg.start_block):
        out_edges = sdfg.out_edges(node)
        in_edges = sdfg.in_edges(node)
        assert len(out_edges) <= 1, f"Node {node} has more than one outgoing edge."
        assert len(in_edges) <= 1, f"Node {node} has more than one incoming edge."

        if len(out_edges) == 1:
            out_edge = out_edges[0]
            assert out_edge.dst != node
            assert isinstance(out_edge.data, dace.InterstateEdge), f"Outgoing edge of node {node} is not an InterstateEdge."
            new_assignments = set(out_edge.data.assignments.keys())
            reassignments = new_assignments.intersection(current_symbols)
            #print("Reassigning these symbols:", reassignments)
            current_symbols.update(new_assignments)

            # Replace all occurences of the reassigned symbols in the assignments in the following nodes
            for reassignment in reassignments:
                if re_counter > 9:
                    raise ValueError("Reassignment counter exceeded 9, TODO")
                #print(f"Replacing {reassignment} with replaced_var_{re_counter}")
                out_edge.data.replace(reassignment, f"replaced_var_{re_counter}")
                replace(sdfg, out_edge.dst, reassignment, f"replaced_var_{re_counter}")
                current_symbols.add(f"replaced_var_{re_counter}")
                re_counter += 1

        #print("Current Symbols:", current_symbols)


    # Why would this happen? This is a workaround for the issue where nested SDFGs do not have their symbols properly assigned.
    for node, parent_graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG):
            child_sdfg = node.sdfg
            connectors = node.in_connectors.keys() | node.out_connectors.keys()
            symbols = set(k for k in node.sdfg.free_symbols if k not in connectors)
            missing_symbols = [s for s in symbols if s not in node.symbol_mapping]
            if missing_symbols:
                for missing_symbol in missing_symbols:
                    child_sdfg.add_symbol(missing_symbol, node.sdfg.symbols[missing_symbol] if missing_symbol in node.sdfg.symbols else dace.int32)
                    node.symbol_mapping[missing_symbol] = missing_symbol


if __name__ == "__main__":
    sdfg = dace.SDFG.from_file("codegen/gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_stage1.sdfgz")
    reassign_vars(sdfg)
    sdfg.save("codegen/gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_stage1_reassigned.sdfgz")
    sdfg.validate()
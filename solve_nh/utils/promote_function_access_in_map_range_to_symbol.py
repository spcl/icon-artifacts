import dace
import re
import copy

def promote_function_access_in_map_range_to_symbol(sdfg: dace.SDFG):
    sym_id = 0
    for node, parent_graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.MapEntry):
            assert isinstance(parent_graph, dace.SDFGState)
            state : dace.SDFGState = parent_graph
            new_range_list = []
            change_range = False
            function_calls = []
            new_symbol_assignments = []
            data_accesses = set()
            for (b, e, s) in node.map.range:
                b_str = str(b)
                e_str = str(e)
                s_str = str(s)
                #print(b,", ",e,", ",s)
                #print(b_str,", ",e_str,", ",s_str)
                range_expr = []
                for expr_str in [b_str, e_str, s_str]:
                    matches = re.findall(r'\b\w+\s*\(.*?\)', expr_str)
                    if matches:
                        assert len(matches) == 1, f"Multiple function calls found in range expression: {matches}"
                        # Update map range
                        change_range = True
                        # Get the match
                        function_calls.extend(matches)
                        match_0 = matches[0]
                        # Get the base for the variable name, use global offset to avoid conflicts
                        var_name = match_0.split('(')[0].strip()
                        assert var_name.startswith("__CG_")
                        #var_name = var_name[5:]  # Remove "__CG_" prefix
                        sym_name = f"{var_name[5:]}_sym_{sym_id}"
                        expr_expr = dace.symbolic.SymExpr(expr_str)
                        updated_expr = expr_str.replace(match_0, sym_name)
                        if expr_expr == updated_expr:
                            raise Exception("Replace must not fail if we detect the pattern:", updated_expr, var_name, sym_name)
                        data_accesses.add(var_name)
                        # Create the access name (array[i] instead of array(i))
                        access_name = match_0.replace('(', '[').replace(')', ']')
                        # Add to the list of assignments to be added to the state edge leading to state
                        # where the map is in
                        new_symbol_assignments.append((sym_name, access_name))
                        range_expr.append(dace.symbolic.SymExpr(updated_expr))
                    else:
                        range_expr.append(dace.symbolic.SymExpr(expr_str))
                new_range_list.append(range_expr)
                range_expr = []
            # If need to change range do it
            if not change_range:
                continue

            node.map.range = dace.subsets.Range(new_range_list)
            #print(node.map.range)
            #print([(b,e,s) for (b,e,s) in node.map.range])
            #print()
            # If this state has no incoming edges, add an empty state to parent graph and connect to this set
            if len(state.parent_graph.in_edges(state)) == 0:
                var_assign_state = dace.SDFGState(
                    label="sym_assign",
                    sdfg=state.sdfg,
                )
                state.parent_graph.add_node(var_assign_state)
                state.parent_graph.add_edge(
                    var_assign_state, state, dace.InterstateEdge()
                )
                sym_id += 1

            # Avoid adding symbols to an edge that already has assignments
            state.parent_graph.add_state_before(state)

            # Get first edge. Since we have added an iedge, #(incoming edges) must be > 0
            assert len(state.parent_graph.in_edges(state)) > 0
            iedge = state.parent_graph.in_edges(state)[0]
            for key, val in new_symbol_assignments:
                assert iedge.data is not None, "Incoming edge data is None"
                assert key not in iedge.data.assignments, f"Symbol {key} already exists in edge assignments"
                iedge.data.assignments[key] = val

            # For each data access added, add the data descriptor and connecto to the parent NSDFG node
            for data_access in data_accesses:
                # If array is not in parent graphs's sdfg's data containers add it
                datadesc = sdfg.arrays[data_access]

                # If data access is already in the parent graph's sdfg, we can continue
                nsdfg_node = state.sdfg.parent_nsdfg_node

                # If this array has been already added to the nSDFG, we can skip, since
                # this transformation adds the complete array, this will be redundant, and
                # multiple edges to the same nSDFG inconnector is invalid.
                if data_access in nsdfg_node.in_connectors:
                    continue

                if data_access in state.sdfg.symbols:
                    state.sdfg.remove_symbol(data_access)
                if data_access not in state.sdfg.arrays:
                    copydesc = copy.deepcopy(datadesc)
                    copydesc.transient = False
                    state.sdfg.add_datadesc(
                        name=data_access,
                        datadesc=copydesc,
                    )
                if data_access not in nsdfg_node.sdfg.arrays:
                    copydesc = copy.deepcopy(datadesc)
                    copydesc.transient = False
                    state.sdfg.add_datadesc(
                        name=data_access,
                        datadesc=copydesc,
                    )
                # Make it flow into the map entry, for it find the state the NSDFG node is in
                parent_nsdfg_node_state: dace.SDFGState = None
                for node, graph in sdfg.all_nodes_recursive():
                    if node == nsdfg_node:
                        parent_nsdfg_node_state = graph
                        break
                assert parent_nsdfg_node_state is not None, "Parent NSDFG node state not found"

                # Get all parent scopes to detect how the data needs to flow (MapEntry -> NSDFG means AccessNode -> MapEntry -> NestedSDFG)
                parent_scopes = []
                cur_parent_scope = nsdfg_node
                scope_dict = parent_nsdfg_node_state.scope_dict()
                while scope_dict[cur_parent_scope] is not None:
                    parent_scopes.append(scope_dict[cur_parent_scope])
                    cur_parent_scope = scope_dict[cur_parent_scope]

                an = parent_nsdfg_node_state.add_access(
                    data_access
                )
                src = an
                for parent_scope in reversed(parent_scopes):
                    dst = parent_scope
                    parent_nsdfg_node_state.add_edge(
                        src,
                        None if isinstance(src, dace.nodes.AccessNode) else f"OUT_{data_access}",
                        dst,
                        data_access if isinstance(dst, dace.nodes.NestedSDFG) else f"IN_{data_access}",
                        dace.memlet.Memlet.from_array(
                            data_access,
                            datadesc
                        )
                    )
                    if not isinstance(src, dace.nodes.AccessNode):
                        src.add_out_connector(f"OUT_{data_access}")
                    if isinstance(dst, dace.nodes.NestedSDFG):
                        dst.add_in_connector(data_access)
                    else:
                        dst.add_in_connector(f"IN_{data_access}")
                    src = parent_scope
                dst = nsdfg_node
                parent_nsdfg_node_state.add_edge(
                    src,
                    None if isinstance(src, dace.nodes.AccessNode) else f"OUT_{data_access}",
                    dst,
                    data_access if isinstance(dst, dace.nodes.NestedSDFG) else f"IN_{data_access}",
                    dace.memlet.Memlet.from_array(
                        data_access,
                        datadesc
                    )
                )
                src.add_out_connector(
                    f"OUT_{data_access}" if not isinstance(src, dace.nodes.AccessNode) else None
                )
                dst.add_in_connector(data_access if isinstance(dst, dace.nodes.NestedSDFG) else f"IN_{data_access}")







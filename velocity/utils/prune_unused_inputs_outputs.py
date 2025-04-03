import os
import dace

def prune_unused_inputs_outputs(sdfg: dace.SDFG):
    # Works on a state that has 1 nested SDFG and 1 map
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.SDFGState):
            for n in node.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    #print("0", n)
                    map_body_nodes = list(node.all_nodes_between(n, node.exit_node(n)))
                    #print("1", map_body_nodes)
                    # If we have a map with a nested SDFG only
                    if len(map_body_nodes) == 1 and isinstance(map_body_nodes[0], dace.nodes.NestedSDFG):
                        # NestedSDFG should have 1 state only and 1 map + 1 nested SDFG + some acess nodes
                        nsdfg = map_body_nodes[0]
                        inner_sdfg = map_body_nodes[0].sdfg
                        #print("1.5", inner_sdfg.nodes())
                        if len(inner_sdfg.nodes()) == 1 and isinstance(inner_sdfg.nodes()[0], dace.SDFGState):
                            inner_state = inner_sdfg.nodes()[0]
                            maps_and_nested_sdfg = [n for n in inner_state.nodes()
                                                    if isinstance(n, dace.nodes.MapEntry) or isinstance(n, dace.nodes.NestedSDFG)]
                            #print("2", maps_and_nested_sdfg)
                            if len(maps_and_nested_sdfg) == 2:
                                nested_sdfg = [n for n in maps_and_nested_sdfg if isinstance(n, dace.nodes.NestedSDFG)][0]
                                map_entry = [n for n in maps_and_nested_sdfg if isinstance(n, dace.nodes.MapEntry)][0]

                                srcs = list(set([e.src for e in inner_state.in_edges(nested_sdfg)]))
                                assert len(srcs) == 1
                                src = srcs[0]
                                #print("3", src, map_entry, src == map_entry)
                                assert src == map_entry
                                map_exit = inner_state.exit_node(src)
                                dsts = list(set([e.dst for e in inner_state.out_edges(nested_sdfg)]))
                                assert len(dsts) == 1
                                assert dsts[0] == map_exit

                                # We have found the Map and the Nested SDFG
                                used_inputs = set()
                                used_outputs = set()

                                for e in inner_state.in_edges(map_entry):
                                    used_inputs.add(e.src.data)
                                for e in inner_state.out_edges(map_exit):
                                    used_outputs.add(e.dst.data)

                                # Now we have the used inputs and outputs
                                # Remove unused inputs and outputs

                                all_inputs = set(nsdfg.in_connectors.keys())
                                all_outputs = set(nsdfg.out_connectors.keys())
                                unused_inputs = all_inputs - used_inputs
                                unused_outputs = all_outputs - used_outputs
                                #print("4", unused_inputs, unused_outputs)

                                for unused_input in unused_inputs:
                                    for ie in node.in_edges(nsdfg):
                                        if ie.dst_conn == unused_input:
                                            nsdfg.remove_in_connector(unused_input)
                                            if unused_input in inner_sdfg.arrays:
                                                used = False
                                                for an in inner_state.nodes():
                                                    if isinstance(an, dace.nodes.AccessNode) and an.data == unused_input:
                                                        used = True
                                                        break
                                                if not used:
                                                    inner_sdfg.remove_data(unused_input)
                                            #if unused_input in inner_sdfg.symbols:
                                            #    inner_sdfg.remove_symbol(unused_input)
                                            assert isinstance(ie.src, dace.nodes.MapEntry)
                                            ie.src.remove_out_connector(ie.src_conn)
                                            src_src_conn = ie.src_conn.replace("OUT_", "IN_")
                                            ie.src.remove_in_connector(src_src_conn)
                                            for iie in node.in_edges(ie.src):
                                                if iie.dst == ie.src and iie.dst_conn == src_src_conn:
                                                    node.remove_edge(iie)
                                                    if node.in_degree(iie.src) == 0 and node.out_degree(iie.src) == 0:
                                                        node.remove_node(iie.src)
                                            node.remove_edge(ie)

                                for unused_output in unused_outputs:
                                    for oe in node.out_edges(nsdfg):
                                        if oe.src_conn == unused_output:
                                            nsdfg.remove_out_connector(unused_output)
                                            if unused_output in inner_sdfg.arrays:
                                                used = False
                                                for an in inner_state.nodes():
                                                    if isinstance(an, dace.nodes.AccessNode) and an.data == unused_input:
                                                        used = True
                                                        break
                                                if not used:
                                                    inner_sdfg.remove_data(unused_output)
                                            #if unused_output in inner_sdfg.symbols:
                                            #    inner_sdfg.remove_symbol(unused_output)
                                            assert isinstance(oe.dst, dace.nodes.MapExit)
                                            oe.dst.remove_in_connector(oe.dst_conn)
                                            dst_dst_conn = oe.dst_conn.replace("IN_", "OUT_")
                                            oe.dst.remove_out_connector(dst_dst_conn)
                                            for ooe in node.out_edges(oe.dst):
                                                if ooe.src == oe.dst and ooe.src_conn == dst_dst_conn:
                                                    node.remove_edge(ooe)
                                                    if node.in_degree(ooe.dst) == 0 and node.out_degree(ooe.dst) == 0:
                                                        node.remove_node(ooe.dst)
                                            node.remove_edge(oe)

def prune_unused_inputs_outputs_recursive(sdfg: dace.SDFG):
    # Works on a state that has 1 nested SDFG and 1 map
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.SDFGState):
            for n in node.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    #print("0", n)
                    map_body_nodes = list(node.all_nodes_between(n, node.exit_node(n)))
                    #print("1", map_body_nodes)
                    # If we have a map with a nested SDFG only
                    if len(map_body_nodes) == 1 and isinstance(map_body_nodes[0], dace.nodes.NestedSDFG):
                        # NestedSDFG should have 1 state only and 1 map + 1 nested SDFG + some acess nodes
                        nsdfg = map_body_nodes[0]
                        inner_sdfg = map_body_nodes[0].sdfg
                        #print("1.5", inner_sdfg.nodes())
                        used_inputs = set()
                        used_outputs = set()

                        for inner_state in inner_sdfg.all_states():
                            for n in inner_state.nodes():
                                if isinstance(n, dace.nodes.AccessNode):
                                # We have found the Map and the Nested SDFG
                                    inp = False
                                    outp = False
                                    for e in inner_state.out_edges(n):
                                        if isinstance(e.dst, dace.nodes.MapEntry):
                                            used_inputs.add(e.src.data)
                                            inp = True
                                    for e in inner_state.in_edges(n):
                                        if isinstance(e.src, dace.nodes.MapExit):
                                            used_outputs.add(e.dst.data)
                                            outp = True
                                    # Cant be sure
                                    if not inp and not outp:
                                        used_inputs.add(n.data)
                                        used_outputs.add(n.data)
                        for e in inner_sdfg.edges():
                            for assignment in e.data.assignments:
                                used_inputs.add(assignment)
                                used_outputs.add(assignment)

                        # Now we have the used inputs and outputs
                        # Remove unused inputs and outputs


                        all_inputs = set(nsdfg.in_connectors.keys())
                        all_outputs = set(nsdfg.out_connectors.keys())
                        for name in all_inputs:
                            if "idx" in name or "index" in name or "blk" in name or "nproma" in name or "cfl_clipping" in name or "levmask" in name or "maxvcfl" in name or "owner_mask" in name or "levelmask" in name:
                                used_inputs.add(name)
                        for name in all_outputs:
                            if "idx" in name or "index" in name or "blk" in name or "nproma" in name or "cfl_clipping" in name or "levmask" in name or "maxvcfl" in name or "owner_mask" in name or "levelmask" in name:
                                used_outputs.add(name)
                        unused_inputs = all_inputs - used_inputs
                        unused_outputs = all_outputs - used_outputs
                        # print("4", unused_inputs, unused_outputs)
                        # print("5", used_inputs, used_outputs)

                        for unused_input in unused_inputs:
                            for ie in node.in_edges(nsdfg):
                                if ie.dst_conn == unused_input:
                                    nsdfg.remove_in_connector(unused_input)
                                    if unused_input in inner_sdfg.arrays:
                                        used = False
                                        for an in inner_state.nodes():
                                            if isinstance(an, dace.nodes.AccessNode) and an.data == unused_input:
                                                used = True
                                                break
                                        if not used:
                                            try:
                                                inner_sdfg.remove_data(unused_input)
                                            except:
                                                continue
                                    #if unused_input in inner_sdfg.symbols:
                                    #    inner_sdfg.remove_symbol(unused_input)
                                    assert isinstance(ie.src, dace.nodes.MapEntry)
                                    ie.src.remove_out_connector(ie.src_conn)
                                    src_src_conn = ie.src_conn.replace("OUT_", "IN_")
                                    ie.src.remove_in_connector(src_src_conn)
                                    for iie in node.in_edges(ie.src):
                                        if iie.dst == ie.src and iie.dst_conn == src_src_conn:
                                            node.remove_edge(iie)
                                            if node.in_degree(iie.src) == 0 and node.out_degree(iie.src) == 0:
                                                node.remove_node(iie.src)
                                    node.remove_edge(ie)

                        for unused_output in unused_outputs:
                            for oe in node.out_edges(nsdfg):
                                if oe.src_conn == unused_output:
                                    nsdfg.remove_out_connector(unused_output)
                                    if unused_output in inner_sdfg.arrays:
                                        used = False
                                        for an in inner_state.nodes():
                                            if isinstance(an, dace.nodes.AccessNode) and an.data == unused_output:
                                                used = True
                                                break
                                        if not used:
                                            try:
                                                inner_sdfg.remove_data(unused_output)
                                            except:
                                                continue
                                    #if unused_output in inner_sdfg.symbols:
                                    #    inner_sdfg.remove_symbol(unused_output)
                                    assert isinstance(oe.dst, dace.nodes.MapExit)
                                    oe.dst.remove_in_connector(oe.dst_conn)
                                    dst_dst_conn = oe.dst_conn.replace("IN_", "OUT_")
                                    oe.dst.remove_out_connector(dst_dst_conn)
                                    for ooe in node.out_edges(oe.dst):
                                        if ooe.src == oe.dst and ooe.src_conn == dst_dst_conn:
                                            node.remove_edge(ooe)
                                            if node.in_degree(ooe.dst) == 0 and node.out_degree(ooe.dst) == 0:
                                                node.remove_node(ooe.dst)
                                    node.remove_edge(oe)

    sdfg.save("tmp.sdfgz", compress=True)
    sdfg = dace.SDFG.from_file("tmp.sdfgz")
    os.remove("tmp.sdfgz")

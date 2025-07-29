import dace
from dace.sdfg.state import CodeBlock, LoopRegion

def repl_code_block_or_str(input: CodeBlock | str, src:str, dst:str):
    if isinstance(input, CodeBlock):
        return CodeBlock(input.as_string.replace(src, dst))
    else:
        return input.replace(src, dst)

def specialize_scalar_impl(root: dace.SDFG, sdfg: dace.SDFG, scalar_name: str, scalar_val: int):
    # RM dynamic input to maps
    # Replace all accurences of the scalar appearances in the SDFG with the scalar value
    if root != sdfg:
        if scalar_name in sdfg.arrays:
            sdfg.remove_data(scalar_name, validate=False)

        if scalar_name in sdfg.symbols:
            sdfg.remove_symbol(scalar_name)


    nsdfgs = set()
    for state in sdfg.all_states():
        # Check dynamic inputs
        for e in state.edges():
            if e.data is not None and e.data.data == scalar_name:
                state.remove_edge(e)
                src: dace.nodes.Node = e.src
                dst: dace.nodes.Node = e.dst
                if e.src_conn is not None:
                    src.remove_out_connector(e.src_conn)
                if e.dst_conn is not None:
                    dst.remove_in_connector(e.dst_conn)
                if state.degree(src) == 0:
                    if isinstance(src, dace.nodes.MapEntry):
                        # Add a dep edge
                        state.add_edge(src, None, dst, None, dace.memlet.Memlet())
                    else:
                        state.remove_node(src)
                if state.degree(dst) == 0:
                    if isinstance(dst, dace.nodes.MapExit):
                        state.add_edge(src, None, dst, None, dace.memlet.Memlet())
                    else:
                        state.remove_node(dst)

        for node in state.nodes():
            if isinstance(node, dace.nodes.MapEntry):
                new_range_list = []

                for (b,e,s) in node.map.range:
                    _b = b.subs(scalar_name, scalar_val)
                    _e = e.subs(scalar_name, scalar_val)
                    _s = s.subs(scalar_name, scalar_val)
                    new_range_list.append((_b, _e, _s))
                node.map.range = dace.subsets.Range(new_range_list)
            elif isinstance(node, dace.nodes.NestedSDFG):
                nsdfgs.add(node.sdfg)

    # Replace on for CFGs as
    for cfg in sdfg.all_control_flow_regions():
        if isinstance(cfg, LoopRegion):
            cfg.loop_condition = repl_code_block_or_str(cfg.loop_condition, scalar_name, str(scalar_val))
            cfg.init_statement = repl_code_block_or_str(cfg.init_statement, scalar_name, str(scalar_val))
            cfg.update_statement = repl_code_block_or_str(cfg.update_statement, scalar_name, str(scalar_val))
            assert cfg.loop_variable != scalar_name, (
                f"Loop variable {cfg.loop_variable} cannot be the same as the scalar {scalar_name}"
            )


    for edge in sdfg.all_interstate_edges(recursive=True):
        if edge.data is not None:
            nassignments = dict()
            for k, v in edge.data.assignments.items():
                _k = k.replace(scalar_name, str(scalar_val))
                if isinstance(v, CodeBlock):
                    _v = CodeBlock(v.as_string().replace(scalar_name, str(scalar_val)))
                else:
                    _v = v.replace(scalar_name, str(scalar_val))
                nassignments[_k] = _v
            edge.data.assignments = nassignments

    if root != sdfg:
        if scalar_name in sdfg.parent_nsdfg_node.symbol_mapping:
            del sdfg.parent_nsdfg_node.symbol_mapping[scalar_name]

    for nsdfg in nsdfgs:
        specialize_scalar_impl(root, nsdfg, scalar_name, scalar_val)

def specialize_scalar(sdfg: dace.SDFG, scalar_name: str, scalar_val: int):
    specialize_scalar_impl(sdfg, sdfg, scalar_name, scalar_val)

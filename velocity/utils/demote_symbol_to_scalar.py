import ast
import dace

def demote_symbol_to_scalar(sdfg: dace.SDFG, symbol_str: str):
    # If assignment is to symbol_str, append it to last scalar before
    sym_dtype = sdfg.symbols[symbol_str]
    sdfg.remove_symbol(symbol_str)
    scalar_name, scalar = sdfg.add_scalar(symbol_str, sym_dtype, transient=True)
    for e in sdfg.edges():
        if e.data is not None and e.data.assignments is not None:
            assert len([(k, v) for k, v in e.data.assignments.items() if k == symbol_str]) <= 1
            if len([(k, v) for k, v in e.data.assignments.items() if k == symbol_str]) == 1:
                dst, assignment = [(k, v) for k, v in e.data.assignments.items() if k == symbol_str][0]
                # print(dst, assignment, type(assignment))
                if dst == symbol_str:
                    for cfg in e.dst.all_control_flow_regions() if not isinstance(e.dst, dace.SDFGState) else [e.dst]:
                        if isinstance(cfg, dace.SDFGState):
                            state = cfg
                            for n in state.nodes():
                                if isinstance(n, dace.nodes.Tasklet):
                                    if n.code is not None:
                                        for i in range(len(n.code.code)):
                                            if symbol_str in ast.unparse(n.code.code[i]):
                                                if state.in_degree(n) > 0:
                                                    assert False, "Unsupported case TODO"
                                                n.code.code[i] =  ast.parse(ast.unparse(n.code.code[i]).replace(symbol_str, "__in_" + symbol_str))
                                                n.add_in_connector("__in_" + symbol_str)
                                                an = state.add_access(scalar_name)
                                                state.add_edge(an, None, n, "__in_" + symbol_str,
                                                            dace.Memlet.from_array(scalar_name, scalar))
                                                an2 = state.add_access(assignment)
                                                state.add_edge(an2, None, an, None,
                                                            dace.Memlet.from_array(assignment, sdfg.arrays[assignment]))
            if symbol_str in e.data.assignments:
                del e.data.assignments[symbol_str]



import ast
import dace
from utils.rename_on_if import rename_on_if

def propagate_block_var(sdfg: dace.SDFG):
    # Works only if all top level CFG have 1 incoming edge and 1 outgoing edge at max
    for cfg in sdfg.nodes():
        assert sdfg.in_degree(cfg) <= 1
        assert sdfg.out_degree(cfg) <= 1

    current_blk_symbols = dict()
    for cfg in sdfg.bfs_nodes():
        blk_symbols = dict()
        for ie in cfg.parent_graph.in_edges(cfg):
            if ie.data is not None:
                if ie.data.assignments is not None:
                    vars_to_rm = set()
                    for var, assignment in ie.data.assignments.items():
                        if "startblk" in var or "endblk" in var:
                            if "edges" in assignment:
                                assert var not in blk_symbols
                                blk_symbols[var] = "EDGE"
                            if "verts" in assignment:
                                assert var not in blk_symbols
                                blk_symbols[var] = "VERT"
                            if "cells" in assignment:
                                assert var not in blk_symbols
                                blk_symbols[var] = "CELL"
                            # delete the assignment we do not need it
                            vars_to_rm.add(var)
                            current_blk_symbols[var] = blk_symbols[var]
                            assert var in blk_symbols, f"Variable {var} not in blk_symbols, assignment: {assignment}"
                    for var in vars_to_rm:
                        del ie.data.assignments[var]
        for node, p in cfg.all_nodes_recursive():
            if isinstance(node, dace.nodes.MapEntry):
                blk_params = set()
                for b,e,s in node.map.range:
                    syms = b.free_symbols.union(e.free_symbols).union(s.free_symbols)
                    str_syms = [str(sym) for sym in syms]
                    for str_sym in str_syms:
                        if str_sym in current_blk_symbols:
                            blk_params.add(str_sym)
                assert all(blk_params) or not any(blk_params)

                blk_param_types = set()
                for blk_param in blk_params:
                    blk_param_types.add(current_blk_symbols[blk_param])
                # print(map, blk_params, blk_param_types)

                assert len(blk_param_types) <= 1, f"blk_param_types: {blk_param_types}"

                if len(blk_params) > 0:
                    blk_type = blk_param_types.pop()
                    if all(blk_params):
                        new_range_list = []
                        if blk_type == "EDGE":
                            new_range_list.append([1, 2, 1])
                        if blk_type == "VERT":
                            new_range_list.append([1, 1, 1])
                        if blk_type == "CELL":
                            new_range_list.append([1, 1, 1])
                        node.map.range = dace.subsets.Range(new_range_list)
            n = node
            # 1-based indexing for Berke reductions are problematic
            if isinstance(n, dace.nodes.Tasklet):
                for i, code in enumerate(n.code.code):
                    code_string = ast.unparse(code)
                    for blk_symbol in current_blk_symbols:
                        if blk_symbol in code_string:
                            if "startblk" in blk_symbol:
                                if current_blk_symbols[blk_symbol] == "EDGE":
                                    code_string = code_string.replace(blk_symbol, "0")
                                if current_blk_symbols[blk_symbol] == "VERT":
                                    code_string = code_string.replace(blk_symbol, "0")
                                if current_blk_symbols[blk_symbol] == "CELL":
                                    code_string = code_string.replace(blk_symbol, "0")
                            if "endblk" in blk_symbol:
                                if current_blk_symbols[blk_symbol] == "EDGE":
                                    code_string = code_string.replace(blk_symbol, "2")
                                if current_blk_symbols[blk_symbol] == "VERT":
                                    code_string = code_string.replace(blk_symbol, "1")
                                if current_blk_symbols[blk_symbol] == "CELL":
                                    code_string = code_string.replace(blk_symbol, "1")
                    # if code_string != ast.unparse(code):
                        # print(code_string, code)
                    _code = ast.parse(code_string)
                    n.code.code[i] = _code
        # Replace rest as usual
        for blk_symbol in current_blk_symbols:
            if "startblk" in blk_symbol:
                cfg.replace(blk_symbol, "1")
                rename_on_if(cfg, blk_symbol, "1", recursive=True)
            if "endblk" in blk_symbol:
                if current_blk_symbols[blk_symbol] == "EDGE":
                    cfg.replace(blk_symbol, "3")
                    rename_on_if(cfg, blk_symbol, "3", recursive=True)
                if current_blk_symbols[blk_symbol] == "VERT":
                    cfg.replace(blk_symbol, "2")
                    rename_on_if(cfg, blk_symbol, "2", recursive=True)
                if current_blk_symbols[blk_symbol] == "CELL":
                    cfg.replace(blk_symbol, "2")
                    rename_on_if(cfg, blk_symbol, "2", recursive=True)


    # print(f"Now unneeded blk symbols: {current_blk_symbols}")
    for sym in current_blk_symbols:
        assert sym in sdfg.free_symbols
        sdfg.remove_symbol(sym)
    # print(sdfg.free_symbols)

    sdfg.validate()

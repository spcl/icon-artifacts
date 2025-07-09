import ast
import copy
import dace
from dace.sdfg.sdfg import ConditionalBlock
from utils.rename_on_if import rename_on_if, rename_on_if2

def make_unique_block_var(sdfg: dace.SDFG, verbose=False):
    # Works only if all top level CFG have 1 incoming edge and 1 outgoing edge at max
    for cfg in sdfg.nodes():
        assert sdfg.in_degree(cfg) <= 1
        assert sdfg.out_degree(cfg) <= 1
    replaced = set()
    current_blk_symbols = dict()
    enu = 0
    visited = set()

    for cfg in sdfg.bfs_nodes():
        blk_symbols_set = set()
        for ie in cfg.parent_graph.in_edges(cfg):
            if ie.data is not None:
                if ie.data.assignments is not None:
                    for var, assignment in ie.data.assignments.items():
                        if "startblk" in var or "endblk" in var:
                            blk_symbols_set.add(var)
                            if var not in current_blk_symbols:
                                current_blk_symbols[var] = var

    for cfg in sdfg.bfs_nodes():
        blk_symbols_set = set()
        for ie in cfg.parent_graph.in_edges(cfg):
            if ie.data is not None:
                if ie.data.assignments is not None:
                    for var, assignment in ie.data.assignments.items():
                        if "startblk" in var or "endblk" in var:
                            blk_symbols_set.add(var)
        if len(blk_symbols_set) > 0:
            suffix = f"u{enu}"
            enu += 1
            for ie in cfg.parent_graph.in_edges(cfg):
                if ie.data is not None:
                    if ie.data.assignments is not None:
                        for var, assignment in list(ie.data.assignments.items()):
                            if "startblk" in var or "endblk" in var:
                                new_name = f"{var}_{suffix}"
                                val = ie.data.assignments.pop(var)
                                ie.data.assignments[new_name] = val
                                if new_name not in cfg.parent_graph.sdfg.symbols:
                                    old_sym_dtype = cfg.parent_graph.sdfg.symbols[var]
                                    cfg.parent_graph.sdfg.add_symbol(new_name, old_sym_dtype)
                                current_blk_symbols[var] = new_name

        rename_on_if2(cfg, current_blk_symbols, True, False)

        cfg.replace_dict(current_blk_symbols)

        for node, p in cfg.all_nodes_recursive():
            n = node
            # 1-based indexing for Berke reductions are problematic
            if isinstance(n, dace.nodes.Tasklet):
                for i, code in enumerate(n.code.code):
                    code_string = ast.unparse(code)
                    for blk_symbol in current_blk_symbols:
                        if blk_symbol in code_string.split(" ") and blk_symbol in blk_symbols_set:
                            code_string = code_string.replace(blk_symbol, current_blk_symbols[blk_symbol])
                    if code_string != ast.unparse(code):
                        _code = ast.parse(code_string)
                        n.code.code[i] = _code

        for node, p in cfg.all_nodes_recursive():
            if isinstance(node, dace.nodes.NestedSDFG):
                for blk_symbol in current_blk_symbols:
                    if blk_symbol in node.symbol_mapping:
                        rmkey = node.symbol_mapping.pop(blk_symbol)
                        #print(rmkey, blk_symbol)
                        dtype = node.sdfg.symbols[blk_symbol]

                        node.symbol_mapping[current_blk_symbols[blk_symbol]] = rmkey
                        node.sdfg.remove_symbol(blk_symbol)
                        node.sdfg.add_symbol(current_blk_symbols[blk_symbol], dtype)

    if verbose:
        print(f"Now unneeded blk symbols: {current_blk_symbols}")
    for sym in current_blk_symbols:
        assert sym in sdfg.free_symbols
        sdfg.remove_symbol(sym)
    if verbose:
        print(sdfg.free_symbols)

    sdfg.validate()
    # sdfg.save("test.sdfg")

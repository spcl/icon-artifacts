import re
import dace
import ast

from dace.codegen.control_flow import ConditionalBlock, LoopRegion
import dace.properties

def rename_on_if(cfg, src: str, dst: str, recursive=False, exact=False):
    gpu_host_name_map = {src: dst}

    for _, node in enumerate([cfg] + cfg.nodes()) if not recursive else cfg.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue

        for b in node.branches:
            if b[0] is None:
                continue
            if isinstance(b[0].code, list):
                for i, el in enumerate(b[0].code):
                    if isinstance(el, str):
                        for src,dst in gpu_host_name_map.items():
                            b[0].code[i] = b[0].code[i].replace(src,dst)
                    else:
                        def replace_x_with_y(expr: ast.Expr, repl_dict) -> ast.Expr:
                            expr_str = ast.unparse(expr).strip()
                            for src, dst in repl_dict.items():
                                #print(src, dst, expr_str, src in expr_str)
                                if not exact:
                                    modified_str = expr_str.replace(src, dst)
                                else:
                                    if src in expr_str.split(" "):
                                        modified_str = expr_str.replace(src, dst)
                                    else:
                                        modified_str = expr_str
                            return ast.parse(modified_str, mode="eval").body
                        b[0].code[i] = replace_x_with_y(b[0].code[i], gpu_host_name_map)
            else:
                assert isinstance(b[0].code, str)
                for src,dst in gpu_host_name_map.items():
                    b[0].code = b[0].code.replace(src, dst)

def rename_on_for(cfg, src: str, dst: str, recursive=False, exact=False):
    gpu_host_name_map = {src: dst}

    for _, node in enumerate([cfg] + cfg.nodes()) if not recursive else cfg.all_nodes_recursive():
        if not isinstance(node, LoopRegion):
            continue

        node.loop_variable = node.loop_variable.replace(src, dst)

        for b in [node.loop_condition, node.init_statement, node.update_statement]:
            if isinstance(b.code, list):
                for i, el in enumerate(b.code):
                    if isinstance(el, str):
                        for src,dst in gpu_host_name_map.items():
                            b.code[i] = b.code[i].replace(src,dst)
                    else:
                        def replace_x_with_y(expr: ast.Expr, repl_dict) -> ast.Expr:
                            expr_str = ast.unparse(expr).strip()
                            for src, dst in repl_dict.items():
                                if not exact:
                                    modified_str = expr_str.replace(src, dst)
                                else:
                                    if src in expr_str.split(" "):
                                        modified_str = expr_str.replace(src, dst)
                                    else:
                                        modified_str = expr_str
                            return ast.parse(modified_str).body
                        b.code[i] = replace_x_with_y(b.code[i], gpu_host_name_map)
            else:
                assert isinstance(b.code, str)
                for src,dst in gpu_host_name_map.items():
                    b.code = b.code.replace(src, dst)

def rename_on_map(cfg, src: str, dst: str, recursive=False, exact=False):
    gpu_host_name_map = {src: dst}

    for _, cfg_or_state in enumerate([cfg] + cfg.nodes()) if not recursive else cfg.all_nodes_recursive():
        if isinstance(cfg_or_state, dace.SDFGState):
            for node in cfg_or_state.nodes():
                if not isinstance(node, dace.nodes.MapEntry):
                    continue
                new_range_arr = []
                for b, e, s in node.map.range:
                    src_sym = dace.symbolic.symbol(src)
                    dst_sym = dace.symbolic.symbol(dst)

                    nb = b.subs(src_sym, dst_sym)
                    ne = e.subs(src_sym, dst_sym)
                    ns = s.subs(src_sym, dst_sym)

                    #print(b,e,s)
                    #if "i_startblk_var_146" in str(b) or "i_endblk_var_147" in str(e):
                    #    raise Exception((b,e,s), (nb, ne, ns))
                    new_range_arr.append((nb, ne, ns))
                node.map.range = dace.subsets.Range(ranges=new_range_arr)

def rename_on_tasklet(cfg, src: str, dst: str, recursive=False):
    for _, cfg_or_state in enumerate([cfg] + cfg.nodes()) if not recursive else cfg.all_nodes_recursive():
        if isinstance(cfg_or_state, dace.SDFGState):
            for node in cfg_or_state.nodes():
                if not isinstance(node, dace.nodes.Tasklet):
                    continue
                code_str = node.code.as_string
                code_lang = node.code.language
                code_str.replace(src, dst)
                node.code = dace.properties.CodeBlock(
                    code=code_str,
                    language=code_lang,
                )


def rename_on_if2(cfg, m, recursive=False, exact=False):
    gpu_host_name_map = m

    for _, node in enumerate([cfg] + cfg.nodes()) if not recursive else cfg.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue

        for b in node.branches:
            if b[0] is None:
                continue
            if isinstance(b[0].code, list):
                for i, el in enumerate(b[0].code):
                    if isinstance(el, str):
                        pattern = re.compile(r'\b(' + '|'.join(map(re.escape, gpu_host_name_map.keys())) + r')\b')
                        result = pattern.sub(lambda x: gpu_host_name_map[x.group()], el)
                        b[0].code[i] = result
                    else:
                        def replace_x_with_y(expr: ast.Expr, repl_dict) -> ast.Expr:
                            expr_str = ast.unparse(expr).strip()
                            pattern = re.compile(r'\b(' + '|'.join(map(re.escape, gpu_host_name_map.keys())) + r')\b')
                            result = pattern.sub(lambda x: gpu_host_name_map[x.group()], expr_str)
                            modified_str = result
                            return ast.parse(modified_str, mode="eval").body
                        b[0].code[i] = replace_x_with_y(b[0].code[i], gpu_host_name_map)
            else:
                assert isinstance(b[0].code, str)
                pattern = re.compile(r'\b(' + '|'.join(map(re.escape, gpu_host_name_map.keys())) + r')\b')
                result = pattern.sub(lambda x: gpu_host_name_map[x.group()], b[0].code)
                b[0].code = result
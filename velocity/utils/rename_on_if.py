import re
import dace
import ast

from dace.codegen.control_flow import ConditionalBlock

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
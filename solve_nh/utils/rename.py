import dace
from dace.codegen.control_flow import ConditionalBlock, LoopRegion
import dace.properties

def rename_on_if(cfg, src: str, dst: str, recursive=False):
    for _, node in enumerate([cfg] + cfg.nodes()) if not recursive else cfg.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue

        for b in node.branches:
            if b[0] is None:
                continue
            assert isinstance(b[0], dace.properties.CodeBlock), f"Branch {b[0]} is not a CodeBlock."
            s = b[0].as_string.replace(src, dst)
            b[0] = dace.properties.CodeBlock(
                code=s,
                language=b[0].language,
            )

def rename_on_for(cfg, src: str, dst: str, recursive=False):
    for _, node in enumerate([cfg] + cfg.nodes()) if not recursive else cfg.all_nodes_recursive():
        if not isinstance(node, LoopRegion):
            continue

        node.loop_variable = node.loop_variable.replace(src, dst)

        for code, attr in [(node.loop_condition, "loop_condition"), (node.init_statement, "init_statement"), (node.update_statement, "update_statement")]:
            assert isinstance(code, dace.properties.CodeBlock), f"LoopRegion {node} has non-CodeBlock statement {code}."
            code_str = code.as_string
            code_str = code_str.replace(src, dst)
            assert hasattr(node, attr), f"LoopRegion {node} does not have attribute {attr}."
            node.__setattr__(attr, dace.properties.CodeBlock(
                code=code_str,
                language=code.language,
            ))

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
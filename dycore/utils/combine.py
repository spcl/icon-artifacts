import copy
import dace
from typing import List, Dict

from dace.codegen.control_flow import ConditionalBlock, ControlFlowRegion
from dace.properties import CodeBlock
import typing

def _unique_names(sdfgs: typing.List[dace.SDFG]):
    for i, sdfg in enumerate(sdfgs):
        sdfg.function_suffix = "_" + str(i)
        visited = set()
        for n, parent in sdfg.all_nodes_recursive():
            if n in visited:
                continue
            # Add unique names for anything that can become CUDA functions to avoid name conflicts
            if isinstance(n, dace.nodes.MapEntry):
                n.map.label = f"{n.map.label}{sdfg.function_suffix}"
                n.label = f"{n.label}{sdfg.function_suffix}"
                visited.add(n.map)
                visited.add(n)
            #if isinstance(n, dace.nodes.MapExit):
            #    n.label = f"{n.label}{sdfg.function_suffix}"
            #    visited.add(n)
            elif isinstance(n, dace.nodes.NestedSDFG):
                n.sdfg.function_suffix = "_" + str(i)
                visited.add(n)
            elif not isinstance(n, dace.nodes.AccessNode) and not isinstance(n, dace.nodes.EntryNode) and not isinstance(n, dace.nodes.ExitNode):
                n.label = f"{n.label}{sdfg.function_suffix}"
                visited.add(n)

def combine(sdfgs: List[dace.SDFG], cond_list: List[Dict[str, str]]):
    merged_sdfg = dace.SDFG("merged_sdfg")

    cb = ConditionalBlock(
        label="entry",
        sdfg=merged_sdfg,
        parent=None,
    )
    merged_sdfg.add_node(cb, is_start_block=True)

    for sdfg, cond_dict in zip(sdfgs, cond_list):
        cfg = ControlFlowRegion(
            label="cfg",
            sdfg=merged_sdfg,
            parent=cb,
        )
        cb.add_branch(
            CodeBlock(" and ".join([f'{k} == {v}' for k, v in cond_dict.items()])),
            cfg,
        )
        node_map = dict()

        for node in sdfg.nodes():
            node_map[node] = copy.deepcopy(node)
        for node in node_map.values():
            cfg.add_node(node)
        for edge in sdfg.edges():
            src = node_map[edge.src]
            dst = node_map[edge.dst]
            merged_sdfg.add_edge(src, dst, copy.deepcopy(edge.data))


        for node, parent in cfg.all_nodes_recursive():
            if isinstance(node, dace.nodes.NestedSDFG):
                node.sdfg.parent_sdfg = parent.sdfg
                node.sdfg.parent_graph = parent

    return merged_sdfg

if __name__ == "__main__":
    sdfg_names = [
        "gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_result.sdfgz",
        "gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_2_result.sdfgz",
        "gpu_velocity_no_nproma_if_prop_lvn_only_1_istep_1_result.sdfgz",
        "gpu_velocity_no_nproma_if_prop_lvn_only_1_istep_2_result.sdfgz",
    ]
    sdfgs = [dace.SDFG.from_file(sdfg_name) for sdfg_name in sdfg_names]
    _unique_names(sdfgs)
    cond_dict = [
        {"i_step": 1, "lvn_only": 0},
        {"i_step": 2, "lvn_only": 0},
        {"i_step": 1, "lvn_only": 1},
        {"i_step": 2, "lvn_only": 1},
    ]
    ms = combine(sdfgs, cond_dict)
    ms.save("merged_sdfg.sdfgz", compress=True)
    ms.validate()
    sdfg_names = [
        "cpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_result.sdfgz",
        "cpu_velocity_no_nproma_if_prop_lvn_only_0_istep_2_result.sdfgz",
        "cpu_velocity_no_nproma_if_prop_lvn_only_1_istep_1_result.sdfgz",
        "cpu_velocity_no_nproma_if_prop_lvn_only_1_istep_2_result.sdfgz",
    ]
    sdfgs = [dace.SDFG.from_file(sdfg_name) for sdfg_name in sdfg_names]
    _unique_names(sdfgs)
    cond_dict = [
        {"i_step": 1, "lvn_only": 0},
        {"i_step": 2, "lvn_only": 0},
        {"i_step": 1, "lvn_only": 1},
        {"i_step": 2, "lvn_only": 1},
    ]
    ms = combine(sdfgs, cond_dict)
    ms.save("merged_sdfg_cpu.sdfgz", compress=True)
    ms.validate()
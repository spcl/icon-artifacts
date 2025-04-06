import copy
import dace
from typing import List, Dict

from dace.codegen.control_flow import ConditionalBlock, ControlFlowRegion
from dace.properties import CodeBlock


def combine(sdfgs: List[dace.SDFG], cond_list: List[Dict[str, str]]):
    merged_sdfg = dace.SDFG("merged_sdfg")

    cb = ConditionalBlock(
        label="entry",
        sdfg=merged_sdfg,
        parent=None,
    )

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
    cond_dict = [
        {"i_step": 1, "lvn_only": 0},
        {"i_step": 2, "lvn_only": 0},
        {"i_step": 1, "lvn_only": 1},
        {"i_step": 2, "lvn_only": 1},
    ]
    ms = combine(sdfgs, cond_dict)
    ms.save("merged_sdfg.sdfgz", compress=True)
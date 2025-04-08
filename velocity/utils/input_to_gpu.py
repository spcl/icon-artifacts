import dace
from dace.sdfg import SDFGState
import re


def input_to_gpu(sdfg: dace.SDFG, input_name: str):
    """
    Transforms an input to be present on the GPU.
    """

    first_state: SDFGState = sdfg.start_state
    last_state = sdfg.sink_nodes()[0]

    # Ensure the symbols are not eliminated
    first_state.add_tasklet(
        "sym_hack",
        {},
        {},
        f"i_am_not_used = {sdfg.arrays[input_name].total_size}",
        side_effects=True,
    )

    # Rename access nodes
    for node, p in sdfg.all_nodes_recursive():
        if not isinstance(node, dace.nodes.AccessNode):
            continue
        if node.data != f"gpu_{input_name}":
            continue

        # Remove copyin/copyout in first/last state
        if p is first_state or p is last_state:
            preds_succs = list(p.predecessors(node)) + list(p.successors(node))
            for pred_succ in preds_succs:
                p.remove_node(pred_succ)
            p.remove_node(node)
        else:
            # Strip the prefix of all access nodes that follow this name: gpu_<input_name>
            # Preserves function signature
            node.data = input_name

    # Rename connectors
    for node, p in sdfg.all_nodes_recursive():
        if not hasattr(node, "in_connectors") or not hasattr(node, "out_connectors"):
            continue

        pattern = r"\b" + re.escape(f"gpu_{input_name}") + r"\b"
        for k in list(node.in_connectors.keys()):
            if k != "gpu_" + input_name:
                continue
            # Rename the connector
            node.in_connectors[input_name] = node.in_connectors[k]
            del node.in_connectors[k]
        for k in list(node.out_connectors.keys()):
            if k != "gpu_" + input_name:
                continue
            # Rename the connector
            node.out_connectors[input_name] = node.out_connectors[k]
            del node.out_connectors[k]

    # Rename edges
    for edge, p in sdfg.all_edges_recursive():
        pattern = r"\b" + re.escape(f"gpu_{input_name}") + r"\b"
        if hasattr(edge.data, "data") and edge.data.data is not None:
            edge.data.data = re.sub(pattern, input_name, edge.data.data)

        if hasattr(edge, "dst_conn") and edge.dst_conn is not None:
            edge.dst_conn = re.sub(pattern, input_name, edge.dst_conn)

        if hasattr(edge, "src_conn") and edge.src_conn is not None:
            edge.src_conn = re.sub(pattern, input_name, edge.src_conn)

    # Adjust array descriptors
    sdfg_appeared = False
    for nsdfg in sdfg.all_sdfgs_recursive():
        if nsdfg is sdfg:
            sdfg_appeared = True
        if f"gpu_{input_name}" not in nsdfg.arrays:
            continue
        if input_name in nsdfg.arrays:
            nsdfg.arrays[f"{input_name}"].storage = nsdfg.arrays[
                f"gpu_{input_name}"
            ].storage
        else:
            nsdfg.arrays[f"{input_name}"] = nsdfg.arrays[f"gpu_{input_name}"]
        del nsdfg.arrays[f"gpu_{input_name}"]

    assert sdfg_appeared, "SDFG not found in the list of all SDFGs"

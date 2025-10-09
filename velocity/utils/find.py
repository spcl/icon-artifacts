import dace


def find_node_by_name(sdfg: dace.SDFG, name: str, skip=0):
    for node, parent in sdfg.all_nodes_recursive():
        if node.label == name:
            if skip > 0:
                skip -= 1
                continue
            return node, parent
    assert False, f"Node {name} not found"

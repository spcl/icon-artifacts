import dace
from dace.sdfg.utils import set_nested_sdfg_parent_references

def used_inconns(ng: dace.sdfg.nodes.NestedSDFG) -> set[str]:
    inconns: set[str] = set(ng.in_connectors.keys())
    used: set[str] = set()
    for k, _ in ng.sdfg.all_nodes_recursive():
        # Nested SDFG's in-connectors are mapped to data-containers.
        if isinstance(k, dace.sdfg.nodes.AccessNode):
            if k.data in inconns:
                used.add(k.data)
        elif isinstance(k, dace.sdfg.state.ConditionalBlock):
            for b, _ in k.branches:
                if not b:
                    continue
                for c in inconns:
                    if c in b.as_string:
                        used.add(c)
    for k, _ in ng.sdfg.all_edges_recursive():
        if isinstance(k, dace.sdfg.graph.Edge) and isinstance(k.data, dace.sdfg.InterstateEdge):
            used = used | k.data.used_arrays(ng.sdfg.arrays)
    return used

def unused_inconns(ng: dace.sdfg.nodes.NestedSDFG) -> set[str]:
    inconns: set[str] = set(ng.in_connectors.keys())
    return inconns - used_inconns(ng)

def remove_unused_inconnectors_from_nestedsdfg(g: dace.SDFG):
    set_nested_sdfg_parent_references(g)
    for ng, ng_state in g.all_nodes_recursive():
        if not isinstance(ng, dace.sdfg.nodes.NestedSDFG):
            continue
        unused = unused_inconns(ng)
        print(f"Removing unused inconnectors from Nested SDFG({ng.guid}): {unused}")
        for c in unused:
            ng.sdfg.remove_data(c)
            for ie in ng.sdfg.parent_sdfg.in_edges_by_connector(ng, c):
                ng_state.remove_memlet_path(ie)

from dace import SDFG
from dace.sdfg.nodes import MapEntry, NestedSDFG


def unique_names(sdfgs: list[SDFG]) -> None:
    for i, sdfg in enumerate(sdfgs):
        sdfg.function_suffix = "_" + str(i)
        visited = set()
        for n, parent in sdfg.all_nodes_recursive():
            if n in visited:
                continue
            if isinstance(n, MapEntry):
                n.map.label = f"{n.map.label}{sdfg.function_suffix}"
                n.label = f"{n.label}{sdfg.function_suffix}"
                visited.add(n.map)
                visited.add(n)
            if isinstance(n, NestedSDFG):
                n.sdfg.function_suffix = "_" + str(i)
                visited.add(n)
import dace
import typing

def unique_names(sdfgs: typing.List[dace.SDFG]):
    for i, sdfg in enumerate(sdfgs):
        sdfg.function_suffix = str(i)
        for n, parent in sdfg.all_nodes_recursive():
            if hasattr(n, "label") and not isinstance(n, dace.nodes.AccessNode):
                n.label = f"{n.label}_s{i}"
            if isinstance(n, dace.nodes.MapEntry):
                n.map.label = f"{n.map.label}_s{i}"
            if isinstance(n, dace.nodes.NestedSDFG):
                n.sdfg.function_suffix = str(i)
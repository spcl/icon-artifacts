import dace
from dace.sdfg.state import ControlFlowRegion

def _has_access_node_access(sdfg: dace.SDFG, name: str) -> bool:
    """Check if the scalar is accessed in the SDFG."""
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.AccessNode) and node.data == name:
                return True
    return False

def add_data_preserver_tasklets_impl(root: dace.SDFG, sdfg: dace.SDFG):
    in_connectors = sdfg.parent_nsdfg_node.in_connectors
    in_scalar_names = [name for name in in_connectors if isinstance(sdfg.arrays[name], dace.data.Scalar)]
    accessed_scalars = [_has_access_node_access(sdfg, name) for name in in_scalar_names]

    for scalar_name, has_access in zip(in_scalar_names, accessed_scalars):
        if has_access:
            # If the scalar is accessed, we do not need to add a data preserver tasklet
            pass
        else:
            # If the scalar is not accessed, we add a tasklet that reads it to prevent its removal
            first_block = sdfg.start_block
            if isinstance(first_block, dace.SDFGState):
                first_state = first_block
            else:
                assert isinstance(first_block, ControlFlowRegion)
                first_state = first_block.all_states()[0]


            tasklet = first_state.add_tasklet(
                name=f"preserve_{scalar_name}",
                inputs={"_in"},
                outputs={},
                code=f"{{ auto _tmp_no_use_sym_hack = _in; }};",
                language=dace.dtypes.Language.CPP,
                side_effects=True,
            )
            an = first_state.add_access(scalar_name)
            tasklet.add_in_connector("_in")
            first_state.add_edge(an, None, tasklet, "_in", dace.Memlet.from_array(scalar_name, sdfg.arrays[scalar_name]))

def add_data_preserver_tasklets(sdfg: dace.SDFG):
    for s in sdfg.all_states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                add_data_preserver_tasklets_impl(sdfg, n.sdfg)
import dace
from dace import SDFG
from dace.data import Array
from dace.memlet import Memlet
from dace.sdfg.nodes import MapEntry, AccessNode, Node
from dace.sdfg.state import ControlFlowRegion, ConditionalBlock, LoopRegion, SDFGState
from dace.sdfg import utils
from dace.sdfg.graph import Edge
from .get_num_parent_map_and_loop_scopes import get_num_parent_map_scopes
import copy
import typing
from typing import Sequence
from utils.rename import rename_on_if, rename_on_for
from dace.transformation.helpers import redirect_edge

def transify_kernel_scalars(sdfg: dace.SDFG, map_sched_type: dace.ScheduleType = dace.ScheduleType.GPU_Device):
    kernel_id = 0
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.MapEntry):
            # If the map is a kernel map, then we need to transify the scalars
            if node.map.schedule == map_sched_type and get_num_parent_map_scopes(sdfg, node, graph) == 0:
                out_data = {e.data.data for e in graph.out_edges(node) if e.data is not None and e.data.data is not None}
                inner_nodes = graph.all_nodes_between(node, graph.exit_node(node))
                transifies = any(isinstance(inner_node, dace.nodes.AccessNode) and inner_node.data not in out_data and not graph.sdfg.arrays[inner_node.data].transient and isinstance(graph.sdfg.arrays[inner_node.data], dace.data.Scalar) for inner_node in inner_nodes)
                if transifies:
                    kernel_id += 1
                name_mapping = dict()
                for inner_node in inner_nodes:
                    if (isinstance(inner_node, dace.nodes.AccessNode) and
                         inner_node.data not in out_data and
                         not graph.sdfg.arrays[inner_node.data].transient and
                         isinstance(graph.sdfg.arrays[inner_node.data], dace.data.Scalar)):
                            # If the access node is an output of the map, then we need to transify it
                            new_scalar_desc = copy.deepcopy(graph.sdfg.arrays[inner_node.data])
                            new_scalar_desc.transient = True
                            new_scalar_desc.storage = dace.dtypes.StorageType.Register
                            graph.sdfg.add_datadesc(f"{inner_node.data}_{kernel_id}", new_scalar_desc)
                            name_mapping[inner_node.data] = f"{inner_node.data}_{kernel_id}"
                for inner_node in inner_nodes:
                    if isinstance(inner_node, dace.nodes.AccessNode) and inner_node.data in name_mapping:
                        inner_node.data = name_mapping[inner_node.data]
                for edge in graph.all_edges(*inner_nodes):
                    if edge.data is not None and edge.data.data is not None:
                        if edge.data.data in name_mapping:
                            edge.data.data = name_mapping[edge.data.data]


def _find_parent_graph(sdfg: dace.SDFG, node: dace.nodes.Node):
    """Find the parent state of a node in a nested SDFG."""
    for n, g in sdfg.all_nodes_recursive():
        if n == node:
            return g
    raise ValueError(f"Node {node} not found in SDFG {sdfg.name}.")

def rm_connection_of_desc_to_nsdfg_node(nsdfg_node: dace.nodes.NestedSDFG, state: dace.SDFGState, desc_name: str):

    input_path = []
    output_path = []

    # Get in-edges in to the parent SDFG node
    if desc_name in nsdfg_node.in_connectors:
        cur_edge = next(iter(state.in_edges_by_connector(nsdfg_node, desc_name)))
        assert len(list(state.in_edges_by_connector(nsdfg_node, desc_name))) == 1, f"Multiple edges found for {nsdfg_node} with connector {desc_name}."
        while not isinstance(cur_edge.src, dace.nodes.AccessNode):
            input_path.append(cur_edge)
            cur_edge = next(iter(state.in_edges_by_connector(cur_edge.src, cur_edge.src_conn.replace("OUT_", "IN_"))))
        input_path.append(cur_edge)

    # Get out-edges out from the parent SDFG node
    if desc_name in nsdfg_node.out_connectors:
        cur_edge = next(iter(state.out_edges_by_connector(nsdfg_node, desc_name)))
        assert len(list(state.out_edges_by_connector(nsdfg_node, desc_name))) == 1, f"Multiple edges found for {nsdfg_node} with connector {desc_name}."
        while not isinstance(cur_edge.dst, dace.nodes.AccessNode):
            output_path.append(cur_edge)
            cur_edge = next(iter(state.out_edges_by_connector(cur_edge.dst, cur_edge.dst_conn.replace("IN_", "OUT_"))))
        output_path.append(cur_edge)

    # Remove all edges in the input and output paths
    for edge in input_path:
        state.remove_edge(edge)
        if edge.src_conn in edge.src.out_connectors:
            edge.src.remove_out_connector(edge.src_conn)
        if edge.dst_conn in edge.dst.in_connectors:
            edge.dst.remove_in_connector(edge.dst_conn)
        if edge == input_path[-1]:
            if state.degree(edge.src) == 0:
                state.remove_node(edge.src)
    for edge in output_path:
        state.remove_edge(edge)
        if edge.src_conn in edge.src.out_connectors:
            edge.src.remove_out_connector(edge.src_conn)
        if edge.dst_conn in edge.dst.in_connectors:
            edge.dst.remove_in_connector(edge.dst_conn)
        if edge == output_path[-1]:
            if state.degree(edge.dst) == 0:
                state.remove_node(edge.dst)

def rm_from_input_output(root: dace.SDFG, sub_sdfg: dace.SDFG, desc_name: str):
    sub_sdfg.remove_data(desc_name, True)
    parent_nsdfg_node = sub_sdfg.parent_nsdfg_node
    if parent_nsdfg_node is None:
        return
    parent_state = _find_parent_graph(root, parent_nsdfg_node)
    while parent_nsdfg_node is not None:
        rm_connection_of_desc_to_nsdfg_node(parent_nsdfg_node, parent_state, desc_name)
        parent_nsdfg_node = parent_state.sdfg.parent_nsdfg_node
        if parent_nsdfg_node is not None:
            parent_state = _find_parent_graph(root, parent_nsdfg_node)


def _get_bfs_states_list(cfg: LoopRegion):
    """Get a list of states in the BFS order."""
    nodes = list(cfg.bfs_nodes(cfg.start_block))

    # Assume Top-level Nodes are like these:
    # [CFG0, State0, CFG1]
    # Then this will expand it further:
    # [CFG0.0, State0.0, State0, State1.0, State1.1]
    # Until there are only states:
    # [State0.0.0, State0.0.1, State0.0, State0 State1.0, State1.1]
    # For IfCFG -> Do it for the branches left-to-right.

    len_changed = True
    while len_changed:
        new_nodes = []
        len_changed = False
        for i, node in enumerate(nodes):
            if isinstance(node, dace.SDFGState):
                new_nodes.append(node)
            elif isinstance(node, LoopRegion):
                nn = node.bfs_nodes(node.start_block)
                len_changed = True
                new_nodes += list(nn)
            elif isinstance(node, ConditionalBlock):
                bodies = []
                for _, body in node.branches:
                    bodies += list(body.bfs_nodes(body.start_block))
                new_nodes += list(bodies)
                len_changed = True
            else:
                raise ValueError(f"Unexpected node type {type(node)} in BFS traversal of LoopRegion.")
        nodes = new_nodes

    return nodes

def _is_always_write_first_impl_cfg(cfg: ControlFlowRegion, desc_name: str):
    for node in cfg.bfs_nodes(cfg.start_block):
        if isinstance(node, dace.SDFGState):
            val =_is_always_write_first_impl_state(node, desc_name)
            if val is not None:
                return val
        elif isinstance(node, ConditionalBlock):
            val = _is_always_write_first_impl_if(node, desc_name)
            if val is not None:
                return val
        else:
            val = _is_always_write_first_impl_cfg(node, desc_name)
            if val is not None:
                return val

    return None

def _is_always_write_first_impl_state(cfg: ControlFlowRegion, desc_name: str):
    assert isinstance(cfg, dace.SDFGState), f"Expected cfg to be a SDFGState, got {type(cfg)}."
    state = cfg
    snode = state.parent_graph
    has_desc_in_state = any([node.data == desc_name for node in state.nodes() if isinstance(node, dace.nodes.AccessNode)])

    if has_desc_in_state:
        always_write_first = all([(snode.in_degree(node) > 0) for node in snode.nodes() if isinstance(node, dace.nodes.AccessNode) and node.data == desc_name])
        return always_write_first

    return None


def _is_always_write_first_impl_if(cfg: ControlFlowRegion, desc_name: str):
    assert isinstance(cfg, ConditionalBlock), f"Expected cfg to be a ConditionalBlock, got {type(cfg)}."
    _is_write_first_vals = [_is_always_write_first_impl_cfg(body, desc_name) for _, body in cfg.branches]

    if all(v is None or v is True for v in _is_write_first_vals):
        return True

    return None

def is_always_write_first(cfg: ControlFlowRegion, desc_name: str):
    return _is_always_write_first_impl_cfg(cfg, desc_name)

def transify_targeted_scalar(sdfg: dace.SDFG, desc_candidate_names: typing.Set[str]):
    # Filter candidate names to only include scalars
    desc_names = set()
    for name in desc_candidate_names:
        if name in sdfg.arrays and isinstance(sdfg.arrays[name], dace.data.Scalar):
            desc_names.add(name)

    for snode, graph in sdfg.all_nodes_recursive():
        # Only apply to SDFGs of LoopRegions (OMP Private => Means the SDFG within a For CFG in SDFG)
        if isinstance(snode, LoopRegion):
            cfg = snode # snode.sdfg is the parent SDFG

            # cfg.all_control_flow_regions() -> should give states parent-first
            # all_nodes_are_states = all(isinstance(node, dace.SDFGState) for node in cfg.nodes())
            # if not all_nodes_are_states:
            #    continue

            path_graph = all(cfg.in_degree(node) <= 1 and cfg.out_degree(node) <= 1 for node in cfg.nodes())
            assert path_graph, "Only path graphs (all top level nodes have in_degree <= 1  and out_degree <= 1) are supported for transifying scalars in LoopRegions."

            # Build a replacement dictionary for the scalars
            replace_dict = dict()
            for desc_name in desc_names:
                # Check if the SDFG has the desc_name accessed in an access node
                has_desc = any([node.data == desc_name for state in snode.all_states() for node in state.nodes() if isinstance(node, dace.nodes.AccessNode)])
                # No access skip the rest
                if not has_desc:
                    continue

                # Need to be write-first always to be a real private/threadlocal scalar
                # BFS the states, the moment we see write-first or non-write-first access pattern then stop
                # As if in state 0, it is written first, it does not matter what happens in state 1

                # If CFG bfs recursively, what matters is the state
                # If IfBlock is encountered, ensure it is write-first in all branches (if not writes None is accepted too)
                desc_is_write_first = is_always_write_first(cfg, desc_name)

                # If None then this scalar is not used in the ForCFG
                # If true, then it can become a transient
                # If not write-first (e.g. read before completely writing to), then we can transify it
                if desc_is_write_first is not None and desc_is_write_first is True:
                    # Add the local transient to the SDFG
                    desc = snode.sdfg.arrays[desc_name]
                    name = desc_name + f"_local"
                    if name not in snode.sdfg.arrays:
                        copydesc = copy.deepcopy(desc)
                        copydesc.transient = True
                        copydesc.storage = dace.dtypes.StorageType.Register
                        snode.sdfg.add_datadesc(name, copydesc)
                    # Add the name to the replacement dictionary
                    replace_dict[desc_name] = name

            # Replace the scalars in the SDFG
            cfg.replace_dict(repl=replace_dict)
            for src, dst in replace_dict.items():
                rename_on_if(cfg, src, dst)
                # rename_on_for(cfg, src, dst) # This is OK, no need to call again as the current f2dace commit replaces for loops
                # Repl-name might make the the transient local accesses to be-non transient due to name change on the data container
                if dst in snode.sdfg.arrays:
                    desc = snode.sdfg.arrays[dst]
                    assert isinstance(desc, dace.data.Scalar), f"Expected {dst} to be a scalar, got {type(desc)}."
                    if desc.transient is False:
                        desc.transient = True
                        desc.storage = dace.dtypes.StorageType.Register


def identify_persistent_scalars_with_writes(g: SDFG) -> set[str]:
    return {
        a for a, d in g.arrays.items()
        if isinstance(d, dace.data.Scalar)
        and not d.transient
        and any(n for n, st in g.all_nodes_recursive() 
                if isinstance(n, dace.nodes.AccessNode) 
                and n.data == a
                and len(st.in_edges(n)) > 0)}

def transify_targeted_scalar_general_version(g: SDFG, scalars: Sequence[str]):
    # Transify scalars in the SDFG to be transient and local

    # First, build a map of scalars to their new names
    scalar_map = {}
    for scalar in scalars:
        if scalar not in g.arrays:
            print(f"Warning: Scalar {scalar} not found in SDFG {g.name}. Skipping transification.")
            continue
        if not isinstance(g.arrays[scalar], dace.data.Scalar):
            print(f"Warning: {scalar} is not a scalar in SDFG {g.name}. Skipping transification.")
            continue
        if g.arrays[scalar].transient:
            print(f"Warning: {scalar} is already transient in SDFG {g.name}. Skipping transification.")
            continue
        # Create a new scalar with the same properties but transient
        new_scalar_name = f"{scalar}_transified"
        if new_scalar_name in g.arrays:
            print(f"Warning: {new_scalar_name} already exists in SDFG {g.name}. Skipping transification.")
            continue
        new_scalar_desc = copy.deepcopy(g.arrays[scalar])
        new_scalar_desc.transient = True
        new_scalar_desc.storage = dace.dtypes.StorageType.Register
        g.add_datadesc(new_scalar_name, new_scalar_desc)
        scalar_map[scalar] = new_scalar_name

    # Then, replace all occurrences of the scalar with the new scalar in one pass.
    # Since we don't want to change the original scalar, we need to replace it using the `ControlFlowRegion` method.
    for node in g.nodes():
        node.replace_dict(scalar_map)
    for edge in g.edges():
        edge.data.replace_dict(scalar_map)

    # Finally, initialize the new scalars in the SDFG
    start_state = g.start_state
    assert start_state is not None, f"Expected SDFG {g.name} to have a start state."
    for scalar, new_scalar in scalar_map.items():
        assert scalar in g.arrays, f"Expected {scalar} to be in SDFG {g.name} arrays."
        assert new_scalar in g.arrays, f"Expected {new_scalar} to be in SDFG {g.name} arrays."
        start_state.add_edge(
            start_state.add_access(scalar),
            None,
            start_state.add_access(new_scalar),
            None,
            dace.memlet.Memlet.from_array(new_scalar, g.arrays[new_scalar])
        )

def transify_targeted_array(sdfg: dace.SDFG, desc_candidate_names: typing.Set[str]):
    # Filter candidate names to only include arrays
    desc_names = set()
    for name in desc_candidate_names:
        if name in sdfg.arrays and isinstance(sdfg.arrays[name], dace.data.Array):
            desc_names.add(name)

    for snode, graph in sdfg.all_nodes_recursive():
        # Only apply to SDFGs of LoopRegions (OMP Private => Means the SDFG within a For CFG in SDFG)
        if isinstance(snode, LoopRegion):
            cfg = snode # snode.sdfg is the parent SDFG

            # cfg.all_control_flow_regions() -> should give states parent-first
            # all_nodes_are_states = all(isinstance(node, dace.SDFGState) for node in cfg.nodes())
            # if not all_nodes_are_states:
            #    continue

            path_graph = all(cfg.in_degree(node) <= 1 and cfg.out_degree(node) <= 1 for node in cfg.nodes())
            assert path_graph, "Only path graphs (all top level nodes have in_degree <= 1  and out_degree <= 1) are supported for transifying scalars in LoopRegions."

            # Build a replacement dictionary for the scalars
            replace_dict = dict()
            #print(f"Transifying targeted arrays in {snode.sdfg.name} for {snode.name} with candidates: {desc_names}")
            for desc_name in desc_names:
                # Check if the SDFG has the desc_name accessed in an access node
                has_desc = any([node.data == desc_name for state in snode.all_states() for node in state.nodes() if isinstance(node, dace.nodes.AccessNode)])
                # No access skip the rest
                if not has_desc:
                    continue

                # Need to be write-first always to be a real private/threadlocal scalar
                # BFS the states, the moment we see write-first or non-write-first access pattern then stop
                # As if in state 0, it is written first, it does not matter what happens in state 1

                # If CFG bfs recursively, what matters is the state
                # If IfBlock is encountered, ensure it is write-first in all branches (if not writes None is accepted too)
                desc_is_write_first = is_always_write_first(cfg, desc_name)

                #print(f"Checking {desc_name} in {snode.sdfg.name} in {snode.name} for write-first: {desc_is_write_first}")

                # Now for access nodes
                for state in snode.all_states():
                    for node in state.nodes():
                        # If the node is access node to desc, then:
                        # memlet1 -> AN -> memlet1
                        #            AN -> memlet2
                        # [0] -> scalar_AN -> [0]
                        # and AN -> memlet2[1]
                        if isinstance(node, dace.nodes.AccessNode) and node.data == desc_name:
                            ies = {ie for ie in state.in_edges(node)}
                            oes = {oe for oe in state.out_edges(node)}

                            if len(ies) == 1 and len(oes) > 0: # Input needs to be always degree one
                                matched_edges = set()
                                matched_in_edges = set()
                                matched_out_edges = set()
                                for ie in ies:
                                    if ie in matched_in_edges:
                                        continue
                                    for oe in oes:
                                        if oe in matched_out_edges:
                                            continue
                                        # Normall it is nlev, where it is offset 1 if 3D and offset 0 if 2D
                                        # exner_ic is special case, only in predictor pre tho
                                        #if (ie.data.data == "z_exner_ic"):
                                        #    print(ie.data.subset[1] == oe.data.subset[1], len(ie.data.subset), sdfg.label)
                                        #    #raise Exception("Unexpected z_exner_ic access in transify_targeted_array, this is a bug.")
                                        if ie.data.data == "z_exner_ic" and "predictor_pre" in sdfg.label:
                                            if ie.data.subset[1] == oe.data.subset[1] and len(ie.data.subset) == 2:
                                                matched_edges.add((ie, oe))
                                                matched_in_edges.add(ie)
                                                matched_out_edges.add(oe)
                                        else:
                                            if ie.data.data == oe.data.data and (
                                            (ie.data.subset[1] == oe.data.subset[1] and len(ie.data.subset) == 3) or
                                            (ie.data.subset[0] == oe.data.subset[0] and len(ie.data.subset) < 3)):
                                                matched_edges.add((ie, oe))
                                                matched_in_edges.add(ie)
                                                matched_out_edges.add(oe)
                                #sdfg.save("a.sdfgz", compress=True)
                                assert ies - matched_in_edges == set(), f"Expected all in-edges ({len(ies)}) to be matched ({len(matched_edges)}), got unmatched: {ies - matched_in_edges}."

                                unmatched_out_edges = oes - matched_out_edges
                                assert len(matched_edges) == len(ies), f"Expected all in-edges ({len(ies)}) to be matched, got unmatched: {ies - matched_in_edges} ({ies})."
                                assert len(unmatched_out_edges) == len(oes) - len(matched_out_edges)
                                unmatched_in_edges = ies - matched_in_edges
                                assert len(unmatched_in_edges) == 0

                                #print()
                                #print("==")
                                #print(matched_edges)
                                #print("==")
                                #print(matched_in_edges)
                                #print("==")
                                #print(matched_out_edges)
                                #print("==")
                                #print(unmatched_out_edges)
                                #print("==")
                                #print()

                                # replace with a scalar
                                nds = set()
                                for ie, oe in matched_edges:
                                    nd = ie.dst
                                    nds.add(nd)
                                    n_name = f"{ie.data.data}_local"
                                    if n_name not in state.sdfg.arrays:
                                        n_desc = state.sdfg.add_scalar(
                                            n_name, dtype=snode.sdfg.arrays[ie.data.data].dtype,
                                            transient=True, storage=dace.dtypes.StorageType.Register
                                        )
                                    n_access = state.add_access(n_name)
                                    assert isinstance(snode.sdfg.arrays[n_name], dace.data.Scalar), f"Expected {n_name} to be a scalar, got {type(snode.sdfg.arrays[n_name])}."
                                    ie_data = dace.memlet.Memlet.from_array(
                                        f"{ie.data.data}_local", snode.sdfg.arrays[n_name]
                                    )
                                    oe_data = dace.memlet.Memlet.from_array(
                                        f"{ie.data.data}_local", snode.sdfg.arrays[n_name]
                                    )
                                    ie_dst = n_access
                                    oe_src = n_access
                                    if ie in state.edges():
                                        state.remove_edge(ie)
                                    if oe in state.edges():
                                        state.remove_edge(oe)
                                    state.add_edge(
                                        ie.src, ie.src_conn, ie_dst, None, ie_data
                                    )
                                    state.add_edge(
                                        oe_src, None, oe.dst, oe.dst_conn, oe_data
                                    )
                                    nds.add(nd)

                                for nd in nds:
                                    state.remove_node(nd)

                                # For
                                nds = set()
                                for oe in unmatched_out_edges:
                                    an = state.add_access(f"{oe.data.data}")
                                    if oe in state.edges():
                                        state.remove_edge(oe)
                                    state.add_edge(
                                        an, None, oe.dst, oe.dst_conn,
                                        copy.deepcopy(oe.data)
                                    )
                                    nds.add(oe.src)
                                for nd in nds:
                                    if nd in state.nodes():
                                        state.remove_node(nd)

                #sdfg.save("sdfg_before.sdfgz", compress=True)
                #raise Exception("uwu")
    sdfg.validate()

#def transify_targeted_scalar_double_out():
#    # Write -> AN -> Read1 (write-then-reuse)
#    #          AN -> Read2
#    # Make it so that we read AN in Read2
#    # We write to scalar_AN and sue it, and write to AN Read1
#    pass


def retransify_scalar_with_local_prefix(root: dace.SDFG, sdfg: dace.SDFG):
    for arr_name, arr_desc in sdfg.arrays.items():
        if (arr_name.endswith("_local") and isinstance(arr_desc, dace.data.Scalar) and
            not arr_name.startswith("i_startidx") and not arr_name.startswith("i_endidx") and
            not arr_name.startswith("je_") and not arr_name.startswith("jb_")):
            if arr_desc.transient is False:
                arr_desc.transient = True
                arr_desc.storage = dace.dtypes.StorageType.Register
            # Remove in and out connectors
            parent_nsdfg_node = sdfg.parent_nsdfg_node
            if parent_nsdfg_node is not None:
                parent_state = _find_parent_graph(root, parent_nsdfg_node)
                rm_connection_of_desc_to_nsdfg_node(parent_nsdfg_node, parent_state, arr_name)

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                retransify_scalar_with_local_prefix(root, node.sdfg)


def add_copy_tasklet(st: SDFGState, acc: AccessNode, dst: Node, dst_conn: str | None, dst_memlet: str):
    g = st.sdfg
    t = st.add_tasklet('copyblind', {'inp'}, {'out'}, 'out = inp')
    st.add_edge(acc, None, t, 'inp', g.make_array_memlet(acc.data))
    st.add_edge(t, 'out', dst, dst_conn, Memlet(dst_memlet))

def transify_sneaky_array_writes_inside_map(g: SDFG):
    tCounter = 0 # Counter to disambiguate names
    for st, _ in g.all_nodes_recursive():
        if not isinstance(st, SDFGState):
            continue
        node_scopes = st.scope_dict()
        for mE in utils.scope_aware_topological_sort(st, reverse=True):
            if not isinstance(mE, MapEntry):
                continue
            mX = st.exit_node(mE)
            out_data = [ed.data.data for ed in st.out_edges(mX) if isinstance(ed.data, Memlet) and ed.data.data]
            array_accs = [n for n in st.all_nodes_between(mE, mX)
                        if isinstance(n, AccessNode)
                        and isinstance(n.desc(g), Array)
                        and n.data not in out_data
                        and node_scopes[n] is mE
                        and st.in_degree(n) == 1]
            if not array_accs:
                continue
            for acc in array_accs:
                # Verify that the rewrite is valid.
                in_set = None
                for ed in st.in_edges(acc):
                    in_set = ed.data.dst_subset
                valid_rewrite = True
                for ed in st.out_edges(acc):
                    if ed.data.src_subset != in_set:
                        valid_rewrite = False
                        break
                if not valid_rewrite:
                    print(f"Transify ({mE}): The read offsets and write offsets are not the same for {acc.data}. Skipping.")
                    continue

                # Actual rewrite.
                print(f"Transify ({mE}): Rewriting {acc.data} as a transient inside map.")
                while f"{acc.data}_transified_{tCounter}" in g.arrays:
                    tCounter += 1
                acc_local, _ = g.add_scalar(f"{acc.data}_transified_{tCounter}", acc.desc(g).dtype, transient=True)
                acc_local = st.add_access(acc_local)

                for ed in st.in_edges(acc):
                    redirect_edge(st, ed, new_dst=acc_local, new_memlet=g.make_array_memlet(acc_local.data))
                for ed in st.out_edges(acc):
                    redirect_edge(st, ed, new_src=acc_local, new_memlet=g.make_array_memlet(acc_local.data))
                add_copy_tasklet(st, acc_local, mX, f"IN_{acc_local.data}", f"{acc.data}[{in_set}]")

                cmE, cmX = mE, mX
                while cmX:
                    cmX.add_scope_connectors(acc_local.data)
                    nmE = node_scopes[cmE]
                    nmX = st.exit_node(nmE) if nmE else None
                    if nmX:
                        st.add_edge(cmX, f"OUT_{acc_local.data}", nmX, f"IN_{acc_local.data}", g.make_array_memlet(acc.data))
                    else:
                        st.add_edge(cmX, f"OUT_{acc_local.data}", acc, None, g.make_array_memlet(acc.data))
                    cmE, cmX = nmE, nmX
    g.validate()

"""
This pass separates states with multiple concurrent subgraphs into multiple states.
"""

import dace
from dace.sdfg import SDFG
from dace.sdfg import utils as sdutil
from dace.sdfg.state import SDFGState
from dace.transformation import transformation
from dace.properties import make_properties, Property
from typing import Optional
from dace import nodes
import copy


@make_properties
class MapStateFission(transformation.SingleStateTransformation):
    access_node = transformation.PatternNode(dace.nodes.AccessNode)

    allow_transients = Property(dtype=bool, default=False)

    @classmethod
    def expressions(cls):
        return [sdutil.node_path_graph(cls.access_node)]

    def annotates_memlets(self) -> bool:
        return True

    def can_be_applied(
        self,
        state: dace.SDFGState,
        expr_index: int,
        sdfg: dace.SDFG,
        permissive: bool = False,
    ):
        # Don't split if the access node is wrapped in a subgraph
        if state.entry_node(self.access_node) is not None:
            return False

        # Skip transients if not allowed
        if (
            self.allow_transients is False
            and sdfg.arrays[self.access_node.data].transient
        ):
            return False

        # Must have exactly one predecessor and one successor
        preds = state.predecessors(self.access_node)
        succs = state.successors(self.access_node)
        if len(preds) != 1 or len(succs) != 1:
            return False

        # Predecessor and successor must be maps
        if not isinstance(preds[0], dace.nodes.MapExit) or not isinstance(
            succs[0], dace.nodes.MapEntry
        ):
            return False

        return True

    def apply(self, state: SDFGState, sdfg: SDFG):
        node = self.access_node
        label = state.label + "_F"
        MapStateFission.state_fission_after_deterministic(state, node, label)

    @staticmethod
    def state_fission_after_deterministic(
        state: SDFGState, node: nodes.Node, label: Optional[str] = None
    ) -> SDFGState:
        newstate = state.parent_graph.add_state_after(state, label=label)

        # Bookkeeping
        nodes_to_move = set([node])
        boundary_nodes = set()
        orig_edges = set()

        # Collect predecessors
        if not isinstance(node, nodes.AccessNode):
            for edge in state.in_edges(node):
                for e in state.memlet_path(edge):
                    nodes_to_move.add(e.src)
                    orig_edges.add(e)

        # Collect nodes_to_move
        for edge in state.edge_bfs(node):
            nodes_to_move.add(edge.dst)
            orig_edges.add(edge)

            if not isinstance(edge.dst, nodes.AccessNode):
                for iedge in state.in_edges(edge.dst):
                    if iedge == edge:
                        continue

                    for e in state.memlet_path(iedge):
                        nodes_to_move.add(e.src)
                        orig_edges.add(e)

        # Define boundary nodes
        for node in nodes_to_move:
            if isinstance(node, nodes.AccessNode):
                for iedge in state.in_edges(node):
                    if iedge.src not in nodes_to_move:
                        boundary_nodes.add(node)
                        break

                if node in boundary_nodes:
                    continue

                for oedge in state.out_edges(node):
                    if oedge.dst not in nodes_to_move:
                        boundary_nodes.add(node)
                        break

        # Duplicate boundary nodes
        new_nodes = {}
        for node in boundary_nodes:
            node_ = copy.deepcopy(node)
            state.add_node(node_)
            new_nodes[node] = node_

        for edge in state.edges():
            if edge.src in boundary_nodes and edge.dst in boundary_nodes:
                state.add_edge(
                    new_nodes[edge.src],
                    edge.src_conn,
                    new_nodes[edge.dst],
                    edge.dst_conn,
                    copy.deepcopy(edge.data),
                )
            elif edge.src in boundary_nodes:
                state.add_edge(
                    new_nodes[edge.src],
                    edge.src_conn,
                    edge.dst,
                    edge.dst_conn,
                    copy.deepcopy(edge.data),
                )
            elif edge.dst in boundary_nodes:
                state.add_edge(
                    edge.src,
                    edge.src_conn,
                    new_nodes[edge.dst],
                    edge.dst_conn,
                    copy.deepcopy(edge.data),
                )

        # Move nodes
        state.remove_nodes_from(nodes_to_move)

        for n in nodes_to_move:
            if isinstance(n, nodes.NestedSDFG):
                # Set the new parent state
                n.sdfg.parent = newstate

        newstate.add_nodes_from(nodes_to_move)

        orig_edges = list(orig_edges)
        orig_edges.sort(key=lambda x: x.data.data if x.data.data is not None else "")
        for e in orig_edges:
            newstate.add_edge(e.src, e.src_conn, e.dst, e.dst_conn, e.data)

        return newstate


"""
This pass duplicates access nodes with multiple edges, such that each access
node has at most one incoming or one outgoing edge.
"""


@make_properties
class AccessDuplicate(transformation.SingleStateTransformation):
    access_node = transformation.PatternNode(dace.nodes.AccessNode)

    allow_transients = Property(dtype=bool, default=False)

    @classmethod
    def expressions(cls):
        return [sdutil.node_path_graph(cls.access_node)]

    def annotates_memlets(self) -> bool:
        return True

    def can_be_applied(
        self,
        state: dace.SDFGState,
        expr_index: int,
        sdfg: dace.SDFG,
        permissive: bool = False,
    ):
        # Node must have only incoming or outgoing edges
        if (
            state.in_degree(self.access_node) != 0
            and state.out_degree(self.access_node) != 0
        ):
            return False

        # At least two incoming or outgoing edges
        if (
            state.in_degree(self.access_node) < 2
            and state.out_degree(self.access_node) < 2
        ):
            return False

        # Not in a map
        if state.entry_node(self.access_node) is not None:
            return False

        # If node is read, it cannot be written to in two independent subgraphs
        if (
            state.out_degree(self.access_node) > 1
            and len(sdutil.concurrent_subgraphs(state)) > 1
        ):
            for node in state.nodes():
                if not isinstance(node, dace.nodes.AccessNode):
                    continue
                if node.data == self.access_node.data and state.in_degree(node) > 0:
                    return False

        # Skip transients if not allowed
        if (
            self.allow_transients is False
            and sdfg.arrays[self.access_node.data].transient
        ):
            return False

        return True

    def apply(self, state: SDFGState, sdfg: SDFG):
        new_node = copy.deepcopy(self.access_node)
        state.add_node(new_node)

        for edge in state.in_edges(self.access_node):
            state.add_edge(
                edge.src,
                edge.src_conn,
                new_node,
                edge.dst_conn,
                copy.deepcopy(edge.data),
            )
            state.remove_edge(edge)
            break

        for edge in state.out_edges(self.access_node):
            state.add_edge(
                new_node,
                edge.src_conn,
                edge.dst,
                edge.dst_conn,
                copy.deepcopy(edge.data),
            )
            state.remove_edge(edge)
            break

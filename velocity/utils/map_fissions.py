from copy import deepcopy
from typing import Union, Set

import networkx
from dace import SDFGState, SDFG, InterstateEdge
from dace.frontend.fortran.ast_utils import singular
from dace.properties import make_properties
from dace.sdfg.nodes import MapEntry, NestedSDFG, MapExit, AccessNode
from dace.sdfg.utils import node_path_graph
from dace.transformation import SingleStateTransformation, PatternNode


@make_properties
class YoloMapFission(SingleStateTransformation):
    map_entry = PatternNode(MapEntry)
    nested_sdfg = PatternNode(NestedSDFG)
    map_exit = PatternNode(MapExit)

    @classmethod
    def expressions(cls):
        return [node_path_graph(cls.map_entry, cls.nested_sdfg, cls.map_exit)]

    def can_be_applied(self, s: SDFGState, expr_index: int, g: SDFG, permissive: bool = False) -> bool:
        return set(s.all_nodes_between(self.map_entry, self.map_exit)) == {self.nested_sdfg}

    @staticmethod
    def _partition_nodes(g: SDFG):
        # Contract the cycles.
        gx = networkx.DiGraph()
        gx.add_nodes_from(u.guid for u in g.nodes())
        gx.add_edges_from((ed.src.guid, ed.dst.guid) for ed in g.edges())
        cyx = networkx.simple_cycles(gx)
        contractions = networkx.utils.UnionFind()
        for cy in cyx:
            contractions.union(cy)
        for u in gx.nodes:
            contractions.union(u)
        anticontractions = {}
        for u in g.nodes():
            assert u.guid in contractions
            cont = contractions[u.guid]
            if cont not in anticontractions:
                anticontractions[cont] = []
            anticontractions[cont].append(u.guid)
        # Then, topologically sort the contracted graph to get a maximal fissioned partition.
        gx = networkx.DiGraph()
        gx.add_nodes_from(contractions[u.guid] for u in g.nodes())
        gx.add_edges_from((contractions[ed.src.guid], contractions[ed.dst.guid]) for ed in g.edges()
                          if contractions[ed.src.guid] != contractions[ed.dst.guid])
        orderd_nodes = list(anticontractions[u] for u in networkx.topological_sort(gx))

        return orderd_nodes

    @staticmethod
    def _add_replica_state_after(s: SDFGState, g:SDFG) -> SDFGState:
        nus = deepcopy(s)
        for u in nus.nodes():
            if isinstance(u, NestedSDFG):
                u.sdfg.parent_sdfg = g
        nus.parent = g
        g.add_node(nus, ensure_unique_name=True)
        for ed in g.out_edges(s):
            g.add_edge(nus, ed.dst, ed.data)
            g.remove_edge(ed)
        g.add_edge(s, nus, InterstateEdge())
        return nus

    @staticmethod
    def _remove_all_nodes_with_guids(s: Union[SDFGState, SDFG], guids: Set[str]):
        for u in s.nodes():
            if u.guid in guids:
                s.remove_node(u)

    @staticmethod
    def _remove_all_nodes_except_guids(s: Union[SDFGState, SDFG], guids: Set[str]):
        for u in s.nodes():
            if u.guid not in guids:
                s.remove_node(u)

    @staticmethod
    def _remove_isolated_access_nodes(s: SDFGState):
        for u in s.nodes():
            if isinstance(u, AccessNode) and not s.degree(u):
                s.remove_node(u)

    def apply(self, s: SDFGState, g: SDFG):
        GUIDS = {self.map_entry.guid, self.nested_sdfg.guid, self.map_exit.guid}
        ACC_GUIDS = {u.guid for u in s.nodes() if isinstance(u, AccessNode)}
        nus = self._add_replica_state_after(s, g)
        self._remove_all_nodes_except_guids(s, GUIDS.union(ACC_GUIDS))
        self._remove_all_nodes_with_guids(nus, GUIDS)
        self._remove_isolated_access_nodes(s)
        self._remove_isolated_access_nodes(nus)

        ordered_nodes = self._partition_nodes(self.nested_sdfg.sdfg)
        ordered_nodes = [singular(u for u in us) for us in ordered_nodes]
        for _ in range(1):
            upto = len(ordered_nodes) - 1
            # Pt: 1
            nus = self._add_replica_state_after(s, g)
            tgt_node = singular(u for u in self.nested_sdfg.sdfg.nodes() if u.guid == ordered_nodes[upto])
            tgt_edge = singular(ed for ed in self.nested_sdfg.sdfg.in_edges(tgt_node))
            crossing_edge = singular(ed for ed in g.in_edges(nus))
            crossing_edge.data = deepcopy(tgt_edge.data)
            # Pt: 2
            ng = singular(u for u in s.nodes() if isinstance(u, NestedSDFG)).sdfg
            GUIDS = {ordered_nodes[0], *ordered_nodes[1:upto]}
            self._remove_all_nodes_except_guids(ng, GUIDS)
            # Pt: 3
            ng = singular(u for u in nus.nodes() if isinstance(u, NestedSDFG)).sdfg
            prelude = singular(u for u in ng.nodes() if u.guid == ordered_nodes[0])
            work = singular(u for u in ng.nodes() if u.guid == ordered_nodes[upto])
            tgt_edge = singular(ed for ed in ng.out_edges(prelude))
            ng.add_edge(prelude, work, deepcopy(tgt_edge.data))
            GUIDS = {ordered_nodes[0], *ordered_nodes[upto:]}
            self._remove_all_nodes_except_guids(ng, GUIDS)

            ordered_nodes = ordered_nodes[:upto]

        for _ in range(1):
            upto = 3
            # Pt: 1
            nus = self._add_replica_state_after(s, g)
            tgt_node = singular(u for u in self.nested_sdfg.sdfg.nodes() if u.guid == ordered_nodes[upto])
            tgt_edge = singular(ed for ed in self.nested_sdfg.sdfg.in_edges(tgt_node))
            crossing_edge = singular(ed for ed in g.in_edges(nus))
            crossing_edge.data = deepcopy(tgt_edge.data)
            # Pt: 2
            ng = singular(u for u in s.nodes() if isinstance(u, NestedSDFG)).sdfg
            GUIDS = {ordered_nodes[0], *ordered_nodes[1:upto]}
            self._remove_all_nodes_except_guids(ng, GUIDS)
            # Pt: 3
            ng = singular(u for u in nus.nodes() if isinstance(u, NestedSDFG)).sdfg
            prelude = singular(u for u in ng.nodes() if u.guid == ordered_nodes[0])
            work = singular(u for u in ng.nodes() if u.guid == ordered_nodes[upto])
            tgt_edge = singular(ed for ed in ng.out_edges(prelude))
            ng.add_edge(prelude, work, deepcopy(tgt_edge.data))
            GUIDS = {ordered_nodes[0], *ordered_nodes[upto:]}
            self._remove_all_nodes_except_guids(ng, GUIDS)

            ordered_nodes = ordered_nodes[:upto]

        for _ in range(1):
            upto = 2
            # Pt: 1
            nus = self._add_replica_state_after(s, g)
            tgt_node = singular(u for u in self.nested_sdfg.sdfg.nodes() if u.guid == ordered_nodes[upto])
            tgt_edge = singular(ed for ed in self.nested_sdfg.sdfg.in_edges(tgt_node))
            crossing_edge = singular(ed for ed in g.in_edges(nus))
            crossing_edge.data = deepcopy(tgt_edge.data)
            # Pt: 2
            ng = singular(u for u in s.nodes() if isinstance(u, NestedSDFG)).sdfg
            GUIDS = {ordered_nodes[0], *ordered_nodes[1:upto]}
            self._remove_all_nodes_except_guids(ng, GUIDS)
            # Pt: 3
            ng = singular(u for u in nus.nodes() if isinstance(u, NestedSDFG)).sdfg
            prelude = singular(u for u in ng.nodes() if u.guid == ordered_nodes[0])
            work = singular(u for u in ng.nodes() if u.guid == ordered_nodes[upto])
            tgt_edge = singular(ed for ed in ng.out_edges(prelude))
            ng.add_edge(prelude, work, deepcopy(tgt_edge.data))
            GUIDS = {ordered_nodes[0], *ordered_nodes[upto:]}
            self._remove_all_nodes_except_guids(ng, GUIDS)

            ordered_nodes = ordered_nodes[:upto]

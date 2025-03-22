from copy import deepcopy
from itertools import chain
from typing import Union, List, Dict, Iterable, Set

import networkx
from dace import SDFGState, SDFG, Memlet, InterstateEdge
from dace.frontend.fortran.ast_utils import singular
from dace.properties import make_properties
from dace.sdfg.graph import generate_element_id
from dace.sdfg.nodes import MapEntry, NestedSDFG, MapExit, Node, AccessNode
from dace.sdfg.state import ControlFlowBlock, ConditionalBlock, ControlFlowRegion
from dace.sdfg.utils import node_path_graph
from dace.transformation import SingleStateTransformation, PatternNode

GOOD_NODE_TYPES = Union[ConditionalBlock, SDFGState, ControlFlowRegion]
GOOD_NODE_CLASSES = (ConditionalBlock, SDFGState, ControlFlowRegion)


@make_properties
class SaneMapFission(SingleStateTransformation):
    map_entry = PatternNode(MapEntry)
    nested_sdfg = PatternNode(NestedSDFG)
    map_exit = PatternNode(MapExit)
    guidmap, mirror, partition_group = {}, {}, {}

    @classmethod
    def expressions(cls):
        return [node_path_graph(cls.map_entry, cls.nested_sdfg, cls.map_exit)]

    def can_be_applied(self, s: SDFGState, expr_index: int, g: SDFG, permissive: bool = False) -> bool:
        if self.nested_sdfg.guid != 'd8426c5d-c0b9-4348-8be3-0c88380906bd':
            return False
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

    def _uniq_deepcopy(self, x: Union[Node, ControlFlowBlock]) -> Union[Node, ControlFlowBlock]:
        x_nu = deepcopy(x)
        x_nu._label = f"copy_{x.label}"
        x_nu.guid = generate_element_id(x_nu)
        self.guidmap[x_nu.guid] = x_nu
        return x_nu

    def _mirror(self, x: Union[Node, ControlFlowBlock]) -> Union[Node, ControlFlowBlock]:
        if x.guid in self.mirror:
            return self.guidmap[self.mirror[x.guid]]
        x_nu = self._uniq_deepcopy(x)
        self.mirror[x.guid] = x_nu.guid
        return x_nu

    @staticmethod
    def _removeprefix(c: str, p: str):
        """Since `str.removeprefix()` wasn't added until Python 3.9"""
        if not c.startswith(p):
            return c
        return c[len(p):]

    def _connector_counterpart(self, c: Union[str, None]) -> Union[str, None]:
        """If it's an input connector, find the corresponding output connector, and vice versa."""
        if c is None:
            return None
        assert isinstance(c, str)
        if c.startswith('IN_'):
            return f"OUT_{self._removeprefix(c, 'IN_')}"
        elif c.startswith('OUT_'):
            return f"IN_{self._removeprefix(c, 'OUT_')}"
        return None

    def _copy_partition(self, pst: SDFGState, partition: List[str]):
        mbeg, mend = self._uniq_deepcopy(self.map_entry), self._uniq_deepcopy(self.map_exit)
        mbeg.in_connectors, mbeg.out_connectors = {}, {}
        mend.in_connectors, mend.out_connectors = {}, {}
        grpg = NestedSDFG('mirror', SDFG('mirror_sdfg'),
                          # carry_over_conns, carry_over_conns,
                          set(), set(),
                          self.nested_sdfg.symbol_mapping,
                          self.nested_sdfg.schedule)
        for u in partition:
            grpg.sdfg.add_node(self._mirror(self.guidmap[u]))
            self.partition_group[u] = grpg.guid
        for k, v in self.nested_sdfg.sdfg.arrays.items():
            print(f"data desc: {k} => {v}")
            grpg.sdfg.add_datadesc(k, v)
        self.guidmap[grpg.guid] = grpg
        pst.add_node(grpg)
        if mbeg is not self.map_entry:
            pst.add_node(mbeg)
        if mend is not self.map_exit:
            pst.add_node(mend)

        return mbeg, grpg, mend

    def apply(self, s: SDFGState, g: SDFG):
        ng = self.nested_sdfg.sdfg
        self.guidmap: Dict[str, Union[ConditionalBlock, SDFGState]] = \
            {u.guid: u for u in chain(ng.nodes(), [self.map_entry, self.nested_sdfg, self.map_exit])}
        self.mirror = {}
        self.partition_group = {}
        orderd_nodes = self._partition_nodes(ng)
        all_conns = {*self.nested_sdfg.in_connectors, *self.nested_sdfg.out_connectors}
        last_known = {}
        for c in self.nested_sdfg.in_connectors:
            ed = singular(ed for ed in s.in_edges_by_connector(self.nested_sdfg, c))
            ed = singular(ed for ed in s.in_edges_by_connector(ed.src, self._connector_counterpart(ed.src_conn)))
            last_known[c] = (ed.src, ed.src_conn, ed.data)

        class Partition:
            def __init__(self, og_nodes: Iterable[GOOD_NODE_TYPES]):
                self.og_nodes: List[GOOD_NODE_TYPES] = list(og_nodes)
                assert all(isinstance(u, GOOD_NODE_CLASSES) for u in self.og_nodes)
                accs = [(v, bool(vst.out_edges(v)), bool(vst.in_edges(v)))
                        for u in self.og_nodes for v, vst in u.all_nodes_recursive()
                        if isinstance(v, AccessNode) and v.data in all_conns]
                self.group_inc = {u.data for u, r, _ in accs if r}
                self.group_outc = {u.data for u, _, w in accs if w}

        # Set up the mirror nodes.
        tail = None
        for idx, group in enumerate(orderd_nodes):
            parti = Partition([self.guidmap[u] for u in group])
            mbeg, grpg, mend = self._copy_partition(s, group)
            for c in parti.group_inc:
                grpg.add_in_connector(c)
            for c in parti.group_outc:
                grpg.add_out_connector(c)
            s.add_edge(mbeg, None, grpg, None, Memlet())
            s.add_edge(grpg, None, mend, None, Memlet())
            # The edges should be like this: `tail -> mbeg`, or `mbeg -> grpg` or `grpg -> mend`. The last `mend` is to
            # be handled as a special case.
            if tail:
                # An empty edge to enforce sequencing.
                s.add_edge(tail, None, mbeg, None, Memlet())
                print(f"added: {tail.guid} => {mbeg.guid} -> {grpg.guid} -> {mend.guid}")
            else:
                # Mirror the original incoming edges, but only to force sequencing.
                for ed in s.in_edges(self.map_entry):
                    s.add_edge(ed.src, None, mbeg, None, Memlet())
                print(f"added: {mbeg.guid} -> {grpg.guid} -> {mend.guid}")
            for c in parti.group_inc:
                assert c in last_known
                src, src_conn, data = last_known[c]
                inc, outc = f"IN_{c}", f"OUT_{c}"
                mbeg.add_in_connector(inc)
                mbeg.add_out_connector(outc)
                x = s.add_edge(src, src_conn, mbeg, inc, data)
                print(f"x = {x} / {c}|{src}%{src.guid}:{src_conn} -> {mbeg.guid}:{inc}")
                s.add_edge(mbeg, outc, grpg, c, data)
            for c in parti.group_outc:
                inc, outc = f"IN_{c}", f"OUT_{c}"
                if c in parti.group_inc:
                    # Either we are propagating data.
                    ed = singular(ed for ed in s.in_edges_by_connector(grpg, c))
                    data = ed.data
                else:
                    # Or we are writing to data.
                    accu, accust = [(u, ust) for u, ust in grpg.sdfg.all_nodes_recursive()
                                    if isinstance(u, AccessNode) and u.data == c and ust.in_edges(u)][-1]
                    ed = singular(ed for ed in accust.in_edges(accu))
                    data = ed.data
                mend.add_in_connector(inc)
                mend.add_out_connector(outc)
                s.add_edge(grpg, c, mend, inc, data)
                ed = singular(ed for ed in s.out_edges_by_connector(grpg, c))
                last_known[c] = (mend, self._connector_counterpart(ed.dst_conn), data)
            tail = mend

        for ed in ng.edges():
            src, dst = ed.src.guid, ed.dst.guid
            if (src not in self.mirror or dst not in self.mirror
                    or self.partition_group[src] != self.partition_group[dst]):
                continue
            grpg = self.guidmap[self.partition_group[src]]
            src, dst = self._mirror(ed.src), self._mirror(ed.dst)
            grpg.sdfg.add_edge(src, dst, ed.data)

        s.remove_nodes_from([self.map_entry, self.nested_sdfg, self.map_exit])
        s.remove_nodes_from([u for u in s.nodes() if isinstance(u, AccessNode) and not s.degree(u)])


@make_properties
class YoloMapFission(SingleStateTransformation):
    map_entry = PatternNode(MapEntry)
    nested_sdfg = PatternNode(NestedSDFG)
    map_exit = PatternNode(MapExit)

    @classmethod
    def expressions(cls):
        return [node_path_graph(cls.map_entry, cls.nested_sdfg, cls.map_exit)]

    def can_be_applied(self, s: SDFGState, expr_index: int, g: SDFG, permissive: bool = False) -> bool:
        if self.nested_sdfg.guid not in {
            'd8426c5d-c0b9-4348-8be3-0c88380906bd',  # CPU
            '89b077dc-e393-4c8f-a1e4-6aa01bda625e',  # GPU
        }:
            return False
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
    def _add_replica_state_after(s: SDFGState, g: SDFG) -> SDFGState:
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

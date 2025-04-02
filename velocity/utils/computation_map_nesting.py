# Copyright 2019-2025 ETH Zurich and the DaCe authors. All rights reserved.

from dataclasses import dataclass
from dace.sdfg.state import (
    ControlFlowBlock,
    ControlFlowRegion,
    ConditionalBlock,
    LoopRegion,
)
from dace.transformation import pass_pipeline as ppl, transformation
from dace import SDFG, properties, SDFGState
from typing import Dict, Set, Optional
from dace import data as dt
from dace.sdfg.nodes import (
    AccessNode,
    Tasklet,
    LibraryNode,
    MapEntry,
    MapExit,
    NestedSDFG,
)
from dace.subsets import Range
import re
from functools import lru_cache
import copy


@dataclass(unsafe_hash=True)
@properties.make_properties
@transformation.explicit_cf_compatible
class ComputationMapNesting(ppl.Pass):
    """
    Duplicates and nests computations outside of the map into the map to allow parallelization.
    For example:

      a = some computation
      for i in range(x):
        #  use a without writing to it

    becomes:

      for i in range(x):
        a = some computation
        #  use a without writing to it

    We are assuming that the computation is done in a previous state.
    """

    CATEGORY: str = "Optimization Preparation"

    def modifies(self) -> ppl.Modifies:
        return ppl.Modifies.Edges | ppl.Modifies.Nodes

    def should_reapply(self, modified: ppl.Modifies) -> bool:
        # If anything was modified, reapply
        return modified != ppl.Modifies.Nothing

    def apply_pass(self, sdfg: SDFG, _) -> Optional[Set[str]]:
        # For the fixed-point analysis we maintain a table of mappings from array name to their access node, where the array is last written.

        # Get all CFG blocks present in the SDFG
        all_cfgb = dict()
        for node, parent in sdfg.all_nodes_recursive():
            if isinstance(node, ControlFlowBlock):
                all_cfgb[node] = parent

        # For each CFG Block maintain a dict of incoming and outgoing tables
        in_table = {cfgb: {} for cfgb in all_cfgb.keys()}
        out_table = {cfgb: {} for cfgb in all_cfgb.keys()}

        # Perform a forward fixed-point iteration to build tables
        changed = True
        while changed:
            changed = False

            # Update incoming table
            for cfgb, parent in all_cfgb.items():
                new_in_table = self._get_in_table(
                    sdfg, cfgb, parent, in_table, out_table
                )

                # Check if the incoming table have changed
                if new_in_table != in_table[cfgb]:
                    changed = True
                    in_table[cfgb] = new_in_table

            # Update outgoing table
            for cfgb, parent in all_cfgb.items():
                new_out_table = self._get_out_table(
                    sdfg, cfgb, parent, in_table, out_table
                )

                # Check if the outgoing table have changed
                if new_out_table != out_table[cfgb]:
                    changed = True
                    out_table[cfgb] = new_out_table

        # Clean up the tables (remove None entries)
        for cfgb, parent in all_cfgb.items():
            in_table[cfgb] = {k: v for k, v in in_table[cfgb].items() if v is not None}
            out_table[cfgb] = {
                k: v for k, v in out_table[cfgb].items() if v is not None
            }

        # Compute set of arrays that are being considered for replacement
        considered = set()
        for cfgb, parent in all_cfgb.items():
            for k in in_table[cfgb].keys():
                considered.add(k)
            for k in out_table[cfgb].keys():
                considered.add(k)

        map_arrays = set()
        for cfgb, parent in all_cfgb.items():
            if cfgb.sdfg is sdfg:
                map_arrays |= ComputationMapNesting._get_map_arrays(cfgb)
        considered = considered & map_arrays

        # Perform replacement of the arrays
        for i, (cfgb, parent) in enumerate(all_cfgb.items()):
            self._replace(sdfg, cfgb, parent, in_table, out_table)
        return set()

    # Given a CFGB, builds the incoming table
    def _get_in_table(
        self,
        sdfg: SDFG,
        cfgb: ControlFlowBlock,
        parent: ControlFlowRegion,
        in_table: Dict[
            ControlFlowBlock, Dict[str, tuple[AccessNode, ControlFlowBlock]]
        ],
        out_table: Dict[
            ControlFlowBlock, Dict[str, tuple[AccessNode, ControlFlowBlock]]
        ],
    ) -> Dict[str, tuple[AccessNode, ControlFlowBlock]]:
        new_in_table = {}

        # Combine the outgoing tables of all incoming edges
        for i, pred in enumerate(parent.predecessors(cfgb)):
            sym_table = out_table[pred].copy()
            if i == 0:
                new_in_table = sym_table
            else:
                new_in_table = self._combine_entries(new_in_table, sym_table)

        # Nested starting CFGBs should inherit from their parent
        # Ignore SDFGs as nested SDFGs have inputs and outputs
        if (parent.start_block == cfgb and not isinstance(parent, SDFG)) or (
            isinstance(parent, ConditionalBlock) and cfgb in parent.sub_regions()
        ):
            assert new_in_table == {}
            new_in_table = in_table[parent].copy()

        return new_in_table

    # Given a CFGB, builds the outgoing table
    def _get_out_table(
        self,
        sdfg: SDFG,
        cfgb: ControlFlowBlock,
        parent: ControlFlowRegion,
        in_table: Dict[
            ControlFlowBlock, Dict[str, tuple[AccessNode, ControlFlowBlock]]
        ],
        out_table: Dict[
            ControlFlowBlock, Dict[str, tuple[AccessNode, ControlFlowBlock]]
        ],
    ) -> Dict[str, tuple[AccessNode, ControlFlowBlock]]:
        if isinstance(cfgb, LoopRegion):
            # Combine all outgoing tables of the sink nodes and the incoming table of the loop (as the loop might not be taken)
            new_out_table = in_table[cfgb].copy()
            for n in cfgb.sink_nodes():
                assert isinstance(n, ControlFlowBlock)
                new_out_table = self._combine_entries(new_out_table, out_table[n])
            return new_out_table

        elif isinstance(cfgb, ConditionalBlock):
            # Combine all outgoing tables of the branches
            new_out_table = out_table[cfgb.sub_regions()[0]].copy()
            for b in cfgb.sub_regions():
                new_out_table = self._combine_entries(new_out_table, out_table[b])

            # If no else branch is present, also combine the incoming table (implicit else branch)
            has_non_conds = any([c is None for c, _ in cfgb.branches])
            if not has_non_conds:
                new_out_table = self._combine_entries(new_out_table, in_table[cfgb])

            return new_out_table

        elif isinstance(cfgb, SDFGState):
            new_out_table = in_table[cfgb].copy()

            # FIXME: We should check if the predecessors of the source array are also not (partially) written

            # Remove (None) any array that is partially written in the current state
            for arr in ComputationMapNesting._get_partially_written_arrays(cfgb):
                if arr in new_out_table:
                    new_out_table[arr] = None

            # Add any array that is completely written in the current state
            for arr, node in ComputationMapNesting._get_overwritten_arrays(
                cfgb
            ).items():
                new_out_table[arr] = (node, cfgb)

            return new_out_table

        else:
            # Combine all sinks
            sink_nodes = [
                n
                for n in cfgb.nodes()
                if cfgb.out_degree(n) == 0 and isinstance(n, ControlFlowBlock)
            ]
            if len(sink_nodes) == 0:
                return in_table[cfgb]

            new_out_table = out_table[sink_nodes[0]].copy()
            for n in sink_nodes:
                new_out_table = self._combine_entries(new_out_table, out_table[n])
            return new_out_table

    # Combines two table entries
    def _combine_entries(
        self,
        e1: Dict[str, tuple[AccessNode, ControlFlowBlock]],
        e2: Dict[str, tuple[AccessNode, ControlFlowBlock]],
    ) -> Dict[str, tuple[AccessNode, ControlFlowBlock]]:
        out = {}
        for k, v in e1.items():
            if v is None:
                out[k] = None
            elif k not in e2 or v[0] is not e2[k][0] or v[1] is not e2[k][1]:
                out[k] = None
            else:
                out[k] = v
        return out

    # Checks if an access node is completely written
    @staticmethod  # To make it cacheable
    @lru_cache(maxsize=None)
    def _is_overwritten(state: SDFGState, node: AccessNode) -> bool:
        # Turn array into a range
        node_range = Range.from_array(state.sdfg.arrays[node.data])
        # Check coverage
        for edge in state.in_edges(node):
            if (
                edge.data
                and edge.data.dst_subset
                and edge.data.dst_subset.covers_precise(node_range)
            ):
                return True
        return False

    # Given a state, returns all arrays that are completely written
    @staticmethod  # To make it cacheable
    @lru_cache(maxsize=None)
    def _get_overwritten_arrays(state: SDFGState) -> Dict[str, AccessNode]:
        overwritten = {}
        for node in state.data_nodes():
            assert isinstance(node, AccessNode)
            # Skip view nodes
            if isinstance(node.desc(state.sdfg), dt.View):
                continue

            # Skip non-transient nodes
            if not node.desc(state.sdfg).transient:
                continue

            # Skip nodes that are not end-of-chain
            if state.out_degree(node) > 0:
                continue

            # Node should only have a single predecessor
            if len(state.predecessors(node)) != 1:
                continue
            pred = state.predecessors(node)[0]

            # Skip nodes that don't directly depend on a tasklet or library node
            if not isinstance(pred, (Tasklet, LibraryNode)):
                continue

            # The tasklet or library node should only have one successor
            if len(state.successors(pred)) != 1:
                continue

            # Check if the node is completely written
            if ComputationMapNesting._is_overwritten(state, node):
                # NOTE: There cannot be multiple end-of-chain full writes without dataraces. So we don't need to check for duplicates.
                assert node.data not in overwritten
                overwritten[node.data] = node
        return overwritten

    # Given a state, returns all partially written array names
    @staticmethod  # To make it cacheable
    @lru_cache(maxsize=None)
    def _get_partially_written_arrays(state: SDFGState) -> Set[str]:
        partially_written = set()
        for node in state.data_nodes():
            assert isinstance(node, AccessNode)
            # Skip view nodes
            if isinstance(node.desc(state.sdfg), dt.View):
                continue
            # Check if the node is partially written
            if state.in_degree(node) > 0:
                partially_written.add(node.data)
        return partially_written

    # Given a CFGB return the top-level nsdfg node
    @staticmethod  # To make it cacheable
    @lru_cache(maxsize=None)
    def _get_top_level_nsdfg_node(
        cfgb: ControlFlowBlock, sdfg: SDFG
    ) -> Optional[ControlFlowBlock]:
        # Map nsdfg nodes to their parent
        nsdfg_nodes = {}
        for n, p in sdfg.all_nodes_recursive():
            if isinstance(n, NestedSDFG):
                nsdfg_nodes[n] = p

        # Get the top-level nsdfg node
        tlp = cfgb
        tlsdfg = tlp.sdfg.parent_nsdfg_node
        while tlp.sdfg is not sdfg:
            tlsdfg = tlp.sdfg.parent_nsdfg_node
            tlp = nsdfg_nodes[tlsdfg]
        return tlsdfg

    # Given a CFGB, gets all arrays names that are read in a map
    @staticmethod  # To make it cacheable
    @lru_cache(maxsize=None)
    def _get_map_arrays(cfgb: ControlFlowBlock) -> Set[str]:
        map_arrays = set()
        for node, parent in cfgb.all_nodes_recursive():
            if not isinstance(node, AccessNode):
                continue
            if parent.out_degree(node) == 0:
                continue
            if parent.entry_node(node) is not None:
                map_arrays.add(node.data)
                continue

            if parent.sdfg is cfgb.sdfg:
                continue
            tlp = ComputationMapNesting._get_top_level_nsdfg_node(parent, cfgb.sdfg)
            if cfgb.entry_node(tlp) is not None:
                map_arrays.add(node.data)
                continue

        return map_arrays

    # Given a CFGB, replaces all reads in maps with the computation
    def _replace(
        self,
        sdfg: SDFG,
        cfgb: ControlFlowBlock,
        parent: ControlFlowRegion,
        in_table: Dict[
            ControlFlowBlock, Dict[str, tuple[AccessNode, ControlFlowBlock]]
        ],
        out_table: Dict[
            ControlFlowBlock, Dict[str, tuple[AccessNode, ControlFlowBlock]]
        ],
    ) -> None:
        for arr_name in in_table[cfgb].keys():
            # Find access nodes inside maps, which only read from this array
            for acc_node, parent in cfgb.all_nodes_recursive():
                if not isinstance(acc_node, AccessNode):
                    continue
                if acc_node.data != arr_name:
                    continue
                if all(
                    isinstance(succ, MapEntry) for succ in parent.successors(acc_node)
                ):
                    continue

                src_acc = in_table[cfgb][arr_name][0]
                src_parent: SDFGState = in_table[cfgb][arr_name][1]
                assert isinstance(src_parent, SDFGState)

                # Keep a mapping of the original nodes and the new nodes
                node_map = {src_acc: acc_node}

                # Traverse the src backwards and create a clone of each node and edge
                to_process = [*src_parent.predecessors(src_acc)]
                while len(to_process) > 0:
                    node = to_process.pop(0)
                    # Already cloned
                    if node in node_map:
                        continue
                    # Don't clone MapEntry/Exit nodes
                    if isinstance(node, (MapEntry, MapExit)):
                        continue
                    # Children are not cloned yet
                    if any(s not in node_map for s in src_parent.successors(node)):
                        to_process.append(node)
                        continue

                    node_clone = copy.deepcopy(node)
                    node_map[node] = node_clone
                    parent.add_node(node_clone)

                    # Copy the edges
                    for e in src_parent.out_edges(node):
                        assert e.dst in node_map
                        parent.add_edge(
                            node_clone,
                            e.src_conn,
                            node_map[e.dst],
                            e.dst_conn,
                            copy.deepcopy(e.data),
                        )

                    # Add the predecessors
                    for pred in src_parent.predecessors(node):
                        to_process.append(pred)

                # Rename access nodes to make the data transient
                old_new_names = {}
                for o, c in node_map.items():
                    if not isinstance(c, AccessNode):
                        continue
                    if not src_parent.sdfg.arrays[c.data].transient:
                        continue
                    # FIXME: It's not this simple, any array where the in-edges are a subset of the out-edges, cannot be renamed
                    if parent.in_degree(c) == 0:
                        continue
                    desc = copy.deepcopy(src_parent.sdfg.arrays[c.data])
                    c.data = parent.sdfg.add_datadesc(
                        f"{c.data}_CMN", desc, find_new_name=True
                    )
                    old_new_names[o.data] = c.data
                for o, c in node_map.items():
                    for edge in parent.out_edges(c):
                        edge.data.replace(old_new_names)

                        for old, new in old_new_names.items():
                            repl_pattern = r"\b" + re.escape(old) + r"\b"
                            edge.data.data = re.sub(repl_pattern, new, edge.data.data)

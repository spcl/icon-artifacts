import re
import warnings
import dace

from dace import properties
from dace.codegen.common import sym2cpp
from dace.transformation import pass_pipeline as ppl, transformation

from typing import Dict, List, Set

@properties.make_properties
@transformation.explicit_cf_compatible
class AssignmentAndCopyKernelToMemcpyAndMemset(ppl.Pass):
    """
    Title says it all.
    """

    def modifies(self) -> ppl.Modifies:
        return ppl.Modeifies.Everything

    def should_reapply(self, modified: ppl.Modifies) -> bool:
        return False

    def depends_on(self):
        return set()

    def _detect_contiguous_memcpy_paths(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        in_access_edges = {e for e in state.in_edges(node) if isinstance(e.src, dace.nodes.AccessNode)}
        paths = set()

        # If map range is not contigous, we can't do contiguous copy detection
        step_equal_one = True
        for (b, e, s) in node.map.range:
            if s != 1:
                step_equal_one = False
                break

        # Non-zero step in map range
        if not step_equal_one:
            return paths

        path_candidate = []
        for e in in_access_edges:

            # Make sure AccessNode -> MapEntry goes to a pass-through connector, and connector has 1 edge
            path_candidate.append(e)
            map_entry_in_conn = e.dst_conn
            if not map_entry_in_conn.startswith("IN_"):
                # Dynamic in connection, can't be a contiguous copy
                path_candidate = []
                continue
            map_entry_out_conn = map_entry_in_conn.replace("IN_", "OUT_")

            map_entry_out_edges = {e for e in state.out_edges_by_connector(node, map_entry_out_conn)}

            if len(map_entry_out_edges) != 1:
                # More than one out edge, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            # MapEntry has exactly one out edge, and leads to a tasklett
            map_entry_out_edge = map_entry_out_edges.pop()
            path_candidate.append(map_entry_out_edge)

            tasklet = map_entry_out_edge.dst
            if not isinstance(tasklet, dace.nodes.Tasklet):
                # Not a tasklet, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            if len(tasklet.in_connectors) != 1 or len(tasklet.out_connectors) != 1:
                # Tasklet does not have exactly one in and one out connector, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            # Tasklet has exactly one in and one out connector, leads to a map exit
            out_conn = tasklet.out_connectors[0]

            tasklet_out_edges = {e for e in state.out_edges(tasklet) if e.dst_conn == out_conn}
            if len(tasklet_out_edges) != 1:
                # More than one out edge, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            tasklet_out_edge = tasklet_out_edges.pop()
            path_candidate.append(tasklet_out_edge)

            map_exit = tasklet_out_edge.dst
            if not isinstance(map_exit, dace.nodes.MapExit):
                # Not a map exit, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            map_exit_in_conn = tasklet_out_edge.dst_conn
            if not map_exit_in_conn.startswith("IN_"):
                # This SDFG is not valid btw.
                path_candidate = []
                continue

            map_exit_out_conn = map_exit_in_conn.replace("IN_", "OUT_")
            map_exit_out_edges = {e for e in state.out_edges_by_connector(map_exit, map_exit_out_conn)}

            if len(map_exit_out_edges) != 1:
                # More than one out edge, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            map_exit_out_edge = map_exit_out_edges.pop()
            path_candidate.append(map_exit_out_edge)

            if not isinstance(map_exit_out_edge.dst, dace.nodes.AccessNode):
                # Not an access node, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            # Check if the tasklet has the form of `out_conn = in_conn`
            in_conn = tasklet.in_connectors[0]
            if len(tasklet.in_connectors) != 1:
                # Tasklet does not have exactly one in and one out connector, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            if tasklet.language == dace.Language.Python:
                tasklet_code_str = tasklet.code.as_string
                if f"{out_conn} = {in_conn}" != tasklet_code_str:
                    # Tasklet does not have the form of `out_conn = in_conn`, can't be a contiguous copy pattern we look for
                    path_candidate = []
                    continue
            elif tasklet.language == dace.Language.CPP:
                tasklet_code_str = tasklet.code.as_string
                if f"{out_conn} = {in_conn};" != tasklet_code_str:
                    # Tasklet does not have the form of `out_conn = in_conn;`, can't be a contiguous copy pattern we look for
                    path_candidate = []
                    continue
            else:
                # Unsupported language, can't do it
                warnings.warn(f"Unsupported tasklet language {tasklet.language} in contiguous copy detection, skipping.", UserWarning)
                path_candidate = []
                continue

            # We found it finally!
            paths.add(path_candidate)

    def _detect_contiguous_memset_paths(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        all_tasklets = {n for n in state.all_nodes_between(node, state.exit_node(node)) if isinstance(n, dace.nodes.Tasklet)}
        possible_assignment_tasklets = {t for t in all_tasklets if len(t.in_connectors) == 0 and len(t.out_connectors) == 1 and state.in_degree(t) == 1 and state.out_degree(t) == 1}

        paths = set()

        path_candidate = []
        in_edges_from_tasklets = {e for e in state.in_edges(node) if isinstance(e.src, dace.nodes.Tasklet)}

        # If map range is not contigous, we can't do contiguous copy detection
        step_equal_one = True
        for (b, e, s) in node.map.range:
            if s != 1:
                step_equal_one = False
                break

        # Non-zero step in map range
        if not step_equal_one:
            return paths

        for e in in_edges_from_tasklets:
            path_candidate.append(e)

            if e.data.data is not None:
                # If the data is not None, it is not a contiguous copy
                path_candidate = []
                continue
            if len(e.dst.out_connectors) != 1:
                # If the destination has more than one out connector, it is not a contiguous copy
                path_candidate = []
                continue

            tasklet: dace.nodes.Tasklet = e.dst
            zero_literal_pattern = r"(0|0\.0|0\.0f|0\.f|0\.0d|0\.d)"
            out_conn = tasklet.out_connectors[0]
            tasklet_code_str = tasklet.code.as_string

            if tasklet.language == dace.Language.Python:
                if not re.fullmatch(rf"{re.escape(out_conn)} *= *{zero_literal_pattern}", tasklet_code_str.strip()):
                    # Not a recognized zero assignment pattern
                    path_candidate = []
                    continue

            elif tasklet.language == dace.Language.CPP:
                if not re.fullmatch(rf"{re.escape(out_conn)} *= *{zero_literal_pattern};", tasklet_code_str.strip()):
                    # Not a recognized zero assignment pattern
                    path_candidate = []
                    continue
            else:
                # Unsupported language, can't do it
                warnings.warn(f"Unsupported tasklet language {tasklet.language} in contiguous copy detection, skipping.", UserWarning)
                path_candidate = []
                continue

            tasklet_out_edges = {e for e in state.out_edges(tasklet) if e.dst_conn == out_conn}
            if len(tasklet_out_edges) != 1:
                # More than one out edge, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            tasklet_out_edge = tasklet_out_edges.pop()
            path_candidate.append(tasklet_out_edge)

            map_exit = tasklet_out_edge.dst
            if not isinstance(map_exit, dace.nodes.MapExit) and map_exit != state.exit_node(node):
                # Not a map exit, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            map_exit_in_conn = tasklet_out_edge.dst_conn
            if not map_exit_in_conn.startswith("IN_"):
                # This SDFG is not valid btw.
                path_candidate = []
                continue
            map_exit_out_conn = map_exit_in_conn.replace("IN_", "OUT_")
            map_exit_out_edges = {e for e in state.out_edges_by_connector(map_exit, map_exit_out_conn)}
            if len(map_exit_out_edges) != 1:
                # More than one out edge, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            map_exit_out_edge = map_exit_out_edges.pop()
            path_candidate.append(map_exit_out_edge)
            if not isinstance(map_exit_out_edge.dst, dace.nodes.AccessNode):
                # Not an access node, can't be a contiguous copy pattern we look for
                path_candidate = []
                continue

            # We found it finally!
            paths.add(tuple(path_candidate))

    def _rm_path(self, state: dace.SDFGState, path: List):
        # Rm edge, collect nodes, if degree is 0, remove node, also rm in and out connectors
        nodes = set()

        for e in path:
            state.remove_edge(e)
            nodes.add(e.src)
            nodes.add(e.dst)

            src_conn = e.src_conn
            dst_conn = e.dst_conn

            e.src.remove_out_connector(src_conn)
            e.dst.remove_in_connector(dst_conn)

        for n in nodes:
            if state.degree(n) == 0:
                state.remove_node(n)

    def _get_num_tasklets_within_map(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        n = {n for n in state.all_nodes_between(node, state.exit_node(node)) if isinstance(n, dace.nodes.Tasklet)}
        return len(n)

    def _get_write_begin_and_length(self, state: dace.SDFGState, map_entry: dace.nodes.MapEntry, tasklet: dace.nodes.Tasklet):
        range_list = {dace.symbolic.Symbol(p): (b, e, s) for (p, (b, e, s)) in zip(map_entry.map.params, map_entry.map.range)}

        in_edge = state.in_edges(tasklet)[0]
        out_edge = state.out_edges(tasklet)[0]

        if in_edge.data.data is not None:
            in_data_range = [(b,e,s) for (b,e,s) in in_edge.data.subset]
        out_data_range = [(b,e,s) for (b,e,s) in out_edge.data.subset]

        new_in_data_range = []
        new_out_data_range = []

        if in_edge.data.data is not None:
            for (b, e, s) in in_data_range:
                nb: dace.symbolic.SymExpr = b
                ne: dace.symbolic.SymExpr = e
                ns: dace.symbolic.SymExpr = s
                for (p, (b2, e2, s2)) in range_list.items():
                    nb = nb.subs(p, b2)
                    ne = ne.subs(p, e2)
                    assert ns == 1 and s2 == 1, "Only step of 1 is supported for memcpy detection"
                new_in_data_range.append((nb, ne, ns))
        for (b, e, s) in out_data_range:
            nb: dace.symbolic.SymExpr = b
            ne: dace.symbolic.SymExpr = e
            ns: dace.symbolic.SymExpr = s
            for (p, (b2, e2, s2)) in range_list.items():
                nb = nb.subs(p, b2)
                ne = ne.subs(p, e2)
                assert ns == 1 and s2 == 1, "Only step of 1 is supported for memcpy detection"
            new_out_data_range.append((nb, ne, ns))


        if in_edge.data.data is not None:
            in_data_strides = [s for s in state.sdfg.arrays[in_edge.data.data].strides]
        out_data_strides = [s for s in state.sdfg.arrays[out_edge.data.data].strides]

        if in_edge.data.data is not None:
            in_begin_exprs = [b for (b, e, s) in new_in_data_range]
            in_length_exprs = [(e + 1) - b for (b, e, s) in new_in_data_range]
        out_begin_exprs = [b for (b, e, s) in new_out_data_range]
        out_length_exprs = [(e + 1) - b for (b, e, s) in new_out_data_range]

        if in_edge.data.data is not None:
            in_begin_collapsed = dace.symbolic.SymExpr(0)
            in_length_collapsed = dace.symbolic.SymExpr(0)
        out_begin_collapsed = dace.symbolic.SymExpr(0)
        out_length_collapsed = dace.symbolic.SymExpr(0)

        if in_edge.data.data is not None:
            for i, b in enumerate(in_begin_exprs):
                in_begin_collapsed += b * in_data_strides[i]

            for i, l in enumerate(in_length_exprs):
                in_length_collapsed += l * in_data_strides[i]

        for i, b in enumerate(out_begin_exprs):
            out_begin_collapsed += b * out_data_strides[i]

        for i, l in enumerate(out_length_exprs):
            out_length_collapsed += l * out_data_strides[i]

        if in_edge.data.data is None:
            in_begin_collapsed = None
            in_length_collapsed = None

        assert in_length_collapsed == out_length_collapsed, "Input and output lengths must be equal for memcpy detection"

        return new_in_data_range, new_out_data_range, out_length_collapsed

    def remove_memcpy_from_kernel(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        memcpy_paths = self._detect_contiguous_memcpy_paths(state, node)
        for memcpy_path in memcpy_paths:
            src_access_node = memcpy_path[0].src
            map_entry = memcpy_path[0].dst
            tasklet = memcpy_path[1].dst
            map_exit = memcpy_path[2].dst
            dst_access_node = memcpy_path[3].dst

            # If src and dst types are not the same, we can't do memcpy
            src_desc = state.sdfg.arrays[src_access_node.data]
            dst_desc = state.sdfg.arrays[dst_access_node.data]
            if src_desc.dtype != dst_desc.dtype:
                warnings.warn(f"Source and destination types do not match for memcpy removal: {src_desc.dtype} != {dst_desc.dtype}. Skipping.", UserWarning)
                continue
            if src_desc.storage != dst_desc.storage and src_desc.storage != dace.StorageType.GPU_Global:
                warnings.warn(f"Source and destination storage types do not match (or not GPU Global) for memcpy removal: {src_desc.storage} != {dst_desc.storage}. Skipping.", UserWarning)
                continue

            # We can now remove the memcpy path
            self._rm_path(state, memcpy_path)

            # If src / dst not in the graph anymore, add new ones
            if src_access_node not in state.nodes():
                new_src = dace.nodes.AccessNode(src_access_node.data)
                state.add_node(new_src)
                src_access_node = new_src
            if dst_access_node not in state.nodes():
                new_dst = dace.nodes.AccessNode(dst_access_node.data)
                state.add_node(new_dst)
                dst_access_node = new_dst

            # To calculate the total range,
            # Take input subset of tasklet replace expression with map range
            # For now, we will just use the original range
            begin_subset, exit_subset, copy_length = self._get_write_begin_and_length(state, map_entry, tasklet)

            # Add a new memcpy tasklet
            in_memcpy_an = state.add_access(src_access_node.data)
            out_memcpy_an = state.add_access(dst_access_node.data)
            tasklet = state.add_tasklet(
                name=f"memcpy_{src_access_node.data}_{dst_access_node.data}",
                inputs={"_in"},
                outputs={"_out"},
                code=f"cudaMemcpyAsync(_out, _in, {sym2cpp(copy_length)} * sizeof({src_desc.storage.dtype.ctype}), cudaMemcpyDeviceToDevice, nullptr);",
                language=dace.Language.CPP,
                code_global=f"#include <cuda_runtime.h>\n"
            )
            state.add_edge(in_memcpy_an, None, tasklet, "_in",
                           dace.memlet.Memlet(subset=begin_subset, data=src_access_node.data))
            state.add_edge(tasklet, "_out", out_memcpy_an, None,
                           dace.memlet.Memlet(subset=exit_subset, data=dst_access_node.data))

    def remove_memset_from_kernel(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        memset_paths = self._detect_contiguous_memset_paths(state, node)
        for memset_path in memset_paths:
            map_entry = memset_path[0].src
            tasklet = memset_path[0].dst
            map_exit = memset_path[1].dst
            dst_access_node = memset_path[2].dst

            # If src and dst types are not the same, we can't do memset
            dst_desc = state.sdfg.arrays[dst_access_node.data]
            if dst_desc.storage != dace.StorageType.GPU_Global:
                warnings.warn(f"Destination storage is not GPU_Global for memset removal: {dst_desc.storage}. Skipping.", UserWarning)
                continue

            # We can now remove the memset path
            self._rm_path(state, memset_path)

            # If src / dst not in the graph anymore, add new ones
            if dst_access_node not in state.nodes():
                new_dst = dace.nodes.AccessNode(dst_access_node.data)
                state.add_node(new_dst)
                dst_access_node = new_dst

            # To calculate the total range,
            # Take input subset of tasklet replace expression with map range
            # For now, we will just use the original range
            begin_subset, exit_subset, copy_length = self._get_write_begin_and_length(state, map_entry, tasklet)

            # Add a new memcpy tasklet
            out_memcpy_an = state.add_access(dst_access_node.data)
            tasklet = state.add_tasklet(
                name=f"memset_0_{dst_access_node.data}",
                inputs={},
                outputs={"_out"},
                code=f"cudaMemcpyAsync(_out, 0, {sym2cpp(copy_length)} * sizeof({dst_desc.storage.dtype.ctype}), cudaMemcpyDeviceToDevice, nullptr);",
                language=dace.Language.CPP,
                code_global=f"#include <cuda_runtime.h>\n"
            )
            state.add_edge(tasklet, "_out", out_memcpy_an, None,
                           dace.memlet.Memlet(subset=exit_subset, data=dst_access_node.data))


    def apply_pass(self, sdfg: dace.SDFG, pipeline_res: Dict) -> Dict[int, Dict[dace.SDFGState, Set[dace.SDFGState]]]:
        gpu_map_entries = set()

        for n, g in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.MapEntry) and n.map.schedule == dace.ScheduleType.GPU_Device:
                gpu_map_entries.add((n, g))

        for (node, state) in gpu_map_entries:
            if self._get_num_tasklets_within_map(state, node) == 0:
                continue

            self.remove_memcpy_from_kernel(state, node)

            # If the map is only used for 1 memcpy, then it might have been already removed
            if node in state.nodes():
                self.remove_memset_from_kernel(state, node)




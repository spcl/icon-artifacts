import re
import warnings
import dace

from dace import Tuple, properties
from dace.codegen.common import sym2cpp
from dace.transformation import pass_pipeline as ppl, transformation

from typing import Dict, List, Set

@properties.make_properties
@transformation.explicit_cf_compatible
class AssignmentAndCopyKernelToMemsetAndMemcpy(ppl.Pass):
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
            out_conn = next(iter(tasklet.out_connectors))

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
            in_conn = next(iter(tasklet.in_connectors))
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

        return paths

    def _detect_contiguous_memset_paths(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        # All tasklets within the map
        all_tasklets = {n for n in state.all_nodes_between(node, state.exit_node(node)) if isinstance(n, dace.nodes.Tasklet)}

        # Assignment tasklet: no in connector, but only out connector
        possible_assignment_tasklets = {t for t in all_tasklets if len(t.in_connectors) == 0 and len(t.out_connectors) == 1 and state.in_degree(t) == 1 and state.out_degree(t) == 1}

        paths = set()

        path_candidate = []
        in_edges_from_tasklets = {e for t in possible_assignment_tasklets for e in state.in_edges(t)}

        # If map range is not contigous, we can't do contiguous memset detection
        for (b, e, s) in node.map.range:
            if s != 1:
                return set()

        # Create all possible paths
        for e in in_edges_from_tasklets:
            path_candidate.append(e)

            if e.data.data is not None:
                # If the data is not None, it is not an assignment
                path_candidate = []
                continue

            if len(e.dst.out_connectors) != 1:
                # If the destination has more than one out connector, it is not a contiguous memset
                path_candidate = []
                continue

            tasklet: dace.nodes.Tasklet = e.dst
            zero_literal_pattern = r"(0|0\.0|0\.0f|0\.f|0\.0d|0\.d)"
            assert len(tasklet.out_connectors) == 1, "Tasklet must have exactly one out connector for contiguous copy detection"
            out_conn = next(iter(tasklet.out_connectors))
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

            tasklet_out_edges = {e for e in state.out_edges(tasklet)}
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

        return paths

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

        rmed = 0
        for n in nodes:
            if n in state.nodes() and state.degree(n) == 0:
                state.remove_node(n)
                rmed += 1
        while rmed > 0:
            rmed = 0
            for n in nodes:
                if n in state.nodes() and state.degree(n) == 0:
                    state.remove_node(n)
                    rmed += 1


    def _get_num_tasklets_within_map(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        n = {n for n in state.all_nodes_between(node, state.exit_node(node)) if isinstance(n, dace.nodes.Tasklet)}
        return len(n)

    # [(b,e,s), ...] is the range
    # Need to find out if it is contiguous, this means:
    # The stride==1 dimension is the first one and strides are ascending where the storage is packed
    # or stride==1 dimension is the last one and strides are descending where the storage is packed

    def _get_packed_fortran_strides(self, array: dace.data.Array) -> List[int]:
        accum = 1
        strides = []
        for shape in array.shape:
            strides.append(accum)
            accum *= shape
        return tuple(strides)

    def _get_packed_c_strides(self, array: dace.data.Array) -> List[int]:
        accum = 1
        strides = []
        # Same as Fortran order if shape is inversed
        for shape in reversed(array.shape):
            strides.append(accum)
            accum *= shape
        return tuple(list(reversed(strides)))

    def _is_packed_fortran_strides(self, array: dace.data.Array) -> bool:
        strides = self._get_packed_fortran_strides(array)
        print(f"Checking Fortran strides: {strides} vs {array.strides}")
        return tuple(strides) == tuple(array.strides)

    def _is_packed_c_strides(self, array: dace.data.Array) -> bool:
        strides = self._get_packed_c_strides(array)
        print(f"Checking C strides: {strides} vs {array.strides}")
        return tuple(strides) == tuple(array.strides)


    # let's say arrays strides are [1, N, M*N]
    # then the expression we have needs to cover whole first dimension X-1 if it is not 1 in dimension X
    def _is_contig_subset(self, range_list: List[Tuple], array: dace.data.Array) -> bool:
        if self._is_packed_fortran_strides(array):
            range_list = range_list
            expr_lens = [((e + 1) - b) for (b, e, s) in range_list]
        elif self._is_packed_c_strides(array):
            range_list = list(reversed(range_list))
            expr_lens = [((e + 1) - b) for (b, e, s) in reversed(range_list)]
        else:
            raise ValueError(f"Array {array} does not have Fortran or C strides, has strides: {array.strides}, expected Fortran: {self._get_packed_fortran_strides(array)} or C: {self._get_packed_c_strides(array)}")

        expr_lens = [((e + 1) - b) for (b, e, s) in range_list]
        for i, expr_len in enumerate(expr_lens):
            # It can be that this triggers an error because trurth value is rational, then we assume it is less than the shape
            try:
                if expr_len < array.shape[i]:
                    # All next ones must be 1
                    for j in range(i + 1, len(expr_lens)):
                        if expr_lens[j] != 1:
                            return False
                    return True
            except TypeError:
                # All next ones must be 1
                for j in range(i + 1, len(expr_lens)):
                    if expr_lens[j] != 1:
                        return False
                return True

        return True


    def _get_write_begin_and_length(self, state: dace.SDFGState, map_entry: dace.nodes.MapEntry, tasklet: dace.nodes.Tasklet):
        range_list = {dace.symbolic.symbol(p): (b, e, s) for (p, (b, e, s)) in zip(map_entry.map.params, map_entry.map.range)}

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

        new_in_data_subset = dace.subsets.Range(new_in_data_range) if in_edge.data.data is not None else None
        new_out_data_subset = dace.subsets.Range(new_out_data_range) if out_edge.data.data is not None else None
        print(f"New input data subset: {new_in_data_subset}, New output data subset: {new_out_data_subset}")

        if in_edge.data.data is not None:
            contig_subset = self._is_contig_subset(new_in_data_range, state.sdfg.arrays[in_edge.data.data])
            print(f"Input array {in_edge.data.data} is contiguous: {contig_subset}")
            print(f"{new_in_data_range} vs {state.sdfg.arrays[in_edge.data.data].shape} with strides {state.sdfg.arrays[in_edge.data.data].strides}")
            if not contig_subset:
                warnings.warn(f"Input array {in_edge.data.data} is not contiguous, cannot remove memcpy.", UserWarning)
                return None, None, None

        if out_edge.data.data is not None:
            contig_subset = self._is_contig_subset(new_out_data_range, state.sdfg.arrays[out_edge.data.data])
            print(f"Output array {out_edge.data.data} is contiguous: {contig_subset}")
            print(f"{new_out_data_range} vs {state.sdfg.arrays[out_edge.data.data].shape} with strides {state.sdfg.arrays[out_edge.data.data].strides}")
            if not contig_subset:
                warnings.warn(f"Output array {out_edge.data.data} is not contiguous, cannot remove memcpy.", UserWarning)
                return None, None, None



        if in_edge.data.data is not None:
            in_data_strides = [s for s in state.sdfg.arrays[in_edge.data.data].strides]
        out_data_strides = [s for s in state.sdfg.arrays[out_edge.data.data].strides]

        if in_edge.data.data is not None:
            in_begin_exprs = [b for (b, e, s) in new_in_data_range]
            in_length_exprs = [(e + 1) - b for (b, e, s) in new_in_data_range]
        out_begin_exprs = [b for (b, e, s) in new_out_data_range]
        out_length_exprs = [(e + 1) - b for (b, e, s) in new_out_data_range]

        if in_edge.data.data is not None:
            in_begin_collapsed = dace.symbolic.SymExpr(1)
            in_length_collapsed = dace.symbolic.SymExpr(1)
        out_begin_collapsed = dace.symbolic.SymExpr(1)
        out_length_collapsed = dace.symbolic.SymExpr(1)

        # We ensured the subset is contiguous, so we can get the length by multiplying each dimension's length
        if in_edge.data.data is not None:
            for i, b in enumerate(in_begin_exprs):
                in_begin_collapsed *= b

            for i, l in enumerate(in_length_exprs):
                in_length_collapsed *= l

        for i, b in enumerate(out_begin_exprs):
            out_begin_collapsed *= b

        for i, l in enumerate(out_length_exprs):
            out_length_collapsed *= l

        if in_edge.data.data is None:
            in_begin_collapsed = None
            in_length_collapsed = None

        if in_length_collapsed is not None:
            assert in_length_collapsed == out_length_collapsed, f"Input and output lengths must be equal for memcpy detection {in_length_collapsed} != {out_length_collapsed}"

        #print(f"Input begin: {in_begin_collapsed}, length: {in_length_collapsed}")
        #print(f"Output begin: {out_begin_collapsed}, length: {out_length_collapsed}")
        #print(f"Input range: {new_in_data_range}, Output range: {new_out_data_range}")
        #raise Exception("DEBUG: Check the input and output ranges and lengths for memcpy detection")

        return new_in_data_range, new_out_data_range, out_length_collapsed

    def remove_memcpy_from_kernel(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        memcpy_paths = self._detect_contiguous_memcpy_paths(state, node)
        rmed_count = 0

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


            # To calculate the total range,
            # Take input subset of tasklet replace expression with map range
            # For now, we will just use the original range
            # Needs to be before removing the path because it requires edges of the tasklet
            begin_subset, exit_subset, copy_length = self._get_write_begin_and_length(state, map_entry, tasklet)

            # We can now remove the memcpy path
            self._rm_path(state, memcpy_path)

            # If src / dst not in the graph anymore, add new ones
            if src_access_node not in state.nodes():
                new_src_access_node = state.add_access(src_access_node.data)
            else:
                new_src_access_node = src_access_node
            if dst_access_node not in state.nodes():
                new_dst_access_node = state.add_access(dst_access_node.data)
            else:
                new_dst_access_node = dst_access_node

            # Add a new memcpy tasklet
            tasklet = state.add_tasklet(
                name=f"memcpy_{new_src_access_node.data}_{new_dst_access_node.data}",
                inputs={"_in"},
                outputs={"_out"},
                code=f"cudaMemcpyAsync(_out, _in, {sym2cpp(copy_length)} * sizeof({src_desc.storage.dtype.ctype}), cudaMemcpyDeviceToDevice, nullptr);",
                language=dace.Language.CPP,
                code_global=f"#include <cuda_runtime.h>\n"
            )
            state.add_edge(new_src_access_node, None, tasklet, "_in",
                           dace.memlet.Memlet(subset=dace.subsets.Range(begin_subset), data=new_src_access_node.data))
            state.add_edge(tasklet, "_out", new_dst_access_node, None,
                           dace.memlet.Memlet(subset=dace.subsets.Range(exit_subset), data=new_dst_access_node.data))
            rmed_count += 1
        return rmed_count

    def remove_memset_from_kernel(self, state: dace.SDFGState, node: dace.nodes.MapEntry):
        memset_paths = self._detect_contiguous_memset_paths(state, node)
        rmed_count = 0
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

            # To calculate the total range,
            # Take input subset of tasklet replace expression with map range
            # For now, we will just use the original range
            # Needs to be done before removing the memset path
            if map_entry not in state.nodes() or map_exit not in state.nodes() or tasklet not in state.nodes():
                warnings.warn(f"Map entry, exit or tasklet not in state: {map_entry} ({map_entry in state.nodes()}), {map_exit} ({map_exit in state.nodes()}), {tasklet} ({tasklet in state.nodes()}). Skipping.", UserWarning)
                continue
            current_tasklets = {n for n in state.all_nodes_between(map_entry, map_exit) if isinstance(n, dace.nodes.Tasklet)}
            if len(memset_paths) != len(current_tasklets):
                warnings.warn(f"Number of memset paths {len(memset_paths)} does not match number of tasklets in map {len({n for n in state.all_nodes_between(map_entry, map_exit) if isinstance(n, dace.nodes.Tasklet)})}. Was removed before probably.", UserWarning)
                if tasklet not in current_tasklets:
                    warnings.warn(f"Tasklet {tasklet} is not in the current tasklets, skipping.", UserWarning)
                    continue
            #if "1928" in tasklet.label:
            #    print(len(memset_paths))
            #    print(memset_paths)
            #    raise Exception("DEBUG: Check the memset paths and tasklet label")
            #print(f"Removing memset path: {memset_path}")
            begin_subset, exit_subset, copy_length = self._get_write_begin_and_length(state, map_entry, tasklet)

            if begin_subset is None or exit_subset is None or copy_length is None:
                warnings.warn(f"Could not determine begin or exit subset or copy length for memset removal (or they are not contiguous) in map {map_entry.map}({map_entry.map.label}). Skipping.", UserWarning)
                continue

            # We can now remove the memset path
            self._rm_path(state, memset_path)

            # If src / dst not in the graph anymore, add new ones
            if dst_access_node not in state.nodes():
                new_dst_access_node = state.add_access(dst_access_node.data)
            else:
                new_dst_access_node = dst_access_node


            # Add a new memset tasklet
            tasklet = state.add_tasklet(
                name=f"memset_0_{dst_access_node.data}",
                inputs={},
                outputs={"_out"},
                code=f"cudaMemsetAsync(_out, 0, {sym2cpp(copy_length)} * sizeof({dst_desc.dtype.ctype}), nullptr);",
                language=dace.Language.CPP,
                code_global=f"#include <cuda_runtime.h>\n"
            )
            state.add_edge(tasklet, "_out", new_dst_access_node, None,
                           dace.memlet.Memlet(subset=dace.subsets.Range(exit_subset),
                                              data=new_dst_access_node.data)
                            )
            rmed_count += 1
        return rmed_count


    def apply_pass(self, sdfg: dace.SDFG, pipeline_res: Dict) -> Dict[int, Dict[dace.SDFGState, Set[dace.SDFGState]]]:
        num_rmed_memcpies = 1
        num_rmed_memsets = 1

        while num_rmed_memcpies > 0 or num_rmed_memsets > 0:
            gpu_map_entries = set()

            for n, g in sdfg.all_nodes_recursive():
                if isinstance(n, dace.nodes.MapEntry) and n.map.schedule == dace.ScheduleType.GPU_Device:
                    gpu_map_entries.add((n, g))

            rmed_memcpies = dict()
            rmed_memsets = dict()

            for (node, state) in gpu_map_entries:
                if self._get_num_tasklets_within_map(state, node) == 0:
                    continue

                rmed_memcpy = self.remove_memcpy_from_kernel(state, node)

                # If the map is only used for 1 memcpy, then it might have been already removed
                if node in state.nodes():
                    rmed_memset = self.remove_memset_from_kernel(state, node)

                assert node not in rmed_memsets
                assert node not in rmed_memcpies
                rmed_memcpies[node] = rmed_memcpy
                rmed_memsets[node] = rmed_memset

            num_rmed_memcpies = sum(rmed_memcpies.values())
            num_rmed_memsets = sum(rmed_memsets.values())

            print(f"Removed {num_rmed_memcpies} contiguous memcopies (_out = _in) and {num_rmed_memsets} contiguous memsets (_out = 0) from GPU maps.")
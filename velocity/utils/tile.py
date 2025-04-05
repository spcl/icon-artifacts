import dace

from pathlib import Path
import shutil
import dace
import os
from dace.transformation.auto_tile.add_compute_element_map import AddComputeElementBlockMap
from dace.transformation.auto_tile.remainder_loop_stencil_map import RemainderLoopStencilMap
from dace.transformation.auto_tile.thread_coarsening import ThreadCoarsening
from dace.transformation.interstate import (
    LoopToMap,
    ContinueToCondition,
    ConditionFusion,
    StateFusion,
)
from dace.transformation.passes import (
    InlineSDFGs,
    SymbolPropagation,
    StructToContainerGroups,
)

from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.dataflow import MapCollapse, MapFusion, TrivialMapElimination
from dace.transformation.passes.to_gpu import ToGPU
from utils import *
from dace.sdfg import utils as sdutil

def _can_apply(graph, n, seq_map_ok=False):
    if not (isinstance(n, dace.nodes.MapEntry) and n.schedule == dace.ScheduleType.GPU_Device):
        return False
    # Assert no reductions in the map
    ns = graph.all_nodes_between(n, graph.exit_node(n))
    cont = False
    for _n in ns:
        if isinstance(_n, dace.nodes.LibraryNode):
            cont = True
            break
    if seq_map_ok:
        return not cont
    else:
        has_seq_map = any([isinstance(_n, dace.nodes.MapEntry) and _n.map.schedule == dace.dtypes.ScheduleType.Sequential for _n in ns])
        cont = cont or has_seq_map
        return not cont

def tile_kernels(sdfg: dace.SDFG):
    for graph in [v for v, _ in list(sdfg.all_nodes_recursive()) if isinstance(v, dace.SDFGState)]:
        for n in graph.nodes():
            if isinstance(n, dace.nodes.MapEntry):
                if n.schedule == dace.ScheduleType.GPU_Device:
                    AddComputeElementBlockMap.apply_to(
                        sdfg=graph.sdfg,
                        verify=False,
                        map_entry=n,
                        options={
                            "compute_element_group_dims": [128, 1, 1],
                            "map_schedule": dace.dtypes.ScheduleType.GPU_Device,
                            "schedule_to_add": dace.dtypes.ScheduleType.GPU_ThreadBlock,
                        },
                    )

    for graph in [v for v, _ in list(sdfg.all_nodes_recursive()) if isinstance(v, dace.SDFGState)]:
        for n in graph.nodes():
            if not _can_apply(graph, n):
                continue
            for n2 in sdutil.dfs_topological_sort(graph, n):
                if (
                    isinstance(n2, dace.nodes.MapEntry)
                    and n2.map.schedule == dace.dtypes.ScheduleType.GPU_ThreadBlock
                    and graph.entry_node(n2) == n
                    and "nrdmax_jg" not in str(n.map.range[0])
                ):
                    coarsening_factors = []
                    if not remainder_loop:
                        for (b, e, s), (tb, te, ts) in zip(n.map.range, n2.map.range):
                            range1 = (e+1-b)//s
                            range2 = (te+1-tb)//ts
                            dim = 1
                            try:
                                dim = int(range1 // range2)
                            except:
                                dim = 1
                            if dim == 92:
                                coarsening_factor = 8
                            if dim == 91:
                                coarsening_factor = 7
                            elif dim == 90:
                                coarsening_factor = 9
                            elif dim == 89:
                                coarsening_factor = 1
                            else:
                                coarsening_factor = 1
                            coarsening_factors.append(coarsening_factor)
                    else:
                        coarsening_factors = [4, 2]
                    if not all([v == 1 for v in coarsening_factors]):
                        ThreadCoarsening.apply_to(
                            sdfg=graph.sdfg,
                            verify=False,
                            thread_group_map_entry=n2,
                            device_map_entry=n,
                            options={
                                "tile_sizes": list(reversed(coarsening_factors)),
                            },
                        )
                        # We added 1 map, the n is parent of
                        n = graph.entry_node(n)

    if not remainder_loop:
        sdfg.validate()
        return

    for graph in [v for v, _ in list(sdfg.all_nodes_recursive()) if isinstance(v, dace.SDFGState)]:
        for n in graph.nodes():
            if not _can_apply(graph, n, seq_map_ok=True):
                continue

            for n2 in sdutil.dfs_topological_sort(graph, n):
                if (
                    isinstance(n2, dace.nodes.MapEntry)
                    and n2.map.label.startswith("ThreadCoarsenedMap")
                    and graph.entry_node(n2).map.schedule == dace.dtypes.ScheduleType.GPU_ThreadBlock
                    and graph.entry_node(graph.entry_node(n2)) == n
                    and "nrdmax_jg" not in str(n.map.range[0])
                ):
                    RemainderLoopStencilMap.apply_to(
                        sdfg=graph.sdfg,
                        verify=True,
                        inner_work_map_entry=n2,
                        tblock_type=dace.dtypes.ScheduleType.GPU_ThreadBlock,
                        options={
                            "tblock_type": dace.dtypes.ScheduleType.GPU_ThreadBlock,
                        }
                    )
                    break
    sdfg.validate()
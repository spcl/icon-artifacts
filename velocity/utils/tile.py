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

def tile_kernels(sdfg: dace.SDFG):
    for n, graph in sdfg.all_nodes_recursive():
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
            if not (isinstance(n, dace.nodes.MapEntry) and n.schedule == dace.ScheduleType.GPU_Device):
                continue
            # Assert no reductions in the map
            ns = graph.all_nodes_between(n, graph.exit_node(n))
            cont = False
            for _n in ns:
                if isinstance(_n, dace.nodes.LibraryNode):
                    cont = True
                    break
            has_seq_map = any([isinstance(_n, dace.nodes.MapEntry) and _n.map.schedule == dace.dtypes.ScheduleType.Sequential for _n in ns])
            cont = cont or has_seq_map
            if cont:
                continue

            for n2 in sdutil.dfs_topological_sort(graph, n):
                if (
                    isinstance(n2, dace.nodes.MapEntry)
                    and n2.map.schedule == dace.dtypes.ScheduleType.GPU_ThreadBlock
                    and graph.entry_node(n2) == n
                ):
                    #print(n.map.range) # 1:91(0:90) or 1:92(0:91) -> meaning 90 and 91 elements
                    coarsening_factors = []
                    if not remainder_loop:
                        for (b, e, s), (tb, te, ts) in zip(n.map.range, n2.map.range):
                            range1 = (e+1-b)//s
                            range2 = (te+1-tb)//ts
                            print(f"Range1: {range1}, Range2: {range2} for map {n}")
                            dim = 1
                            try:
                                dim = int(range1 // range2)
                            except:
                                dim = 1
                            if dim == 92:
                                coarsening_factor = 8
                                print("Coarsening factor: 8 for range 92")
                            if dim == 91:
                                coarsening_factor = 7
                                print("Coarsening factor: 7 for range 91")
                            elif dim == 90:
                                coarsening_factor = 9
                                print("Coarsening factor: 9 for range 90")
                            elif dim == 89:
                                coarsening_factor = 1
                                print("Coarsening factor: 1 for range 89")
                            else:
                                coarsening_factor = 1
                            coarsening_factors.append(coarsening_factor)
                    else:
                        coarsening_factors = [4, 2]
                    print(f"Coarsening factors: {coarsening_factors} apply value: {not all([v == 1 for v in coarsening_factors])}")
                    print("\n")
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

    for graph in [v for v, _ in list(sdfg.all_nodes_recursive()) if isinstance(v, dace.SDFGState)]:
        for n in graph.nodes():
            if not (isinstance(n, dace.nodes.MapEntry) and n.schedule == dace.ScheduleType.GPU_Device):
                continue
            # Assert no reductions in the map
            ns = graph.all_nodes_between(n, graph.exit_node(n))
            cont = False
            for _n in ns:
                if isinstance(_n, dace.nodes.LibraryNode):
                    cont = True
                    break
            has_seq_map = any([isinstance(_n, dace.nodes.MapEntry) and _n.map.schedule == dace.dtypes.ScheduleType.Sequential for _n in ns])
            cont = cont or has_seq_map
            if cont:
                continue

            for n in graph.nodes():
                for n2 in sdutil.dfs_topological_sort(graph, n):
                    if remainder_loop:
                        for n2 in sdutil.dfs_topological_sort(graph, n):
                            if (
                                isinstance(n2, dace.nodes.MapEntry)
                                and n2.map.label.startswith("ThreadCoarsenedMap")
                                and graph.entry_node(n2).map.schedule == dace.dtypes.ScheduleType.GPU_ThreadBlock
                                and graph.entry_node(graph.entry_node(n2)) == n
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
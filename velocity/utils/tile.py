from typing import List
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
from utils.config import tile

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

def tile_specific_kernel(sdfg: dace.SDFG, params:List[str]=["_for_it_23", "_for_it_24"],
                         tblock_sizes:List[int]=[256,1,1],
                         coarsening_factors:List[int]=[4,2],
                         remainder_loop:bool=True):
    map_entry, parent_state, parent_sdfg = None, None, None
    for graph in [v for v, _ in list(sdfg.all_nodes_recursive()) if isinstance(v, dace.SDFGState)]:
        for n in graph.nodes():
            if isinstance(n, dace.nodes.MapEntry) and n.map.params == params:
                map_entry = n
                parent_state = graph
                parent_sdfg = graph.sdfg
                break

    if map_entry is None:
        return

    if map_entry is not None:
        mguid = map_entry.guid
        AddComputeElementBlockMap.apply_to(
            sdfg=parent_sdfg,
            verify=False,
            map_entry=map_entry,
            options={
                "compute_element_group_dims": tblock_sizes,
                "map_schedule": dace.dtypes.ScheduleType.GPU_Device,
                "schedule_to_add": dace.dtypes.ScheduleType.GPU_ThreadBlock,
                "tiles_evenly": remainder_loop,
            },
        )
        map_entry = parent_state.entry_node(map_entry) # Due to how maptiling works
        tblock_entry = set([e.dst for e in parent_state.out_edges(map_entry) if isinstance(e.dst, dace.nodes.MapEntry)]).pop()
        #print(map_entry, tblock_entry)

        if not remainder_loop:
            for i, ((b, e, s), (tb, te, ts)) in enumerate(zip(map_entry.map.range, tblock_entry.map.range)):
                if coarsening_factors[i] == 1:
                    continue
                range1 = (e+1-b)//s
                range2 = (te+1-tb)//ts
                dim = int(range1 // range2)
                if coarsening_factors[i] != 1:
                    assert dim % coarsening_factors[-(i+1)] == 0, f"Coarsening factor {coarsening_factors[i]} is not a divisor of {dim}"

            ThreadCoarsening.apply_to(
                sdfg=parent_sdfg,
                verify=False,
                thread_group_map_entry=tblock_entry,
                device_map_entry=map_entry,
                options={
                    "tile_sizes": list(reversed(coarsening_factors)),
                },
            )
        else:
            ThreadCoarsening.apply_to(
                sdfg=parent_sdfg,
                verify=False,
                thread_group_map_entry=tblock_entry,
                device_map_entry=map_entry,
                options={
                    "tile_sizes": list(reversed(coarsening_factors)),
                },
            )

        #map_entry = parent_state.entry_node(map_entry) # Due to how maptiling works
        tblock_entry = set([e.dst for e in parent_state.out_edges(map_entry) if isinstance(e.dst, dace.nodes.MapEntry)]).pop()
        inner_work_map_entry = set([e.dst for e in parent_state.out_edges(tblock_entry) if isinstance(e.dst, dace.nodes.MapEntry)]).pop()
        #print(map_entry, tblock_entry, inner_work_map_entry)

        if remainder_loop:
            RemainderLoopStencilMap.apply_to(
                sdfg=parent_sdfg,
                verify=True,
                inner_work_map_entry=inner_work_map_entry,
                tblock_type=dace.dtypes.ScheduleType.GPU_ThreadBlock,
                options={
                    "tblock_type": dace.dtypes.ScheduleType.GPU_ThreadBlock,
                }
            )

    pass

def tile_kernels(sdfg: dace.SDFG):
    for graph in [v for v, _ in list(sdfg.all_nodes_recursive()) if isinstance(v, dace.SDFGState)]:
        for n in graph.nodes():
            if isinstance(n, dace.nodes.MapEntry):
                if n.schedule == dace.ScheduleType.GPU_Device:
                    _coarsening_factors = []

                    if len(n.map.range) < 2:
                        continue
                    (b, e, s) = n.map.range[1]
                    range1 = (e+1-b)//s
                    dim = 1
                    try:
                        dim = range1
                    except:
                        dim = 1
                    if dim == 92:
                        coarsening_factor = 2
                    if dim == 91:
                        coarsening_factor = 1 # could be 7 but it is probablly too much
                    elif dim == 90:
                        coarsening_factor = 3
                    elif dim == 89:
                        coarsening_factor = 1
                    else:
                        coarsening_factor = 1
                    _coarsening_factors.append(coarsening_factor)

                    if  _coarsening_factors != 1:
                        AddComputeElementBlockMap.apply_to(
                            sdfg=graph.sdfg,
                            verify=False,
                            map_entry=n,
                            options={
                                "compute_element_group_dims": [256, 1, 1],
                                "map_schedule": dace.dtypes.ScheduleType.GPU_Device,
                                "schedule_to_add": dace.dtypes.ScheduleType.GPU_ThreadBlock,
                                "tiles_evenly": False,
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

                    for (b, e, s), (tb, te, ts) in zip(n.map.range, n2.map.range):
                        range1 = (e+1-b)//s
                        range2 = (te+1-tb)//ts
                        dim = 1
                        try:
                            dim = int(range1 // range2)
                        except:
                            dim = 1
                        if dim == 92:
                            coarsening_factor = 2
                        if dim == 91:
                            coarsening_factor = 1 # could be 7 but it is probablly too much
                        elif dim == 90:
                            coarsening_factor = 3
                        elif dim == 89:
                            coarsening_factor = 1
                        else:
                            coarsening_factor = 1
                        coarsening_factors.append(coarsening_factor)

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

    sdfg.validate()
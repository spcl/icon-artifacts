import dace

def insert_timers_for_profiling(sdfg: dace.SDFG):
    deflatten_state = None
    deflatten_node = None
    flatten_state = None
    flatten_node = None
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.LibraryNode) and "deflatten" in node.label:
                deflatten_state = state
                deflatten_node = node
            if isinstance(node, dace.nodes.LibraryNode) and "flatten" in node.label and "deflatten" not in node.label:
                flatten_state = state
                flatten_node = node
                break
    if deflatten_state is None or deflatten_node is None:
        raise ValueError("Deflatten node not found in SDFG")

    last_blocks = [n for n in sdfg.nodes() if sdfg.out_degree(n) == 0]
    assert len(last_blocks) == 1, "Expected exactly one last block in the SDFG"
    last_block = last_blocks[0]

    timer_sync_state1 = sdfg.add_state_after(state=flatten_state, label="entry_timer_sync")
    timer_sync_node1 = timer_sync_state1.add_tasklet(
        name="timer_wait1",
        code=f'dace_wait_device();',
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_wait_device.h"',
    )
    timer_state1 = sdfg.add_state_after(state=timer_sync_state1, label="entry_timer")
    timer_node1 = timer_state1.add_tasklet(
        name="timer1",
        code=f'dace_measure_time("{sdfg.name}");',
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_measure_time.h"',
    )

    timer_state2 = sdfg.add_state_before(state=deflatten_state, label="exit_timer")
    timer_node2 = timer_state2.add_tasklet(
        name="timer2",
        code=f'dace_measure_time("{sdfg.name}");',
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        #code_global='#include "dace_measure_time.h"',
    )


def insert_synchronization_for_profiling(sdfg: dace.SDFG):
    deflatten_state = None
    deflatten_node = None
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.LibraryNode) and "deflatten" in node.label:
                deflatten_state = state
                deflatten_node = node
                break
    if deflatten_state is None or deflatten_node is None:
        raise ValueError("Deflatten node not found in SDFG")

    last_blocks = [n for n in sdfg.nodes() if sdfg.out_degree(n) == 0]
    assert len(last_blocks) == 1, "Expected exactly one last block in the SDFG"
    last_block = last_blocks[0]


    sync_state1 = sdfg.add_state_before(state=deflatten_state, label="profile_sync_state")
    sync_node1 = sync_state1.add_tasklet(
        name="sync1",
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_wait_device.h"',
    )

    sync_state2 = sdfg.add_state_after(state=last_block, label="program_exit_sync")
    sync_node2 = sync_state2.add_tasklet(
        name="sync2",
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        # code_global='#include "dace_wait_device.h"', # skip include
    )

    start_block = sdfg.start_block
    sync_state3 = sdfg.add_state_before(start_block, label="profile_start_sync")
    sync_node3 = sync_state3.add_tasklet(
        name="sync0",
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        #code_global='#include "dace_wait_device.h"', # skip include
    )

def remove_profiling_states(sdfg: dace.SDFG):
    timer_state_names = {"entry_timer", "exit_timer"}
    rm_state_and_reroute(sdfg, timer_state_names)

def rm_state_and_reroute(sdfg:dace.SDFG, state_names):
    for state in sdfg.all_states():
        if state.label in state_names:
            src_edge = sdfg.in_edges(state)[0] if len(sdfg.in_edges(state)) == 1 else None
            dst_edge = sdfg.out_edges(state)[0] if len(sdfg.out_edges(state)) == 1 else None
            sdfg.remove_node(state)
            if src_edge is not None and dst_edge is not None:
                nassignments = dict()
                for k, v in src_edge.data.assignments.items():
                    if k not in nassignments:
                        nassignments[k] = v
                    if k in nassignments:
                        if nassignments[k] != v:
                            raise ValueError(f"Duplicate assignment for key {k} in edge {src_edge}")
                for k, v in dst_edge.data.assignments.items():
                    if k not in nassignments:
                        nassignments[k] = v
                    if k in nassignments:
                        if nassignments[k] != v:
                            raise ValueError(f"Duplicate assignment for key {k} in edge {dst_edge}")
                sdfg.add_edge(src_edge.src, dst_edge.dst, dace.InterstateEdge(assignments=nassignments))

def remove_sync_states(sdfg:dace.SDFG):
    sync_state_names = {"program_exit_sync", "profile_start_sync", "profile_sync_state", "entry_timer_sync"}
    rm_state_and_reroute(sdfg, sync_state_names)

def set_default_stream(sdfg: dace.SDFG):
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry) and n.map.schedule == dace.ScheduleType.GPU_Device:
            n._cuda_stream = "nullptr"
            n.map._cuda_stream = "nullptr"

def insert_synchronization_and_timers_for_profiling(sdfg: dace.SDFG):
    insert_synchronization_for_profiling(sdfg)
    insert_timers_for_profiling(sdfg)

def remove_sync_and_profiling_states(sdfg: dace.SDFG):
    remove_sync_states(sdfg)
    remove_profiling_states(sdfg)

def insert_program_entry_exit_syncs(sdfg: dace.SDFG):
    last_blocks = [n for n in sdfg.nodes() if sdfg.out_degree(n) == 0]
    assert len(last_blocks) == 1, "Expected exactly one last block in the SDFG"
    last_block = last_blocks[0]


    sync_state1 = sdfg.add_state_before(state=sdfg.start_block, label="program_entry_sync")
    sync_node1 = sync_state1.add_tasklet(
        name="sync1",
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_wait_device.h"',
    )

    sync_state2 = sdfg.add_state_after(state=last_block, label="program_exit_sync")
    sync_node2 = sync_state2.add_tasklet(
        name="sync2",
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        # code_global='#include "dace_wait_device.h"', # skip include
    )

def insert_pre_reduction_sync(sdfg: dace.SDFG):
    last_blocks = [n for n in sdfg.nodes() if sdfg.out_degree(n) == 0]
    assert len(last_blocks) == 1, "Expected exactly one last block in the SDFG"
    last_block = last_blocks[0]
    sync_state2 = sdfg.add_state_before(state=last_block, label="pre_reduce_sync")
    sync_node2 = sync_state2.add_tasklet(
        name="sync0",
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_wait_device.h"',
    )

def rm_reduntant_copies(sdfg: dace.SDFG):
    for state in sdfg.all_states():
        for edge in state.edges():
            if edge not in state.edges():
                continue
            if (isinstance(edge.src, dace.nodes.AccessNode) and
                isinstance(edge.dst, dace.nodes.AccessNode) and
                edge.src.data == edge.dst.data
                ):
                state.remove_edge(edge)
                state.remove_node(edge.src)
                state.remove_node(edge.dst)


    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                rm_reduntant_copies(node.sdfg)
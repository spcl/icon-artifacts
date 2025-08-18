import dace

ENTRY_TIMER = "entry_timer"
EXIT_TIMER = "exit_timer"
PROFILE_START_SYNC = "profile_start_sync"
PROFILE_STOP_SYNC = "profile_stop_sync"
PROGRAM_EXIT_SYNC = "program_exit_sync"
PROGRAM_ENTRY_SYNC = "program_entry_sync"


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

    timer_sync_state1 = sdfg.add_state_after(state=flatten_state, label=PROFILE_START_SYNC)
    timer_sync_node1 = timer_sync_state1.add_tasklet(
        name="sync_tasklet_" + PROFILE_START_SYNC,
        code=f"dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_wait_device.h"',
    )
    timer_state1 = sdfg.add_state_after(state=timer_sync_state1, label=ENTRY_TIMER)
    timer_node1 = timer_state1.add_tasklet(
        name="timer_" + ENTRY_TIMER,
        code=f'dace_measure_time("{sdfg.name}");',
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_measure_time.h"',
    )

    timer_state2 = sdfg.add_state_before(state=deflatten_state, label=EXIT_TIMER)
    timer_node2 = timer_state2.add_tasklet(
        name="timer_" + EXIT_TIMER,
        code=f'dace_measure_time("{sdfg.name}");',
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        # code_global='#include "dace_measure_time.h"',
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

    sync_state1 = sdfg.add_state_before(state=deflatten_state, label=PROFILE_STOP_SYNC)
    sync_node1 = sync_state1.add_tasklet(
        name="sync_tasklet_" + PROFILE_STOP_SYNC,
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_wait_device.h"',
    )

    insert_program_entry_exit_syncs(sdfg)


def remove_profiling_states(sdfg: dace.SDFG):
    timer_state_names = {ENTRY_TIMER, EXIT_TIMER}
    rm_state_and_reroute(sdfg, timer_state_names)


def rm_state_and_reroute(sdfg: dace.SDFG, state_names):
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
                    if k in nassignments and v != nassignments[k]:
                        raise ValueError(f"Duplicate assignment for key {k} in edge {src_edge}")
                for k, v in dst_edge.data.assignments.items():
                    if k not in nassignments:
                        nassignments[k] = v
                    if k in nassignments and v != nassignments[k]:
                        raise ValueError(f"Duplicate assignment for key {k} in edge {src_edge}")
                sdfg.add_edge(src_edge.src, dst_edge.dst, dace.InterstateEdge(assignments=nassignments))


def remove_sync_states(sdfg: dace.SDFG):
    sync_state_names = {PROGRAM_ENTRY_SYNC, PROGRAM_EXIT_SYNC, PROFILE_START_SYNC, PROFILE_STOP_SYNC}
    rm_state_and_reroute(sdfg, sync_state_names)


def insert_program_entry_exit_syncs(sdfg: dace.SDFG):
    last_blocks = [n for n in sdfg.nodes() if sdfg.out_degree(n) == 0]
    assert len(last_blocks) == 1, "Expected exactly one last block in the SDFG"
    last_block = last_blocks[0]

    if "predictor_pre" in sdfg.name:
        sync_state1 = sdfg.add_state_before(state=sdfg.start_block, label=PROGRAM_ENTRY_SYNC)
        sync_node1 = sync_state1.add_tasklet(
            name="sync_tasklet_" + PROGRAM_ENTRY_SYNC,
            code="dace_wait_device();",
            inputs={},
            outputs={},
            language=dace.dtypes.Language.CPP,
            code_global='#include "dace_wait_device.h"',
        )

    sync_state2 = sdfg.add_state_after(state=last_block, label=PROGRAM_EXIT_SYNC)
    sync_node2 = sync_state2.add_tasklet(
        name="sync_tasklet_" + PROGRAM_EXIT_SYNC,
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        # code_global='#include "dace_wait_device.h"', # skip include
    )

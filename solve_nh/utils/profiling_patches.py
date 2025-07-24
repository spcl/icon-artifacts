import dace

def insert_timers_for_profiling(sdfg: dace.SDFG):
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

    timer_state1 = sdfg.add_state_before(state=sdfg.start_block, label="profile_sync_state")
    timer_node1 = timer_state1.add_tasklet(
        name="timer1",
        code=f'dace_measure_time("{sdfg.name}");',
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        code_global='#include "dace_measure_timer.h"',
    )

    timer_state2 = sdfg.add_state_after(state=last_block, label="program_exit_sync")
    timer_node2 = timer_state2.add_tasklet(
        name="timer2",
        code=f'dace_measure_time("{sdfg.name}");',
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        #code_global='#include "dace_measure_timer.h"',
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
        name="sync3",
        code="dace_wait_device();",
        inputs={},
        outputs={},
        language=dace.dtypes.Language.CPP,
        #code_global='#include "dace_wait_device.h"', # skip include
    )

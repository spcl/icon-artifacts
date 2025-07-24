import dace
import copy


headers = """
#include <cuda_runtime.h>
#include <cstdio>
\n\n
"""

get_start_event = """
static cudaEvent_t& get_start_event() {
    static cudaEvent_t start_event;
    static bool initialized = false;
    if (!initialized) {
        cudaEventCreate(&start_event);
        initialized = true;
    }
    return start_event;
}\n\n
"""

get_stop_event = """
static cudaEvent_t& get_stop_event() {
    static cudaEvent_t stop_event;
    static bool initialized = false;
    if (!initialized) {
        cudaEventCreate(&stop_event);
        initialized = true;
    }
    return stop_event;
}
\n\n
"""

dace_timer_start = """
static void dace_timer_start() {
    cudaDeviceSynchronize();
    cudaEventRecord(get_start_event());
}
\n\n
"""

dace_timer_stop = """
static void dace_timer_stop(const char* label) {
    cudaEventRecord(get_stop_event());
    cudaEventSynchronize(get_stop_event());

    float milliseconds = 0.0f;
    cudaEventElapsedTime(&milliseconds, get_start_event(), get_stop_event());

    printf("[CUDA TIMING] %s: %.5f us\n", label, milliseconds * 1000);
    cudaDeviceSynchronize();
}
\n\n
"""

def create_profile_sdfg(sdfg: dace.SDFG):
    id = 0
    new_first_state = sdfg.add_state_before(sdfg.start_state, "init_events", is_start_block=True, is_start_state=True)
    init_events_tasklet = new_first_state.add_tasklet(
        "init_events",
        {},
        {},
        code="get_start_event();\nget_stop_event();",
        language=dace.Language.CPP,
        code_global=headers + get_start_event + get_stop_event + dace_timer_start + dace_timer_stop
    )
    scl_name = "profile_aid_scalar"
    scl_desc = dace.data.Scalar(
        dtype=dace.int64,
        transient=True,
        storage=dace.StorageType.Register
    )
    if scl_name not in sdfg.arrays:
        sdfg.add_datadesc(scl_name, copy.deepcopy(scl_desc))

    for node, state in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.MapEntry) and node.map.schedule == dace.ScheduleType.GPU_Device:
            # Put a start event before each map entry
            # Put a stop event after each map exit
            map_identifier = node.label + "[" + ', '.join(node.map.params) + f"]({id})"
            if scl_name not in state.sdfg.arrays:
                state.sdfg.add_datadesc(scl_name, copy.deepcopy(scl_desc))

            scl_a1 = state.add_access(scl_name)
            #scl_a2 = state.add_access(scl_name)

            # Start event before the map entry
            start_event_tasklet = state.add_tasklet(
                f"start_event_{id}",
                {},
                {"_out_tracker"},
                code="dace_timer_start();",
                language=dace.Language.CPP
            )
            start_event_tasklet.add_out_connector("_out_tracker")
            #srcs = {e.src for e in state.in_edges(node)}
            #if len(srcs) > 0:
            #    state.add_edge(
            #        srcs.pop(), None, start_event_tasklet, None, dace.memlet.Memlet()
            #    )
            state.add_edge(
                scl_a1, None, node, "_tracker", dace.memlet.Memlet.from_array(scl_name, sdfg.arrays[scl_name])
            )
            if "_tracker" not in node.in_connectors:
                node.add_in_connector("_tracker", dtype=dace.int64)
            state.add_edge(
                start_event_tasklet, "_out_tracker", scl_a1, None,
                dace.memlet.Memlet.from_array(scl_name, sdfg.arrays[scl_name])
            )

            # Stop event after the map exit
            map_exit = state.exit_node(node)
            stop_event_tasklet = state.add_tasklet(
                f"stop_event_{id}",
                {"_in_tracker"},
                {},
                code=f'dace_timer_stop("{map_identifier}");',
                language=dace.Language.CPP
            )
            #stop_event_tasklet.add_in_connector("_in_tracker")
            #dsts = {e.dst for e in state.out_edges(state.exit_node(node))}
            #if len(dsts) > 0:
            #    state.add_edge(
            #        stop_event_tasklet, None, dsts.pop(), None, dace.memlet.Memlet()
            #    )
            # Assert at least one out edge
            dsts = {e.dst for e in state.out_edges(map_exit) if isinstance(e.dst, dace.nodes.AccessNode)}
            assert len(dsts) > 0, "Map exit must have at least one out edge."
            dst = dsts.pop()
            stop_event_tasklet.add_in_connector("_in_tracker")
            #state.add_edge(
            #    map_exit, None, stop_event_tasklet, None, dace.memlet.Memlet()
            #)
            dst_dsts = {e.dst for e in state.out_edges(dst)}
            state.add_edge(
                dst, None, stop_event_tasklet, "_in_tracker", dace.memlet.Memlet.from_array(dst.data, sdfg.arrays[dst.data])
            )
            if len(dst_dsts) > 0:
                state.add_edge(
                    stop_event_tasklet, None, dst_dsts.pop(), None, dace.memlet.Memlet()
                )
            #state.add_edge(
            #    scl_a2, None, stop_event_tasklet, "_in_tracker",
            #    dace.memlet.Memlet.from_array(scl_name, sdfg.arrays[scl_name])
            #)

            id += 1
    sdfg.validate()
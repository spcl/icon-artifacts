import dace


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
    new_first_state = sdfg.add_state_before(sdfg.start_state, "init_events")
    init_events_tasklet = new_first_state.add_tasklet(
        "init_events",
        {},
        {},
        code="dace_start_event();\ndace_stop_event();",
        language=dace.Language.CPP,
        code_global=headers + get_start_event + get_stop_event + dace_timer_start + dace_timer_stop
    )

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.MapEntry):
                # Put a start event before each map entry
                # Put a stop event after each map exit
                map_identifier = node.label + "[ + ', '.join(node.map.params) + ' ]"

                # Start event before the map entry
                start_event_tasklet = state.add_tasklet(
                    f"start_event_{id}",
                    {},
                    {},
                    code="dace_timer_start();",
                    language=dace.Language.CPP
                )
                srcs = {e.src for e in state.in_edges(node)}
                if len(srcs) > 0:
                    state.add_edge(
                        srcs.pop(), None, start_event_tasklet, None, dace.memlet.Memlet()
                    )
                state.add_edge(
                    start_event_tasklet, None, node, None, dace.memlet.Memlet()
                )

                # Stop event after the map exit
                map_exit = state.exit_node(node)
                stop_event_tasklet = state.add_tasklet(
                    f"stop_event_{id}",
                    {"label": dace.types.pointer(dace.types.char)},
                    {},
                    code=f'dace_timer_stop("{map_identifier}");',
                    language=dace.Language.CPP
                )
                dsts = {e.dst for e in state.out_edges(state.exit_node(node))}
                if len(dsts) > 0:
                    state.add_edge(
                        stop_event_tasklet, None, dsts.pop(), None, dace.memlet.Memlet()
                    )
                state.add_edge(
                    map_exit, None, stop_event_tasklet, None, dace.memlet.Memlet()
                )

                id += 1
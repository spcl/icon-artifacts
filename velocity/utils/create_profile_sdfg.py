import dace
import copy

def create_profile_sdfg(sdfg: dace.SDFG):
    # First, count the number of GPU_Device maps
    num_maps = 0
    for node, state in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.MapEntry) and node.map.schedule == dace.ScheduleType.GPU_Device:
            num_maps += 1

    # Generate the global helper functions for each map
    funcs = ["#include <cuda_runtime.h>", "#include <cstdio>"]
    for i in range(num_maps):
        funcs.append(f"""
static cudaEvent_t& get_start_event_{i}() {{
    static cudaEvent_t start_event;
    static bool initialized = false;
    if (!initialized) {{
        cudaEventCreate(&start_event);
        initialized = true;
    }}
    return start_event;
}}
""")
        funcs.append(f"""
static cudaEvent_t& get_stop_event_{i}() {{
    static cudaEvent_t stop_event;
    static bool initialized = false;
    if (!initialized) {{
        cudaEventCreate(&stop_event);
        initialized = true;
    }}
    return stop_event;
}}
""")
        funcs.append(f"""
static void dace_timer_start_{i}() {{
    cudaDeviceSynchronize();
    cudaEventRecord(get_start_event_{i}());
}}
""")
        funcs.append(f"""
static void dace_timer_stop_{i}(const char* label) {{
    cudaEventRecord(get_stop_event_{i}());
    cudaEventSynchronize(get_stop_event_{i}());

    float milliseconds = 0.0f;
    cudaEventElapsedTime(&milliseconds, get_start_event_{i}(), get_stop_event_{i}());

    printf("[CUDA TIMING] %s: %.5f us\\n", label, milliseconds * 1000);
    cudaDeviceSynchronize();
}}
""")
    global_code = "\n".join(funcs)

    # Add an initialisation state that creates all events
    init_state = sdfg.add_state_before(sdfg.start_block, "init_events", is_start_block=True)
    init_code = "\n".join([f"get_start_event_{i}(); get_stop_event_{i}();" for i in range(num_maps)])
    init_tasklet = init_state.add_tasklet(
        "init_events",
        {},
        {},
        code=init_code,
        language=dace.Language.CPP,
        code_global=global_code,
        side_effects=True,
    )
    # No edges needed; the tasklet runs once.


    # Instrument each GPU map
    map_id = 0
    for node, state in sdfg.all_nodes_recursive():
        if not (isinstance(node, dace.nodes.MapEntry) and node.map.schedule == dace.ScheduleType.GPU_Device):
            continue

        map_entry = node
        map_exit = state.exit_node(node)
        label = f"{node.label}[{', '.join(node.map.params)}](Profiler Id: {map_id})"

        # Add access nodes for the scalar
        scl_name = f"profile_aid_scalar_{map_id}"

        assert scl_name not in state.sdfg.arrays
        state.sdfg.add_datadesc(scl_name, 
            dace.data.Scalar(dtype=dace.int64, transient=True, storage=dace.StorageType.Register)
        )

        scl_a1 = state.add_access(scl_name)
        #scl_a2 = state.add_access(scl_name)

        # ---- Start timer before the map ----
        start_tasklet = state.add_tasklet(
            f"start_event_{map_id}",
            {},
            {"_out_tracker"},
            code=f"dace_timer_start_{map_id}();",
            language=dace.Language.CPP,
            side_effects=True,
        )
        start_tasklet.add_out_connector("_out_tracker")
        # Connect start_tasklet -> scl_a1 -> map_entry
        state.add_edge(start_tasklet, "_out_tracker", scl_a1, None,
                       dace.memlet.Memlet.from_array(scl_name, state.sdfg.arrays[scl_name]))
        # Add tracker connector to map_entry if not present
        if "_tracker" not in map_entry.in_connectors:
            map_entry.add_in_connector("_tracker", dtype=dace.int64)
        state.add_edge(scl_a1, None, map_entry, "_tracker",
                       dace.memlet.Memlet.from_array(scl_name, state.sdfg.arrays[scl_name]))

        # ---- Stop timer after the map ----
        # Find a successor access node of the map_exit to attach the stop_tasklet
        out_edges = list(state.out_edges(map_exit))
        # There should be at least one outgoing edge from the map_exit
        assert len(out_edges) > 0, "Map exit must have at least one outgoing edge."
        # We'll pick the first destination (any access node) to route the scalar through
        stop_tasklet = state.add_tasklet(
            f"stop_event_{map_id}",
            {},
            {},
            code=f'dace_timer_stop_{map_id}("{label}");',
            language=dace.Language.CPP,
            side_effects=True,
        )
        #stop_tasklet.add_in_connector("_in_tracker")

        # This crashes f2dace
        """
        # Add edge from map_exit to scl_a2 (with an empty memlet, just control)
        state.add_edge(map_exit, None, scl_a2, None, dace.memlet.Memlet())
        # Connect scl_a2 to stop_tasklet
        state.add_edge(scl_a2, None, stop_tasklet, "_in_tracker",
                       dace.memlet.Memlet.from_array(scl_name, state.sdfg.arrays[scl_name]))
        """
        for e in out_edges:
            dst = e.dst
            state.add_edge(
                dst, None, stop_tasklet, None, dace.memlet.Memlet(None)
            )

        map_id += 1

    sdfg.validate()
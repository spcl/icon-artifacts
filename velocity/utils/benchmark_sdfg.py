import dace
import os
from dace.libraries.standard import CodeLibraryNode
from dace.properties import make_properties, Property
from utils.compile_sdfg import compile_sdfg


@make_properties
class TimeStartNode(CodeLibraryNode):
    def __init__(self):
        super().__init__(name="time_start", input_names=[], output_names=[])

    def generate_code(self, inputs, outputs):
        return "measure_time();"


@make_properties
class TimeEndNode(CodeLibraryNode):
    def __init__(self):
        super().__init__(name="time_end", input_names=[], output_names=[])

    def generate_code(self, inputs, outputs):
        return 'measure_time(__state, "SDFG w/o flatten & copy");'


def benchmark_sdfg(
    sdfg: dace.SDFG,
    prefix: str,
    gpu: bool,
    release: bool,
    warmups: int = 0,
    measurements: int = 1,
    profile=True,
    output_file=None,
    save_kernel_sdfg=False,
):
    sdfg.instrument = dace.InstrumentationType.Timer
    sdfg_name = sdfg.name

    # Add timing calls for profiling
    if profile:
        kernels = []
        lib_nodes = []
        for state in sdfg.all_states():
            maps = [
                n
                for n in state.nodes()
                if isinstance(n, dace.nodes.MapEntry) and state.entry_node(n) is None
            ]
            libs = [
                n
                for n in state.nodes()
                if isinstance(n, dace.nodes.LibraryNode) and state.entry_node(n) is None
            ]
            kernels.extend(maps)
            lib_nodes.extend(libs)

        for i, kernel in enumerate(kernels):
            if (
                kernel.map.schedule == dace.ScheduleType.GPU_Default
                or kernel.map.schedule == dace.ScheduleType.GPU_Device
                or kernel.map.schedule == dace.ScheduleType.GPU_ThreadBlock
                or kernel.map.schedule == dace.ScheduleType.GPU_ThreadBlock_Dynamic
                or kernel.map.schedule == dace.ScheduleType.GPU_Persistent
            ):
                kernel.map.label = f"GPU_Kernel_{i}"
                kernel.instrument = dace.InstrumentationType.GPU_Events
            else:
                kernel.map.label = f"CPU_Kernel_{i}"
                kernel.instrument = dace.InstrumentationType.Timer

        for i, lib_node in enumerate(lib_nodes):
            lib_node: CodeLibraryNode
            lib_node.name = f"{lib_node.name}_{i}"
            lib_node.code = f"""
            auto lib_startT_{i} = std::chrono::high_resolution_clock::now();
            {lib_node.code}
            auto lib_endT_{i} = std::chrono::high_resolution_clock::now();
            unsigned long int lib_start_{i} = std::chrono::duration_cast<std::chrono::microseconds>(lib_startT_{i}.time_since_epoch()).count();
            unsigned long int lib_end_{i} = std::chrono::duration_cast<std::chrono::microseconds>(lib_endT_{i}.time_since_epoch()).count();
            __state->report.add_completion("Lib {lib_node.name}", "Timer", lib_start_{i}, lib_end_{i}, 0, 0, 0);
            """

    # Start timer after the first state, and stop before the last state
    start_timer_state = sdfg.add_state_after(sdfg.start_state)
    dummy_array = None
    for a, k in sdfg.arrays.items():
        if not isinstance(k, dace.data.View):
            dummy_array = a
            break
    start_timer_state.add_edge(
        start_timer_state.add_read(dummy_array),
        None,
        TimeStartNode(),
        None,
        dace.Memlet(),
    )
    assert len(sdfg.sink_nodes()) == 1, "Only one sink node supported"
    stop_timer_state = sdfg.add_state_before(sdfg.sink_nodes()[0])
    stop_timer_state.add_edge(
        stop_timer_state.add_read(dummy_array),
        None,
        TimeEndNode(),
        None,
        dace.Memlet(),
    )

    # Add timing function
    with open("include/timer.h", "r") as file:
        timing_function = file.read()
    sdfg.append_global_code("\n")
    sdfg.append_global_code(timing_function)
    sdfg.append_global_code("\n")

    # Add early abort
    sdfg.append_exit_code("__err = -1;")

    # Save modified SDFG
    if save_kernel_sdfg:
        sdfg.save(f"{sdfg_name}_kernels.sdfg")

    # Compile
    compile_sdfg(sdfg, gpu=gpu, release=release)

    # Warmup
    for i in range(warmups):
        os.system(f"./{sdfg_name}")

    # Measure
    times = []
    for i in range(measurements):
        sdfg.clear_instrumentation_reports()
        os.system(f"./{sdfg_name}")

        for report in sdfg.get_instrumentation_reports():
            for event in report.events:
                name = event.name
                duration = event.duration
                times.append((name, duration))

    # Output to file
    if output_file:
        if not os.path.exists(output_file):
            with open(output_file, "w") as f:
                f.write("tag,name,time(us)\n")

        sorted_times = sorted(times, key=lambda x: x[1])
        for name, time in sorted_times:
            with open(output_file, "a") as f:
                f.write(f"{prefix},{name},{time}\n")

    # If not file is defined, take minimal time of each named kernel
    if not output_file:
        min_times = {}
        for name, time in times:
            if name not in min_times:
                min_times[name] = time
            else:
                min_times[name] = min(min_times[name], time)

        min_times = dict(sorted(min_times.items(), key=lambda item: item[1]))
        print("tag,name,time(us)")
        for name, time in min_times.items():
            print(f"{name},{time}")

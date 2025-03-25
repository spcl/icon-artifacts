import dace
import os
import shutil
from pathlib import Path
from utils.compile_sdfg import _pre_injection, _injection, _post_injection


def benchmark_sdfg(
    sdfg: dace.SDFG,
    prefix: str,
    gpu: bool,
    release: bool,
    warmups: int = 0,
    measurements: int = 1,
    profile=True,
    output_file=None,
):
    sdfg.instrument = dace.InstrumentationType.Timer
    sdfg_name = sdfg.name

    # Add timing calls for profiling
    if profile:
        kernels = []
        for state in sdfg.all_states():
            maps = [
                n
                for n in state.nodes()
                if isinstance(n, dace.nodes.MapEntry) and state.entry_node(n) is None
            ]
            kernels.extend(maps)

        for i, kernel in enumerate(kernels):
            if kernel.map.schedule == dace.ScheduleType.GPU_Default or kernel.map.schedule == dace.ScheduleType.GPU_Device or kernel.map.schedule == dace.ScheduleType.GPU_ThreadBlock or kernel.map.schedule == dace.ScheduleType.GPU_ThreadBlock_Dynamic or kernel.map.schedule == dace.ScheduleType.GPU_Persistent:
              kernel.map.label = f"kernel_{i}_GPU"
              kernel.instrument = dace.InstrumentationType.GPU_Events
            else:
              kernel.map.label = f"kernel_{i}_CPU"
              kernel.instrument = dace.InstrumentationType.Timer

        sdfg.save(f"{sdfg_name}_named_kernels.sdfg")

    # Add timing function
    with open("include/timer.h", "r") as file:
        timing_function = file.read()   
    sdfg.append_global_code(timing_function)

    # Generate code with injections
    _pre_injection(sdfg, gpu=gpu, release=release)
    _injection(sdfg, gpu=gpu, release=release)

    # Add timing calls without flattener
    with open(f"{sdfg.build_folder}/src/cpu/{sdfg_name}.cpp", "r") as file:
        code = file.read()

    # Check that // End flatten and // Start deflatten are present
    assert "// End flatten" in code
    assert "// Start deflatten" in code

    # Find // End flatten
    end_flatten = code.find("// End flatten")
    code = code[:end_flatten] + f"measure_time();" + code[end_flatten:]

    # Find // Start deflatten
    start_deflatten = code.find("// Start deflatten")
    code = (
        code[:start_deflatten]
        + f'measure_time(__state,"SDFG w/o flattening");'
        + code[start_deflatten:]
    )

    with open(f"{sdfg.build_folder}/src/cpu/{sdfg_name}.cpp", "w") as file:
        file.write(code)

    # Compile
    _post_injection(sdfg, gpu=gpu, release=release)

    # Warmup
    for i in range(warmups):
        os.system(f"./{sdfg_name}")

    # Measure
    times = []
    for i in range(measurements):
        sdfg.clear_instrumentation_reports()
        os.system(f"./{sdfg_name}")
        report = sdfg.get_latest_report()

        for event in report.events:
            name = event.name
            duration = event.duration
            times.append((name, duration))

    # Output to file
    if output_file:
        for name, time in times:
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
        for name, time in min_times.items():
            print(f"{name},{time}")

from pathlib import Path
import dace
import shutil
import os
from dace.transformation.interstate import LoopToMap, ContinueToCondition
from dace.transformation.passes import SymbolPropagation, StructToContainerGroups
from dace.transformation.dataflow import MapCollapse
from utils import (
    make_array_loop_local,
    loop_to_max_reduction,
    cfl_clipping_to_reduction,
    maxvcfl_to_reduction,
    tmp_call_13_to_reduction,
    levmask_to_reduction,
    compare_got_and_want,
    compile,
    count_loops,
)


use_cache = True
run_benchmark = False

# Load SDFG
sdfg = dace.SDFG.from_file("velocity.sdfgz")
sdfg.validate()
build_loc = sdfg.build_folder
sdfg_name = sdfg.name


################################################################################
### Apply Optimizations
################################################################################


# Apply transformations
if Path("cpu_pipe_stage1.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("cpu_pipe_stage1.sdfg")
else:
    sdfg.apply_transformations_repeated(ContinueToCondition)
    sdfg.simplify()
    SymbolPropagation().apply_pass(sdfg, {})
    sdfg.simplify()
    StructToContainerGroups(
        save_steps=False,
        verbose=False,
        simplify=False,
        interface_with_struct_copy=True,
        interface_to_gpu=False,
    ).apply_pass(sdfg, {})
    sdfg.simplify(skip=["ArrayElimination"])
    make_array_loop_local(sdfg, "difcoef", "FOR_l_505_c_505")
    make_array_loop_local(sdfg, "_if_cond_27", "FOR_l_555_c_555")
    sdfg.simplify(skip=["ArrayElimination"])
    loop_to_max_reduction(sdfg)
    cfl_clipping_to_reduction(sdfg)
    maxvcfl_to_reduction(sdfg)
    tmp_call_13_to_reduction(sdfg)
    levmask_to_reduction(sdfg)
    sdfg.simplify(skip=["ArrayElimination"])
    if use_cache:
        sdfg.save("cpu_pipe_stage1.sdfg")

if Path("cpu_pipe_stage2.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("cpu_pipe_stage2.sdfg")
else:
    sdfg.apply_transformations_repeated(LoopToMap)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
    if use_cache:
        sdfg.save("cpu_pipe_stage2.sdfg")

# How many loops?
count_loops(sdfg)
sdfg.validate()
sdfg.instrument = dace.InstrumentationType.Timer

# Turn all maps to CPU_Multicore
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, dace.nodes.MapEntry):
        node.map.schedule = dace.ScheduleType.CPU_Multicore


################################################################################
### Numerically validate the SDFG
################################################################################

# Compile the SDFG
compile(sdfg, gpu=False)

# check if execution was successful
if os.system(f"./{sdfg_name}") != 0:
    print("Execution failed")
    exit(1)

# Compare .got and .want files
compare_got_and_want()

################################################################################
### Measure performance
################################################################################

if run_benchmark:
    # Warmup
    for i in range(10):
        os.system(f"./{sdfg_name}")

    # Measure
    times = []
    for i in range(10):
        sdfg.clear_instrumentation_reports()
        os.system(f"./{sdfg_name}")
        report = sdfg.get_latest_report()
        assert report.events[-1].name == f"SDFG {sdfg.name}"
        time = report.events[-1].duration  # in us
        times.append(time)

    for time in times:
        print(f"CPU,{time}")

################################################################################
### Cleanup
################################################################################

# remove the compiled program
os.remove(sdfg_name)

# remove .got and .want files
for f in os.listdir():
    if f.endswith(".got") or f.endswith(".want"):
        os.remove(f)

# remove the .dacecache folder
shutil.rmtree(build_loc)

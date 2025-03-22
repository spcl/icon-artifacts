import math
import os
import shutil
from pathlib import Path
import shutil
import dace
import os
from dace.transformation.interstate import LoopToMap, ContinueToCondition
from dace.transformation.passes import SymbolPropagation, StructToContainerGroups
from dace.transformation.dataflow import MapCollapse

import dace
from dace.libraries.standard import CodeLibraryNode
from dace.properties import make_properties, Property
from dace.sdfg.state import LoopRegion, ConditionalBlock
from dace.transformation.dataflow import MapCollapse
from dace.transformation.interstate import (
    ContinueToCondition,
)
from dace.transformation.interstate import LoopToMap
from dace.transformation.passes import (
    StructToContainerGroups,
)
from dace.transformation.passes import (
    SymbolPropagation,
)
from dace.transformation.passes.to_gpu import ToGPU
from utils import (
    make_array_loop_local,
    loop_to_max_reduction,
    cfl_clipping_to_reduction,
    maxvcfl_to_reduction,
    tmp_call_13_to_reduction,
    levmask_to_reduction,
    compare_got_and_want,
    compile_sdfg,
    count_loops,
)


from velocity.map_fissions import YoloMapFission

use_cache = True
run_benchmark = False
cleanup = False

# Load SDFG
sdfg = dace.SDFG.from_file("velocity.sdfgz")
sdfg.validate()
build_loc = sdfg.build_folder
sdfg_name = sdfg.name

################################################################################
### Apply Optimizations
################################################################################


# Apply transformations
if Path("gpu_pipe_stage1.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("gpu_pipe_stage1.sdfg")
else:
    sdfg.apply_transformations_repeated(ContinueToCondition)
    sdfg.simplify(verbose=True)
    SymbolPropagation().apply_pass(sdfg, {})
    sdfg.simplify(verbose=True)
    StructToContainerGroups(
        validate=False,
        save_steps=False,
        verbose=False,
        simplify=False,
        interface_with_struct_copy=True,
        interface_to_gpu=True,
    ).apply_pass(sdfg, {})
    sdfg.simplify(skip=["ArrayElimination"], verbose=True)
    make_array_loop_local(sdfg, "difcoef", "FOR_l_505_c_505")
    make_array_loop_local(sdfg, "_if_cond_22", "FOR_l_555_c_555")
    loop_to_max_reduction(sdfg)
    cfl_clipping_to_reduction(sdfg)
    maxvcfl_to_reduction(sdfg)
    tmp_call_13_to_reduction(sdfg)
    levmask_to_reduction(sdfg)
    sdfg.simplify(skip=["ArrayElimination"], verbose=True)
    if use_cache:
        sdfg.save("gpu_pipe_stage1.sdfg")

if Path("gpu_pipe_stage2.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("gpu_pipe_stage2.sdfg")
else:
    sdfg.apply_transformations_repeated(LoopToMap)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"], verbose=True)
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"], verbose=True)
    ToGPU().apply_pass(sdfg, {})
    if use_cache:
        sdfg.save("gpu_pipe_stage2.sdfg")


sdfg.apply_transformations(YoloMapFission, validate=False)
sdfg.reset_cfg_list()
sdfg.save('/Users/pmz/Downloads/boo.sdfgz')
sdfg.validate()

# How many loops?
count_loops(sdfg)
sdfg.validate()
sdfg.instrument = dace.InstrumentationType.Timer

################################################################################
### Numerically validate the SDFG
################################################################################

# Compile the SDFG
compile_sdfg(sdfg, gpu=True, release=False)


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
        print(f"GPU,{time}")

################################################################################
### Cleanup
################################################################################

# remove the compiled program
if cleanup:
    os.remove(sdfg_name)

    # remove .got and .want files
    for f in os.listdir():
        if f.endswith(".got") or f.endswith(".want"):
            os.remove(f)

    # remove the .dacecache folder
    shutil.rmtree(build_loc)

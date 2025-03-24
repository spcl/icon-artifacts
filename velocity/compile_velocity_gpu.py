from pathlib import Path
import shutil
import dace
import os
from dace.transformation.interstate import LoopToMap, ContinueToCondition
from dace.transformation.passes import InlineSDFGs, SymbolPropagation, StructToContainerGroups
# from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.dataflow import MapCollapse, MapFusion
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
    move_transients_to_top_level,
    split_map_sdfg,
    untangle_if_sdfg,
    raise_loop_invariant_if,
    # wrap_reduction_and_T_l488_c488in_gpumap,
)

from utils.map_fissions import YoloMapFission

from utils.config import use_cache, run_benchmark, cleanup, reduction, release


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
    sdfg.simplify()
    SymbolPropagation().apply_pass(sdfg, {})
    sdfg.simplify()
    StructToContainerGroups(
        validate=False,
        save_steps=False,
        verbose=False,
        simplify=False,
        interface_with_struct_copy=True,
        interface_to_gpu=True,
    ).apply_pass(sdfg, {})
    sdfg.simplify(skip=["ArrayElimination"])
    make_array_loop_local(sdfg, "difcoef", "FOR_l_505_c_505")
    make_array_loop_local(sdfg, "_if_cond_27", "FOR_l_555_c_555")
    if reduction:
        loop_to_max_reduction(sdfg)
        cfl_clipping_to_reduction(sdfg)
        maxvcfl_to_reduction(sdfg)
        tmp_call_13_to_reduction(sdfg)
        levmask_to_reduction(sdfg)
    sdfg.simplify(skip=["ArrayElimination"])
    if use_cache:
        sdfg.save("gpu_pipe_stage1.sdfg")

if Path("gpu_pipe_stage2.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("gpu_pipe_stage2.sdfg")
else:
    sdfg.apply_transformations_repeated(LoopToMap)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
    sdfg.save("parallel.sdfgz", compress=True)
    move_transients_to_top_level(root=sdfg,
                                 upper_bounds={
                                     "z_w_con_c": 960,
                                     "maxvcfl_arr": 960,
                                     "cfl_clipping": 960,
                                     "z_w_concorr_mc": 960,
                                 }
                                )
    sdfg.save("transients_moved.sdfgz", compress=True)
    ToGPU().apply_pass(sdfg, {})
    if not reduction:
        for cfg in sdfg.nodes():
            if cfg.label == "FOR_l_568_c_568":
                s = sdfg.add_state_before(cfg, "copy_vcflmax")
                a0 = s.add_access("gpu_vcflmax")
                a1 = s.add_access("vcflmax")
                s.add_edge(a0, None, a1, None, dace.Memlet(expr="gpu_vcflmax"))
    # sdfg.apply_transformations_repeated(GPUKernelLaunchRestructure)
    # wrap_reduction_and_T_l488_c488in_gpumap(sdfg)
    if use_cache:
        sdfg.save("gpu_pipe_stage2.sdfg")


sdfg.apply_transformations(YoloMapFission, validate=False)
sdfg.validate()

untangle_if_sdfg(sdfg)
split_map_sdfg(sdfg, True)

for n, g in sdfg.all_nodes_recursive():
    if isinstance(n, dace.nodes.NestedSDFG):
        untangle_if_sdfg(n.sdfg)

for n, g in sdfg.all_nodes_recursive():
    if isinstance(n, dace.nodes.NestedSDFG):
        split_map_sdfg(n.sdfg, True)

sdfg.validate()

raise_loop_invariant_if(sdfg,check_invariant_if_conds = ["1 - ldeepatmo == 1", "_if_cond_27 == 1"],
                             copy_edge_before = [False, True])
raise_loop_invariant_if(sdfg,check_invariant_if_conds = ["not (lvn_only == 1)"],
                             copy_edge_before = [False])
# Nested Case extend support for this
#raise_loop_invariant_if(sdfg,check_invariant_if_conds = ["not (lvn_only == 1)", "_if_cond_27 == 1"],
#                             copy_edge_before = [False, True])
raise_loop_invariant_if(sdfg,check_invariant_if_conds = ["(1 - lvn_only) == 1"],
                             copy_edge_before = [False])
raise_loop_invariant_if(sdfg,check_invariant_if_conds = ["(istep == 1) == 1"],
                             copy_edge_before = [False])

InlineSDFGs().apply_pass(sdfg, {})
k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
print(f"Applied MapCollapse {k} time(s)")
k = sdfg.apply_transformations_repeated(MapFusion)
for n, g in sdfg.all_nodes_recursive():
    if isinstance(n, dace.nodes.NestedSDFG):
        if isinstance(n, dace.nodes.NestedSDFG):
            k = n.sdfg.apply_transformations_repeated(MapFusion, permissive=True)
            print(f"Applied MapFusion {k} time(s) to NestedSDFG {n.sdfg.name}")
print(f"Applied MapFusion {k} time(s)")
k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
print(f"Applied MapCollapse {k} time(s)")
sdfg.simplify()

sdfg.save("gpu_pipe_stage3.sdfgz", compress=True)

# How many loops?
count_loops(sdfg)
sdfg.validate()
sdfg.instrument = dace.InstrumentationType.Timer

################################################################################
### Numerically validate the SDFG
################################################################################

# Compile the SDFG
compile_sdfg(sdfg, gpu=True, release=release)

sdfg.save("gpu_velocity.sdfgz", compress=True)

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

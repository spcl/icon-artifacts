from pathlib import Path
import dace
import shutil
import os
import math
import ast
import copy
from dace.transformation.interstate import LoopToMap, ContinueToCondition, LoopNormalize
from dace.transformation.dataflow import MapCollapse
from dace.transformation.passes import (
    SymbolPropagation,
    StructToContainerGroups,
    DuplicateConstArrays,
)
from dace.sdfg.state import LoopRegion, ConditionalBlock, ControlFlowRegion
from dace.libraries.standard import CodeLibraryNode
from dace.properties import make_properties, Property
from dace.transformation.passes.to_gpu import ToGPU

use_cache = True
run_benchmark = False
save_steps = False

# Load SDFG
sdfg = dace.SDFG.from_file("velocity.sdfgz")
sdfg.validate()

################################################################################
### Fixing Functions
################################################################################


def make_array_loop_local(sdfg: dace.SDFG, array_name, loop_name):
    """
    Renames an array in the loop, so it's only accessed in the loop. You need to make sure that the array is not accessed outside of the loop (or written before read outside of the loop).
    """
    # Find the loop
    loop = None
    for node, _ in sdfg.all_nodes_recursive():
        if isinstance(node, LoopRegion) and node.label == loop_name:
            loop = node
            break
    assert loop is not None, f"Loop {loop_name} not found"

    # Creat a new array
    array = sdfg.arrays[array_name]
    if isinstance(array, dace.data.Scalar):
        new_name, _ = sdfg.add_scalar(
            f"{array_name}_local",
            dtype=array.dtype,
            storage=array.storage,
            transient=array.transient,
            lifetime=array.lifetime,
            debuginfo=array.debuginfo,
            find_new_name=True,
        )
    else:
        new_name, _ = sdfg.add_array(
            f"{array_name}_local",
            shape=array.shape,
            dtype=array.dtype,
            storage=array.storage,
            location=array.location,
            transient=array.transient,
            strides=array.strides,
            offset=array.offset,
            lifetime=array.lifetime,
            debuginfo=array.debuginfo,
            allow_conflicts=array.allow_conflicts,
            total_size=array.total_size,
            find_new_name=True,
            alignment=array.alignment,
            may_alias=array.may_alias,
        )

    # Replace each occurrence of the array in the loop
    loop.replace(array_name, new_name)
    nodelist = list(loop.nodes())
    while nodelist:
        node = nodelist.pop()
        if isinstance(node, (LoopRegion, ConditionalBlock)):
            nodelist.extend(node.nodes())
            node.replace_meta_accesses({array_name: new_name})


@make_properties
class MaxReduce(CodeLibraryNode):
    code = Property(dtype=str, default="", allow_none=False)

    def __init__(self, name, input_names, output_names, code):
        super().__init__(name=name, input_names=input_names, output_names=output_names)
        self.code = code

    def generate_code(self, inputs, outputs):
        return self.code


def replace_loop_with_max_reduction(sdfg: dace.SDFG, loop_name: str):
    loop_node = None
    for node, state in sdfg.all_nodes_recursive():
        if node.label == loop_name:
            loop_node = node
            break
    assert loop_node is not None
    red_state = sdfg.add_state_before(loop_node)
    red_lib_node = MaxReduce(
        name="max_reduce",
        input_names=["in_arr"],
        output_names=[],
        code="""
        // Max reduce
        // TODO: Implement max reduce
        // End of max reduce
        """,
    )
    red_lib_node.schedule = dace.ScheduleType.GPU_Device
    red_state.add_node(red_lib_node)
    red_state.add_edge(
        red_state.add_read("vcflmax"),
        None,
        red_lib_node,
        "in_arr",
        dace.Memlet("vcflmax"),
    )

    post_state = sdfg.add_state_after(loop_node)
    sdfg.remove_node(loop_node)
    sdfg.add_edge(red_state, post_state, dace.InterstateEdge())


# Replace cpp with cu
def replace_cpp_with_cu(directory):
    directory = Path(directory)  # Convert to Path object
    for file in directory.rglob("*.cpp"):  # Find all .cpp files
        new_name = file.with_suffix(".cu")  # Change the suffix to .cu
        file.rename(new_name)  # Rename the file
        print(f"Renamed: {file} -> {new_name}")
    for file in directory.rglob("*.cc"):
        new_name = file.with_suffix(".cu")  # Change the suffix to .cu
        file.rename(new_name)  # Rename the file
        print(f"Renamed: {file} -> {new_name}")


################################################################################
### Apply Optimizations
################################################################################


# Apply transformations
if Path("gpu_pipe_stage1.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("gpu_pipe_stage1.sdfg")
else:
    # sdfg.apply_transformations_repeated(ContinueToCondition)
    # sdfg.simplify()
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
    ToGPU().apply_pass(sdfg, {})

    for cfg in sdfg.nodes():
      if cfg.label == "FOR_l_568_c_568":
          s = sdfg.add_state_before(cfg, "copy_vcflmax")
          a0 = s.add_access("gpu_vcflmax")
          a1 = s.add_access("vcflmax")
          s.add_edge(a0, None, a1, None, dace.Memlet(expr="gpu_vcflmax"))

    if use_cache:
        sdfg.save("gpu_pipe_stage2.sdfg")

# How many loops?
loops_post = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        loops_post += 1
print(f"Loops remaining: {loops_post}")

sdfg.validate()
sdfg.instrument = dace.InstrumentationType.Timer

################################################################################
### Compile the (optimized) SDFG with alterations
################################################################################

# get build location and dace location
build_loc = sdfg.build_folder
sdfg_name = sdfg.name
dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

# remove the .dacecache folder
shutil.rmtree(build_loc, ignore_errors=True)

# Generate code
try:
    sdfg.compile()
except Exception as e:
    pass

# TODO: Make manual changes to the generated code if necessary

# compile the SDFG
sdfg._regenerate_code = False
sdfg.compile()

# copy main_cpp_file to .dacecache/<name>/src/cpu/
shutil.copy(f"main_gpu.cc", f"{build_loc}/src/cpu/main.cu")

# copy header to .dacecache/<name>/include/
shutil.copy(f"include/serde_velocity.h", f"{build_loc}/include/serde_velocity.h")

# To avoid link issues fastly for CUDA libs and have cuda compiler definition
replace_cpp_with_cu(build_loc)

# compile nvcc <SDFG cpp file> <SDFG cuda file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -Xcompiler=-faligned-new --expt-relaxed-constexpr -std=c++20 -arch=native -O0 -w
exit_code = os.system(
    f"nvcc {build_loc}/src/cpu/{sdfg_name}.cu {build_loc}/src/cuda/{sdfg_name}_cuda.cu {build_loc}/src/cpu/main.cu -I {build_loc}/include -I {dace_include} -Xcompiler=-faligned-new --expt-relaxed-constexpr -std=c++20 -arch=native -O3 -Xcompiler=-O3 -Xcompiler=-fopenmp -lineinfo -w -o {sdfg_name}"
)

# check if compilation was successful
if exit_code != 0:
    print("Compilation failed")
    exit(1)


################################################################################
### Execute and compare .got and .want files
################################################################################

# execute the compiled program
exit_code = os.system(f"./{sdfg_name}")

# check if execution was successful
if exit_code != 0:
    print("Execution failed")
    exit(1)

# Get list of .got and .want files
got_files = [f for f in os.listdir() if f.endswith(".got")]
want_files = [f.replace(".got", ".want") for f in got_files]
assert len(got_files) == len(
    [f for f in os.listdir() if f.endswith(".want")]
), "Number of .got and .want files do not match"

# Compare each .got file with its corresponding .want file
found_diff_all = False
for got, want in zip(got_files, want_files):
    found_diff = False
    with open(got, "r") as got_file, open(want, "r") as want_file:
        got_lines = got_file.readlines()
        want_lines = want_file.readlines()

        if len(got_lines) != len(want_lines):
            print(f"{got} and {want} have different number of lines ❌")
            found_diff = True
            continue

        # lines containing text should be identical, lines containing numbers should be close
        for got_line, want_line in zip(got_lines, want_lines):
            # Are the lines floating point numbers?
            try:
                got_num = float(got_line)
                want_num = float(want_line)
                # TODO: Adjust rel_tol and abs_tol
                if not math.isclose(got_num, want_num, rel_tol=0, abs_tol=1e-8):
                    print(f"{got} and {want} have numerical differences ❌")
                    found_diff = True
                    break

            except ValueError:
                # If not, they should be identical
                if got_line != want_line:
                    print(f"{got} and {want} have different text ❌")
                    found_diff = True
                    break
    if not found_diff:
        print(f"{got} and {want} are identical ✅")
    found_diff_all = found_diff_all or found_diff


if not found_diff_all:
    print("No numerical differences found ✅")
else:
    print("Numerical differences found ❌")


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
os.remove(sdfg_name)

# remove the .got files
for got in got_files:
    os.remove(got)

# remove the .want files
for want in want_files:
    os.remove(want)

# remove the .dacecache folder
# shutil.rmtree(build_loc)

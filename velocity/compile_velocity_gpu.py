from pathlib import Path
import dace
import shutil
import os
import math
import ast
import copy
from dace.codegen.control_flow import ContinueBlock, ControlFlowBlock
from dace.transformation.interstate import LoopToMap, ContinueToCondition, LoopNormalize, ConditionFusion
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

# Load SDFG
sdfg = dace.SDFG.from_file("velocity.sdfgz")
sdfg.validate()

################################################################################
### Optimization Functions
################################################################################


def find_node_by_name(sdfg: dace.SDFG, name: str, skip=0):
    for node, parent in sdfg.all_nodes_recursive():
        if node.label == name:
            if skip > 0:
                skip -= 1
                continue
            return node, parent
    assert False, f"Node {name} not found"


def make_array_loop_local(sdfg: dace.SDFG, array_name, loop_name):
    """
    Renames an array in the loop, so it's only accessed in the loop. You need to make sure that the array is not accessed outside of the loop (or written before read outside of the loop).
    """
    # Find the loop
    loop, _ = find_node_by_name(sdfg, loop_name)

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
class LibNode(CodeLibraryNode):
    code = Property(dtype=str, default="", allow_none=False)

    def __init__(self, name, input_names, output_names, code):
        super().__init__(name=name, input_names=input_names, output_names=output_names)
        self.code = code

    def generate_code(self, inputs, outputs):
        return self.code


def insert_reduction(
    sdfg: dace.SDFG,
    state: dace.SDFGState,
    in_name: str,
    in_size: str,
    out_name: str,
    type: str,
    in_expr: str = None,
    out_expr: str = None,
):
    """
    Adds a reduction node to the state after the given state.
    """
    red_state = sdfg.add_state_after(state)
    red_lib_node = LibNode(
        name="reduce",
        input_names=["in_arr"],
        output_names=["out"],
        code=f"out = reduce_{type}(in_arr, {in_size});",
    )
    red_lib_node.schedule = dace.ScheduleType.GPU_Default
    in_expr = in_expr if in_expr is not None else in_name
    red_state.add_edge(
        red_state.add_read(in_name), None, red_lib_node, "in_arr", dace.Memlet(in_expr)
    )

    if out_expr is None:
      arr_name, arr = red_state.sdfg.add_scalar(
        "out_val", dtype=dace.float64, transient=True, find_new_name=True
      )
      red_state.add_edge(
          red_lib_node, "out", red_state.add_write(arr_name), None, dace.Memlet(arr_name)
      )
      sdfg.add_state_after(red_state, assignments={out_name: f"{arr_name}"})
    else:
      red_state.add_edge(
          red_lib_node, "out", red_state.add_write(out_name), None, dace.Memlet(out_expr)
      )
        
    return red_state


def loop_to_max_reduction(sdfg: dace.SDFG):
    """
    Turns the max loop at the end of the SDFG into a reduction.
    """
    loop_node, _ = find_node_by_name(sdfg, "FOR_l_568_c_568")
    insert_reduction(sdfg, loop_node, "vcflmax", "640", "tmp_call_18", "max")
    sdfg.append_global_code("DACE_EXPORTED double reduce_max(double *d_in, int n);")
    pre_state = sdfg.add_state_before(loop_node)
    post_state = sdfg.add_state_after(loop_node)
    sdfg.remove_node(loop_node)
    sdfg.add_edge(pre_state, post_state, dace.InterstateEdge())


def cfl_clipping_to_reduction(sdfg: dace.SDFG):
    """
    Turns the cfl_clipping scan/sum into a reduction.
    """
    task, parent = find_node_by_name(sdfg, "T_l467_c467")
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)
    cond_block, parent = find_node_by_name(sdfg, "Conditional_l_467_c_467")
    parent.remove_node(cond_block)
    loop, parent = find_node_by_name(sdfg, "FOR_l_465_c_465")
    del parent.in_edges(loop)[0].data.assignments["clip_count"]
    insert_reduction(
        parent,
        loop,
        "cfl_clipping",
        "tmp_struct_symbol_7",
        "clip_count",
        "sum",
        in_expr="cfl_clipping[i_startidx_var_88-1:i_endidx_var_89-1,_for_it_35-1]",
    )
    sdfg.append_global_code("DACE_EXPORTED int reduce_sum(int *d_in, int n);")


def maxvcfl_to_reduction(sdfg: dace.SDFG):
    """
    Turns the maxvcfl max into a reduction.
    """
    task, parent = find_node_by_name(sdfg, "T_l462_c462")
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)
    task, parent = find_node_by_name(sdfg, "T_l474_c474", skip=1)
    assert task.code.as_string == "maxvcfl_out = max(maxvcfl_0_in, tmp_call_8_0_in)"
    task.code.as_string = "maxvcfl_out = tmp_call_8_0_in"
    task.remove_in_connector("maxvcfl_0_in")
    for pred in parent.predecessors(task):
        if pred.label == "maxvcfl":
            parent.remove_node(pred)
    parent.remove_node(parent.successors(task)[0])

    arr_name, arr = parent.sdfg.add_array(
        "maxvcfl_arr",
        shape=["tmp_struct_symbol_7", 91],
        dtype=dace.float64,
        transient=True,
    )
    arr_acc = parent.add_write(arr_name)
    parent.add_edge(
        task,
        "maxvcfl_out",
        arr_acc,
        None,
        dace.Memlet(f"{arr_name}[_for_it_37-1,_for_it_35-1]"),
    )

    loop, parent = find_node_by_name(sdfg, "FOR_l_463_c_463")
    insert_reduction(
        parent, loop, "maxvcfl_arr", "tmp_struct_symbol_7*91", "maxvcfl", "max"
    )
    sdfg.append_global_code("DACE_EXPORTED double reduce_max(double *d_in, int n);")


def tmp_call_13_to_reduction(sdfg: dace.SDFG):
    """
    Turns the tmp_call_13 scan into a reduction.
    """
    loop, parent = find_node_by_name(sdfg, "FOR_l_516_c_516")
    insert_reduction(
        parent,
        loop,
        "levmask",
        "i_endblk_var_87 - i_startblk_var_86",
        "tmp_call_13",
        "scan",
        in_expr="levmask[i_startblk_var_86-1:i_endblk_var_87-1,_for_it_46-1]",
    )
    pre_state = parent.add_state_before(loop)
    post_state = parent.add_state_after(loop)
    parent.remove_node(loop)
    parent.add_edge(pre_state, post_state, dace.InterstateEdge())
    sdfg.append_global_code("DACE_EXPORTED double reduce_scan(int *d_in, int n);")

def levmask_to_reduction(sdfg: dace.SDFG):
    """
    Turns the levmask scan into a reduction.
    """
    loop, parent = find_node_by_name(sdfg, "FOR_l_470_c_470")
    prestate = parent.add_state_before(loop)
    insert_reduction(
        parent,
        prestate,
        "cfl_clipping",
        "i_endidx_var_89 - i_startidx_var_88",
        "levmask",
        "scan",
        in_expr="cfl_clipping[i_startidx_var_88-1:i_endidx_var_89-1,_for_it_35-1]",
        out_expr="levmask[_for_it_22-1,_for_it_35-1]",
    )
    task, parent = find_node_by_name(sdfg, "T_l472_c472")
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)
    sdfg.append_global_code("DACE_EXPORTED double reduce_scan(int *d_in, int n);")



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
    ToGPU().apply_pass(sdfg, {})
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

# Prepend reduction library to .dacecache/<name>/src/cuda/<name>_cuda.cu
with open(f"src/reductions.cu", "r") as file:
    reduction_code = file.read()
with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "r") as file:
    main_cpp_code = file.read()
with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "w") as file:
    file.write(reduction_code + main_cpp_code)

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
    f"nvcc {build_loc}/src/cpu/{sdfg_name}.cu {build_loc}/src/cuda/{sdfg_name}_cuda.cu {build_loc}/src/cpu/main.cu -I {build_loc}/include -I {dace_include} -Xcompiler=-faligned-new --expt-relaxed-constexpr -std=c++20 -arch=sm_80 -O0 -Xcompiler=-O0 -Xcompiler=-fopenmp -lineinfo -w -o {sdfg_name}"
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
    max_rel_diff = 0
    max_abs_diff = 0
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

                abs_diff = abs(got_num - want_num)
                if want_num != 0:
                  max_rel_diff = max(max_rel_diff, abs_diff / abs(want_num))
                max_abs_diff = max(max_abs_diff, abs_diff)

                # TODO: Adjust rel_tol and abs_tol
                if not math.isclose(got_num, want_num, rel_tol=0, abs_tol=1e-12):
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
        print(f"{got} and {want} are OK ✅")
    print(f"  Rel: {max_rel_diff}, Abs: {max_abs_diff}")
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

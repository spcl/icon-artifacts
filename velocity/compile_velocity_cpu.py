from pathlib import Path
import dace
import shutil
import os
import math
from dace.transformation.interstate import LoopToMap, ContinueToCondition
from dace.transformation.passes import SymbolPropagation, StructToContainerGroups
from dace.sdfg.state import LoopRegion, ConditionalBlock

use_cache = True
run_benchmark = False

# Load SDFG
sdfg = dace.SDFG.from_file("velocity.sdfgz")
sdfg.validate()

################################################################################
### Apply Optimizations
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


# How many for loops exist?
loops_prev = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        loops_prev += 1

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
    if use_cache:
        sdfg.save("cpu_pipe_stage1.sdfg")

if Path("cpu_pipe_stage2.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("cpu_pipe_stage2.sdfg")
else:
    sdfg.apply_transformations_repeated(LoopToMap)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
    if use_cache:
        sdfg.save("cpu_pipe_stage2.sdfg")

# How many now?
loops_post = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        loops_post += 1
print(f"Loops before: {loops_prev}, Loops after: {loops_post}")

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
shutil.copy(f"main.cc", f"{build_loc}/src/cpu/main.cc")

# copy header to .dacecache/<name>/include/
shutil.copy(f"include/serde_velocity.h", f"{build_loc}/include/serde_velocity.h")

# compile c++ <SDFG cpp file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -std=c++20 -O0 -ggdb
exit_code = os.system(
    f"c++ {build_loc}/src/cpu/{sdfg_name}.cpp {build_loc}/src/cpu/main.cc -I {build_loc}/include -I {dace_include} -std=c++20 -O0 -ggdb -o {sdfg_name}"
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
                  max_rel_diff = max(max_rel_diff, abs_diff / want_num)
                max_abs_diff = max(max_abs_diff, abs_diff)

                # TODO: Adjust rel_tol and abs_tol
                if not math.isclose(got_num, want_num, rel_tol=0, abs_tol=0):
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
        print(f"CPU,{time}")

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
shutil.rmtree(build_loc)

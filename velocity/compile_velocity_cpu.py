import copy
from pathlib import Path
import subprocess
import dace
import shutil
import os
import math
from dace.transformation.passes.duplicate_const_arrays import DuplicateConstArrays
from dace.transformation.passes.struct_to_container_group import StructToContainerGroups
from dace.transformation.interstate import LoopToMap
from dace.transformation.interstate import LoopNormalize
from dace.transformation.interstate import ContinueToCondition
from dace.transformation.passes import SymbolPropagation
from dace.sdfg.state import LoopRegion, ContinueBlock, ConditionalBlock
from dace.sdfg.utils import inline_control_flow_regions

# Load SDFG
sdfg = dace.SDFG.from_file("velocity.sdfg")
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
    assert loop is not None
    # Creat a new array
    assert array_name in sdfg.arrays
    array = sdfg.arrays[array_name]
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


# How many for loops exist?
loops_prev = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        loops_prev += 1

# Apply transformations

if Path("s2cg.sdfg").exists():
    sdfg = dace.SDFG.from_file("s2cg.sdfg")
else:
  StructToContainerGroups(
      save_steps=False,
      verbose=False,
      simplify=False,
      interface_with_struct_copy=True,
      interface_to_gpu=False,
  ).apply_pass(sdfg, {})
  sdfg.save("s2cg.sdfg")

if Path("dca.sdfg").exists():
    sdfg = dace.SDFG.from_file("dca.sdfg")
else:
  sdfg.simplify()
  sdfg.apply_transformations_repeated(ContinueToCondition)
  sdfg.simplify()
  sdfg.apply_transformations_repeated(LoopNormalize)
  sdfg.simplify()
  SymbolPropagation().apply_pass(sdfg, {})
  sdfg.simplify()

  # XXX: Order is important!
  make_array_loop_local(sdfg, "difcoef", "FOR_l_505_c_505")
  make_array_loop_local(sdfg, "_if_cond_27", "FOR_l_553_c_553")
  make_array_loop_local(sdfg, "_if_cond_23", "FOR_l_505_c_505")
  make_array_loop_local(sdfg, "_if_cond_23", "FOR_l_503_c_503")

  sdfg.save("dca.sdfg")

sdfg.simplify()

sdfg.apply_transformations_repeated(LoopToMap)
# sdfg.apply_transformations_repeated(LoopToMap)

# How many now?
loops_post = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        print(node)
        loops_post += 1
print(f"Loops before: {loops_prev}, Loops after: {loops_post}")

sdfg.validate()

################################################################################
### Compile the (optimized) SDFG with alterations
################################################################################

# get build location and dace location
build_loc = sdfg.build_folder
sdfg_name = sdfg.name
dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

# Generate code
sdfg.instrument = dace.InstrumentationType.Timer
try:
    sdfg.compile()
except Exception as e:
    pass

# compile the SDFG
sdfg._regenerate_code = False
sdfg.compile()

# copy main_cpp_file to .dacecache/<name>/src/cpu/
shutil.copy(f"main.cc", f"{build_loc}/src/cpu/main.cc")

# copy header to .dacecache/<name>/include/
shutil.copy(f"serde_velocity.h", f"{build_loc}/include/serde_velocity.h")

# compile c++ <SDFG cpp file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -std=c++17 -O0 -ggdb
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

# Compare each .got file with its corresponding .want file
found_diff_all = False
for got, want in zip(got_files, want_files):
    found_diff = False
    with open(got, "r") as got_file, open(want, "r") as want_file:
        got_lines = got_file.readlines()
        want_lines = want_file.readlines()

        if len(got_lines) != len(want_lines):
            print(f"{got} and {want} have different number of lines")
            found_diff = True
            continue

        # lines containing text should be identical, lines containing numbers should be close
        for got_line, want_line in zip(got_lines, want_lines):
            # Are the lines floating point numbers?
            try:
                got_num = float(got_line)
                want_num = float(want_line)
                # TODO: Adjust rel_tol and abs_tol
                if not math.isclose(got_num, want_num, rel_tol=0, abs_tol=0):
                    print(f"{got} and {want} have numerical differences")
                    found_diff = True
                    break

            except ValueError:
                # If not, they should be identical
                if got_line != want_line:
                    print(f"{got} and {want} have different text")
                    found_diff = True
                    break
    if not found_diff:
        print(f"{got} and {want} are identical")
    found_diff_all = found_diff_all or found_diff


if not found_diff_all:
    print("No numerical differences found")
else:
    exit(1)


################################################################################
### Measure performance
################################################################################

# # Warmup
# for i in range(10):
#     os.system(f"./{sdfg_name}")

# # Measure
# times = []
# for i in range(10):
#     sdfg.clear_instrumentation_reports()
#     os.system(f"./{sdfg_name}")
#     report = sdfg.get_latest_report()
#     assert report.events[-1].name == f"SDFG {sdfg.name}"
#     time = report.events[-1].duration # in us
#     times.append(time)

# for time in times:
#     print(f"CPU,{time}")

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

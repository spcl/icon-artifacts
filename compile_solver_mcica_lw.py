import dace
import shutil
import os
import math

from dace.sdfg.state import LoopRegion
from dace.transformation.interstate import LoopToMap
from dace.transformation.passes.struct_to_container_group import StructToContainerGroups
from dace.transformation.interstate import LoopNormalize
from dace.transformation.passes import SymbolPropagation

# Mapping of SDFG -> headerfile
header_dict = {"solver_mcica_lw": "serdesl.h"}

# Mapping of SDFG -> main file
main_dict = {"solver_mcica_lw": "main_solver_mcica_lw.cc"}

# Load SDFG
path = "sdfgs/solver_mcica_lw_simplified_dbg22.sdfgz"
sdfg = dace.SDFG.from_file(path)
sdfg.validate()

################################################################################
### Apply Optimizations
################################################################################

# How many for loops exist?
loops_prev = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        loops_prev += 1

# Apply pipeline
StructToContainerGroups().apply_pass(sdfg, {})
print("StructToContainerGroups applied")

sdfg.apply_transformations_repeated(LoopNormalize)
print("LoopNormalize applied")

SymbolPropagation().apply_pass(sdfg, {})
print("SymbolPropagation applied")

sdfg.simplify()
print("SDFG simplified")

sdfg.apply_transformations_repeated(LoopToMap)
print("LoopToMap applied")

# How many now?
loops_post = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        loops_post += 1
print(f"Loops before: {loops_prev}, Loops after: {loops_post}")

# Validate the SDFG
sdfg.validate()

# Turn all maps to CPU_Multicore
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, dace.nodes.MapEntry):
        node.map.schedule = dace.ScheduleType.CPU_Multicore


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

# Replace int_ceil with int_floor
with open(f"{sdfg.build_folder}/src/cpu/{sdfg_name}.cpp", "r") as file:
    lines = file.readlines()
with open(f"{sdfg.build_folder}/src/cpu/{sdfg_name}.cpp", "w") as file:
    for line in lines:
        file.write(line.replace("int_ceil", "int_floor"))

# Prepend tmp_arg_11 = (140 * nlev_var_514); to tmp_arg_3_1 = new double DACE_ALIGN(64)[tmp_arg_11];
with open(f"{sdfg.build_folder}/src/cpu/{sdfg_name}.cpp", "r") as file:
    lines = file.readlines()
with open(f"{sdfg.build_folder}/src/cpu/{sdfg_name}.cpp", "w") as file:
    for line in lines:
        if "tmp_arg_3_1 = new double DACE_ALIGN(64)[tmp_arg_11];" in line:
            file.write("tmp_arg_11 = (140 * nlev_var_514);\n")
        file.write(line)

# compile the SDFG
sdfg._regenerate_code = False
sdfg.compile()

# copy main_cpp_file to .dacecache/<name>/src/cpu/
main_name = main_dict[sdfg_name]
shutil.copy(f"main_cpp_files/{main_name}", f"{build_loc}/src/cpu/{main_name}")

# change the line "constexpr char ROOT[] ="
# to contain "<path to this script>/inputs/<name>/"
input_folder = os.path.dirname(os.path.realpath(__file__)) + "/inputs"
with open(f"{build_loc}/src/cpu/{main_name}", "r") as file:
    lines = file.readlines()
with open(f"{build_loc}/src/cpu/{main_name}", "w") as file:
    for line in lines:
        if line.startswith("constexpr char ROOT[] ="):
            file.write(f'constexpr char ROOT[] = "{input_folder}/{sdfg_name}/";\n')
        else:
            file.write(line)

# copy header to .dacecache/<name>/include/
header_name = header_dict[sdfg_name]
shutil.copy(f"headers/{header_name}", f"{build_loc}/include/{header_name}")

# compile c++ <SDFG cpp file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -std=c++17 -O0 -ggdb
exit_code = os.system(
    f"c++ {build_loc}/src/cpu/{sdfg_name}.cpp {build_loc}/src/cpu/{main_name} -I {build_loc}/include -I {dace_include} -std=c++17 -O0 -ggdb -o {sdfg_name}"
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
    time = report.events[-1].duration # in us
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
shutil.rmtree(build_loc)

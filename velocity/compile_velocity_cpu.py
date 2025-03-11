import copy
from pathlib import Path
import subprocess
import dace
import shutil
import os
from dace.transformation.passes.duplicate_const_arrays import DuplicateConstArrays
from dace.transformation.passes.struct_to_container_group import StructToContainerGroups
from dace.transformation.interstate import LoopToMap

header_dict = {
    "velocity_tendencies": "serde_velocity.h",
}

main_dict = {
    "velocity_tendencies": "main.cc",
}

path = "velocity.sdfgz"

save_steps = True

# Load SDFG
sdfg = dace.SDFG.from_file(path)

StructToContainerGroups(save_steps=False, verbose=False, simplify=False, interface_with_struct_copy=True,
                        interface_to_gpu=False).apply_pass(sdfg, {})
if save_steps:
    sdfg.save("flat_velocity.sdfgz", compress=True)
sdfg.validate()
sdfg.compile()

build_loc = sdfg.build_folder
sdfg_name = sdfg.name
dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

# copy main_cpp_file to .dacecache/<name>/src/cpu/
main_name = main_dict[sdfg_name]
shutil.copy(f"{main_name}", f"{build_loc}/src/cpu/{main_name}")

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
shutil.copy(f"{header_name}", f"{build_loc}/include/{header_name}")

# compile c++ <SDFG cpp file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -std=c++17 -O0 -ggdb
# But CUDA version this time


os.system(
    f"c++ {build_loc}/src/cpu/{sdfg_name}.cpp \
{build_loc}/src/cpu/{main_name} -I {build_loc}/include -I {dace_include} \
-faligned-new -std=c++20 -O0 -o {sdfg_name}"
)
run = True
if run:
    os.system(
        f"./{sdfg_name}"
    )

    got_files = [f for f in os.listdir() if f.endswith(".got")]

    for got_file in got_files:
        want_file = got_file.replace(".got", ".want")

        if os.path.isfile(want_file):
            print(f"Comparing {got_file} with {want_file}...")
            result = subprocess.run(["diff", got_file, want_file], capture_output=True, text=True)

            if result.stdout:  # If there's a difference
                print("Verification failed")
                with open(got_file + ".out", "w") as f:
                    f.write(result.stdout)
                if result.stderr:  # If there's an error
                    with open(got_file + ".err", "w") as f:
                        f.write(result.stderr)
            else:
                print("All good")
        else:
            print(f"Warning: No matching .want file for {got_file}")

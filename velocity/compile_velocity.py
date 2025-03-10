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


################################################################################
### Apply Optimizations
################################################################################


if Path("velocity_to_gpu.sdfgz").exists():
    sdfg = sdfg.from_file("to_gpu_velocity.sdfgz")
else:
    StructToContainerGroups(save_steps=False, verbose=False, simplify=False, interface_with_struct_copy=True, interface_to_gpu=True).apply_pass(sdfg, {})
    if save_steps:
        sdfg.save("flat_velocity.sdfgz", compress=True)
    sdfg.apply_transformations_repeated(LoopToMap, validate=False)
    if save_steps:
        sdfg.save(f"map_velocity.sdfgz", compress=True)
    sdfg.validate()
    sdfg.apply_gpu_transformations(validate=False, simplify=False, host_data=[v for v, k in sdfg.arrays.items() if isinstance(k, dace.data.Array)],
                                   dont_copy_structs=True)
    if save_steps:
        sdfg.save("to_gpu_velocity.sdfgz", compress=True)

# The task lists are the tasklets that need to be wrapped in a single-state GPU map even after applying array duplication
["T_l467_c467", "T_l472_c472"]
DuplicateConstArrays().apply_pass(sdfg, {"wrap_list": ["T_l467_c467", "T_l472_c472"]})
if save_steps:
    sdfg.save("arrays_duplicated_velocity.sdfgz", compress=True)


# Does what the title says
def if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(sdfg : dace.SDFG, labels):
    for state in sdfg.states():
        for node in state.nodes():
            if (state.label, node.label) in labels:
                if isinstance(node, dace.nodes.MapEntry):
                    nodes = list(state.all_nodes_between(node, state.exit_node(node)))
                    in_data = set()
                    out_data = set()
                    hasviews = False
                    for oe in state.out_edges(node):
                        if isinstance(oe.dst, dace.nodes.AccessNode) and isinstance(sdfg.arrays[oe.dst.data], dace.data.View):
                            hasviews = True
                    if not hasviews:
                        continue

                    for oe in state.out_edges(node):
                        in_data.add(oe.data.data)
                    for ie in state.in_edges(state.exit_node(node)):
                        out_data.add(ie.data.data)

                    nested_sdfg = dace.SDFG("nested")
                    nested_state = nested_sdfg.add_state("nested_state")

                    for id in set.union(in_data, out_data):
                        desc = copy.deepcopy(sdfg.arrays[id])
                        if not isinstance(desc, dace.data.View):
                            desc.transient = False
                        nested_sdfg.add_datadesc(id, desc)

                    node_map = dict()
                    for _n in nodes:
                        if _n != node and _n != state.exit_node(node):
                            if _n not in node_map:
                                __n = copy.deepcopy(_n)
                                nested_state.add_node(__n)
                                node_map[_n] = __n

                    for edge in state.out_edges(node):
                        nnode = node_map[edge.dst]
                        an = nested_state.add_access(edge.data.data)
                        nested_state.add_edge(an, None, nnode, edge.dst_conn, copy.deepcopy(edge.data))

                    for edge in state.in_edges(state.exit_node(node)):
                        nnode = node_map[edge.src]
                        an = nested_state.add_access(edge.data.data)
                        nested_state.add_edge(nnode, edge.src_conn, an, None, copy.deepcopy(edge.data))

                    for e in state.all_edges(*nodes):
                        if e.src != node and e.dst != state.exit_node(node):
                            nsrc = node_map[e.src]
                            ndst = node_map[e.dst]
                            nested_state.add_edge(nsrc, e.src_conn, ndst, e.dst_conn, copy.deepcopy(e.data))
                            if isinstance(nsrc, dace.nodes.AccessNode):
                                if nsrc.data not in nested_sdfg.arrays:
                                    nested_sdfg.add_datadesc(nsrc.data, copy.deepcopy(sdfg.arrays[nsrc.data]))
                            if isinstance(ndst, dace.nodes.AccessNode):
                                if ndst.data not in nested_sdfg.arrays:
                                    nested_sdfg.add_datadesc(ndst.data, copy.deepcopy(sdfg.arrays[ndst.data]))

                    nsdfg = state.add_nested_sdfg(nested_sdfg, state, in_data, out_data)
                    edges_to_add = set()
                    for oe in state.out_edges(node):
                        edges_to_add.add((oe.src, oe.src_conn, nsdfg, oe.data.data, dace.memlet.Memlet(expr=oe.data.data)))
                    for ie in state.in_edges(state.exit_node(node)):
                        edges_to_add.add((nsdfg, ie.data.data, ie.dst, ie.dst_conn, dace.memlet.Memlet(expr=ie.data.data)))

                    for e in edges_to_add:
                        state.add_edge(*e)
                    for n in nodes:
                        state.remove_node(n)
            if isinstance(node, dace.nodes.NestedSDFG):
                if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(node.sdfg, labels)
            if isinstance(node, dace.nodes.MapEntry):
                pass

# Set default map schedules to GPU device on top-level SDFG
def set_default_map_to_gpu(sdfg):
    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                pass
            if isinstance(n, dace.nodes.MapEntry):
                if n.map.schedule == dace.ScheduleType.Default:
                    n.map.schedule = dace.ScheduleType.GPU_Device

# Pass levmask as an argument if it is a symbol in the SDFG but not passed as an array
def pass_levmask_as_array_not_as_symbol(rootsdfg, sdfg: dace.SDFG, _n: dace.nodes.Node, levmask):
    has_levmask = False
    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                pass_levmask_as_array_not_as_symbol(rootsdfg, n.sdfg, n, levmask)
        for n in s.nodes():
            if isinstance(n, dace.nodes.AccessNode):
                if n.data == "levmask":
                    has_levmask = True
        for e in s.edges():
            if isinstance(e.data, dace.memlet.Memlet):
                if e.data.data == "levmask":
                    has_levmask = True

    if has_levmask:
        assert "levmask" in sdfg.arrays
    if not has_levmask:
        if ("levmask" in sdfg.arrays):
            sdfg.remove_data("levmask")
        if ("levmask" in sdfg.symbols):
            assert sdfg != rootsdfg
            arr =  copy.deepcopy(rootsdfg.arrays["levmask"])
            arr.transient = False
            sdfg.remove_symbol("levmask")
            sdfg.add_datadesc("levmask", arr)
            an = sdfg.parent.add_access("levmask")
            sdfg.parent.add_edge(an, None, _n, "levmask", dace.memlet.Memlet(expr="levmask"))
            _n.add_in_connector("levmask")
            sdfg.save("levmask_passed.sdfgz", compress=True)

def set_scalar_storage_from_gpu_global_to_register(sdfg: dace.SDFG):
    for arr_name, arr in sdfg.arrays.items():
        if isinstance(arr, dace.data.Scalar):
            if arr.storage == dace.dtypes.StorageType.GPU_Global:
                arr.storage = dace.dtypes.StorageType.Register

# Also iterates to nested SDFGs if scope is None and storage default, put to GPU global
def set_top_level_default_storage_to_gpu_global(sdfg):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                set_top_level_default_storage_to_gpu_global(n.sdfg)
            if isinstance(n, dace.nodes.AccessNode):
                arr = sdfg.arrays[n.data]
                if arr.storage == dace.dtypes.StorageType.Default and state.scope_dict()[n] is None:
                    arr.storage = dace.dtypes.StorageType.GPU_Global

# Pad access node between map and view
def pad_access_node_between_map_and_view(sdfg):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                pad_access_node_between_map_and_view(n.sdfg)
            if isinstance(n, dace.nodes.AccessNode) and isinstance(sdfg.arrays[n.data], dace.data.View):
                assert state.in_degree(n) == 1
                for ie in state.in_edges(n):
                    if isinstance(ie.src, dace.nodes.MapEntry):
                        d = ie.data.data
                        an = state.add_access(d)
                        state.add_edge(an, None, n, "views", copy.deepcopy(ie.data))
                        state.add_edge(ie.src, ie.src_conn, an, None, dace.memlet.Memlet(expr=d))
                        state.remove_edge(ie)

# Apply velocity tendencies specific "fix" transformations
if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(sdfg,labels=[ ("single_state_body", "single_state_body_map"),
                ("single_state_body_1", "single_state_body_map"),
                ("single_state_body_0","single_state_body_map")])
set_default_map_to_gpu(sdfg)
pass_levmask_as_array_not_as_symbol(sdfg, sdfg, None, sdfg.arrays["levmask"])
set_scalar_storage_from_gpu_global_to_register(sdfg)

# Prob not needed anymore
# set_top_level_default_storage_to_gpu_global(sdfg)
# pad_access_node_between_map_and_view(sdfg)

if save_steps:
    sdfg.save("velocity_fixed.sdfgz", compress=True)
sdfg.validate()

try:
    sdfg.compile(validate=False)
except Exception as e:
    print("Code is still not compiling!")
    raise e

sdfg.simplify(validate=True)
if save_steps:
    sdfg.save("velocity_final.sdfgz", compress=True)

################################################################################
### Compile the (optimized) SDFG with alterations
################################################################################

# compile the SDFG
sdfg.compile(validate=True)

# get build location and dace location
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
os.system(
    f"c++ {build_loc}/src/cpu/{sdfg_name}.cpp {build_loc}/src/cpu/{main_name} -I {build_loc}/include -I {dace_include} -faligned-new -std=c++20 -O0 -ggdb -o {sdfg_name}"
)
os.system(
    f"./{sdfg_name}"
)

got_files = [f for f in os.listdir() if f.endswith(".got")]

for got_file in got_files:
    want_file = got_file.replace(".got", ".want")

    if os.path.isfile(want_file):
        print(f"Comparing {got_file} with {want_file}...")
        result = subprocess.run(["diff", got_file, want_file])
        if result.stdout:
            with open(got_file + ".out", "w") as f:
                f.write(result.stdout)
        if result.stderr:
            print(f"Error: {result.stderr}")  # Print any errors
            with open(got_file + ".err", "w") as f:
                f.write(result.stderr)
    else:
        print(f"Warning: No matching .want file for {got_file}")

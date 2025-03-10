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


if Path("to_gpu_velocity.sdfgz").exists():
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

for arr_name, arr in sdfg.arrays.items():
    if "gpu_" + arr_name in sdfg.arrays:
        arr.storage = dace.dtypes.StorageType.CPU_Heap

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
def pass_name_as_array_not_as_symbol(rootsdfg, sdfg: dace.SDFG, nested_sdfg_node: dace.nodes.Node, name: str):
    has_name = False
    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                pass_name_as_array_not_as_symbol(rootsdfg, n.sdfg, n, name)
        for n in s.nodes():
            if isinstance(n, dace.nodes.AccessNode):
                if n.data == name:
                    has_name = True
        for e in s.edges():
            if isinstance(e.data, dace.memlet.Memlet):
                if e.data.data == name:
                    has_name = True

    if has_name:
        assert name in sdfg.arrays
    if not has_name:
        # If does not have the name but is defined as a symbol
        # Then it is sued on interstate edge prob and need to pass it
        if (name in sdfg.arrays):
            sdfg.remove_data(name)
        if (name in sdfg.symbols):
            assert sdfg != rootsdfg
            arr =  copy.deepcopy(rootsdfg.arrays[name])
            arr.transient = False
            sdfg.remove_symbol(name)
            sdfg.add_datadesc(name, arr)
            an = sdfg.parent.add_access(name)
            #sdfg.parent.add_edge(an, None, _n, name, dace.memlet.Memlet(expr=name))
            entry_nodes = []
            enode = nested_sdfg_node
            while enode is not None:
                entry_nodes.append(enode)
                enode = sdfg.parent.entry_node(enode)

            entry_chain = list(reversed(entry_nodes))

            sdfg.parent.add_edge(an, None, entry_chain[0], f"IN_{name}", dace.memlet.Memlet(expr=name))
            entry_chain[0].add_in_connector(f"IN_{name}")

            for i in range(len(entry_chain) - 2):
                sdfg.parent.add_edge(entry_chain[i], f"OUT_{name}", entry_chain[i + 1], f"IN_{name}", dace.memlet.Memlet(expr=name))
                entry_chain[i].add_out_connector(f"OUT_{name}")
                entry_chain[i+1].add_in_connector(f"IN_{name}")

            # Last node is the nested SDFG
            sdfg.parent.add_edge(entry_chain[-2], f"OUT_{name}", entry_chain[-1], f"{name}", dace.memlet.Memlet(expr=name))
            entry_chain[-2].add_out_connector(f"OUT_{name}")
            entry_chain[-1].add_in_connector(f"{name}")

            if save_steps:
                sdfg.save(f"{name}_passed.sdfgz", compress=True)

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

def rename_symbol_connector(sdfg: dace.SDFG, name: str):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                rename_symbol_connector(n.sdfg, name)
            # If AccessNode -> MapEntry, where the data is scalar and is used to create a symbol
            # Then change the in connector name and change all occurences within the area
            if isinstance(n, dace.nodes.AccessNode):
                for oe in state.out_edges(n):
                    if (isinstance(oe.dst, dace.nodes.MapEntry) and
                        name in oe.dst.in_connectors and n.data == name and
                        isinstance(sdfg.arrays[oe.data.data], dace.data.Scalar)):
                        oe.dst.remove_in_connector(name)
                        oe.dst.add_in_connector("__" + name)
                        oe.dst_conn = "__" + name

                        # If state.replace does not work, change this
                        for _n in list(state.all_nodes_between(oe.dst, state.exit_node(oe.dst))) + [oe.dst, state.exit_node(oe.dst)]:
                            if isinstance(_n, dace.nodes.MapEntry):
                                new_params = ["__" + name if p == name else p for p in _n.map.params]
                                new_subsets = [(b.subs(name, "__" + name) if isinstance(b, dace.symbolic.SymExpr) else b,
                                                e.subs(name, "__" + name) if isinstance(e, dace.symbolic.SymExpr) else e,
                                                s.subs(name, "__" + name) if isinstance(s, dace.symbolic.SymExpr) else s)
                                               for (b,e,s) in _n.map.range]
                                _n.map.params = new_params
                                _n.map.range = dace.subsets.Range(new_subsets)
                            if isinstance(_n, dace.nodes.AccessNode) and _n.data == name:
                                _n.data = "__" + name

                        #for _e in list(*state.all_nodes_between(oe.dst, state.exit_node(oe.dst))):
                        # If it used in interstate edges it will crash, implement it here.

                        if save_steps:
                            sdfg.save("reconnectored_velocity.sdfgz", compress=True)


def set_view_lifetime_to_scope(sdfg: dace.SDFG):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                set_view_lifetime_to_scope(n.sdfg)
    for arr in sdfg.arrays.values():
        if isinstance(arr, dace.data.View):
            arr.lifetime = dace.dtypes.AllocationLifetime.Scope

# Apply velocity tendencies specific "fix" transformations
if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(sdfg,labels=[ ("single_state_body", "single_state_body_map"),
                ("single_state_body_1", "single_state_body_map"),
                ("single_state_body_0","single_state_body_map")])
set_default_map_to_gpu(sdfg)
pass_name_as_array_not_as_symbol(sdfg, sdfg, None, "levmask")
set_scalar_storage_from_gpu_global_to_register(sdfg)
rename_symbol_connector(sdfg, "nflatlev_jg")
set_view_lifetime_to_scope(sdfg)

# Prob not needed anymore
# set_top_level_default_storage_to_gpu_global(sdfg)
# pad_access_node_between_map_and_view(sdfg)

if save_steps:
    sdfg.save("velocity_fixed.sdfgz", compress=True)
sdfg.validate()

try:
    sdfg.compile(validate=True)
except Exception as e:
    print("Code is still not compiling!")
    raise e

# Simplifying makes it invalid again...
#sdfg.simplify(validate=True)
#if save_steps:
#    sdfg.save("velocity_final.sdfgz", compress=True)

################################################################################
### Compile the (optimized) SDFG with alterations
################################################################################

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
# But CUDA version this time

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

# To avoid link issues fastly for CUDA libs and have cuda compiler definition
replace_cpp_with_cu(build_loc)

os.system(
    f"nvcc {build_loc}/src/cpu/{sdfg_name}.cu {build_loc}/src/cuda/{sdfg_name}_cuda.cu \
{build_loc}/src/cpu/{main_name.replace(".cc", ".cu")} -I {build_loc}/include -I {dace_include} -Xcompiler=-faligned-new -std=c++20 -o {sdfg_name}"
)
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

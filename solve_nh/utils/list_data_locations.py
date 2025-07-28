from pathlib import Path
import re

import sympy
import dace
from dace.sdfg import is_devicelevel_gpu
import copy

path = Path(__file__).parent.parent

sdfg_paths = {
    path / "codegen" / "gpu_solve_nh_corrector_post_stage3.sdfgz",
    path / "codegen" / "gpu_solve_nh_corrector_pre_stage3.sdfgz",
    path / "codegen" / "gpu_solve_nh_predictor_pre_stage3.sdfgz",
    path / "codegen" / "gpu_solve_nh_predictor_post_stage3.sdfgz",
}

report_paths = {
    path / "gpu_solve_nh_corrector_post_stage3_data_report.txt",
    path / "gpu_solve_nh_corrector_pre_stage3_data_report.txt",
    path / "gpu_solve_nh_predictor_pre_stage3_data_report.txt",
    path / "gpu_solve_nh_predictor_post_stage3_data_report.txt",
}

def _demangle_name(name: str) -> str:
    lname = copy.deepcopy(name)
    if lname.startswith("gpu_"):
        lname = lname[4:]
    nname = ""
    if lname.startswith("__CG"):
        tokens = re.split(r'__CG_|__CA_|__m_', lname)
        for token in tokens:
            if token != "_" and token != "" and token != "CG" and token != "m" and token != "CA":
                nname += token + "->"
    if nname.endswith("->"):
        nname = nname[:-2]
    if nname == "":
        nname = lname
    return nname

def list_data_locations():
    global_gpu_set = set()
    global_cpu_set = set()
    global_cpu_gpu_intersection = set()
    for sdfg_path, report_path in zip(sdfg_paths, report_paths):
        with open(report_path, 'w') as report_file:
            report_file.write(f"Data locations for {sdfg_path.name}:\n")
            gpu_set = set()
            cpu_set = set()
            cpu_gpu_intersection = set()
            sdfg = dace.SDFG.from_file(sdfg_path)
            for n,g in sdfg.all_nodes_recursive():
                node = n
                state = g
                if isinstance(node, dace.nodes.MapEntry):
                    for ie in state.in_edges(node):
                        if ie.data is not None:
                            data_name = ie.data.data
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Array):
                                if sdfg.arrays[data_name].storage == dace.StorageType.GPU_Global:
                                    gpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.CPU_Heap:
                                    cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Default:
                                    is_gpu = is_devicelevel_gpu(state.sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Register:
                                    is_gpu = is_devicelevel_gpu(state.sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Scalar) and sdfg.arrays[data_name].transient is False:
                                cpu_set.add(data_name)

                if isinstance(node, dace.nodes.MapExit):
                    for oe in state.out_edges(node):
                        if oe.data is not None:
                            data_name = oe.data.data
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Array):
                                if sdfg.arrays[data_name].storage == dace.StorageType.GPU_Global:
                                    gpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.CPU_Heap:
                                    cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Default:
                                    is_gpu = is_devicelevel_gpu(sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Register:
                                    is_gpu = is_devicelevel_gpu(sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Scalar) and sdfg.arrays[data_name].transient is False:
                                cpu_set.add(data_name)

                if isinstance(node, dace.nodes.Tasklet) and "velocity_tendencies" in node.label:
                    # This is a special case where we have a tasklet that computes velocity tendencies
                    # and it uses some arrays that are not directly connected to the map.
                    for e in state.in_edges(node):
                        if e.data is not None:
                            data_name = e.data.data
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Array) and sdfg.arrays[data_name].transient is False:
                                if sdfg.arrays[data_name].storage == dace.StorageType.GPU_Global:
                                    gpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.CPU_Heap:
                                    cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Default:
                                    is_gpu = is_devicelevel_gpu(sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Register:
                                    is_gpu = is_devicelevel_gpu(sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Scalar) and sdfg.arrays[data_name].transient is False:
                                cpu_set.add(data_name)
                    for e in state.out_edges(node):
                        if e.data is not None:
                            data_name = e.data.data
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Array):
                                if sdfg.arrays[data_name].storage == dace.StorageType.GPU_Global:
                                    gpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.CPU_Heap:
                                    cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Default:
                                    is_gpu = is_devicelevel_gpu(sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                                if sdfg.arrays[data_name].storage == dace.StorageType.Register:
                                    is_gpu = is_devicelevel_gpu(sdfg, state, node, False)
                                    if is_gpu:
                                        gpu_set.add(data_name)
                                    else:
                                        cpu_set.add(data_name)
                            if data_name in sdfg.arrays and isinstance(sdfg.arrays[data_name], dace.data.Scalar) and sdfg.arrays[data_name].transient is False:
                                cpu_set.add(data_name)

            # Collect all data from interstate edges (to nsdfgs passing should be already ok - since we do it for only top leve
            # all of the data should be CPU)
            for e in sdfg.all_interstate_edges():
                for k, v in e.data.assignments.items():
                    k_str = str(k)
                    v_str = v.as_string if isinstance(v, dace.properties.CodeBlock) else str(v)
                    def _get_all_symbols(expr):
                        symbols = {s for s in expr.atoms(sympy.Symbol)}
                        functions = {f.func for f in expr.atoms(sympy.Function)}
                        return symbols.union(functions)
                    assert k_str not in sdfg.arrays, f"Expected assignment key to be an array name, got {k_str}."
                    #print(k,v)
                    #print(_get_all_symbols(dace.symbolic.SymExpr(v_str)))
                    for sym_v in _get_all_symbols(dace.symbolic.SymExpr(v_str)):
                        sym_v_str = str(sym_v)
                        if sym_v_str in sdfg.arrays:
                            assert not sym_v_str.startswith("gpu_")
                            if sym_v_str.startswith("__CG"):
                                #print(sym_v_str)
                                cpu_set.add(sym_v_str)
                                if sym_v_str in gpu_set:
                                    cpu_gpu_intersection.add(sym_v_str)



            cpu_gpu_intersection = gpu_set.intersection(cpu_set)
            report_file.write("Data needed only on GPU (Pass to GPU):\n")
            for data in gpu_set - cpu_gpu_intersection:
                report_file.write(f"  {data}: {_demangle_name(data)}\n")
            report_file.write("Data needed only on CPU (Pass to CPU):\n")
            for data in cpu_set - cpu_gpu_intersection:
                report_file.write(f"  {data}: {_demangle_name(data)}\n")
            report_file.write("Data needed both on CPU and GPU (Pass to CPU):\n")
            if not (cpu_set - cpu_gpu_intersection):
                report_file.write("  (No data needed on CPU.)\n")
            for data in cpu_gpu_intersection:
                report_file.write(f"  {data}: {_demangle_name(data)}\n")
            if not cpu_gpu_intersection:
                report_file.write("  (No data needed both on CPU and GPU.)\n")
            global_gpu_set.update(gpu_set)
            global_cpu_set.update(cpu_set)
            global_cpu_gpu_intersection.update(cpu_gpu_intersection)

    with open(path / "data_locations_combined.txt", 'w') as global_report_file:
        global_report_file.write("Combined data locations:\n")
        global_report_file.write("Data needed only on GPU (Pass to GPU):\n")
        for data in global_gpu_set - global_cpu_gpu_intersection:
            global_report_file.write(f"  {data}: {_demangle_name(data)}\n")
        global_report_file.write("Data needed only on CPU (Pass to CPU):\n")
        for data in global_cpu_set - global_cpu_gpu_intersection:
            global_report_file.write(f"  {data}: {_demangle_name(data)}\n")
        if not (global_cpu_set - global_cpu_gpu_intersection):
            global_report_file.write("  (No data needed on CPU.)\n")
        global_report_file.write("Data needed both on CPU and GPU (Pass to CPU):\n")
        for data in global_cpu_gpu_intersection:
            global_report_file.write(f"  {data}: {_demangle_name(data)}\n")
        if not global_cpu_gpu_intersection:
            global_report_file.write("  (No data needed both on CPU and GPU.)\n")

def list_scalar_locations():
    with open("combined_non_transient_scalars.txt", 'w') as combined_report_file:
        combined_report_file.write("Scalar locations:\n")
        s = set()
        for sdfg_path, report_path in zip(sdfg_paths, report_paths):
            with open(report_path, 'w') as report_file:
                scalars = {arr_name for arr_name, desc in dace.SDFG.from_file(sdfg_path).arrays.items() if isinstance(desc, dace.data.Scalar) and desc.transient is False}
                for scalar_name in scalars:
                    report_file.write(f"{scalar_name}: {_demangle_name(scalar_name)}\n")
                    s.add((scalar_name, _demangle_name(scalar_name)))
        for scalar_name, demangled_name in sorted(s):
            combined_report_file.write(f"{scalar_name}: {demangled_name}\n")


if __name__ == "__main__":
    #list_data_locations()
    #print("Data locations have been listed in 'data_locations_combined.txt' and individual reports.")
    list_scalar_locations()
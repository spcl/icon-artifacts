import dace
import os
import re
import typing
from pathlib import Path
import sys
from dace.sdfg import infer_types
from utils.config import rm_syncs
from utils.prune_names import prune_names, compare_structs

# ─── Backend detection ────────────────────────────────────────────────
AMD = (
    os.getenv("__HIP_PLATFORM_AMD__", "0") == "1"
    or os.getenv("HIP_PLATFORM_AMD", "0") == "1"
)

USE_CUDA_EVENTS = os.getenv("_USE_CUDA_EVENTS", "0").lower() in ("1", "true", "yes")
USE_NVHPC = os.getenv("_USE_NVHPC", "0").lower() in ("1", "true", "yes")

# ─── CUDA ↔ HIP symbol mapping ───────────────────────────────────────
_CUDA_TO_HIP = {
    # ── Runtime ──────────────────────────────────────────────────────
    "cudaDeviceSynchronize":           "hipDeviceSynchronize",
    "cudaDeviceReset":                 "hipDeviceReset",
    "cudaGetDevice":                   "hipGetDevice",
    "cudaSetDevice":                   "hipSetDevice",
    "cudaGetDeviceCount":              "hipGetDeviceCount",
    "cudaGetDeviceProperties":         "hipGetDeviceProperties",
    "cudaDeviceGetAttribute":          "hipDeviceGetAttribute",
    # ── Streams ──────────────────────────────────────────────────────
    "cudaStreamCreate":                "hipStreamCreate",
    "cudaStreamCreateWithFlags":       "hipStreamCreateWithFlags",
    "cudaStreamCreateWithPriority":    "hipStreamCreateWithPriority",
    "cudaStreamDestroy":               "hipStreamDestroy",
    "cudaStreamSynchronize":           "hipStreamSynchronize",
    "cudaStreamWaitEvent":             "hipStreamWaitEvent",
    "cudaStreamQuery":                 "hipStreamQuery",
    "cudaStream_t":                    "hipStream_t",
    "cudaStreamDefault":               "hipStreamDefault",
    "cudaStreamNonBlocking":           "hipStreamNonBlocking",
    # ── Events ───────────────────────────────────────────────────────
    "cudaEvent_t":                     "hipEvent_t",
    "cudaEventCreate":                 "hipEventCreate",
    "cudaEventCreateWithFlags":        "hipEventCreateWithFlags",
    "cudaEventRecord":                 "hipEventRecord",
    "cudaEventSynchronize":            "hipEventSynchronize",
    "cudaEventElapsedTime":            "hipEventElapsedTime",
    "cudaEventDestroy":                "hipEventDestroy",
    "cudaEventQuery":                  "hipEventQuery",
    "cudaEventDisableTiming":          "hipEventDisableTiming",
    "cudaEventBlockingSync":           "hipEventBlockingSync",
    # ── Memory allocation ────────────────────────────────────────────
    "cudaMalloc":                      "hipMalloc",
    "cudaMallocManaged":               "hipMallocManaged",
    "cudaMallocHost":                  "hipHostMalloc",
    "cudaHostAlloc":                   "hipHostMalloc",
    "cudaMallocAsync":                 "hipMallocAsync",
    "cudaFree":                        "hipFree",
    "cudaFreeHost":                    "hipHostFree",
    "cudaFreeAsync":                   "hipFreeAsync",
    # ── Memory copy ──────────────────────────────────────────────────
    "cudaMemcpy":                      "hipMemcpy",
    "cudaMemcpyAsync":                 "hipMemcpyAsync",
    "cudaMemcpy2D":                    "hipMemcpy2D",
    "cudaMemcpy2DAsync":               "hipMemcpy2DAsync",
    "cudaMemcpy3D":                    "hipMemcpy3D",
    "cudaMemcpy3DAsync":               "hipMemcpy3DAsync",
    "cudaMemcpyPeer":                  "hipMemcpyPeer",
    "cudaMemcpyPeerAsync":             "hipMemcpyPeerAsync",
    "cudaMemcpyToSymbol":              "hipMemcpyToSymbol",
    "cudaMemcpyFromSymbol":            "hipMemcpyFromSymbol",
    "cudaMemcpyDeviceToHost":          "hipMemcpyDeviceToHost",
    "cudaMemcpyHostToDevice":          "hipMemcpyHostToDevice",
    "cudaMemcpyDeviceToDevice":        "hipMemcpyDeviceToDevice",
    "cudaMemcpyHostToHost":            "hipMemcpyHostToHost",
    "cudaMemcpyDefault":               "hipMemcpyDefault",
    # ── Memset ───────────────────────────────────────────────────────
    "cudaMemset":                      "hipMemset",
    "cudaMemsetAsync":                 "hipMemsetAsync",
    "cudaMemset2D":                    "hipMemset2D",
    "cudaMemset2DAsync":               "hipMemset2DAsync",
    "cudaMemset3D":                    "hipMemset3D",
    "cudaMemset3DAsync":               "hipMemset3DAsync",
    # ── Memory info ──────────────────────────────────────────────────
    "cudaMemGetInfo":                  "hipMemGetInfo",
    "cudaMemPrefetchAsync":            "hipMemPrefetchAsync",
    "cudaMemAdvise":                   "hipMemAdvise",
    "cudaPointerGetAttributes":        "hipPointerGetAttributes",
    # ── Error handling ───────────────────────────────────────────────
    "cudaGetLastError":                "hipGetLastError",
    "cudaPeekAtLastError":             "hipPeekAtLastError",
    "cudaGetErrorString":              "hipGetErrorString",
    "cudaGetErrorName":                "hipGetErrorName",
    "cudaError_t":                     "hipError_t",
    "cudaSuccess":                     "hipSuccess",
    "cudaErrorNotReady":               "hipErrorNotReady",
    "cudaErrorMemoryAllocation":       "hipErrorOutOfMemory",
    # ── Launch ───────────────────────────────────────────────────────
    "cudaLaunchKernel":                "hipLaunchKernel",
    "cudaFuncSetAttribute":            "hipFuncSetAttribute",
    "cudaFuncSetCacheConfig":          "hipFuncSetCacheConfig",
    "cudaFuncGetAttributes":           "hipFuncGetAttributes",
    "cudaOccupancyMaxActiveBlocksPerMultiprocessor":
        "hipOccupancyMaxActiveBlocksPerMultiprocessor",
    "cudaOccupancyMaxPotentialBlockSize":
        "hipOccupancyMaxPotentialBlockSize",
    # ── Texture / Surface (if used) ──────────────────────────────────
    "cudaCreateTextureObject":         "hipCreateTextureObject",
    "cudaDestroyTextureObject":        "hipDestroyTextureObject",
    "cudaTextureObject_t":             "hipTextureObject_t",
    # ── Host register ────────────────────────────────────────────────
    "cudaHostRegister":                "hipHostRegister",
    "cudaHostUnregister":              "hipHostUnregister",
    "cudaHostGetDevicePointer":        "hipHostGetDevicePointer",
    # ── Includes ─────────────────────────────────────────────────────
    "<cuda_runtime.h>":                "<hip/hip_runtime.h>",
    '"cuda_runtime.h"':                "<hip/hip_runtime.h>",
    "<cuda_runtime_api.h>":            "<hip/hip_runtime_api.h>",
    "<cuda.h>":                        "<hip/hip_runtime.h>",
    "<openacc.h>":                     "<hip/hip_runtime.h>",
    # ── Labels ───────────────────────────────────────────────────────
    "CUDA Events":                     "HIP Events",
}

# Sort longest-first to avoid partial replacement (e.g. cudaFree before cudaFreeHost)
_SORTED_MAP = sorted(_CUDA_TO_HIP.items(), key=lambda x: -len(x[0]))


def _sym(cuda_name: str) -> str:
    """Return the correct GPU API symbol for the current backend."""
    return _CUDA_TO_HIP.get(cuda_name, cuda_name) if AMD else cuda_name


def _hipify(text: str) -> str:
    """Replace all CUDA symbols in text with HIP equivalents if on AMD."""
    if not AMD:
        return text
    for cuda, hip in _SORTED_MAP:
        text = text.replace(cuda, hip)
    return text


# ─── File path helpers ────────────────────────────────────────────────
def _cpu_src(build_loc: str, name: str) -> str:
    if AMD:
        return f"{build_loc}/src/cpu/{name}.cpp"
    return f"{build_loc}/src/cpu/{name}.cu"


def _gpu_src(build_loc: str, name: str) -> str:
    if AMD:
        return f"{build_loc}/src/cuda/hip/{name}_cuda.cpp"
    return f"{build_loc}/src/cuda/{name}_cuda.cu"


def _header(build_loc: str, name: str) -> str:
    return f"{build_loc}/include/{name}.h"


# ─── Generic file manipulation ────────────────────────────────────────
def _read(path: str) -> str:
    with open(path, "r", encoding="utf-8") as f:
        return f.read()


def _write(path: str, content: str):
    with open(path, "w", encoding="utf-8") as f:
        f.write(content)


def repl_in_file(file_path: str, src: str, dst: str):
    _write(file_path, _read(file_path).replace(src, dst))


def repl_in_file_per_line_with_cond(
    file_path: str, src: str, dst: str, condition: callable
):
    lines = _read(file_path).splitlines(keepends=True)
    _write(
        file_path,
        "".join(line.replace(src, dst) if condition(line) else line for line in lines),
    )


# ─── Rename .cpp/.cc → .cu (CUDA only) ───────────────────────────────
def _replace_cpp_with_cu(directory: str):
    for ext in ("*.cpp", "*.cc"):
        for f in Path(directory).rglob(ext):
            new = f.with_suffix(".cu")
            f.rename(new)
            print(f"Renamed: {f} -> {new}")


# ─── Static variable fixups ──────────────────────────────────────────
_TMP_STRUCT_RE = re.compile(r"^(\s*)int tmp_struct_symbol")
_F2DACE_RE = re.compile(r"\bint\s+(__(f2dace_[a-zA-Z0-9_]+));")


def _fix_static_vars(directory: str):
    """Make tmp_struct_symbol and f2dace vars static."""
    for root, _, files in os.walk(directory):
        for fn in files:
            if not fn.endswith((".c", ".h", ".cpp", ".cu")):
                continue
            path = os.path.join(root, fn)
            lines = _read(path).splitlines(keepends=True)
            changed = False
            out = []
            for line in lines:
                if _TMP_STRUCT_RE.match(line):
                    line = _TMP_STRUCT_RE.sub(r"\1static int tmp_struct_symbol", line)
                    changed = True
                line = _F2DACE_RE.sub(r"static int \1;", line)
                out.append(line)
            if changed:
                _write(path, "".join(out))


# ─── Timer insertion ──────────────────────────────────────────────────
def add_timers(file_path: str, gpu: bool, stage: int, use_openacc_stream: bool = False):
    code = _read(file_path)

    if stage < 7:
        pat1 = r"^\s*nrdmax_jg\s*=\s*__CG_global_data__m_nrdmax\[0\];\s*$"
    else:
        pat1 = r"^\s*nflatlev_jg\s*=\s*__CG_global_data__m_nflatlev\[0\];\s*$"
    pat2 = r"^\s*double p_diag_out_max_vcfl_dyn;\s*$"

    sync_stream = _sym("cudaStreamSynchronize")
    sync_dev = _sym("cudaDeviceSynchronize")
    ev_t = _sym("cudaEvent_t")
    ev_create = _sym("cudaEventCreate")
    ev_record = _sym("cudaEventRecord")
    ev_sync = _sym("cudaEventSynchronize")
    ev_elapsed = _sym("cudaEventElapsedTime")
    ev_destroy = _sym("cudaEventDestroy")
    ev_label = _sym("CUDA Events")

    if not gpu:
        rep1 = ' measure_time("Run"); \n\\g<0>'
        rep2 = '\\g<0>  measure_time("Run");\n'
    else:
        # Entry sync + optional event start
        if stage > 5 and stage < 9:
            entry_sync = f"   {sync_stream}(__state->gpu_context->streams[0]); //EntryStreamSync\n"
        elif stage == 9 and not use_openacc_stream:
            entry_sync = f"   {sync_dev}(); //EntryStreamSync\n"
        elif stage == 9 and use_openacc_stream:
            entry_sync = ""
        else:
            entry_sync = f"   {sync_dev}(); //EntryStreamSync\n"

        if USE_CUDA_EVENTS and stage != 9:
            ev_start = (
                f"      {ev_t} start1, stop1;\n"
                f"    {ev_create}(&start1);\n"
                f"    {ev_create}(&stop1);\n"
                f"    {ev_record}(start1); \n"
            )
            timer_start = ""
        else:
            ev_start = ""
            timer_start = ' measure_time("Run");\n'

        rep1 = entry_sync + ev_start + timer_start + "\\g<0>"

        # Exit: optional event stop + timer
        if USE_CUDA_EVENTS and stage != 9:
            ev_stop = (
                f"  {ev_record}(stop1);\n"
                f"    {ev_sync}(stop1);\n"
                f"    float milliseconds1 = 0;\n"
                f"    {ev_elapsed}(&milliseconds1, start1, stop1);\n"
                f"  {ev_destroy}(start1);\n"
                f"    {ev_destroy}(stop1);\n"
            )
            if stage > 5:
                ev_stop += f"    {sync_stream}(__state->gpu_context->streams[0]); \n"
            else:
                ev_stop += f"    {sync_dev}(); \n"
            ev_stop += f'  std::cout << "{ev_label} Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;\n'
            timer_stop = ""
        else:
            ev_stop = ""
            if stage == 9:
                timer_stop = (
                    f"  {sync_stream}(__state->gpu_context->streams[0]);\n"
                    f'     measure_time("Host Based C++ Timer"); \n'
                    f"  {sync_dev}(); \n"
                )
            elif stage > 5:
                timer_stop = f'     measure_time("Host Based C++ Timer"); \n'
            else:
                timer_stop = f'     measure_time("Host Based C++ Timer"); \n'

        rep2 = "\\g<0>" + ev_stop + timer_stop

    code = re.sub(pat1, rep1, code, flags=re.MULTILINE)
    code = re.sub(pat2, rep2, code, flags=re.MULTILINE)

    if gpu and stage > 5:
        # Fix CopyNDDynamic → explicit memcpy
        old_copy = (
            "dace::CopyNDDynamic<double, 1, false, 1>::template ConstDst<1>::Copy(\n"
            "            __state->__0_gpu_vcflmax, __state->__0_vcflmax, tmp_struct_symbol_12, 1);"
        )
        memcpy_async = _sym("cudaMemcpyAsync")
        memcpy_d2h = _sym("cudaMemcpyDeviceToHost")
        new_copy = (
            f"DACE_GPU_CHECK({memcpy_async}((void*)__state->__0_vcflmax, "
            f"(void*)__state->__0_gpu_vcflmax, "
            f"static_cast<size_t>(tmp_struct_symbol_12) * sizeof(double), "
            f"{memcpy_d2h}, __state->gpu_context->streams[0]));"
        )
        code = code.replace(old_copy, new_copy)

        # Insert stream sync before vcflmax read
        pat5 = r"(^\s*double\s*.*\s*in_arr\s*=.*vcflmax.*;)"
        rep5 = rf"{sync_stream}(__state->gpu_context->streams[0]);//ExitStreamSync\n\1"
        code = re.sub(pat5, rep5, code, flags=re.MULTILINE)

    _write(file_path, code)


# ─── OpenACC stream setup ────────────────────────────────────────────
def change_to_openacc_stream(
    host_file_path: str, dev_file_path: str
):
    stream_decl = _hipify(
        "\n// Generated by velocity utils for openacc stream.\n"
        "#include <cuda_runtime.h>\n"
        "#include <openacc.h>\n"
        f"static {_sym('cudaStream_t')} open_acc_stream;\n"
    )

    host_check = "void __program_velocity_no_nproma_if_prop"
    dev_check = "DACE_EXPORTED int __dace_init_cuda_"

    sync_stream = _sym("cudaStreamSynchronize")
    ev_t = _sym("cudaEvent_t")
    ev_create = _sym("cudaEventCreate")
    ev_record = _sym("cudaEventRecord")
    stream_create = _sym("cudaStreamCreateWithFlags")
    stream_destroy = _sym("cudaStreamDestroy")
    ev_create_flags = _sym("cudaEventCreateWithFlags")
    ev_destroy = _sym("cudaEventDestroy")

    for file_path, check in [(host_file_path, host_check), (dev_file_path, dev_check)]:
        lines = _read(file_path).splitlines(keepends=True)
        out = [stream_decl]

        def _process_line(line: str) -> str:
            if "__dace_current_stream = __state->gpu_context->streams" in line:
                return f"{_sym('cudaStream_t')} __dace_current_stream = open_acc_stream;\n"
            skip_syms = (stream_create, stream_destroy, ev_create_flags, ev_destroy)
            if any(s in line for s in skip_syms) and "internal_streams[" in line or (
                any(s in line for s in skip_syms)
                and _sym("cudaLaunchKernel") not in line
                and "__state->gpu_context->internal_streams[" in line
            ):
                return "//" + line
            if any(s in line for s in skip_syms) and _sym("cudaLaunchKernel") not in line:
                if "__state->gpu_context->internal_streams[" in line:
                    return "//" + line
            if "__state->gpu_context->streams[0]" in line:
                return line.replace("__state->gpu_context->streams[0]", "open_acc_stream")
            return line

        i = 0
        while i < len(lines):
            line = lines[i]
            if check in line:
                out.append(_process_line(line))
                i += 1
                is_host = check == host_check
                if is_host and "_internal" in line and "{" not in line and ";" not in line and "DACE_EXPORTED" not in line:
                    if i < len(lines) and lines[i].strip() == "{":
                        out.append("{\n")
                        out.append(
                            f"open_acc_stream = ({_sym('cudaStream_t')}) acc_get_cuda_stream(1);\n"
                        )
                        out.append(f"{sync_stream}(open_acc_stream); //EntryStreamSync\n")
                        if USE_CUDA_EVENTS:
                            out.append(
                                f"    {ev_t} start1, stop1;\n"
                                f"    {ev_create}(&start1);\n"
                                f"    {ev_create}(&stop1);\n"
                                f"    {ev_record}(start1); \n"
                            )
                        else:
                            out.append('measure_time("Run");\n')
                        i += 1
                elif not is_host and "{" in line:
                    out.append(
                        f"open_acc_stream = ({_sym('cudaStream_t')}) acc_get_cuda_stream(1);\n"
                    )
            else:
                out.append(_process_line(line))
                i += 1

        _write(file_path, "".join(out))


# ─── Sync removal ────────────────────────────────────────────────────
def comment_out_syncs(filepath: str, gpu: bool):
    sync_stream = _sym("cudaStreamSynchronize")
    ev_record = _sym("cudaEventRecord")
    stream_wait = _sym("StreamWaitEvent")  # partial match is fine

    lines = _read(filepath).splitlines(keepends=True)
    out = []
    for line in lines:
        if any(s in line for s in (sync_stream, ev_record, stream_wait)):
            if "stop" not in line and "start" not in line:
                line = "//" + line
        if "tmp_call_18 = -1.7976931348623157e+308;" in line:
            if gpu:
                line = f"DACE_GPU_CHECK({sync_stream}(__state->gpu_context->streams[0]));\n" + line
            else:
                line = "//" + line
        out.append(line)
    _write(filepath, "".join(out))


# ─── Alloc/free commenting ───────────────────────────────────────────
def comment_out_allocs_and_frees(filepath: str, name_set: typing.Set[str]):
    gpu_free = _sym("cudaFree")
    gpu_malloc = _sym("cudaMalloc")

    lines = _read(filepath).splitlines(keepends=True)
    out = []
    for i, line in enumerate(lines):
        stripped = line.strip()
        if stripped.startswith("//"):
            out.append(line)
            continue
        should_comment = False
        for name in name_set:
            if ("delete[]" in line or "delete" in line) and name in line and ";" in line:
                should_comment = True; break
            if gpu_free in line and name in line:
                should_comment = True; break
            if gpu_malloc in line and name in line:
                should_comment = True; break
            if name in line and "=" in line and "new" in line and "DACE_ALIGN" in line:
                should_comment = True; break
        if should_comment:
            ws = line[: len(line) - len(line.lstrip())]
            out.append(ws + "//" + line.lstrip())
        else:
            out.append(line)
    _write(filepath, "".join(out))


# ─── Reduce cleanup calls ────────────────────────────────────────────
def add_reduce_clean_up_calls(filepath: str):
    target = "DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop"
    lines = _read(filepath).splitlines(keepends=True)
    out = []
    i = 0
    while i < len(lines):
        if target in lines[i]:
            out.append(lines[i])
            i += 1
            assert lines[i].strip() == "{"
            out.append("{\n")
            out.append("cleanup_reduce_sum_gpu();\n")
            out.append("cleanup_reduce_maxZ_gpu();\n")
        else:
            out.append(lines[i])
        i += 1
    _write(filepath, "".join(out))


# ─── Default stream fix ──────────────────────────────────────────────
def set_default_stream(file_path: str):
    repl_in_file(file_path, "__state->gpu_context->streams[0]", "nullptr")


# ─── Levelmask fixes ─────────────────────────────────────────────────
def fix_levelmask_calls(filepath: str, host: bool, stage: int):
    lines = _read(filepath).splitlines(keepends=True)
    out = []

    if stage <= 5:
        p1 = "uint8_t  gpu_levelmask, double *"
        r1 = "uint8_t* __restrict__  gpu_levelmask, double *"
        p2 = "gpu_levelmask, &"
        r2 = "&gpu_levelmask[0], &" if host else "gpu_levelmask[0], &"
    else:
        p1_host = "uint8_t  gpu_levelmask, double *"
        p1_dev = "uint8_t gpu_levelmask, double *"
        p1 = p1_host if host else p1_dev
        r1 = "uint8_t* __restrict__  gpu_levelmask, double *"
        p2 = "__state->__0_gpu_levelmask, &" if host else "&__state->__0_gpu_levelmask, &"
        r2 = "&__state->__0_gpu_levelmask[0], &"

    for line in lines:
        if not host:
            line = line.replace(
                "uint8_t in_arr = gpu_cfl_clipping;",
                "uint8_t in_arr = gpu_cfl_clipping[((_for_it_22 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];",
            )
            line = line.replace(
                "uint8_t  gpu_cfl_clipping,",
                "uint8_t* __restrict__  gpu_cfl_clipping,",
            )
        line = line.replace(p1, r1).replace(p2, r2)
        if stage > 5:
            line = line.replace(", &gpu_levelmask,", ", &gpu_levelmask[0],")
        out.append(line)
    _write(filepath, "".join(out))


# ─── Struct definition replacement ───────────────────────────────────
_SHARED_STRUCTS = {
    "global_data_type", "t_tangent_vectors", "t_grid_edges", "t_nh_metrics",
    "t_prepare_adv", "t_nh_ref", "t_nh_prog", "t_nh_diag", "t_nh_state",
    "t_grid_domain_decomp_info", "t_grid_cells", "t_int_state",
    "t_grid_vertices", "t_patch",
}


def use_solve_nh_struct_definitions(filepath: str):
    lines = _read(filepath).split("\n")
    out = []
    i = 0
    while i < len(lines):
        stripped = lines[i].strip()
        fwd = re.match(r"\s*struct\s+(\w+)\s*;", lines[i])
        if fwd and fwd.group(1) in _SHARED_STRUCTS:
            i += 1; continue
        defn = re.search(r"\bstruct\s+(\w+)\s*\{", lines[i])
        if defn and defn.group(1) in _SHARED_STRUCTS:
            i += 1
            while i < len(lines) and lines[i].strip() != "};":
                i += 1
            i += 1; continue
        out.append(lines[i])
        i += 1
    _write(filepath, '#include "shared_struct_defs.h"\n' + "\n".join(out))


# ─── Pass-by-copy → pass-by-ref ──────────────────────────────────────
_PASS_BY_REF_TUPLES = [
    ("double", "__CG_p_diag__m_max_vcfl_dyn"),
]


def replace_pass_by_copy_to_pass_by_ref(path: str):
    content = _read(path)
    for type_name, name in _PASS_BY_REF_TUPLES:
        content = re.sub(
            rf" {re.escape(type_name)} {re.escape(name)},",
            rf"{type_name}& {name},",
            content,
        )
        content = re.sub(
            rf" {re.escape(type_name)} {re.escape(name)}[)]",
            rf"{type_name}& {name})",
            content,
        )
    _write(path, content)


# ─── Build helpers ────────────────────────────────────────────────────
def _get_compiler(gpu: bool) -> str:
    if gpu:
        return "hipcc" if AMD else "nvcc"
    return "c++"


def _get_flags(gpu: bool, release: bool, lib: bool, debuginfo: bool) -> str:
    # ── OpenMP flags per backend ──
    # hipcc wraps clang++, so -fopenmp goes directly.
    # nvcc needs -Xcompiler=-fopenmp for host code.
    # CPU compiler (g++/clang++) takes -fopenmp directly.
    if gpu and AMD:
        omp_flag = "-fopenmp"
    elif gpu:
        omp_flag = "-Xcompiler=-fopenmp"
    else:
        omp_flag = "-fopenmp"

    if gpu and AMD:
        arch = "gfx942"
        common = f"--offload-arch={arch} -std=c++20 -DNDEBUG"
        if release:
            flags = (
                f"{common} -Wall -Wextra {omp_flag} "
                f"--offload-arch={arch} "
                "-mllvm -amdgpu-early-inline-all=true "
                "-munsafe-fp-atomics "
                "-ffp-contract=fast "
                "-fPIC -O3 -ffast-math "
                "-Wno-unused-parameter -Wno-ignored-attributes -Wno-unused-result"
            )
        else:
            flags = (
                f"{common} -O0 -g -ggdb -fPIC -Wall -Wextra {omp_flag} "
                "-Wno-unused-parameter -Wno-ignored-attributes -Wno-unused-result "
                "-DDACE_VELOCITY_DEBUG"
            )
        if debuginfo:
            flags += " -g"
        if lib:
            flags += " -DNO_SERDE -fPIC -shared"
    elif gpu:
        # NVIDIA CUDA
        gencode_num = os.getenv("GENCODE_NUMBER", "90a")
        if gencode_num == "0":
            raise ValueError("Set GENCODE_NUMBER (e.g. 90)")
        nvhpc = "-ccbin=nvc++ " if USE_NVHPC else ""
        suppress = (
            "--diag-suppress 68 --diag-suppress 550 --diag-suppress 20208 "
            "--diag-suppress 1835 --diag-suppress 177 --diag-suppress 20012 "
            "--diag-suppress 1098"
        )
        xcompiler_warns = (
            "-Xcompiler=-Wconversion -Xcompiler=-Wsign-conversion "
            "-Xcompiler=-Wfloat-conversion -Xcompiler=-Wno-unknown-pragmas "
            "-Xcompiler=-faligned-new"
        ) if not USE_NVHPC else ""
        debugflag = "-lineinfo" if debuginfo else ""
        arch_flag = f"-arch=sm_{gencode_num}"

        if release:
            flags = (
                f"{nvhpc}{suppress} {xcompiler_warns} -DNDEBUG -Xcompiler=-DNDEBUG "
                f"-Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-O3 {omp_flag} "
                f"--expt-relaxed-constexpr {arch_flag} "
                f"--use_fast_math -O3 {debugflag} --ftz=true "
                f"--prec-div=false --prec-sqrt=false --fmad=true "
                f"-Xptxas=-O3 -Xptxas=-v -Xcompiler=-march=native "
                f"-Xcompiler=-mtune=native --restrict"
            )
        else:
            flags = (
                f"{suppress} {xcompiler_warns} -DNDEBUG "
                f"-Xcompiler=-Wall -Xcompiler=-Wextra {omp_flag} "
                f"--expt-relaxed-constexpr {arch_flag} "
                f"-O0 -Xcompiler=-g -g -Xcompiler=-O0 -G {debugflag} "
                f"--fmad=false --prec-div=true --prec-sqrt=true --ftz=false "
                f"-DDACE_VELOCITY_DEBUG -Xcompiler=-DDACE_VELOCITY_DEBUG"
            )
        if lib:
            flags += " -DNO_SERDE -std=c++17 -Xcompiler=-fPIC --compiler-options '-fPIC' --shared"
        else:
            flags += " -std=c++20"
    else:
        # CPU
        warns = (
            "-Wconversion -Wno-sign-conversion -Wfloat-conversion "
            "-Wno-unknown-pragmas -faligned-new"
        ) if not USE_NVHPC else ""
        debugflag = "-g" if debuginfo else ""
        if release:
            flags = (
                f"{warns} {debugflag} -std=c++20 -Wall -Wextra "
                f"-Wno-unused-parameter -Wno-unused-variable -O3 -DNDEBUG "
                f"{omp_flag}"
            )
        else:
            flags = (
                f"{warns} -DDACE_VELOCITY_DEBUG -std=c++20 -Wall -Wextra "
                f"-Wno-unused-parameter -Wno-unused-variable "
                f"-Wno-unknown-pragmas -O0 -g -ggdb {debugflag} "
                f"{omp_flag}"
            )

    if AMD:
        flags += " -D__HIP_PLATFORM_AMD__=1"
        flags += " -DHIP_PLATFORM_AMD=1"

    return flags


import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed

def _compile_and_link(
    sources: typing.List[str],
    includes: str,
    flags: str,
    output: str,
    compiler: str,
    lib: bool,
    jobs: int = os.cpu_count(),
):
    compile_flags = flags.replace("--shared", "").replace("-shared", "")
    objects = []

    def compile_one(src):
        obj = os.path.splitext(src)[0] + ".o"
        cmd = f"{compiler} -c {src} {includes} {compile_flags} -o {obj}"
        ret = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        return src, obj, ret

    with ThreadPoolExecutor(max_workers=jobs) as pool:
        futures = {pool.submit(compile_one, src): src for src in sources}
        for fut in as_completed(futures):
            src, obj, ret = fut.result()
            print(f"  [CC] {src}")
            if ret.stdout:
                print(ret.stdout, end="")
            if ret.stderr:
                print(ret.stderr, end="", file=sys.stderr)
            if ret.returncode != 0:
                raise RuntimeError(f"FAILED: {src}")
            objects.append(obj)

    # Extract arch flag from compile_flags to pass during linking
    import re as _re
    arch_match = _re.search(r"-arch=sm_\w+", compile_flags)
    arch_flag = arch_match.group(0) if arch_match else ""

    # Link flags
    link_flags = ""
    if lib:
        link_flags = "-shared" if AMD or compiler == "c++" else "--shared -Xcompiler=-fPIC"

    # Add OpenMP to linker
    if AMD:
        link_flags += " -fopenmp "
    elif "nvcc" in compiler:
        link_flags += " -Xcompiler=-fopenmp "
    else:
        link_flags += " -fopenmp "
    
    link_cmd = f"{compiler} {' '.join(objects)} {arch_flag}  {link_flags} -o {output} -lnuma"
    print(f"  [LD] {output}")
    ret = subprocess.run(link_cmd, shell=True)
    if ret.returncode != 0:
        raise RuntimeError(f"FAILED: {link_cmd}")


# ─── Main entry point ────────────────────────────────────────────────
def compile_if_propagated_sdfgs(
    sdfgs: typing.List[dace.SDFG],
    gpu: bool,
    release: bool,
    generate_code: bool,
    lib: bool,
    main_name: typing.Optional[str],
    stage: int,
    debuginfo: bool,
    allocation_names_to_comment_out: typing.Optional[set],
    use_openacc_stream: bool,
):
    compare_structs(sdfgs)

    do_rm_timers = os.environ.get("RM_TIMERS", "0") == "1"
    if do_rm_timers:
        def rm_timers(sdfg: dace.SDFG):
            rmed = 0
            for state in sdfg.all_states():
                if state.label in {"profile_stop_sync", "entry_timer", "exit_timer", "profile_start_sync"}:
                    nodes = state.nodes()
                    assert len(nodes) == 1 and isinstance(nodes[0], dace.nodes.Tasklet)
                    state.remove_node(nodes[0])
                    rmed += 1
            #assert rmed == 4, f"Expected to remove 4 timer-related tasklets, but removed {rmed} in SDFG {sdfg.name}"
        
        for sdfg in sdfgs:
            rm_timers(sdfg)  # Only need to remove from one SDFG since they are all the same

    dace.Config.set("compiler", "cuda", "max_concurrent_streams", value="1")

    if AMD:
        dace.config.Config.set("compiler", "cuda", "backend", value="hip")
        dace.config.Config.set("compiler", "cuda", "path", value="/opt/rocm")
        dace.config.Config.set("compiler", "cuda", "hip_arch", value="gfx942")
        dace.config.Config.set("compiler", "cuda", "default_block_size", value="32,16,1")
        dace.config.Config.set(
            "compiler", "cuda", "hip_args",
            value=(
                "--offload-arch=gfx942 "
                "-mllvm -amdgpu-early-inline-all=true "
                "-munsafe-fp-atomics "
                "-ffp-contract=fast "
                "-fPIC -O3 -ffast-math "
                "-Wno-unused-parameter -Wno-ignored-attributes -Wno-unused-result"
            ),
        )
    else:
        dace.config.Config.set("compiler", "cuda", "default_block_size", value="32,16,1")

    # External sources
    sources = ["src/reductions.cpp", "src/timer.cpp"]
    if gpu:
        ext = ".cpp" if AMD else ".cu"
        sources.append(f"src/reductions_kernel{ext}")

    headers = ["-Iinclude"]

    from dace.codegen import codegen, compiler

    lowered = os.getenv("_REDUCE_BITWIDTH_TRANSFORMATION", "0") == "1"
    lowered_suffix = "_lowered" if lowered is True else ""
    for sdfg in sdfgs:
        # Changing sdfg name changes state name, makes compiling fail
        #if lowered:
        #    sdfg.name += "_lowered"
        name = sdfg.name
        if lowered and (not sdfg.build_folder.endswith("_lowered")):
            sdfg.build_folder += "_lowered"
        build_loc = sdfg.build_folder

        if generate_code:
            try:
                sdfg.fill_scope_connectors()
                infer_types.infer_connector_types(sdfg)
                infer_types.set_default_schedule_and_storage_types(sdfg, None)
                sdfg.expand_library_nodes()
                infer_types.infer_connector_types(sdfg)
                infer_types.set_default_schedule_and_storage_types(sdfg, None)
                sdfg.save(name + "_concretized.sdfgz", compress=True)
                program_objects = codegen.generate_code(sdfg, validate=False)
            except Exception:
                fpath = os.path.join("_dacegraphs", "failing.sdfgz")
                sdfg.save(fpath, compress=True)
                print(f"Failing SDFG saved: {os.path.abspath(fpath)}")
                raise

            compiler.generate_program_folder(sdfg, program_objects, build_loc)
            _fix_static_vars(build_loc)

        cpu_file = _cpu_src(build_loc, name)
        gpu_file = _gpu_src(build_loc, name)
        hdr_file = _header(build_loc, name)

        if gpu:
            if not AMD:
                _replace_cpp_with_cu(build_loc)

            if stage > 5 and rm_syncs:
                comment_out_syncs(cpu_file, gpu)

            if allocation_names_to_comment_out is not None:
                assert stage == 9
                comment_out_allocs_and_frees(cpu_file, allocation_names_to_comment_out)

            if use_openacc_stream:
                assert stage == 9 and gpu
                change_to_openacc_stream(cpu_file, gpu_file)

            add_reduce_clean_up_calls(cpu_file)
            fix_levelmask_calls(cpu_file, host=True, stage=stage)

            if stage > 5:
                fix_levelmask_calls(gpu_file, host=False, stage=stage)

                # Prepend reduction device header
                code = _read(gpu_file)
                _write(
                    gpu_file,
                    '#include "reductions_device.cuh"\n#define __REDUCE_DEVICE__\n' + code,
                )
                repl_in_file(gpu_file, "const const", "const")
                repl_in_file(cpu_file, "const const", "const")

            if stage == 9:
                cond = lambda line: (
                    "double __CG_p_diag__m_max_vcfl_dyn" in line
                    and "__CG_p_diag__m_max_vcfl_dyn;" not in line
                )
                for fp in (cpu_file, gpu_file, hdr_file):
                    if stage > 5 or fp != gpu_file:
                        repl_in_file_per_line_with_cond(
                            fp,
                            "double __CG_p_diag__m_max_vcfl_dyn",
                            "double &__CG_p_diag__m_max_vcfl_dyn",
                            condition=cond,
                        )

            if AMD and stage > 5:
                _write(gpu_file, _hipify(_read(gpu_file)))
            
            if stage >= 5:
                sources.append(gpu_file)

            # Prepend includes to cpu file
            code = _read(cpu_file)
            _write(
                cpu_file,
                '#include "reductions_kernel.cuh"\n'
                '#include "reductions_cpu.h"\n'
                '#include "timer.h"\n' + code,
            )

            if stage >= 6:
                set_default_stream(cpu_file)
                if stage > 5:
                    set_default_stream(gpu_file)

            if AMD:
                _write(cpu_file, _hipify(_read(cpu_file)))

            sources.append(cpu_file)
        else:
            # CPU-only
            code = _read(f"{build_loc}/src/cpu/{name}.cpp")
            _write(
                f"{build_loc}/src/cpu/{name}.cpp",
                '#include "reductions_cpu.h"\n#include "timer.h"\n' + code,
            )
            sources.append(f"{build_loc}/src/cpu/{name}.cpp")

        # Integration build struct fixes
        if os.getenv("_BUILD_LIB_FOR_SOLVE_NH", "0").lower() in ("1", "true", "yes"):
            if stage in (1, 9):
                targets = [cpu_file]
                if gpu and stage == 9:
                    targets.append(gpu_file)
                for t in targets:
                    use_solve_nh_struct_definitions(t)

            target_src = cpu_file if gpu else f"{build_loc}/src/cpu/{name}.cpp"
            replace_pass_by_copy_to_pass_by_ref(target_src)
            replace_pass_by_copy_to_pass_by_ref(hdr_file)

    # Add main
    if main_name is not None:
        if AMD and main_name.endswith(".cu"):
            import shutil
            new_name = main_name[:-3] + ".cpp"
            shutil.copy2(main_name, new_name)
            main_name = new_name
        sources.append(main_name)
    elif not lib:
        if gpu:
            ext = ".cpp" if AMD else ".cu"
            sources.append(f"main_gpu{ext}")
        else:
            sources.append("main.cc")

    # Compile
    cc = _get_compiler(gpu)
    flags = _get_flags(gpu, release, lib, debuginfo)
    dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"
    includes = " ".join(
        [f"-I{sdfg.build_folder}/include" for sdfg in sdfgs]
        + [f"-I{dace_include}"]
        + headers
    )

    lowered = os.getenv("_REDUCE_BITWIDTH_TRANSFORMATION", "0") == "1"
    lowered_suffix = "_lowered" if lowered is True else ""
    if lib:
        output = "libvelocity_gpu.so" if gpu else "libvelocity_cpu.so"
    else:
        output = f"velocity_gpu{lowered_suffix}" if gpu else f"velocity_cpu{lowered_suffix}"

    print(f"\nBackend: {'HIP (AMD)' if AMD else 'CUDA (NVIDIA)' if gpu else 'CPU'}")
    print(f"Compiler: {cc}")
    print(f"Output: {output}")
    print(f"Sources: {len(sources)} files\n")

    _compile_and_link(sources, includes, flags, output, cc, lib)
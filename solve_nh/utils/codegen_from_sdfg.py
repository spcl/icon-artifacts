from itertools import chain
import os
import dace
from dace import SDFG
from pathlib import Path
from dace.codegen import codegen, compiler
from dace.sdfg import infer_types

import subprocess
import re
from enum import Enum
import platform


GPU_STAGE_BEGINS = 3


class Mode(Enum):
    STATIC = "static"
    SHARED = "shared"
    EXEC = "exec"

    def __str__(self) -> str:
        return self.value


def generate_code_from_sdfg(g: SDFG) -> None:
    """
    Prepares and generates C++ code from a DaCe SDFG.

    This function performs several preparation steps on the SDFG, such as
    filling scope connectors, inferring types, and expanding library nodes.
    After preparation, it saves a "concrete" version of the SDFG and then
    generates the C++ source code, saving it into the SDFG's build folder
    (g.build_folder).

    :param g: The SDFG object to generate code from.
    """

    g.fill_scope_connectors()
    infer_types.infer_connector_types(g)
    infer_types.set_default_schedule_and_storage_types(g, None)

    g.expand_library_nodes()
    infer_types.infer_connector_types(g)
    infer_types.set_default_schedule_and_storage_types(g, None)

    g.save(f"{g.name}.concrete.sdfgz", compress=True)

    objs = codegen.generate_code(g, validate=False)
    compiler.generate_program_folder(g, objs, g.build_folder)

    print(f"Code generated and saved to {g.build_folder}")


def wrap_namespace(name: str, content: str) -> str:
    # Extract header guard (e.g. #ifndef ... #define ... #endif)
    # and includes (e.g. #include <...> or #include "...") at the top of the file.

    lines = content.splitlines()

    header_guard_lines = []
    include_lines = []
    rest_lines = []

    in_header_guard = True
    for line in lines:
        stripped = line.strip()
        # Collect header guard lines until we see first non-header-guard line
        if in_header_guard and (
            stripped.startswith("#ifndef")
            or stripped.startswith("#define")
            or stripped.startswith("#endif")
        ):
            header_guard_lines.append(line)
        elif stripped.startswith("#include"):
            include_lines.append(line)
        else:
            in_header_guard = False
            rest_lines.append(line)

    fixed_start = "/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */"
    pattern_start = re.compile(r"#define\s+__DACE_CODEGEN_SOLVE_NH_[A-Z_]+__")
    pattern_end = re.compile(r"struct\s+solve_nh_[a-z_]+_state_t\s*")
    start_idx: int | None = None
    end_idx: int | None = None
    # Find the start and end indices
    for i, line in enumerate(rest_lines):
        if start_idx is None and (fixed_start in line or pattern_start.search(line)):
            start_idx = i
        elif start_idx is not None and pattern_end.search(line):
            end_idx = i
            break
    assert start_idx is not None and end_idx is not None
    rest_lines = rest_lines[: start_idx + 1] + rest_lines[end_idx:]

    # Join the parts
    header_guard = "\n".join(header_guard_lines)
    includes = "\n".join(include_lines)
    main_content = "\n".join(rest_lines).strip()

    symbol_suffix_pattern = re.compile(r"(->__f2dace_[a-zA-Z0-9_]+_d_[0-9]+_s)_[0-9]+")
    main_content = symbol_suffix_pattern.sub(r"\1", main_content)

    # Wrap main content in namespace
    wrapped = f"""
{header_guard}
{includes}
#include "shared_struct_defs.h"
#include "velocity_shim.h"

namespace {name} {{
{main_content}
}}
"""
    return wrapped.strip()

def wrap_gpu_namespace(name: str, content: str) -> str:
    # Extract header guard (e.g. #ifndef ... #define ... #endif)
    # and includes (e.g. #include <...> or #include "...") at the top of the file.

    lines = content.splitlines()

    header_guard_lines = []
    include_lines = []
    rest_lines = []

    in_header_guard = True
    for line in lines:
        stripped = line.strip()
        # Collect header guard lines until we see first non-header-guard line
        if in_header_guard and (
            stripped.startswith("#ifndef")
            or stripped.startswith("#define")
            or stripped.startswith("#endif")
        ):
            header_guard_lines.append(line)
        elif stripped.startswith("#include"):
            include_lines.append(line)
        else:
            in_header_guard = False
            rest_lines.append(line)
    pattern_end = re.compile(r"struct\s+solve_nh_[a-z_]+_state_t\s*")
    start_idx: int | None = None
    end_idx: int | None = None
    # Find the start and end indices
    for i, line in enumerate(rest_lines):
        if end_idx is None and (pattern_end.search(line)):
            end_idx = i
            break
    start_idx = 0
    assert start_idx is not None and end_idx is not None, f"Start index: {start_idx}, End index: {end_idx}"
    rest_lines = rest_lines[:start_idx] + rest_lines[end_idx:]

    # Join the parts
    header_guard = "\n".join(header_guard_lines)
    includes = "\n".join(include_lines)
    main_content = "\n".join(rest_lines).strip()

    symbol_suffix_pattern = re.compile(r"(->__f2dace_[a-zA-Z0-9_]+_d_[0-9]+_s)_[0-9]+")
    main_content = symbol_suffix_pattern.sub(r"\1", main_content)

    # Wrap main content in namespace
    wrapped = f"""
{header_guard}
{includes}
#include "shared_struct_defs.h"
#include "velocity_shim.h"

namespace {name.replace("_cuda", "")} {{

//struct solve_nh_{name.replace("_cuda", "")}_state_t {{
//    dace::cuda::Context *gpu_context;
//}};

{main_content.replace("DACE_EXPORTED", "")}
}}
"""
    return wrapped.strip()

# --- Constants ---
CC = "clang++" if platform.system() == "Darwin" else "g++"
NVCC = "nvcc"
OBJ_FILE = "solve_nh_parts.o"
CUDA_OBJ_FILE = "solve_nh_parts_cuda.o"
STATIC_LIB_FILE = "libsolve_nh_parts.a"
SHARED_LIB_FILE = "libsolve_nh_parts.so"
EXEC_FILE = "verify_solve_nh_parts"
CONSOLIDATED_HEADER = "solve_nh_parts.h"
CONSOLIDATED_SOURCE = "solve_nh_parts.cpp"
CONSOLIDATED_CUDA_SOURCE = "solve_nh_parts.cu"
STANDALONE_INCLUDE_DIR = Path("include/")
STANDALONE_MAIN_SRC = Path("main.cc")
STANDALONE_CUDA_MAIN_SRC = Path("main.cc")



def _run_command(command: list[str], env: dict | None = None) -> None:
    """Runs a command, checks for errors, and prints output."""
    print(f"Running command: {' '.join(command)}")
    result = subprocess.run(command, capture_output=True, text=True, env=env)
    if result.stdout:
        print(f"Output:\n{result.stdout}")
    if result.stderr:
        print(f"Error:\n{result.stderr}")
    if result.returncode != 0:
        print(f"Command failed with return code {result.returncode}")
        exit(1)
    print("Command succeeded.")


class Compiler:
    def __init__(self, cc: str = CC, nvcc: str = NVCC):
        self.cc = cc
        self.diagnosis_flags = self._get_diagnosis_flags()
        self.optimization_flags = self._get_optimization_flags()
        self.standard_flags = self._get_standard_flags()
        self.cuda_diagnosis_flags = self._get_cuda_diagnosis_flags()
        self.cuda_optimization_flags = self._get_cuda_optimization_flags()
        self.cuda_standard_flags = self._get_cuda_standard_flags()
        self.dace_include = Path(dace.__file__).parent / "runtime/include/"
        self.nvcc = nvcc

    def _get_diagnosis_flags(self) -> list[str]:
        errlimit_flag = (
            "-fmax-errors=1" if self.cc.startswith("g++") else "-ferror-limit=1"
        )
        clang_only_warnings = (
            "-Wno-parentheses-equality -Wno-constant-logical-operand"
            if self.cc.startswith("clang")
            else ""
        )
        return (
            f"{errlimit_flag} -g -Wall -Wextra -Wno-unused-parameter "
            f"-Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable "
            f"-Wno-unused-but-set-parameter -Wno-sign-compare {clang_only_warnings}"
        ).split()

    def _get_cuda_diagnosis_flags(self) -> list[str]:
        errlimit_flag = (
            "-Xcompiler=-fmax-errors=1" if self.cc.startswith("g++") else "-Xcompiler=-ferror-limit=1"
        )
        clang_only_warnings = (
            "-Xcompiler=-Wno-parentheses-equality -Xcompiler=-Wno-constant-logical-operand"
            if self.cc.startswith("clang")
            else ""
        )
        return (
            f"{errlimit_flag} -Xcompiler=-g -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter "
            f"-Xcompiler=-Wno-unused-variable -Xcompiler=-Wno-unused-function -Xcompiler=-Wno-unused-but-set-variable "
            f"-Xcompiler=-Wno-unused-but-set-parameter -Xcompiler=-Wno-sign-compare -Wno-deprecated-declarations {clang_only_warnings}"
        ).split()

    def _get_optimization_flags(self) -> list[str]:
        return "-O0 -march=native -fno-strict-aliasing -fno-omit-frame-pointer -fno-fast-math -ffp-contract=off".split()

    def _get_cuda_optimization_flags(self) -> list[str]:
        return "-O3 -Xcompiler=-march=native -Xcompiler=-fno-strict-aliasing -Xcompiler=-fno-omit-frame-pointer -Xcompiler=-fno-fast-math -Xcompiler=-ffp-contract=off".split()

    def _get_standard_flags(self) -> list[str]:
        return "-fPIC -fopenmp".split()

    def _get_cuda_standard_flags(self) -> list[str]:
        return "-Xcompiler=-fPIC -Xcompiler=-fopenmp -arch=native --expt-relaxed-constexpr -Xcompiler=-fno-var-tracking-assignments -rdc=true -Xcompiler=-fPIC --compiler-options='-fPIC' -DGPU".split()

    def _get_cpp_standard_flags(self) -> list[str]:
        return ["-std=c++20"]

    def get_base_flags(self) -> list[str]:
        return self.diagnosis_flags + self.optimization_flags + self.standard_flags

    def get_cuda_base_flags(self) -> list[str]:
        return self.cuda_diagnosis_flags + self.cuda_optimization_flags + self.cuda_standard_flags

    def _get_cuda_src_file_flag(self) -> str:
        return "-x=cu"

    def get_velocity_linker_flags(self, stage: int) -> list[str]:
        # Search for existence of velocity library files intended for this stage
        if any(Path(f).exists() for f in [
            f"libvelocity_{stage}.so", f"libvelocity_{stage}.dylib", f"libvelocity_{stage}.a"]):
            rpath_flag = '-Xcompiler="-Wl,-rpath,."' if stage >= GPU_STAGE_BEGINS else "-Wl,-rpath,."
            return ["-L.", f"-lvelocity_{stage}", rpath_flag]
        else:
            return []

    def get_linker_flags(self, mode: Mode) -> list[str]:
        if mode == Mode.SHARED:
            dyn_link = "-dynamiclib" if platform.system() == "Darwin" else "-shared"
            dyn_symbols = (
                "-Wl,-undefined,dynamic_lookup"
                if platform.system() == "Darwin"
                else "-Wl,--unresolved-symbols=ignore-all"
            )
            return [dyn_link, dyn_symbols]
        return []

    def get_gpu_executable_linker_flags(self) -> list[str]:
        return []

    def get_gpu_library_linker_flags(self) -> list[str]:
        return ["-shared"]

    def compile_object(
        self, sources: list[Path], includes: list[Path], stage = 0,
    ):
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]
        if stage >= GPU_STAGE_BEGINS:
            raise Exception("GPU stage compilation for library is not implemented yet.")
        else:
            cmd = (
                [self.cc, "-c"]
                + [str(s) for s in sources]
                + [f"-I{i}" for i in all_includes]
                + self.get_base_flags()
                + self._get_cpp_standard_flags()
            )
            _run_command([str(c) for c in cmd if c])

    def archive_static_library(self, obj_files: list[str], lib_name: str):
        cmd = ["ar", "rcs", lib_name] + obj_files
        _run_command(cmd)

    def link_shared_library(self, static_lib: str, lib_name: str, stage: int):
        flags = self.get_base_flags() if stage < GPU_STAGE_BEGINS else self.get_cuda_base_flags()
        flags.extend(self.get_linker_flags(Mode.SHARED))
        flags.extend(self.get_velocity_linker_flags(stage))
        cmd = ([self.cc if stage < GPU_STAGE_BEGINS else self.nvcc, static_lib]
               + flags
               + self._get_cpp_standard_flags()
               + ["-o", lib_name]
        )
        _run_command([str(c) for c in cmd if c])

    def link_executable(
        self, main_src: Path, static_lib: str, includes: list[Path], bin_name: str, stage: int
    ):
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]
        flags = self.get_base_flags() if stage < GPU_STAGE_BEGINS else self.get_cuda_base_flags()
        flags.extend(self.get_linker_flags(Mode.EXEC))
        flags.extend(self.get_velocity_linker_flags(stage))
        cmd = (
            [self.cc if stage < GPU_STAGE_BEGINS else self.nvcc, str(main_src), static_lib]
            + [f"-I{i}" for i in all_includes]
            + flags
            + self._get_cpp_standard_flags()
            + ["-o", bin_name]
        )
        _run_command([str(c) for c in cmd if c])

    def compile_gpu_executable(
        self, main_src: Path, host_sources: list[Path], includes: list[Path], gpu_output_name: str, stage = 0,
    ):
        # sdfg_srcs, sdfg_cuda_srcs, sdfg_includes, EXEC_FILE, stage
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]
        assert stage >= GPU_STAGE_BEGINS, f"GPU stage compilation requires stage >= {GPU_STAGE_BEGINS}"
        gen_sources = []
        for s in [main_src] + host_sources:
            gen_sources.append(self._get_cuda_src_file_flag())
            gen_sources.append(str(s))
        cmd = (
            [self.nvcc,]
            + gen_sources
            + [f"-I{i}" for i in all_includes]
            + self.get_cuda_base_flags()
            + self._get_cpp_standard_flags()
            + self.get_gpu_executable_linker_flags()
            + self.get_velocity_linker_flags(stage)
            + ["-o", gpu_output_name]
        )
        _run_command([str(c) for c in cmd if c])


def _fix_init_cuda(cuda_source_path: Path, host_source_path: Path) -> None:
    host_cuda_src_pairs = [(host_source_path, cuda_source_path)]

    for cpp_src, cuda_src in host_cuda_src_pairs:
        cuda_inits = {}
        with open(cpp_src) as f:
            for line in f:
                if "int __dace_init_cuda(" in line and line.strip().endswith(";"):
                    key = re.search(r"int __dace_init_cuda\((\w+)", line).group(1)
                    assert key.endswith("_state_t")
                    key = key[:-len("_state_t")]
                    cuda_inits[key] = line.strip().rstrip(";").strip()
                    assert not cuda_inits[key].endswith(";"), f"Expected {cuda_inits[key]} to not end with a semicolon after processing"

        assert len(cuda_inits) == 4

        with open(cuda_src) as f:
            lines = f.readlines()

        with open(cuda_src, "w") as f:
            for line in lines:
                if "int __dace_init_cuda(" in line:
                    key = re.search(r"int __dace_init_cuda\((\w+)", line).group(1)
                    key = key[:-len("_state_t")]
                    assert key in cuda_inits, f"Expected {key} to be in cuda_inits"
                    newline = cuda_inits[key]
                    if line.strip().endswith(";"):
                        newline += ";"
                    elif line.strip().endswith("{"):
                        newline += " {"
                    else:
                        newline += " "
                    line = newline + "\n"
                f.write(line)

def consolidate_generated_code(
    sdfg_includes: list[Path], sdfg_srcs: list[Path], sdfg_cuda_srcs: list[Path], store: Path, stage: int
) -> None:
    """
    Consolidates and post-processes generated C++ code.

    This function takes the generated header and source files, wraps each
    in a unique namespace, and combines them into single `solve_nh_parts.h`
    and `solve_nh_parts.cpp` files in the `store` directory.

    It also performs several post-processing steps:
    - Removes the `__restrict__` keyword.
    - Runs `clang-format` to format the code.
    - Applies specific string replacements to fix pointer dereferencing for
      certain data structures.

    :param sdfg_includes: A list of paths to directories containing generated
                          header files.
    :param sdfg_srcs: A list of paths to generated source files.
    :param store: The directory where the consolidated files will be stored.
    """
    all_headers = {
        f.stem[len("solve_nh_") :]: f.read_text()
        for p in sdfg_includes
        for f in p.glob("solve_nh_*.h")
    }
    all_sources = {f.stem[len("solve_nh_") :]: f.read_text() for f in sdfg_srcs}

    combined_header = "\n".join(
        wrap_namespace(name, content).strip() for name, content in all_headers.items()
    ).replace("__restrict__", "")
    combined_source = "\n".join(
        wrap_namespace(name, content).strip() for name, content in all_sources.items()
    ).replace("__restrict__", "")

    store.mkdir(parents=True, exist_ok=True)
    header_path = store / CONSOLIDATED_HEADER
    source_path = store / CONSOLIDATED_SOURCE
    header_path.write_text(combined_header)
    source_path.write_text(combined_source)

    # Needs to be run before formatting
    if stage >= GPU_STAGE_BEGINS:
        all_cuda_sources = {f.stem[len("solve_nh_") :]: f.read_text() for f in sdfg_cuda_srcs}

        combined_cuda_source = "\n".join(
            wrap_gpu_namespace(name, content).strip() for name, content in all_cuda_sources.items()
        ).replace("__restrict__", "")

        store.mkdir(parents=True, exist_ok=True)
        cuda_source_path = store / CONSOLIDATED_CUDA_SOURCE
        cuda_source_path.write_text(combined_cuda_source)

        _fix_init_cuda(cuda_source_path, source_path)
        _run_command(["clang-format", "-i", str(cuda_source_path)])

    # Format the code once before modifications
    _run_command(["clang-format", "-i", str(header_path), str(source_path)])

    # Apply specific replacements
    replacements = [
        (
            "global_data_type *in_global_data = global_data[0];",
            "global_data_type *in_global_data = global_data;",
        ),
        ("t_int_state *in_p_int = p_int[0];", "t_int_state *in_p_int = p_int;"),
        ("t_patch *in_p_patch = p_patch[0];", "t_patch *in_p_patch = p_patch;"),
        (
            "t_nh_prog *in_p_prog = p_nh_prog_nnew[0];",
            "t_nh_prog *in_p_prog = p_nh_prog_nnew;",
        ),
        (
            "t_nh_prog *in_p_prog = p_nh_prog_nnow[0];",
            "t_nh_prog *in_p_prog = p_nh_prog_nnow;",
        ),
        (
            "t_nh_state *in_p_nh = p_nh[0];",
            "t_nh_state *in_p_nh = p_nh;",
        ),
        ("global_data[0] = out_global_data;", "global_data = out_global_data;"),
        ("p_int[0] = out_p_int;", "p_int = out_p_int;"),
        ("p_patch[0] = out_p_patch;", "p_patch = out_p_patch;"),
        ("p_nh_prog_nnew[0] = out_p_prog;", "p_nh_prog_nnew = out_p_prog;"),
        ("p_nh_prog_nnow[0] = out_p_prog;", "p_nh_prog_nnow = out_p_prog;"),
        ("p_nh[0] = out_p_nh;", "p_nh = out_p_nh;"),
        ("DACE_EXPORTED", ""),
        ("const const", "const"),
        ("t_nh_prog *in_p_nh_prog_nnew = p_nh_prog_nnew[0];",
         "t_nh_prog *in_p_nh_prog_nnew = p_nh_prog_nnew;")
    ]

    # Format again after replacements
    _run_command(["clang-format", "-i", str(header_path), str(source_path)])
    print(f"Consolidated generated code into {header_path} and {source_path}")

    src_content = source_path.read_text()
    for old, new in replacements:
        src_content = src_content.replace(old, new)
    source_path.write_text(src_content)

    header_content = header_path.read_text()
    for old, new in replacements:
        header_content = header_content.replace(old, new)
    header_path.write_text(header_content)

    if stage >= GPU_STAGE_BEGINS:
        # Apply specific replacements
        replacements = [
            ("DACE_EXPORTED", ""),
            ("const const", "const"),
        ]

        # Format again after replacements
        _run_command(["clang-format", "-i", str(cuda_source_path)])

        cuda_src_content = cuda_source_path.read_text()
        for old, new in replacements:
            cuda_src_content = cuda_src_content.replace(old, new)
        cuda_source_path.write_text(cuda_src_content)


def compile_generated_code(
    sdfg_includes: list[Path], sdfg_srcs: list[Path], mode: Mode, stage: int,
) -> None:
    """
    Compiles the generated C++ code into a static library, shared library, or executable.

    This function constructs and executes a compiler command (e.g., `clang++`) to
    compile the provided source files. The compilation is controlled by the
    `mode` parameter, which determines the output type:
    - `Mode.STATIC`: A static library (`.a`).
    - `Mode.SHARED`: A shared library (`.so` or `.dylib`).
    - `Mode.EXEC`: An executable.

    It automatically includes necessary DaCe runtime headers and sets
    various compiler flags for optimization, warnings, and C++ standards.

    :param sdfg_includes: A list of paths to directories containing header files
                          to be included during compilation.
    :param sdfg_srcs: A list of paths to the C++ source files to compile.
    :param mode: The compilation mode, determining the output artifact.
    """
    compiler = Compiler()

    if mode == Mode.STATIC or mode == Mode.SHARED or mode == Mode.EXEC:
        if stage >= GPU_STAGE_BEGINS:
            print(f"Skipping static library compilation for CUDA stage {GPU_STAGE_BEGINS} and above")
        else:
            compiler.compile_object(sdfg_srcs, sdfg_includes, stage)
            # Derive the object file names from the source files
            obj_files = [str(src.with_suffix(".o").name) for src in sdfg_srcs]
            compiler.archive_static_library(obj_files, STATIC_LIB_FILE)
            print(f"Successfully created static library: {STATIC_LIB_FILE}")

    if mode == Mode.SHARED:
        if stage >= GPU_STAGE_BEGINS:
            print(f"Skipping shared library compilation for CUDA stage {GPU_STAGE_BEGINS} and above. Shared library feature needs to be implemented for CUDA stage 4.")
        else:
            compiler.link_shared_library(STATIC_LIB_FILE, SHARED_LIB_FILE, stage)
            print(f"Successfully created shared library: {SHARED_LIB_FILE}")

    if mode == Mode.EXEC:
        if stage >= GPU_STAGE_BEGINS:
            compiler.compile_gpu_executable(
                STANDALONE_MAIN_SRC, sdfg_srcs, sdfg_includes, EXEC_FILE, stage
            )
        else:
            compiler.link_executable(
                STANDALONE_MAIN_SRC, STATIC_LIB_FILE, sdfg_includes, EXEC_FILE, stage
            )
        print(f"Successfully created executable: {EXEC_FILE}")

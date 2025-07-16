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


# --- Constants ---
CC = "clang++" if platform.system() == "Darwin" else "g++"
OBJ_FILE = "solve_nh_parts.o"
STATIC_LIB_FILE = "libsolve_nh_parts.a"
SHARED_LIB_FILE = "libsolve_nh_parts.so"
EXEC_FILE = "verify_solve_nh_parts"
CONSOLIDATED_HEADER = "solve_nh_parts.h"
CONSOLIDATED_SOURCE = "solve_nh_parts.cpp"
STANDALONE_INCLUDE_DIR = Path("include/")
STANDALONE_MAIN_SRC = Path("main.cc")


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
    def __init__(self, cc: str = CC):
        self.cc = cc
        self.diagnosis_flags = self._get_diagnosis_flags()
        self.optimization_flags = self._get_optimization_flags()
        self.standard_flags = self._get_standard_flags()
        self.dace_include = Path(dace.__file__).parent / "runtime/include/"

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

    def _get_optimization_flags(self) -> list[str]:
        return "-O0 -march=native -fno-strict-aliasing -fno-omit-frame-pointer -fno-fast-math -ffp-contract=off".split()

    def _get_standard_flags(self) -> list[str]:
        return "-std=c++23 -fPIC -fopenmp".split()

    def get_base_flags(self) -> list[str]:
        return self.diagnosis_flags + self.optimization_flags + self.standard_flags

    def get_linker_flags(self, mode: Mode) -> list[str]:
        if mode == Mode.SHARED:
            dyn_link = "-dynamiclib" if platform.system() == "Darwin" else "-shared"
            dyn_symbols = (
                "-Wl,-undefined,dynamic_lookup"
                if platform.system() == "Darwin"
                else "-Wl,--unresolved-symbols=ignore-all"
            )
            return [dyn_link, dyn_symbols]
        if mode == Mode.EXEC:
            return [
                "-Wl,-undefined,dynamic_lookup"
                if platform.system() == "Darwin"
                else "-Wl,--unresolved-symbols=ignore-all"
            ]
        return []

    def compile_object(
        self, sources: list[Path], includes: list[Path], output_name: str
    ):
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]
        cmd = (
            [self.cc, "-c"]
            + [str(s) for s in sources]
            + [f"-I{i}" for i in all_includes]
            + self.get_base_flags()
            + ["-o", output_name]
        )
        _run_command([str(c) for c in cmd if c])

    def archive_static_library(self, object_file: str, lib_name: str):
        cmd = ["ar", "rcs", lib_name, object_file]
        _run_command(cmd)

    def link_shared_library(self, static_lib: str, lib_name: str):
        flags = self.get_base_flags() + self.get_linker_flags(Mode.SHARED)
        cmd = [self.cc, static_lib] + flags + ["-o", lib_name]
        _run_command([str(c) for c in cmd if c])

    def link_executable(
        self, main_src: Path, static_lib: str, includes: list[Path], bin_name: str
    ):
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]
        flags = self.get_base_flags() + self.get_linker_flags(Mode.EXEC)
        cmd = (
            [self.cc, str(main_src), static_lib]
            + [f"-I{i}" for i in all_includes]
            + flags
            + ["-o", bin_name]
        )
        _run_command([str(c) for c in cmd if c])


def consolidate_generated_code(
    sdfg_includes: list[Path], sdfg_srcs: list[Path], store: Path
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
    ]

    src_content = source_path.read_text()
    for old, new in replacements:
        src_content = src_content.replace(old, new)
    source_path.write_text(src_content)

    # Format again after replacements
    _run_command(["clang-format", "-i", str(header_path), str(source_path)])

    print(f"Consolidated generated code into {header_path} and {source_path}")


def compile_generated_code(
    sdfg_includes: list[Path], sdfg_srcs: list[Path], mode: Mode
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
        compiler.compile_object(sdfg_srcs, sdfg_includes, OBJ_FILE)
        compiler.archive_static_library(OBJ_FILE, STATIC_LIB_FILE)
        print(f"Successfully created static library: {STATIC_LIB_FILE}")

    if mode == Mode.SHARED:
        compiler.link_shared_library(STATIC_LIB_FILE, SHARED_LIB_FILE)
        print(f"Successfully created shared library: {SHARED_LIB_FILE}")

    if mode == Mode.EXEC:
        compiler.link_executable(
            STANDALONE_MAIN_SRC, STATIC_LIB_FILE, sdfg_includes, EXEC_FILE
        )
        print(f"Successfully created executable: {EXEC_FILE}")

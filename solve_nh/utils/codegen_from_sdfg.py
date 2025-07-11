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
    Generate code from a given SDFG and save it to the specified root directory.

    :param sdfg: The SDFG object to generate code from.
    :param root: The root directory where the generated code will be saved.
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


def consolidate_generated_code(
    sdfg_includes: list[Path], sdfg_srcs: list[Path], store: Path
) -> None:
    """
    Consolidate the generated code for a given SDFG.

    :param sdfg_includes: List of include paths for the SDFG.
    :param sdfg_srcs: List of source files for the SDFG.
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
    (store / "solve_nh_parts.h").write_text(combined_header)
    (store / "solve_nh_parts.cpp").write_text(combined_source)

    CLANG_FORMAT_CMD = [
        "clang-format",
        "-i",
        str(store / "solve_nh_parts.h"),
        str(store / "solve_nh_parts.cpp"),
    ]
    subprocess.run(CLANG_FORMAT_CMD, check=True, env=os.environ.copy())

    src = (
        (store / "solve_nh_parts.cpp")
        .read_text()
        .replace(
            "global_data_type *in_global_data = global_data[0];",
            "global_data_type *in_global_data = global_data;",
        )
        .replace(
            "t_int_state *in_p_int = p_int[0];",
            "t_int_state *in_p_int = p_int;",
        )
        .replace(
            "t_patch *in_p_patch = p_patch[0];",
            "t_patch *in_p_patch = p_patch;",
        )
        .replace(
            "t_nh_prog *in_p_prog = p_nh_prog_nnew[0];",
            "t_nh_prog *in_p_prog = p_nh_prog_nnew;",
        )
        .replace(
            "t_nh_prog *in_p_prog = p_nh_prog_nnow[0];",
            "t_nh_prog *in_p_prog = p_nh_prog_nnow;",
        )
        .replace(
            "global_data[0] = out_global_data;",
            "global_data = out_global_data;",
        )
        .replace(
            "p_int[0] = out_p_int;",
            "p_int = out_p_int;",
        )
        .replace(
            "p_patch[0] = out_p_patch;",
            "p_patch = out_p_patch;",
        )
        .replace(
            "p_nh_prog_nnew[0] = out_p_prog;",
            "p_nh_prog_nnew = out_p_prog;",
        )
    )
    (store / "solve_nh_parts.cpp").write_text(src)
    CLANG_FORMAT_CMD = [
        "clang-format",
        "-i",
        str(store / "solve_nh_parts.h"),
        str(store / "solve_nh_parts.cpp"),
    ]
    subprocess.run(CLANG_FORMAT_CMD, check=True)

    print(
        f"Consolidated generated code into {store / 'solve_nh_parts.h'} and {store / 'solve_nh_parts.cpp'}"
    )


def compile_generated_code_for(
    sdfg_includes: list[Path], sdfg_srcs: list[Path], mode: Mode
) -> None:
    """
    Compile the generated code for a given SDFG.

    :param g: The SDFG object to compile.
    """
    CC = "clang++"

    DACE_INCLUDE = Path(dace.__file__).parent / "runtime/include/"
    STANDALONE_INCLUDE = Path("include/")
    INCLUDES = [
        f"-I{include}" for include in sdfg_includes + [DACE_INCLUDE, STANDALONE_INCLUDE]
    ]

    STANDALONE_SRC = Path("main.cc")
    if mode == Mode.EXEC:
        SOURCES = [STANDALONE_SRC] + sdfg_srcs
    else:
        SOURCES = sdfg_srcs

    if mode == Mode.STATIC:
        BIN = f"verify_solve_nh_parts.o"
    elif mode == Mode.SHARED:
        BIN = f"libverify_solve_nh_parts.so"
    elif mode == Mode.EXEC:
        BIN = f"verify_solve_nh_parts"

    ERRLIMIT_FLAG = "-fmax-errors=1" if CC.startswith("g++") else "-ferror-limit=1"
    CLANG_ONLY_DISABLED_WARNINGS = (
        "-Wno-parentheses-equality -Wno-constant-logical-operand"
        if CC.startswith("clang")
        else ""
    )
    DIAGNOSIS_FLAGS = f"{ERRLIMIT_FLAG} -g -Wall -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-but-set-parameter -Wno-sign-compare {CLANG_ONLY_DISABLED_WARNINGS}".split(
        " "
    )
    OPTIMIZATION_FLAGS = (
        "-O3 -march=native -fno-strict-aliasing -fno-omit-frame-pointer".split(" ")
    )
    STANDARD_FLAGS = "-std=c++23 -fPIC -fopenmp".split(" ")
    if mode in [Mode.EXEC, Mode.SHARED]:
        if platform.system() == "Darwin":
            STANDARD_FLAGS.append("-Wl,-undefined,dynamic_lookup")
        else:
            STANDARD_FLAGS.append("-Wl,--unresolved-symbols=ignore-all")
    if mode == Mode.SHARED:
        STANDARD_FLAGS.append(
            "-dynamiclib" if platform.system() == "Darwin" else "-shared"
        )
    elif mode == Mode.STATIC:
        STANDARD_FLAGS.append("-c")

    FLAGS = DIAGNOSIS_FLAGS + OPTIMIZATION_FLAGS + STANDARD_FLAGS

    COMPILE_COMMAND = list([CC] + SOURCES + INCLUDES + FLAGS + ["-o", BIN])
    COMPILE_COMMAND = [str(x) for x in COMPILE_COMMAND if x]

    print(f"Compiling with command: {' '.join(COMPILE_COMMAND)}")
    output = subprocess.run(COMPILE_COMMAND, capture_output=True, env=os.environ.copy())
    if output.returncode != 0:
        print(f"Compilation failed.")
    else:
        print(
            f"Compilation succeeded. {'Executable' if mode == Mode.EXEC else 'Library'} created: {BIN}"
        )
    print(f"Output: {output.stdout.decode()}")
    print(f"Error: {output.stderr.decode()}")

    if mode == Mode.STATIC:
        LIB = "libverify_solve_nh_parts.a"
        ARCHIVE_COMMAND = f"ar rcs {LIB} {BIN}".split(" ")
        print(f"Archiving with command: {' '.join(ARCHIVE_COMMAND)}")
        output = subprocess.run(
            ARCHIVE_COMMAND, capture_output=True, env=os.environ.copy()
        )
        if output.returncode != 0:
            print(f"Archive failed.")
        else:
            print(f"Archive succeeded. Library created: {LIB}")
        print(f"Output: {output.stdout.decode()}")
        print(f"Error: {output.stderr.decode()}")
    if output.returncode != 0:
        exit(1)

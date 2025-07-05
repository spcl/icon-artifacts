from os import name
import dace
from dace import SDFG
from pathlib import Path
from dace.codegen import codegen, compiler
from dace.sdfg import infer_types
import subprocess
import re


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

    # Join the parts
    header_guard = "\n".join(header_guard_lines)
    includes = "\n".join(include_lines)
    main_content = "\n".join(rest_lines).strip()

    # Wrap main content in namespace
    wrapped = f"""
{header_guard}
{includes}

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
    subprocess.run(CLANG_FORMAT_CMD, check=True)

    print(
        f"Consolidated generated code into {store / 'solve_nh_parts.h'} and {store / 'solve_nh_parts.cpp'}"
    )


def compile_generated_code_for(
    sdfg_includes: list[Path], sdfg_srcs: list[Path]
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
    SOURCES = [STANDALONE_SRC] + sdfg_srcs

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
    FLAGS = DIAGNOSIS_FLAGS + OPTIMIZATION_FLAGS + STANDARD_FLAGS

    COMPILE_COMMAND = list([CC] + SOURCES + INCLUDES + FLAGS + ["-o", BIN])
    COMPILE_COMMAND = [str(x) for x in COMPILE_COMMAND]

    print(f"Compiling with command: {' '.join(COMPILE_COMMAND)}")
    output = subprocess.run(COMPILE_COMMAND, capture_output=True)
    if output.returncode != 0:
        print(f"Compilation failed.")
    else:
        print(f"Compilation succeeded. Executable created: {BIN}")
    print(f"Output: {output.stdout.decode()}")
    print(f"Error: {output.stderr.decode()}")
    if output.returncode != 0:
        exit(1)

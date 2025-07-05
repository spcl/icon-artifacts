import dace
from dace import SDFG
from pathlib import Path
from dace.codegen import codegen, compiler
from dace.sdfg import infer_types
import subprocess


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


def compile_generated_code_for(sdfg_includes: list[Path], sdfg_srcs: list[Path]) -> None:
    """
    Compile the generated code for a given SDFG.

    :param g: The SDFG object to compile.
    """
    CC = "g++-15"

    DACE_INCLUDE = Path(dace.__file__).parent / "runtime/include/"
    STANDALONE_INCLUDE = Path("include/")
    INCLUDES = [
        f"-I{include}" for include in sdfg_includes + [DACE_INCLUDE, STANDALONE_INCLUDE]
    ]

    STANDALONE_SRC = Path("main.cc")
    SOURCES = [STANDALONE_SRC] + sdfg_srcs

    BIN = f"verify_solve_nh_parts"

    DIAGNOSIS_FLAGS = "-fmax-errors=1 -g -Wall -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-but-set-parameter -Wno-sign-compare".split(
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

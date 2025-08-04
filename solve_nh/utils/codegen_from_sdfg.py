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


class ArtifactMode(Enum):
    STATIC = "static"
    SHARED = "shared"
    EXEC = "exec"

    def __str__(self) -> str:
        return self.value


class OptimizationMode(Enum):
    DEBUG = "debug"
    RELEASE = "release"


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
        if in_header_guard and any(stripped.startswith(p) for p in ["#ifndef", "#define", "#endif"]):
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
        if in_header_guard and any(stripped.startswith(p) for p in ["#ifndef", "#define", "#endif"]):
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
    """
    Manages compilation and linking of C++ and CUDA code generated by DaCe.

    This class encapsulates the logic for determining compiler flags based on
    optimization mode (debug/release) and target artifact (static lib, shared lib, executable).
    It supports both CPU (C++) and GPU (CUDA) compilation stages.
    """

    def __init__(self, cc: str = CC, nvcc: str = NVCC, optmode: OptimizationMode = OptimizationMode.DEBUG):
        """
        Initializes the Compiler with specified compilers and optimization mode.

        :param cc: The C++ compiler executable (e.g., 'g++', 'clang++').
        :param nvcc: The CUDA compiler executable (e.g., 'nvcc').
        :param optmode: The optimization mode (DEBUG or RELEASE). This influences
                        the set of compiler and linker flags used. Defaults to DEBUG.
        """
        self.cc = cc
        self.nvcc = nvcc
        self.optmode = optmode
        # Paths are derived/accessed directly within methods, not passed via init
        self.dace_include = (
            Path(dace.__file__).parent / "runtime/include/"
        )  # Points to DaCe's internal runtime headers.
        self.cuda_arch = os.getenv("CUDA_ARCH", "native")  # Target CUDA architecture, 'native' by default.

    def _get_diagnosis_flags_cpp(self) -> list[str]:
        """
        Returns a list of C++ compiler flags for diagnostics and warnings.
        Includes debug information (`-g`) only if `optmode` is DEBUG.
        """
        # Limit compilation errors to speed up initial feedback.
        errlimit_flag = "-fmax-errors=1" if self.cc.startswith("g++") else "-ferror-limit=1"

        flags = [
            "-Wall",  # Enable all common warnings.
            "-Wextra",  # Enable extra warnings not covered by -Wall.
            "-Wno-unused-parameter",  # Don't warn about unused function parameters.
            "-Wno-unused-variable",  # Don't warn about unused local variables.
            "-Wno-unused-function",  # Don't warn about unused static functions.
            "-Wno-unused-but-set-variable",  # Don't warn about variables set but not used.
            "-Wno-unused-but-set-parameter",  # Don't warn about parameters set but not used.
            "-Wno-sign-compare",  # Don't warn about signed/unsigned comparison mismatches.
        ]

        # Clang-specific warning suppressions for compatibility/noise reduction.
        if self.cc.startswith("clang"):
            flags.extend(
                [
                    "-Wno-parentheses-equality",  # Don't warn about equality comparisons in parentheses.
                    "-Wno-constant-logical-operand",  # Don't warn about logical operations with constant operands.
                ]
            )

        if self.optmode == OptimizationMode.DEBUG:
            flags.append("-g")  # Add debug symbols in debug mode.

        return [errlimit_flag] + flags

    def _get_diagnosis_flags_cuda(self) -> list[str]:
        """
        Returns a list of CUDA compiler flags for diagnostics and warnings.
        These flags are passed to the host C++ compiler via -Xcompiler=.
        Includes debug information (`-G`) for device code only if `optmode` is DEBUG.
        """
        # Limit host compiler errors.
        errlimit_flag = "-Xcompiler=-fmax-errors=1" if self.cc.startswith("g++") else "-Xcompiler=-ferror-limit=1"

        flags = [
            "-Xcompiler=-Wall",  # Host: All common warnings.
            "-Xcompiler=-Wextra",  # Host: Extra warnings.
            "-Xcompiler=-Wno-unused-parameter",  # Host: Suppress unused parameter warnings.
            "-Xcompiler=-Wno-unused-variable",  # Host: Suppress unused variable warnings.
            "-Xcompiler=-Wno-unused-function",  # Host: Suppress unused function warnings.
            "-Xcompiler=-Wno-unused-but-set-variable",  # Host: Suppress variables set but not used.
            "-Xcompiler=-Wno-unused-but-set-parameter",  # Host: Suppress parameters set but not used.
            "-Xcompiler=-Wno-sign-compare",  # Host: Suppress signed/unsigned comparison warnings.
            "-Wno-deprecated-declarations",  # CUDA: Suppress warnings for deprecated CUDA API usage.
        ]

        # Clang-specific warning suppressions for the host compiler.
        if self.cc.startswith("clang"):
            flags.extend(["-Xcompiler=-Wno-parentheses-equality", "-Xcompiler=-Wno-constant-logical-operand"])

        if self.optmode == OptimizationMode.DEBUG:
            flags.append("-Xcompiler=-g")  # Host debug symbols.
            flags.append("-G")  # Device debug symbols (enables CUDA-GDB for kernel debugging).

        return [errlimit_flag] + flags

    def _get_optimization_flags_cpp(self) -> list[str]:
        """
        Returns a list of C++ compiler flags for optimization, based on `self.optmode`.
        """
        if self.optmode == OptimizationMode.DEBUG:
            return [
                "-O0",  # No optimization, crucial for effective debugging.
                "-fno-strict-aliasing",  # Disables aggressive alias analysis, safer for complex pointer usage.
                "-fno-omit-frame-pointer",  # Keeps frame pointers, essential for proper stack traces in debuggers.
                "-fno-fast-math",  # Ensures strict IEEE 754 compliance for floating-point operations.
                "-ffp-contract=off",  # Disables Fused Multiply-Add (FMA) instructions for precision.
            ]
        elif self.optmode == OptimizationMode.RELEASE:
            return [
                "-O3",  # Aggressive optimizations for maximum performance.
                "-march=native",  # Optimize for the CPU architecture where compilation occurs.
                "-fstrict-aliasing",  # Enables aggressive alias analysis for potentially faster code.
                "-fomit-frame-pointer",  # Omits frame pointers to free a register (minor speedup, harder debugging).
                "-ffast-math",  # Enables less strict floating-point optimizations (speed over strict IEEE 754).
                "-ffp-contract=fast",  # Enables Fused Multiply-Add (FMA) instructions for performance.
            ]
        return []

    def _get_optimization_flags_cuda(self) -> list[str]:
        """
        Returns a list of CUDA compiler flags for optimization, based on `self.optmode`.
        These include both host compiler options and device code options.
        """
        if self.optmode == OptimizationMode.DEBUG:
            return [
                "-O0",  # Host compiler: No optimization.
                "-Xcompiler=-O0",  # Host compiler: No optimization.
                "-Xcompiler=-march=native",  # Host compiler: Optimize for current CPU.
                "-Xcompiler=-fno-strict-aliasing",  # Host compiler: Safer aliasing.
                "-Xcompiler=-fno-omit-frame-pointer",  # Host compiler: Keeps frame pointers.
                "-Xcompiler=-fno-fast-math",  # Host compiler: Strict FP math.
                "-Xcompiler=-ffp-contract=off",  # Host compiler: Disable FMA.
                "--fmad=false",  # Device: Disable Fused Multiply-Add (FMA) for debug precision.
                "--prec-div=true",  # Device: Use higher precision for division.
                "--prec-sqrt=true",  # Device: Use higher precision for square root.
                "--ftz=false",  # Device: Disable Flush-to-Zero for denormalized numbers (precision).
            ]
        elif self.optmode == OptimizationMode.RELEASE:
            return [
                "-O3",  # Host compiler: Aggressive optimizations.
                "-Xcompiler=-O3",  # Host compiler: Aggressive optimizations.
                "-Xcompiler=-march=native",  # Host compiler: Optimize for current CPU.
                "-Xcompiler=-fstrict-aliasing",  # Host compiler: Strict aliasing.
                "-Xcompiler=-fomit-frame-pointer",  # Host compiler: Omit frame pointers.
                "-Xcompiler=-ffast-math",  # Host compiler: Fast FP math.
                "-Xcompiler=-ffp-contract=on",  # Host compiler: Enable FMA.
                "-lineinfo",  # Device: Include line information in the device binary for profiling.
                "--fmad=true",  # Device: Enable Fused Multiply-Add (FMA) for performance.
                "--prec-div=false",  # Device: Use less precise (faster) division.
                "--prec-sqrt=false",  # Device: Use less precise (faster) square root.
                "--ftz=true",  # Device: Enable Flush-to-Zero for denormalized numbers (performance).
                "-Xptxas=-O3",  # Device: Pass -O3 to PTXAS (PTX assembler) for aggressive optimization.
                "-Xptxas=-v",  # Device: Pass -v to PTXAS for verbose output.
                "--restrict",  # Device: Treat pointers as restricted, enabling no-aliasing optimizations.
            ]
        return []

    def _get_standard_flags_cpp(self) -> list[str]:
        """
        Returns standard C++ compiler flags that apply broadly (e.g., PIC, OpenMP).
        """
        return [
            "-fPIC",  # Generate Position-Independent Code, essential for shared libraries.
            "-pthread",
            # DISABLED: No OpenMP for us.
            # "-fopenmp",  # Enable OpenMP directives for parallel processing.
        ]

    def _get_standard_flags_cuda(self) -> list[str]:
        """
        Returns standard CUDA compiler flags.
        Includes host compiler flags and device code generation flags (e.g., architecture).
        """
        # Host compiler flags are passed to the underlying C++ compiler via -Xcompiler.
        host_flags = [
            "-Xcompiler=-fPIC",  # Host: Generate Position-Independent Code.
            "-Xcompiler=-pthread",  # Host: Enable pthread.
            # DISABLED: No OpenMP for us.
            # "-Xcompiler=-fopenmp",  # Host: Enable OpenMP.
        ]

        # Device architecture flags:
        arch_flags = []
        if self.cuda_arch == "native":
            arch_flags.append("-arch=native")  # If 'native', nvcc targets host's GPU directly.
        else:
            # Assumes CUDA_ARCH is 'sm_XX'. Generates SASS for specific GPU and PTX for future compatibility.
            compute_version_num = self.cuda_arch[3:]  # Extract 'XX' from 'sm_XX' (e.g., '86').
            compute_version = f"compute_{compute_version_num}"  # Example: 'compute_86'.
            sm_version = f"sm_{compute_version_num}"  # Example: 'sm_86'.
            arch_flags.append(f"-gencode=arch={compute_version},code={sm_version}")  # Generate SASS.
            arch_flags.append(f"-gencode=arch={compute_version},code={compute_version}")  # Generate PTX.

        # Other CUDA specific flags:
        cuda_specific_flags = [
            "--expt-relaxed-constexpr",  # Allow more liberal use of `constexpr` in device code.
            "-Xcompiler=-fno-var-tracking-assignments",  # Host: Helps with debugger issues or certain optimizations.
            "-rdc=true",  # Relocatable Device Code: Essential for linking multiple CUDA object files.
            "-DGPU",  # Define preprocessor macro 'GPU' for conditional compilation.
            "--relocatable-device-code=true",  # Redundant with -rdc=true, but kept for legacy/clarity.
        ]

        return host_flags + arch_flags + cuda_specific_flags

    def _get_cpp_standard_flags(self) -> list[str]:
        """
        Returns flags for the C++ standard version (e.g., C++20).
        """
        return ["-std=c++20"]  # Enforce C++20 standard.

    def get_base_flags_cpp(self) -> list[str]:
        """
        Combines all C++ compiler flags (diagnosis, optimization, standard C++ features).
        Flags are recomputed on each call to reflect potential dynamic changes (though unlikely with current design).
        """
        return self._get_diagnosis_flags_cpp() + self._get_optimization_flags_cpp() + self._get_standard_flags_cpp()

    def get_base_flags_cuda(self) -> list[str]:
        """
        Combines all CUDA compiler flags (diagnosis, optimization, standard CUDA features).
        Flags are recomputed on each call to reflect potential dynamic changes.
        """
        return self._get_diagnosis_flags_cuda() + self._get_standard_flags_cuda() + self._get_optimization_flags_cuda()

    def _get_cuda_src_file_flag(self) -> str:
        """
        Returns the flag to explicitly tell nvcc to treat an input file as CUDA source.
        This is useful when source files might not have a typical '.cu' extension.
        """
        return "-x=cu"

    def get_velocity_linker_flags(self, stage: int) -> list[str]:
        """
        Determines linker flags for the 'velocity' library based on the compilation stage.
        Looks for pre-existing library files in the current directory.

        :param stage: The numerical stage of the compilation, used to find the correct
                      'velocity' library version (e.g., libvelocity_3.so).
        :return: A list of linker flags (e.g., -L., -lvelocity_X, -rpath) if the library
                 is found, otherwise an empty list.
        """
        # Search for existence of velocity library files intended for this stage
        lib_extensions = [".so", ".dylib", ".a"]  # Common shared library extensions.
        potential_lib_names = [f"libvelocity_{stage}{ext}" for ext in lib_extensions]

        if any(Path(name).exists() for name in potential_lib_names):  # Check if any matching library exists.
            # rpath_flag: Ensures the dynamic linker finds the shared library at runtime.
            # -Xcompiler="..." is used by nvcc to pass linker options to the host linker.
            rpath_flag = '-Xcompiler="-Wl,-rpath,."' if stage >= GPU_STAGE_BEGINS else "-Wl,-rpath,."
            return [
                "-L.",  # Add current directory to library search path.
                f"-lvelocity_{stage}",  # Link against 'libvelocity_X' (e.g., libvelocity_3).
                rpath_flag,
            ]
        else:
            return []

    def get_linker_flags_artifact_mode(self, mode: ArtifactMode) -> list[str]:
        """
        Returns specific linker flags based on the target artifact mode (shared library, executable).

        :param mode: The target artifact mode (STATIC, SHARED, EXEC).
        :return: A list of linker flags.
        """
        flags = []
        if mode == ArtifactMode.SHARED:
            flags.append(
                "-dynamiclib" if platform.system() == "Darwin" else "-shared"
            )  # Specifies shared library output.
            flags.append(
                "-Wl,-undefined,dynamic_lookup"  # macOS: Allows symbols to be resolved at runtime.
                if platform.system() == "Darwin"
                else "-Wl,--unresolved-symbols=ignore-all"  # Linux: Very permissive, allows linking with missing symbols.
            )

        return flags

    def get_gpu_linker_flags(self) -> list[str]:
        return ["-shared"]

    def compile_object(self, sources: list[Path], includes: list[Path], stage: int = 0):
        """
        Compiles C++ source files into object files.
        This method is designed for CPU (C++) compilation. GPU stage compilation for library
        objects is currently not supported via this specific method (handled by nvcc linking).

        :param sources: A list of paths to C++ source files (.cpp, .cc).
        :param includes: A list of additional directories to search for header files.
        :param stage: The compilation stage. If `stage >= GPU_STAGE_BEGINS`, an exception
                      is raised as this method is for CPU compilation.
        :raises Exception: If `stage` indicates a GPU compilation stage.
        """
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]  # Global include path.
        if stage >= GPU_STAGE_BEGINS:
            raise Exception(
                "GPU stage compilation for individual library objects is not supported by `compile_object`. "
                "GPU code is typically compiled and linked as part of a larger unit using `nvcc`."
            )
        else:
            cmd = (
                [self.cc, "-c"]  # Compile source files into object files without linking.
                + [str(s) for s in sources]  # List of source files.
                + [f"-I{i}" for i in all_includes]  # Add include directories.
                + self.get_base_flags_cpp()  # Base C++ compiler flags (diagnosis, optimization, standard).
                + self._get_cpp_standard_flags()  # C++ standard version flag.
            )
            _run_command([str(c) for c in cmd if c])  # Execute the compilation command.

    def archive_static_library(self, obj_files: list[str], lib_name: str):
        """
        Archives compiled object files into a static library (.a file).
        Static libraries are collections of object files that are copied directly
        into the final executable during the linking phase.

        :param obj_files: A list of paths (as strings) to object files (.o) to be archived.
        :param lib_name: The desired output name for the static library (e.g., 'libmylib.a').
        """
        cmd = [
            "ar",  # The archiver utility.
            "rcs",  # 'r': insert/replace, 'c': create if not exists, 's': write/update index.
            lib_name,
        ] + obj_files
        _run_command(cmd)

    def link_shared_library(self, static_lib: str, lib_name: str, stage: int):
        """
        Links a static library or object files into a shared library (.so or .dylib).
        Shared libraries are loaded into memory at runtime and can be shared by multiple programs.

        :param static_lib: Path (as string) to the static library or object file to link.
        :param lib_name: The desired output name for the shared library.
        :param stage: The compilation stage, which determines whether to use the C++
                      compiler (`cc`) or CUDA compiler (`nvcc`) and relevant flags.
        """
        compiler_exe = self.nvcc if stage >= GPU_STAGE_BEGINS else self.cc  # Select compiler based on stage.
        base_flags = (
            self.get_base_flags_cuda()
            if stage >= GPU_STAGE_BEGINS  # Get base CUDA flags.
            else self.get_base_flags_cpp()
        )  # Get base C++ flags.

        flags = (
            base_flags
            + self.get_linker_flags_artifact_mode(ArtifactMode.SHARED)  # Specific linker flags for shared library.
            + self.get_velocity_linker_flags(stage)  # Linker flags for external 'velocity' library.
            + self._get_cpp_standard_flags()  # C++ standard flag (for host code, even with nvcc).
        )

        cmd = [compiler_exe, static_lib] + flags + ["-o", lib_name]  # Output to specified library name.
        _run_command([str(c) for c in cmd if c])  # Execute the linking command.

    def link_executable(self, main_src: Path, static_lib: str, includes: list[Path], bin_name: str, stage: int):
        """
        Links a static library with a main source file to create an executable.

        :param main_src: Path to the main source file (e.g., 'main.cc' or 'main.cu').
        :param static_lib: Path (as string) to the static library to link.
        :param includes: A list of additional directories to search for header files.
        :param bin_name: The desired output name for the executable.
        :param stage: The compilation stage, which determines whether to use the C++
                      compiler (`cc`) or CUDA compiler (`nvcc`) and relevant flags.
        """
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]  # Global include path.
        compiler_exe = self.nvcc if stage >= GPU_STAGE_BEGINS else self.cc  # Select compiler.
        base_flags = (
            self.get_base_flags_cuda()
            if stage >= GPU_STAGE_BEGINS  # Get base CUDA flags.
            else self.get_base_flags_cpp()
        )  # Get base C++ flags.

        flags = (
            base_flags
            + self.get_linker_flags_artifact_mode(ArtifactMode.EXEC)  # Specific linker flags for executable.
            + self.get_velocity_linker_flags(stage)  # Linker flags for external 'velocity' library.
            + self._get_cpp_standard_flags()  # C++ standard flag.
        )

        cmd = [compiler_exe, str(main_src), static_lib] + [f"-I{i}" for i in all_includes] + flags + ["-o", bin_name]
        _run_command([str(c) for c in cmd if c])  # Execute the linking command.

    def compile_gpu_executable(
        self,
        main_src: Path,
        host_sources: list[Path],
        includes: list[Path],
        gpu_output_name: str,
        stage: int = 0,
    ):
        """
        Compiles and links CUDA (GPU) source files into a single executable.
        This method specifically targets GPU compilation with `nvcc`.

        :param main_src: Path to the primary source file for the executable (e.g., 'main.cu').
        :param host_sources: A list of paths to additional C++ or CUDA source files
                             that should be compiled as part of the executable.
        :param includes: A list of additional directories to search for header files.
        :param gpu_output_name: The desired output name for the GPU executable.
        :param stage: The compilation stage. Must be `>= GPU_STAGE_BEGINS` as this
                      method is for GPU compilation.
        :raises AssertionError: If `stage` is less than `GPU_STAGE_BEGINS`.
        """
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]  # Global include path.
        assert stage >= GPU_STAGE_BEGINS, f"GPU stage compilation requires stage >= {GPU_STAGE_BEGINS}"

        gen_sources = []
        for s in [main_src] + host_sources:
            gen_sources.append(self._get_cuda_src_file_flag())  # Explicitly tell nvcc to treat them as .cu files.
            gen_sources.append(str(s))

        flags = (
            self.get_base_flags_cuda()  # Get all base CUDA compiler flags.
            + self.get_linker_flags_artifact_mode(ArtifactMode.EXEC)  # Specific linker flags for executable.
            + self.get_velocity_linker_flags(stage)  # Linker flags for external 'velocity' library.
            + self._get_cpp_standard_flags()  # C++ standard flag, applied to host code by nvcc.
        )

        cmd = [self.nvcc] + gen_sources + [f"-I{i}" for i in all_includes] + flags + ["-o", gpu_output_name]
        _run_command([str(c) for c in cmd if c])

    def compile_gpu_shared_lib(
        self,
        host_sources: list[Path],
        includes: list[Path],
        gpu_output_name: str,
        stage: int = 0,
    ):
        """
        Compiles and links CUDA (GPU) source files into a single shared library.
        This method specifically targets GPU compilation with `nvcc`.
        """
        all_includes = includes + [self.dace_include, STANDALONE_INCLUDE_DIR]  # Global include path.
        assert stage >= GPU_STAGE_BEGINS, f"GPU stage compilation requires stage >= {GPU_STAGE_BEGINS}"

        gen_sources = []
        for s in host_sources:
            gen_sources.append(self._get_cuda_src_file_flag())  # Explicitly tell nvcc to treat them as .cu files.
            gen_sources.append(str(s))

        flags = (
            self.get_base_flags_cuda()  # Get all base CUDA compiler flags.
            + ["-DDYCORE_GPU_INTEGRATION"]
            + self.get_gpu_linker_flags()  # Specific linker flags for shared library.
            + self.get_velocity_linker_flags(stage)  # Linker flags for external 'velocity' library.
            + self._get_cpp_standard_flags()  # C++ standard flag, applied to host code by nvcc.
        )

        cmd = [self.nvcc] + gen_sources + [f"-I{i}" for i in all_includes] + flags + ["-o", gpu_output_name]
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
                    key = key[: -len("_state_t")]
                    cuda_inits[key] = line.strip().rstrip(";").strip()
                    assert not cuda_inits[key].endswith(";"), (
                        f"Expected {cuda_inits[key]} to not end with a semicolon after processing"
                    )

        assert len(cuda_inits) == 4

        with open(cuda_src) as f:
            lines = f.readlines()

        with open(cuda_src, "w") as f:
            for line in lines:
                if "int __dace_init_cuda(" in line:
                    key = re.search(r"int __dace_init_cuda\((\w+)", line).group(1)
                    key = key[: -len("_state_t")]
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
    all_headers = {f.stem[len("solve_nh_") :]: f.read_text() for p in sdfg_includes for f in p.glob("solve_nh_*.h")}
    all_sources = {f.stem[len("solve_nh_") :]: f.read_text() for f in sdfg_srcs}

    combined_header = "\n".join(wrap_namespace(name, content).strip() for name, content in all_headers.items()).replace(
        "**__restrict__", "*__restrict *__restrict__"
    )
    combined_source = "\n".join(wrap_namespace(name, content).strip() for name, content in all_sources.items()).replace(
        "**__restrict__", "*__restrict *__restrict__"
    )

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
        ).replace("**__restrict__", "*__restrict *__restrict__")

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
        ("t_nh_prog *in_p_nh_prog_nnow = p_nh_prog_nnow[0];", "t_nh_prog *in_p_nh_prog_nnow = p_nh_prog_nnow;"),
        ("t_nh_prog *in_p_nh_prog_nnew = p_nh_prog_nnew[0];", "t_nh_prog *in_p_nh_prog_nnew = p_nh_prog_nnew;"),
        (
            "t_nh_prog *in_p_prog = p_nh_prog_nnew[0];",
            "t_nh_prog *in_p_prog = p_nh_prog_nnew;",
        ),
        (
            "t_nh_prog *in_p_prog = p_nh_prog_nnow[0];",
            "t_nh_prog *in_p_prog = p_nh_prog_nnow;",
        ),
        (
            "t_nh_prog *in_p_prog_nnew = p_nh_prog_nnew[0];",
            "t_nh_prog *in_p_prog_nnew = p_nh_prog_nnew;",
        ),
        (
            "t_nh_prog *in_p_prog_nnow = p_nh_prog_nnow[0];",
            "t_nh_prog *in_p_prog_nnow = p_nh_prog_nnow;",
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
        ("t_nh_prog *in_p_nh_prog_nnew = p_nh_prog_nnew[0];", "t_nh_prog *in_p_nh_prog_nnew = p_nh_prog_nnew;"),
        ("new double DACE_ALIGN(64)", "new (std::align_val_t(64)) double"),
        ("new int DACE_ALIGN(64)", "new (std::align_val_t(64)) int"),
        ("new float DACE_ALIGN(64)", "new (std::align_val_t(64)) float"),
        ("new uint16_t DACE_ALIGN(64)", "new (std::align_val_t(64)) uint16_t"),
        ("new unsigned char DACE_ALIGN(64)", "new (std::align_val_t(64)) unsigned char"),
        ("new double DACE_ALIGN(\n    64)", "new (std::align_val_t(64)) double"),
        ("new int DACE_ALIGN(\n    64)", "new (std::align_val_t(64)) int"),
        ("new float DACE_ALIGN(\n    64)", "new (std::align_val_t(64)) float"),
        ("new uint16_t DACE_ALIGN(\n    64)", "new (std::align_val_t(64)) uint16_t"),
        ("new unsigned char DACE_ALIGN(\n    64)", "new (std::align_val_t(64)) unsigned char"),
        (
            "DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));",
            "// disabled: DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));",
        ),
        ("__state->gpu_context->streams[0]", "nullptr"),
    ]
    _run_command(["clang-format", "-i", str(header_path), str(source_path)])
    print(f"Consolidated generated code into {header_path} and {source_path}")

    src_content = source_path.read_text()
    for old, new in replacements:
        src_content = src_content.replace(old, new)
    # Then, we need to put back `extern "C"` for the actual interface functions.
    for x in ["predictor_pre", "predictor_post", "corrector_pre", "corrector_post"]:
        for look_for in [f"solve_nh_{x}_state_t *__dace_init_solve_nh_{x}(", f"void __program_solve_nh_{x}(", f"int __dace_exit_solve_nh_{x}("]:
            src_content = src_content.replace(look_for, f'extern "C" {look_for}')
    # TODO: WHY DOES CODEGEN DO THIS TO US???
    src_content = src_content.replace(
        "const double *__restrict__ gpu___CG_p_nh__CG_diag__m_mass_fl_e",
        "double *__restrict__ gpu___CG_p_nh__CG_diag__m_mass_fl_e"
    )
    source_path.write_text(src_content)
    _run_command(["clang-format", "-i", str(source_path)])

    header_content = header_path.read_text()
    for old, new in replacements:
        header_content = header_content.replace(old, new)
    # Then, we need to put back `extern "C"` for the actual interface functions.
    for x in ["predictor_pre", "predictor_post", "corrector_pre", "corrector_post"]:
        for look_for in [f"solve_nh_{x}_state_t *__dace_init_solve_nh_{x}(", f"void __program_solve_nh_{x}(", f"int __dace_exit_solve_nh_{x}("]:
            header_content = header_content.replace(look_for, f'extern "C" {look_for}')
    header_path.write_text(header_content)
    _run_command(["clang-format", "-i", str(header_path)])

    if stage >= GPU_STAGE_BEGINS:
        # Apply specific replacements
        replacements = [
            ("DACE_EXPORTED", ""),
            ("const const", "const"),
            ("__state->gpu_context->streams[0]", "nullptr"),
        ]

        cuda_src_content = cuda_source_path.read_text()
        for old, new in replacements:
            cuda_src_content = cuda_src_content.replace(old, new)
        # TODO: WHY DOES CODEGEN DO THIS TO US???
        cuda_src_content = cuda_src_content.replace(
            "const double *__restrict__ gpu___CG_p_nh__CG_diag__m_mass_fl_e",
            "double *__restrict__ gpu___CG_p_nh__CG_diag__m_mass_fl_e"
        )
        cuda_source_path.write_text(cuda_src_content)
        _run_command(["clang-format", "-i", str(cuda_source_path)])


def compile_generated_code(
    sdfg_includes: list[Path],
    sdfg_srcs: list[Path],
    artifact_mode: ArtifactMode,
    optimization_mode: OptimizationMode,
    stage: int,
) -> None:
    """
    Compiles the generated C++ code into a static library, shared library, or executable.

    This function constructs and executes a compiler command (e.g., `clang++`) to
    compile the provided source files. The compilation is controlled by the
    `mode` parameter, which determines the output type:
    - `ArtifactMode.STATIC`: A static library (`.a`).
    - `ArtifactMode.SHARED`: A shared library (`.so` or `.dylib`).
    - `ArtifactMode.EXEC`: An executable.

    It automatically includes necessary DaCe runtime headers and sets
    various compiler flags for optimization, warnings, and C++ standards.

    :param sdfg_includes: A list of paths to directories containing header files
                          to be included during compilation.
    :param sdfg_srcs: A list of paths to the C++ source files to compile.
    :param mode: The compilation mode, determining the output artifact.
    """
    compiler = Compiler(optmode=optimization_mode)

    if artifact_mode in [ArtifactMode.EXEC, ArtifactMode.STATIC, ArtifactMode.SHARED]:
        if stage >= GPU_STAGE_BEGINS:
            print(f"Skipping static library compilation for CUDA stage {GPU_STAGE_BEGINS} and above")
        else:
            compiler.compile_object(sdfg_srcs, sdfg_includes, stage)
            # Derive the object file names from the source files
            obj_files = [str(src.with_suffix(".o").name) for src in sdfg_srcs]
            compiler.archive_static_library(obj_files, STATIC_LIB_FILE)
            print(f"Successfully created static library: {STATIC_LIB_FILE}")

    if artifact_mode == ArtifactMode.SHARED:
        if stage >= GPU_STAGE_BEGINS:
            compiler.compile_gpu_shared_lib(sdfg_srcs, sdfg_includes, SHARED_LIB_FILE, stage)
        else:
            compiler.link_shared_library(STATIC_LIB_FILE, SHARED_LIB_FILE, stage)
            print(f"Successfully created shared library: {SHARED_LIB_FILE}")

    if artifact_mode == ArtifactMode.EXEC:
        if stage >= GPU_STAGE_BEGINS:
            compiler.compile_gpu_executable(STANDALONE_MAIN_SRC, sdfg_srcs, sdfg_includes, EXEC_FILE, stage)
        else:
            compiler.link_executable(STANDALONE_MAIN_SRC, STATIC_LIB_FILE, sdfg_includes, EXEC_FILE, stage)
        print(f"Successfully created executable: {EXEC_FILE}")

from pathlib import Path
import dace
from dace import SDFG
from utils.unique_names import unique_names
from utils.codegen_from_sdfg import (
    generate_code_from_sdfg,
    compile_generated_code_for,
    consolidate_generated_code,
)

STARTER_SDFG_FILES = [
    "solve_nh_predictor_pre.sdfgz",
    "solve_nh_predictor_post.sdfgz",
    "solve_nh_corrector_pre.sdfgz",
    "solve_nh_corrector_post.sdfgz",
]

DEFAULT_CODEGEN_DIR = "codegen"


def sdfg_names(verify: bool = False) -> list[str]:
    if verify:
        for f in STARTER_SDFG_FILES:
            assert Path(f).exists()
    return list(sorted(Path(f).stem for f in STARTER_SDFG_FILES))


def stage_input(name: str, stage: int, codegen_dir=DEFAULT_CODEGEN_DIR) -> str:
    if stage > 0:
        return f"{codegen_dir}/gpu_{name}_stage{stage - 1}.sdfgz"
    else:
        starter_map = {Path(f).stem: f for f in STARTER_SDFG_FILES}
        assert name in starter_map
        return starter_map[name]


def stage_output(name: str, stage: int, codegen_dir=DEFAULT_CODEGEN_DIR) -> str:
    return f"{codegen_dir}/gpu_{name}_stage{stage}.sdfgz"


def stage_inputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR) -> dict[str, str]:
    return {name: stage_input(name, stage, codegen_dir) for name in sdfg_names()}


def stage_outputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR) -> dict[str, str]:
    return {name: stage_output(name, stage, codegen_dir) for name in sdfg_names()}


def canonicalize_sdfgs(
    stage: int,
    sdfgs: dict[str, SDFG],
) -> None:
    sdfgs = list(sdfgs.values())
    # Avoid name conflicts.
    unique_names(sdfgs)


def populate_build_folders(
    stage: int,
    sdfgs: dict[str, SDFG],
) -> None:
    for name, g in sdfgs.items():
        g.build_folder = f"{DEFAULT_CODEGEN_DIR}/stage{stage}/{name}"


def codegen_action(
    stage: int,
    sdfgs: dict[str, SDFG],
) -> None:
    dace.config.Config.set("compiler", "cuda", "max_concurrent_streams", value="10")
    dace.config.Config.set("compiler", "cuda", "default_block_size", value="256,1,1")
    dace.config.Config.set("compiler", "default_data_types", value="C")

    populate_build_folders(stage, sdfgs)
    for _, g in sdfgs.items():
        generate_code_from_sdfg(g)
    SDFG_INCLUDES = [Path(g.build_folder) / "include/" for _, g in sdfgs.items()]
    SDFG_SRCS = [
        Path(g.build_folder) / "src/cpu" / f"{g.name}.cpp" for _, g in sdfgs.items()
    ]
    consolidate_generated_code(
        SDFG_INCLUDES, SDFG_SRCS, Path(f"{DEFAULT_CODEGEN_DIR}/stage{stage}")
    )


def compile_action(stage: int) -> None:
    SDFG_INCLUDES = [Path(f"{DEFAULT_CODEGEN_DIR}/stage{stage}")]
    SDFG_SRCS = [Path(f"{DEFAULT_CODEGEN_DIR}/stage{stage}") / "solve_nh_parts.cpp"]

    compile_generated_code_for(SDFG_INCLUDES, SDFG_SRCS)

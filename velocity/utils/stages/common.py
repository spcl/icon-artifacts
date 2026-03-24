from pathlib import Path
from typing import Dict
import dace
import utils.stages.common as common
import utils.config as config
from utils.reductions import add_all_reductions
from utils.unique_names import unique_names
from utils.benchmark_sdfg import instrument_sdfg
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
from utils.make_flattened_data_to_input import make_flattened_data_to_non_transient_cpu_input, make_flattened_data_to_non_transient_gpu_input
import os

dace.config.Config.set('compiler', 'cuda', 'max_concurrent_streams', value="10")
dace.config.Config.set('compiler', 'cuda', 'default_block_size', value="256,1,1")
dace.config.Config.set('compiler', 'default_data_types', value='C')

STARTER_SDFG_FILES = [
    "velocity_no_nproma_if_prop_lvn_only_0_istep_1.sdfgz",
    "velocity_no_nproma_if_prop_lvn_only_1_istep_1.sdfgz",
    "velocity_no_nproma_if_prop_lvn_only_1_istep_2.sdfgz",
    "velocity_no_nproma_if_prop_lvn_only_0_istep_2.sdfgz",
]

DEFAULT_CODEGEN_DIR = 'codegen'

def sdfg_names(verify:bool=False):
  if verify:
    for f in STARTER_SDFG_FILES:
      assert Path(f).exists()
  return list(sorted(Path(f).stem for f in STARTER_SDFG_FILES))

def stage_input(name:str, stage:int, codegen_dir=DEFAULT_CODEGEN_DIR):
  if stage > 1:
    return f"{codegen_dir}/gpu_{name}_stage{stage - 1}.sdfgz"
  else:
    starter_map = {Path(f).stem : f for f in STARTER_SDFG_FILES}
    assert name in starter_map
    return starter_map[name]

def stage_output(name:str, stage:int, codegen_dir=DEFAULT_CODEGEN_DIR):
  if stage == 0:
    return stage_input(name, stage+1, codegen_dir)
  else:
    return f"{codegen_dir}/gpu_{name}_stage{stage}.sdfgz"

def stage_inputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR):
  return {name: stage_input(name, stage, codegen_dir) for name in sdfg_names()}

def stage_outputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR):
  return {name: stage_output(name, stage, codegen_dir) for name in sdfg_names()}

def compile_action(stage: int, sdfgs: Dict[str, dace.SDFG], lib,
                    allocation_names_to_comment_out: set,
                    use_openacc_stream: bool, name_suffix: str = "",
                    main_name=None, tblock_dim=None,
                    stage_suffix:str = ""):
  dace.config.Config.set('compiler', 'default_data_types', value='C')
  release = os.getenv('_RELEASE', '0').lower() in ('1', 'true', 'yes')
  lowered = os.getenv('_REDUCE_BITWIDTH_TRANSFORMATION', '0') == '1'
  lowered_suffix = "_lowered" if lowered else ""
  for name, g in sdfgs.items():
      g.build_folder = f"{common.DEFAULT_CODEGEN_DIR}/stage{stage}{stage_suffix}{lowered_suffix}/{name}"
  sdfgs = list(sdfgs.values())
  # Avoid name conflicts.
  unique_names(sdfgs)
  # Add instrumentation if necessary.
  if config.instrument:
      instrument_sdfg(sdfgs)

  if tblock_dim is None:
    tblock_dim = "256,1,1"
  dace.Config.set('compiler', 'cuda', 'default_block_size', value=tblock_dim)
  dace.Config.set('compiler', 'cuda', 'max_concurrent_streams', value="1")
  _build_for_integration = os.getenv('_BUILD_LIB_FOR_SOLVE_NH', '0').lower() in ('1', 'true', 'yes')

  if lib:
    assert stage == 9 or stage == 5

    compile_if_propagated_sdfgs(
        sdfgs, gpu=True,
        release=release,
        generate_code=True,
        lib=True,
        main_name=main_name,
        stage=stage,
        debuginfo=False,
        allocation_names_to_comment_out=allocation_names_to_comment_out,
        use_openacc_stream=False,
      )
  elif stage == 8:
    if _build_for_integration:
      compile_if_propagated_sdfgs(
        sdfgs, gpu=True,
        release=release,
        generate_code=True,
        lib=True,
        main_name=main_name,
        stage=stage,
        debuginfo=False,
        allocation_names_to_comment_out=allocation_names_to_comment_out,
        use_openacc_stream=False,
      )
    else:
      compile_if_propagated_sdfgs(
        sdfgs, gpu=True,
        release=release,
        generate_code=True,
        lib=False,
        main_name="main_gpu.cu" if main_name is None else main_name,
        stage=stage,
        debuginfo=False,
        allocation_names_to_comment_out=allocation_names_to_comment_out,
        use_openacc_stream=False,
      )
  elif stage > 5:
    compile_if_propagated_sdfgs(
        sdfgs, gpu=True,
        release=release,
        generate_code=True,
        lib=False,
        main_name="main_gpu.cu" if main_name is None else main_name,
        stage=stage,
        allocation_names_to_comment_out=None,
        use_openacc_stream=False,
        debuginfo=True
      )
  elif stage > 1:
    compile_if_propagated_sdfgs(
        sdfgs, gpu=True,
        release=release,
        generate_code=True,
        lib=False,
        main_name="main.cu" if main_name is None else main_name,
        stage=stage,
        debuginfo=True,
        allocation_names_to_comment_out=None,
        use_openacc_stream=False,
      )
  else:
    assert stage == 1
    if not _build_for_integration:
      compile_if_propagated_sdfgs(
          sdfgs, gpu=True,
          release=release,
          generate_code=True,
          lib=False,
          main_name="main.cu" if main_name is None else main_name,
          stage=stage,
          debuginfo=True,
          allocation_names_to_comment_out=None,
          use_openacc_stream=False,
        )
    else:
      for sdfg in sdfgs:
        make_flattened_data_to_non_transient_cpu_input(sdfg)
      compile_if_propagated_sdfgs(
          sdfgs, gpu=True,
          release=release,
          generate_code=True,
          lib=True,
          main_name=main_name,
          stage=stage,
          debuginfo=True,
          allocation_names_to_comment_out=None,
          use_openacc_stream=False,
        )

  opt_suffix = '_release' if release else '_debug'
  _build_for_integration = os.getenv('_BUILD_LIB_FOR_SOLVE_NH', '0').lower() in ('1', 'true', 'yes')
  integration_suffix = '_solve_nh_integration' if _build_for_integration else '_standalone'
  lowered = os.getenv("_REDUCE_BITWIDTH_TRANSFORMATION", "0") == "1"
  lowered_suffix = "_lowered" if lowered else ""
  if stage == 1 or stage == 8:
      if not _build_for_integration:
        binpath = Path(f'velocity_gpu{lowered_suffix}')
        assert binpath.exists()
        binpath = binpath.rename(f"{binpath.name}.stage{stage}{integration_suffix}{opt_suffix}{name_suffix}{lowered_suffix}")
        print(f"Binary available: {binpath}")
      else:
        libpath = Path('libvelocity_gpu.so')
        assert libpath.exists()
        libpath = libpath.rename(f"libvelocity_gpu_stage{stage}{integration_suffix}{opt_suffix}{name_suffix}.so")
        print(f"Library available: {libpath}")
  else:
    if not lib:
      binpath = Path(f'velocity_gpu{lowered_suffix}')
      assert binpath.exists()
      binpath = binpath.rename(f"{binpath.name}.stage{stage}{integration_suffix}{opt_suffix}{name_suffix}{lowered_suffix}")
      print(f"Binary available: {binpath}")
    else:
      libpath = Path('libvelocity_gpu.so')
      assert libpath.exists()
      libpath = libpath.rename(f"libvelocity_gpu_stage{stage}{integration_suffix}{opt_suffix}{name_suffix}.so")
      print(f"Library available: {libpath}")

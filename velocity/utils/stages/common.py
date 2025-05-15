from pathlib import Path
from typing import Dict
import dace
import utils.stages.common as common
import utils.config as config
from utils.reductions import add_all_reductions
from utils.unique_names import unique_names
from utils.benchmark_sdfg import instrument_sdfg
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs


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
  if stage > 6:
    return f"{codegen_dir}/gpu_{name}_stage{stage - 1}.sdfgz"
  elif stage > 1:
    return f"{codegen_dir}/cpu_{name}_stage{stage - 1}.sdfgz"
  else:
    starter_map = {Path(f).stem : f for f in STARTER_SDFG_FILES}
    assert name in starter_map
    return starter_map[name]

def stage_output(name:str, stage:int, codegen_dir=DEFAULT_CODEGEN_DIR):
  if stage == 0:
    return stage_input(name, stage+1, codegen_dir)
  elif stage <= 5:
    return f"{codegen_dir}/cpu_{name}_stage{stage}.sdfgz"
  else:
    return f"{codegen_dir}/gpu_{name}_stage{stage}.sdfgz"

def stage_inputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR):
  return {name: stage_input(name, stage, codegen_dir) for name in sdfg_names()}

def stage_outputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR):
  return {name: stage_output(name, stage, codegen_dir) for name in sdfg_names()}

def compile_action(stage: int, sdfgs: Dict[str, dace.SDFG]):
  for name, g in sdfgs.items():
      g.build_folder = f"{common.DEFAULT_CODEGEN_DIR}/stage{stage}/{name}"
  sdfgs = list(sdfgs.values())
  # Avoid name conflicts.
  unique_names(sdfgs)
  # Add instrumentation if necessary.
  if config.instrument:
      instrument_sdfg(sdfgs)

  dace.Config.set('compiler', 'cuda', 'default_block_size', value="256,1,1")
  gpu = stage >= 6
  compile_if_propagated_sdfgs(
      sdfgs, gpu=gpu, release=True,
      instrument=config.instrument,  # Redundant. TODO: Remove from the interface.
      generate_code=True, lib=False,
      stage_suffix=None, # stage3 if you need clip_count, else None, TODO: improve this
      )
  binpath = Path('velocity_cpu')
  assert binpath.exists()
  binpath = binpath.rename(f"{binpath.name}.stage{stage}")
  print(f"Binary available: {binpath}")

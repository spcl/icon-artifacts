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
  return {Path(f).stem for f in STARTER_SDFG_FILES}

def stage_input(name:str, stage:int, codegen_dir=DEFAULT_CODEGEN_DIR):
  if stage > 1:
    return f"{codegen_dir}/cpu_{name}_stage{stage - 1}.sdfgz"
  else:
    starter_map = {Path(f).stem : f for f in STARTER_SDFG_FILES}
    assert name in starter_map
    return starter_map[name]

def stage_output(name:str, stage:int, codegen_dir=DEFAULT_CODEGEN_DIR):
  return f"{codegen_dir}/cpu_{name}_stage{stage}.sdfgz"

def stage_inputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR):
  return {name: stage_input(name, stage, codegen_dir) for name in sdfg_names()}

def stage_outputs(stage: int, codegen_dir=DEFAULT_CODEGEN_DIR):
  return {name: stage_output(name, stage, codegen_dir) for name in sdfg_names()}

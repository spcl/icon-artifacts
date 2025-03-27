import os
import shutil
from pathlib import Path
import dace
from dace.transformation.interstate import (
    LoopToMap,
    ContinueToCondition,
    ConditionFusion,
)
from dace.transformation.passes import SymbolPropagation, StructToContainerGroups
from dace.transformation.dataflow import MapCollapse
from utils import *

# Load SDFG
sdfg_names = [
    "velocity_nproma20480_if_prop_lvn_only_0_istep_1.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_1_istep_1.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_1_istep_2.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_0_istep_2.sdfgz",
]
resulting_sdfgs = []
for sdfg_name in sdfg_names:
    sdfg = dace.SDFG.from_file(sdfg_name)
    sdfg.validate()
    resulting_sdfgs.append(sdfg)

compile_if_propagated_sdfgs(resulting_sdfgs, gpu=False, release=release)

# check if execution was successful
if os.system(f"./velocity_cpu") != 0:
    print("Execution failed")
    exit(1)

compare_got_and_want()

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
    "velocity_no_nproma.sdfgz",
]
resulting_sdfgs = []
for sdfg_name in sdfg_names:
    sdfg = dace.SDFG.from_file(sdfg_name)
    sdfg.validate()
    resulting_sdfgs.append(sdfg)

compile_if_propagated_sdfgs(resulting_sdfgs, gpu=False, release=release, instrument=instrument, ref=True)

import copy
import subprocess
import dace
import shutil
import os

from dace.transformation.interstate.loop_to_map import LoopToMap
from dace.transformation.passes.struct_to_container_group import StructToContainerGroups


paths = [
    "sdfgs/add_aerosol_optics_simplified_dbg22.sdfgz",
    "sdfgs/calc_surface_spectral_simplified_dbg22.sdfgz",
    "sdfgs/cloud_optics_fn_438_simplified_dbg22.sdfgz",
    "sdfgs/crop_cloud_fraction_simplified_dbg22.sdfgz",
    "sdfgs/get_albedos_simplified_dbg22.sdfgz",
    "sdfgs/solver_mcica_lw_simplified_dbg22.sdfgz",
    "sdfgs/solver_mcica_sw_simplified_dbg22.sdfgz",
    #"sdfgs/gas_optics_simplified_dbg22.sdfgz",
]
for path in paths:
    print(f"Load and validate {path}")
    sdfg = dace.SDFG.from_file(path)
    sdfg.validate()
    print(f"Apply flattening, save, validate {sdfg.name}")
    StructToContainerGroups(save_steps=False, verbose=False, simplify=False).apply_pass(sdfg, {})
    sdfg.save(f"flat_{sdfg.name}.sdfgz", compress=True)
    sdfg.validate()
    print(f"Simplify flattened SDFG, validate {sdfg.name}")
    sdfg.simplify()
    sdfg.validate()

    #sdfg.apply_transformations_repeated(LoopToMap, validate=False)
    #sdfg.save(f"map_{sdfg.name}.sdfgz", compress=True)
    #sdfg.validate()
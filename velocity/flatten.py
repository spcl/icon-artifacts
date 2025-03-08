import dace
import dace.transformation
import dace.transformation.passes
import dace.transformation.passes.struct_to_container_group
from dace.transformation.passes.struct_to_container_group import StructToContainerGroups
from dace.transformation.interstate import LoopToMap

"""
snames = [
    "solver_mcica_lw_simplified_dbg22.sdfgz", # OK
    "add_aerosol_optics_simplified_dbg22.sdfgz", # OK
    "calc_surface_spectral_simplified_dbg22.sdfgz", # OK
    "cloud_optics_fn_438_simplified_dbg22.sdfgz", # OK
    "crop_cloud_fraction_simplified_dbg22.sdfgz", # OK
    "gas_optics_simplified_dbg22.sdfgz", # Takes too long
    "get_albedos_simplified_dbg22.sdfgz", # OK
    "solver_mcica_sw_simplified_dbg22.sdfgz", # OK
]
"""
snames = [
    "velocity.sdfgz"
]

for sname in snames:
    sdfg = dace.SDFG.from_file(sname)
    sdfg.validate()
    StructToContainerGroups(save_steps=False, verbose=True, simplify=False).apply_pass(sdfg, {})
    sdfg.compile()
    sdfg.save(f"flat_{sname}", compress=True)
    sdfg.simplify()
    sdfg.save(f"flat_simplified_{sname}", compress=True)
    sdfg.validate()
    LoopToMap().apply_pass(sdfg, {})
    sdfg.validate()
    sdfg.save(f"flat_simplified_loop_to_map_{sname}", compress=True)

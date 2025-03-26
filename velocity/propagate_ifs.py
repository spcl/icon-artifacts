import copy
import dace
from utils import *

# Load SDFG
sdfg_name = "velocity_nproma20480.sdfgz"
sdfg = dace.SDFG.from_file(sdfg_name)
sdfg.name = sdfg_name.split(".")[0]
sdfg.validate()
build_loc = sdfg.build_folder
sdfg_name = sdfg.name

prop_dict = {"lextra_diffu": "1", "ldeepatmo": "0", "lvn_only": "0", "istep": "1"}
print(f"Propagate for: {prop_dict}")
sdfg1 = copy.deepcopy(sdfg)
sdfg1.name = sdfg_name + "_if_prop_lvn_only_0_istep_1"
propagate_if_cond(sdfg1, sdfg1, prop_dict, verbose=True)
sdfg1.save(sdfg1.name + ".sdfgz", compress=True)
sdfg1.compile()

prop_dict = {"lextra_diffu": "1", "ldeepatmo": "0", "lvn_only": "1", "istep": "1"}
print(f"Propagate for: {prop_dict}")
sdfg2 = copy.deepcopy(sdfg)
sdfg2.name = sdfg_name + "_if_prop_lvn_only_1_istep_1"
propagate_if_cond(sdfg2, sdfg2, prop_dict, verbose=True)
sdfg2.save(sdfg2.name + ".sdfgz", compress=True)
sdfg2.compile()

prop_dict = {"lextra_diffu": "1", "ldeepatmo": "0", "lvn_only": "1", "istep": "2"}
print(f"Propagate for: {prop_dict}")
sdfg3 = copy.deepcopy(sdfg)
sdfg3.name = sdfg_name + "_if_prop_lvn_only_1_istep_2"
propagate_if_cond(sdfg3, sdfg3, prop_dict, verbose=True)
sdfg3.save(sdfg3.name + ".sdfgz", compress=True)
sdfg3.compile()

prop_dict = {"lextra_diffu": "1", "ldeepatmo": "0", "lvn_only": "0", "istep": "2"}
print(f"Propagate for: {prop_dict}")
sdfg4 = copy.deepcopy(sdfg)
sdfg4.name = sdfg_name + "_if_prop_lvn_only_0_istep_2"
propagate_if_cond(sdfg4, sdfg4, prop_dict, verbose=True)
sdfg4.save(sdfg4.name + ".sdfgz", compress=True)
sdfg4.compile()
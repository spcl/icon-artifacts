import dace

sdfg = dace.SDFG.from_file("gpu_velocity_no_nproma_if_prop_lvn_only_0_istep_1_stage1.sdfgz")

sdfg.compile()
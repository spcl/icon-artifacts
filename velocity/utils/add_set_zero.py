import dace

def add_set_zero(sdfg: dace.SDFG, array_name:str):
    state = sdfg.start_block
    assert isinstance(state, dace.SDFGState), "Start block must be a state."
    assert array_name in sdfg.arrays, f"Array '{array_name}' not found in SDFG."

    num_elements = sdfg.arrays[array_name].total_size
    c_dtype = sdfg.arrays[array_name].dtype.ctype
    #real_name = array_name if sdfg.arrays[array_name].storage != dace.StorageType.persistent else f"__state->__0_{array_name}"

    code = f"cudaMemsetAsync(_in, 0, {num_elements} * sizeof({c_dtype}), __state->gpu_context->streams[0]);"

    t = state.add_tasklet(
        name=f"set_zero_{array_name}",
        inputs={"_in"},
        outputs=set(),
        code=code,
        language=dace.Language.CPP,
        side_effects=True
    )
    t.add_in_connector("_in")
    a = state.add_access(array_name)
    state.add_edge(
        a, None, t, "_in", dace.Memlet.from_array(array_name, sdfg.arrays[array_name])
    )

import dace

def clean_view_descs(sdfg: dace.SDFG):
    arrs_to_rm = set()
    for arr_name, arr in sdfg.arrays.items():
        if isinstance(arr, dace.data.View):
            arrs_to_rm.add(arr_name)
    for arr_name in arrs_to_rm:
        sdfg.remove_data(arr_name, validate=True)

def set_transient_storage_to_persistent(sdfg: dace.SDFG):
    for arr_name, arr in sdfg.arrays.items():
        if arr.transient and isinstance(arr, dace.data.Array):
            arr.lifetime = dace.dtypes.AllocationLifetime.Persistent


def check_transients_in_nsdfgs_impl(sdfg: dace.SDFG, depth: int):
    nsdfgs = set()
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                nsdfgs.add(node.sdfg)

    if depth != 0:
        for arr_name, arr in sdfg.arrays.items():
            if arr.transient and isinstance(arr, dace.data.Array):
                print(f"Transient array {arr_name} found in SDFG {sdfg.name} at depth {depth}. "
                       "This array should be moved to top level for optimization purposes.")


    for nsdfg in nsdfgs:
        check_transients_in_nsdfgs_impl(nsdfg, depth + 1)

def check_transients_in_nsdfgs(sdfg: dace.SDFG):
    check_transients_in_nsdfgs_impl(sdfg, 0)

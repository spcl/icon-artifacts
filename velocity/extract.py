import dace

import argparse
import dace
import copy
import utils.stages.common as common
from utils.int64_to_int32 import int64_to_int32
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule
from utils.tile import prune_unused_inputs_outputs
from utils.hacky_cfl_clipping_related_kernel_removal import hacky_cfl_clipping_related_kernel_removal
from utils.remove_unused_inconnectors_from_nestedsdfg import remove_unused_inconnectors_from_nestedsdfg
from utils.change_array_dtypes import change_array_dtypes
from utils.permute_array_dimensions import PermuteArrayDimensions, inverse_strides

STAGE_ID = 8

# Example label: single_state_body_4_map_0_0
def all_kernels_except(sdfg: dace.SDFG, map_label: str, state_label: str):
    nodes_to_keep = set()
    entry_node, exit_node = None, None
    state = None
    for n, g in sdfg.all_nodes_recursive():
        if n.label == map_label and g.label == state_label and isinstance(n, dace.nodes.MapEntry):
            nodes_to_keep.add(n)
            entry_node = n
            exit_node = g.exit_node(n)
            nodes_to_keep.add(exit_node)
            exit_node = exit_node
            state = g
    
    for n, g in sdfg.all_nodes_recursive():
        if any({(e.dst == entry_node or e.src == exit_node 
                 or e.src == entry_node or e.dst == exit_node)
                for e in g.out_edges(n) + g.in_edges(n)}):
            nodes_to_keep.add(n)

    for s in sdfg.all_states():
        if s.label == "entry_interface":
            continue
        if s.label == "block":
            continue
        for n in s.nodes():
            if n not in nodes_to_keep:
                s.remove_node(n)

    ss = sdfg.add_state_after(state, "printer", is_start_block=False)
    copydesc = copy.deepcopy(sdfg.arrays["gpu_zeta"])
    copydesc.storage = dace.dtypes.StorageType.CPU_Heap
    sdfg.add_datadesc("zeta", copydesc, False)
    a1 = ss.add_access("gpu_zeta")
    a2 = ss.add_access("zeta")
    ss.add_edge(a1, None, a2, None, dace.memlet.Memlet.from_array(
        "gpu_zeta", sdfg.arrays["gpu_zeta"]
    ))
    

    t = ss.add_tasklet(
        name="printer",
        inputs={"_in"},
        outputs={},
        code='printf("value = %f\\n", _in);',
        language=dace.dtypes.Language.CPP,
        code_global="#include <stdio.h>",
        side_effects=True
    )
    ss.add_edge(a2, None, t, "_in", 
                dace.memlet.Memlet("zeta[0,0,0]"))


def optimization_action(sdfg):
    inverse_strides(sdfg, "gpu_levmask")
    sdfg.save("x1.sdfgz", compress=True)
    all_kernels_except(sdfg, "single_state_body_2_map", "_state_l412_c412")
    sdfg.validate()
    sdfg.save("x2.sdfgz", compress=True)
    # Remove all stencilss except 1.
    return sdfg

def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--optimize', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--compile', action=argparse.BooleanOptionalAction, default=False)
    args = argp.parse_args()
    if not args.optimize and not args.compile:
        args.optimize, args.compile = True, True

    names = common.sdfg_names()

    if args.optimize:
        for name in names:
            infile = common.stage_input(name, STAGE_ID)
            outfile = common.stage_output(name, STAGE_ID)

            print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")

            sdfg = dace.SDFG.from_file(infile)
            sdfg.name = name
            sdfg.validate()

            sdfg = optimization_action(sdfg)

            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfg.save(outfile, compress=True)

    if args.compile:
        # Read back the written files as we prepare for compilation.
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        common.compile_action(STAGE_ID, sdfgs, False, None, False)

if __name__ == "__main__":
    main()

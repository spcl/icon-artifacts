import argparse

import dace

import utils.stages.common as common
from utils.find import find_node_by_name
from utils.move_scalar_to_array import _tmp_difcoef
from utils.move_transients_to_top_level import move_transients_to_top_level
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
from utils.remove_unused_inconnectors_from_nestedsdfg import remove_unused_inconnectors_from_nestedsdfg
from utils.merge_maps import merge_maps_in_sdfg
from utils.change_array_dtypes import change_array_dtypes
from dace.transformation.passes.constant_propagation import ConstantPropagation
STAGE_ID = 5


def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    sdfg.validate()
    prune_unused_inputs_outputs(sdfg)
    sdfg.validate()
    # prune_unused_inputs_outputs_recursive(sdfg) # Missing symbol ntnd error
    #sdfg.validate()
    # Hardcoded fixes for the GPU version
    # pre_gpu_fix(sdfg)
    # move_ifs_inside_maps(sdfg)
    flatten_lib, _ = find_node_by_name(sdfg, "flatten")
    deflatten_lib, _ = find_node_by_name(sdfg, "deflatten")

    # if nlev and nlevp1 are propagated
    # z_v_grad_w [ tmp_struct_symbol_4, 90, tmp_struct_symbol_5 ] (nproma,p_patch%nlev,p_patch%nblks_e)
    # tmp_struct_symbol_5 == nblks_e
    # zeta [ tmp_struct_symbol_8, 90, tmp_struct_symbol_9 ] (nproma,p_patch%nlev,p_patch%nblks_v)
    # tmp_struct_symbol_9 == nblks_v
    # z_ekinh [ tmp_struct_symbol_10, 90, tmp_struct_symbol_11 ] (nproma,p_patch%nlev,p_patch%nblks_c)
    # tmp_struct_symbol_11 == nblks_c

    # if nlev and nlevp1 are not propagated
    # z_v_grad_w [ tmp_struct_symbol_7, tmp_struct_symbol_8, tmp_struct_symbol_9 ] (nproma,p_patch%nlev,p_patch%nblks_e)
    # tmp_struct_symbol_9 == nblks_e
    # zeta [ tmp_struct_symbol_13, tmp_struct_symbol_14, tmp_struct_symbol_15 ] (nproma,p_patch%nlev,p_patch%nblks_v)
    # tmp_struct_symbol_15 == nblks_v
    # z_ekinh [ tmp_struct_symbol_16, tmp_struct_symbol_17, tmp_struct_symbol_18 ] (nproma,p_patch%nlev,p_patch%nblks_c)
    # tmp_struct_symbol_18 == nblks_c

    # CAUSES DIFFERENCE IN `ddt_vn_apc_pc` AND `w_concorr_c`.
    # TODO: BEFORE ENABLING THIS `move_transients_to_top_level`, MAKE SURE IT IS CORRECT.
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        only=["z_w_con_c", "z_w_concorr_mc", "levmask", "cfl_clipping"],
        no_dim_change=False,
        offset=-1,
        upper_bounds={
            "z_w_concorr_mc": "tmp_struct_symbol_5",
            "z_w_con_c": "tmp_struct_symbol_5",
            "levmask": "tmp_struct_symbol_5",
            "cfl_clipping": "tmp_struct_symbol_5",
        },
    )
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        only=["z_v_grad_w", "z_ekinh", "zeta", "z_w_v", "z_w_con_c_full"],
        no_dim_change=True,
    )
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        upper_bounds={
            "maxvcfl_arr": "tmp_struct_symbol_11"
        },
        only=["maxvcfl_arr"],
        no_dim_change=False,
        offset=-1,
        set_zero=True,
    )
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        only=["out_val_0"],
        no_dim_change=True,
    )
    if "difcoef" in sdfg.arrays:
        _tmp_difcoef(sdfg)
    sdfg.validate()

    merge_maps_in_sdfg(sdfg)
    sdfg.validate()

    remove_unused_inconnectors_from_nestedsdfg(sdfg)
    sdfg.simplify()
    sdfg.validate()

    # GPU read-write has unit size of 32bits, uint8_t won't help
    #change_array_dtypes(sdfg,
    #                    array_names={"levmask", "levelmask", "cfl_clipping", "gpu_levmask", "gpu_levelmask", "gpu_cfl_clipping"},
    #                    new_type=dace.uint8)
    sdfg.validate()

    ConstantPropagation().apply_pass(sdfg, {})
    sdfg.simplify()
    sdfg.validate()
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

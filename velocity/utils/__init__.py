from utils.find import find_node_by_name, find_node_by_guid
from utils.loop_locality import make_array_loop_local, apply_loop_locality_pass
from utils.reductions import (
    loop_to_max_reduction,
    cfl_clipping_to_reduction,
    maxvcfl_to_reduction,
    tmp_call_13_to_reduction,
    levmask_to_reduction,
    add_all_reductions,
)
from utils.count import count_loops, count_max_maps_per_state, count_symbols_use_defs
from utils.move_transients_to_top_level import move_transients_to_top_level
from utils.config import use_cache, cleanup, reduction, verbose, instrument, tile, remainder_loop, layout_transform
from utils.map_fissions import YoloMapFission
from utils.split_maps import split_map_sdfg, untangle_if_sdfg
from utils.raise_loop_invariant_if import raise_loop_invariant_if
from utils.gpu_kernel_launch_fix import wrap_reduction_and_T_l488_c488in_gpumap
from utils.prune_unused_inputs_outputs import (
    prune_unused_inputs_outputs,
    prune_unused_inputs_outputs_recursive,
)
from utils.map_state_fission import MapStateFission, AccessDuplicate
from utils.benchmark_sdfg import instrument_sdfg, collect_reports, clean_reports
from utils.preprocess_tough_nut import preprocess_tough_nut
from utils.clean_bad_views import clean_bad_views
from utils.propagate_if_cond import propagate_if_cond
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
from utils.unique_names import unique_names
from utils.propagate_block_var import propagate_block_var
from utils.rename_on_if import rename_on_if, rename_on_if2
from utils.demote_symbol_to_scalar import demote_symbol_to_scalar
from utils.computation_map_nesting import ComputationMapNesting
from utils.pre_gpu_fixes import pre_gpu_fix
from utils.make_unique_block_var import make_unique_block_var
from utils.merge_maps import merge_maps, merge_maps_in_sdfg
from utils.permute_index import permute_index
from utils.permute_index import permute_maps
from utils.tile import tile_kernels, tile_specific_kernel
from utils.move_ifs_inside_maps import move_ifs_inside_maps
from utils.segmented_reduction import to_segmented_reduction
from utils.move_scalar_to_array import move_scalar_to_array, _tmp_difcoef
from utils.move_lib_schedules import move_lib_schedules

from utils.combine import combine
from utils.permute import permute_index, permute_maps, permute_all_maps, permute_all_maps_depending_on_input
from utils.input_to_gpu import input_to_gpu
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.init_transient_zero import init_transient_zero
from utils.add_gpu_copies_to_flattener import add_gpu_copies_to_flattener
from utils.int64_to_int32 import int64_to_int32
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule

from utils.rm_segmented_reduce import rm_segmented_reduce
from utils.change_flatten_lib_to_shallow_copy import change_flatten_lib_to_shallow_copy
from utils.add_set_zero import add_set_zero
from utils.change_array_dtypes import change_array_dtypes

from utils.reshape_kernels import reshape_kernels
from utils.decrease_bitwidth_of_const_arrays import decrease_bitwidth_of_const_arrays

from utils.prune_names import prune_names

from utils.make_flattened_data_to_input import make_flattened_data_to_non_transient_cpu_input, make_flattened_data_to_non_transient_gpu_input
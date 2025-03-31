from utils.find import find_node_by_name
from utils.loop_locality import make_array_loop_local, apply_loop_locality_pass
from utils.reductions import (
    loop_to_max_reduction,
    cfl_clipping_to_reduction,
    maxvcfl_to_reduction,
    tmp_call_13_to_reduction,
    levmask_to_reduction,
    add_all_reductions,
)
from utils.compare_got_and_want import compare_got_and_want
from utils.compile_sdfg import compile_sdfg
from utils.count import count_loops, count_max_maps_per_state
from utils.move_transients_to_top_level import move_transients_to_top_level
from utils.config import use_cache, cleanup, reduction, release, verbose, instrument
from utils.map_fissions import YoloMapFission
from utils.split_maps import split_map_sdfg, untangle_if_sdfg
from utils.raise_loop_invariant_if import raise_loop_invariant_if
from utils.gpu_kernel_launch_fix import wrap_reduction_and_T_l488_c488in_gpumap
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
from utils.map_state_fission import MapStateFission, AccessDuplicate
from utils.benchmark_sdfg import instrument_sdfg, collect_reports
from utils.preprocess_tough_nut import preprocess_tough_nut
from utils.clean_bad_views import clean_bad_views
from utils.propagate_if_cond import propagate_if_cond
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
from utils.unique_names import unique_names
from utils.propagate_block_var import propagate_block_var
from utils.rename_on_if import rename_on_if
from utils.demote_symbol_to_scalar import demote_symbol_to_scalar
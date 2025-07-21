import dace
import os
from typing import Callable, Dict, Set, Tuple
from dace.codegen.common import CodeBlock
from dace.sdfg import is_devicelevel_gpu
from dace.sdfg.state import MultiConnectorEdge
from .transify_kernel_scalars import transify_kernel_scalars
from .get_num_parent_map_scopes import get_num_parent_map_scopes

openacc_data_names = """
   !$ACC DATA CREATE(z_kin_hor_e,z_vt_ie,z_w_concorr_me,z_theta_v_fl_e) &
    !$ACC   CREATE(z_dexner_dz_c,z_exner_ex_pr,z_gradh_exner,z_rth_pr,z_grad_rth) &
    !$ACC   CREATE(z_theta_v_pr_ic,z_th_ddz_exner_c,z_w_concorr_mc) &
    !$ACC   CREATE(z_vn_avg,z_rho_e,z_theta_v_e,z_dwdz_dd,z_mflx_top) &
    !$ACC   CREATE(z_exner_ic,z_alpha,z_beta,z_q,z_contr_w_fl_l,z_exner_expl) &
    !$ACC   CREATE(z_flxdiv_mass,z_flxdiv_theta,z_rho_expl,z_w_expl) &
    !$ACC   CREATE(z_rho_v,z_theta_v_v,z_graddiv_vn,z_hydro_corr,z_graddiv2_vn) &
    !$ACC   COPYIN(nflatlev, nflat_gradp, kstart_dd3d, kstart_moist, nrdmax) &
    !$ACC   COPYIN(z_raylfac, ndyn_substeps_var, scal_divdamp, bdy_divdamp) &
    !$ACC   PRESENT(prep_adv, p_int, p_patch, p_nh) &
    !$ACC   PRESENT(icidx, icblk, ividx, ivblk, ieidx, ieblk, ikidx, iqidx, iqblk) &
    !$ACC   PRESENT(ipeidx, ipeblk, iplev)
"""

ptr_assignments = """
    ! Set pointers to neighbor cells
    icidx => p_patch%edges%cell_idx
    icblk => p_patch%edges%cell_blk

    ! Set pointers to neighbor edges
    ieidx => p_patch%cells%edge_idx
    ieblk => p_patch%cells%edge_blk

    ! Set pointers to vertices of an edge
    ividx => p_patch%edges%vertex_idx
    ivblk => p_patch%edges%vertex_blk

    ! Set pointer to vertical neighbor indices for pressure gradient
    ikidx => p_nh%metrics%vertidx_gradp

    ! Set pointers to quad edges
    iqidx => p_patch%edges%quad_idx
    iqblk => p_patch%edges%quad_blk

    ! DA: moved from below to here to get into the same ACC data section
    iplev  => p_nh%metrics%pg_vertidx
    ipeidx => p_nh%metrics%pg_edgeidx
    ipeblk => p_nh%metrics%pg_edgeblk
"""

data_names_gpu = """
z_kin_hor_e,z_vt_ie,z_w_concorr_me,z_theta_v_fl_e,
z_dexner_dz_c,z_exner_ex_pr,z_gradh_exner,z_rth_pr,z_grad_rth,
z_theta_v_pr_ic,z_th_ddz_exner_c,z_w_concorr_mc,
z_vn_avg,z_rho_e,z_theta_v_e,z_dwdz_dd,z_mflx_top,
z_exner_ic,z_alpha,z_beta,z_q,z_contr_w_fl_l,z_exner_expl,
z_flxdiv_mass,z_flxdiv_theta,z_rho_expl,z_w_expl,
z_rho_v,z_theta_v_v,z_graddiv_vn,z_hydro_corr,z_graddiv2_vn,
"""

data_names_both = """
nflatlev,nflat_gradp,kstart_dd3d,kstart_moist,nrdmax,
z_raylfac,ndyn_substeps_var, scal_divdamp,bdy_divdamp,
"""

def gpu_offloading_wo_host_dev_copies(sdfg: dace.SDFG):
    names_gpu = {n.strip() for n in data_names_gpu.replace("\n", "").strip().split(",") if n != "," and n != ""}
    names_both = {n.strip() for n in data_names_both.replace("\n", "").strip().split(",") if n != "," and n != ""}
    parent_map_count = 1
    verbose = os.getenv("VERBOSE", "0").lower().strip() in ("1", "true", "yes", "on")

    _gpu_offloading_wo_host_dev_copies_impl(
        sdfg=sdfg,
        gpu_only_arrays=names_gpu,
        duplicated_arrays=names_both,
        parent_map_count=parent_map_count,
        verbose=verbose
    )

def _check_arrays_are_constant(sdfg: dace.SDFG, array_names: Set[str], verbose: bool):
    if verbose:
        print(f"Checking if arrays: {array_names} are constant.")

    writes_to_access_nodes = dict()
    for graph in sdfg.all_states():
        for node in graph.nodes():
            if isinstance(node, dace.nodes.AccessNode):
                if (
                    graph.in_degree(node) > 0 and
                    any([ie.data is not None for ie in graph.in_edges(node)])
                ):
                    if node.data not in writes_to_access_nodes:
                        writes_to_access_nodes[node.data] = 0
                    writes_to_access_nodes[node.data] += 1
    for array_name in array_names:
        assert writes_to_access_nodes.get(array_name, 0) <= 1
    for array_name in array_names:
        if array_name not in writes_to_access_nodes:
            writes_to_access_nodes[array_name] = 0
    if verbose:
        print(
            f"Writes to arrays: {writes_to_access_nodes}"
        )
        print()
        print()
    return writes_to_access_nodes

import dace
import copy

def _add_gpu_copies_to_flattener(sdfg: dace.SDFG, gpu_arrays: Set[str]):
    flattener_lib_node, flattener_state = None, None
    deflattener_lib_node, deflattener_state = None, None
    added_gpu_arrays = set()

    for state in sdfg.all_states():
        for node in state.nodes():
            if node.label == "flatten" and isinstance(node, dace.sdfg.nodes.LibraryNode):
                flattener_lib_node = node
                flattener_state = state
            elif node.label == "deflatten" and isinstance(node, dace.sdfg.nodes.LibraryNode):
                deflattener_lib_node = node
                deflattener_state = state

    assert flattener_lib_node is not None, "Flattener library node not found in the SDFG."
    assert deflattener_lib_node is not None, "Deflatten library node not found in the SDFG."

    for oe in flattener_state.out_edges(flattener_lib_node):
        assert oe.src == flattener_lib_node, "Output edge source is not the flattener library node."
        dst_node = oe.dst
        out_degree = flattener_state.out_degree(dst_node)
        edges_to_add = set()
        if (
            isinstance(dst_node, dace.sdfg.nodes.AccessNode) and
            dst_node.data in sdfg.arrays and
            isinstance(sdfg.arrays[dst_node.data], dace.data.Array) and
            not isinstance(sdfg.arrays[dst_node.data], dace.data.View) and
            not isinstance(sdfg.arrays[dst_node.data], dace.data.Scalar) and
            not isinstance(sdfg.arrays[dst_node.data], dace.data.Structure) and
            dst_node.data in gpu_arrays
        ):
            arr = sdfg.arrays[dst_node.data]
            if arr.storage != dace.dtypes.StorageType.GPU_Global:
                if "gpu_" + dst_node.data not in sdfg.arrays:
                    copy_arr = copy.deepcopy(arr)
                    copy_arr.storage = dace.dtypes.StorageType.GPU_Global
                    sdfg.add_datadesc("gpu_" + dst_node.data, copy_arr)

                if out_degree > 0:
                    pass
                else:
                    an = flattener_state.add_access("gpu_" + dst_node.data)
                    edges_to_add.add((dst_node, None, an, None, dace.memlet.Memlet.from_array(dst_node.data, arr)))
                    added_gpu_arrays.add("gpu_" + dst_node.data)

        for e_data in edges_to_add:
            flattener_state.add_edge(*e_data)

    for ie in deflattener_state.in_edges(deflattener_lib_node):
        assert ie.dst == deflattener_lib_node, "Output edge source is not the flattener library node."
        src_node = ie.src
        in_degree = deflattener_state.in_degree(src_node)
        edges_to_add = set()
        if (
            isinstance(src_node, dace.sdfg.nodes.AccessNode) and
            src_node.data in sdfg.arrays and
            isinstance(sdfg.arrays[src_node.data], dace.data.Array) and
            not isinstance(sdfg.arrays[src_node.data], dace.data.View) and
            not isinstance(sdfg.arrays[src_node.data], dace.data.Scalar) and
            not isinstance(sdfg.arrays[src_node.data], dace.data.Structure) and
            src_node.data in gpu_arrays
        ):
            arr = sdfg.arrays[src_node.data]
            if arr.storage != dace.dtypes.StorageType.GPU_Global:
                if "gpu_" + src_node.data not in sdfg.arrays:
                    copy_arr = copy.deepcopy(arr)
                    copy_arr.storage = dace.dtypes.StorageType.GPU_Global
                    sdfg.add_datadesc("gpu_" + src_node.data, copy_arr)
                    assert "gpu_" + src_node.data in sdfg.arrays

                # If in_degree > 0 need an intermediate access node and edge
                if in_degree > 0:
                    pass
                    #for ie_d in deflattener_state.in_edges(src_node):
                    #    assert ie_d.dst_conn is None
                    #    edges_to_add.add((ie_d.src, ie_d.src_conn, an, None, copy.deepcopy(ie_d.data)))
                    #    deflattener_state.remove_edge(ie_d)
                    #edges_to_add.add((an, None, src_node, None, dace.memlet.Memlet.from_array("gpu_" + src_node.data, copy_arr)))
                else:
                    an = deflattener_state.add_access("gpu_" + src_node.data)
                    edges_to_add.add((an, None, src_node, None, dace.memlet.Memlet.from_array("gpu_" + src_node.data, arr)))
                assert "gpu_" + src_node.data in added_gpu_arrays

        for e_data in edges_to_add:
            deflattener_state.add_edge(*e_data)

    return added_gpu_arrays

def _find_flattened_names(sdfg: dace.SDFG, names_to_check: Set[str]):
    name_dict = dict()
    for name_to_check in names_to_check:
        name_candidates = set()
        for name, desc in sdfg.arrays.items():
            if "gpu_" in name:
                continue
            if name_to_check in name and not isinstance(desc, dace.data.View):
                name_candidates.add(name)
        # If candidates > 1 then one of the name matches
        if len(name_candidates) > 1:
            assert name_to_check in name_candidates, f"Expected only one candidate for {name_to_check}, found: {name_candidates}"
            name_dict[name_to_check] = name_to_check
        elif len(name_candidates) == 1:
            name_dict[name_to_check] = name_candidates.pop()
        else:
            name_dict[name_to_check] = None
            assert name_to_check not in sdfg.arrays, f"Expected no array {name_to_check} in the SDFG."
    return name_dict


def _copy_nontransient_arrays_to_gpu(sdfg: dace.SDFG, name_dict: dict, verbose: bool):
    if verbose:
        print("Copying non-transient arrays to GPU:")
    prev_start_block = sdfg.start_block
    first_state = sdfg.add_state(label="copy_in_nontransient", is_start_block=True)
    sdfg.add_edge(first_state, prev_start_block, dace.sdfg.InterstateEdge())
    # Add copy-outs in the last state
    prev_last_blocks = [n for n in sdfg.nodes() if sdfg.out_degree(n) == 0]
    assert len(prev_last_blocks) == 1, "Expected only one last state in the SDFG."
    prev_last_block = prev_last_blocks[0]
    last_state = sdfg.add_state(label="copy_out_nontransient")
    sdfg.add_edge(prev_last_block, last_state, dace.sdfg.InterstateEdge())

    for src_name, dst_name in name_dict.items():
        if dst_name is None:
            continue
        if dst_name in sdfg.arrays and sdfg.arrays[dst_name].transient:
            continue  # Skip transient arrays
        dst_gpu_name = "gpu_" + dst_name

        if dst_gpu_name not in sdfg.arrays:
            if isinstance(sdfg.arrays[dst_name], dace.data.Scalar):
                if verbose:
                    print(f"    Skipping scalar {dst_name}.")
                continue
            assert dst_name in sdfg.arrays, f"Expected {dst_name} to be in the SDFG arrays."
            gpu_datadesc = copy.deepcopy(sdfg.arrays[dst_name])
            gpu_datadesc.transient = True
            gpu_datadesc.storage = dace.dtypes.StorageType.GPU_Global
            sdfg.add_datadesc(dst_gpu_name, gpu_datadesc)

        # Add copy-ins in the flattening state
        assert isinstance(first_state, dace.SDFGState), "Expected the first state to be an SDFGState."
        has_access_node = {n for n in first_state.nodes() if isinstance(n, dace.nodes.AccessNode) and n.data == dst_name}
        assert not has_access_node
        an = first_state.add_access(dst_name)
        gpu_an = first_state.add_access(dst_gpu_name)
        first_state.add_edge(
            an, None, gpu_an, None,
            dace.memlet.Memlet.from_array(dst_name, gpu_datadesc)
        )

        assert isinstance(last_state, dace.SDFGState), "Expected the last state to be an SDFGState."
        has_access_node = {n for n in last_state.nodes() if isinstance(n, dace.nodes.AccessNode) and n.data == dst_name}
        assert not has_access_node, f"Expected no access node for {dst_name} in the last state."
        ret_an = last_state.add_access(dst_gpu_name)
        an = last_state.add_access(dst_name)
        last_state.add_edge(
            ret_an, None, an, None,
            dace.memlet.Memlet.from_array(dst_gpu_name, gpu_datadesc)
        )

        if verbose:
            print(f"    Copied non-transient array {dst_name} to GPU as {dst_gpu_name} in the first state of the SDFG.")
            print(f"    Copied back transient array {dst_gpu_name} from GPU to {dst_name} in the last state of the SDFG.")
    if verbose:
        print()
        print()


def _get_data_used_by_map(map_entry: dace.nodes.MapEntry, state: dace.SDFGState):
    """
    Returns a set of data names used by the map entry node.
    """
    data_used = set()
    for edge in state.in_edges(map_entry):
        if edge.data is not None:
            datadesc = state.sdfg.arrays[edge.data.data]
            if isinstance(datadesc, dace.data.Array):
                data_used.add(edge.data.data)
    for edge in state.out_edges(state.exit_node(map_entry)):
        if edge.data is not None:
            datadesc = state.sdfg.arrays[edge.data.data]
            if isinstance(datadesc, dace.data.Array):
                data_used.add(edge.data.data)
    # All access nodes within the map entry that is not scalar
    nodes = state.all_nodes_between(map_entry, state.exit_node(map_entry))
    for node in nodes:
        if isinstance(node, dace.nodes.AccessNode):
            if node.data in state.sdfg.arrays:
                datadesc = state.sdfg.arrays[node.data]
                if isinstance(datadesc, dace.data.Array) and not isinstance(datadesc, dace.data.Scalar):
                    data_used.add(node.data)
    return data_used


def _set_gpu_schedule(parent_map_counts: Dict[Tuple[dace.nodes.MapEntry, dace.SDFGState], int],
                      parent_map_count: int,
                      additional_condition: Callable):
    """
    Sets the GPU schedule for maps with more than parent_map_count parent maps.
    """
    for (map_node, map_state), num_parent_maps in parent_map_counts.items():
        if num_parent_maps == parent_map_count:
            map_node.map.schedule = dace.ScheduleType.GPU_Device
        elif num_parent_maps > parent_map_count:
            map_node.map.schedule = dace.ScheduleType.Sequential
        else:
            assert num_parent_maps < parent_map_count
            map_node.map.schedule = dace.ScheduleType.Sequential
        if additional_condition(map_node, map_state):
            map_node.map.schedule = dace.ScheduleType.GPU_Device

def _is_blk_map(map_node: dace.nodes.MapEntry, map_state: dace.SDFGState) -> bool:
    """
    Checks if the map node is a block map.
    """
    _ranges = map_node.map.range
    range_list = list()
    for (b,e,s) in _ranges:
        range_list.append(str(b))
        range_list.append(str(e))
        range_list.append(str(s))
    has_startblk = any("startblk" in expr_str for expr_str in range_list)
    has_endblk = any("endblk" in expr_str for expr_str in range_list)
    has_bdy_mflx_e_dim = any("bdy_mflx_e_dim" in expr_str for expr_str in range_list)
    # All seq. blk maps have only i_startblk and i_endblk as free params
    if (has_startblk and has_endblk and len(map_node.map.range.free_symbols) == 2) or has_bdy_mflx_e_dim:
        return True
    return False

def _additional_offload_condition(map_node: dace.nodes.MapEntry, map_state: dace.SDFGState) -> bool:
    return not _is_blk_map(map_node, map_state)


def _replace_edge_data_with_gpu_data(
        root_sdfg: dace.SDFG,
        state: dace.SDFGState,
        edges: Set[MultiConnectorEdge],
        gpu_arrays: Set[str]
    ):
        for edge in edges:
            if edge.data is not None:
                if edge.data.data is not None:
                    no_gpu_data_name = edge.data.data[4:] if edge.data.data.startswith("gpu_") else edge.data.data
                    gpu_data_name = "gpu_" + no_gpu_data_name
                    if no_gpu_data_name in gpu_arrays:
                        if no_gpu_data_name not in state.sdfg.arrays:
                            assert "gpu_" + no_gpu_data_name in state.sdfg.arrays
                            desc = state.sdfg.arrays[gpu_data_name]
                            if isinstance(desc, dace.data.Array):
                                edge.data.data = gpu_data_name
                        else:
                            desc = state.sdfg.arrays[no_gpu_data_name]
                            if isinstance(desc, dace.data.Array):
                                if gpu_data_name not in state.sdfg.arrays:
                                    gpu_desc = copy.deepcopy(desc)
                                    gpu_desc.storage = dace.dtypes.StorageType.GPU_Global
                                    state.sdfg.add_datadesc(gpu_data_name, gpu_desc)
                                edge.data.data = gpu_data_name


def _replace_connectors_and_nsdfg_desc(
    state: dace.SDFGState,
    edges: Set[MultiConnectorEdge],
    prefix: str,
    gpu_arrays: Set[str]
):
    for edge in edges:
        if edge.data is not None:
            if edge.data.data is not None:
                data_name = edge.data.data
                no_gpu_data_name = data_name[4:] if data_name.startswith("gpu_") else data_name
                if no_gpu_data_name in gpu_arrays:
                    desc = state.sdfg.arrays[data_name]
                    if isinstance(desc, dace.data.Array) and desc.storage == dace.dtypes.StorageType.GPU_Global:
                        # If src_conn starts with "OUT_" (src is MapEntry or Exit)
                        if isinstance(edge.src, (dace.nodes.MapExit, dace.nodes.MapEntry)):
                            if edge.src_conn is not None and edge.src_conn.startswith("OUT_"):
                                rmed = edge.src.remove_out_connector(edge.src_conn)
                                assert rmed, f"Expected to remove OUT connector {edge.src_conn} from {edge.src.label}."
                                edge.src_conn = "OUT_" + prefix + no_gpu_data_name
                                edge.src.add_out_connector(edge.src_conn, force=True)
                        # If src is NestedSDFG
                        elif isinstance(edge.src, dace.nodes.NestedSDFG):
                            assert edge.src_conn is not None, "Expected src_conn to be set for NestedSDFG."
                            if edge.src_conn != data_name:
                                edge.src.sdfg.remove_data(edge.src_conn, validate=False)
                                if data_name not in edge.src.sdfg.arrays:
                                    copydesc = copy.deepcopy(desc)
                                    copydesc.storage = dace.dtypes.StorageType.GPU_Global
                                    copydesc.transient = False
                                    edge.src.sdfg.add_datadesc(data_name, copydesc)
                            rmed = edge.src.remove_out_connector(edge.src_conn)
                            assert rmed, f"Expected to remove OUT connector {edge.src_conn} from {edge.src.label}."
                            edge.src_conn = data_name
                            edge.src.add_out_connector(data_name, force=True)
                        elif isinstance(edge.src, dace.nodes.AccessNode):
                            edge.src.data = data_name
                        else:
                            # Keep the src conn as is
                            pass

                        # If dst is NestedSDFG
                        if isinstance(edge.dst, (dace.nodes.MapExit, dace.nodes.MapEntry)):
                            # If dst_conn starts with "IN_" (dst is MapExit or Entry)
                            if edge.dst_conn is not None and edge.dst_conn.startswith("IN_"):
                                rmed = edge.dst.remove_in_connector(edge.dst_conn)
                                assert rmed, f"Expected to remove IN connector {edge.dst_conn} from {edge.dst.label}."
                                edge.dst_conn = "IN_" + prefix + no_gpu_data_name
                                edge.dst.add_in_connector("IN_" + prefix + no_gpu_data_name, force=True)
                        elif isinstance(edge.dst, dace.nodes.NestedSDFG):
                            assert edge.dst_conn is not None, "Expected dst_conn to be set for NestedSDFG."
                            if edge.dst_conn != data_name:
                                edge.dst.sdfg.remove_data(edge.dst_conn, validate=False)
                                if data_name not in edge.dst.sdfg.arrays:
                                    copydesc = copy.deepcopy(desc)
                                    copydesc.storage = dace.dtypes.StorageType.GPU_Global
                                    copydesc.transient = False
                                    edge.dst.sdfg.add_datadesc(data_name, copydesc)
                            rmed =  edge.dst.remove_in_connector(edge.dst_conn)
                            assert rmed, f"Expected to remove IN connector {edge.dst_conn} from {edge.dst.label}."
                            edge.dst_conn = data_name
                            edge.dst.add_in_connector(data_name, force=True)
                        elif isinstance(edge.dst, dace.nodes.AccessNode):
                            edge.dst.data = data_name
                        else:
                            # Keep the dst conn as is
                            pass


def _replace_names_in_string(text, name_mapping):
    """
    Replace names in a string based on a dictionary mapping.

    Args:
        text (str): The input string containing names to replace
        name_mapping (dict): Dictionary where keys are original names and values are replacement names

    Returns:
        str: String with names replaced according to the mapping
    """
    result = text

    # Sort keys by length (descending) to handle longer names first
    # This prevents partial replacements of longer names
    sorted_names = sorted(name_mapping.keys(), key=len, reverse=True)

    for original_name in sorted_names:
        replacement_name = name_mapping[original_name]
        result = result.replace(original_name, replacement_name)

    return result

def _replace_gpu_data_on_interstate_edges(sdfg: dace.SDFG, names_to_replace: Set[str]):
    name_dict = {n: "gpu_" + n for n in names_to_replace}
    for edge in sdfg.all_interstate_edges():
        if edge.data is not None:
            if isinstance(edge.data, dace.InterstateEdge):
                new_assignments = {}
                for k, v in edge.data.assignments.items():
                    assert isinstance(k, str)
                    assert isinstance(v, (str, CodeBlock))
                    v_str = v.as_string if isinstance(v, CodeBlock) else v
                    new_k = _replace_names_in_string(k, name_dict)
                    new_v_str = _replace_names_in_string(v_str, name_dict)
                    new_assignments[new_k] = CodeBlock(new_v_str) if isinstance(v, CodeBlock) else new_v_str
                edge.data.assignments = new_assignments
                assert edge.data.condition is None or edge.data.condition.as_string == "1",  f"Expected no condition in interstate edge {edge}: {edge.data.condition.as_string}."


def _replace_gpu_data_with_gpu_versions(
    sdfg: dace.SDFG,
    gpu_arrays: Set[str],
    within_gpu_map: bool = False,
):
    inner_sdfgs = set()
    if not within_gpu_map:
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.MapEntry) and state.scope_dict()[node] is None:
                    # Replace all data flow with GPU version:
                    # 1. If src to mapentry is access node and not GPU, replace it with GPU version
                    # 2. If dst from mapexit is access node and not GPU, replace it with GPU version
                    # 3. If gpu version of data is not in SDFG, copy it over from root SDFG
                    # 4. If in connector refers to "IN_<oldname>", "OUT_<oldname>" or "<oldname>" (nsdfg) then update connector names
                    # 4.1. Update (add/rm) connectors accordingly
                    # 5. If nsdfg, then update data descriptors to match the in connetor
                    # (Do it for all edges between map_entry and its exit node)
                    map_exit = state.exit_node(node)
                    all_nodes_between = set(state.all_nodes_between(node, map_exit)).union({node, map_exit})
                    all_edges_between = set(state.all_edges(*(all_nodes_between.union({node, map_exit}))))

                    # Replaces all edge data with GPU version of the same array
                    _replace_edge_data_with_gpu_data(sdfg, state, all_edges_between, gpu_arrays)
                    # Updates connectors to match the GPU data, also updates NSDFG descriptors and access nodes
                    _replace_connectors_and_nsdfg_desc(
                        state, all_edges_between, "gpu_", gpu_arrays
                    )
                if isinstance(node, dace.nodes.NestedSDFG):
                    # If node is NestedSDFG, then we need to replace all data descriptors in the inner SDFG
                    inner_sdfgs.add(node.sdfg)
    else:
        for state in sdfg.all_states():
            all_nodes_between = set(state.nodes())
            all_edges_between = set(state.edges())

            # Replaces all edge data with GPU version of the same array
            _replace_edge_data_with_gpu_data(sdfg, state, all_edges_between, gpu_arrays)
            # Updates connectors to match the GPU data, also updates NSDFG descriptors and access nodes
            _replace_connectors_and_nsdfg_desc(
                state, all_edges_between, "gpu_", gpu_arrays
            )
            for node in state.nodes():
                if isinstance(node, dace.nodes.NestedSDFG):
                    # If node is NestedSDFG, then we need to replace all data descriptors in the inner SDFG
                    inner_sdfgs.add(node.sdfg)

    if within_gpu_map:
        _replace_gpu_data_on_interstate_edges(sdfg, gpu_arrays)

    for inner_sdfg in inner_sdfgs:
        _replace_gpu_data_with_gpu_versions(inner_sdfg, gpu_arrays, True)

from utils.add_missing_symbols import _insert_missing_data_through_parent_scopes, add_missing_data_and_symbols_to_all_nsdfgs

def _repl(s: str, repldict):
    for k,v in repldict.items():
        s = s.replace(k, v)
    return s

def _state_in_gpu_scope(root_sdfg: dace.SDFG, state: dace.SDFGState):
    if state.sdfg.parent_nsdfg_node is None:
        return False

    parent_nsdfg_node = state.sdfg.parent_nsdfg_node
    parent_graph = None
    for n, g in root_sdfg.all_nodes_recursive():
        if n == parent_nsdfg_node:
            parent_graph = g
            break
    assert parent_graph is not None, "Expected to find parent graph for the state."
    assert isinstance(parent_graph, dace.SDFGState), "Expected parent graph to be an SDFGState."
    parent_state : dace.SDFGState = parent_graph
    scope_dict = parent_state.scope_dict()

    cur_node = parent_nsdfg_node
    parent_map_schedules = set()
    while scope_dict[cur_node] is not None:
        if isinstance(scope_dict[cur_node], dace.nodes.MapEntry):
            parent_map_schedules.add(scope_dict[cur_node].map.schedule)
        cur_node = scope_dict[cur_node]

    if dace.ScheduleType.GPU_Device in parent_map_schedules:
        return True
    return False

def _add_interstate_data(root_sdfg: dace.SDFG, sdfg: dace.SDFG, const_arrays: Set[str]):
    for edge in sdfg.all_interstate_edges():
        src: dace.ControlFlowRegion = edge.src
        dst: dace.ControlFlowRegion = edge.dst
        assert src.sdfg == dst.sdfg, "Expected interstate edge to be within the same SDFG."
        parent_nsdfg_node = src.sdfg.parent_nsdfg_node
        state = next(iter(src.sdfg.all_states()))
        is_gpu_code = _state_in_gpu_scope(root_sdfg=root_sdfg, state=state)

        if parent_nsdfg_node is None:
            continue

        parent_nsdfg_node_state = None
        parent_nsdfg_node_sdfg = None
        for n, g in root_sdfg.all_nodes_recursive():
            if n == parent_nsdfg_node:
                parent_nsdfg_node_state = g
                parent_nsdfg_node_sdfg = g.sdfg
                break
        assert parent_nsdfg_node_state is not None, "Expected to find parent NSDFG node state."
        assert isinstance(parent_nsdfg_node_state, dace.SDFGState), "Expected parent NSDFG node state to be an SDFGState."
        assert parent_nsdfg_node_sdfg is not None, "Expected to find parent NSDFG node SDFG."

        if edge.data is not None:
            free_syms = edge.data.free_symbols

            if any(("gpu_" in free_sym) for free_sym in free_syms):
                #print(free_syms)
                if not is_gpu_code:
                    replacements = dict()
                    # Create replacements
                    for free_sym in free_syms:
                        if "gpu_" in free_sym:
                            replacements[free_sym] = free_sym.replace("gpu_", "")
                            if free_sym in root_sdfg.arrays and not isinstance(root_sdfg.arrays[free_sym], dace.data.Scalar):
                                assert free_sym.replace('gpu_', '').split("_m_")[-1] in const_arrays, \
                                    f"Expected {free_sym.replace('gpu_', '').split("_m_")[-1]} to be in constant arrays\nConst arrays: {const_arrays}."
                            # replace this in the interstate edge
                            _insert_missing_data_through_parent_scopes(
                                {free_sym.replace("gpu_", "")}, parent_nsdfg_node, parent_nsdfg_node_state, parent_nsdfg_node_sdfg
                            )

                    if replacements != dict():
                        print(f"Found GPU access on interstate edge: replacing {replacements} in interstate edge {edge} ({src.sdfg.label}).")
                        print(f"Arrays are constant and can be duplicated on the Host and the GPU")

                    new_assignments = dict()
                    for k, v in edge.data.assignments.items():
                        assert isinstance(k, str)
                        assert isinstance(v, (str, CodeBlock))
                        if isinstance(v, CodeBlock):
                            new_assignments[_repl(k, replacements)] = CodeBlock(_repl(v.as_string, replacements))
                        else:
                            new_assignments[_repl(k, replacements)] = _repl(v, replacements)
                    edge.data.assignments = new_assignments

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                _add_interstate_data(root_sdfg, node.sdfg, const_arrays)

def _clean_redundant_pass_through_access_node(sdfg: dace.SDFG):
    tmp_id = 0
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode):
            assert node in graph.nodes()
            assert isinstance(graph, dace.SDFGState), "Expected graph to be an SDFGState."
            if graph.in_degree(node) == 1 and graph.out_degree(node) == 1:
                ie = graph.in_edges(node)[0]
                oe = graph.out_edges(node)[0]
                entry = graph.scope_dict()[node]
                if entry is None or not isinstance(entry, dace.nodes.MapEntry):
                    continue
                if (ie.data is not None and oe.data is not None and
                    ie.data.subset == oe.data.subset and oe.data.data == ie.data.data and
                    isinstance(graph.sdfg.arrays[node.data], dace.data.Array) and
                    not graph.sdfg.arrays[node.data].transient and
                    not isinstance(graph.sdfg.arrays[node.data], dace.data.Scalar)):
                    assign_tasklet = graph.add_tasklet(
                        f"assign_{node.data}",
                        {"_in"},
                        {"_out"},
                        f"_out = _in;",
                        language=dace.dtypes.Language.CPP
                    )
                    #raise Exception(ie, oe)
                    scalar_name, scalar = graph.sdfg.add_scalar(
                        f"tmp_{tmp_id}",
                        graph.sdfg.arrays[node.data].dtype,
                        transient=True,
                        storage=dace.dtypes.StorageType.Register
                    )
                    old_arr_name = node.data
                    # Use scalar for internal tasklet
                    node.data = f"tmp_{tmp_id}"
                    old_memlet_data = copy.deepcopy(oe.data)
                    oe.data = dace.Memlet.from_array(node.data, scalar)
                    ie.data = dace.Memlet.from_array(node.data, scalar)
                    graph.add_edge(node, None, assign_tasklet, "_in", dace.Memlet.from_array(node.data, scalar))
                    map_entry = graph.scope_dict()[node]
                    assert isinstance(map_entry, dace.nodes.MapEntry), f"Expected map entry node {map_entry}."
                    map_exit = graph.exit_node(map_entry)
                    graph.add_edge(assign_tasklet, "_out", map_exit, "IN_" + old_arr_name, copy.deepcopy(old_memlet_data))
                    an = graph.add_access(old_arr_name)
                    graph.add_edge(map_exit, "OUT_" + old_arr_name, an, None, dace.Memlet.from_array(old_arr_name, graph.sdfg.arrays[old_arr_name]))
                    map_exit.add_in_connector("IN_" + old_arr_name)
                    map_exit.add_out_connector("OUT_" + old_arr_name)
                    tmp_id += 1

def _move_scalar_access_to_original_name(sdfg: dace.SDFG):
    nsdfgs = set()
    for edge in sdfg.all_interstate_edges():
        src = edge.src
        dst = edge.dst
        iedge = edge.data
        free_syms = iedge.free_symbols
        gpu_named_scalars = set()
        for free_sym in free_syms:
            if "gpu_" in free_sym:
                desc = sdfg.arrays.get(free_sym, None)
                if desc is None and free_sym.replace("gpu_", "") in sdfg.arrays:
                    if isinstance(sdfg.arrays[free_sym.replace("gpu_", "")], dace.data.Scalar):
                        desc = sdfg.arrays[free_sym.replace("gpu_", "")]
                        gpu_named_scalars.add(free_sym)

        def _repl_gpu_to_no_gpu(s: str, gpu_named_scalars: Set[str]) -> str:
            """
            Replace 'gpu_' with '' in the string s for all gpu_named_scalars.
            """
            for gpu_scalar in gpu_named_scalars:
                s = s.replace(gpu_scalar, gpu_scalar.replace("gpu_", ""))
            return s

        new_assignments = dict()
        for k, v in iedge.assignments.items():
            assert isinstance(k, str)
            assert isinstance(v, (str, CodeBlock))
            if isinstance(v, CodeBlock):
                new_assignments[_repl_gpu_to_no_gpu(k, gpu_named_scalars)] = CodeBlock(_repl_gpu_to_no_gpu(v.as_string, gpu_named_scalars))
            else:
                new_assignments[_repl_gpu_to_no_gpu(k, gpu_named_scalars)] = _repl_gpu_to_no_gpu(v, gpu_named_scalars)
        iedge.assignments = new_assignments

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                # If node is NestedSDFG, then we need to replace all data descriptors in the inner SDFG
                nsdfgs.add(node.sdfg)
    for _inner_sdfg in nsdfgs:
        _move_scalar_access_to_original_name(_inner_sdfg)


def _gpu_offloading_wo_host_dev_copies_impl(sdfg: dace.SDFG,
                                            gpu_only_arrays: Set[str],
                                            duplicated_arrays: Set[str],
                                            parent_map_count: int,
                                            verbose: bool):
    """
    Offloads data to GPU, depending on transient / non-transient data it is copied over to GPU in the beginning
    or allocated directly on the GPU. Offloads only maps with N-parent maps and does not copy data back to host.
    """
    writes_to_arrays = _check_arrays_are_constant(sdfg, duplicated_arrays, verbose)
    constant_arrays = {n for n, w in writes_to_arrays.items() if w <= 0}
    sdfg.validate()

    all_gpu_array_names = gpu_only_arrays.union(duplicated_arrays)
    name_dict = _find_flattened_names(sdfg, all_gpu_array_names)

    _copy_nontransient_arrays_to_gpu(sdfg, name_dict, verbose)
    sdfg.validate()

    if verbose:
        print(f"Found corresponding flattened names for the OpenACC GPU data section:")
        for src_name, dst_name in name_dict.items():
            print(f"    {src_name} -> {dst_name}")
        print()
        print()

    parent_map_counts = dict()
    if verbose:
        print("Finding parent maps for each map entry node in the SDFG:")
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.MapEntry):
            num_parent_maps = get_num_parent_map_scopes(sdfg, node, graph)
            parent_map_counts[(node, graph)] = num_parent_maps
            if verbose:
                print(f"    Map {node.label} [{node.map.range}] ({graph.label}) has {num_parent_maps} parent maps.")

    # Create a set of arrays needed on the GPU (used by GPU maps)
    # And create a set of arrays that are needed on the host (used by CPU maps)
    # The intersection of this two set needs to be in the constant arrays that are duplicated both on the GPU and CPU
    gpu_arrays = set()
    host_arrays = set()
    constant_arrays = constant_arrays

    # Can't do the analysis reasonably as changes to lower SDFGs are not propagated to the parent SDFG
    # We will just assume anything used by a map with depth >= parent_map_count can be replaced with their GPU counterpart
    # We just need to make it flow to bottom
    """
    for (map_node, map_state), num_parent_maps in parent_map_counts.items():
        # If > parent_map_count then it is seq. map inside GPU
        if num_parent_maps >= parent_map_count:
            used_data = _get_data_used_by_map(map_entry=map_node, state=map_state)
            gpu_arrays |= used_data
        else:
            used_data = _get_data_used_by_map(map_entry=map_node, state=map_state)
            host_arrays |= used_data

    if verbose:
        print(f"GPU arrays used by maps with {parent_map_count} parent maps: {gpu_arrays}")
        print(f"Host arrays used by maps with {parent_map_count} parent maps: {host_arrays}")
        print()

    host_dev_arrays = gpu_arrays.intersection(host_arrays)
    is_subset = host_dev_arrays.issubset(constant_arrays)

    if verbose:
        print(f"Host-device arrays (intersection of GPU and host arrays): {host_dev_arrays}")
        print(f"Is the intersection a subset of constant arrays? {is_subset}")
        print()
        print()

    if not is_subset:
        raise Exception(
            f"GPU offloading without host-device copies is not possible for the SDFG {sdfg.name}.\n"
            f"Host-device arrays: {host_dev_arrays} are not a subset of constant arrays: {constant_arrays}.\n"
            f"The arrays that can't be duplicated are: {host_dev_arrays - constant_arrays}."
        )
    """
    for (map_node, map_state), num_parent_maps in parent_map_counts.items():
        # If > parent_map_count then it is seq. map inside GPU
        if num_parent_maps >= parent_map_count:
            used_data = _get_data_used_by_map(map_entry=map_node, state=map_state)
            gpu_arrays |= used_data
    if verbose:
        print(f"GPU arrays used by maps with >={parent_map_count} parent maps: {gpu_arrays}")

    # Only copy-in GPU arrays
    arrays_added_to_flattener = _add_gpu_copies_to_flattener(sdfg, gpu_arrays)
    if verbose:
        print(f"Arrays added as copies to flattener/deflattener nodes: {arrays_added_to_flattener}")
        print()
        print()
    sdfg.validate()

    # Replace all arrays used by GPU maps with their GPU counterparts
    _set_gpu_schedule(parent_map_counts, parent_map_count, _additional_offload_condition)
    _replace_gpu_data_with_gpu_versions(sdfg, gpu_arrays, False)

    # If we have GPU access on interstate edge on CPU scope, then convert to the CPU version, add the array, ensure it is constant data
    _add_interstate_data(sdfg, sdfg, constant_arrays)

    # Writing to non-transient scalar within a kernel is not allowed, try to fix that
    transify_kernel_scalars(sdfg)
    # If subset1 -> non-transient-an -> subset2 where subset1 == subset2 and of size 1
    # then remove the access node and replace it with an assignment tasklet and transient scalar
    # to avoid writing to data within the kernel
    _clean_redundant_pass_through_access_node(sdfg)

    # gpu___CG_p_nh_prog_nnew__m_w access has a dependency where layer n+1 depends on n

    # Add missing symbols
    _move_scalar_access_to_original_name(sdfg)
    add_missing_data_and_symbols_to_all_nsdfgs(sdfg)

    sdfg.validate()

import dace
import copy

from dace.transformation.dataflow import PruneConnectors
from dace.transformation.dataflow.prune_connectors import PruneSymbols


def clean_unused_array(root: dace.SDFG, parent_state, sdfg: dace.SDFG, verbose: bool):
    #for arr_name, arr in sdfg.arrays.items():
    used_arrays = set()
    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.AccessNode):
                used_arrays.add(n.data)
            if isinstance(n, dace.nodes.NestedSDFG):
                if n in s.nodes():
                    for ie in s.in_edges(n):
                        if ie.data is not None and ie.data.data is not None:
                            used_arrays.add(ie.data.data)

        for e in s.edges():
            if e.data is not None and e.data.data is not None:
                for arr_name in sdfg.arrays.keys():
                    if arr_name in str(e.data.data):
                        used_arrays.add(arr_name)

    """
    for s in sdfg.all_states():
        for e in s.parent_graph.in_edges(s) + s.parent_graph.out_edges(s):
            if e.data is not None and e.data.data is not None:
                for arr_name in sdfg.arrays.keys():
                    if arr_name in str(e.data.data):
                        used_arrays.add(arr_name)
    """
    for cfg in sdfg.all_control_flow_regions():
        if not isinstance(cfg, dace.SDFGState):
            for e in cfg.edges():
                if e.data is not None and e.data.assignments is not None:
                    for assignment, src in e.data.assignments.items():
                        for arr_name in sdfg.arrays.keys():
                            if arr_name in str(assignment) or arr_name in str(src):
                                used_arrays.add(arr_name)
    for s in sdfg.all_states():
        for e in s.parent_graph.in_edges(s) + s.parent_graph.out_edges(s):
            if e.data is not None and e.data.assignments is not None:
                for assignment, src in e.data.assignments.items():
                    for arr_name in sdfg.arrays.keys():
                        if arr_name in str(assignment) or arr_name in str(src):
                            used_arrays.add(arr_name)
    for e in sdfg.edges():
        if e.data is not None and e.data.assignments is not None:
            for assignment, src in e.data.assignments.items():
                for arr_name in sdfg.arrays.keys():
                    if arr_name in str(assignment) or arr_name in str(src):
                        used_arrays.add(arr_name)


    unused_arrays = set(sdfg.arrays.keys()) - used_arrays
    removed_arrays = set()
    for unused_arr_name in unused_arrays:
        if unused_arr_name in unused_arrays:
            if (isinstance(sdfg.arrays[unused_arr_name], dace.data.Array) or
                isinstance(sdfg.arrays[unused_arr_name], dace.data.Scalar) ):
                #if sdfg == root and (sdfg.arrays[unused_arr_name].transient is False):
                if sdfg.arrays[unused_arr_name].transient is False:
                    continue
                if "." in unused_arr_name:
                    continue
                if verbose:
                    print(f"Remove {unused_arr_name} from {sdfg.name}")
                arr = sdfg.arrays[unused_arr_name]
                sdfg.remove_data(unused_arr_name)
                removed_arrays.add((unused_arr_name, arr.transient))

    # If not root we need to remove in connectors and the inputs
    if root != sdfg:
        for rmed, transient in removed_arrays:
        #    nsdfg = sdfg.parent_nsdfg_node
        #if PruneConnectors().can_be_applied_to(sdfg=sdfg.parent_sdfg, nsdfg=sdfg.parent_nsdfg_node):
        #    PruneConnectors().apply_to(sdfg=sdfg.parent_sdfg, nsdfg=sdfg.parent_nsdfg_node)
        #if PruneSymbols().can_be_applied_to(sdfg=sdfg.parent_sdfg, nsdfg=sdfg.parent_nsdfg_node):
        #    PruneSymbols().apply_to(sdfg=sdfg.parent_sdfg, nsdfg=sdfg.parent_nsdfg_node)
        #    """
            # TODO fix this
            if not transient:
                continue

            nsdfg = sdfg.parent_nsdfg_node
            assert nsdfg is not None
            parent_graph: dace.SDFGState = parent_state
            assert parent_graph is not None

            stack = [(nsdfg, rmed)]
            assert transient or rmed in nsdfg.in_connectors or rmed in nsdfg.out_connectors, f"{rmed} not in {nsdfg.in_connectors} or {nsdfg.out_connectors}"
            """
            print(stack)
            while len(stack) > 0:
                n, dst_conn = stack.pop()
                if dst_conn is not None:
                    ies = list(parent_graph.in_edges_by_connector(n, dst_conn))
                    print(ies)
                else:
                    ies = list(parent_graph.in_edges(n))
                if dst_conn is not None:
                    for ie in ies:
                        stack.append((ie.src, ie.src_conn.replace("OUT_", "IN_") if ie.src_conn is not None else ie.src_conn))
                for ie in ies:
                    print(f"Remove {ie}")
                    parent_graph.remove_edge(ie)
                    ie.src.remove_out_connector(ie.src_conn)
                    ie.dst.remove_in_connector(ie.dst_conn)
                print(stack)
            """

        for n in parent_state.nodes():
            if parent_state.in_degree(n) == 0 and parent_state.out_degree(n) == 0:
                parent_state.remove_node(n)
                # print(f"Remove {n}")
    if verbose:
        print(f"Cleaned {len(removed_arrays)} ({removed_arrays} of {unused_arrays}) from {sdfg.name}")

    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                if n in s.nodes():
                    clean_unused_array(root, s, n.sdfg, verbose)


def simplify_recursive(root: dace.SDFG, sdfg: dace.SDFG, verbose: bool):
    sdfg.simplify(skip=["StateFusion"])
    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                simplify_recursive(root, n.sdfg, verbose)

def move_transients_to_top_level(root: dace.SDFG,
                                 upper_bounds = dict[str, int],
                                 verbose=False,
                                 only=None,
                                 ilifetime=None,
                                 no_dim_change=False,
                                 offset:int=0,
                                 set_zero:bool=False):
    # If we have a transient array, make it live on the top level SDFG
    # For this, collect all transients that do not exist on top level SDFG
    # Add them to top level SDFG, if they are arrays and have storage location Default
    #
    # for s in sdfg.states():
    #    for n in s.nodes():
    #        if isinstance(n, dace.nodes.NestedSDFG):
    #            self.move_transients_to_top_level(roots + [sdfg], n.sdfg)
    #simplify_recursive(root, root, verbose)
    root.validate()
    #root.simplify()
    clean_unused_array(root, None, root, verbose)
    # root.save("uwu.sdfgz", compress=True)
    root.validate()

    # Add arrays from bottom to up
    arrays_added = dict()
    map_chain = []
    for sdfg, arr_name, arr in root.arrays_recursive():
        #print(sdfg, arr_name)
        #if arr_name == "z_w_con_c":
        #    print(f"z_w_con_c: {sdfg.label}, {root.label}")
        if sdfg != root:
            if (
                arr.transient
                and isinstance(arr, dace.data.Array)
                and arr.shape != (1,)
            ):
                #if arr_name == "z_w_con_c":
                #    print(f"z_w_con_c: {arr}, {arr.shape}, type(arr): {type(arr)}, {arr.storage}")
                if (
                    arr.storage == dace.dtypes.StorageType.Default
                    or arr.storage == dace.dtypes.CPU_Heap
                    or arr.storage == dace.dtypes.GPU_Global
                ):
                    if only is not None and arr_name not in only:
                        continue
                    #print(f"Move {arr_name} from {sdfg.name} to {root.name}")
                    arr.transient = False
                    # As we go up, we need to understand how this array used
                    # Map with N threads using a (S1, S2) shape array will need
                    # (S1, S2, N) shape which each thread assigned to one of the Ns
                    ways_up = 0
                    _sdfg = sdfg
                    while _sdfg is not None and _sdfg != root:
                        _sdfg = _sdfg.parent_sdfg
                        ways_up += 1
                    #print(f"{arr_name} needs to be moved {ways_up} level{'s' if ways_up == 1 else ''} up")
                    if ways_up != 1:
                        # root.save("move_transient_failing.sdfgz", compress=True)
                        raise Exception(f"Moving transients to top level only supports if the transient needs to be moved once currently, {arr_name}, {arr}, {ways_up} in sdfg: {root.name}")

                    # To support more than 1 level need to check nested SDFGs and the map chain
                    _sdfg = sdfg
                    while _sdfg is not None and _sdfg != root:
                        parent = _sdfg.parent_sdfg
                        for state in parent.all_states():
                            for node in state.nodes():
                                if isinstance(node, dace.nodes.MapEntry):
                                    _nodes = [_n for _n in state.all_nodes_between(node, state.exit_node(node))]
                                    for _n in _nodes:
                                        if isinstance(_n, dace.nodes.NestedSDFG) and arr_name in _n.sdfg.arrays:
                                            if _n not in map_chain:
                                                map_chain.append((parent, _n.sdfg, _n, node, arr_name))
                        _sdfg = _sdfg.parent_sdfg
                    #print(f"{arr_name} needs to be moved {ways_up} through {map_chain}")

                    """
                    _sdfg = sdfg
                    while _sdfg is not None:
                        if _sdfg == root:
                            if arr_name not in _sdfg.arrays:
                                arr2 = copy.deepcopy(arr)
                                if sdfg == root:
                                    arr2.transient = True
                                else:
                                    arr2.transient = False
                                _sdfg.add_datadesc(arr_name, arr2)
                        else:
                            if arr_name not in sdfg.arrays:
                                arr2 = copy.deepcopy(arr)
                                if sdfg == root:
                                    arr2.transient = True
                                else:
                                    arr2.transient = False
                                _sdfg.add_datadesc(arr_name, arr2)
                        if _sdfg not in arrays_added:
                            arrays_added[_sdfg] = set([arr_name])
                        else:
                            arrays_added[_sdfg].add(arr_name)

                        _sdfg = _sdfg.parent_sdfg
                    """

    if upper_bounds is None:
        upper_bounds = dict()

    for parent_sdfg, child_sdfg, nsdfg, map_entry, arr_name in map_chain:
        assert type(map_entry) == dace.nodes.MapEntry
        assert type(parent_sdfg) == dace.SDFG
        assert type(child_sdfg) == dace.SDFG
        assert type(nsdfg) == dace.nodes.NestedSDFG
        arr_desc: dace.data.Data = child_sdfg.arrays[arr_name]
        assert len(map_entry.map.range) == 1
        if arr_name in upper_bounds:
            bound = upper_bounds[arr_name] if isinstance(upper_bounds[arr_name], int) else dace.symbolic.symbol(upper_bounds[arr_name])
            lifetime = dace.AllocationLifetime.SDFG
            if bound not in child_sdfg.symbols:
                child_sdfg.add_symbol(str(bound), dace.int32, False)
                nsdfg.symbol_mapping[str(bound)] = str(bound)
        else:
            b, e, s = map_entry.map.range[0]
            bound = (e+1-b)//s
            lifetime = dace.AllocationLifetime.Scope
            if ilifetime is not None:
                lifetime = ilifetime # can break but if user passed something they should now it
            for bs in bound.free_symbols:
                child_sdfg.add_symbol(bs, dace.int32, False)
                nsdfg.symbol_mapping[bs] = bs

        assert arr_desc.start_offset == 0, f"{arr_desc}, {arr_desc.start_offset}"
        if not no_dim_change:
            old_desc = arr_desc
            old_shape = list(arr_desc.shape)
            old_strides  = list(arr_desc.strides)
            from sympy import symbols, simplify
            from functools import reduce
            import operator

            def check_col_major_strides(lst, second_list):
                if not second_list or second_list[0] != 1:
                    return False
                expected = [1]
                for i in range(1, len(second_list)):
                    prod = reduce(operator.mul, lst[:i], 1)
                    expected.append(prod)
                return all(simplify(e - a) == 0 for e, a in zip(expected, second_list))
            assert check_col_major_strides(old_shape, old_strides), f"{arr_name}, desc:{old_desc}, {old_shape}, {old_strides}"

            prod = reduce(operator.mul, arr_desc.shape[:], 1)
            assert all(arr_desc.offset[i] == 0 for i in range(len(arr_desc.offset))), f"{arr_desc}, {arr_desc.offset}"
            new_desc = dace.data.Array(
                dtype=arr_desc.dtype,
                shape=list(arr_desc.shape) + [bound],
                strides=list(arr_desc.strides) + [prod],
                transient=True,
                storage=arr_desc.storage,
                location=arr_desc.location,
                allow_conflicts=arr_desc.allow_conflicts,
                offset=list(arr_desc.offset) + [0],
                may_alias=arr_desc.may_alias,
                lifetime=lifetime,
                alignment=arr_desc.alignment,
                debuginfo=arr_desc.debuginfo,
                start_offset=0,
            )
        else:
            new_desc = copy.deepcopy(arr_desc)
            new_desc.transient = True
        copy_new_desc = copy.deepcopy(new_desc)
        copy_new_desc.transient = False
        child_sdfg.remove_data(arr_name, False)
        if arr_name in parent_sdfg.arrays:
            parent_sdfg.remove_data(arr_name, False)
        parent_sdfg.add_datadesc(arr_name, new_desc)
        child_sdfg.add_datadesc(arr_name, copy_new_desc)

        # Add the final dimension that depends on the map iterator
        map_param_strs = map_entry.map.params
        assert len(map_param_strs) == 1
        map_param_str = map_param_strs[0]
        param_sym = dace.symbolic.symbol(map_param_str)

        # Replace all memlets
        for state in child_sdfg.all_states():
            for edge in state.edges():
                if edge.data.data == arr_name:
                    mem_range = copy.deepcopy(edge.data.subset)
                    mem_range_list = []
                    for b,e,s in mem_range.ranges:
                        mem_range_list += [(b, e, s)]
                    if not no_dim_change:
                        if offset == 0:
                            mem_range_list += [(param_sym, param_sym, 1)]
                        else:
                            mem_range_list += [(param_sym+offset, param_sym+offset, 1)]
                    state.remove_edge(edge)
                    state.add_edge(
                        edge.src,
                        edge.src_conn,
                        edge.dst,
                        edge.dst_conn,
                        dace.memlet.Memlet(data=edge.data.data,
                                            subset=dace.subsets.Range(mem_range_list))
                    )


        # Pass accesses

        # Check if we have a write, if we have a write, then add exit edge too
        has_write = False
        for state in child_sdfg.all_states():
            for edge in state.edges():
                if isinstance(edge.dst, dace.nodes.AccessNode):
                    if edge.dst.data == arr_name:
                        has_write = True
                        break

        parent_state = [s for s in parent_sdfg.all_states() if map_entry in s.nodes()]
        assert len(parent_state) == 1
        parent_state = parent_state[0]

        map_exit = parent_state.exit_node(map_entry)
        if "IN_" + arr_name not in map_entry.in_connectors:
            a0 = parent_state.add_access(arr_name)
            if set_zero:
                a0.setzero = True
            map_entry.add_in_connector("IN_" + arr_name)
            map_entry.add_out_connector("OUT_" + arr_name)
            map_exit = parent_state.exit_node(map_entry)
            nsdfg.add_in_connector(arr_name)

            parent_state.add_edge(
                a0,
                None,
                map_entry,
                "IN_" + arr_name,
                dace.memlet.Memlet.from_array(arr_name, new_desc),
            )
            parent_state.add_edge(
                map_entry,
                "OUT_" + arr_name,
                nsdfg,
                arr_name,
                dace.memlet.Memlet.from_array(arr_name, new_desc),
            )
        #if arr_name == "z_w_con_c":
        #    print(f"z_w_con_c: {arr_name}, {new_desc}")
        #    if map_exit in parent_state.nodes():
        #        for oe in parent_state.out_edges(map_exit):
        #            if isinstance(oe.dst, dace.nodes.AccessNode):
        #                if oe.dst.data == arr_name:
        #                    print(f"z_w_con_c: {oe}")
        #                    raise Exception("uwu")
        if ("OUT_" + arr_name not in map_exit.out_connectors) and has_write:
            #print(has_write, map_exit.out_connectors)
            #raise Exception(f"{map_exit} not in {parent_state.nodes()}")
            a1 = parent_state.add_access(arr_name)
            map_exit.add_in_connector("IN_" + arr_name)
            map_exit.add_out_connector("OUT_" + arr_name)
            nsdfg.add_out_connector(arr_name, force=True)
            parent_state.add_edge(
                nsdfg,
                arr_name,
                map_exit,
                "IN_" + arr_name,
                dace.memlet.Memlet.from_array(arr_name, new_desc),
            )
            parent_state.add_edge(
                map_exit,
                "OUT_" + arr_name,
                a1,
                None,
                dace.memlet.Memlet.from_array(arr_name, new_desc),
            )

    root.validate()
    return arrays_added

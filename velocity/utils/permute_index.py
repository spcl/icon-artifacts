import dace
from typing import Dict, List

from dace.transformation.dataflow.map_dim_shuffle import MapDimShuffle

def permute_index(root: dace.SDFG, sdfg: dace.SDFG, permute_map : Dict[str, List[int]]):
    if root == sdfg:
        s = sdfg.add_state_before(sdfg.start_state, "transpose")
        permuted_arrays = dict()
        name_map = dict()
        for arr_name, _arr in list(sdfg.arrays.items()):
            if arr_name in permute_map:
                permute_indices = permute_map[arr_name]
                arr: dace.data.Data = _arr

                arr_shape = arr.shape
                arr_strides = arr.strides

                per_shape = []
                for i in permute_indices:
                    per_shape.append(arr_shape[i])

                per_arr = dace.data.Array(
                    dtype=arr.dtype,
                    shape=per_shape,
                    transient=True,
                    allow_conflicts=arr.allow_conflicts,
                    storage=arr.storage,
                    alignment=arr.alignment,
                    lifetime=arr.lifetime,
                )
                sdfg.add_datadesc("per_" + arr_name, per_arr)
                assert arr.offset == tuple([0] * len(arr_shape)), f"{arr.offset}"
                name_map[arr_name] = "per_" + arr_name
        for oldn, newn in name_map.items():
            olda = s.add_access(oldn)
            newa = s.add_access(newn)
            range_dict = dict()
            for i in range(len(permute_indices)):
                range_dict[f"i{i}"] = f"0:{arr_shape[i]}"
            map_entry, map_exit = s.add_map("transpose_impl", range_dict)
            src_access = ", ".join(f"i{i}" for i in range(len(permute_indices)))
            dst_access = ", ".join(f"i{permute_indices[i]}" for i in range(len(permute_indices)))
            map_entry.add_in_connector("IN_" + oldn)
            map_entry.add_out_connector("OUT_" + oldn)
            map_exit.add_in_connector("IN_" + newn)
            map_exit.add_out_connector("OUT_" + newn)
            s.add_edge(olda, None, map_entry, "IN_" + oldn,
                       dace.Memlet.from_array(oldn, sdfg.arrays[oldn]))
            s.add_edge(map_exit, "OUT_" + newn, newa, None,
                       dace.Memlet.from_array(newn, sdfg.arrays[newn]))
            t= s.add_tasklet("assign", {"_in1"}, {"_out1"}, f"_out1 = _in1")
            s.add_edge(map_entry, "OUT_" + oldn, t, "_in1",
                       dace.Memlet(expr=f"{oldn}[{src_access}]"))
            s.add_edge(t, "_out1", map_exit, "IN_" + newn,
                       dace.Memlet(expr=f"{newn}[{dst_access}]"))

        final_block = [v for v in sdfg.nodes() if sdfg.out_degree(v) == 0][0]
        s2 = sdfg.add_state_after(final_block, "transpose2")
        for oldn, newn in name_map.items():
            olda = s2.add_access(oldn)
            newa = s2.add_access(newn)
            range_dict = dict()
            for i in range(len(permute_indices)):
                range_dict[f"i{i}"] = f"0:{arr_shape[i]}"
            map_entry, map_exit = s2.add_map("transpose_impl", range_dict)
            src_access = ", ".join(f"i{i}" for i in range(len(permute_indices)))
            dst_access = ", ".join(f"i{permute_indices[i]}" for i in range(len(permute_indices)))
            map_entry.add_in_connector("IN_" + newn)
            map_entry.add_out_connector("OUT_" + newn)
            map_exit.add_in_connector("IN_" + oldn)
            map_exit.add_out_connector("OUT_" + oldn)
            s2.add_edge(newa, None, map_entry, "IN_" + newn,
                       dace.Memlet.from_array(newn, sdfg.arrays[newn]))
            s2.add_edge(map_exit, "OUT_" + oldn, olda, None,
                       dace.Memlet.from_array(oldn, sdfg.arrays[oldn]))

            t= s2.add_tasklet("assign", {"_in1"}, {"_out1"}, f"_out1 = _in1")
            s2.add_edge(map_entry, "OUT_" + newn, t, "_in1",
                       dace.Memlet(expr=f"{newn}[{dst_access}]"))
            s2.add_edge(t, "_out1", map_exit, "IN_" + oldn,
                       dace.Memlet(expr=f"{oldn}[{src_access}]"))
    else:
        # Replace the array with shape
        name_map = dict()
        arr_add = dict()
        for arr_name, _arr in list(sdfg.arrays.items()):
            if arr_name in permute_map:
                permute_indices = permute_map[arr_name]
                arr: dace.data.Data = _arr
                arr_shape = arr.shape

                per_shape = []
                if len(arr.shape) != len(permute_indices):
                    continue
                for i in permute_indices:
                    #print(arr_shape, permute_indices, arr_name, permute_map)
                    per_shape.append(arr_shape[i])

                per_arr = dace.data.Array(
                    dtype=arr.dtype,
                    shape=per_shape,
                    transient=arr.transient,
                    allow_conflicts=arr.allow_conflicts,
                    storage=arr.storage,
                    alignment=arr.alignment,
                    lifetime=arr.lifetime,
                )
                sdfg.remove_data(arr_name, validate=False)
                sdfg.add_datadesc(arr_name, per_arr)
                assert arr.offset == tuple([0] * len(arr_shape)), f"{arr.offset}"

                name_map[arr_name] = arr_name

    for s in sdfg.all_states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                new_permute_map = dict()
                for ie in s.in_edges(n):
                    src_name = ie.data.data
                    dst_name = ie.dst_conn
                    if src_name in permute_map:
                        new_permute_map[dst_name] = permute_map[src_name]
                permute_index(root, n.sdfg, new_permute_map)

    final_block = [v for v in sdfg.nodes() if sdfg.out_degree(v) == 0][0]
    for s in sdfg.all_states():
        if sdfg == root and (s == sdfg.start_block or s == final_block):
            continue
        for n in s.nodes():
            if isinstance(n, dace.nodes.AccessNode):
                if n.data in name_map:
                    n.data = name_map[n.data]
        for e in s.edges():
            if e.data.data in name_map:
                if e.dst_conn == "IN_" + e.data.data:
                    e.dst_conn = "IN_" + name_map[e.data.data]
                    e.dst.remove_in_connector("IN_" + e.data.data)
                    e.dst.add_in_connector("IN_" + name_map[e.data.data])
                if e.src_conn == "OUT_" + e.data.data:
                    e.src_conn = "OUT_" + name_map[e.data.data]
                    e.src.remove_out_connector("OUT_" + e.data.data)
                    e.src.add_out_connector("OUT_" + name_map[e.data.data])
                oldn = e.data.data
                e.data.data = name_map[e.data.data]
                new_subset = []
                permute_indices = permute_map[oldn]
                for i in range(len(permute_indices)):
                    new_subset.append(e.data.subset[permute_indices[i]])
                e.data.subset = dace.subsets.Range(new_subset)

def permute_maps(sdfg: dace.SDFG, permute_map : Dict[str, List[int]]):
    for s, g in sdfg.all_nodes_recursive():
        if isinstance(s, dace.SDFGState):
            for n in s.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    old_params = n.map.params
                    new_params = []
                    if n.map.label in permute_map:
                        for j in range(len(permute_map[n.map.label])):
                            new_params.append(old_params[permute_map[n.map.label][j]])
                        MapDimShuffle.apply_to(sdfg, map_entry=n, options={"parameters": new_params})
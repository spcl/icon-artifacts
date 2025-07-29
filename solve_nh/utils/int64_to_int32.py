import os
import dace

from typing import Dict

# Replace all int64 symbols and arrays with int32
def _int64_to_int32_impl(root: dace.SDFG, sdfg: dace.SDFG, mapping: Dict[str, dace.typeclass], verbose: bool = False):
    num_converted = 0
    for arr_name, arr in sdfg.arrays.items():
        if arr.transient:
            if arr.dtype == dace.int64:
                arr.dtype = dace.int32
                if arr_name in mapping:
                    assert mapping[arr_name] == dace.int32
                mapping[arr_name] = dace.int32
                if verbose:
                    print(f"Converted transient array {arr_name} from int64 to int32.")
                num_converted += 1
            else:
                if arr_name in mapping:
                    assert mapping[arr_name] == arr.dtype
                mapping[arr_name] = arr.dtype
        else:
            if arr_name in mapping:
                assert mapping[arr_name] == arr.dtype
            mapping[arr_name] = arr.dtype
    for sym_name, sym_type in sdfg.symbols.items():
        if sym_name not in sdfg.free_symbols:
            if sym_type == dace.int64:
                if sym_name in mapping:
                    assert mapping[sym_name] == dace.int32
                sdfg.symbols[sym_name] = dace.int32
                mapping[sym_name] = dace.int32
                if verbose:
                    print(f"Converted symbol {sym_name} from int64 to int32.")
                num_converted += 1
            else:
                if sym_name in mapping:
                    assert mapping[sym_name] == dace.int32
                mapping[sym_name] = sym_type
        else:
            if sym_name in mapping:
                assert mapping[sym_name] == dace.int32
            mapping[sym_name] = sym_type

    nsdfgs = set()
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                # Make sure in connector (and inner data) types match
                for inconn_name, inconn_type in node.in_connectors.items():
                    if inconn_type != mapping[inconn_name]:
                        node.in_connectors[inconn_name] = mapping[inconn_name]
                        if inconn_name in node.sdfg.arrays:
                            node.sdfg.arrays[inconn_name].dtype = mapping[inconn_name]
                        if verbose:
                            print(f"Converted nested SDFG connector {inconn_name} from {inconn_type} to {mapping[inconn_name]}.")
                        num_converted += 1
                # Make sure out connector (and inner data) types match
                for outconn_name, outconn_type in node.out_connectors.items():
                    if outconn_type != mapping[outconn_name]:
                        node.out_connectors[outconn_name] = mapping[outconn_name]
                        if outconn_name in node.sdfg.arrays:
                            node.sdfg.arrays[outconn_name].dtype = mapping[outconn_name]
                        if verbose:
                            print(f"Converted nested SDFG connector {outconn_name} from {outconn_type} to {mapping[outconn_name]}.")
                        num_converted += 1
                # Make sure symbol types match
                for name, dtype in mapping.items():
                    if name in node.sdfg.symbols:
                        if node.sdfg.symbols[name] != dtype:
                            node.sdfg.symbols[name] = dtype
                            if verbose:
                                print(f"Converted nested SDFG symbol {name} from {node.sdfg.symbols[name]} to {dtype}.")
                        num_converted += 1

                nsdfgs.add(node.sdfg)


    for nsdfg in nsdfgs:
        num_converted += _int64_to_int32_impl(sdfg, nsdfg, mapping, verbose)

    return num_converted

def int64_to_int32(sdfg: dace.SDFG):
    verbose = os.getenv("VERBOSE", "1").lower() in ("1", "true", "yes")
    num_converted_types = _int64_to_int32_impl(sdfg, sdfg, dict(), verbose)
    if verbose:
        print(f"Total converted types: {num_converted_types}")
import dace
import numpy

# Replace all int64 symbols and arrays with int32
def int64_to_int32(sdfg: dace.SDFG):
    for arr_name, arr in sdfg.arrays.items():
        if arr.dtype == dace.int64:
            arr.dtype = dace.int32
        if arr_name == "i_startidx_var_148":
            raise Exception(arr_name)
    for sym_name, sym_type in sdfg.symbols.items():
        if sym_type == dace.int64:
            sdfg.symbols[sym_name] = dace.int32
        if sym_name == "i_startidx_var_148":
            raise Exception(sym_name)

    nsdfgs = set()
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                for inconn_name, inconn_type in node.in_connectors.items():
                    if inconn_name == "i_startidx_var_148":
                        raise Exception(sym_name)
                    #print(inconn_name, inconn_type)
                    if inconn_type == dace.int64:
                        node.in_connectors[inconn_name] = dace.int32
                        #print(inconn_name, inconn_type, node.in_connectors[inconn_name])
                for outconn_name, outconn_type in node.out_connectors.items():
                    if outconn_type == dace.int64:
                        #print(outconn_name, outconn_type, node.out_connectors[outconn_name])
                        pass
                    if outconn_name == "i_startidx_var_148":
                        raise Exception(sym_name)
                nsdfgs.add(node.sdfg)


    for nsdfg in nsdfgs:
        int64_to_int32(nsdfg)
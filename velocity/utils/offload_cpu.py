import dace


def offload_cpu(sdfg: dace.SDFG):
    block_param_strings = {"startblk", "endblk", "replaced_var"}

    # Recursively search, if map does not have block param strings then offload
    # If not offloaded continue further down

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.MapEntry):
                s1 = " ".join({str(s) for s in node.map.params})
                s2 = " ".join({str(b) + " " + str(e) + " " + str(s) for (b,e,s) in node.map.range})
                s = s1 + " " + s2
                if any(bs in s for bs in block_param_strings):
                    #raise Exception(s, block_param_strings)
                    node.map.schedule = dace.ScheduleType.Sequential
                else:
                    # Block map continue
                    node.map.schedule = dace.ScheduleType.CPU_Multicore
                    if len(node.map.params) > 1:
                        node.map.collapse = 2

    nsdfgs = set()
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                parent_map = state.scope_dict()[node]
                if parent_map.schedule == dace.ScheduleType.Sequential:
                    nsdfgs.add(node.sdfg)
    
    for nsdfg in nsdfgs:
        offload_cpu(nsdfg.sdfg)
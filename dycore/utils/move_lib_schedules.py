import dace

def move_lib_schedules(sdfg: dace.SDFG, schedule: dace.dtypes.ScheduleType):
    for state in sdfg.all_states():
        sdict = state.scope_dict()
        for node in state.nodes():
            if isinstance(node, dace.nodes.LibraryNode):
                # Move the schedule to the top level
                if sdict is None or sdict[node] is None:
                    node.schedule = schedule
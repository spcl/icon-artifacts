import dace
import typing
from pathlib import Path

def change_flatten_lib_to_shallow_copy(sdfg: dace.SDFG, shallow_copy_used_structs: typing.List[str],
                                       deflatten_used_structs = typing.List[str]) -> None:
    states = sdfg.all_states()
    flatten_node = None
    flatten_state : dace.SDFGState = None
    deflatten_node = None
    deflatten_state : dace.SDFGState= None
    for state in states:
        for node in state.nodes():
            if isinstance(node, dace.nodes.LibraryNode):
                if "flatten" == node.label:
                    flatten_node = node
                    flatten_state = state
                elif "deflatten" == node.label:
                    deflatten_node = node
                    deflatten_state = state


    assert flatten_node is not None
    assert deflatten_node is not None

    # Delete flatten nodes completely as we do not need to copy out explicitly anymore
    # Nproma is constant so no real copy out necessary
    deflatten_sources = {ie.src for ie in deflatten_state.in_edges(deflatten_node)}
    deflatten_destinations = {ie.dst for ie in deflatten_state.out_edges(deflatten_node)}

    deflatten_state.remove_node(deflatten_node)

    for src in deflatten_sources:
        if deflatten_state.in_degree(src) == 0 and deflatten_state.out_degree(src) == 0:
            deflatten_state.remove_node(src)
        elif deflatten_state.in_degree(src) == 1:
            ie_ie = deflatten_state.in_edges(src)[0]
            if isinstance(ie_ie.src, dace.nodes.AccessNode) and ie_ie.src.data == "gpu_" + src.data:
                deflatten_state.remove_node(ie_ie.src)
                deflatten_state.remove_node(src)
    for dst in deflatten_destinations:
        if deflatten_state.out_degree(dst) == 0 and deflatten_state.in_degree(dst) == 0:
            deflatten_state.remove_node(dst)


    root_path = Path(__file__).parent
    deflatten_codefile_name = sdfg.label + "_deflattener_code.cpp"
    tasklet_src_file = root_path / ".." / deflatten_codefile_name

    with open(tasklet_src_file, 'r') as f:
        file_content = f.read()

    shallow_deflatten_tasklet = deflatten_state.add_tasklet(name="shallow_deflatten",
        inputs=set(),
        outputs=set(),
        code=file_content,
        language=dace.Language.CPP,
        side_effects=True
    )
    s = file_content
    # :-1 is to remove the last semicolon
    rhs_set = {line.split('=')[1][:-1].strip() for line in s.strip().splitlines() if '=' in line}

    src_names = {src.data for src in deflatten_sources}
    _src_names = {src.data for src in deflatten_sources}
    for name in rhs_set:
        if name in src_names:
            src = [src for src in deflatten_sources if src.data == name][0]
            deflatten_state.add_edge(src, None, shallow_deflatten_tasklet, None, dace.Memlet())
        else:
            a = deflatten_state.add_access(name)
            deflatten_state.add_edge(a, None, shallow_deflatten_tasklet, None, dace.Memlet())

    for arr in shallow_copy_used_structs:
        a = deflatten_state.add_access(arr)
        deflatten_state.add_edge(a, None, shallow_deflatten_tasklet, None, dace.Memlet())


    #==================================================================================

    flatten_sources = {ie.src for ie in flatten_state.in_edges(flatten_node)}
    flatten_destinations = {ie.dst for ie in flatten_state.out_edges(flatten_node)}

    flatten_state.remove_node(flatten_node)

    root_path = Path(__file__).parent
    flatten_codefile_name = sdfg.label + "_flattener_code.cpp"
    tasklet_src_file = root_path / ".." / flatten_codefile_name

    with open(tasklet_src_file, 'r') as f:
        file_content = f.read()

    shallow_copy_tasklet = flatten_state.add_tasklet(name="shallow_flatten",
        inputs=set(),
        outputs=set(),
        code=file_content,
        language=dace.Language.CPP,
        side_effects=True
    )
    s = file_content
    lhs_set = {line.split('=')[0].strip() for line in s.strip().splitlines() if '=' in line}

    src_names = {src.data for src in flatten_sources}
    for src in flatten_sources:
        if src.data in shallow_copy_used_structs or src.data in lhs_set:
            flatten_state.add_edge(src, None, shallow_copy_tasklet, None, dace.Memlet())
    for _item in lhs_set:
        if _item not in src_names:
            access_node = flatten_state.add_access(_item)
            flatten_state.add_edge(access_node, None, shallow_copy_tasklet, None, dace.Memlet())

    #print(flatten_destinations)
    #raise Exception(flatten_destinations, [flatten_state.out_degree(dst) for dst in flatten_destinations])
    for src in flatten_sources:
        if flatten_state.in_degree(src) == 0 and flatten_state.out_degree(src) == 0:
            flatten_state.remove_node(src)
    for dst in flatten_destinations:
        #print(dst, flatten_state.out_degree(dst) == 0, flatten_state.in_degree(dst) == 0)
        if flatten_state.out_degree(dst) == 0 and flatten_state.in_degree(dst) == 0:
            flatten_state.remove_node(dst)
        elif flatten_state.out_degree(dst) == 1:
            oe_oe = flatten_state.out_edges(dst)[0]
            #print("oe_oe", isinstance(oe_oe.dst, dace.nodes.AccessNode))
            if isinstance(oe_oe.dst, dace.nodes.AccessNode):
                #print(oe_oe.dst.data.startswith("gpu_"), dst.data in oe_oe.dst.data)
                if oe_oe.dst.data.startswith("gpu_") and dst.data in oe_oe.dst.data:
                    flatten_state.remove_node(oe_oe.dst)
                    flatten_state.remove_node(dst)

    return _src_names.union(src_names)
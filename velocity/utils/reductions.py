import dace
from dace.libraries.standard import CodeLibraryNode
from dace.properties import make_properties, Property
from utils import find_node_by_name
from dace.transformation.passes.analysis import loop_analysis
from dace.sdfg.state import ControlFlowRegion, LoopRegion

@make_properties
class LibNode(CodeLibraryNode):
    code = Property(dtype=str, default="", allow_none=False)

    def __init__(self, name, input_names, output_names, code):
        super().__init__(name=name, input_names=input_names, output_names=output_names)
        self.code = code

    def generate_code(self, inputs, outputs):
        if (
            inputs["in_arr"].storage == dace.StorageType.GPU_Global
            or inputs["in_size"].storage == dace.StorageType.GPU_Shared
        ):
            return f"""
            #define __REDUCE_GPU__
            {self.code}
            #undef __REDUCE_GPU__
            """

        return self.code


def _insert_reduction(
    parent: ControlFlowRegion,
    state: dace.SDFGState,
    in_name: str,
    in_size: str,
    out_name: str,
    type: str,
    in_expr: str = None,
    out_expr: str = None,
):
    """
    Adds a reduction node to the state after the given state.
    """
    red_state = parent.add_state_after(state)

    # Choose the library node
    red_node = LibNode(
        name=f"reduce_{type}",
        input_names=["in_arr", "in_size"],
        output_names=["out"],
        code=f"""
        #ifdef __REDUCE_DEVICE__
          out = reduce_{type}_device(in_arr, in_size);
        #elif defined(__REDUCE_GPU__)
          out = reduce_{type}_gpu(in_arr, in_size);
        #else
          out = reduce_{type}_cpu(in_arr, in_size);
        #endif
        """,
    )

    # Route array
    in_expr = in_expr if in_expr is not None else in_name
    in_access = None
    if in_name in parent.sdfg.arrays:
        in_access = red_state.add_read(in_name)
    else:
        in_access_task = red_state.add_tasklet(
            f"read_{in_name}", {}, {"out"}, f"out = {in_name}"
        )
        in_sym = parent.sdfg.symbols[in_name]
        in_access_name, in_arr = red_state.sdfg.add_scalar(
            f"reduce_{type}_in",
            dtype=in_sym.dtype,
            transient=True,
            find_new_name=True,
        )
        in_access = red_state.add_read(in_access_name)
        in_expr = in_access_name if in_expr is in_name else in_expr
        red_state.add_edge(
            in_access_task,
            "out",
            in_access,
            None,
            dace.Memlet.from_array(in_access_name, in_arr),
        )
    red_state.add_nedge(in_access, red_node, dace.Memlet(in_expr))

    # Route size
    size_task = red_state.add_tasklet(
        f"size_reduce_{type}", {}, {"size"}, f"size = {in_size}"
    )
    size_name, _ = red_state.sdfg.add_scalar(
        f"reduce_{type}_size",
        dtype=dace.int32,
        transient=True,
        find_new_name=True,
    )
    size_access = red_state.add_access(size_name)

    red_state.add_edge(size_task, "size", size_access, None, dace.Memlet(size_name))
    red_state.add_edge(
        size_access, None, red_node, "in_size", dace.Memlet(size_name)
    )

    # Route output
    if out_expr is None:
        arr_name, arr = red_state.sdfg.add_scalar(
            "out_val",
            dtype=dace.float64,
            transient=True,
            find_new_name=True,
        )
        red_state.add_nedge(
            red_node,
            red_state.add_write(arr_name),
            dace.Memlet.from_array(arr_name, arr),
        )
        parent.add_state_after(red_state, assignments={out_name: f"{arr_name}"})
    else:
        red_state.add_nedge(
            red_node, red_state.add_write(out_name), dace.Memlet(out_expr)
        )

    return red_state


def loop_to_max_reduction(sdfg: dace.SDFG, loop_name, task_name):
    """
    Turns the max loop at the end of the SDFG into a reduction.
    """
    loop_node, _ = find_node_by_name(sdfg, loop_name)
    start = str(loop_analysis.get_init_assignment(loop_node))
    end = str(loop_analysis.get_loop_end(loop_node))
    vcfl_name = None
    for name in sdfg.arrays.keys():
        if "vcflmax" in name:
            vcfl_name = name
            break
    assert vcfl_name is not None, "vcflmax not found"

    var_name = list(
        loop_node.nodes()[0].branches[0][0].get_free_symbols() - loop_node.free_symbols
    )
    assert len(var_name) == 1
    _insert_reduction(
        sdfg,
        loop_node,
        vcfl_name,
        f"{end} - {start}",
        f"{var_name[0]}",
        "maxZ",
        in_expr=f"{vcfl_name}[{start}-1:{end}-1]",
    )
    pre_state = sdfg.add_state_before(loop_node)
    post_state = sdfg.add_state_after(loop_node)
    sdfg.remove_node(loop_node)
    sdfg.add_edge(pre_state, post_state, dace.InterstateEdge())
    task, _ = find_node_by_name(sdfg, task_name)
    in_name = list(task.free_symbols)[0]
    out_name = list(task.out_connectors.keys())[0]
    task.code.as_string = f"{out_name} = {in_name}"


def cfl_clipping_to_reduction(sdfg: dace.SDFG, task_name, cond_name, loop_name):
    """
    Turns the cfl_clipping scan/sum into a reduction.
    """
    task, parent = find_node_by_name(sdfg, task_name)
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)
    cond_block, parent = find_node_by_name(sdfg, cond_name)
    parent.remove_node(cond_block)
    loop, parent = find_node_by_name(sdfg, loop_name)
    del parent.in_edges(loop)[0].data.assignments["clip_count"]
    start = str(loop_analysis.get_init_assignment(loop))
    end = str(loop_analysis.get_loop_end(loop))

    outer_loop = parent
    outer_it_var = outer_loop.loop_variable

    _insert_reduction(
        parent,
        loop,
        "cfl_clipping",
        f"{end} - {start}",
        "clip_count",
        "sum",
        in_expr=f"cfl_clipping[{start}-1:{end}-1,{outer_it_var}-1]",
    )


def maxvcfl_to_reduction(sdfg: dace.SDFG, task_name, loop_name):
    """
    Turns the maxvcfl max into a reduction.
    """
    task, parent = find_node_by_name(sdfg, task_name, skip=1)
    assert task.code.as_string == "maxvcfl_out = max(maxvcfl_0_in, tmp_call_8_0_in)"
    task.code.as_string = "maxvcfl_out = tmp_call_8_0_in"
    task.remove_in_connector("maxvcfl_0_in")
    for pred in parent.predecessors(task):
        if pred.label == "maxvcfl":
            parent.remove_node(pred)
    parent.remove_node(parent.successors(task)[0])

    loop, loop_P = find_node_by_name(sdfg, loop_name)

    inner_loop = parent.parent_graph.parent_graph.parent_graph
    assert isinstance(inner_loop, LoopRegion)
    ol_it_name = loop.loop_variable
    il_it_name = inner_loop.loop_variable

    ol_start = str(loop_analysis.get_init_assignment(loop))
    ol_end = str(loop_analysis.get_loop_end(loop))
    il_start = str(loop_analysis.get_init_assignment(inner_loop))
    il_end = str(loop_analysis.get_loop_end(inner_loop))

    # The size of the required array is dynamic
    # and even if not, DaCe allocates arrays in the beginning
    # the size depends on runtime values, thus we get wrong sizes
    # so we overapproximate here
    arr_name, arr = parent.sdfg.add_array(
        "maxvcfl_arr",
        # shape=[100, 100], # We cannot overapproximate here afterall
        shape=[f"{il_end} - {il_start}", f"{ol_end} - {ol_start}"],
        dtype=dace.float64,
        transient=True,
        find_new_name=True,
    )
    arr_acc = parent.add_write(arr_name)

    parent.add_edge(
        task,
        "maxvcfl_out",
        arr_acc,
        None,
        dace.Memlet(f"{arr_name}[{il_it_name}-1,{ol_it_name}-1]"),
    )

    _insert_reduction(
        loop_P,
        loop,
        "maxvcfl_arr",
        f"({arr.shape[0]}) * ({arr.shape[1]})",
        "maxvcfl",
        "maxZ",
        out_expr="maxvcfl[0]",
    )


def tmp_call_13_to_reduction(sdfg: dace.SDFG, loop_name, task_name):
    """
    Turns the tmp_call_13 scan into a reduction.
    """
    loop, parent = find_node_by_name(sdfg, loop_name)
    start = str(loop_analysis.get_init_assignment(loop))
    end = str(loop_analysis.get_loop_end(loop))

    outer_loop = parent
    outer_it_var = outer_loop.loop_variable

    _insert_reduction(
        parent,
        loop,
        "levmask",
        f"{end} - {start}",
        "levelmask",
        "scan",
        in_expr=f"levmask[{start}-1:{end}-1,{outer_it_var}-1]",
        out_expr=f"levelmask[{outer_it_var}-1]",
    )
    pre_state = parent.add_state_before(loop)
    post_state = parent.add_state_after(loop)
    parent.remove_node(loop)
    parent.add_edge(pre_state, post_state, dace.InterstateEdge())
    task, parent = find_node_by_name(sdfg, task_name)
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)


def levmask_to_reduction(sdfg: dace.SDFG, loop_name, task_name):
    """
    Turns the levmask scan into a reduction.
    """
    loop, parent = find_node_by_name(sdfg, loop_name)
    prestate = parent.add_state_before(loop)
    start = str(loop_analysis.get_init_assignment(loop))
    end = str(loop_analysis.get_loop_end(loop))

    outer_loop = parent.parent_graph.parent_graph
    assert isinstance(outer_loop, LoopRegion)
    outer_it_var = outer_loop.loop_variable

    outer_outer_loop = outer_loop.parent_graph
    assert isinstance(outer_outer_loop, LoopRegion)
    outer_outer_it_var = outer_outer_loop.loop_variable

    _insert_reduction(
        parent,
        prestate,
        "cfl_clipping",
        f"{end} - {start}",
        "levmask",
        "scan",
        in_expr=f"cfl_clipping[{start}-1:{end}-1,{outer_it_var}-1]",
        out_expr=f"levmask[{outer_outer_it_var}-1,{outer_it_var}-1]",
    )
    task, parent = find_node_by_name(sdfg, task_name)
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)


def _demote_vcflmax(sdfg: dace.SDFG):
    """
    Demotes the vcflmax symbol to a scalar.
    vcflmax is only used in interstate edges, so we only check interstate edges and replace them.
    """
    vcfl_name, _ = sdfg.add_array(
        "vcflmax",
        shape=[
            1,
        ],
        dtype=sdfg.symbols["vcflmax"],
        transient=True,
        find_new_name=True,
    )
    replaced_write = False
    replaced_read = False
    for edge, parent in sdfg.all_edges_recursive():
        if not isinstance(edge.data, dace.sdfg.InterstateEdge):
            continue
        if "vcflmax" in edge.data.assignments.keys():
            assert (
                not replaced_write
            ), "TODO: vcflmax is assigned in multiple interstate edges"
            del edge.data.assignments["vcflmax"]

            vstate = parent.add_state_after(edge.src, "vcflmax_state")
            rnode = vstate.add_read("maxvcfl")
            wnode = vstate.add_write(vcfl_name)
            vstate.add_edge(
                rnode,
                None,
                wnode,
                None,
                dace.Memlet.from_array("maxvcfl", sdfg.arrays["maxvcfl"]),
            )
            replaced_write = True
        if "vcflmax" in edge.data.assignments.values():
            assert (
                not replaced_read
            ), "TODO: vcflmax is read in multiple interstate edges"
            edge.data.replace("vcflmax", vcfl_name)
            replaced_read = True

    sdfg.remove_symbol("vcflmax")


def add_all_reductions(sdfg: dace.SDFG):
    # Make sure vcflmax is not a symbol
    if "vcflmax" in sdfg.symbols:
        import warnings

        warnings.warn("vcflmax is a symbol, demoting to a scalar")
        _demote_vcflmax(sdfg)

    # We assume the array names and iteration variable names never change
    if "nproma32" in sdfg.name:
        loop_to_max_reduction(sdfg, f"FOR_l_568_c_568", "T_l568_c568")
        cfl_clipping_to_reduction(
            sdfg, "T_l467_c467", "Conditional_l_467_c_467", f"FOR_l_465_c_465"
        )
        maxvcfl_to_reduction(sdfg, "T_l474_c474", f"FOR_l_463_c_463")
        tmp_call_13_to_reduction(sdfg, f"FOR_l_516_c_516", "T_l516_c516")
        levmask_to_reduction(sdfg, f"FOR_l_470_c_470", "T_l472_c472")

    elif "nproma20480" in sdfg.name:
        loop_to_max_reduction(sdfg, f"FOR_l_652_c_652", "T_l652_c652")
        cfl_clipping_to_reduction(
            sdfg, "T_l551_c551", "Conditional_l_551_c_551", "FOR_l_549_c_549"
        )
        maxvcfl_to_reduction(sdfg, "T_l558_c558", f"FOR_l_547_c_547")
        tmp_call_13_to_reduction(sdfg, f"FOR_l_600_c_600", "T_l600_c600")
        levmask_to_reduction(sdfg, f"FOR_l_554_c_554", "T_l556_c556")

    else:
        raise ValueError("Unknown NPROMA size")

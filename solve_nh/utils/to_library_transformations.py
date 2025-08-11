import dace
from typing import Set, List, Dict, Tuple
import re
import copy
import dace
from pathlib import Path

COPYIN_NAME = "copy_in_nontransient"
COPYOUT_NAME = "copy_out_nontransient"

def collect_to_gpu_nontransient_set(sdfg: dace.SDFG):
    copy_in_states = {s for s in  sdfg.all_states() if s.label == COPYIN_NAME}
    assert len(copy_in_states) == 1, "Expected exactly one copy-in state in the SDFG"
    copy_in_state = copy_in_states.pop()
    copy_out_states = {s for s in sdfg.all_states() if s.label == COPYOUT_NAME}
    assert len(copy_out_states) == 1, "Expected exactly one copy-out state in the SDFG"
    copy_out_state = copy_out_states.pop()

    gpu_nontransients = set()
    for e in copy_in_state.edges():
        src = e.src
        dst = e.dst
        if isinstance(dst, dace.nodes.Tasklet):
            continue
        assert isinstance(src, dace.nodes.AccessNode) and isinstance(dst, dace.nodes.AccessNode), \
            "Copy-in and copy-out nodes must be AccessNodes"
        assert "gpu_"+src.data == dst.data, \
            "Copy-in node data must be prefixed with 'gpu_' to indicate GPU non-transient data"
        gpu_nontransients.add(src.data)
    for e in copy_out_state.edges():
        src = e.src
        dst = e.dst
        assert isinstance(src, dace.nodes.AccessNode) and isinstance(dst, dace.nodes.AccessNode), \
            "Copy-in and copy-out nodes must be AccessNodes"
        assert "gpu_"+dst.data == src.data, \
            "Copy-out node data must be prefixed with 'gpu_' to indicate GPU non-transient data"
        assert dst.data in gpu_nontransients, \
            "Copy-out node data must be subset of copy-in node data"

    return gpu_nontransients


def nontransient_inputs_to_gpu(sdfg: dace.SDFG):
    non_transients = collect_to_gpu_nontransient_set(sdfg)
    for input_name in non_transients:
        input_to_gpu(sdfg, input_name)
    rm_redundant_copies(sdfg)


def input_to_gpu(sdfg: dace.SDFG, input_name: str):
    """
    Transforms an input to be present on the GPU.
    """

    copy_in_states = {s for s in  sdfg.all_states() if s.label == COPYIN_NAME}
    assert len(copy_in_states) == 1, "Expected exactly one copy-in state in the SDFG"
    copy_in_state = copy_in_states.pop()
    copy_out_states = {s for s in sdfg.all_states() if s.label == COPYOUT_NAME}
    assert len(copy_out_states) == 1, "Expected exactly one copy-out state in the SDFG"
    copy_out_state = copy_out_states.pop()

    first_state = copy_in_state
    last_state = copy_out_state

    # Ensure the symbols are not eliminated
    first_state.add_tasklet(
        "sym_hack",
        {},
        {},
        f"i_am_not_used = {sdfg.arrays[input_name].total_size}",
        side_effects=True,
    )

    # Rename access nodes
    for node, p in sdfg.all_nodes_recursive():
        if not isinstance(node, dace.nodes.AccessNode):
            continue
        if node.data != f"gpu_{input_name}":
            continue

        # Remove copyin/copyout in first/last state
        if p is first_state or p is last_state:
            preds_succs = list(p.predecessors(node)) + list(p.successors(node))
            for pred_succ in preds_succs:
                p.remove_node(pred_succ)
            p.remove_node(node)
        else:
            # Strip the prefix of all access nodes that follow this name: gpu_<input_name>
            # Preserves function signature
            node.data = input_name

    # Rename connectors
    for node, p in sdfg.all_nodes_recursive():
        if not hasattr(node, "in_connectors") or not hasattr(node, "out_connectors"):
            continue

        pattern = r"\b" + re.escape(f"gpu_{input_name}") + r"\b"
        for k in list(node.in_connectors.keys()):
            if k != "gpu_" + input_name:
                continue
            # Rename the connector
            node.in_connectors[input_name] = node.in_connectors[k]
            del node.in_connectors[k]
        for k in list(node.out_connectors.keys()):
            if k != "gpu_" + input_name:
                continue
            # Rename the connector
            node.out_connectors[input_name] = node.out_connectors[k]
            del node.out_connectors[k]

    # Rename edges
    for edge, p in sdfg.all_edges_recursive():
        pattern = r"\b" + re.escape(f"gpu_{input_name}") + r"\b"
        if hasattr(edge.data, "data") and edge.data.data is not None:
            edge.data.data = re.sub(pattern, input_name, edge.data.data)

        if hasattr(edge, "dst_conn") and edge.dst_conn is not None:
            edge.dst_conn = re.sub(pattern, input_name, edge.dst_conn)

        if hasattr(edge, "src_conn") and edge.src_conn is not None:
            edge.src_conn = re.sub(pattern, input_name, edge.src_conn)

    # Adjust array descriptors
    sdfg_appeared = False
    for nsdfg in sdfg.all_sdfgs_recursive():
        if nsdfg is sdfg:
            sdfg_appeared = True
        if f"gpu_{input_name}" not in nsdfg.arrays:
            continue
        if input_name in nsdfg.arrays:
            nsdfg.arrays[f"{input_name}"].storage = nsdfg.arrays[
                f"gpu_{input_name}"
            ].storage
        else:
            nsdfg.arrays[f"{input_name}"] = nsdfg.arrays[f"gpu_{input_name}"]
        del nsdfg.arrays[f"gpu_{input_name}"]

    assert sdfg_appeared, "SDFG not found in the list of all SDFGs"

def rm_redundant_copies(sdfg: dace.SDFG):
    for state in sdfg.all_states():
        for edge in state.edges():
            if edge not in state.edges():
                continue
            if (isinstance(edge.src, dace.nodes.AccessNode) and
                isinstance(edge.dst, dace.nodes.AccessNode) and
                edge.src.data == edge.dst.data
                ):
                state.remove_edge(edge)
                state.remove_node(edge.src)
                state.remove_node(edge.dst)


    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                rm_redundant_copies(node.sdfg)


# This is the set of data that is needed both on the GPU and CPU, in this case we will accept them on the CPU
# and copy them to the GPU.
cpu_gpu_copies_to_keep = {
    "gpu___CG_global_data__m_ndyn_substeps_var",
    "gpu___CG_global_data__m_kstart_dd3d",  # ADDED BY PRATYAI, AS PER BEN'S SUGGESTION.
}

def _find_flatten_node_and_state(sdfg: dace.SDFG):
    states = sdfg.all_states()
    flatten_node = None
    flatten_state : dace.SDFGState = None
    deflatten_node = None
    deflatten_state : dace.SDFGState = None
    for state in states:
        for node in state.nodes():
            if isinstance(node, dace.nodes.LibraryNode):
                if "flatten" == node.label and "deflatten" not in node.label:
                    flatten_node = node
                    flatten_state = state
                if "deflatten" == node.label:
                    deflatten_node = node
                    deflatten_state = state

    assert flatten_node is not None
    assert deflatten_node is not None

    return flatten_node, flatten_state, deflatten_node, deflatten_state

def _load_flatten_code(sdfg: dace.SDFG):
    root_path = Path(__file__).parent
    flatten_codefile_name = sdfg.label + "_flattener_code.cpp"
    tasklet_src_file = root_path / ".." / flatten_codefile_name

    with open(tasklet_src_file, 'r') as f:
        file_content = f.read()

    return file_content

def _write_filtered_content(sdfg: dace.SDFG, filtered_shallow_copy_str: str):
    root_path = Path(__file__).parent
    tasklet_dst_file = root_path / ".." / ("filtered_"  + sdfg.label + "_flattener_code.cpp")
    with open(tasklet_dst_file, 'w') as f2:
        f2.write(filtered_shallow_copy_str)


def _generate_shallow_copy_tasklet_outputs(sdfg: dace.SDFG, flatten_state: dace.SDFGState,
                                           flatten_destinations: Set[dace.nodes.AccessNode],
                                           shallow_copy_base_source_code: str) -> Tuple[Set[str], Dict[str, dace.nodes.AccessNode], List[str]]:
    # Need to update the file content, we always have dst_ptr = src_ptr; or some comments that do not have = in the line
    assignments = {(line.split('=')[0].strip(), line.split('=')[1].strip()) for line in shallow_copy_base_source_code.strip().splitlines() if '=' in line}
    lhs_set = {k1 for k1, _ in assignments}
    available_lhs_set = {lhs for lhs in lhs_set if lhs in sdfg.arrays}

    # Build up to outputs, since inputs are structs, pust them without connectors
    # For outputs add required accesses etc.
    outputs = set()
    outputs_to_an = dict()
    for dst in flatten_destinations:
        if flatten_state.out_degree(dst) == 0 and flatten_state.in_degree(dst) == 0:
            # It was a scalar / cpu data
            #flatten_state.add_edge(shallow_copy_tasklet, None, dace.Memlet())
            assert "out_"+ dst.data not in outputs, \
                f"Output {dst.data} already in outputs, this should not happen"
            outputs.add("out_"+ dst.data)
            outputs_to_an["out_"+ dst.data] = flatten_state.add_access(dst.data)
        elif flatten_state.out_degree(dst) == 1:
            # Connect to the GPU if not "__CG_global_data__m_ndyn_substeps_var"
            oe_oe = flatten_state.out_edges(dst)[0]
            if isinstance(oe_oe.dst, dace.nodes.AccessNode):
                if oe_oe.dst.data in cpu_gpu_copies_to_keep:
                    assert oe_oe.dst.data.startswith("gpu_") and dst.data == oe_oe.dst.data[4:]
                    #flatten_state.add_edge(oe_oe.dst, None, shallow_copy_tasklet, None, dace.Memlet())
                    assert "out_"+ dst.data not in outputs, \
                        f"Output {dst.data} already in outputs, this should not happen"
                    outputs.add("out_"+ dst.data)
                    cpu_an = flatten_state.add_access(dst.data)
                    outputs_to_an["out_"+ dst.data] = cpu_an
                    # Reinsert cpu->gpu copy
                    gpu_an = flatten_state.add_access("gpu_" + dst.data)
                    flatten_state.add_edge(cpu_an, None, gpu_an, None,
                                             dace.Memlet.from_array(dst.data, sdfg.arrays[dst.data]))
                else:
                    assert oe_oe.dst.data.startswith("gpu_") and dst.data == oe_oe.dst.data[4:]
                    #flatten_state.add_edge(oe_oe.dst, None, shallow_copy_tasklet, None, dace.Memlet())
                    assert "out_"+ oe_oe.dst.data not in outputs, \
                        f"Output {oe_oe.dst.data} already in outputs, this should not happen"
                    outputs.add("out_"+ oe_oe.dst.data)
                    outputs_to_an["out_"+ oe_oe.dst.data] = flatten_state.add_access(oe_oe.dst.data)
                    flatten_state.remove_node(dst)
        else:
            raise Exception(
                f"Flatten destination {dst} has more than one out-degree, cannot handle this case"
            )

    # Update the missing ones from the src code, and filter the code to not include data not used by the SDFG
    filtered_content = []
    filtered_content += ["double * _internal_t_tangent_vectors = nullptr;"]
    for k, v in assignments:
        if k == "" or k.strip() == "":
            continue
        if k.startswith("//"):
            continue
        if v.strip().startswith("&"):
            if v.strip().endswith("]"):
                v = v.strip()
                v = v[1:-1]  # Remove & and [0];
                v = "&(" + v + "]);"
            elif v.strip().endswith("];"):
                v = v.strip()
                v = v[1:-2]  # Remove & and [0];
                v = "&(" + v + "]);"
            else:
                raise Exception(
                    f"Cannot handle {v} in the flattening code, expected &<data> or &<data>[0]; or &<data>[0];"
                )
        v = v.replace("->t_tangent_vectors[", "[")
        if k in available_lhs_set and k in sdfg.arrays:
            filtered_content.append(f"out_{k} = {v}")
            if ("out_" + k) not in outputs:
                assert "out_" + k not in outputs, \
                    f"Output {k} already in outputs, this should not happen"
                outputs.add("out_" + k)
                outputs_to_an["out_" + k] = flatten_state.add_access(k)
        else:
            filtered_content.append(f"// out_{k} = {v} // Comment out because lhs is not in the SDFG arrays")

    return outputs, outputs_to_an, filtered_content

def change_flatten_lib_to_shallow_copy(sdfg: dace.SDFG) -> None:
    flatten_node, flatten_state, deflatten_node, deflatten_state = _find_flatten_node_and_state(sdfg)

    flatten_sources = {ie.src for ie in flatten_state.in_edges(flatten_node) if isinstance(sdfg.arrays[ie.src.data], dace.data.Structure)}
    flatten_destinations = {oe.dst for oe in flatten_state.out_edges(flatten_node) if isinstance(oe.dst, dace.nodes.AccessNode)}

    # Snapshot of old nodes
    flatten_state.remove_node(flatten_node)
    old_flatten_nodes = flatten_state.nodes()

    shallow_copy_base_source_code = _load_flatten_code(sdfg)

    outputs_set, outputs_to_access_node_dict, filtered_shallow_copies = _generate_shallow_copy_tasklet_outputs(sdfg, flatten_state, flatten_destinations, shallow_copy_base_source_code)

    # Remove old flatten nodes
    for n in old_flatten_nodes:
        flatten_state.remove_node(n)

    filtered_shallow_copy_str = "\n".join(filtered_shallow_copies)
    _write_filtered_content(sdfg, filtered_shallow_copy_str)

    # To prevent the stupid codegen from failing, copy the destinations nodes to src too if they are scalars
    scalar_outputs = {k for k in outputs_set if isinstance(sdfg.arrays[k[len("out_"):]], dace.data.Scalar)}
    inputs_set = {"in_" + k[len("out_"):] for k in scalar_outputs}

    shallow_copy_tasklet = flatten_state.add_tasklet(name="shallow_flatten",
        inputs=inputs_set,
        outputs=outputs_set,
        code=filtered_shallow_copy_str,
        language=dace.Language.CPP,
        side_effects=True
    )

    # Connect the tasklet to the source and destinations
    for src in flatten_sources:
        flatten_state.add_edge(src, None, shallow_copy_tasklet, None, dace.Memlet())

    for output, dst in outputs_to_access_node_dict.items():
        flatten_state.add_edge(shallow_copy_tasklet, output, dst, None,
                               dace.Memlet.from_array(output[len("out_"):], sdfg.arrays[output[len("out_"):]]))
        shallow_copy_tasklet.add_out_connector(output)

    for input in inputs_set:
        # Add tasklet to not get unset transient warning (annoying)
        # t = flatten_state.add_tasklet(
        #     name="setzero_" + input[len("in_"):],
        #     inputs=set(),
        #     outputs={"_out"},
        #     code=f"_out = _out;"
        # )
        sdfg.arrays[input[len("in_"):]].lifetime = dace.dtypes.AllocationLifetime.SDFG
        src_access = flatten_state.add_access(input[len("in_"):])
        # flatten_state.add_edge(t, "_out", src_access, None, dace.Memlet.from_array(input[len("in_"):], sdfg.arrays[input[len("in_"):]]))
        flatten_state.add_edge(src_access, None, shallow_copy_tasklet, input, dace.Memlet.from_array(input[len("in_"):], sdfg.arrays[input[len("in_"):]]))


    # Remove all nodes connecting to the deflatten node
    deflatten_state.remove_node(deflatten_node)
    # Copy full size copies of gpu to cpu
    for e in deflatten_state.edges():
        if (isinstance(e.src, dace.nodes.AccessNode) and e.src.data.startswith("gpu_")
            and isinstance(e.dst, dace.nodes.AccessNode) and e.dst.data == e.src.data[4:]):
            deflatten_state.remove_edge(e)

    rmed = 1
    while rmed > 0:
        rmed = 0
        nds_to_rm = []
        for node in deflatten_state.nodes():
            if deflatten_state.degree(node) == 0:
                nds_to_rm.append(node)
        for node in nds_to_rm:
            deflatten_state.remove_node(node)
            rmed += 1


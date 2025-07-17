import dace
import copy

from dace.codegen.common import CodeBlock


def post_stage1_fixes(g: dace.SDFG):
    state_name = "_state_l169_c169"
    tasklet_name = "T_l940_c940"

    for n, graph in g.all_nodes_recursive():
        if (isinstance(n, dace.nodes.Tasklet) and
            isinstance(graph, dace.SDFGState)):
            if n.label == tasklet_name and graph.label == state_name:
                # Remove the tasklet to state before
                parent_graph = graph.parent_graph
                state_before = parent_graph.add_state_before(graph, "prefix", is_start_block=parent_graph.in_degree(graph) == 0)
                an0 = state_before.add_access("nproma_gradp")
                an1 = state_before.add_access("__CG_p_nh__CG_metrics__m_pg_listdim")
                tasklet_copy = copy.deepcopy(n)
                assert graph.out_degree(n) == 1
                out_edge = graph.out_edges(n)[0]
                out_an = out_edge.dst

                tasklet_code = CodeBlock(
                    tasklet_copy.code.as_string.replace("nproma_gradp", "_in_nproma_gradp").replace(
                    "__CG_p_nh__CG_metrics__m_pg_listdim", "_in___CG_p_nh__CG_metrics__m_pg_listdim"
                ))
                tasklet_copy.code = tasklet_code

                # Rm tasklet -> out_an
                graph.remove_node(n)
                graph.remove_node(out_an)

                # Add the an0 -> tasklet, an1 -> tasklet, tasklet -> out_an_edges and nodes
                state_before.add_node(tasklet_copy)
                state_before.add_edge(an0, None, tasklet_copy, "_in_nproma_gradp",
                                      dace.memlet.Memlet.from_array("nproma_gradp",
                                                                    graph.sdfg.arrays["nproma_gradp"]))
                state_before.add_edge(an1, None, tasklet_copy, "_in___CG_p_nh__CG_metrics__m_pg_listdim",
                                      dace.memlet.Memlet.from_array(
                                          "__CG_p_nh__CG_metrics__m_pg_listdim",
                                          graph.sdfg.arrays["__CG_p_nh__CG_metrics__m_pg_listdim"]))
                state_before.add_edge(tasklet_copy, out_edge.src_conn, out_an, None,
                                      copy.deepcopy(out_edge.data))
                tasklet_copy.add_in_connector("_in_nproma_gradp")
                tasklet_copy.add_in_connector("_in___CG_p_nh__CG_metrics__m_pg_listdim")

                print(f"Removed tasklet {tasklet_name} from state {state_name}")

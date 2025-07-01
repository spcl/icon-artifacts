from dace import SDFG
from dace import nodes
from dace.sdfg.sdfg import InterstateEdge

def hacky_cfl_clipping_related_kernel_removal(sdfg: SDFG):
      # REMOVE THE `cfl_clipping` DEPENDENT BRANCHES (PART 1)
    for ed, est in sdfg.all_edges_recursive():
        if not isinstance(ed.data, InterstateEdge):
            continue
        ied = ed.data
        if any(c in ied.assignments for c in {
            '_if_cond_18',
            '_if_cond_25',
            '_if_cond_28',
        }):
            est.remove_node(ed.src)
            est.remove_node(ed.dst)
    # REMOVE EMPTY KERNELS
    for en, enst in sdfg.all_nodes_recursive():
        if not isinstance(en, nodes.MapEntry):
            continue
        if en not in enst.nodes():
            continue
        ensg = enst.scope_subgraph(en)
        empty_kernel = True
        for n, nst in ensg.all_nodes_recursive():
            if isinstance(n, (nodes.Tasklet, nodes.LibraryNode)):
                empty_kernel = False
        if empty_kernel:
            print(f"DROPPING {en}")
            enst.remove_nodes_from(ensg)
    # REMOVE `levelmask` AND ITS COMPUTER KERNEL.
    for n, nst in sdfg.all_nodes_recursive():
        if not isinstance(n, nodes.AccessNode) or str(n.data) != 'gpu_levelmask':
            continue
        for ed in nst.in_edges(n):
            assert isinstance(ed.src, nodes.MapExit)
            nst.remove_nodes_from(nst.scope_subgraph(nst.entry_node(ed.src)))
        for ed in nst.out_edges(n):
            assert isinstance(ed.dst, nodes.MapEntry)
            nst.remove_memlet_path(ed)
        nst.remove_node(n)
    # REMOVE THE CONTAINER KERNEL OF `reduce_scan_size_0`
    for n, nst in sdfg.all_nodes_recursive():    
        if not isinstance(n, nodes.AccessNode) or str(n.data) != 'reduce_scan_size_0':
            continue
        block_1, reduction_togo = nst.parent.parent, nst.parent.parent_nsdfg_node
        en = block_1.entry_node(reduction_togo)
        block_1.remove_nodes_from(block_1.scope_subgraph(en))
    # REMOVE `levmask` AND ITS COMPUTER KERNEL.
    for n, nst in sdfg.all_nodes_recursive():
        if not isinstance(n, nodes.AccessNode) or str(n.data) != 'gpu_levmask':
            continue
        for ed in nst.in_edges(n) + nst.out_edges(n):
            nst.remove_memlet_path(ed)
        nst.remove_node(n)
    # REMOVE THE KERNEL `segmented_reduce_sum_to_address`
    for n, nst in sdfg.all_nodes_recursive():    
        if not isinstance(n, nodes.LibraryNode) or str(n.name) != 'segmented_reduce_sum_to_address':
            continue
        nst.remove_node(n)
    # REMOVE `cfl_clipping` AND ITS COMPUTER KERNEL.
    for n, nst in sdfg.all_nodes_recursive():
        if not isinstance(n, nodes.AccessNode) or str(n.data) != 'gpu_cfl_clipping':
            continue
        for ed in nst.in_edges(n) + nst.out_edges(n):
            nst.remove_memlet_path(ed)
        nst.remove_node(n)
    # CLEANUP DATA ARRAYS
    for a in {'gpu_levelmask', 'gpu_levmask', 'gpu_cfl_clipping'}:
        sdfg.remove_data(a)
        for g, _ in sdfg.all_nodes_recursive():
            if not isinstance(g, nodes.NestedSDFG):
                continue
            g.sdfg.remove_data(a)
    # REMOVE ORPHANS ACCESS NODES
    for n, nst in sdfg.all_nodes_recursive():
        if not isinstance(n, nodes.AccessNode):
            continue
        if not(nst.in_edges(n)) and not(nst.out_edges(n)):
            nst.remove_node(n)

    return sdfg
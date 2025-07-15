import dace

def state_fusion_without_copyin_and_copyout(sdfg: dace.SDFG):
    from dace.transformation.interstate import StateFusion, BlockFusion  # Avoid import loop
    copy_in = sdfg.start_block
    copy_out = [n for n in sdfg.nodes() if sdfg.out_degree(n) == 0][0]
    assert any([n for n in copy_in.nodes() if n.label == "flatten" and isinstance(n, dace.sdfg.nodes.LibraryNode)])
    assert any([n for n in copy_out.nodes() if n.label == "deflatten" and isinstance(n, dace.sdfg.nodes.LibraryNode)])

    for sd in sdfg.all_sdfgs_recursive():
        for cfg in sd.all_control_flow_regions():
            while True:
                edges = list(cfg.nx.edges)
                applied = 0
                skip_nodes = set()
                for u, v in edges:
                    if u in skip_nodes or v in skip_nodes:
                        continue
                    if u == copy_in or v == copy_in or u == copy_out or v == copy_out:
                        continue

                    if isinstance(u, dace.SDFGState) and isinstance(v, dace.SDFGState):
                        candidate = {StateFusion.first_state: u, StateFusion.second_state: v}
                        sf = StateFusion()
                        sf.setup_match(cfg, cfg.cfg_id, -1, candidate, 0, override=True)
                        if sf.can_be_applied(cfg, 0, sd):
                            sf.apply(cfg, sd)
                            applied += 1
                            counter += 1
                            skip_nodes.add(u)
                            skip_nodes.add(v)
                    else:
                        candidate = {BlockFusion.first_block: u, BlockFusion.second_block: v}
                        bf = BlockFusion()
                        bf.setup_match(cfg, cfg.cfg_id, -1, candidate, 0, override=True)
                        if bf.can_be_applied(cfg, 0, sd):
                            bf.apply(cfg, sd)
                            applied += 1
                            counter += 1
                            skip_nodes.add(u)
                            skip_nodes.add(v)
                if applied == 0:
                    break

# Layout Permutation Suggestions

```
    ! Variant 1
    DO jk = 1, nlev
    DO jc = i_startidx, i_endidx
    z_ekinh(jc,jk,jb) =  &
        p_int%e_bln_c_s(jc,1,jb)*z_kin_hor_e(ieidx(jc,jb,1),jk,ieblk(jc,jb,1)) + &
        p_int%e_bln_c_s(jc,2,jb)*z_kin_hor_e(ieidx(jc,jb,2),jk,ieblk(jc,jb,2)) + &
        p_int%e_bln_c_s(jc,3,jb)*z_kin_hor_e(ieidx(jc,jb,3),jk,ieblk(jc,jb,3))

    ENDDO
    ENDDO
```

```
    ! Variant 2
    DO jc = i_startidx, i_endidx
    DO jk = 1, nlev
    z_ekinh(jk,jc,jb) =  &
        p_int%e_bln_c_s(1,jc,jb)*z_kin_hor_e(jk,ieidx(1,jc,jb),ieblk(1,jc,jb)) + &
        p_int%e_bln_c_s(2,jc,jb)*z_kin_hor_e(jk,ieidx(2,jc,jb),ieblk(2,jc,jb)) + &
        p_int%e_bln_c_s(3,jc,jb)*z_kin_hor_e(jk,ieidx(3,jc,jb),ieblk(3,jc,jb))

    ENDDO
    ENDDO
```

# Layout Optimization: Array Inventory for `mo_velocity_advection`

Two transformations applied globally for ~4x speedup on GPUs and CPUs:

- **(A) Structured-dim-first:** Move the vertical/level dimension to the leading position.
- **(B) Neighbor-index-first:** Move the neighbor/stencil index to the leading position.

## Work Arrays (local to subroutine)

| Array | Current Layout | Optimized Layout | Transform |
|---|---|---|---|
| `z_ekinh` | `(nproma, nlev, nblks_c)` | `(nlev, nproma, nblks_c)` | A |
| `z_kin_hor_e` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `z_v_grad_w` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `z_w_v` | `(nproma, nlevp1, nblks_v)` | `(nlevp1, nproma, nblks_v)` | A |
| `zeta` | `(nproma, nlev, nblks_v)` | `(nlev, nproma, nblks_v)` | A |
| `z_vt_ie` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `z_w_concorr_me` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `z_w_con_c_full` | `(nproma, nlev, nblks_c)` | `(nlev, nproma, nblks_c)` | A |
| `z_w_concorr_mc` | `(nproma, nlev)` | `(nlev, nproma)` | — |
| `z_w_con_c` | `(nproma, nlevp1)` | `(nlev, nproma)` | — |

## Prognostic Fields (`p_prog`)

| Array | Current Layout | Optimized Layout | Transform |
|---|---|---|---|
| `p_prog%vn` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `p_prog%w` | `(nproma, nlevp1, nblks_c)` | `(nlevp1, nproma, nblks_c)` | A |

## Diagnostic Fields (`p_diag`)

| Array | Current Layout | Optimized Layout | Transform |
|---|---|---|---|
| `p_diag%vt` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `p_diag%vn_ie` | `(nproma, nlevp1, nblks_e)` | `(nlevp1, nproma, nblks_e)` | A |
| `p_diag%w_concorr_c` | `(nproma, nlev, nblks_c)` | `(nlev, nproma, nblks_c)` | A |
| `p_diag%ddt_vn_apc_pc` | `(nproma, nlev, nblks_e, ntnd)` | `(nlev, nproma, nblks_e, ntnd)` | A |
| `p_diag%ddt_w_adv_pc` | `(nproma, nlev, nblks_c, ntnd)` | `(nlev, nproma, nblks_c, ntnd)` | A |
| `p_diag%ddt_vn_cor_pc` | `(nproma, nlev, nblks_e, ntnd)` | `(nlev, nproma, nblks_e, ntnd)` | A |
| `p_diag%vn_ie_ubc` | `(nproma, 2, nblks_e)` | `(2, nproma, nblks_e)` | A |
| `p_diag%max_vcfl_dyn` | scalar | *unchanged* | — |

## Metric Fields (`p_metrics`)

| Array | Current Layout | Optimized Layout | Transform |
|---|---|---|---|
| `p_metrics%wgtfac_e` | `(nproma, nlevp1, nblks_e)` | `(nlevp1, nproma, nblks_e)` | A |
| `p_metrics%wgtfac_c` | `(nproma, nlevp1, nblks_c)` | `(nlevp1, nproma, nblks_c)` | A |
| `p_metrics%wgtfacq_e` | `(nproma, 3, nblks_e)` | `(3, nproma, nblks_e)` | B |
| `p_metrics%ddxn_z_full` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `p_metrics%ddxt_z_full` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `p_metrics%coeff_gradekin` | `(nproma, 2, nblks_e)` | `(2, nproma, nblks_e)` | B |
| `p_metrics%ddqz_z_half` | `(nproma, nlevp1, nblks_c)` | `(nlevp1, nproma, nblks_c)` | A |
| `p_metrics%ddqz_z_full_e` | `(nproma, nlev, nblks_e)` | `(nlev, nproma, nblks_e)` | A |
| `p_metrics%coeff1_dwdz` | `(nproma, nlev, nblks_c)` | `(nlev, nproma, nblks_c)` | A |
| `p_metrics%coeff2_dwdz` | `(nproma, nlev, nblks_c)` | `(nlev, nproma, nblks_c)` | A |
| `p_metrics%deepatmo_gradh_ifc` | `(nlevp1)` | *unchanged* | — |
| `p_metrics%deepatmo_invr_ifc` | `(nlevp1)` | *unchanged* | — |
| `p_metrics%deepatmo_gradh_mc` | `(nlev)` | *unchanged* | — |
| `p_metrics%deepatmo_invr_mc` | `(nlev)` | *unchanged* | — |

## Interpolation Coefficients (`p_int`)

| Array | Current Layout | Optimized Layout | Transform |
|---|---|---|---|
| `p_int%rbf_vec_coeff_e` | `(4, nproma, nblks_e)` | *unchanged* | — |
| `p_int%e_bln_c_s` | `(nproma, 3, nblks_c)` | `(3, nproma, nblks_c)` | B |
| `p_int%c_lin_e` | `(nproma, 2, nblks_e)` | `(2, nproma, nblks_e)` | B |
| `p_int%geofac_n2s` | `(nproma, 4, nblks_c)` | `(4, nproma, nblks_c)` | B |
| `p_int%geofac_grdiv` | `(nproma, 5, nblks_e)` | `(5, nproma, nblks_e)` | B |
| `p_int%cells_aw_verts` | *passed to library call* | *depends on `cells2verts_scalar_ri`* | — |

## Connectivity Tables (pointers into `p_patch`)

| Array | Source | Current Layout | Optimized Layout | Transform |
|---|---|---|---|---|
| `icidx` | `edges%cell_idx` | `(nproma, nblks_e, 2)` | `(2, nproma, nblks_e)` | B |
| `icblk` | `edges%cell_blk` | `(nproma, nblks_e, 2)` | `(2, nproma, nblks_e)` | B |
| `ieidx` | `cells%edge_idx` | `(nproma, nblks_c, 3)` | `(3, nproma, nblks_c)` | B |
| `ieblk` | `cells%edge_blk` | `(nproma, nblks_c, 3)` | `(3, nproma, nblks_c)` | B |
| `ividx` | `edges%vertex_idx` | `(nproma, nblks_e, 2)` | `(2, nproma, nblks_e)` | B |
| `ivblk` | `edges%vertex_blk` | `(nproma, nblks_e, 2)` | `(2, nproma, nblks_e)` | B |
| `iqidx` | `edges%quad_idx` | `(nproma, nblks_e, 4)` | `(4, nproma, nblks_e)` | B |
| `iqblk` | `edges%quad_blk` | `(nproma, nblks_e, 4)` | `(4, nproma, nblks_e)` | B |
| `incidx` | `cells%neighbor_idx` | `(nproma, nblks_c, 3)` | `(3, nproma, nblks_c)` | B |
| `incblk` | `cells%neighbor_blk` | `(nproma, nblks_c, 3)` | `(3, nproma, nblks_c)` | B |

## Geometry Fields (unchanged — already 2D)

| Array | Layout |
|---|---|
| `p_patch%edges%inv_dual_edge_length` | `(nproma, nblks_e)` |
| `p_patch%edges%inv_primal_edge_length` | `(nproma, nblks_e)` |
| `p_patch%edges%tangent_orientation` | `(nproma, nblks_e)` |
| `p_patch%edges%f_e` | `(nproma, nblks_e)` |
| `p_patch%edges%ft_e` | `(nproma, nblks_e)` |
| `p_patch%edges%fn_e` | `(nproma, nblks_e)` |
| `p_patch%edges%area_edge` | `(nproma, nblks_e)` |
| `p_patch%cells%area` | `(nproma, nblks_c)` |
| `p_patch%cells%decomp_info%owner_mask` | `(nproma, nblks_c)` |

## Summary

Total | Relayouted | Unchanged |
|---|---|---|
**59** | **41** | **18** |


```python
permute_map = {
    # Work arrays — transform A: (nproma, nlev, nblks) → (nlev, nproma, nblks)
    "z_ekinh":                        [1, 0, 2],
    "z_kin_hor_e":                    [1, 0, 2],
    "z_v_grad_w":                     [1, 0, 2],
    "z_w_v":                          [1, 0, 2],
    "zeta":                           [1, 0, 2],
    "z_vt_ie":                        [1, 0, 2],
    "z_w_concorr_me":                 [1, 0, 2],
    "z_w_concorr_mc":                 [1, 0],
    "z_w_con_c_full":                 [1, 0, 2],
    "z_w_con_c":                      [1, 0],

    # Prognostic fields — transform A
    "p_prog%vn":                      [1, 0, 2],
    "p_prog%w":                       [1, 0, 2],

    # Diagnostic fields — transform A (3D and 4D)
    "p_diag%vt":                      [1, 0, 2],
    "p_diag%vn_ie":                   [1, 0, 2],
    "p_diag%w_concorr_c":             [1, 0, 2],
    "p_diag%ddt_vn_apc_pc":           [1, 0, 2, 3],
    "p_diag%ddt_w_adv_pc":            [1, 0, 2, 3],
    "p_diag%ddt_vn_cor_pc":           [1, 0, 2, 3],
    "p_diag%vn_ie_ubc":              [1, 0, 2],

    # Metric fields — transform A
    "p_metrics%wgtfac_e":             [1, 0, 2],
    "p_metrics%wgtfac_c":             [1, 0, 2],
    "p_metrics%ddxn_z_full":          [1, 0, 2],
    "p_metrics%ddxt_z_full":          [1, 0, 2],
    "p_metrics%ddqz_z_half":          [1, 0, 2],
    "p_metrics%ddqz_z_full_e":        [1, 0, 2],
    "p_metrics%coeff1_dwdz":          [1, 0, 2],
    "p_metrics%coeff2_dwdz":          [1, 0, 2],
    # Metric fields — transform B: (nproma, N, nblks) → (N, nproma, nblks)
    "p_metrics%wgtfacq_e":            [1, 0, 2],
    "p_metrics%coeff_gradekin":        [1, 0, 2],

    # Interpolation coefficients — transform B: (nproma, N, nblks) → (N, nproma, nblks)
    "p_int%e_bln_c_s":               [1, 0, 2],
    "p_int%c_lin_e":                  [1, 0, 2],
    "p_int%geofac_n2s":               [1, 0, 2],
    "p_int%geofac_grdiv":             [1, 0, 2],

    # Connectivity tables — transform B: (nproma, nblks, N) → (N, nproma, nblks)
    "p_patch%edges%cell_idx":         [2, 0, 1],
    "p_patch%edges%cell_blk":         [2, 0, 1],
    "p_patch%cells%edge_idx":         [2, 0, 1],
    "p_patch%cells%edge_blk":         [2, 0, 1],
    "p_patch%edges%vertex_idx":       [2, 0, 1],
    "p_patch%edges%vertex_blk":       [2, 0, 1],
    "p_patch%edges%quad_idx":         [2, 0, 1],
    "p_patch%edges%quad_blk":         [2, 0, 1],
    "p_patch%cells%neighbor_idx":     [2, 0, 1],
    "p_patch%cells%neighbor_blk":     [2, 0, 1],
}


# Reduction locations
# reduce_maxZ at "T_l652_c652" is on CPU over nblks, it is ok

# segmented_reduce is removed to always run the kernel
# reduce_scan from gpu_cfl_clipping to gpu_levmask is length 1, is ok

# Reduce maxZ scalar from maxvcfl arr to vcflmax is over the full array, size should be upgraded to nproma * nlev

# Reduce scan in _for_it_46 -> over nblks
# from gpu_levmask[nblks, nlev] -> gpu_levelmask[nlev]
# This needs to be updated
```
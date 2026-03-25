"""
sc26_layout/extract_gpu_kernel_stage8.py
=========================================
Layout-permutation configs and SDFG helpers for GPU stage 8
(velocity_tendencies kernel).

Five groups — split COMPUTE into vertical and horizontal patterns:

  cv  COMPUTE_VERT   Arrays whose dominant access is vertical accumulation.
                     These are the ones that directly benefit from level-first:
                         z_w_con_c, z_w_con_c_full, z_w_concorr_mc,
                         z_w_concorr_me, z_w_v
                     Binary: identity [0,1,2]/[0,1] or level-first [1,0,2]/[1,0]

  ch  COMPUTE_HORIZ  Arrays written in horizontal stencil loops (je/jc inner).
                     Level-first here breaks coalescing; sweep to verify:
                         z_ekinh, z_kin_hor_e, z_vt_ie, z_v_grad_w,
                         zeta, maxvcfl_arr, levmask, cfl_clipping
                     Binary: identity or level-first

  f   FIELDS         Prognostic inputs/outputs + diagnostic outputs.
                     Read in both vertical and horizontal loops:
                         vn, w, vt, vn_ie, w_concorr_c, ddt_vn_apc_pc,
                         ddt_w_adv_pc, ddt_vn_cor_pc
                     Binary: identity or level-first (ntl always stays last)

  s   STENCIL        Read-only metric + interpolation coefficients.
                     Accessed with je/jc as innermost — level-first likely
                     hurts coalescing; sweep to confirm:
                         wgtfac_e/c, ddxn/ddxt/ddqz, coeff_*, geofac_*,
                         e_bln_c_s, c_lin_e, cells_aw_verts
                     Binary: identity or level-first

  n   CONN           Connectivity index/block tables.
                     All 6 permutations of 3 dims — [2,0,1] puts N-dim first
                     so je/jc access stays stride-1 after gather.

Total: 2 × 2 × 2 × 2 × 6 - 1 = 95 non-identity configs.

Config names: "cv{0|1}_ch{0|1}_f{0|1}_s{0|1}_n{perm}"
  cv/ch/f/s : 0 = identity,  1 = level-first
  n         : 3-digit permutation string (012 = identity, 201 = [2,0,1], ...)

Named aliases
-------------
  "named_empty"     : placeholder — no arrays permuted
  "named_original"  : exact original permute_map from stage-8 profiling

ntl convention
--------------
4-D arrays (ddt_*) have ntl as their last dimension.
Level-first perm = [1,0,2,3]  — nblks and ntl stay in place.

strip_gpu_prefix=True  strips "gpu_" from all array names before applying
PermuteDimensions (for SDFGs compiled without the prefix).
"""

from __future__ import annotations

from itertools import permutations as _iter_perms
from typing import Dict, List

import dace
from dace.codegen.control_flow import ConditionalBlock
from dace.properties import CodeBlock
from dace.transformation.layout.permute_dimensions import PermuteDimensions
from dace.sdfg.construction_utils import move_state_after, move_state_before


# ---------------------------------------------------------------------------
# Types
# ---------------------------------------------------------------------------
Perm    = List[int]
PermMap = Dict[str, Perm]

# ---------------------------------------------------------------------------
# Internal helpers
# ---------------------------------------------------------------------------

def _inverse_perm(p: Perm) -> Perm:
    inv = [0] * len(p)
    for i, v in enumerate(p):
        inv[v] = i
    return inv


def _make_config(permute_map: PermMap) -> dict:
    return {
        "permute_map": permute_map,
        "inverse_permute_map": {k: _inverse_perm(v) for k, v in permute_map.items()},
    }


def _label(p: Perm) -> str:
    return "".join(str(i) for i in p)


def _merge(*maps: PermMap) -> PermMap:
    out: PermMap = {}
    for m in maps:
        out.update(m)
    return out

# ---------------------------------------------------------------------------
# Group definitions
# ---------------------------------------------------------------------------

# cv — COMPUTE_VERT
# Vertical accumulation pattern: jk is the natural parallelism axis.
#   z_w_con_c(jc,jb)       += z_w_con_c_full(jc,jk,jb) * ...   vertical sum
#   z_w_concorr_mc(jc,jb)   = wgtfac_c * z_w_concorr_me(jc,jk) interpolation
#   z_w_concorr_me(je,jk,jb) written in vertical loop
#   z_w_v(iv,jk,jb)         vorticity vertical component
# Level-first [1,0,2] makes jk-access stride-1 for these.
_COMPUTE_VERT_PERMUTED: PermMap = {
    # 3-D (nproma, nlev, nblks) → (nlev, nproma, nblks)
    "gpu_z_w_con_c_full":   [1, 0, 2],
    "gpu_z_w_concorr_me":   [1, 0, 2],
    "gpu_z_w_v":            [1, 0, 2],
    # 2-D (nproma, nblks) → (nblks, nproma)
    "gpu_z_w_concorr_mc":   [1, 0],
    "gpu_z_w_con_c":        [1, 0],
}

# ch — COMPUTE_HORIZ
# Horizontal stencil pattern: je/jc is the innermost loop.
#   z_ekinh(jc,jk,jb)    = 0.5*(vn^2 + vt^2)  written per (jc,jk)
#   z_kin_hor_e(je,jk,jb) same, edge domain
#   z_vt_ie(je,jk,jb)    RBF tangential wind interpolation
#   z_v_grad_w(je,jk,jb) horizontal gradient of w
#   zeta(iv,jk,jb)        vorticity, horizontal loop over iv
#   maxvcfl_arr / levmask / cfl_clipping — written in horizontal loop
# Level-first [1,0,2] breaks stride-1 on je/jc; sweep to confirm hypothesis.
_COMPUTE_HORIZ_PERMUTED: PermMap = {
    # 3-D
    "gpu_z_ekinh":          [1, 0, 2],
    "gpu_z_kin_hor_e":      [1, 0, 2],
    "gpu_z_vt_ie":          [1, 0, 2],
    "gpu_z_v_grad_w":       [1, 0, 2],
    "gpu_zeta":             [1, 0, 2],
    "gpu_maxvcfl_arr":      [1, 0, 2],
    # 2-D
    "gpu_cfl_clipping":     [1, 0],
    "gpu_levmask":          [1, 0],
    #"gpu_levelmask":        [0], # Is 1D
}

# f — FIELDS
# Prognostic arrays (vn, w) are read in both vertical and horizontal loops.
# Diagnostic outputs (vt, vn_ie, ddt_*) are written in horizontal loops but
# read back in vertical loops (e.g. vn_ie used in w_concorr computation).
# 4-D arrays: ntl is always the last dim → perm [1,0,2,3].
_FIELDS_PERMUTED: PermMap = {
    # Prognostic 3-D
    "gpu___CG_p_prog__m_vn":              [1, 0, 2],
    "gpu___CG_p_prog__m_w":               [1, 0, 2],
    # Diagnostic 3-D
    "gpu___CG_p_diag__m_vt":              [1, 0, 2],
    "gpu___CG_p_diag__m_vn_ie":           [1, 0, 2],
    "gpu___CG_p_diag__m_vn_ie_ubc":       [1, 0, 2],
    "gpu___CG_p_diag__m_w_concorr_c":     [1, 0, 2],
    # Diagnostic 4-D  (nproma, nlev, nblks, ntl) → (nlev, nproma, nblks, ntl)
    "gpu___CG_p_diag__m_ddt_vn_apc_pc":   [1, 0, 2, 3],
    "gpu___CG_p_diag__m_ddt_w_adv_pc":    [1, 0, 2, 3],
    "gpu___CG_p_diag__m_ddt_vn_cor_pc":   [1, 0, 2, 3],
}

# s — STENCIL
# Read-only metric + interpolation coefficients.
# Predominantly accessed with je/jc as innermost loop:
#   wgtfac_e(je,jk,jb), ddxn_z_full(je,jk,jb) — horizontal gradient loop
#   e_bln_c_s(jc,ne,jb) — 3-edge BLN contraction, jc inner
#   geofac_*(je,ne,jb)  — geofac contraction, je inner
# Level-first likely hurts; included in sweep to confirm.
_STENCIL_PERMUTED: PermMap = {
    # Metric fields
    "gpu___CG_p_metrics__m_wgtfac_e":          [1, 0, 2],
    "gpu___CG_p_metrics__m_wgtfacq_e":         [1, 0, 2],
    "gpu___CG_p_metrics__m_wgtfac_c":          [1, 0, 2],
    "gpu___CG_p_metrics__m_ddxn_z_full":       [1, 0, 2],
    "gpu___CG_p_metrics__m_ddxt_z_full":       [1, 0, 2],
    "gpu___CG_p_metrics__m_ddqz_z_half":       [1, 0, 2],
    "gpu___CG_p_metrics__m_ddqz_z_full_e":     [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff1_dwdz":       [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff2_dwdz":       [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff_gradekin":    [1, 0, 2],
    # Interpolation coefficients
    "gpu___CG_p_int__m_e_bln_c_s":             [1, 0, 2],
    "gpu___CG_p_int__m_c_lin_e":               [1, 0, 2],
    "gpu___CG_p_int__m_geofac_n2s":            [1, 0, 2],
    "gpu___CG_p_int__m_geofac_grdiv":          [1, 0, 2],
    "gpu___CG_p_int__m_cells_aw_verts":        [1, 0, 2],
    "gpu___CG_p_int__m_geofac_rot":            [1, 0, 2],
}

# n — CONN
# Original Fortran layout: (nproma, nblks, N) where N ∈ {2,3,4}.
# [2,0,1] → (N, nproma, nblks): je/jc still stride-1 after gather on N.
# Sweep all 6 to find optimal.
_CONN_ARRAYS: List[str] = [
    "gpu___CG_p_patch__CG_cells__m_edge_idx",
    "gpu___CG_p_patch__CG_cells__m_edge_blk",
    "gpu___CG_p_patch__CG_cells__m_neighbor_idx",
    "gpu___CG_p_patch__CG_cells__m_neighbor_blk",
    "gpu___CG_p_patch__CG_edges__m_cell_idx",
    "gpu___CG_p_patch__CG_edges__m_cell_blk",
    "gpu___CG_p_patch__CG_edges__m_vertex_idx",
    "gpu___CG_p_patch__CG_edges__m_vertex_blk",
    "gpu___CG_p_patch__CG_edges__m_quad_idx",
    "gpu___CG_p_patch__CG_edges__m_quad_blk",
    "gpu___CG_p_patch__CG_verts__m_cell_blk",
    "gpu___CG_p_patch__CG_verts__m_cell_idx",
    "gpu___CG_p_patch__CG_verts__m_edge_idx",
    "gpu___CG_p_patch__CG_verts__m_edge_blk",
]

_ALL_CONN_PERMS: List[Perm] = [list(p) for p in _iter_perms([0, 1, 2])]
_ID_CONN: Perm = [0, 1, 2]


def _conn_map(perm: Perm) -> PermMap:
    return {a: perm for a in _CONN_ARRAYS}

# ---------------------------------------------------------------------------
# Config generation   2 × 2 × 2 × 2 × 6 - 1 = 95 non-identity configs
# ---------------------------------------------------------------------------

def _cfg_name(cv: int, ch: int, f: int, s: int, np: Perm) -> str:
    return f"cv{cv}_ch{ch}_f{f}_s{s}_n{_label(np)}"


def _build_cfg(cv: int, ch: int, f: int, s: int, np: Perm) -> dict:
    parts: List[PermMap] = []
    if cv: parts.append(_COMPUTE_VERT_PERMUTED)
    if ch: parts.append(_COMPUTE_HORIZ_PERMUTED)
    if f:  parts.append(_FIELDS_PERMUTED)
    if s:  parts.append(_STENCIL_PERMUTED)
    if np != _ID_CONN: parts.append(_conn_map(np))
    return _make_config(_merge(*parts))


PERMUTE_CONFIGS: Dict[str, dict] = {}

for _cv in (0, 1):
    for _ch in (0, 1):
        for _f in (0, 1):
            for _s in (0, 1):
                for _np in _ALL_CONN_PERMS:
                    if _cv == 0 and _ch == 0 and _f == 0 and _s == 0 and _np == _ID_CONN:
                        continue  # pure identity = unpermuted baseline
                    PERMUTE_CONFIGS[_cfg_name(_cv, _ch, _f, _s, _np)] = \
                        _build_cfg(_cv, _ch, _f, _s, _np)

# ---------------------------------------------------------------------------
# Named aliases
# ---------------------------------------------------------------------------


# named_empty: all arrays level-first, connectivity N-first with [2,0,1]
PERMUTE_CONFIGS["nlev_first"] = _make_config({
    # Work arrays [1,0,2]: (nlev, nproma, nblks)
    "gpu_z_ekinh":                                  [1, 0, 2],
    "gpu_z_kin_hor_e":                              [1, 0, 2],
    "gpu_z_v_grad_w":                               [1, 0, 2],
    "gpu_z_w_v":                                    [1, 0, 2],
    "gpu_zeta":                                     [1, 0, 2],
    "gpu_z_vt_ie":                                  [1, 0, 2],
    "gpu_z_w_concorr_me":                           [1, 0, 2],
    "gpu_z_w_concorr_mc":                           [1, 0],
    "gpu_z_w_con_c_full":                           [1, 0, 2],
    "gpu_z_w_con_c":                                [1, 0],
    "gpu_maxvcfl_arr":                              [1, 0, 2],
    "gpu_cfl_clipping":                             [1, 0],
    "gpu_levmask":                                  [1, 0],
    # Prognostic / diagnostic [1,0,2]
    "gpu___CG_p_prog__m_vn":                        [1, 0, 2],
    "gpu___CG_p_prog__m_w":                         [1, 0, 2],
    "gpu___CG_p_diag__m_vt":                        [1, 0, 2],
    "gpu___CG_p_diag__m_vn_ie":                     [1, 0, 2],
    "gpu___CG_p_diag__m_vn_ie_ubc":                 [1, 0, 2],
    "gpu___CG_p_diag__m_w_concorr_c":               [1, 0, 2],
    "gpu___CG_p_diag__m_ddt_vn_apc_pc":             [1, 0, 2, 3],
    "gpu___CG_p_diag__m_ddt_w_adv_pc":              [1, 0, 2, 3],
    "gpu___CG_p_diag__m_ddt_vn_cor_pc":             [1, 0, 2, 3],
    # Metrics [1,0,2]
    "gpu___CG_p_metrics__m_wgtfac_e":               [1, 0, 2],
    "gpu___CG_p_metrics__m_wgtfacq_e":              [1, 0, 2],
    "gpu___CG_p_metrics__m_wgtfac_c":               [1, 0, 2],
    "gpu___CG_p_metrics__m_ddxn_z_full":            [1, 0, 2],
    "gpu___CG_p_metrics__m_ddxt_z_full":            [1, 0, 2],
    "gpu___CG_p_metrics__m_ddqz_z_half":            [1, 0, 2],
    "gpu___CG_p_metrics__m_ddqz_z_full_e":          [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff1_dwdz":            [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff2_dwdz":            [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff_gradekin":         [1, 0, 2],
    # Interp: (nproma, N, nblks) → [1,0,2] → (N, nproma, nblks)
    "gpu___CG_p_int__m_e_bln_c_s":                  [0, 1, 2],
    "gpu___CG_p_int__m_c_lin_e":                    [0, 1, 2],
    "gpu___CG_p_int__m_geofac_n2s":                 [0, 1, 2],
    "gpu___CG_p_int__m_geofac_grdiv":               [0, 1, 2],
    "gpu___CG_p_int__m_cells_aw_verts":             [0, 1, 2],
    "gpu___CG_p_int__m_geofac_rot":                 [0, 1, 2],
    # Connectivity: (nproma, nblks, N) → [2,0,1] → (N, nproma, nblks)
    # [2,1,0] was WRONG: gives (N, nblks, nproma), stride for jc = N*nblks
    "gpu___CG_p_patch__CG_verts__m_cell_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_idx":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_idx":       [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_idx":     [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_blk":     [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_idx":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_idx":   [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_blk":   [0, 2, 1],
})

# index_only: only connectivity + interp get N-first, everything else identity
PERMUTE_CONFIGS["index_only"] = _make_config({
    # Work/prog/diag: no neighbor dim, identity = no change needed
    # Metrics: (nproma, nlev, nblks) — no neighbor dim, identity
    # Interp: (nproma, N, nblks) → [1,0,2] → (N, nproma, nblks)
    # [0,1,2] was WRONG: identity leaves nproma first, N not first
    "gpu___CG_p_int__m_e_bln_c_s":                  [0, 1, 2],
    "gpu___CG_p_int__m_c_lin_e":                    [0, 1, 2],
    "gpu___CG_p_int__m_geofac_n2s":                 [0, 1, 2],
    "gpu___CG_p_int__m_geofac_grdiv":               [0, 1, 2],
    "gpu___CG_p_int__m_cells_aw_verts":             [0, 1, 2],
    "gpu___CG_p_int__m_geofac_rot":                 [0, 1, 2],
    # Connectivity: (nproma, nblks, N) → [2,0,1] → (N, nproma, nblks)
    # [2,1,0] was WRONG: gives (N, nblks, nproma), stride for jc = N*nblks
    "gpu___CG_p_patch__CG_verts__m_cell_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_idx":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_idx":       [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_idx":     [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_blk":     [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_idx":       [0, 2, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_blk":       [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_idx":   [0, 2, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_blk":   [0, 2, 1],
})

# ---------------------------------------------------------------------------
# Query helpers
# ---------------------------------------------------------------------------

def _parse_name(config_name: str):
    """Return (cv, ch, f, s, conn_perm) from a config name string."""
    base = config_name.removesuffix("_ms").removesuffix("_mu")

    if base == "nlev_first":
        return 1, 1, 1, 1, [2, 0, 1]
    if base == "index_only":
        return 0, 0, 0, 0, [2, 0, 1]

    # Split each token at the boundary between letters and digits.
    # "cv1" → ("cv", "1"),  "f1" → ("f", "1"),  "n201" → ("n", "201")
    import re
    parts = {m.group(1): m.group(2)
             for m in (re.fullmatch(r'([a-z]+)(\d+)', tok)
                       for tok in base.split("_"))
             if m}
    cv = int(parts["cv"])
    ch = int(parts["ch"])
    f  = int(parts["f"])
    s  = int(parts["s"])
    np = [int(x) for x in parts["n"]]
    return cv, ch, f, s, np


def needs_reduction_change(config_name: str) -> bool:
    """
    True when COMPUTE_VERT arrays are level-first (cv=1).
    These are the vertical-accumulation arrays; their segmented reduction
    must switch to the level-outer variant.

        if needs_reduction_change(cfg):
            change_segmented_reduction(sdfg)   # level-outer
        else:
            to_segmented_reduction(sdfg)       # nproma-outer (default)
    """
    cv, _, _, _, _ = _parse_name(config_name)
    return bool(cv)

# ---------------------------------------------------------------------------
# Prefix stripping helper
# ---------------------------------------------------------------------------

def _strip_gpu(pm: PermMap) -> PermMap:
    return {(k[4:] if k.startswith("gpu_") else k): v for k, v in pm.items()}

def add_timers_after_lowering(sdfg: dace.SDFG):
    # label: check_bitwidth_cond
    matches = {n for n in sdfg.nodes() if n.label == "check_bitwidth_cond" and isinstance(n, ConditionalBlock)}
    assert len(matches) == 1
    check_bitwidth_cond = matches.pop()
    permute_in_state = check_bitwidth_cond
    permute_out_states = {s for s in sdfg.all_states() if s.label == "permute_out"}
    if len(permute_out_states) != 1:
        assert len(permute_out_states) == 0
        # Do it before copy out
        exit_interface_state  = {
            s for s in sdfg.all_states()
            if s.label == "block" and "deflatten" in {n.label for n in s.nodes()}}.pop()
        permute_out_state = exit_interface_state
    else:
        permute_out_state = permute_out_states.pop()
    add_timers_w_states(sdfg, permute_in_state, permute_out_state)


def add_timers(sdfg: dace.SDFG):
    permute_in_states  = {s for s in sdfg.all_states() if s.label == "permute_in"}
    if len(permute_in_states) != 1:
        assert len(permute_in_states) == 0
        # Do it after copy in
        entry_interface_state = {
            s for s in sdfg.all_states() if s.label == "entry_interface"}.pop()
        permute_in_state = entry_interface_state
    else:
        permute_in_state = permute_in_states.pop()
    permute_out_states = {s for s in sdfg.all_states() if s.label == "permute_out"}
    if len(permute_out_states) != 1:
        assert len(permute_out_states) == 0
        # Do it before copy out
        exit_interface_state  = {
            s for s in sdfg.all_states()
            if s.label == "block" and "deflatten" in {n.label for n in s.nodes()}}.pop()
        permute_out_state = exit_interface_state
    else:
        permute_out_state = permute_out_states.pop()
    add_timers_w_states(sdfg, permute_in_state, permute_out_state)

def add_timers_w_states(sdfg, copy_in_state: dace.SDFGState, copy_out_state: dace.SDFGState):
    root_sdfg = sdfg
    assert sdfg.parent_nsdfg_node is None
    clock_in  = sdfg.add_state_after(copy_in_state, "clock_in")
    clock_out = sdfg.add_state_before(copy_out_state,  "clock_out")
    _flush_code = f"""
#include <iostream>
#include <cuda_runtime.h>
#include <cstdlib>
#include <cstdio>

#define CCHECK(call)                                                        \\
    do {{                                                                        \\
        cudaError_t _e = (call);                                                \\
        if (_e != cudaSuccess) {{                                                \\
            fprintf(stderr, "[CUDA] %s:%d  %s\\n",                             \\
                    __FILE__, __LINE__, cudaGetErrorString(_e));                \\
            std::abort();                                                       \\
        }}                                                                       \\
    }} while (0)

static constexpr int FLUSH_N       = 8192;
static constexpr int FLUSH_STEPS   = 20;
static constexpr int FLUSH_BLOCK_X = 32;
static constexpr int FLUSH_BLOCK_Y = 8;

static double* flush_A = nullptr;
static double* flush_B = nullptr;

static __global__ void jacobi2d_kernel(const double* __restrict__ src,
                                        double* __restrict__ dst, int N)
{{
    int i = blockIdx.y*blockDim.y + threadIdx.y;
    int j = blockIdx.x*blockDim.x + threadIdx.x;
    if (i>=1 && i<N-1 && j>=1 && j<N-1)
        dst[i*N+j] = 0.25*(src[(i-1)*N+j]+src[(i+1)*N+j]+
                           src[i*N+(j-1)]+src[i*N+(j+1)]);
}}

static __global__ void jacobi2d_init_kernel(double* A, int N)
{{
    int idx = blockIdx.x*blockDim.x + threadIdx.x;
    for (int i=idx; i<N*N; i+=gridDim.x*blockDim.x)
    {{
        int r=i/N, c=i%N;
        A[i]=(r==0||r==N-1||c==0||c==N-1)?1.0:0.0;
    }}
}}

static void flush_all_caches_v2()
{{
    size_t bytes=(size_t)FLUSH_N*FLUSH_N*sizeof(double);
    if(!flush_A){{
        CCHECK(cudaMalloc(&flush_A, bytes));
        CCHECK(cudaMalloc(&flush_B, bytes));
    }}
    int it=256, ib=(FLUSH_N*FLUSH_N+it-1)/it;
    jacobi2d_init_kernel<<<ib,it>>>(flush_A, FLUSH_N);
    CCHECK(cudaGetLastError());
    jacobi2d_init_kernel<<<ib,it>>>(flush_B, FLUSH_N);
    CCHECK(cudaGetLastError());
    CCHECK(cudaDeviceSynchronize());

    dim3 block(FLUSH_BLOCK_X, FLUSH_BLOCK_Y);
    dim3 grid((FLUSH_N+block.x-1)/block.x, (FLUSH_N+block.y-1)/block.y);
    double* src=flush_A; double* dst=flush_B;
    for(int step=0; step<FLUSH_STEPS; ++step){{
        jacobi2d_kernel<<<grid,block>>>(src, dst, FLUSH_N);
        CCHECK(cudaGetLastError());
        double* tmp=src; src=dst; dst=tmp;
    }}
    CCHECK(cudaDeviceSynchronize());

    srand(42);
    int spots[4][2];
    for(int k=0; k<4; ++k){{
        spots[k][0]=1+rand()%(FLUSH_N-2);
        spots[k][1]=1+rand()%(FLUSH_N-2);
    }}
    double hash=0.0;
    for(int k=0; k<4; ++k){{
        double val;
        CCHECK(cudaMemcpy(&val,
                              src + spots[k][0]*FLUSH_N + spots[k][1],
                              sizeof(double), cudaMemcpyDeviceToHost));
        hash+=val;
    }}
    std::cout<<"[flush] jacobi2d hash = "<<hash<<std::endl;
}}

static void gpu_timer_split({root_sdfg.label}_state_t* __state){{
    static cudaEvent_t start, stop;
    static bool is_first_call=true;
    cudaStream_t stream=__state->gpu_context->streams[0];
    if(is_first_call){{
        CCHECK(cudaDeviceSynchronize());
        CCHECK(cudaStreamSynchronize(stream));
        is_first_call=false;
        CCHECK(cudaDeviceSynchronize());
        flush_all_caches_v2();
        CCHECK(cudaDeviceSynchronize());
        std::cout<<"[Timer] Start recorded..."<<std::endl;
        CCHECK(cudaEventCreate(&start));
        CCHECK(cudaEventCreate(&stop));
        CCHECK(cudaEventRecord(start, stream));
    }} else {{
        CCHECK(cudaEventRecord(stop, stream));
        CCHECK(cudaEventSynchronize(stop));
        float ms=0;
        CCHECK(cudaEventElapsedTime(&ms, start, stop));
        std::cout<<"[Timer] Elapsed time: "<<ms<<" ms"<<std::endl;
        CCHECK(cudaDeviceSynchronize());
        flush_all_caches_v2();
        CCHECK(cudaDeviceSynchronize());
        CCHECK(cudaEventDestroy(start));
        CCHECK(cudaEventDestroy(stop));
        is_first_call=true;
    }}
}}
"""
    ct1 = dace.nodes.Tasklet("c1", {}, {}, "gpu_timer_split(__state);",
                              language=dace.dtypes.Language.CPP,
                              side_effects=True, code_global=_flush_code)
    ct2 = dace.nodes.Tasklet("c1", {}, {}, "gpu_timer_split(__state);",
                              language=dace.dtypes.Language.CPP,
                              code_global="", side_effects=True)
    clock_in.add_node(ct1)
    clock_out.add_node(ct2)
    return clock_in, clock_out


def add_symbols(sdfg: dace.SDFG):
    symlist = [
        "__f2dace_A_z_kin_hor_e_d_0_s", "__f2dace_A_z_kin_hor_e_d_1_s",
        "__f2dace_A_z_kin_hor_e_d_2_s", "__f2dace_A_z_vt_ie_d_0_s",
        "__f2dace_A_z_vt_ie_d_1_s",     "__f2dace_A_z_vt_ie_d_2_s",
        "__f2dace_A_z_w_concorr_me_d_0_s", "__f2dace_A_z_w_concorr_me_d_1_s",
        "__f2dace_A_z_w_concorr_me_d_2_s", "__f2dace_OA_z_kin_hor_e_d_0_s",
        "__f2dace_OA_z_kin_hor_e_d_1_s", "__f2dace_OA_z_kin_hor_e_d_2_s",
        "__f2dace_OA_z_vt_ie_d_0_s",    "__f2dace_OA_z_vt_ie_d_1_s",
        "__f2dace_OA_z_vt_ie_d_2_s",    "__f2dace_OA_z_w_concorr_me_d_0_s",
        "__f2dace_OA_z_w_concorr_me_d_1_s", "__f2dace_OA_z_w_concorr_me_d_2_s",
        "dt_linintp_ubc", "dtime", "istep", "ldeepatmo", "lvn_only", "ntnd",
    ]
    new_start = sdfg.add_state_before(sdfg.start_block, "sym_force_use", True)
    sname, _ = sdfg.add_scalar("dummy_symbol_sum", dtype=dace.float64,
                                transient=True, storage=dace.StorageType.Register)
    inputs = {sym for sym in symlist if sym in sdfg.arrays}
    tstr = (
        "_out = "
        + " + ".join(f"_in_{inp}" for inp in inputs)
        + " + "
        + " + ".join(sym for sym in symlist if sym not in inputs)
    )
    new_tasklet = new_start.add_tasklet(
        "sym_force_use", {"_in_" + s for s in inputs}, {"_out"}, tstr,
        side_effects=True)
    for sym in symlist:
        if sym in sdfg.arrays:
            an = new_start.add_access(sym)
            new_start.add_edge(an, None, new_tasklet, "_in_" + sym,
                               dace.Memlet(f"{sym}[0]"))
        elif sym not in sdfg.symbols:
            sdfg.add_symbol(sym, dace.int32, False)
    new_start.add_edge(new_tasklet, "_out", new_start.add_access(sname), None,
                       dace.Memlet(f"{sname}[0]"))


def update_reductions(sdfg: dace.SDFG, permuted_levmask:bool=False):
    # reads levmask[0:tmp_struct_13, 0:90] (block)
    # for it 46 make it to a block reduction
    # writes to gpu levelmask[0:90]
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry):
            params: List[str] = n.map.params
            if params == ["_for_it_46"]:
                exit_node: dace.nodes.MapExit = g.exit_node(n)
                nds = g.all_nodes_between(n, exit_node)
                src_nodes = {e.src for e in g.in_edges(n)}
                dst_nodes = {e.dst for e in g.out_edges(exit_node)}
                assert len(src_nodes) == 1
                assert len(dst_nodes) == 1
                src_node = src_nodes.pop()
                dst_node = dst_nodes.pop()

                for nd in list(nds) + [n, exit_node]:
                    g.remove_node(nd)
                
                begin = "(replaced_var_3 - 1)"
                end = "(replaced_var_2 - 1)"

                if permuted_levmask:
                    D = "90"
                    N = "tmp_struct_symbol_13"
                    tasklet_code = f"reduce_scan_last_dim(in_gpu_levmask, out_gpu_levelmask, {begin}, {end}, {D}, {N});"
                else:
                    D = "90"
                    N = "tmp_struct_symbol_13"
                    tasklet_code = f"reduce_scan_first_dim(in_gpu_levmask, out_gpu_levelmask, {begin}, {end}, {D}, {N});"
                
                assert isinstance(g, dace.SDFGState)
                t = g.add_tasklet(
                    "red_levmask",
                    {"in_gpu_levmask"},
                    {"out_gpu_levelmask"},
                    code = tasklet_code,
                    language = dace.dtypes.Language.CPP,
                )
                g.add_edge(src_node, None, t, "in_gpu_levmask",
                            dace.Memlet.from_array("gpu_levmask", g.sdfg.arrays["gpu_levmask"]))
                g.add_edge(t, "out_gpu_levelmask", dst_node, None,
                            dace.Memlet.from_array("gpu_levelmask", g.sdfg.arrays["gpu_levelmask"]))

    # reduce_maxZ_to_address  / gpu_maxvcfl_arr -> to full array size
    upded = False
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.Tasklet) and \
            len(g.out_edges(n)) == 1 and \
            len(g.in_edges(n)) == 0 and \
            "i_endidx_var_149" in n.code.as_string and \
            "i_startidx_var_148" in n.code.as_string and \
            "size_reduce_maxZ_to_scalar" in str(n.label) and \
            "size" in n.out_connectors:
            n.code = CodeBlock("size = (tmp_struct_symbol_4 * 88)")
            upded = True
        else:
            if  isinstance(n, dace.nodes.Tasklet) and "size" in n.out_connectors:
                print(n)
                print(n.code.as_string)
    #assert upded

def levmask_is_permuted(config_name: str) -> bool:
    _, ch, _, _, _ = _parse_name(config_name)
    return bool(ch)

def permute_sdfg(
    sdfg: dace.SDFG,
    config_name: str = "nlev_first",
    shuffle_map: bool = True,
    strip_gpu_prefix: bool = False,
) -> dace.SDFG:
    if config_name not in PERMUTE_CONFIGS:
        sample = sorted(k for k in PERMUTE_CONFIGS
                        if k not in ("nlev_first", "index_only"))[:5]
        raise KeyError(
            f"Unknown config '{config_name}'. "
            f"Available (sample): {sample}"
        )
    cfg = PERMUTE_CONFIGS[config_name]
    pm  = cfg["permute_map"]
    inv = cfg["inverse_permute_map"]
    if strip_gpu_prefix:
        pm  = _strip_gpu(pm)
        inv = _strip_gpu(inv)

    # This needs to be updated before permuting arrays
    if needs_reduction_change(config_name):
        update_reductions(sdfg, permuted_levmask=levmask_is_permuted(config_name))

    PermuteDimensions(permute_map=pm, add_permute_maps=True,
                      column_major=True).apply_pass(sdfg, {})
    sdfg.validate()

    permute_in_state  = {s for s in sdfg.all_states() if s.label == "permute_in"}.pop()
    permute_out_state = {s for s in sdfg.all_states() if s.label == "permute_out"}.pop()

    entry_interface_state = {
        s for s in sdfg.all_states() if s.label == "entry_interface"}.pop()
    exit_interface_state  = {
        s for s in sdfg.all_states()
        if s.label == "block" and "deflatten" in {n.label for n in s.nodes()}}.pop()

    move_state_after(sdfg,  permute_in_state,  entry_interface_state)
    move_state_before(sdfg, permute_out_state, exit_interface_state)

    for s in {entry_interface_state, exit_interface_state}:
        for e in s.edges():
            if e.data.data is not None and e.data.data.startswith("permuted_"):
                e.data.data = e.data.data.removeprefix("permuted_")
                if e.data.data in inv:
                    pi = inv[e.data.data]
                    e.data.subset = dace.subsets.Range(
                        [e.data.subset[pi[i]] for i in range(len(pi))])
        for n in s.data_nodes():
            if n.data is not None and n.data.startswith("permuted_"):
                n.data = n.data.removeprefix("permuted_")

    sdfg.validate()

    from dace.transformation.dataflow import MapDimShuffle

    if shuffle_map:
        for n, g in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.MapEntry):
                if isinstance(n, dace.nodes.MapEntry) and len(n.map.params) == 2:
                    permuted_param_names = list(reversed(n.map.params))
                    MapDimShuffle().apply_to(
                        sdfg=g.sdfg, map_entry=n,
                        options={"parameters": permuted_param_names})

    add_timers_w_states(sdfg, permute_in_state, permute_out_state)
    add_symbols(sdfg)
    sdfg.validate()
    return sdfg

def permute_sdfg_after_lowering(
    sdfg: dace.SDFG,
    config_name: str = "nlev_first",
    shuffle_map: bool = True,
    strip_gpu_prefix: bool = False,
) -> dace.SDFG:
    cfg = PERMUTE_CONFIGS[config_name]
    pm = cfg["permute_map"]
    extended = dict(pm)
    for arr, perm in pm.items():
        for suffix in ("_uint8", "_uint16"):
            extended[arr + suffix] = perm
    # Temporarily patch the config, call original, restore
    orig = cfg["permute_map"]
    orig_inv = cfg["inverse_permute_map"]
    cfg["permute_map"] = extended
    cfg["inverse_permute_map"] = {k: _inverse_perm(v) for k, v in extended.items()}
    try:
        return permute_sdfg(sdfg, config_name, shuffle_map, strip_gpu_prefix)
    finally:
        cfg["permute_map"] = orig
        cfg["inverse_permute_map"] = orig_inv
# ---------------------------------------------------------------------------
# Sanity check
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    named = {"index_only", "nlev_first"}
    sweep = {k: v for k, v in PERMUTE_CONFIGS.items() if k not in named}
    expected = 2 * 2 * 2 * 2 * 6 - 1   # 95
    print(f"Sweep configs      : {len(sweep)}  (expected {expected})")
    assert len(sweep) == expected

    # Verify all 6 conn perms covered
    conn_seen = {tuple(_parse_name(n)[4]) for n in sweep}
    assert len(conn_seen) == 6, f"Expected 6 conn perms, got {conn_seen}"
    print(f"CONN perms covered : {sorted(conn_seen)}")

    # Verify inverse perms
    for cname, cfg in PERMUTE_CONFIGS.items():
        for arr, p in cfg["permute_map"].items():
            inv = cfg["inverse_permute_map"][arr]
            assert [p[inv[i]] for i in range(len(p))] == list(range(len(p)))
    print("Inverse-perm check : ok")

    n_red = sum(1 for c in sweep if needs_reduction_change(c))
    print(f"Reduction-change   : {n_red} configs  (expected {(expected+1) // 2})")

    print("\nGroup sizes:")
    for label, grp in (
        ("cv (COMPUTE_VERT)",  _COMPUTE_VERT_PERMUTED),
        ("ch (COMPUTE_HORIZ)", _COMPUTE_HORIZ_PERMUTED),
        ("f  (FIELDS)",        _FIELDS_PERMUTED),
        ("s  (STENCIL)",       _STENCIL_PERMUTED),
        ("n  (CONN arrays)",   dict.fromkeys(_CONN_ARRAYS)),
    ):
        print(f"  {label:22s}  {len(grp):2d} arrays")

    # Print all sweep configs grouped by conn permutation
    print(f"\nAll {len(sweep)} sweep configs:")
    for np in _ALL_CONN_PERMS:
        label = _label(np)
        group = sorted(k for k in sweep if k.endswith(f"_n{label}"))
        print(f"\n  n={label}  ({len(group)} configs)")
        for name in group:
            cv, ch, f, s, _ = _parse_name(name)
            active = "+".join(
                g for g, flag in [("cv", cv), ("ch", ch), ("f", f), ("s", s)] if flag
            ) or "none"
            print(f"    {name:30s}  groups: {active}")

    # Print named configs with their array counts
    print(f"\nNamed configs:")
    for name in sorted(named):
        if name in PERMUTE_CONFIGS:
            n_arrays = len(PERMUTE_CONFIGS[name]["permute_map"])
            print(f"  {name:20s}  {n_arrays} arrays permuted")

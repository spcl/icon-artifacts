"""
DaCe Python frontend translation of two kernels from ICON's
mo_solve_nonhydro.f90:

  1. compute_expl_rho_exner  — explicit parts of density & Exner pressure
     (top-level and other-levels loops MERGED into a single jk=0..nlev-1)

  2. solve_tridiag_w         — Thomas-algorithm tridiagonal solve for w
     (forward sweep jk=1..nlev-1, backward sweep jk=nlev-2..1;
      jk=0 is a Dirichlet boundary that cannot be folded into the
      recurrence because the forward sweep accesses jk-1)

Array layout convention (permuted from Fortran):
  Fortran (jc, jk, jb) → Python (jb, jk, jc)
  Fortran (jc, jk)     → Python (jk, jc)
  Fortran (jk)          → Python (jk)

All indices are 0-based.
nproma, nlev passed as explicit integer parameters (DaCe symbols).

Source:
  https://gitlab.dkrz.de/icon/icon-model/-/blob/release-2025.10-public/
  src/atm_dyn_iconam/mo_solve_nonhydro.f90
"""

import dace
import numpy as np

# ---------------------------------------------------------------------------
# Symbolic sizes
# ---------------------------------------------------------------------------
nproma = dace.symbol('nproma')
nlev   = dace.symbol('nlev')
nlevp1 = dace.symbol('nlevp1')   # == nlev + 1
nblks  = dace.symbol('nblks')


# ===================================================================
# Kernel 1: Merged explicit rho / exner  (single jk=0..nlev-1 loop)
# ===================================================================
@dace.program
def compute_expl_rho_exner(
    # --- Prognostic (read) ---
    p_nh_prog_nnow_rho:              dace.float64[nblks, nlev, nproma],
    # --- Diagnostics (read) ---
    p_nh_diag_exner_pr:              dace.float64[nblks, nlev, nproma],
    p_nh_diag_theta_v_ic:            dace.float64[nblks, nlevp1, nproma],
    p_nh_diag_ddt_exner_phy:         dace.float64[nblks, nlev, nproma],
    # --- Metrics (read) ---
    p_nh_metrics_inv_ddqz_z_full:    dace.float64[nblks, nlev, nproma],
    p_nh_metrics_deepatmo_divzU_mc:  dace.float64[nlev],
    p_nh_metrics_deepatmo_divzL_mc:  dace.float64[nlev],
    # --- Per-block working arrays (read) ---
    z_flxdiv_mass:    dace.float64[nlev, nproma],
    z_flxdiv_theta:   dace.float64[nlev, nproma],
    z_contr_w_fl_l:   dace.float64[nlevp1, nproma],
    z_beta:           dace.float64[nlev, nproma],
    # --- Per-block output arrays (write) ---
    z_rho_expl:       dace.float64[nlev, nproma],
    z_exner_expl:     dace.float64[nlev, nproma],
    # --- Scalars ---
    dtime:  dace.float64,
    jb:     dace.int32,
):
    """
    Merged single loop over ALL levels jk=0..nlev-1.

    The original Fortran split jk=1 (top) from jk=2..nlev, but
    the formulas are identical when you substitute jk=1 into the
    general expression, so we merge them.
    """
    for jk in range(nlev):
        z_rho_expl[jk, :] = (
            p_nh_prog_nnow_rho[jb, jk, :]
            - dtime * p_nh_metrics_inv_ddqz_z_full[jb, jk, :]
            * (z_flxdiv_mass[jk, :]
               + z_contr_w_fl_l[jk, :]     * p_nh_metrics_deepatmo_divzU_mc[jk]
               - z_contr_w_fl_l[jk + 1, :] * p_nh_metrics_deepatmo_divzL_mc[jk])
        )

        z_exner_expl[jk, :] = (
            p_nh_diag_exner_pr[jb, jk, :]
            - z_beta[jk, :]
            * (z_flxdiv_theta[jk, :]
               + p_nh_diag_theta_v_ic[jb, jk, :]     * z_contr_w_fl_l[jk, :]
                 * p_nh_metrics_deepatmo_divzU_mc[jk]
               - p_nh_diag_theta_v_ic[jb, jk + 1, :] * z_contr_w_fl_l[jk + 1, :]
                 * p_nh_metrics_deepatmo_divzL_mc[jk])
            + dtime * p_nh_diag_ddt_exner_phy[jb, jk, :]
        )


# ===================================================================
# Kernel 2: Tridiagonal solve for w  (Thomas algorithm)
# ===================================================================
@dace.program
def solve_tridiag_w(
    # --- Metrics (read) ---
    p_nh_metrics_vwind_impl_wgt:     dace.float64[nblks, nproma],
    p_nh_diag_theta_v_ic:            dace.float64[nblks, nlevp1, nproma],
    p_nh_metrics_ddqz_z_half:        dace.float64[nblks, nlevp1, nproma],
    p_nh_metrics_deepatmo_divzU_mc:  dace.float64[nlev],
    p_nh_metrics_deepatmo_divzL_mc:  dace.float64[nlev],
    # --- Per-block working arrays ---
    z_beta:       dace.float64[nlev, nproma],
    z_alpha:      dace.float64[nlevp1, nproma],
    z_q:          dace.float64[nlev, nproma],
    z_w_expl:     dace.float64[nlevp1, nproma],
    z_exner_expl: dace.float64[nlev, nproma],
    # --- Prognostic (read/write) ---
    p_nh_prog_nnew_w: dace.float64[nblks, nlevp1, nproma],
    # --- Scalars ---
    dtime: dace.float64,
    cpd:   dace.float64,
    jb:    dace.int32,
):
    """
    Thomas-algorithm tridiagonal solve for w on a single block jb.

    Preconditions (set by caller):
      z_q[0, :]                 = 0
      p_nh_prog_nnew_w[jb, 0, :]    = upper BC (0 or UBC)
      p_nh_prog_nnew_w[jb, nlev, :] = lower BC (w_concorr_c)

    The forward sweep CANNOT start at jk=0 because it accesses
    z_beta[jk-1], z_alpha[jk-1], z_q[jk-1], and w[jk-1], which
    would go to index -1.  Level 0 is a prescribed Dirichlet BC,
    not a Thomas row.
    """

    # 1-D temporaries over the parallel nproma dimension
    z_gamma = np.empty([nproma], dtype=dace.float64)
    z_a     = np.empty([nproma], dtype=dace.float64)
    z_b     = np.empty([nproma], dtype=dace.float64)
    z_c     = np.empty([nproma], dtype=dace.float64)
    z_g     = np.empty([nproma], dtype=dace.float64)

    # ---- Forward sweep: jk = 1 .. nlev-1 (0-based) ----
    for jk in range(1, nlev):
        z_gamma[:] = (dtime * cpd
                      * p_nh_metrics_vwind_impl_wgt[jb, :]
                      * p_nh_diag_theta_v_ic[jb, jk, :]
                      / p_nh_metrics_ddqz_z_half[jb, jk, :])

        z_a[:] = (-z_gamma[:]
                  * z_beta[jk - 1, :]
                  * z_alpha[jk - 1, :]
                  * p_nh_metrics_deepatmo_divzU_mc[jk - 1])

        z_c[:] = (-z_gamma[:]
                  * z_beta[jk, :]
                  * z_alpha[jk + 1, :]
                  * p_nh_metrics_deepatmo_divzL_mc[jk])

        z_b[:] = (1.0
                  + z_gamma[:] * z_alpha[jk, :]
                  * (z_beta[jk - 1, :] * p_nh_metrics_deepatmo_divzL_mc[jk - 1]
                     + z_beta[jk, :]   * p_nh_metrics_deepatmo_divzU_mc[jk]))

        z_g[:] = 1.0 / (z_b[:] + z_a[:] * z_q[jk - 1, :])

        z_q[jk, :] = -z_c[:] * z_g[:]

        p_nh_prog_nnew_w[jb, jk, :] = (
            z_w_expl[jk, :]
            - z_gamma[:] * (z_exner_expl[jk - 1, :] - z_exner_expl[jk, :])
        )

        p_nh_prog_nnew_w[jb, jk, :] = (
            (p_nh_prog_nnew_w[jb, jk, :]
             - z_a[:] * p_nh_prog_nnew_w[jb, jk - 1, :])
            * z_g[:]
        )

    # ---- Backward sweep: jk = nlev-2 .. 1 (0-based) ----
    for jk in range(nlev - 2, 0, -1):
        p_nh_prog_nnew_w[jb, jk, :] = (
            p_nh_prog_nnew_w[jb, jk, :]
            + p_nh_prog_nnew_w[jb, jk + 1, :] * z_q[jk, :]
        )


# ===================================================================
# Reference implementations (scalar loops)
# ===================================================================

def compute_expl_rho_exner_ref(
    p_nh_prog_nnow_rho,
    p_nh_diag_exner_pr,
    p_nh_diag_theta_v_ic,
    p_nh_diag_ddt_exner_phy,
    p_nh_metrics_inv_ddqz_z_full,
    p_nh_metrics_deepatmo_divzU_mc,
    p_nh_metrics_deepatmo_divzL_mc,
    z_flxdiv_mass,
    z_flxdiv_theta,
    z_contr_w_fl_l,
    z_beta,
    z_rho_expl,
    z_exner_expl,
    dtime, jb, _nproma, _nlev,
):
    for jk in range(_nlev):
        for jc in range(_nproma):
            z_rho_expl[jk, jc] = (
                p_nh_prog_nnow_rho[jb, jk, jc]
                - dtime * p_nh_metrics_inv_ddqz_z_full[jb, jk, jc]
                * (z_flxdiv_mass[jk, jc]
                   + z_contr_w_fl_l[jk, jc]     * p_nh_metrics_deepatmo_divzU_mc[jk]
                   - z_contr_w_fl_l[jk + 1, jc] * p_nh_metrics_deepatmo_divzL_mc[jk])
            )

            z_exner_expl[jk, jc] = (
                p_nh_diag_exner_pr[jb, jk, jc]
                - z_beta[jk, jc]
                * (z_flxdiv_theta[jk, jc]
                   + p_nh_diag_theta_v_ic[jb, jk, jc]     * z_contr_w_fl_l[jk, jc]
                     * p_nh_metrics_deepatmo_divzU_mc[jk]
                   - p_nh_diag_theta_v_ic[jb, jk + 1, jc] * z_contr_w_fl_l[jk + 1, jc]
                     * p_nh_metrics_deepatmo_divzL_mc[jk])
                + dtime * p_nh_diag_ddt_exner_phy[jb, jk, jc]
            )


def solve_tridiag_w_ref(
    p_nh_metrics_vwind_impl_wgt,
    p_nh_diag_theta_v_ic,
    p_nh_metrics_ddqz_z_half,
    p_nh_metrics_deepatmo_divzU_mc,
    p_nh_metrics_deepatmo_divzL_mc,
    z_beta, z_alpha, z_q, z_w_expl, z_exner_expl,
    p_nh_prog_nnew_w,
    dtime, cpd, jb, _nproma, _nlev,
):
    # Forward sweep
    for jk in range(1, _nlev):
        for jc in range(_nproma):
            z_gamma = (dtime * cpd
                       * p_nh_metrics_vwind_impl_wgt[jb, jc]
                       * p_nh_diag_theta_v_ic[jb, jk, jc]
                       / p_nh_metrics_ddqz_z_half[jb, jk, jc])

            z_a = (-z_gamma
                   * z_beta[jk - 1, jc]
                   * z_alpha[jk - 1, jc]
                   * p_nh_metrics_deepatmo_divzU_mc[jk - 1])

            z_c = (-z_gamma
                   * z_beta[jk, jc]
                   * z_alpha[jk + 1, jc]
                   * p_nh_metrics_deepatmo_divzL_mc[jk])

            z_b = (1.0
                   + z_gamma * z_alpha[jk, jc]
                   * (z_beta[jk - 1, jc] * p_nh_metrics_deepatmo_divzL_mc[jk - 1]
                      + z_beta[jk, jc]   * p_nh_metrics_deepatmo_divzU_mc[jk]))

            z_g = 1.0 / (z_b + z_a * z_q[jk - 1, jc])
            z_q[jk, jc] = -z_c * z_g

            p_nh_prog_nnew_w[jb, jk, jc] = (
                z_w_expl[jk, jc]
                - z_gamma * (z_exner_expl[jk - 1, jc] - z_exner_expl[jk, jc])
            )
            p_nh_prog_nnew_w[jb, jk, jc] = (
                (p_nh_prog_nnew_w[jb, jk, jc]
                 - z_a * p_nh_prog_nnew_w[jb, jk - 1, jc])
                * z_g
            )

    # Backward sweep
    for jk in range(_nlev - 2, 0, -1):
        for jc in range(_nproma):
            p_nh_prog_nnew_w[jb, jk, jc] = (
                p_nh_prog_nnew_w[jb, jk, jc]
                + p_nh_prog_nnew_w[jb, jk + 1, jc] * z_q[jk, jc]
            )


# ===================================================================
# Data generation
# ===================================================================

def make_shared_data(NPROMA, NLEV, NBLKS, rng):
    """Create plausible random data.  All layouts are permuted:
         3D → (nblks, nlev/nlevp1, nproma)
         2D → (nlev/nlevp1, nproma)
         1D → (nlev,)
    """
    NLEVP1 = NLEV + 1

    # 3D (nblks, nlev, nproma)
    rho           = rng.uniform(0.8, 1.4, (NBLKS, NLEV, NPROMA))
    exner_pr      = rng.uniform(-0.02, 0.02, (NBLKS, NLEV, NPROMA))
    ddt_exner_phy = rng.uniform(-1e-5, 1e-5, (NBLKS, NLEV, NPROMA))
    inv_ddqz_full = rng.uniform(0.001, 0.02, (NBLKS, NLEV, NPROMA))

    # 3D (nblks, nlevp1, nproma)
    theta_v_ic   = rng.uniform(280.0, 320.0, (NBLKS, NLEVP1, NPROMA))
    ddqz_z_half  = rng.uniform(50.0, 500.0, (NBLKS, NLEVP1, NPROMA))

    # 2D (nblks, nproma)  — vwind_impl_wgt
    vwind_impl_wgt = rng.uniform(0.4, 0.6, (NBLKS, NPROMA))

    # 1D (nlev,)
    divzU = rng.uniform(0.99, 1.01, (NLEV,))
    divzL = rng.uniform(0.99, 1.01, (NLEV,))

    # 2D block-local (nlev, nproma)
    flxdiv_mass  = rng.uniform(-1e-3, 1e-3, (NLEV, NPROMA))
    flxdiv_theta = rng.uniform(-1e-3, 1e-3, (NLEV, NPROMA))
    z_beta       = rng.uniform(1e-6, 1e-4, (NLEV, NPROMA))

    # 2D block-local (nlevp1, nproma)
    contr_w_fl_l = rng.uniform(-0.5, 0.5, (NLEVP1, NPROMA))
    z_w_expl     = rng.uniform(-2.0, 2.0, (NLEVP1, NPROMA))

    # z_alpha: (nlevp1, nproma), last level = 0
    z_alpha = rng.uniform(1e3, 1e5, (NLEVP1, NPROMA))
    z_alpha[NLEVP1 - 1, :] = 0.0

    # z_q: (nlev, nproma), first level = 0
    z_q = np.zeros((NLEV, NPROMA), dtype=np.float64)

    # w: (nblks, nlevp1, nproma)
    w = np.zeros((NBLKS, NLEVP1, NPROMA), dtype=np.float64)
    # Lower BC at jk=NLEV (0-based last half-level)
    w[:, NLEV, :] = rng.uniform(-0.1, 0.1, (NBLKS, NPROMA))
    # Upper BC at jk=0 stays 0 (rigid lid)

    return dict(
        rho=rho, exner_pr=exner_pr, ddt_exner_phy=ddt_exner_phy,
        inv_ddqz_full=inv_ddqz_full, theta_v_ic=theta_v_ic,
        ddqz_z_half=ddqz_z_half, vwind_impl_wgt=vwind_impl_wgt,
        divzU=divzU, divzL=divzL,
        flxdiv_mass=flxdiv_mass, flxdiv_theta=flxdiv_theta,
        z_beta=z_beta, contr_w_fl_l=contr_w_fl_l,
        z_w_expl=z_w_expl, z_alpha=z_alpha, z_q=z_q, w=w,
    )


# ===================================================================
# Tests
# ===================================================================

def test_expl_rho_exner():
    NPROMA, NLEV, NBLKS = 32, 60, 4
    NLEVP1 = NLEV + 1
    JB     = 1
    DTIME  = 10.0

    rng  = np.random.default_rng(42)
    data = make_shared_data(NPROMA, NLEV, NBLKS, rng)

    # --- Reference ---
    ref_rho   = np.zeros((NLEV, NPROMA))
    ref_exner = np.zeros((NLEV, NPROMA))
    compute_expl_rho_exner_ref(
        data['rho'], data['exner_pr'], data['theta_v_ic'],
        data['ddt_exner_phy'], data['inv_ddqz_full'],
        data['divzU'], data['divzL'],
        data['flxdiv_mass'], data['flxdiv_theta'],
        data['contr_w_fl_l'], data['z_beta'],
        ref_rho, ref_exner,
        DTIME, JB, NPROMA, NLEV,
    )

    # --- DaCe ---
    dace_rho   = np.zeros((NLEV, NPROMA))
    dace_exner = np.zeros((NLEV, NPROMA))
    compute_expl_rho_exner(
        data['rho'], data['exner_pr'], data['theta_v_ic'],
        data['ddt_exner_phy'], data['inv_ddqz_full'],
        data['divzU'], data['divzL'],
        data['flxdiv_mass'], data['flxdiv_theta'],
        data['contr_w_fl_l'], data['z_beta'],
        dace_rho, dace_exner,
        DTIME, JB,
        nproma=NPROMA, nlev=NLEV, nlevp1=NLEVP1, nblks=NBLKS,
    )

    err_rho   = np.max(np.abs(dace_rho - ref_rho))
    err_exner = np.max(np.abs(dace_exner - ref_exner))
    print(f"[expl_rho_exner]  max|rho err| = {err_rho:.2e}   max|exner err| = {err_exner:.2e}")
    assert np.any(ref_rho != 0.0),   "Reference rho all zeros"
    assert np.any(ref_exner != 0.0), "Reference exner all zeros"
    assert err_rho   < 1e-14, f"rho mismatch: {err_rho}"
    assert err_exner < 1e-14, f"exner mismatch: {err_exner}"
    print("[expl_rho_exner]  PASSED ✓")


def test_tridiag_w():
    NPROMA, NLEV, NBLKS = 32, 60, 4
    NLEVP1 = NLEV + 1
    JB     = 1
    DTIME  = 10.0
    CPD    = 1004.64

    rng  = np.random.default_rng(42)
    data = make_shared_data(NPROMA, NLEV, NBLKS, rng)

    # We need z_exner_expl filled first (compute_expl_rho_exner populates it).
    # For the Thomas solver test, just use random data directly.
    z_exner_expl = rng.uniform(-0.01, 0.01, (NLEV, NPROMA))

    # --- Reference ---
    z_q_ref = data['z_q'].copy()
    w_ref   = data['w'].copy()
    solve_tridiag_w_ref(
        data['vwind_impl_wgt'], data['theta_v_ic'],
        data['ddqz_z_half'], data['divzU'], data['divzL'],
        data['z_beta'].copy(), data['z_alpha'].copy(),
        z_q_ref, data['z_w_expl'].copy(), z_exner_expl.copy(),
        w_ref,
        DTIME, CPD, JB, NPROMA, NLEV,
    )

    # --- DaCe ---
    z_q_dace = data['z_q'].copy()
    w_dace   = data['w'].copy()
    solve_tridiag_w(
        data['vwind_impl_wgt'], data['theta_v_ic'],
        data['ddqz_z_half'], data['divzU'], data['divzL'],
        data['z_beta'].copy(), data['z_alpha'].copy(),
        z_q_dace, data['z_w_expl'].copy(), z_exner_expl.copy(),
        w_dace,
        DTIME, CPD, JB,
        nproma=NPROMA, nlev=NLEV, nlevp1=NLEVP1, nblks=NBLKS,
    )

    err_w = np.max(np.abs(w_dace[JB, :, :] - w_ref[JB, :, :]))
    err_q = np.max(np.abs(z_q_dace - z_q_ref))
    print(f"[tridiag_w]  max|w err| = {err_w:.2e}   max|q err| = {err_q:.2e}")
    assert np.any(w_ref[JB, 1:-1, :] != 0.0), "Reference w all zeros in interior"
    assert err_w < 1e-12, f"w mismatch: {err_w}"
    assert err_q < 1e-12, f"q mismatch: {err_q}"
    print("[tridiag_w]  PASSED ✓")


if __name__ == "__main__":
    test_expl_rho_exner()
    print()
    test_tridiag_w()
    print("\nAll tests passed ✓")
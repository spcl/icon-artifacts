"""
DaCe Python frontend translation of the explicit density (rho) and Exner
pressure computation at the top level (jk=0, 0-based) from ICON's
mo_solve_nonhydro.f90.

Array layout convention (permuted from Fortran):
  Fortran (jc, jk, jb) → Python (jb, jk, jc)
  Fortran (jc, jk)     → Python (jk, jc)
  Fortran (jk)          → Python (jk)

All indices are 0-based.  nproma, nlev are passed as explicit integer
parameters (DaCe symbols resolved at call time).
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


@dace.program
def compute_expl_rho_exner_top(
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
    # --- Scalar parameters ---
    dtime:  dace.float64,
    jb:     dace.int32,
):
    """
    Compute the explicit parts of density and Exner pressure at the top
    level (jk=0, 0-based).  Operates on a single block jb.

    Fortran original:
      jk=1 (1-based) corresponds to jk=0 (0-based) here.
      jc loop over i_startidx..i_endidx is the full nproma range [:].
    """

    # ----- z_rho_expl at top level (jk=0) -----
    z_rho_expl[0, :] = (
        p_nh_prog_nnow_rho[jb, 0, :]
        - dtime * p_nh_metrics_inv_ddqz_z_full[jb, 0, :]
        * (z_flxdiv_mass[0, :]
           + z_contr_w_fl_l[0, :] * p_nh_metrics_deepatmo_divzU_mc[0]
           - z_contr_w_fl_l[1, :] * p_nh_metrics_deepatmo_divzL_mc[0])
    )

    # ----- z_exner_expl at top level (jk=0) -----
    z_exner_expl[0, :] = (
        p_nh_diag_exner_pr[jb, 0, :]
        - z_beta[0, :]
        * (z_flxdiv_theta[0, :]
           + p_nh_diag_theta_v_ic[jb, 0, :] * z_contr_w_fl_l[0, :]
             * p_nh_metrics_deepatmo_divzU_mc[0]
           - p_nh_diag_theta_v_ic[jb, 1, :] * z_contr_w_fl_l[1, :]
             * p_nh_metrics_deepatmo_divzL_mc[0])
        + dtime * p_nh_diag_ddt_exner_phy[jb, 0, :]
    )


# ---------------------------------------------------------------------------
# Pure-NumPy scalar-loop reference (matches Fortran loop-for-loop)
# ---------------------------------------------------------------------------
def compute_expl_rho_exner_top_ref(
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
    dtime, jb, _nproma,
):
    """Scalar-loop reference matching the original Fortran exactly."""
    for jc in range(_nproma):
        z_rho_expl[0, jc] = (
            p_nh_prog_nnow_rho[jb, 0, jc]
            - dtime * p_nh_metrics_inv_ddqz_z_full[jb, 0, jc]
            * (z_flxdiv_mass[0, jc]
               + z_contr_w_fl_l[0, jc] * p_nh_metrics_deepatmo_divzU_mc[0]
               - z_contr_w_fl_l[1, jc] * p_nh_metrics_deepatmo_divzL_mc[0])
        )

        z_exner_expl[0, jc] = (
            p_nh_diag_exner_pr[jb, 0, jc]
            - z_beta[0, jc]
            * (z_flxdiv_theta[0, jc]
               + p_nh_diag_theta_v_ic[jb, 0, jc] * z_contr_w_fl_l[0, jc]
                 * p_nh_metrics_deepatmo_divzU_mc[0]
               - p_nh_diag_theta_v_ic[jb, 1, jc] * z_contr_w_fl_l[1, jc]
                 * p_nh_metrics_deepatmo_divzL_mc[0])
            + dtime * p_nh_diag_ddt_exner_phy[jb, 0, jc]
        )


# ---------------------------------------------------------------------------
# Data generation
# ---------------------------------------------------------------------------
def make_test_data(NPROMA: int, NLEV: int, NBLKS: int, rng):
    """
    Create plausible random data for verification.
    All 3D arrays use layout (nblks, nlev or nlevp1, nproma).
    All 2D block-local arrays use layout (nlev or nlevp1, nproma).
    1D metric arrays use (nlev,).

    No indirect accesses (neighbor lists) in this snippet, so none
    are generated here.
    """
    NLEVP1 = NLEV + 1

    # --- 3D fields: (nblks, nlev, nproma) ---
    p_nh_prog_nnow_rho           = rng.uniform(0.8, 1.4, (NBLKS, NLEV, NPROMA))
    p_nh_diag_exner_pr           = rng.uniform(-0.02, 0.02, (NBLKS, NLEV, NPROMA))
    p_nh_diag_ddt_exner_phy      = rng.uniform(-1e-5, 1e-5, (NBLKS, NLEV, NPROMA))
    p_nh_metrics_inv_ddqz_z_full = rng.uniform(0.001, 0.02, (NBLKS, NLEV, NPROMA))

    # --- 3D fields: (nblks, nlevp1, nproma) ---
    p_nh_diag_theta_v_ic = rng.uniform(280.0, 320.0, (NBLKS, NLEVP1, NPROMA))

    # --- 1D metric arrays: (nlev,) ---
    p_nh_metrics_deepatmo_divzU_mc = rng.uniform(0.99, 1.01, (NLEV,))
    p_nh_metrics_deepatmo_divzL_mc = rng.uniform(0.99, 1.01, (NLEV,))

    # --- 2D block-local arrays: (nlev, nproma) ---
    z_flxdiv_mass  = rng.uniform(-1e-3, 1e-3, (NLEV, NPROMA))
    z_flxdiv_theta = rng.uniform(-1e-3, 1e-3, (NLEV, NPROMA))
    z_beta         = rng.uniform(1e-6, 1e-4, (NLEV, NPROMA))

    # --- 2D block-local: (nlevp1, nproma) ---
    z_contr_w_fl_l = rng.uniform(-0.5, 0.5, (NLEVP1, NPROMA))

    # --- Output arrays: (nlev, nproma) ---
    z_rho_expl   = np.zeros((NLEV, NPROMA), dtype=np.float64)
    z_exner_expl = np.zeros((NLEV, NPROMA), dtype=np.float64)

    return dict(
        p_nh_prog_nnow_rho=p_nh_prog_nnow_rho,
        p_nh_diag_exner_pr=p_nh_diag_exner_pr,
        p_nh_diag_theta_v_ic=p_nh_diag_theta_v_ic,
        p_nh_diag_ddt_exner_phy=p_nh_diag_ddt_exner_phy,
        p_nh_metrics_inv_ddqz_z_full=p_nh_metrics_inv_ddqz_z_full,
        p_nh_metrics_deepatmo_divzU_mc=p_nh_metrics_deepatmo_divzU_mc,
        p_nh_metrics_deepatmo_divzL_mc=p_nh_metrics_deepatmo_divzL_mc,
        z_flxdiv_mass=z_flxdiv_mass,
        z_flxdiv_theta=z_flxdiv_theta,
        z_contr_w_fl_l=z_contr_w_fl_l,
        z_beta=z_beta,
        z_rho_expl=z_rho_expl,
        z_exner_expl=z_exner_expl,
    )


# ---------------------------------------------------------------------------
# Test harness
# ---------------------------------------------------------------------------
def test_expl_rho_exner_top():
    """Verify the DaCe program against the scalar-loop reference."""
    NPROMA = 32
    NLEV   = 60
    NLEVP1 = NLEV + 1
    NBLKS  = 4
    JB     = 1          # test block index
    DTIME  = 10.0       # seconds

    rng = np.random.default_rng(123)
    data = make_test_data(NPROMA, NLEV, NBLKS, rng)

    # ---- Reference ----
    ref_rho   = data['z_rho_expl'].copy()
    ref_exner = data['z_exner_expl'].copy()
    compute_expl_rho_exner_top_ref(
        data['p_nh_prog_nnow_rho'],
        data['p_nh_diag_exner_pr'],
        data['p_nh_diag_theta_v_ic'],
        data['p_nh_diag_ddt_exner_phy'],
        data['p_nh_metrics_inv_ddqz_z_full'],
        data['p_nh_metrics_deepatmo_divzU_mc'],
        data['p_nh_metrics_deepatmo_divzL_mc'],
        data['z_flxdiv_mass'],
        data['z_flxdiv_theta'],
        data['z_contr_w_fl_l'],
        data['z_beta'],
        ref_rho,
        ref_exner,
        DTIME, JB, NPROMA,
    )

    # ---- DaCe ----
    dace_rho   = data['z_rho_expl'].copy()
    dace_exner = data['z_exner_expl'].copy()
    compute_expl_rho_exner_top(
        data['p_nh_prog_nnow_rho'],
        data['p_nh_diag_exner_pr'],
        data['p_nh_diag_theta_v_ic'],
        data['p_nh_diag_ddt_exner_phy'],
        data['p_nh_metrics_inv_ddqz_z_full'],
        data['p_nh_metrics_deepatmo_divzU_mc'],
        data['p_nh_metrics_deepatmo_divzL_mc'],
        data['z_flxdiv_mass'],
        data['z_flxdiv_theta'],
        data['z_contr_w_fl_l'],
        data['z_beta'],
        dace_rho,
        dace_exner,
        DTIME, JB,
        nproma=NPROMA, nlev=NLEV, nlevp1=NLEVP1, nblks=NBLKS,
    )

    # ---- Compare ----
    err_rho   = np.max(np.abs(dace_rho[0, :] - ref_rho[0, :]))
    err_exner = np.max(np.abs(dace_exner[0, :] - ref_exner[0, :]))
    print(f"Max |rho_dace - rho_ref|     (jk=0) = {err_rho:.2e}")
    print(f"Max |exner_dace - exner_ref| (jk=0) = {err_exner:.2e}")

    # Sanity: check that we actually computed something nonzero
    assert np.any(ref_rho[0, :] != 0.0), "Reference rho is all zeros"
    assert np.any(ref_exner[0, :] != 0.0), "Reference exner is all zeros"

    assert err_rho   < 1e-14, f"rho mismatch: {err_rho}"
    assert err_exner < 1e-14, f"exner mismatch: {err_exner}"
    print("PASSED ✓")


if __name__ == "__main__":
    test_expl_rho_exner_top()
#include "shared_struct_defs.h"
#include <dace/dace.h>

#ifndef __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_0_ISTEP_1__
struct velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t; // Forward
                                                              // declaration.

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *
__dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state,
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

#endif // __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_0_ISTEP_1__
#include "shared_struct_defs.h"
#include <dace/dace.h>

#ifndef __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_1_ISTEP_1__
struct velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t; // Forward
                                                              // declaration.

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *
__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state,
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

#endif // __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_1_ISTEP_1__
#include "shared_struct_defs.h"
#include <dace/dace.h>

#ifndef __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_0_ISTEP_2__
struct velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t; // Forward
                                                              // declaration.

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *
__dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);
DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state,
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);

#endif // __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_0_ISTEP_2__
#include "shared_struct_defs.h"
#include <dace/dace.h>

#ifndef __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_1_ISTEP_2__
struct velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t; // Forward
                                                              // declaration.

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *
__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state,
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

#endif // __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_1_ISTEP_2__

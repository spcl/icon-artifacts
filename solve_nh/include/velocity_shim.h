#ifndef __VELOCITY_SHIM_H__
#define __VELOCITY_SHIM_H__

#include "shared_struct_defs.h"
#include <dace/dace.h>

#if defined(GPU)

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_kin_hor_e_d_2_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_vt_ie_d_2_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_2_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s,
    int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s,
    int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_kin_hor_e_d_2_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_vt_ie_d_2_s, int __f2dace_A_z_w_concorr_me_d_0_s,
    int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_A_z_w_concorr_me_d_2_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_kin_hor_e_d_2_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_vt_ie_d_2_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_2_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s,
    int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s,
    int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_kin_hor_e_d_2_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_vt_ie_d_2_s, int __f2dace_A_z_w_concorr_me_d_0_s,
    int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_A_z_w_concorr_me_d_2_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s,
    int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_2(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_kin_hor_e_d_2_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_vt_ie_d_2_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_2_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s,
    int __f2dace_OA_z_vt_ie_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_kin_hor_e_d_2_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_vt_ie_d_2_s, int __f2dace_A_z_w_concorr_me_d_0_s,
    int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_A_z_w_concorr_me_d_2_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s,
    int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    global_data_type *global_data, t_nh_diag *p_diag, t_int_state *p_int,
    t_nh_metrics *p_metrics, t_patch *p_patch, t_nh_prog *p_prog,
    double *z_kin_hor_e, double *z_vt_ie, double *z_w_concorr_me,
    int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s,
    int __f2dace_A_z_kin_hor_e_d_2_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_vt_ie_d_2_s,
    int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s,
    int __f2dace_A_z_w_concorr_me_d_2_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_kin_hor_e_d_2_s,
    int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s,
    int __f2dace_A_z_vt_ie_d_2_s, int __f2dace_A_z_w_concorr_me_d_0_s,
    int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_A_z_w_concorr_me_d_2_s,
    int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s,
    int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

#else

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
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
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s,
    int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s,
    int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s,
    int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
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
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s,
    int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s,
    int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s,
    int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s,
    double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only,
    int ntnd);

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_2(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
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
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s,
    int __f2dace_OA_z_vt_ie_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

DACE_EXPORTED int
__dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(void *__state);
DACE_EXPORTED void *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
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
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    void *__state, global_data_type *global_data, t_nh_diag *p_diag,
    t_int_state *p_int, t_nh_metrics *p_metrics, t_patch *p_patch,
    t_nh_prog *p_prog, double *z_kin_hor_e, double *z_vt_ie,
    double *z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s,
    int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s,
    int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s,
    int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s,
    int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s,
    int __f2dace_OA_z_vt_ie_d_2_s, double dt_linintp_ubc, double dtime,
    int istep, int ldeepatmo, int lvn_only, int ntnd);

static void velocity_tendencies(
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
    int istep, int ldeepatmo, int lvn_only, int ntnd) {

  if (lvn_only == 1 && istep == 1) {
    auto *h = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
        global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s,
        __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s,
        __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s,
        dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
        h, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s,
        __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s,
        __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s,
        dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    int err = __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(h);
  } else if (lvn_only == 0 && istep == 1) {
    auto *h = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
        global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s,
        __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s,
        __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s,
        dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
        h, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s,
        __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s,
        __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s,
        dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    int err = __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(h);
  } else if (lvn_only == 1 && istep == 2) {
    auto *h = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
        global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, dt_linintp_ubc, dtime, istep, ldeepatmo,
        lvn_only, ntnd);
    __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
        h, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, dt_linintp_ubc, dtime, istep, ldeepatmo,
        lvn_only, ntnd);
    int err = __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(h);
  } else if (lvn_only == 0 && istep == 2) {
    auto *h = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
        global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, dt_linintp_ubc, dtime, istep, ldeepatmo,
        lvn_only, ntnd);
    __program_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
        h, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s,
        __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s,
        __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s,
        __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s,
        __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s,
        __f2dace_OA_z_vt_ie_d_2_s, dt_linintp_ubc, dtime, istep, ldeepatmo,
        lvn_only, ntnd);
    int err = __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_2(h);
  } else {
    throw std::runtime_error("Law of Logic and Mathematics violated");
  }
}

#endif

#endif // __VELOCITY_SHIM_H__
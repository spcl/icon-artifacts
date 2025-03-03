
#ifndef __DACE_CODEGEN_VELOCITY_TENDENCIES__
#define __DACE_CODEGEN_VELOCITY_TENDENCIES__

#include <dace/dace.h>


struct t_grid_vertices {
    int* cell_blk = {};
int* cell_idx = {};
int* edge_blk = {};
int* edge_idx = {};
int* end_blk = {};
int* end_block = {};
int* end_index = {};
int* start_blk = {};
int* start_block = {};
int* start_index = {};
};


struct global_data_type {
    int lextra_diffu = {};
int* nflatlev = {};
int* nrdmax = {};
int timer_intp = {};
int timer_solve_nh_veltend = {};
int timers_level = {};
};


struct t_nh_prog {
    int __f2dace_SA_vn_d_0_s_76 = {};
int __f2dace_SA_vn_d_1_s_77 = {};
int __f2dace_SA_vn_d_2_s_78 = {};
int __f2dace_SA_w_d_0_s_73 = {};
int __f2dace_SA_w_d_1_s_74 = {};
int __f2dace_SA_w_d_2_s_75 = {};
int __f2dace_SOA_vn_d_0_s_76 = {};
int __f2dace_SOA_vn_d_1_s_77 = {};
int __f2dace_SOA_vn_d_2_s_78 = {};
int __f2dace_SOA_w_d_0_s_73 = {};
int __f2dace_SOA_w_d_1_s_74 = {};
int __f2dace_SOA_w_d_2_s_75 = {};
double* vn = {};
double* w = {};
};


struct t_grid_domain_decomp_info {
    int* owner_mask = {};
};


struct t_grid_cells {
    int __f2dace_SA_area_d_0_s_2 = {};
int __f2dace_SA_area_d_1_s_3 = {};
int __f2dace_SOA_area_d_0_s_2 = {};
int __f2dace_SOA_area_d_1_s_3 = {};
double* area = {};
t_grid_domain_decomp_info* decomp_info = {};
int* edge_blk = {};
int* edge_idx = {};
int* end_block = {};
int* end_index = {};
int* neighbor_blk = {};
int* neighbor_idx = {};
int* start_block = {};
int* start_index = {};
};


struct t_grid_edges {
    double* area_edge = {};
int* cell_blk = {};
int* cell_idx = {};
int* end_block = {};
int* end_index = {};
double* f_e = {};
double* fn_e = {};
double* ft_e = {};
double* inv_dual_edge_length = {};
double* inv_primal_edge_length = {};
int* quad_blk = {};
int* quad_idx = {};
int* start_block = {};
int* start_index = {};
double* tangent_orientation = {};
int* vertex_blk = {};
int* vertex_idx = {};
};


struct t_patch {
    t_grid_cells* cells = {};
t_grid_edges* edges = {};
t_grid_vertices* verts = {};
};


struct t_nh_diag {
    int __f2dace_SA_ddt_vn_apc_pc_d_0_s_88 = {};
int __f2dace_SA_ddt_vn_apc_pc_d_1_s_89 = {};
int __f2dace_SA_ddt_vn_apc_pc_d_2_s_90 = {};
int __f2dace_SA_ddt_vn_apc_pc_d_3_s_91 = {};
int __f2dace_SA_ddt_w_adv_pc_d_0_s_92 = {};
int __f2dace_SA_ddt_w_adv_pc_d_1_s_93 = {};
int __f2dace_SA_ddt_w_adv_pc_d_2_s_94 = {};
int __f2dace_SA_ddt_w_adv_pc_d_3_s_95 = {};
int __f2dace_SA_vn_ie_d_0_s_82 = {};
int __f2dace_SA_vn_ie_d_1_s_83 = {};
int __f2dace_SA_vn_ie_d_2_s_84 = {};
int __f2dace_SA_vt_d_0_s_79 = {};
int __f2dace_SA_vt_d_1_s_80 = {};
int __f2dace_SA_vt_d_2_s_81 = {};
int __f2dace_SA_w_concorr_c_d_0_s_85 = {};
int __f2dace_SA_w_concorr_c_d_1_s_86 = {};
int __f2dace_SA_w_concorr_c_d_2_s_87 = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_88 = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_89 = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_90 = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_91 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_0_s_92 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_1_s_93 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_2_s_94 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_3_s_95 = {};
int __f2dace_SOA_vn_ie_d_0_s_82 = {};
int __f2dace_SOA_vn_ie_d_1_s_83 = {};
int __f2dace_SOA_vn_ie_d_2_s_84 = {};
int __f2dace_SOA_vt_d_0_s_79 = {};
int __f2dace_SOA_vt_d_1_s_80 = {};
int __f2dace_SOA_vt_d_2_s_81 = {};
int __f2dace_SOA_w_concorr_c_d_0_s_85 = {};
int __f2dace_SOA_w_concorr_c_d_1_s_86 = {};
int __f2dace_SOA_w_concorr_c_d_2_s_87 = {};
double* ddt_vn_apc_pc = {};
double* ddt_w_adv_pc = {};
double max_vcfl_dyn = {};
double* vn_ie = {};
double* vt = {};
double* w_concorr_c = {};
};


struct t_nh_metrics {
    int __f2dace_SA_coeff1_dwdz_d_0_s_120 = {};
int __f2dace_SA_coeff1_dwdz_d_1_s_121 = {};
int __f2dace_SA_coeff1_dwdz_d_2_s_122 = {};
int __f2dace_SA_coeff2_dwdz_d_0_s_123 = {};
int __f2dace_SA_coeff2_dwdz_d_1_s_124 = {};
int __f2dace_SA_coeff2_dwdz_d_2_s_125 = {};
int __f2dace_SA_coeff_gradekin_d_0_s_117 = {};
int __f2dace_SA_coeff_gradekin_d_1_s_118 = {};
int __f2dace_SA_coeff_gradekin_d_2_s_119 = {};
int __f2dace_SA_ddqz_z_full_e_d_0_s_102 = {};
int __f2dace_SA_ddqz_z_full_e_d_1_s_103 = {};
int __f2dace_SA_ddqz_z_full_e_d_2_s_104 = {};
int __f2dace_SA_ddqz_z_half_d_0_s_105 = {};
int __f2dace_SA_ddqz_z_half_d_1_s_106 = {};
int __f2dace_SA_ddqz_z_half_d_2_s_107 = {};
int __f2dace_SA_ddxn_z_full_d_0_s_96 = {};
int __f2dace_SA_ddxn_z_full_d_1_s_97 = {};
int __f2dace_SA_ddxn_z_full_d_2_s_98 = {};
int __f2dace_SA_ddxt_z_full_d_0_s_99 = {};
int __f2dace_SA_ddxt_z_full_d_1_s_100 = {};
int __f2dace_SA_ddxt_z_full_d_2_s_101 = {};
int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_128 = {};
int __f2dace_SA_deepatmo_gradh_mc_d_0_s_126 = {};
int __f2dace_SA_deepatmo_invr_ifc_d_0_s_129 = {};
int __f2dace_SA_deepatmo_invr_mc_d_0_s_127 = {};
int __f2dace_SA_wgtfac_c_d_0_s_108 = {};
int __f2dace_SA_wgtfac_c_d_1_s_109 = {};
int __f2dace_SA_wgtfac_c_d_2_s_110 = {};
int __f2dace_SA_wgtfac_e_d_0_s_111 = {};
int __f2dace_SA_wgtfac_e_d_1_s_112 = {};
int __f2dace_SA_wgtfac_e_d_2_s_113 = {};
int __f2dace_SA_wgtfacq_e_d_0_s_114 = {};
int __f2dace_SA_wgtfacq_e_d_1_s_115 = {};
int __f2dace_SA_wgtfacq_e_d_2_s_116 = {};
int __f2dace_SOA_coeff1_dwdz_d_0_s_120 = {};
int __f2dace_SOA_coeff1_dwdz_d_1_s_121 = {};
int __f2dace_SOA_coeff1_dwdz_d_2_s_122 = {};
int __f2dace_SOA_coeff2_dwdz_d_0_s_123 = {};
int __f2dace_SOA_coeff2_dwdz_d_1_s_124 = {};
int __f2dace_SOA_coeff2_dwdz_d_2_s_125 = {};
int __f2dace_SOA_coeff_gradekin_d_0_s_117 = {};
int __f2dace_SOA_coeff_gradekin_d_1_s_118 = {};
int __f2dace_SOA_coeff_gradekin_d_2_s_119 = {};
int __f2dace_SOA_ddqz_z_full_e_d_0_s_102 = {};
int __f2dace_SOA_ddqz_z_full_e_d_1_s_103 = {};
int __f2dace_SOA_ddqz_z_full_e_d_2_s_104 = {};
int __f2dace_SOA_ddqz_z_half_d_0_s_105 = {};
int __f2dace_SOA_ddqz_z_half_d_1_s_106 = {};
int __f2dace_SOA_ddqz_z_half_d_2_s_107 = {};
int __f2dace_SOA_ddxn_z_full_d_0_s_96 = {};
int __f2dace_SOA_ddxn_z_full_d_1_s_97 = {};
int __f2dace_SOA_ddxn_z_full_d_2_s_98 = {};
int __f2dace_SOA_ddxt_z_full_d_0_s_99 = {};
int __f2dace_SOA_ddxt_z_full_d_1_s_100 = {};
int __f2dace_SOA_ddxt_z_full_d_2_s_101 = {};
int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_128 = {};
int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_126 = {};
int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_129 = {};
int __f2dace_SOA_deepatmo_invr_mc_d_0_s_127 = {};
int __f2dace_SOA_wgtfac_c_d_0_s_108 = {};
int __f2dace_SOA_wgtfac_c_d_1_s_109 = {};
int __f2dace_SOA_wgtfac_c_d_2_s_110 = {};
int __f2dace_SOA_wgtfac_e_d_0_s_111 = {};
int __f2dace_SOA_wgtfac_e_d_1_s_112 = {};
int __f2dace_SOA_wgtfac_e_d_2_s_113 = {};
int __f2dace_SOA_wgtfacq_e_d_0_s_114 = {};
int __f2dace_SOA_wgtfacq_e_d_1_s_115 = {};
int __f2dace_SOA_wgtfacq_e_d_2_s_116 = {};
double* coeff1_dwdz = {};
double* coeff2_dwdz = {};
double* coeff_gradekin = {};
double* ddqz_z_full_e = {};
double* ddqz_z_half = {};
double* ddxn_z_full = {};
double* ddxt_z_full = {};
double* deepatmo_gradh_ifc = {};
double* deepatmo_gradh_mc = {};
double* deepatmo_invr_ifc = {};
double* deepatmo_invr_mc = {};
double* wgtfac_c = {};
double* wgtfac_e = {};
double* wgtfacq_e = {};
};


struct t_int_state {
    double* c_lin_e = {};
double* cells_aw_verts = {};
double* e_bln_c_s = {};
double* geofac_grdiv = {};
double* geofac_n2s = {};
double* geofac_rot = {};
double* rbf_vec_coeff_e = {};
};




struct velocity_tendencies_state_t;  // Forward declaration.

DACE_EXPORTED velocity_tendencies_state_t *__dace_init_velocity_tendencies(global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_151, int __f2dace_A_z_kin_hor_e_d_1_s_152, int __f2dace_A_z_vt_ie_d_0_s_154, int __f2dace_A_z_vt_ie_d_1_s_155, int __f2dace_A_z_w_concorr_me_d_0_s_148, int __f2dace_A_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_kin_hor_e_d_0_s_151, int __f2dace_OA_z_kin_hor_e_d_1_s_152, int __f2dace_OA_z_kin_hor_e_d_2_s_153, int __f2dace_OA_z_vt_ie_d_0_s_154, int __f2dace_OA_z_vt_ie_d_1_s_155, int __f2dace_OA_z_vt_ie_d_2_s_156, int __f2dace_OA_z_w_concorr_me_d_0_s_148, int __f2dace_OA_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_w_concorr_me_d_2_s_150, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED int __dace_exit_velocity_tendencies(velocity_tendencies_state_t *__state);
DACE_EXPORTED void __program_velocity_tendencies(velocity_tendencies_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_151, int __f2dace_A_z_kin_hor_e_d_1_s_152, int __f2dace_A_z_vt_ie_d_0_s_154, int __f2dace_A_z_vt_ie_d_1_s_155, int __f2dace_A_z_w_concorr_me_d_0_s_148, int __f2dace_A_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_kin_hor_e_d_0_s_151, int __f2dace_OA_z_kin_hor_e_d_1_s_152, int __f2dace_OA_z_kin_hor_e_d_2_s_153, int __f2dace_OA_z_vt_ie_d_0_s_154, int __f2dace_OA_z_vt_ie_d_1_s_155, int __f2dace_OA_z_vt_ie_d_2_s_156, int __f2dace_OA_z_w_concorr_me_d_0_s_148, int __f2dace_OA_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_w_concorr_me_d_2_s_150, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd);

#endif // __DACE_CODEGEN_VELOCITY_TENDENCIES__

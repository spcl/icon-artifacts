/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

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

struct t_int_state {
    double* c_lin_e = {};
    double* cells_aw_verts = {};
    double* e_bln_c_s = {};
    double* geofac_grdiv = {};
    double* geofac_n2s = {};
    double* geofac_rot = {};
    double* rbf_vec_coeff_e = {};
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

struct t_patch {
    t_grid_cells* cells = {};
    t_grid_edges* edges = {};
    t_grid_vertices* verts = {};
};

struct t_nh_metrics {
    int __f2dace_SA_coeff1_dwdz_d_0_s_126 = {};
    int __f2dace_SA_coeff1_dwdz_d_1_s_127 = {};
    int __f2dace_SA_coeff1_dwdz_d_2_s_128 = {};
    int __f2dace_SA_coeff2_dwdz_d_0_s_129 = {};
    int __f2dace_SA_coeff2_dwdz_d_1_s_130 = {};
    int __f2dace_SA_coeff2_dwdz_d_2_s_131 = {};
    int __f2dace_SA_coeff_gradekin_d_0_s_123 = {};
    int __f2dace_SA_coeff_gradekin_d_1_s_124 = {};
    int __f2dace_SA_coeff_gradekin_d_2_s_125 = {};
    int __f2dace_SA_ddqz_z_full_e_d_0_s_108 = {};
    int __f2dace_SA_ddqz_z_full_e_d_1_s_109 = {};
    int __f2dace_SA_ddqz_z_full_e_d_2_s_110 = {};
    int __f2dace_SA_ddqz_z_half_d_0_s_111 = {};
    int __f2dace_SA_ddqz_z_half_d_1_s_112 = {};
    int __f2dace_SA_ddqz_z_half_d_2_s_113 = {};
    int __f2dace_SA_ddxn_z_full_d_0_s_102 = {};
    int __f2dace_SA_ddxn_z_full_d_1_s_103 = {};
    int __f2dace_SA_ddxn_z_full_d_2_s_104 = {};
    int __f2dace_SA_ddxt_z_full_d_0_s_105 = {};
    int __f2dace_SA_ddxt_z_full_d_1_s_106 = {};
    int __f2dace_SA_ddxt_z_full_d_2_s_107 = {};
    int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_134 = {};
    int __f2dace_SA_deepatmo_gradh_mc_d_0_s_132 = {};
    int __f2dace_SA_deepatmo_invr_ifc_d_0_s_135 = {};
    int __f2dace_SA_deepatmo_invr_mc_d_0_s_133 = {};
    int __f2dace_SA_wgtfac_c_d_0_s_114 = {};
    int __f2dace_SA_wgtfac_c_d_1_s_115 = {};
    int __f2dace_SA_wgtfac_c_d_2_s_116 = {};
    int __f2dace_SA_wgtfac_e_d_0_s_117 = {};
    int __f2dace_SA_wgtfac_e_d_1_s_118 = {};
    int __f2dace_SA_wgtfac_e_d_2_s_119 = {};
    int __f2dace_SA_wgtfacq_e_d_0_s_120 = {};
    int __f2dace_SA_wgtfacq_e_d_1_s_121 = {};
    int __f2dace_SA_wgtfacq_e_d_2_s_122 = {};
    int __f2dace_SOA_coeff1_dwdz_d_0_s_126 = {};
    int __f2dace_SOA_coeff1_dwdz_d_1_s_127 = {};
    int __f2dace_SOA_coeff1_dwdz_d_2_s_128 = {};
    int __f2dace_SOA_coeff2_dwdz_d_0_s_129 = {};
    int __f2dace_SOA_coeff2_dwdz_d_1_s_130 = {};
    int __f2dace_SOA_coeff2_dwdz_d_2_s_131 = {};
    int __f2dace_SOA_coeff_gradekin_d_0_s_123 = {};
    int __f2dace_SOA_coeff_gradekin_d_1_s_124 = {};
    int __f2dace_SOA_coeff_gradekin_d_2_s_125 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_0_s_108 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_1_s_109 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_2_s_110 = {};
    int __f2dace_SOA_ddqz_z_half_d_0_s_111 = {};
    int __f2dace_SOA_ddqz_z_half_d_1_s_112 = {};
    int __f2dace_SOA_ddqz_z_half_d_2_s_113 = {};
    int __f2dace_SOA_ddxn_z_full_d_0_s_102 = {};
    int __f2dace_SOA_ddxn_z_full_d_1_s_103 = {};
    int __f2dace_SOA_ddxn_z_full_d_2_s_104 = {};
    int __f2dace_SOA_ddxt_z_full_d_0_s_105 = {};
    int __f2dace_SOA_ddxt_z_full_d_1_s_106 = {};
    int __f2dace_SOA_ddxt_z_full_d_2_s_107 = {};
    int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_134 = {};
    int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_132 = {};
    int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_135 = {};
    int __f2dace_SOA_deepatmo_invr_mc_d_0_s_133 = {};
    int __f2dace_SOA_wgtfac_c_d_0_s_114 = {};
    int __f2dace_SOA_wgtfac_c_d_1_s_115 = {};
    int __f2dace_SOA_wgtfac_c_d_2_s_116 = {};
    int __f2dace_SOA_wgtfac_e_d_0_s_117 = {};
    int __f2dace_SOA_wgtfac_e_d_1_s_118 = {};
    int __f2dace_SOA_wgtfac_e_d_2_s_119 = {};
    int __f2dace_SOA_wgtfacq_e_d_0_s_120 = {};
    int __f2dace_SOA_wgtfacq_e_d_1_s_121 = {};
    int __f2dace_SOA_wgtfacq_e_d_2_s_122 = {};
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

struct global_data_type {
    int lextra_diffu = {};
    int* nflatlev = {};
    int* nrdmax = {};
    int timer_intp = {};
    int timer_solve_nh_veltend = {};
    int timers_level = {};
};

struct t_nh_diag {
    int __f2dace_SA_ddt_vn_apc_pc_d_0_s_94 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_1_s_95 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_2_s_96 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_3_s_97 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_0_s_98 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_1_s_99 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_2_s_100 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_3_s_101 = {};
    int __f2dace_SA_vn_ie_d_0_s_88 = {};
    int __f2dace_SA_vn_ie_d_1_s_89 = {};
    int __f2dace_SA_vn_ie_d_2_s_90 = {};
    int __f2dace_SA_vn_ie_ubc_d_0_s_82 = {};
    int __f2dace_SA_vn_ie_ubc_d_1_s_83 = {};
    int __f2dace_SA_vn_ie_ubc_d_2_s_84 = {};
    int __f2dace_SA_vt_d_0_s_85 = {};
    int __f2dace_SA_vt_d_1_s_86 = {};
    int __f2dace_SA_vt_d_2_s_87 = {};
    int __f2dace_SA_w_concorr_c_d_0_s_91 = {};
    int __f2dace_SA_w_concorr_c_d_1_s_92 = {};
    int __f2dace_SA_w_concorr_c_d_2_s_93 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_94 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_95 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_96 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_97 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_0_s_98 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_1_s_99 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_2_s_100 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_3_s_101 = {};
    int __f2dace_SOA_vn_ie_d_0_s_88 = {};
    int __f2dace_SOA_vn_ie_d_1_s_89 = {};
    int __f2dace_SOA_vn_ie_d_2_s_90 = {};
    int __f2dace_SOA_vn_ie_ubc_d_0_s_82 = {};
    int __f2dace_SOA_vn_ie_ubc_d_1_s_83 = {};
    int __f2dace_SOA_vn_ie_ubc_d_2_s_84 = {};
    int __f2dace_SOA_vt_d_0_s_85 = {};
    int __f2dace_SOA_vt_d_1_s_86 = {};
    int __f2dace_SOA_vt_d_2_s_87 = {};
    int __f2dace_SOA_w_concorr_c_d_0_s_91 = {};
    int __f2dace_SOA_w_concorr_c_d_1_s_92 = {};
    int __f2dace_SOA_w_concorr_c_d_2_s_93 = {};
    double* ddt_vn_apc_pc = {};
    double* ddt_w_adv_pc = {};
    double max_vcfl_dyn = {};
    double* vn_ie = {};
    double* vn_ie_ubc = {};
    double* vt = {};
    double* w_concorr_c = {};
};

struct t_nh_prog {
    int __f2dace_SA_vn_d_0_s_79 = {};
    int __f2dace_SA_vn_d_1_s_80 = {};
    int __f2dace_SA_vn_d_2_s_81 = {};
    int __f2dace_SA_w_d_0_s_76 = {};
    int __f2dace_SA_w_d_1_s_77 = {};
    int __f2dace_SA_w_d_2_s_78 = {};
    int __f2dace_SOA_vn_d_0_s_79 = {};
    int __f2dace_SOA_vn_d_1_s_80 = {};
    int __f2dace_SOA_vn_d_2_s_81 = {};
    int __f2dace_SOA_w_d_0_s_76 = {};
    int __f2dace_SOA_w_d_1_s_77 = {};
    int __f2dace_SOA_w_d_2_s_78 = {};
    double* vn = {};
    double* w = {};
};

struct velocity_tendencies_state_t {

};

int __f2dace_SOA_area_d_0_s_2_cells_p_patch_1;
int __f2dace_SOA_area_d_1_s_3_cells_p_patch_1;
int __f2dace_SA_area_d_0_s_2_cells_p_patch_1;
int __f2dace_SA_area_d_1_s_3_cells_p_patch_1;
int __f2dace_SOA_w_d_0_s_76_p_prog_6;
int __f2dace_SOA_w_d_1_s_77_p_prog_6;
int __f2dace_SOA_w_d_2_s_78_p_prog_6;
int __f2dace_SA_w_d_0_s_76_p_prog_6;
int __f2dace_SA_w_d_1_s_77_p_prog_6;
int __f2dace_SA_w_d_2_s_78_p_prog_6;
int __f2dace_SOA_vn_d_0_s_79_p_prog_6;
int __f2dace_SOA_vn_d_1_s_80_p_prog_6;
int __f2dace_SOA_vn_d_2_s_81_p_prog_6;
int __f2dace_SA_vn_d_0_s_79_p_prog_6;
int __f2dace_SA_vn_d_1_s_80_p_prog_6;
int __f2dace_SA_vn_d_2_s_81_p_prog_6;
int __f2dace_SOA_ddxn_z_full_d_0_s_102_p_metrics_7;
int __f2dace_SOA_ddxn_z_full_d_1_s_103_p_metrics_7;
int __f2dace_SOA_ddxn_z_full_d_2_s_104_p_metrics_7;
int __f2dace_SA_ddxn_z_full_d_0_s_102_p_metrics_7;
int __f2dace_SA_ddxn_z_full_d_1_s_103_p_metrics_7;
int __f2dace_SA_ddxn_z_full_d_2_s_104_p_metrics_7;
int __f2dace_SOA_ddxt_z_full_d_0_s_105_p_metrics_7;
int __f2dace_SOA_ddxt_z_full_d_1_s_106_p_metrics_7;
int __f2dace_SOA_ddxt_z_full_d_2_s_107_p_metrics_7;
int __f2dace_SA_ddxt_z_full_d_0_s_105_p_metrics_7;
int __f2dace_SA_ddxt_z_full_d_1_s_106_p_metrics_7;
int __f2dace_SA_ddxt_z_full_d_2_s_107_p_metrics_7;
int __f2dace_SOA_ddqz_z_full_e_d_0_s_108_p_metrics_7;
int __f2dace_SOA_ddqz_z_full_e_d_1_s_109_p_metrics_7;
int __f2dace_SOA_ddqz_z_full_e_d_2_s_110_p_metrics_7;
int __f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7;
int __f2dace_SA_ddqz_z_full_e_d_1_s_109_p_metrics_7;
int __f2dace_SA_ddqz_z_full_e_d_2_s_110_p_metrics_7;
int __f2dace_SOA_ddqz_z_half_d_0_s_111_p_metrics_7;
int __f2dace_SOA_ddqz_z_half_d_1_s_112_p_metrics_7;
int __f2dace_SOA_ddqz_z_half_d_2_s_113_p_metrics_7;
int __f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7;
int __f2dace_SA_ddqz_z_half_d_1_s_112_p_metrics_7;
int __f2dace_SA_ddqz_z_half_d_2_s_113_p_metrics_7;
int __f2dace_SOA_wgtfac_c_d_0_s_114_p_metrics_7;
int __f2dace_SOA_wgtfac_c_d_1_s_115_p_metrics_7;
int __f2dace_SOA_wgtfac_c_d_2_s_116_p_metrics_7;
int __f2dace_SA_wgtfac_c_d_0_s_114_p_metrics_7;
int __f2dace_SA_wgtfac_c_d_1_s_115_p_metrics_7;
int __f2dace_SA_wgtfac_c_d_2_s_116_p_metrics_7;
int __f2dace_SOA_wgtfac_e_d_0_s_117_p_metrics_7;
int __f2dace_SOA_wgtfac_e_d_1_s_118_p_metrics_7;
int __f2dace_SOA_wgtfac_e_d_2_s_119_p_metrics_7;
int __f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7;
int __f2dace_SA_wgtfac_e_d_1_s_118_p_metrics_7;
int __f2dace_SA_wgtfac_e_d_2_s_119_p_metrics_7;
int __f2dace_SOA_wgtfacq_e_d_0_s_120_p_metrics_7;
int __f2dace_SOA_wgtfacq_e_d_1_s_121_p_metrics_7;
int __f2dace_SOA_wgtfacq_e_d_2_s_122_p_metrics_7;
int __f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7;
int __f2dace_SA_wgtfacq_e_d_1_s_121_p_metrics_7;
int __f2dace_SA_wgtfacq_e_d_2_s_122_p_metrics_7;
int __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7;
int __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7;
int __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7;
int __f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7;
int __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7;
int __f2dace_SA_coeff_gradekin_d_2_s_125_p_metrics_7;
int __f2dace_SOA_coeff1_dwdz_d_0_s_126_p_metrics_7;
int __f2dace_SOA_coeff1_dwdz_d_1_s_127_p_metrics_7;
int __f2dace_SOA_coeff1_dwdz_d_2_s_128_p_metrics_7;
int __f2dace_SA_coeff1_dwdz_d_0_s_126_p_metrics_7;
int __f2dace_SA_coeff1_dwdz_d_1_s_127_p_metrics_7;
int __f2dace_SA_coeff1_dwdz_d_2_s_128_p_metrics_7;
int __f2dace_SOA_coeff2_dwdz_d_0_s_129_p_metrics_7;
int __f2dace_SOA_coeff2_dwdz_d_1_s_130_p_metrics_7;
int __f2dace_SOA_coeff2_dwdz_d_2_s_131_p_metrics_7;
int __f2dace_SA_coeff2_dwdz_d_0_s_129_p_metrics_7;
int __f2dace_SA_coeff2_dwdz_d_1_s_130_p_metrics_7;
int __f2dace_SA_coeff2_dwdz_d_2_s_131_p_metrics_7;
int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_132_p_metrics_7;
int __f2dace_SA_deepatmo_gradh_mc_d_0_s_132_p_metrics_7;
int __f2dace_SOA_deepatmo_invr_mc_d_0_s_133_p_metrics_7;
int __f2dace_SA_deepatmo_invr_mc_d_0_s_133_p_metrics_7;
int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_134_p_metrics_7;
int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_134_p_metrics_7;
int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_135_p_metrics_7;
int __f2dace_SA_deepatmo_invr_ifc_d_0_s_135_p_metrics_7;
int __f2dace_SOA_vn_ie_ubc_d_0_s_82_p_diag_8;
int __f2dace_SOA_vn_ie_ubc_d_1_s_83_p_diag_8;
int __f2dace_SOA_vn_ie_ubc_d_2_s_84_p_diag_8;
int __f2dace_SA_vn_ie_ubc_d_0_s_82_p_diag_8;
int __f2dace_SA_vn_ie_ubc_d_1_s_83_p_diag_8;
int __f2dace_SA_vn_ie_ubc_d_2_s_84_p_diag_8;
int __f2dace_SOA_vt_d_0_s_85_p_diag_8;
int __f2dace_SOA_vt_d_1_s_86_p_diag_8;
int __f2dace_SOA_vt_d_2_s_87_p_diag_8;
int __f2dace_SA_vt_d_0_s_85_p_diag_8;
int __f2dace_SA_vt_d_1_s_86_p_diag_8;
int __f2dace_SA_vt_d_2_s_87_p_diag_8;
int __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8;
int __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8;
int __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8;
int __f2dace_SA_vn_ie_d_0_s_88_p_diag_8;
int __f2dace_SA_vn_ie_d_1_s_89_p_diag_8;
int __f2dace_SA_vn_ie_d_2_s_90_p_diag_8;
int __f2dace_SOA_w_concorr_c_d_0_s_91_p_diag_8;
int __f2dace_SOA_w_concorr_c_d_1_s_92_p_diag_8;
int __f2dace_SOA_w_concorr_c_d_2_s_93_p_diag_8;
int __f2dace_SA_w_concorr_c_d_0_s_91_p_diag_8;
int __f2dace_SA_w_concorr_c_d_1_s_92_p_diag_8;
int __f2dace_SA_w_concorr_c_d_2_s_93_p_diag_8;
int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_94_p_diag_8;
int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_95_p_diag_8;
int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_96_p_diag_8;
int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_97_p_diag_8;
int __f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8;
int __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8;
int __f2dace_SA_ddt_vn_apc_pc_d_2_s_96_p_diag_8;
int __f2dace_SA_ddt_vn_apc_pc_d_3_s_97_p_diag_8;
int __f2dace_SOA_ddt_w_adv_pc_d_0_s_98_p_diag_8;
int __f2dace_SOA_ddt_w_adv_pc_d_1_s_99_p_diag_8;
int __f2dace_SOA_ddt_w_adv_pc_d_2_s_100_p_diag_8;
int __f2dace_SOA_ddt_w_adv_pc_d_3_s_101_p_diag_8;
int __f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8;
int __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8;
int __f2dace_SA_ddt_w_adv_pc_d_2_s_100_p_diag_8;
int __f2dace_SA_ddt_w_adv_pc_d_3_s_101_p_diag_8;
void __program_velocity_tendencies_internal(velocity_tendencies_state_t*__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_157, int __f2dace_A_z_kin_hor_e_d_1_s_158, int __f2dace_A_z_vt_ie_d_0_s_160, int __f2dace_A_z_vt_ie_d_1_s_161, int __f2dace_A_z_w_concorr_me_d_0_s_154, int __f2dace_A_z_w_concorr_me_d_1_s_155, int __f2dace_OA_z_kin_hor_e_d_0_s_157, int __f2dace_OA_z_kin_hor_e_d_1_s_158, int __f2dace_OA_z_kin_hor_e_d_2_s_159, int __f2dace_OA_z_vt_ie_d_0_s_160, int __f2dace_OA_z_vt_ie_d_1_s_161, int __f2dace_OA_z_vt_ie_d_2_s_162, int __f2dace_OA_z_w_concorr_me_d_0_s_154, int __f2dace_OA_z_w_concorr_me_d_1_s_155, int __f2dace_OA_z_w_concorr_me_d_2_s_156, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    double *z_w_concorr_mc;
    z_w_concorr_mc = new double DACE_ALIGN(64)[90];
    double *z_w_con_c;
    z_w_con_c = new double DACE_ALIGN(64)[91];
    double *z_w_con_c_full;
    z_w_con_c_full = new double DACE_ALIGN(64)[57600];
    double *z_v_grad_w;
    z_v_grad_w = new double DACE_ALIGN(64)[86400];
    double *z_w_v;
    z_w_v = new double DACE_ALIGN(64)[29211];
    double *zeta;
    zeta = new double DACE_ALIGN(64)[28890];
    double *z_ekinh;
    z_ekinh = new double DACE_ALIGN(64)[57600];
    double cfl_w_limit;
    double vcfl;
    double maxvcfl;
    double *vcflmax;
    vcflmax = new double DACE_ALIGN(64)[640];
    double w_con_e;
    double scalfac_exdiff;
    double difcoef;
    int nrdmax_jg;
    int nflatlev_jg;
    int *levmask;
    levmask = new int DACE_ALIGN(64)[57600];
    int *levelmask;
    levelmask = new int DACE_ALIGN(64)[90];
    int *cfl_clipping;
    cfl_clipping = new int DACE_ALIGN(64)[91];
    double tmp_call_2;
    double tmp_call_13;
    double tmp_call_19;
    int _if_cond_9;
    int _if_cond_17;
    int _if_cond_19;
    int _if_cond_24;
    int _if_cond_28;
    int* v_global_data_lextra_diffu;
    v_global_data_lextra_diffu = (int*)(&(global_data->lextra_diffu));
    t_grid_edges** v_p_patch_edges;
    v_p_patch_edges = (t_grid_edges**)(&(p_patch->edges));
    t_grid_cells** v_p_patch_cells;
    v_p_patch_cells = (t_grid_cells**)(&(p_patch->cells));
    double* v_p_prog_vn;
    v_p_prog_vn = (double*)(&(p_prog->vn)[0]);
    double* v_p_diag_vt;
    v_p_diag_vt = (double*)(&(p_diag->vt)[0]);
    double* v_p_metrics_wgtfac_e;
    v_p_metrics_wgtfac_e = (double*)(&(p_metrics->wgtfac_e)[0]);
    double* v_p_diag_vn_ie;
    v_p_diag_vn_ie = (double*)(&(p_diag->vn_ie)[0]);
    double* v_p_prog_w;
    v_p_prog_w = (double*)(&(p_prog->w)[0]);
    double* v_p_int_e_bln_c_s;
    v_p_int_e_bln_c_s = (double*)(&(p_int->e_bln_c_s)[0]);
    double* v_p_diag_w_concorr_c;
    v_p_diag_w_concorr_c = (double*)(&(p_diag->w_concorr_c)[0]);
    double* v_p_metrics_ddqz_z_half;
    v_p_metrics_ddqz_z_half = (double*)(&(p_metrics->ddqz_z_half)[0]);
    double* v_p_diag_ddt_w_adv_pc;
    v_p_diag_ddt_w_adv_pc = (double*)(&(p_diag->ddt_w_adv_pc)[0]);
    double* v_p_metrics_coeff_gradekin;
    v_p_metrics_coeff_gradekin = (double*)(&(p_metrics->coeff_gradekin)[0]);
    double* v_p_int_c_lin_e;
    v_p_int_c_lin_e = (double*)(&(p_int->c_lin_e)[0]);
    double* v_p_metrics_ddqz_z_full_e;
    v_p_metrics_ddqz_z_full_e = (double*)(&(p_metrics->ddqz_z_full_e)[0]);
    double* v_p_diag_ddt_vn_apc_pc;
    v_p_diag_ddt_vn_apc_pc = (double*)(&(p_diag->ddt_vn_apc_pc)[0]);
    int* v_v_p_patch_edges_start_block;
    v_v_p_patch_edges_start_block = (int*)(&((*v_p_patch_edges)->start_block)[0]);
    int* v_v_p_patch_edges_end_block;
    v_v_p_patch_edges_end_block = (int*)(&((*v_p_patch_edges)->end_block)[0]);
    int* v_v_p_patch_cells_start_block;
    v_v_p_patch_cells_start_block = (int*)(&((*v_p_patch_cells)->start_block)[0]);
    int* v_v_p_patch_cells_end_block;
    v_v_p_patch_cells_end_block = (int*)(&((*v_p_patch_cells)->end_block)[0]);
    int* v_v_p_patch_edges_quad_idx;
    v_v_p_patch_edges_quad_idx = (int*)(&((*v_p_patch_edges)->quad_idx)[0]);
    int* v_v_p_patch_edges_quad_blk;
    v_v_p_patch_edges_quad_blk = (int*)(&((*v_p_patch_edges)->quad_blk)[0]);
    int* v_v_p_patch_edges_cell_idx;
    v_v_p_patch_edges_cell_idx = (int*)(&((*v_p_patch_edges)->cell_idx)[0]);
    int* v_v_p_patch_edges_cell_blk;
    v_v_p_patch_edges_cell_blk = (int*)(&((*v_p_patch_edges)->cell_blk)[0]);
    int* v_v_p_patch_edges_vertex_blk;
    v_v_p_patch_edges_vertex_blk = (int*)(&((*v_p_patch_edges)->vertex_blk)[0]);
    double* v_v_p_patch_edges_inv_primal_edge_length;
    v_v_p_patch_edges_inv_primal_edge_length = (double*)(&((*v_p_patch_edges)->inv_primal_edge_length)[0]);
    double* v_v_p_patch_edges_tangent_orientation;
    v_v_p_patch_edges_tangent_orientation = (double*)(&((*v_p_patch_edges)->tangent_orientation)[0]);
    double* v_v_p_patch_edges_ft_e;
    v_v_p_patch_edges_ft_e = (double*)(&((*v_p_patch_edges)->ft_e)[0]);
    int* v_v_p_patch_cells_edge_idx;
    v_v_p_patch_cells_edge_idx = (int*)(&((*v_p_patch_cells)->edge_idx)[0]);
    int* v_v_p_patch_cells_edge_blk;
    v_v_p_patch_cells_edge_blk = (int*)(&((*v_p_patch_cells)->edge_blk)[0]);
    int* v_v_p_patch_cells_neighbor_idx;
    v_v_p_patch_cells_neighbor_idx = (int*)(&((*v_p_patch_cells)->neighbor_idx)[0]);
    int* v_v_p_patch_cells_neighbor_blk;
    v_v_p_patch_cells_neighbor_blk = (int*)(&((*v_p_patch_cells)->neighbor_blk)[0]);
    double* v_v_p_patch_edges_f_e;
    v_v_p_patch_edges_f_e = (double*)(&((*v_p_patch_edges)->f_e)[0]);
    t_patch** p_patch_var_31_3;
    p_patch_var_31_3 = &p_patch;
    t_grid_edges** v_p_patch_var_31_edges;
    v_p_patch_var_31_edges = (t_grid_edges**)(&((*p_patch_var_31_3)->edges));
    int* v_v_p_patch_var_31_edges_start_index;
    v_v_p_patch_var_31_edges_start_index = (int*)(&((*v_p_patch_var_31_edges)->start_index)[0]);
    int* v_v_p_patch_var_31_edges_end_index;
    v_v_p_patch_var_31_edges_end_index = (int*)(&((*v_p_patch_var_31_edges)->end_index)[0]);
    t_patch** p_patch_var_31_0;
    p_patch_var_31_0 = &p_patch;
    t_patch** p_patch_var_22_1;
    p_patch_var_22_1 = &p_patch;
    t_grid_cells** v_p_patch_var_22_cells;
    v_p_patch_var_22_cells = (t_grid_cells**)(&((*p_patch_var_22_1)->cells));
    int* v_v_p_patch_var_22_cells_start_index;
    v_v_p_patch_var_22_cells_start_index = (int*)(&((*v_p_patch_var_22_cells)->start_index)[0]);
    int* v_v_p_patch_var_22_cells_end_index;
    v_v_p_patch_var_22_cells_end_index = (int*)(&((*v_p_patch_var_22_cells)->end_index)[0]);
    t_patch** p_patch_var_22_0;
    p_patch_var_22_0 = &p_patch;
    t_patch** p_patch_var_31_1;
    p_patch_var_31_1 = &p_patch;
    t_patch** p_patch_var_31_2;
    p_patch_var_31_2 = &p_patch;
    t_patch** ptr_patch_var_49_0;
    ptr_patch_var_49_0 = &p_patch;
    t_grid_vertices** v_ptr_patch_var_49_verts;
    v_ptr_patch_var_49_verts = (t_grid_vertices**)(&((*ptr_patch_var_49_0)->verts));
    int* v_v_ptr_patch_var_49_verts_start_block;
    v_v_ptr_patch_var_49_verts_start_block = (int*)(&((*v_ptr_patch_var_49_verts)->start_block)[0]);
    int* v_v_ptr_patch_var_49_verts_end_block;
    v_v_ptr_patch_var_49_verts_end_block = (int*)(&((*v_ptr_patch_var_49_verts)->end_block)[0]);
    int* v_v_ptr_patch_var_49_verts_edge_idx;
    v_v_ptr_patch_var_49_verts_edge_idx = (int*)(&((*v_ptr_patch_var_49_verts)->edge_idx)[0]);
    int* v_v_ptr_patch_var_49_verts_edge_blk;
    v_v_ptr_patch_var_49_verts_edge_blk = (int*)(&((*v_ptr_patch_var_49_verts)->edge_blk)[0]);
    t_patch** ptr_patch_var_68_0;
    ptr_patch_var_68_0 = &p_patch;
    t_patch** p_patch_var_40_0;
    p_patch_var_40_0 = &(*ptr_patch_var_68_0);
    t_grid_vertices** v_p_patch_var_40_verts;
    v_p_patch_var_40_verts = (t_grid_vertices**)(&((*p_patch_var_40_0)->verts));
    int* v_v_p_patch_var_40_verts_start_index;
    v_v_p_patch_var_40_verts_start_index = (int*)(&((*v_p_patch_var_40_verts)->start_index)[0]);
    int* v_v_p_patch_var_40_verts_end_index;
    v_v_p_patch_var_40_verts_end_index = (int*)(&((*v_p_patch_var_40_verts)->end_index)[0]);
    t_grid_vertices** v_ptr_patch_var_68_verts;
    v_ptr_patch_var_68_verts = (t_grid_vertices**)(&((*ptr_patch_var_68_0)->verts));
    int* v_v_ptr_patch_var_68_verts_start_blk;
    v_v_ptr_patch_var_68_verts_start_blk = (int*)(&((*v_ptr_patch_var_68_verts)->start_blk)[0]);
    int* v_v_ptr_patch_var_68_verts_end_blk;
    v_v_ptr_patch_var_68_verts_end_blk = (int*)(&((*v_ptr_patch_var_68_verts)->end_blk)[0]);
    int* v_v_ptr_patch_var_68_verts_cell_idx;
    v_v_ptr_patch_var_68_verts_cell_idx = (int*)(&((*v_ptr_patch_var_68_verts)->cell_idx)[0]);
    int* v_v_ptr_patch_var_68_verts_cell_blk;
    v_v_ptr_patch_var_68_verts_cell_blk = (int*)(&((*v_ptr_patch_var_68_verts)->cell_blk)[0]);
    int _if_cond_10;
    int i_startblk_var_61_0;
    int i_endblk_var_62_0;
    int _if_cond_11;
    int i_startblk_var_86;
    int i_endblk_var_87;
    int _if_cond_14;
    int _if_cond_15;
    int i_startblk_2;
    int i_endblk_2;
    int tmp_arg_9;
    double tmp_call_20;
    int i_startblk_var_80_0;
    int i_endblk_var_81_0;
    int _for_it_3_0;
    int _for_it_4_0;
    int tmp_index_101_0;
    int tmp_index_103_0;
    int tmp_index_113_0;
    int tmp_index_115_0;
    int tmp_index_125_0;
    int tmp_index_127_0;
    int tmp_index_137_0;
    int tmp_index_139_0;
    int tmp_index_149_0;
    int tmp_index_151_0;
    int tmp_index_161_0;
    int tmp_index_163_0;
    int _for_it_5_0;
    int i_endidx_var_83_0;
    int i_startidx_var_82_0;
    int tmp_call_0_3;
    int _for_it_6;
    int _for_it_7;
    int tmp_index_180;
    int tmp_index_182;
    int tmp_index_192;
    int tmp_index_194;
    int tmp_index_204;
    int tmp_index_206;
    int tmp_index_216;
    int tmp_index_218;
    int _for_it_8;
    int _for_it_9;
    int _for_it_10;
    int _for_it_11;
    int _for_it_12;
    int _for_it_13;
    int _for_it_14;
    int _for_it_15;
    int i_startidx_var_88;
    int i_endidx_var_89;
    int tmp_call_0_2;
    int _for_it_17;
    int _for_it_18;
    int tmp_index_376;
    int tmp_index_378;
    int tmp_index_385;
    int tmp_index_387;
    int tmp_index_403;
    int tmp_index_412;
    int _for_it_19;
    int tmp_call_0_1;
    int _for_it_20;
    int _for_it_21;
    int _for_it_22;
    int _if_cond_16;
    int tmp_arg_4;
    int tmp_arg_5;
    int _if_cond_22;
    int _for_it_23;
    int _for_it_24;
    int tmp_index_454;
    int tmp_index_456;
    int tmp_index_466;
    int tmp_index_468;
    int tmp_index_478;
    int tmp_index_480;
    int _for_it_25;
    int _for_it_26;
    int tmp_index_492;
    int tmp_index_494;
    int tmp_index_504;
    int tmp_index_506;
    int tmp_index_516;
    int tmp_index_518;
    int _for_it_27;
    int _for_it_28;
    int _for_it_29;
    int _for_it_30;
    int _for_it_31;
    int64_t _for_it_32;
    int _for_it_33;
    int _for_it_34;
    int _for_it_35;
    int clip_count;
    int _for_it_36;
    int _for_it_37;
    int _for_it_38;
    int _for_it_39;
    int64_t _for_it_40;
    int _for_it_41;
    int tmp_index_587;
    int _for_it_42;
    int _for_it_43;
    int tmp_index_614;
    int tmp_index_618;
    int tmp_index_630;
    int tmp_index_642;
    int tmp_index_654;
    int _for_it_44;
    int tmp_arg_6;
    int _for_it_45;
    int _for_it_46;
    int tmp_index_669;
    int tmp_index_673;
    int tmp_index_688;
    int tmp_index_690;
    int tmp_index_700;
    int tmp_index_702;
    int tmp_index_712;
    int tmp_index_714;
    int i_startidx_2;
    int i_endidx_2;
    int tmp_call_15;
    int _for_it_47;
    int tmp_parfor_0;
    int tmp_call_0_0;
    int _if_cond_27;
    int _for_it_48;
    int _for_it_49;
    int tmp_index_726;
    int tmp_index_747;
    int tmp_index_759;
    int tmp_index_773;
    int tmp_index_782;
    int tmp_index_794;
    int tmp_index_806;
    int _for_it_50;
    int _for_it_51;
    int tmp_index_819;
    int tmp_index_840;
    int tmp_index_852;
    int tmp_index_867;
    int tmp_index_876;
    int tmp_index_889;
    int tmp_index_901;
    int _for_it_52;
    int tmp_arg_10;
    int _for_it_53;
    int tmp_index_930;
    int tmp_index_942;
    int _for_it_54;
    int tmp_index_952;
    int tmp_index_956;
    int tmp_index_974;
    int tmp_index_976;
    int tmp_index_986;
    int tmp_index_988;
    int tmp_index_998;
    int tmp_index_1000;
    int tmp_index_1010;
    int tmp_index_1012;
    int tmp_index_1025;
    int tmp_index_1034;
    int _for_it_0_0;
    int _for_it_1_0;
    int tmp_index_19_0;
    int tmp_index_21_0;
    int tmp_index_31_0;
    int tmp_index_33_0;
    int tmp_index_43_0;
    int tmp_index_45_0;
    int tmp_index_55_0;
    int tmp_index_57_0;
    int tmp_index_67_0;
    int tmp_index_69_0;
    int tmp_index_79_0;
    int tmp_index_81_0;
    int _for_it_2_0;
    int i_startidx_var_63_0;
    int i_endidx_var_64_0;


    {
        int* v_global_data_nrdmax;
        v_global_data_nrdmax = (int*)(&(global_data->nrdmax)[0]);
        int* v_global_data_nflatlev;
        v_global_data_nflatlev = (int*)(&(global_data->nflatlev)[0]);

        {
            int global_data_0_in_nrdmax_0 = v_global_data_nrdmax[0];
            int nrdmax_jg_out;

            ///////////////////
            // Tasklet code (T_l329_c329)
            nrdmax_jg_out = global_data_0_in_nrdmax_0;
            ///////////////////

            nrdmax_jg = nrdmax_jg_out;
        }
        {
            int global_data_0_in_nflatlev_0 = v_global_data_nflatlev[0];
            int nflatlev_jg_out;

            ///////////////////
            // Tasklet code (T_l330_c330)
            nflatlev_jg_out = global_data_0_in_nflatlev_0;
            ///////////////////

            nflatlev_jg = nflatlev_jg_out;
        }
        {
            int global_data_0_in_lextra_diffu = v_global_data_lextra_diffu[0];
            int _if_cond_9_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_9_out = global_data_0_in_lextra_diffu;
            ///////////////////

            _if_cond_9 = _if_cond_9_out;
        }

    }

    if ((_if_cond_9 == 1)) {
        {

            {
                double dtime_0_in = dtime;
                double cfl_w_limit_out;

                ///////////////////
                // Tasklet code (T_l334_c334)
                cfl_w_limit_out = (0.65 / dtime_0_in);
                ///////////////////

                cfl_w_limit = cfl_w_limit_out;
            }
            {
                double dtime_0_in = dtime;
                double dtime_1_in = dtime;
                double cfl_w_limit_0_in = cfl_w_limit;
                double scalfac_exdiff_out;

                ///////////////////
                // Tasklet code (T_l335_c335)
                scalfac_exdiff_out = (0.05 / (dtime_0_in * (0.85 - (cfl_w_limit_0_in * dtime_1_in))));
                ///////////////////

                scalfac_exdiff = scalfac_exdiff_out;
            }

        }
    } else {
        {

            {
                double dtime_0_in = dtime;
                double cfl_w_limit_out;

                ///////////////////
                // Tasklet code (T_l337_c337)
                cfl_w_limit_out = (0.85 / dtime_0_in);
                ///////////////////

                cfl_w_limit = cfl_w_limit_out;
            }
            {
                double scalfac_exdiff_out;

                ///////////////////
                // Tasklet code (T_l338_c338)
                scalfac_exdiff_out = 0.0;
                ///////////////////

                scalfac_exdiff = scalfac_exdiff_out;
            }

        }
    }
    _if_cond_10 = (1 - lvn_only);

    if ((_if_cond_10 == 1)) {
        {


        }
        i_startblk_var_80_0 = v_v_ptr_patch_var_68_verts_start_blk[9];
        {


        }
        i_endblk_var_81_0 = v_v_ptr_patch_var_68_verts_end_blk[2];
        for (_for_it_3_0 = i_startblk_var_80_0; (_for_it_3_0 <= i_endblk_var_81_0); _for_it_3_0 = (_for_it_3_0 + 1)) {
            if (((_for_it_3_0 == i_startblk_var_80_0) == 1)) {
                {


                }
                i_endidx_var_83_0 = 1;
                i_startidx_var_82_0 = v_v_p_patch_var_40_verts_start_index[9];
                if (((_for_it_3_0 == i_endblk_var_81_0) == 1)) {
                    {


                    }
                    i_endidx_var_83_0 = v_v_p_patch_var_40_verts_end_index[2];

                }
            } else {
                if (((_for_it_3_0 == i_endblk_var_81_0) == 1)) {

                    i_startidx_var_82_0 = 1;
                    {


                    }
                    i_endidx_var_83_0 = v_v_p_patch_var_40_verts_end_index[2];

                } else {

                    i_endidx_var_83_0 = 1;
                    i_startidx_var_82_0 = 1;

                }
            }
            for (_for_it_4_0 = 1; (_for_it_4_0 <= __f2dace_SA_w_d_1_s_77_p_prog_6); _for_it_4_0 = (_for_it_4_0 + 1)) {
                for (_for_it_5_0 = i_startidx_var_82_0; (_for_it_5_0 <= i_endidx_var_83_0); _for_it_5_0 = (_for_it_5_0 + 1)) {
                    {


                    }
                    tmp_index_101_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_3_0) + _for_it_5_0) - 33)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_103_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_3_0) + _for_it_5_0) - 33)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {


                    }
                    tmp_index_113_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 10239)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_115_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 10239)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {


                    }
                    tmp_index_125_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 20511)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_127_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 20511)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {


                    }
                    tmp_index_137_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 30783)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_139_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 30783)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {


                    }
                    tmp_index_149_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 41055)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_151_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 41055)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {


                    }
                    tmp_index_161_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 51327)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_163_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 51327)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {
                        double* p_prog_w_1;
                        p_prog_w_1 = (double*)(&(p_prog->w)[0]);
                        double* p_int_cells_aw_verts_2;
                        p_int_cells_aw_verts_2 = (double*)(&(p_int->cells_aw_verts)[0]);

                        {
                            double c_int_0_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_3_0) + _for_it_5_0) - 193)];
                            double c_int_1_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_3_0) + _for_it_5_0) - 161)];
                            double c_int_2_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_3_0) + _for_it_5_0) - 129)];
                            double c_int_3_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_3_0) + _for_it_5_0) - 97)];
                            double c_int_4_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_3_0) + _for_it_5_0) - 65)];
                            double c_int_5_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_3_0) + _for_it_5_0) - 33)];
                            double p_cell_in_0_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_103_0) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_4_0))) + tmp_index_101_0)];
                            double p_cell_in_1_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_115_0) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_4_0))) + tmp_index_113_0)];
                            double p_cell_in_2_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_127_0) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_4_0))) + tmp_index_125_0)];
                            double p_cell_in_3_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_139_0) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_4_0))) + tmp_index_137_0)];
                            double p_cell_in_4_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_151_0) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_4_0))) + tmp_index_149_0)];
                            double p_cell_in_5_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_163_0) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_4_0))) + tmp_index_161_0)];
                            double p_vert_out_out_0;

                            ///////////////////
                            // Tasklet code (T_l263_c263)
                            p_vert_out_out_0 = ((((((c_int_0_in_0 * p_cell_in_0_in_0) + (c_int_1_in_0 * p_cell_in_1_in_0)) + (c_int_2_in_0 * p_cell_in_2_in_0)) + (c_int_3_in_0 * p_cell_in_3_in_0)) + (c_int_4_in_0 * p_cell_in_4_in_0)) + (c_int_5_in_0 * p_cell_in_5_in_0));
                            ///////////////////

                            z_w_v[(((91 * _for_it_3_0) + _for_it_4_0) - 92)] = p_vert_out_out_0;
                        }

                    }

                }

            }

        }
    }

    {


    }
    i_startblk_var_61_0 = v_v_ptr_patch_var_49_verts_start_block[9];

    {


    }
    i_endblk_var_62_0 = v_v_ptr_patch_var_49_verts_end_block[2];

    for (_for_it_0_0 = i_startblk_var_61_0; (_for_it_0_0 <= i_endblk_var_62_0); _for_it_0_0 = (_for_it_0_0 + 1)) {
        if (((_for_it_0_0 == i_startblk_var_61_0) == 1)) {
            {


            }
            i_startidx_var_63_0 = v_v_p_patch_var_40_verts_start_index[9];
            i_endidx_var_64_0 = 1;
            if (((_for_it_0_0 == i_endblk_var_62_0) == 1)) {
                {


                }
                i_endidx_var_64_0 = v_v_p_patch_var_40_verts_end_index[2];

            }
        } else {
            if (((_for_it_0_0 == i_endblk_var_62_0) == 1)) {

                i_startidx_var_63_0 = 1;
                {


                }
                i_endidx_var_64_0 = v_v_p_patch_var_40_verts_end_index[2];

            } else {

                i_startidx_var_63_0 = 1;
                i_endidx_var_64_0 = 1;

            }
        }
        for (_for_it_1_0 = 1; (_for_it_1_0 <= __f2dace_SA_vn_d_1_s_80_p_prog_6); _for_it_1_0 = (_for_it_1_0 + 1)) {
            for (_for_it_2_0 = i_startidx_var_63_0; (_for_it_2_0 <= i_endidx_var_64_0); _for_it_2_0 = (_for_it_2_0 + 1)) {
                {


                }
                tmp_index_19_0 = (v_v_ptr_patch_var_49_verts_edge_idx[(((32 * _for_it_0_0) + _for_it_2_0) - 33)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                {


                }
                tmp_index_21_0 = (v_v_ptr_patch_var_49_verts_edge_blk[(((32 * _for_it_0_0) + _for_it_2_0) - 33)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                {


                }
                tmp_index_31_0 = (v_v_ptr_patch_var_49_verts_edge_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 10239)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                {


                }
                tmp_index_33_0 = (v_v_ptr_patch_var_49_verts_edge_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 10239)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                {


                }
                tmp_index_43_0 = (v_v_ptr_patch_var_49_verts_edge_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 20511)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                {


                }
                tmp_index_45_0 = (v_v_ptr_patch_var_49_verts_edge_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 20511)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                {


                }
                tmp_index_55_0 = (v_v_ptr_patch_var_49_verts_edge_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 30783)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                {


                }
                tmp_index_57_0 = (v_v_ptr_patch_var_49_verts_edge_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 30783)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                {


                }
                tmp_index_67_0 = (v_v_ptr_patch_var_49_verts_edge_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 41055)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                {


                }
                tmp_index_69_0 = (v_v_ptr_patch_var_49_verts_edge_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 41055)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                {


                }
                tmp_index_79_0 = (v_v_ptr_patch_var_49_verts_edge_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 51327)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                {


                }
                tmp_index_81_0 = (v_v_ptr_patch_var_49_verts_edge_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 51327)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                {
                    double* p_prog_vn_3;
                    p_prog_vn_3 = (double*)(&(p_prog->vn)[0]);
                    t_int_state** ptr_int_0;
                    ptr_int_0 = &p_int;
                    double* v_ptr_int_geofac_rot;
                    v_ptr_int_geofac_rot = (double*)(&((*ptr_int_0)->geofac_rot)[0]);

                    {
                        double ptr_int_0_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_0_0) + _for_it_2_0) - 193)];
                        double ptr_int_1_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_0_0) + _for_it_2_0) - 161)];
                        double ptr_int_2_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_0_0) + _for_it_2_0) - 129)];
                        double ptr_int_3_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_0_0) + _for_it_2_0) - 97)];
                        double ptr_int_4_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_0_0) + _for_it_2_0) - 65)];
                        double ptr_int_5_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_0_0) + _for_it_2_0) - 33)];
                        double vec_e_0_in_0 = p_prog_vn_3[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_21_0) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_1_0))) + tmp_index_19_0)];
                        double vec_e_1_in_0 = p_prog_vn_3[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_33_0) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_1_0))) + tmp_index_31_0)];
                        double vec_e_2_in_0 = p_prog_vn_3[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_45_0) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_1_0))) + tmp_index_43_0)];
                        double vec_e_3_in_0 = p_prog_vn_3[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_57_0) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_1_0))) + tmp_index_55_0)];
                        double vec_e_4_in_0 = p_prog_vn_3[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_69_0) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_1_0))) + tmp_index_67_0)];
                        double vec_e_5_in_0 = p_prog_vn_3[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_81_0) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_1_0))) + tmp_index_79_0)];
                        double rot_vec_out_0;

                        ///////////////////
                        // Tasklet code (T_l180_c180)
                        rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
                        ///////////////////

                        zeta[(((90 * _for_it_0_0) + _for_it_1_0) - 91)] = rot_vec_out_0;
                    }

                }

            }

        }

    }
    _if_cond_11 = (istep == 1);

    if ((_if_cond_11 == 1)) {
        {


        }
        i_startblk_var_86 = v_v_p_patch_edges_start_block[18];
        {


        }
        i_endblk_var_87 = v_v_p_patch_edges_end_block[3];
        for (_for_it_6 = i_startblk_var_86; (_for_it_6 <= i_endblk_var_87); _for_it_6 = (_for_it_6 + 1)) {
            {


            }
            tmp_call_0_3 = max(1, v_v_p_patch_var_31_edges_start_index[18]);
            if ((_for_it_6 != i_startblk_var_86)) {

                i_startidx_var_88 = 1;

            } else {

                i_startidx_var_88 = tmp_call_0_3;

            }
            if ((_for_it_6 != i_endblk_var_87)) {

                i_endidx_var_89 = 1;

            } else {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_31_edges_end_index[3];

            }
            for (_for_it_7 = 1; (_for_it_7 <= 90); _for_it_7 = (_for_it_7 + 1)) {
                for (_for_it_8 = i_startidx_var_88; (_for_it_8 <= i_endidx_var_89); _for_it_8 = (_for_it_8 + 1)) {
                    {


                    }
                    tmp_index_180 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) - 33)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                    {


                    }
                    tmp_index_182 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) - 33)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                    {


                    }
                    tmp_index_192 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) + 30687)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                    {


                    }
                    tmp_index_194 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) + 30687)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                    {


                    }
                    tmp_index_204 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) + 61407)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                    {


                    }
                    tmp_index_206 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) + 61407)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                    {


                    }
                    tmp_index_216 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) + 92127)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                    {


                    }
                    tmp_index_218 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) + 92127)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                    {
                        double* v_p_int_rbf_vec_coeff_e;
                        v_p_int_rbf_vec_coeff_e = (double*)(&(p_int->rbf_vec_coeff_e)[0]);

                        {
                            double p_int_0_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 132)];
                            double p_int_1_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 131)];
                            double p_int_2_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 130)];
                            double p_int_3_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 129)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_182) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_7))) + tmp_index_180)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_194) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_7))) + tmp_index_192)];
                            double p_prog_2_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_206) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_7))) + tmp_index_204)];
                            double p_prog_3_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_218) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_7))) + tmp_index_216)];
                            double p_diag_out_vt_0;

                            ///////////////////
                            // Tasklet code (T_l351_c351)
                            p_diag_out_vt_0 = ((((p_int_0_in_rbf_vec_coeff_e_0 * p_prog_0_in_vn_0) + (p_int_1_in_rbf_vec_coeff_e_0 * p_prog_1_in_vn_0)) + (p_int_2_in_rbf_vec_coeff_e_0 * p_prog_2_in_vn_0)) + (p_int_3_in_rbf_vec_coeff_e_0 * p_prog_3_in_vn_0));
                            ///////////////////

                            v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * ((- __f2dace_SOA_vt_d_1_s_86_p_diag_8) + _for_it_7))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_8)] = p_diag_out_vt_0;
                        }

                    }

                }

            }
            for (_for_it_9 = 2; (_for_it_9 <= 90); _for_it_9 = (_for_it_9 + 1)) {
                for (_for_it_10 = i_startidx_var_88; (_for_it_10 <= i_endidx_var_89); _for_it_10 = (_for_it_10 + 1)) {
                    {

                        {
                            double p_metrics_0_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * __f2dace_SA_wgtfac_e_d_1_s_118_p_metrics_7) * ((- __f2dace_SOA_wgtfac_e_d_2_s_119_p_metrics_7) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * ((- __f2dace_SOA_wgtfac_e_d_1_s_118_p_metrics_7) + _for_it_9))) - __f2dace_SOA_wgtfac_e_d_0_s_117_p_metrics_7) + _for_it_10)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_9))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_10)];
                            double p_metrics_1_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * __f2dace_SA_wgtfac_e_d_1_s_118_p_metrics_7) * ((- __f2dace_SOA_wgtfac_e_d_2_s_119_p_metrics_7) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * ((- __f2dace_SOA_wgtfac_e_d_1_s_118_p_metrics_7) + _for_it_9))) - __f2dace_SOA_wgtfac_e_d_0_s_117_p_metrics_7) + _for_it_10)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * (((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_9) - 1))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_10)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l356_c356)
                            p_diag_out_vn_ie_0 = ((p_metrics_0_in_wgtfac_e_0 * p_prog_0_in_vn_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_prog_1_in_vn_0));
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * ((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_9))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_10)] = p_diag_out_vn_ie_0;
                        }
                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * ((- __f2dace_SOA_vt_d_1_s_86_p_diag_8) + _for_it_9))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_10)];
                            double tmp_call_2_out;

                            ///////////////////
                            // Tasklet code (T_l357_c357)
                            tmp_call_2_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                            ///////////////////

                            tmp_call_2 = tmp_call_2_out;
                        }

                    }
                    {
                        double tmp_call_1;

                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_9))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_10)];
                            double tmp_call_1_out;

                            ///////////////////
                            // Tasklet code (T_l357_c357)
                            tmp_call_1_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                            ///////////////////

                            tmp_call_1 = tmp_call_1_out;
                        }
                        {
                            double tmp_call_2_0_in = tmp_call_2;
                            double tmp_call_1_0_in = tmp_call_1;
                            double z_kin_hor_e_out_0;

                            ///////////////////
                            // Tasklet code (T_l357_c357)
                            z_kin_hor_e_out_0 = (0.5 * (tmp_call_1_0_in + tmp_call_2_0_in));
                            ///////////////////

                            z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_157 * __f2dace_A_z_kin_hor_e_d_1_s_158) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_159) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_157 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_158) + _for_it_9))) - __f2dace_OA_z_kin_hor_e_d_0_s_157) + _for_it_10)] = z_kin_hor_e_out_0;
                        }

                    }

                }

            }
            _if_cond_11 = (1 - lvn_only);
            if ((_if_cond_11 == 1)) {
                for (_for_it_11 = 2; (_for_it_11 <= 90); _for_it_11 = (_for_it_11 + 1)) {
                    for (_for_it_12 = i_startidx_var_88; (_for_it_12 <= i_endidx_var_89); _for_it_12 = (_for_it_12 + 1)) {
                        {

                            {
                                double p_metrics_0_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * __f2dace_SA_wgtfac_e_d_1_s_118_p_metrics_7) * ((- __f2dace_SOA_wgtfac_e_d_2_s_119_p_metrics_7) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * ((- __f2dace_SOA_wgtfac_e_d_1_s_118_p_metrics_7) + _for_it_11))) - __f2dace_SOA_wgtfac_e_d_0_s_117_p_metrics_7) + _for_it_12)];
                                double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * ((- __f2dace_SOA_vt_d_1_s_86_p_diag_8) + _for_it_11))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_12)];
                                double p_metrics_1_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * __f2dace_SA_wgtfac_e_d_1_s_118_p_metrics_7) * ((- __f2dace_SOA_wgtfac_e_d_2_s_119_p_metrics_7) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 * ((- __f2dace_SOA_wgtfac_e_d_1_s_118_p_metrics_7) + _for_it_11))) - __f2dace_SOA_wgtfac_e_d_0_s_117_p_metrics_7) + _for_it_12)];
                                double p_diag_1_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * (((- __f2dace_SOA_vt_d_1_s_86_p_diag_8) + _for_it_11) - 1))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_12)];
                                double z_vt_ie_out_0;

                                ///////////////////
                                // Tasklet code (T_l363_c363)
                                z_vt_ie_out_0 = ((p_metrics_0_in_wgtfac_e_0 * p_diag_0_in_vt_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_diag_1_in_vt_0));
                                ///////////////////

                                z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_160 * __f2dace_A_z_vt_ie_d_1_s_161) * ((- __f2dace_OA_z_vt_ie_d_2_s_162) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_160 * ((- __f2dace_OA_z_vt_ie_d_1_s_161) + _for_it_11))) - __f2dace_OA_z_vt_ie_d_0_s_160) + _for_it_12)] = z_vt_ie_out_0;
                            }

                        }

                    }

                }
            }
            for (_for_it_13 = nflatlev_jg; (_for_it_13 <= 90); _for_it_13 = (_for_it_13 + 1)) {
                for (_for_it_14 = i_startidx_var_88; (_for_it_14 <= i_endidx_var_89); _for_it_14 = (_for_it_14 + 1)) {
                    {
                        double* v_p_metrics_ddxn_z_full;
                        v_p_metrics_ddxn_z_full = (double*)(&(p_metrics->ddxn_z_full)[0]);
                        double* v_p_metrics_ddxt_z_full;
                        v_p_metrics_ddxt_z_full = (double*)(&(p_metrics->ddxt_z_full)[0]);

                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_13))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_14)];
                            double p_metrics_0_in_ddxn_z_full_0 = v_p_metrics_ddxn_z_full[(((((__f2dace_SA_ddxn_z_full_d_0_s_102_p_metrics_7 * __f2dace_SA_ddxn_z_full_d_1_s_103_p_metrics_7) * ((- __f2dace_SOA_ddxn_z_full_d_2_s_104_p_metrics_7) + _for_it_6)) + (__f2dace_SA_ddxn_z_full_d_0_s_102_p_metrics_7 * ((- __f2dace_SOA_ddxn_z_full_d_1_s_103_p_metrics_7) + _for_it_13))) - __f2dace_SOA_ddxn_z_full_d_0_s_102_p_metrics_7) + _for_it_14)];
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * ((- __f2dace_SOA_vt_d_1_s_86_p_diag_8) + _for_it_13))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_14)];
                            double p_metrics_1_in_ddxt_z_full_0 = v_p_metrics_ddxt_z_full[(((((__f2dace_SA_ddxt_z_full_d_0_s_105_p_metrics_7 * __f2dace_SA_ddxt_z_full_d_1_s_106_p_metrics_7) * ((- __f2dace_SOA_ddxt_z_full_d_2_s_107_p_metrics_7) + _for_it_6)) + (__f2dace_SA_ddxt_z_full_d_0_s_105_p_metrics_7 * ((- __f2dace_SOA_ddxt_z_full_d_1_s_106_p_metrics_7) + _for_it_13))) - __f2dace_SOA_ddxt_z_full_d_0_s_105_p_metrics_7) + _for_it_14)];
                            double z_w_concorr_me_out_0;

                            ///////////////////
                            // Tasklet code (T_l369_c369)
                            z_w_concorr_me_out_0 = ((p_prog_0_in_vn_0 * p_metrics_0_in_ddxn_z_full_0) + (p_diag_0_in_vt_0 * p_metrics_1_in_ddxt_z_full_0));
                            ///////////////////

                            z_w_concorr_me[(((((__f2dace_A_z_w_concorr_me_d_0_s_154 * __f2dace_A_z_w_concorr_me_d_1_s_155) * ((- __f2dace_OA_z_w_concorr_me_d_2_s_156) + _for_it_6)) + (__f2dace_A_z_w_concorr_me_d_0_s_154 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_155) + _for_it_13))) - __f2dace_OA_z_w_concorr_me_d_0_s_154) + _for_it_14)] = z_w_concorr_me_out_0;
                        }

                    }

                }

            }
            if (((1 - 0) == 1)) {
                for (_for_it_15 = i_startidx_var_88; (_for_it_15 <= i_endidx_var_89); _for_it_15 = (_for_it_15 + 1)) {
                    {

                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * (1 - __f2dace_SOA_vn_d_1_s_80_p_prog_6))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_15)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l374_c374)
                            p_diag_out_vn_ie_0 = p_prog_0_in_vn_0;
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * (1 - __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_15)] = p_diag_out_vn_ie_0;
                        }
                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * (1 - __f2dace_SOA_vt_d_1_s_86_p_diag_8))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_15)];
                            double z_vt_ie_out_0;

                            ///////////////////
                            // Tasklet code (T_l375_c375)
                            z_vt_ie_out_0 = p_diag_0_in_vt_0;
                            ///////////////////

                            z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_160 * __f2dace_A_z_vt_ie_d_1_s_161) * ((- __f2dace_OA_z_vt_ie_d_2_s_162) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_160 * (1 - __f2dace_OA_z_vt_ie_d_1_s_161))) - __f2dace_OA_z_vt_ie_d_0_s_160) + _for_it_15)] = z_vt_ie_out_0;
                        }

                    }
                    {
                        double tmp_call_4;
                        double tmp_call_3;

                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * (1 - __f2dace_SOA_vt_d_1_s_86_p_diag_8))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_15)];
                            double tmp_call_4_out;

                            ///////////////////
                            // Tasklet code (T_l376_c376)
                            tmp_call_4_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                            ///////////////////

                            tmp_call_4 = tmp_call_4_out;
                        }
                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * (1 - __f2dace_SOA_vn_d_1_s_80_p_prog_6))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_15)];
                            double tmp_call_3_out;

                            ///////////////////
                            // Tasklet code (T_l376_c376)
                            tmp_call_3_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                            ///////////////////

                            tmp_call_3 = tmp_call_3_out;
                        }
                        {
                            double tmp_call_3_0_in = tmp_call_3;
                            double tmp_call_4_0_in = tmp_call_4;
                            double z_kin_hor_e_out_0;

                            ///////////////////
                            // Tasklet code (T_l376_c376)
                            z_kin_hor_e_out_0 = (0.5 * (tmp_call_3_0_in + tmp_call_4_0_in));
                            ///////////////////

                            z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_157 * __f2dace_A_z_kin_hor_e_d_1_s_158) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_159) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_157 * (1 - __f2dace_OA_z_kin_hor_e_d_1_s_158))) - __f2dace_OA_z_kin_hor_e_d_0_s_157) + _for_it_15)] = z_kin_hor_e_out_0;
                        }

                    }
                    {
                        double* v_p_metrics_wgtfacq_e;
                        v_p_metrics_wgtfacq_e = (double*)(&(p_metrics->wgtfacq_e)[0]);

                        {
                            double p_metrics_0_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7 * __f2dace_SA_wgtfacq_e_d_1_s_121_p_metrics_7) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_122_p_metrics_7) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7 * (1 - __f2dace_SOA_wgtfacq_e_d_1_s_121_p_metrics_7))) - __f2dace_SOA_wgtfacq_e_d_0_s_120_p_metrics_7) + _for_it_15)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * (90 - __f2dace_SOA_vn_d_1_s_80_p_prog_6))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_15)];
                            double p_metrics_1_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7 * __f2dace_SA_wgtfacq_e_d_1_s_121_p_metrics_7) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_122_p_metrics_7) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7 * (2 - __f2dace_SOA_wgtfacq_e_d_1_s_121_p_metrics_7))) - __f2dace_SOA_wgtfacq_e_d_0_s_120_p_metrics_7) + _for_it_15)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * (89 - __f2dace_SOA_vn_d_1_s_80_p_prog_6))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_15)];
                            double p_metrics_2_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7 * __f2dace_SA_wgtfacq_e_d_1_s_121_p_metrics_7) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_122_p_metrics_7) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7 * (3 - __f2dace_SOA_wgtfacq_e_d_1_s_121_p_metrics_7))) - __f2dace_SOA_wgtfacq_e_d_0_s_120_p_metrics_7) + _for_it_15)];
                            double p_prog_2_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * (88 - __f2dace_SOA_vn_d_1_s_80_p_prog_6))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_15)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l377_c377)
                            p_diag_out_vn_ie_0 = (((p_metrics_0_in_wgtfacq_e_0 * p_prog_0_in_vn_0) + (p_metrics_1_in_wgtfacq_e_0 * p_prog_1_in_vn_0)) + (p_metrics_2_in_wgtfacq_e_0 * p_prog_2_in_vn_0));
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * (91 - __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_15)] = p_diag_out_vn_ie_0;
                        }

                    }

                }
            }

        }
    }

    {


    }
    i_startblk_var_86 = v_v_p_patch_edges_start_block[20];

    {


    }
    i_endblk_var_87 = v_v_p_patch_edges_end_block[4];
    _if_cond_14 = (1 - lvn_only);

    if ((_if_cond_14 == 1)) {
        for (_for_it_17 = i_startblk_var_86; (_for_it_17 <= i_endblk_var_87); _for_it_17 = (_for_it_17 + 1)) {
            {


            }
            tmp_call_0_2 = max(1, v_v_p_patch_var_31_edges_start_index[20]);
            if ((_for_it_17 != i_startblk_var_86)) {

                i_startidx_var_88 = 1;

            } else {

                i_startidx_var_88 = tmp_call_0_2;

            }
            if ((_for_it_17 != i_endblk_var_87)) {

                i_endidx_var_89 = 1;

            } else {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_31_edges_end_index[4];

            }
            for (_for_it_18 = 1; (_for_it_18 <= 90); _for_it_18 = (_for_it_18 + 1)) {
                for (_for_it_19 = i_startidx_var_88; (_for_it_19 <= i_endidx_var_89); _for_it_19 = (_for_it_19 + 1)) {
                    {


                    }
                    tmp_index_376 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_17) + _for_it_19) - 33)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_378 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_17) + _for_it_19) - 33)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {


                    }
                    tmp_index_385 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_17) + _for_it_19) + 30687)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                    {


                    }
                    tmp_index_387 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_17) + _for_it_19) + 30687)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                    {


                    }
                    {


                    }
                    tmp_index_403 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_17) + _for_it_19) - 33)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_412 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_17) + _for_it_19) + 30687)] - 1);
                    {
                        double* v_v_p_patch_edges_inv_dual_edge_length;
                        v_v_p_patch_edges_inv_dual_edge_length = (double*)(&((*v_p_patch_edges)->inv_dual_edge_length)[0]);

                        {
                            double p_diag_0_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_17)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * ((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_18))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_19)];
                            double p_patch_0_in_edges_inv_dual_edge_length_0 = v_v_p_patch_edges_inv_dual_edge_length[(((32 * _for_it_17) + _for_it_19) - 33)];
                            double z_vt_ie_0_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_160 * __f2dace_A_z_vt_ie_d_1_s_161) * ((- __f2dace_OA_z_vt_ie_d_2_s_162) + _for_it_17)) + (__f2dace_A_z_vt_ie_d_0_s_160 * ((- __f2dace_OA_z_vt_ie_d_1_s_161) + _for_it_18))) - __f2dace_OA_z_vt_ie_d_0_s_160) + _for_it_19)];
                            double p_patch_1_in_edges_inv_primal_edge_length_0 = v_v_p_patch_edges_inv_primal_edge_length[(((32 * _for_it_17) + _for_it_19) - 33)];
                            double p_patch_2_in_edges_tangent_orientation_0 = v_v_p_patch_edges_tangent_orientation[(((32 * _for_it_17) + _for_it_19) - 33)];
                            double p_prog_0_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_378) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_18))) + tmp_index_376)];
                            double p_prog_1_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_387) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_18))) + tmp_index_385)];
                            double z_w_v_0_in_0 = z_w_v[((_for_it_18 + (91 * tmp_index_403)) - 1)];
                            double z_w_v_1_in_0 = z_w_v[((_for_it_18 + (91 * tmp_index_412)) - 1)];
                            double z_v_grad_w_out_0;

                            ///////////////////
                            // Tasklet code (T_l398_c398)
                            z_v_grad_w_out_0 = (((p_diag_0_in_vn_ie_0 * p_patch_0_in_edges_inv_dual_edge_length_0) * (p_prog_0_in_w_0 - p_prog_1_in_w_0)) + (((z_vt_ie_0_in_0 * p_patch_1_in_edges_inv_primal_edge_length_0) * p_patch_2_in_edges_tangent_orientation_0) * (z_w_v_0_in_0 - z_w_v_1_in_0)));
                            ///////////////////

                            z_v_grad_w[(((90 * _for_it_17) + _for_it_18) - 91)] = z_v_grad_w_out_0;
                        }

                    }

                }

            }

        }
    }
    _if_cond_15 = ((1 - lvn_only) && ldeepatmo);

    if ((_if_cond_15 == 1)) {
        for (_for_it_20 = i_startblk_var_86; (_for_it_20 <= i_endblk_var_87); _for_it_20 = (_for_it_20 + 1)) {
            {


            }
            tmp_call_0_1 = max(1, v_v_p_patch_var_31_edges_start_index[20]);
            if ((_for_it_20 != i_startblk_var_86)) {

                i_startidx_var_88 = 1;

            } else {

                i_startidx_var_88 = tmp_call_0_1;

            }
            if ((_for_it_20 != i_endblk_var_87)) {

                i_endidx_var_89 = 1;

            } else {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_31_edges_end_index[4];

            }
            for (_for_it_21 = 1; (_for_it_21 <= 90); _for_it_21 = (_for_it_21 + 1)) {
                for (_for_it_22 = i_startidx_var_88; (_for_it_22 <= i_endidx_var_89); _for_it_22 = (_for_it_22 + 1)) {
                    {
                        double* v_p_metrics_deepatmo_gradh_ifc;
                        v_p_metrics_deepatmo_gradh_ifc = (double*)(&(p_metrics->deepatmo_gradh_ifc)[0]);
                        double* v_p_metrics_deepatmo_invr_ifc;
                        v_p_metrics_deepatmo_invr_ifc = (double*)(&(p_metrics->deepatmo_invr_ifc)[0]);
                        double* v_v_p_patch_edges_fn_e;
                        v_v_p_patch_edges_fn_e = (double*)(&((*v_p_patch_edges)->fn_e)[0]);

                        {
                            double z_v_grad_w_0_in_0 = z_v_grad_w[(((90 * _for_it_20) + _for_it_21) - 91)];
                            double p_metrics_0_in_deepatmo_gradh_ifc_0 = v_p_metrics_deepatmo_gradh_ifc[((- __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_134_p_metrics_7) + _for_it_21)];
                            double p_diag_0_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_20)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * ((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_21))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_22)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_20)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * ((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_21))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_22)];
                            double p_metrics_1_in_deepatmo_invr_ifc_0 = v_p_metrics_deepatmo_invr_ifc[((- __f2dace_SOA_deepatmo_invr_ifc_d_0_s_135_p_metrics_7) + _for_it_21)];
                            double p_patch_0_in_edges_ft_e_0 = v_v_p_patch_edges_ft_e[(((32 * _for_it_20) + _for_it_22) - 33)];
                            double z_vt_ie_0_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_160 * __f2dace_A_z_vt_ie_d_1_s_161) * ((- __f2dace_OA_z_vt_ie_d_2_s_162) + _for_it_20)) + (__f2dace_A_z_vt_ie_d_0_s_160 * ((- __f2dace_OA_z_vt_ie_d_1_s_161) + _for_it_21))) - __f2dace_OA_z_vt_ie_d_0_s_160) + _for_it_22)];
                            double p_metrics_2_in_deepatmo_invr_ifc_0 = v_p_metrics_deepatmo_invr_ifc[((- __f2dace_SOA_deepatmo_invr_ifc_d_0_s_135_p_metrics_7) + _for_it_21)];
                            double p_patch_1_in_edges_fn_e_0 = v_v_p_patch_edges_fn_e[(((32 * _for_it_20) + _for_it_22) - 33)];
                            double z_vt_ie_1_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_160 * __f2dace_A_z_vt_ie_d_1_s_161) * ((- __f2dace_OA_z_vt_ie_d_2_s_162) + _for_it_20)) + (__f2dace_A_z_vt_ie_d_0_s_160 * ((- __f2dace_OA_z_vt_ie_d_1_s_161) + _for_it_21))) - __f2dace_OA_z_vt_ie_d_0_s_160) + _for_it_22)];
                            double z_v_grad_w_out_0;

                            ///////////////////
                            // Tasklet code (T_l408_c408)
                            z_v_grad_w_out_0 = (((z_v_grad_w_0_in_0 * p_metrics_0_in_deepatmo_gradh_ifc_0) + (p_diag_0_in_vn_ie_0 * ((p_diag_1_in_vn_ie_0 * p_metrics_1_in_deepatmo_invr_ifc_0) - p_patch_0_in_edges_ft_e_0))) + (z_vt_ie_0_in_0 * ((z_vt_ie_1_in_0 * p_metrics_2_in_deepatmo_invr_ifc_0) + p_patch_1_in_edges_fn_e_0)));
                            ///////////////////

                            z_v_grad_w[(((90 * _for_it_20) + _for_it_21) - 91)] = z_v_grad_w_out_0;
                        }

                    }

                }

            }

        }
    }

    {


    }
    i_startblk_var_86 = v_v_p_patch_cells_start_block[12];

    {


    }
    i_endblk_var_87 = v_v_p_patch_cells_end_block[3];

    {


    }
    i_startblk_2 = v_v_p_patch_cells_start_block[13];

    {


    }
    i_endblk_2 = v_v_p_patch_cells_end_block[4];

    for (_for_it_23 = i_startblk_var_86; (_for_it_23 <= i_endblk_var_87); _for_it_23 = (_for_it_23 + 1)) {
        if (((_for_it_23 == i_startblk_var_86) == 1)) {
            {


            }
            i_startidx_var_88 = max(1, v_v_p_patch_var_22_cells_start_index[12]);
            i_endidx_var_89 = 1;
            if (((_for_it_23 == i_endblk_var_87) == 1)) {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_22_cells_end_index[3];

            }
        } else {
            if (((_for_it_23 == i_endblk_var_87) == 1)) {

                i_startidx_var_88 = 1;
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_22_cells_end_index[3];

            } else {

                i_startidx_var_88 = 1;
                i_endidx_var_89 = 1;

            }
        }
        for (_for_it_24 = 1; (_for_it_24 <= 90); _for_it_24 = (_for_it_24 + 1)) {
            for (_for_it_25 = i_startidx_var_88; (_for_it_25 <= i_endidx_var_89); _for_it_25 = (_for_it_25 + 1)) {
                {


                }
                tmp_index_454 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_23) + _for_it_25) - 33)] - __f2dace_OA_z_kin_hor_e_d_0_s_157);
                {


                }
                tmp_index_456 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_25) - 33)] - __f2dace_OA_z_kin_hor_e_d_2_s_159);
                {


                }
                tmp_index_466 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_23) + _for_it_25) + 20447)] - __f2dace_OA_z_kin_hor_e_d_0_s_157);
                {


                }
                tmp_index_468 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_25) + 20447)] - __f2dace_OA_z_kin_hor_e_d_2_s_159);
                {


                }
                tmp_index_478 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_23) + _for_it_25) + 40927)] - __f2dace_OA_z_kin_hor_e_d_0_s_157);
                {


                }
                tmp_index_480 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_25) + 40927)] - __f2dace_OA_z_kin_hor_e_d_2_s_159);
                {

                    {
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_25) - 97)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_25) - 65)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_25) - 33)];
                        double z_kin_hor_e_0_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_157 * __f2dace_A_z_kin_hor_e_d_1_s_158) * tmp_index_456) + (__f2dace_A_z_kin_hor_e_d_0_s_157 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_158) + _for_it_24))) + tmp_index_454)];
                        double z_kin_hor_e_1_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_157 * __f2dace_A_z_kin_hor_e_d_1_s_158) * tmp_index_468) + (__f2dace_A_z_kin_hor_e_d_0_s_157 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_158) + _for_it_24))) + tmp_index_466)];
                        double z_kin_hor_e_2_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_157 * __f2dace_A_z_kin_hor_e_d_1_s_158) * tmp_index_480) + (__f2dace_A_z_kin_hor_e_d_0_s_157 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_158) + _for_it_24))) + tmp_index_478)];
                        double z_ekinh_out_0;

                        ///////////////////
                        // Tasklet code (T_l425_c425)
                        z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_kin_hor_e_2_in_0));
                        ///////////////////

                        z_ekinh[(((90 * _for_it_23) + _for_it_24) - 91)] = z_ekinh_out_0;
                    }

                }

            }

        }
        _if_cond_16 = (istep == 1);
        if ((_if_cond_16 == 1)) {
            for (_for_it_26 = nflatlev_jg; (_for_it_26 <= 90); _for_it_26 = (_for_it_26 + 1)) {
                for (_for_it_27 = i_startidx_var_88; (_for_it_27 <= i_endidx_var_89); _for_it_27 = (_for_it_27 + 1)) {
                    {


                    }
                    tmp_index_492 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_23) + _for_it_27) - 33)] - __f2dace_OA_z_w_concorr_me_d_0_s_154);
                    {


                    }
                    tmp_index_494 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_27) - 33)] - __f2dace_OA_z_w_concorr_me_d_2_s_156);
                    {


                    }
                    tmp_index_504 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_23) + _for_it_27) + 20447)] - __f2dace_OA_z_w_concorr_me_d_0_s_154);
                    {


                    }
                    tmp_index_506 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_27) + 20447)] - __f2dace_OA_z_w_concorr_me_d_2_s_156);
                    {


                    }
                    tmp_index_516 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_23) + _for_it_27) + 40927)] - __f2dace_OA_z_w_concorr_me_d_0_s_154);
                    {


                    }
                    tmp_index_518 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_27) + 40927)] - __f2dace_OA_z_w_concorr_me_d_2_s_156);
                    {

                        {
                            double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_27) - 97)];
                            double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_27) - 65)];
                            double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_27) - 33)];
                            double z_w_concorr_me_0_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_154 * __f2dace_A_z_w_concorr_me_d_1_s_155) * tmp_index_494) + (__f2dace_A_z_w_concorr_me_d_0_s_154 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_155) + _for_it_26))) + tmp_index_492)];
                            double z_w_concorr_me_1_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_154 * __f2dace_A_z_w_concorr_me_d_1_s_155) * tmp_index_506) + (__f2dace_A_z_w_concorr_me_d_0_s_154 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_155) + _for_it_26))) + tmp_index_504)];
                            double z_w_concorr_me_2_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_154 * __f2dace_A_z_w_concorr_me_d_1_s_155) * tmp_index_518) + (__f2dace_A_z_w_concorr_me_d_0_s_154 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_155) + _for_it_26))) + tmp_index_516)];
                            double z_w_concorr_mc_out_0;

                            ///////////////////
                            // Tasklet code (T_l431_c431)
                            z_w_concorr_mc_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_w_concorr_me_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_w_concorr_me_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_w_concorr_me_2_in_0));
                            ///////////////////

                            z_w_concorr_mc[(_for_it_26 - 1)] = z_w_concorr_mc_out_0;
                        }

                    }

                }

            }
            for (_for_it_28 = (nflatlev_jg + 1); (_for_it_28 <= 90); _for_it_28 = (_for_it_28 + 1)) {
                for (_for_it_29 = i_startidx_var_88; (_for_it_29 <= i_endidx_var_89); _for_it_29 = (_for_it_29 + 1)) {
                    {
                        double* v_p_metrics_wgtfac_c;
                        v_p_metrics_wgtfac_c = (double*)(&(p_metrics->wgtfac_c)[0]);

                        {
                            double p_metrics_0_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[(((((__f2dace_SA_wgtfac_c_d_0_s_114_p_metrics_7 * __f2dace_SA_wgtfac_c_d_1_s_115_p_metrics_7) * ((- __f2dace_SOA_wgtfac_c_d_2_s_116_p_metrics_7) + _for_it_23)) + (__f2dace_SA_wgtfac_c_d_0_s_114_p_metrics_7 * ((- __f2dace_SOA_wgtfac_c_d_1_s_115_p_metrics_7) + _for_it_28))) - __f2dace_SOA_wgtfac_c_d_0_s_114_p_metrics_7) + _for_it_29)];
                            double z_w_concorr_mc_0_in_0 = z_w_concorr_mc[(_for_it_28 - 1)];
                            double p_metrics_1_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[(((((__f2dace_SA_wgtfac_c_d_0_s_114_p_metrics_7 * __f2dace_SA_wgtfac_c_d_1_s_115_p_metrics_7) * ((- __f2dace_SOA_wgtfac_c_d_2_s_116_p_metrics_7) + _for_it_23)) + (__f2dace_SA_wgtfac_c_d_0_s_114_p_metrics_7 * ((- __f2dace_SOA_wgtfac_c_d_1_s_115_p_metrics_7) + _for_it_28))) - __f2dace_SOA_wgtfac_c_d_0_s_114_p_metrics_7) + _for_it_29)];
                            double z_w_concorr_mc_1_in_0 = z_w_concorr_mc[(_for_it_28 - 2)];
                            double p_diag_out_w_concorr_c_0;

                            ///////////////////
                            // Tasklet code (T_l436_c436)
                            p_diag_out_w_concorr_c_0 = ((p_metrics_0_in_wgtfac_c_0 * z_w_concorr_mc_0_in_0) + ((1.0 - p_metrics_1_in_wgtfac_c_0) * z_w_concorr_mc_1_in_0));
                            ///////////////////

                            v_p_diag_w_concorr_c[(((((__f2dace_SA_w_concorr_c_d_0_s_91_p_diag_8 * __f2dace_SA_w_concorr_c_d_1_s_92_p_diag_8) * ((- __f2dace_SOA_w_concorr_c_d_2_s_93_p_diag_8) + _for_it_23)) + (__f2dace_SA_w_concorr_c_d_0_s_91_p_diag_8 * ((- __f2dace_SOA_w_concorr_c_d_1_s_92_p_diag_8) + _for_it_28))) - __f2dace_SOA_w_concorr_c_d_0_s_91_p_diag_8) + _for_it_29)] = p_diag_out_w_concorr_c_0;
                        }

                    }

                }

            }
        }
        for (_for_it_30 = 1; (_for_it_30 <= 90); _for_it_30 = (_for_it_30 + 1)) {
            for (_for_it_31 = i_startidx_var_88; (_for_it_31 <= i_endidx_var_89); _for_it_31 = (_for_it_31 + 1)) {
                {

                    {
                        double p_prog_0_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * ((- __f2dace_SOA_w_d_2_s_78_p_prog_6) + _for_it_23)) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_30))) - __f2dace_SOA_w_d_0_s_76_p_prog_6) + _for_it_31)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l442_c442)
                        z_w_con_c_out_0 = p_prog_0_in_w_0;
                        ///////////////////

                        z_w_con_c[(_for_it_30 - 1)] = z_w_con_c_out_0;
                    }

                }

            }

        }
        for (_for_it_32 = i_startidx_var_88; (_for_it_32 <= i_endidx_var_89); _for_it_32 = (_for_it_32 + 1)) {
            {

                {
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l446_c446)
                    z_w_con_c_out_0 = 0.0;
                    ///////////////////

                    z_w_con_c[90] = z_w_con_c_out_0;
                }

            }

        }
        for (_for_it_33 = 90; (_for_it_33 >= (nflatlev_jg + 1)); _for_it_33 = (_for_it_33 + -1)) {
            for (_for_it_34 = i_startidx_var_88; (_for_it_34 <= i_endidx_var_89); _for_it_34 = (_for_it_34 + 1)) {
                {

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(_for_it_33 - 1)];
                        double p_diag_0_in_w_concorr_c_0 = v_p_diag_w_concorr_c[(((((__f2dace_SA_w_concorr_c_d_0_s_91_p_diag_8 * __f2dace_SA_w_concorr_c_d_1_s_92_p_diag_8) * ((- __f2dace_SOA_w_concorr_c_d_2_s_93_p_diag_8) + _for_it_23)) + (__f2dace_SA_w_concorr_c_d_0_s_91_p_diag_8 * ((- __f2dace_SOA_w_concorr_c_d_1_s_92_p_diag_8) + _for_it_33))) - __f2dace_SOA_w_concorr_c_d_0_s_91_p_diag_8) + _for_it_34)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l450_c450)
                        z_w_con_c_out_0 = (z_w_con_c_0_in_0 - p_diag_0_in_w_concorr_c_0);
                        ///////////////////

                        z_w_con_c[(_for_it_33 - 1)] = z_w_con_c_out_0;
                    }

                }

            }

        }
        tmp_arg_4 = (nrdmax_jg - 2);
        for (_for_it_35 = max(3, tmp_arg_4); (_for_it_35 <= (90 - 3)); _for_it_35 = (_for_it_35 + 1)) {
            {

                {
                    int levmask_out_0;

                    ///////////////////
                    // Tasklet code (T_l454_c454)
                    levmask_out_0 = 0;
                    ///////////////////

                    levmask[((_for_it_23 + (640 * _for_it_35)) - 641)] = levmask_out_0;
                }

            }

        }
        tmp_arg_5 = (nrdmax_jg - 2);
        {

            {
                double maxvcfl_out;

                ///////////////////
                // Tasklet code (T_l456_c456)
                maxvcfl_out = 0;
                ///////////////////

                maxvcfl = maxvcfl_out;
            }

        }
        for (_for_it_36 = max(3, tmp_arg_5); (_for_it_36 <= (90 - 3)); _for_it_36 = (_for_it_36 + 1)) {

            clip_count = 0;
            for (_for_it_37 = i_startidx_var_88; (_for_it_37 <= i_endidx_var_89); _for_it_37 = (_for_it_37 + 1)) {
                {
                    double tmp_call_9;

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(_for_it_36 - 1)];
                        double tmp_call_9_out;

                        ///////////////////
                        // Tasklet code (T_l460_c460)
                        tmp_call_9_out = abs(z_w_con_c_0_in_0);
                        ///////////////////

                        tmp_call_9 = tmp_call_9_out;
                    }
                    {
                        double cfl_w_limit_0_in = cfl_w_limit;
                        double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * __f2dace_SA_ddqz_z_half_d_1_s_112_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_113_p_metrics_7) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_112_p_metrics_7) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_111_p_metrics_7) + _for_it_37)];
                        double tmp_call_9_0_in = tmp_call_9;
                        int cfl_clipping_out_0;

                        ///////////////////
                        // Tasklet code (T_l460_c460)
                        cfl_clipping_out_0 = (tmp_call_9_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_half_0));
                        ///////////////////

                        cfl_clipping[(_for_it_36 - 1)] = cfl_clipping_out_0;
                    }
                    {
                        int cfl_clipping_0_in_0 = cfl_clipping[(_for_it_36 - 1)];
                        int _if_cond_17_out;

                        ///////////////////
                        // Tasklet code (T_l461_c461)
                        _if_cond_17_out = cfl_clipping_0_in_0;
                        ///////////////////

                        _if_cond_17 = _if_cond_17_out;
                    }

                }
                if ((_if_cond_17 == 1)) {

                    clip_count = (clip_count + 1);

                }

            }
            if (((clip_count == 0) == 1)) {
                continue;
            }
            for (_for_it_38 = i_startidx_var_88; (_for_it_38 <= i_endidx_var_89); _for_it_38 = (_for_it_38 + 1)) {
                {

                    {
                        int cfl_clipping_0_in_0 = cfl_clipping[(_for_it_36 - 1)];
                        int _if_cond_19_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_19_out = cfl_clipping_0_in_0;
                        ///////////////////

                        _if_cond_19 = _if_cond_19_out;
                    }

                }
                if ((_if_cond_19 == 1)) {
                    {
                        double tmp_call_10;

                        {
                            int levmask_out_0;

                            ///////////////////
                            // Tasklet code (T_l466_c466)
                            levmask_out_0 = 1;
                            ///////////////////

                            levmask[((_for_it_23 + (640 * _for_it_36)) - 641)] = levmask_out_0;
                        }
                        {
                            double dtime_0_in = dtime;
                            double z_w_con_c_0_in_0 = z_w_con_c[(_for_it_36 - 1)];
                            double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * __f2dace_SA_ddqz_z_half_d_1_s_112_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_113_p_metrics_7) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_112_p_metrics_7) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_111_p_metrics_7) + _for_it_38)];
                            double vcfl_out;

                            ///////////////////
                            // Tasklet code (T_l467_c467)
                            vcfl_out = ((z_w_con_c_0_in_0 * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0);
                            ///////////////////

                            vcfl = vcfl_out;
                        }
                        {
                            double vcfl_0_in = vcfl;
                            double tmp_call_10_out;

                            ///////////////////
                            // Tasklet code (T_l468_c468)
                            tmp_call_10_out = abs(vcfl_0_in);
                            ///////////////////

                            tmp_call_10 = tmp_call_10_out;
                        }
                        {
                            double vcfl_0_in = vcfl;
                            int _if_cond_19_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_19_out = (vcfl_0_in < -0.85);
                            ///////////////////

                            _if_cond_19 = _if_cond_19_out;
                        }
                        {
                            double maxvcfl_0_in = maxvcfl;
                            double tmp_call_10_0_in = tmp_call_10;
                            double maxvcfl_out;

                            ///////////////////
                            // Tasklet code (T_l468_c468)
                            maxvcfl_out = max(maxvcfl_0_in, tmp_call_10_0_in);
                            ///////////////////

                            maxvcfl = maxvcfl_out;
                        }

                    }
                    if ((_if_cond_19 == 1)) {
                        {

                            {
                                double dtime_0_in = dtime;
                                double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * __f2dace_SA_ddqz_z_half_d_1_s_112_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_113_p_metrics_7) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_112_p_metrics_7) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_111_p_metrics_7) + _for_it_38)];
                                double z_w_con_c_out_0;

                                ///////////////////
                                // Tasklet code (T_l470_c470)
                                z_w_con_c_out_0 = (- ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in));
                                ///////////////////

                                z_w_con_c[(_for_it_36 - 1)] = z_w_con_c_out_0;
                            }

                        }
                    } else {
                        {

                            {
                                double vcfl_0_in = vcfl;
                                int _if_cond_19_out;

                                ///////////////////
                                // Tasklet code (T_l471_c471)
                                _if_cond_19_out = (vcfl_0_in > 0.85);
                                ///////////////////

                                _if_cond_19 = _if_cond_19_out;
                            }

                        }
                        if ((_if_cond_19 == 1)) {
                            {

                                {
                                    double dtime_0_in = dtime;
                                    double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * __f2dace_SA_ddqz_z_half_d_1_s_112_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_113_p_metrics_7) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_112_p_metrics_7) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_111_p_metrics_7) + _for_it_38)];
                                    double z_w_con_c_out_0;

                                    ///////////////////
                                    // Tasklet code (T_l472_c472)
                                    z_w_con_c_out_0 = ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in);
                                    ///////////////////

                                    z_w_con_c[(_for_it_36 - 1)] = z_w_con_c_out_0;
                                }

                            }
                        }
                    }
                }

            }

        }
        for (_for_it_39 = 1; (_for_it_39 <= 90); _for_it_39 = (_for_it_39 + 1)) {
            for (_for_it_40 = i_startidx_var_88; (_for_it_40 <= i_endidx_var_89); _for_it_40 = (_for_it_40 + 1)) {
                {

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(_for_it_39 - 1)];
                        double z_w_con_c_1_in_0 = z_w_con_c[_for_it_39];
                        double z_w_con_c_full_out_0;

                        ///////////////////
                        // Tasklet code (T_l479_c479)
                        z_w_con_c_full_out_0 = (0.5 * (z_w_con_c_0_in_0 + z_w_con_c_1_in_0));
                        ///////////////////

                        z_w_con_c_full[(((90 * _for_it_23) + _for_it_39) - 91)] = z_w_con_c_full_out_0;
                    }

                }

            }

        }
        {

            {
                double maxvcfl_0_in = maxvcfl;
                double vcflmax_out_0;

                ///////////////////
                // Tasklet code (T_l482_c482)
                vcflmax_out_0 = maxvcfl_0_in;
                ///////////////////

                vcflmax[(_for_it_23 - 1)] = vcflmax_out_0;
            }

        }
        _if_cond_22 = lvn_only;
        if ((_if_cond_22 == 1)) {
            continue;
        }
        if ((((_for_it_23 < i_startblk_2) || (_for_it_23 > i_endblk_2)) == 1)) {
            continue;
        }
        if (((_for_it_23 == i_startblk_2) == 1)) {
            {


            }
            i_startidx_2 = max(1, v_v_p_patch_var_22_cells_start_index[13]);
            i_endidx_2 = 1;
            if (((_for_it_23 == i_endblk_2) == 1)) {
                {


                }
                i_endidx_2 = v_v_p_patch_var_22_cells_end_index[4];

            }
        } else {
            if (((_for_it_23 == i_endblk_2) == 1)) {

                i_startidx_2 = 1;
                {


                }
                i_endidx_2 = v_v_p_patch_var_22_cells_end_index[4];

            } else {

                i_startidx_2 = 1;
                i_endidx_2 = 1;

            }
        }
        for (_for_it_41 = 2; (_for_it_41 <= 90); _for_it_41 = (_for_it_41 + 1)) {
            for (_for_it_42 = i_startidx_2; (_for_it_42 <= i_endidx_2); _for_it_42 = (_for_it_42 + 1)) {

                tmp_index_587 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_101_p_diag_8);
                {
                    double* v_p_metrics_coeff1_dwdz;
                    v_p_metrics_coeff1_dwdz = (double*)(&(p_metrics->coeff1_dwdz)[0]);
                    double* v_p_metrics_coeff2_dwdz;
                    v_p_metrics_coeff2_dwdz = (double*)(&(p_metrics->coeff2_dwdz)[0]);

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(_for_it_41 - 1)];
                        double p_prog_0_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * ((- __f2dace_SOA_w_d_2_s_78_p_prog_6) + _for_it_23)) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * (((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_41) - 1))) - __f2dace_SOA_w_d_0_s_76_p_prog_6) + _for_it_42)];
                        double p_metrics_0_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[(((((__f2dace_SA_coeff1_dwdz_d_0_s_126_p_metrics_7 * __f2dace_SA_coeff1_dwdz_d_1_s_127_p_metrics_7) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_128_p_metrics_7) + _for_it_23)) + (__f2dace_SA_coeff1_dwdz_d_0_s_126_p_metrics_7 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_127_p_metrics_7) + _for_it_41))) - __f2dace_SOA_coeff1_dwdz_d_0_s_126_p_metrics_7) + _for_it_42)];
                        double p_prog_1_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * ((- __f2dace_SOA_w_d_2_s_78_p_prog_6) + _for_it_23)) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * (((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_41) + 1))) - __f2dace_SOA_w_d_0_s_76_p_prog_6) + _for_it_42)];
                        double p_metrics_1_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[(((((__f2dace_SA_coeff2_dwdz_d_0_s_129_p_metrics_7 * __f2dace_SA_coeff2_dwdz_d_1_s_130_p_metrics_7) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_131_p_metrics_7) + _for_it_23)) + (__f2dace_SA_coeff2_dwdz_d_0_s_129_p_metrics_7 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_130_p_metrics_7) + _for_it_41))) - __f2dace_SOA_coeff2_dwdz_d_0_s_129_p_metrics_7) + _for_it_42)];
                        double p_prog_2_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * ((- __f2dace_SOA_w_d_2_s_78_p_prog_6) + _for_it_23)) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_41))) - __f2dace_SOA_w_d_0_s_76_p_prog_6) + _for_it_42)];
                        double p_metrics_2_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[(((((__f2dace_SA_coeff2_dwdz_d_0_s_129_p_metrics_7 * __f2dace_SA_coeff2_dwdz_d_1_s_130_p_metrics_7) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_131_p_metrics_7) + _for_it_23)) + (__f2dace_SA_coeff2_dwdz_d_0_s_129_p_metrics_7 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_130_p_metrics_7) + _for_it_41))) - __f2dace_SOA_coeff2_dwdz_d_0_s_129_p_metrics_7) + _for_it_42)];
                        double p_metrics_3_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[(((((__f2dace_SA_coeff1_dwdz_d_0_s_126_p_metrics_7 * __f2dace_SA_coeff1_dwdz_d_1_s_127_p_metrics_7) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_128_p_metrics_7) + _for_it_23)) + (__f2dace_SA_coeff1_dwdz_d_0_s_126_p_metrics_7 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_127_p_metrics_7) + _for_it_41))) - __f2dace_SOA_coeff1_dwdz_d_0_s_126_p_metrics_7) + _for_it_42)];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l488_c488)
                        p_diag_out_ddt_w_adv_pc_0 = (- (z_w_con_c_0_in_0 * (((p_prog_0_in_w_0 * p_metrics_0_in_coeff1_dwdz_0) - (p_prog_1_in_w_0 * p_metrics_1_in_coeff2_dwdz_0)) + (p_prog_2_in_w_0 * (p_metrics_2_in_coeff2_dwdz_0 - p_metrics_3_in_coeff1_dwdz_0)))));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * __f2dace_SA_ddt_w_adv_pc_d_2_s_100_p_diag_8) * tmp_index_587) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_100_p_diag_8) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_99_p_diag_8) + _for_it_41))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_98_p_diag_8) + _for_it_42)] = p_diag_out_ddt_w_adv_pc_0;
                    }

                }

            }

        }
        for (_for_it_43 = 2; (_for_it_43 <= 90); _for_it_43 = (_for_it_43 + 1)) {
            for (_for_it_44 = i_startidx_2; (_for_it_44 <= i_endidx_2); _for_it_44 = (_for_it_44 + 1)) {

                tmp_index_614 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_101_p_diag_8);
                tmp_index_618 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_101_p_diag_8);
                {


                }
                {


                }
                tmp_index_630 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_44) - 33)] - 1);
                {


                }
                {


                }
                tmp_index_642 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_44) + 20447)] - 1);
                {


                }
                {


                }
                tmp_index_654 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_23) + _for_it_44) + 40927)] - 1);
                {

                    {
                        double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * __f2dace_SA_ddt_w_adv_pc_d_2_s_100_p_diag_8) * tmp_index_618) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_100_p_diag_8) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_99_p_diag_8) + _for_it_43))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_98_p_diag_8) + _for_it_44)];
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_44) - 97)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_44) - 65)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_23) + _for_it_44) - 33)];
                        double z_v_grad_w_0_in_0 = z_v_grad_w[((_for_it_43 + (90 * tmp_index_630)) - 1)];
                        double z_v_grad_w_1_in_0 = z_v_grad_w[((_for_it_43 + (90 * tmp_index_642)) - 1)];
                        double z_v_grad_w_2_in_0 = z_v_grad_w[((_for_it_43 + (90 * tmp_index_654)) - 1)];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l493_c493)
                        p_diag_out_ddt_w_adv_pc_0 = (((p_diag_0_in_ddt_w_adv_pc_0 + (p_int_0_in_e_bln_c_s_0 * z_v_grad_w_0_in_0)) + (p_int_1_in_e_bln_c_s_0 * z_v_grad_w_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_v_grad_w_2_in_0));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * __f2dace_SA_ddt_w_adv_pc_d_2_s_100_p_diag_8) * tmp_index_614) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_100_p_diag_8) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_99_p_diag_8) + _for_it_43))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_98_p_diag_8) + _for_it_44)] = p_diag_out_ddt_w_adv_pc_0;
                    }

                }

            }

        }
        {

            {
                int global_data_0_in_lextra_diffu = v_global_data_lextra_diffu[0];
                int _if_cond_24_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_24_out = global_data_0_in_lextra_diffu;
                ///////////////////

                _if_cond_24 = _if_cond_24_out;
            }

        }
        if ((_if_cond_24 == 1)) {

            tmp_arg_6 = (nrdmax_jg - 2);
            for (_for_it_45 = max(3, tmp_arg_6); (_for_it_45 <= (90 - 3)); _for_it_45 = (_for_it_45 + 1)) {
                {

                    {
                        int levmask_0_in_0 = levmask[((_for_it_23 + (640 * _for_it_45)) - 641)];
                        int _if_cond_24_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_24_out = levmask_0_in_0;
                        ///////////////////

                        _if_cond_24 = _if_cond_24_out;
                    }

                }
                if ((_if_cond_24 == 1)) {
                    for (_for_it_46 = i_startidx_2; (_for_it_46 <= i_endidx_2); _for_it_46 = (_for_it_46 + 1)) {
                        {
                            t_grid_domain_decomp_info** v_v_p_patch_cells_decomp_info;
                            v_v_p_patch_cells_decomp_info = (t_grid_domain_decomp_info**)(&((*v_p_patch_cells)->decomp_info));
                            int* v_v_v_p_patch_cells_decomp_info_owner_mask;
                            v_v_v_p_patch_cells_decomp_info_owner_mask = (int*)(&((*v_v_p_patch_cells_decomp_info)->owner_mask)[0]);

                            {
                                int cfl_clipping_0_in_0 = cfl_clipping[(_for_it_45 - 1)];
                                int p_patch_0_in_cells_decomp_info_owner_mask_0 = v_v_v_p_patch_cells_decomp_info_owner_mask[(((32 * _for_it_23) + _for_it_46) - 33)];
                                int _if_cond_24_out;

                                ///////////////////
                                // Tasklet code (T_l0_c0)
                                _if_cond_24_out = (cfl_clipping_0_in_0 && p_patch_0_in_cells_decomp_info_owner_mask_0);
                                ///////////////////

                                _if_cond_24 = _if_cond_24_out;
                            }

                        }
                        if ((_if_cond_24 == 1)) {

                            tmp_index_669 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_101_p_diag_8);
                            tmp_index_673 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_101_p_diag_8);
                            {

                                {
                                    double z_w_con_c_0_in_0 = z_w_con_c[(_for_it_45 - 1)];
                                    double tmp_call_13_out;

                                    ///////////////////
                                    // Tasklet code (T_l501_c501)
                                    tmp_call_13_out = abs(z_w_con_c_0_in_0);
                                    ///////////////////

                                    tmp_call_13 = tmp_call_13_out;
                                }

                            }
                            tmp_index_688 = (v_v_p_patch_cells_neighbor_idx[(((32 * _for_it_23) + _for_it_46) - 33)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                            {
                                double tmp_call_12;
                                double tmp_arg_7;
                                double tmp_arg_8;

                                {
                                    double tmp_call_13_0_in = tmp_call_13;
                                    double dtime_0_in = dtime;
                                    double cfl_w_limit_0_in = cfl_w_limit;
                                    double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * __f2dace_SA_ddqz_z_half_d_1_s_112_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_113_p_metrics_7) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_112_p_metrics_7) + _for_it_45))) - __f2dace_SOA_ddqz_z_half_d_0_s_111_p_metrics_7) + _for_it_46)];
                                    double dtime_1_in = dtime;
                                    double tmp_arg_8_out;

                                    ///////////////////
                                    // Tasklet code (T_l501_c501)
                                    tmp_arg_8_out = (((tmp_call_13_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0) - (cfl_w_limit_0_in * dtime_1_in));
                                    ///////////////////

                                    tmp_arg_8 = tmp_arg_8_out;
                                }
                                {
                                    double cfl_w_limit_0_in = cfl_w_limit;
                                    double dtime_0_in = dtime;
                                    double tmp_arg_7_out;

                                    ///////////////////
                                    // Tasklet code (T_l501_c501)
                                    tmp_arg_7_out = (0.85 - (cfl_w_limit_0_in * dtime_0_in));
                                    ///////////////////

                                    tmp_arg_7 = tmp_arg_7_out;
                                }
                                {
                                    double tmp_arg_7_0_in = tmp_arg_7;
                                    double tmp_arg_8_0_in = tmp_arg_8;
                                    double tmp_call_12_out;

                                    ///////////////////
                                    // Tasklet code (T_l501_c501)
                                    tmp_call_12_out = min(tmp_arg_7_0_in, tmp_arg_8_0_in);
                                    ///////////////////

                                    tmp_call_12 = tmp_call_12_out;
                                }
                                {
                                    double scalfac_exdiff_0_in = scalfac_exdiff;
                                    double tmp_call_12_0_in = tmp_call_12;
                                    double difcoef_out;

                                    ///////////////////
                                    // Tasklet code (T_l501_c501)
                                    difcoef_out = (scalfac_exdiff_0_in * tmp_call_12_0_in);
                                    ///////////////////

                                    difcoef = difcoef_out;
                                }

                            }
                            tmp_index_690 = (v_v_p_patch_cells_neighbor_blk[(((32 * _for_it_23) + _for_it_46) - 33)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                            {


                            }
                            tmp_index_700 = (v_v_p_patch_cells_neighbor_idx[(((32 * _for_it_23) + _for_it_46) + 20447)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                            {


                            }
                            tmp_index_702 = (v_v_p_patch_cells_neighbor_blk[(((32 * _for_it_23) + _for_it_46) + 20447)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                            {


                            }
                            tmp_index_712 = (v_v_p_patch_cells_neighbor_idx[(((32 * _for_it_23) + _for_it_46) + 40927)] - __f2dace_SOA_w_d_0_s_76_p_prog_6);
                            {


                            }
                            tmp_index_714 = (v_v_p_patch_cells_neighbor_blk[(((32 * _for_it_23) + _for_it_46) + 40927)] - __f2dace_SOA_w_d_2_s_78_p_prog_6);
                            {
                                double* v_p_int_geofac_n2s;
                                v_p_int_geofac_n2s = (double*)(&(p_int->geofac_n2s)[0]);
                                double* v_v_p_patch_cells_area;
                                v_v_p_patch_cells_area = (double*)(&((*v_p_patch_cells)->area)[0]);

                                {
                                    double difcoef_0_in = difcoef;
                                    double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * __f2dace_SA_ddt_w_adv_pc_d_2_s_100_p_diag_8) * tmp_index_673) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_100_p_diag_8) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_99_p_diag_8) + _for_it_45))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_98_p_diag_8) + _for_it_46)];
                                    double p_patch_0_in_cells_area_0 = v_v_p_patch_cells_area[(((__f2dace_SA_area_d_0_s_2_cells_p_patch_1 * ((- __f2dace_SOA_area_d_1_s_3_cells_p_patch_1) + _for_it_23)) - __f2dace_SOA_area_d_0_s_2_cells_p_patch_1) + _for_it_46)];
                                    double p_prog_0_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * ((- __f2dace_SOA_w_d_2_s_78_p_prog_6) + _for_it_23)) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_45))) - __f2dace_SOA_w_d_0_s_76_p_prog_6) + _for_it_46)];
                                    double p_int_0_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_23) + _for_it_46) - 129)];
                                    double p_int_1_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_23) + _for_it_46) - 97)];
                                    double p_int_2_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_23) + _for_it_46) - 65)];
                                    double p_int_3_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_23) + _for_it_46) - 33)];
                                    double p_prog_1_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_690) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_45))) + tmp_index_688)];
                                    double p_prog_2_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_702) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_45))) + tmp_index_700)];
                                    double p_prog_3_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_76_p_prog_6 * __f2dace_SA_w_d_1_s_77_p_prog_6) * tmp_index_714) + (__f2dace_SA_w_d_0_s_76_p_prog_6 * ((- __f2dace_SOA_w_d_1_s_77_p_prog_6) + _for_it_45))) + tmp_index_712)];
                                    double p_diag_out_ddt_w_adv_pc_0;

                                    ///////////////////
                                    // Tasklet code (T_l502_c502)
                                    p_diag_out_ddt_w_adv_pc_0 = (p_diag_0_in_ddt_w_adv_pc_0 + ((difcoef_0_in * p_patch_0_in_cells_area_0) * ((((p_prog_0_in_w_0 * p_int_0_in_geofac_n2s_0) + (p_prog_1_in_w_0 * p_int_1_in_geofac_n2s_0)) + (p_prog_2_in_w_0 * p_int_2_in_geofac_n2s_0)) + (p_prog_3_in_w_0 * p_int_3_in_geofac_n2s_0))));
                                    ///////////////////

                                    v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * __f2dace_SA_ddt_w_adv_pc_d_2_s_100_p_diag_8) * tmp_index_669) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_100_p_diag_8) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_99_p_diag_8) + _for_it_45))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_98_p_diag_8) + _for_it_46)] = p_diag_out_ddt_w_adv_pc_0;
                                }

                            }
                        }

                    }
                }

            }
        }

    }
    tmp_arg_9 = (nrdmax_jg - 2);

    for (_for_it_47 = max(3, tmp_arg_9); (_for_it_47 <= (90 - 3)); _for_it_47 = (_for_it_47 + 1)) {

        tmp_call_15 = 0;
        for (tmp_parfor_0 = i_startblk_var_86; (tmp_parfor_0 <= i_endblk_var_87); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
            if ((levmask[(((640 * _for_it_47) + tmp_parfor_0) - 641)] == 1)) {

                tmp_call_15 = 1;

            }

        }
        {

            {
                int levelmask_out_0;

                ///////////////////
                // Tasklet code (T_l510_c510)
                levelmask_out_0 = tmp_call_15;
                ///////////////////

                levelmask[(_for_it_47 - 1)] = levelmask_out_0;
            }

        }

    }

    {


    }
    i_startblk_var_86 = v_v_p_patch_edges_start_block[23];

    {


    }
    i_endblk_var_87 = v_v_p_patch_edges_end_block[5];

    for (_for_it_48 = i_startblk_var_86; (_for_it_48 <= i_endblk_var_87); _for_it_48 = (_for_it_48 + 1)) {
        {


        }
        tmp_call_0_0 = max(1, v_v_p_patch_var_31_edges_start_index[23]);
        if ((_for_it_48 != i_startblk_var_86)) {

            i_startidx_var_88 = 1;

        } else {

            i_startidx_var_88 = tmp_call_0_0;

        }
        if ((_for_it_48 != i_endblk_var_87)) {

            i_endidx_var_89 = 1;

        } else {
            {


            }
            i_endidx_var_89 = v_v_p_patch_var_31_edges_end_index[5];

        }
        _if_cond_27 = (1 - ldeepatmo);
        if ((_if_cond_27 == 1)) {
            for (_for_it_49 = 1; (_for_it_49 <= 90); _for_it_49 = (_for_it_49 + 1)) {
                for (_for_it_50 = i_startidx_var_88; (_for_it_50 <= i_endidx_var_89); _for_it_50 = (_for_it_50 + 1)) {

                    tmp_index_726 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_97_p_diag_8);
                    {


                    }
                    {


                    }
                    tmp_index_747 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_50) + 30687)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_759 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_50) - 33)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_773 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_48) + _for_it_50) - 33)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_782 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_48) + _for_it_50) + 30687)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_794 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_50) - 33)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_806 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_50) + 30687)] - 1);
                    {

                        {
                            double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_157 * __f2dace_A_z_kin_hor_e_d_1_s_158) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_159) + _for_it_48)) + (__f2dace_A_z_kin_hor_e_d_0_s_157 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_158) + _for_it_49))) - __f2dace_OA_z_kin_hor_e_d_0_s_157) + _for_it_50)];
                            double p_metrics_0_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_50)];
                            double p_metrics_1_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_50)];
                            double p_metrics_2_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_50)];
                            double p_metrics_3_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_50)];
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_48)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * ((- __f2dace_SOA_vt_d_1_s_86_p_diag_8) + _for_it_49))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_50)];
                            double p_patch_0_in_edges_f_e_0 = v_v_p_patch_edges_f_e[(((32 * _for_it_48) + _for_it_50) - 33)];
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_48) + _for_it_50) - 65)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_48) + _for_it_50) - 33)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * ((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_49))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_50)];
                            double p_diag_2_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * (((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_49) + 1))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_50)];
                            double p_metrics_4_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * __f2dace_SA_ddqz_z_full_e_d_1_s_109_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_110_p_metrics_7) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_109_p_metrics_7) + _for_it_49))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_108_p_metrics_7) + _for_it_50)];
                            double z_ekinh_0_in_0 = z_ekinh[((_for_it_49 + (90 * tmp_index_747)) - 1)];
                            double z_ekinh_1_in_0 = z_ekinh[((_for_it_49 + (90 * tmp_index_759)) - 1)];
                            double zeta_0_in_0 = zeta[((_for_it_49 + (90 * tmp_index_773)) - 1)];
                            double zeta_1_in_0 = zeta[((_for_it_49 + (90 * tmp_index_782)) - 1)];
                            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((_for_it_49 + (90 * tmp_index_794)) - 1)];
                            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((_for_it_49 + (90 * tmp_index_806)) - 1)];
                            double p_diag_out_ddt_vn_apc_pc_0;

                            ///////////////////
                            // Tasklet code (T_l521_c521)
                            p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
                            ///////////////////

                            v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) * tmp_index_726) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) + _for_it_49))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_94_p_diag_8) + _for_it_50)] = p_diag_out_ddt_vn_apc_pc_0;
                        }

                    }

                }

            }
        } else {
            for (_for_it_51 = 1; (_for_it_51 <= 90); _for_it_51 = (_for_it_51 + 1)) {
                for (_for_it_52 = i_startidx_var_88; (_for_it_52 <= i_endidx_var_89); _for_it_52 = (_for_it_52 + 1)) {

                    tmp_index_819 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_97_p_diag_8);
                    {


                    }
                    {


                    }
                    tmp_index_840 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_52) + 30687)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_852 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_52) - 33)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_867 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_48) + _for_it_52) - 33)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_876 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_48) + _for_it_52) + 30687)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_889 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_52) - 33)] - 1);
                    {


                    }
                    {


                    }
                    tmp_index_901 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_52) + 30687)] - 1);
                    {
                        double* v_p_metrics_deepatmo_gradh_mc;
                        v_p_metrics_deepatmo_gradh_mc = (double*)(&(p_metrics->deepatmo_gradh_mc)[0]);
                        double* v_p_metrics_deepatmo_invr_mc;
                        v_p_metrics_deepatmo_invr_mc = (double*)(&(p_metrics->deepatmo_invr_mc)[0]);

                        {
                            double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_157 * __f2dace_A_z_kin_hor_e_d_1_s_158) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_159) + _for_it_48)) + (__f2dace_A_z_kin_hor_e_d_0_s_157 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_158) + _for_it_51))) - __f2dace_OA_z_kin_hor_e_d_0_s_157) + _for_it_52)];
                            double p_metrics_0_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_52)];
                            double p_metrics_1_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_52)];
                            double p_metrics_2_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_52)];
                            double p_metrics_3_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7))) - __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7) + _for_it_52)];
                            double p_metrics_4_in_deepatmo_gradh_mc_0 = v_p_metrics_deepatmo_gradh_mc[((- __f2dace_SOA_deepatmo_gradh_mc_d_0_s_132_p_metrics_7) + _for_it_51)];
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_85_p_diag_8 * __f2dace_SA_vt_d_1_s_86_p_diag_8) * ((- __f2dace_SOA_vt_d_2_s_87_p_diag_8) + _for_it_48)) + (__f2dace_SA_vt_d_0_s_85_p_diag_8 * ((- __f2dace_SOA_vt_d_1_s_86_p_diag_8) + _for_it_51))) - __f2dace_SOA_vt_d_0_s_85_p_diag_8) + _for_it_52)];
                            double p_patch_0_in_edges_f_e_0 = v_v_p_patch_edges_f_e[(((32 * _for_it_48) + _for_it_52) - 33)];
                            double p_metrics_5_in_deepatmo_gradh_mc_0 = v_p_metrics_deepatmo_gradh_mc[((- __f2dace_SOA_deepatmo_gradh_mc_d_0_s_132_p_metrics_7) + _for_it_51)];
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_48) + _for_it_52) - 65)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_48) + _for_it_52) - 33)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * ((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_51))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_52)];
                            double p_diag_2_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * __f2dace_SA_vn_ie_d_1_s_89_p_diag_8) * ((- __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_88_p_diag_8 * (((- __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8) + _for_it_51) + 1))) - __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8) + _for_it_52)];
                            double p_metrics_6_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * __f2dace_SA_ddqz_z_full_e_d_1_s_109_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_110_p_metrics_7) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_109_p_metrics_7) + _for_it_51))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_108_p_metrics_7) + _for_it_52)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_48)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_51))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_52)];
                            double p_metrics_7_in_deepatmo_invr_mc_0 = v_p_metrics_deepatmo_invr_mc[((- __f2dace_SOA_deepatmo_invr_mc_d_0_s_133_p_metrics_7) + _for_it_51)];
                            double p_patch_1_in_edges_ft_e_0 = v_v_p_patch_edges_ft_e[(((32 * _for_it_48) + _for_it_52) - 33)];
                            double z_ekinh_0_in_0 = z_ekinh[((_for_it_51 + (90 * tmp_index_840)) - 1)];
                            double z_ekinh_1_in_0 = z_ekinh[((_for_it_51 + (90 * tmp_index_852)) - 1)];
                            double zeta_0_in_0 = zeta[((_for_it_51 + (90 * tmp_index_867)) - 1)];
                            double zeta_1_in_0 = zeta[((_for_it_51 + (90 * tmp_index_876)) - 1)];
                            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((_for_it_51 + (90 * tmp_index_889)) - 1)];
                            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((_for_it_51 + (90 * tmp_index_901)) - 1)];
                            double p_diag_out_ddt_vn_apc_pc_0;

                            ///////////////////
                            // Tasklet code (T_l534_c534)
                            p_diag_out_ddt_vn_apc_pc_0 = (- ((((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) * p_metrics_4_in_deepatmo_gradh_mc_0) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + ((0.5 * (zeta_0_in_0 + zeta_1_in_0)) * p_metrics_5_in_deepatmo_gradh_mc_0)))) + (((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * ((((p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0) / p_metrics_6_in_ddqz_z_full_e_0) + (p_prog_0_in_vn_0 * p_metrics_7_in_deepatmo_invr_mc_0)) - p_patch_1_in_edges_ft_e_0))));
                            ///////////////////

                            v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) * tmp_index_819) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) + _for_it_51))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_94_p_diag_8) + _for_it_52)] = p_diag_out_ddt_vn_apc_pc_0;
                        }

                    }

                }

            }
        }
        {

            {
                int global_data_0_in_lextra_diffu = v_global_data_lextra_diffu[0];
                int _if_cond_28_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_28_out = global_data_0_in_lextra_diffu;
                ///////////////////

                _if_cond_28 = _if_cond_28_out;
            }

        }
        if ((_if_cond_28 == 1)) {

            tmp_arg_10 = (nrdmax_jg - 2);
            for (_for_it_53 = max(3, tmp_arg_10); (_for_it_53 <= (90 - 4)); _for_it_53 = (_for_it_53 + 1)) {
                {

                    {
                        int levelmask_0_in_0 = levelmask[(_for_it_53 - 1)];
                        int levelmask_1_in_0 = levelmask[_for_it_53];
                        int _if_cond_28_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_28_out = (levelmask_0_in_0 || levelmask_1_in_0);
                        ///////////////////

                        _if_cond_28 = _if_cond_28_out;
                    }

                }
                if ((_if_cond_28 == 1)) {
                    for (_for_it_54 = i_startidx_var_88; (_for_it_54 <= i_endidx_var_89); _for_it_54 = (_for_it_54 + 1)) {
                        {


                        }
                        {


                        }
                        tmp_index_930 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_54) - 33)] - 1);
                        {


                        }
                        {


                        }
                        tmp_index_942 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_48) + _for_it_54) + 30687)] - 1);
                        {
                            double tmp_call_17;

                            {
                                double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_48) + _for_it_54) - 65)];
                                double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_48) + _for_it_54) - 33)];
                                double z_w_con_c_full_0_in_0 = z_w_con_c_full[((_for_it_53 + (90 * tmp_index_930)) - 1)];
                                double z_w_con_c_full_1_in_0 = z_w_con_c_full[((_for_it_53 + (90 * tmp_index_942)) - 1)];
                                double w_con_e_out;

                                ///////////////////
                                // Tasklet code (T_l550_c550)
                                w_con_e_out = ((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0));
                                ///////////////////

                                w_con_e = w_con_e_out;
                            }
                            {
                                double w_con_e_0_in = w_con_e;
                                double tmp_call_17_out;

                                ///////////////////
                                // Tasklet code (T_l0_c0)
                                tmp_call_17_out = abs(w_con_e_0_in);
                                ///////////////////

                                tmp_call_17 = tmp_call_17_out;
                            }
                            {
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * __f2dace_SA_ddqz_z_full_e_d_1_s_109_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_110_p_metrics_7) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_109_p_metrics_7) + _for_it_53))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_108_p_metrics_7) + _for_it_54)];
                                double tmp_call_17_0_in = tmp_call_17;
                                int _if_cond_28_out;

                                ///////////////////
                                // Tasklet code (T_l0_c0)
                                _if_cond_28_out = (tmp_call_17_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_full_e_0));
                                ///////////////////

                                _if_cond_28 = _if_cond_28_out;
                            }

                        }
                        if ((_if_cond_28 == 1)) {
                            {

                                {
                                    double w_con_e_0_in = w_con_e;
                                    double tmp_call_19_out;

                                    ///////////////////
                                    // Tasklet code (T_l552_c552)
                                    tmp_call_19_out = abs(w_con_e_0_in);
                                    ///////////////////

                                    tmp_call_19 = tmp_call_19_out;
                                }

                            }
                            tmp_index_952 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_97_p_diag_8);
                            tmp_index_956 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_97_p_diag_8);
                            {


                            }
                            tmp_index_974 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_48) + _for_it_54) - 33)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                            {
                                double tmp_call_18;
                                double tmp_arg_11;
                                double tmp_arg_12;

                                {
                                    double tmp_call_19_0_in = tmp_call_19;
                                    double dtime_0_in = dtime;
                                    double cfl_w_limit_0_in = cfl_w_limit;
                                    double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * __f2dace_SA_ddqz_z_full_e_d_1_s_109_p_metrics_7) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_110_p_metrics_7) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_109_p_metrics_7) + _for_it_53))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_108_p_metrics_7) + _for_it_54)];
                                    double dtime_1_in = dtime;
                                    double tmp_arg_12_out;

                                    ///////////////////
                                    // Tasklet code (T_l552_c552)
                                    tmp_arg_12_out = (((tmp_call_19_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_full_e_0) - (cfl_w_limit_0_in * dtime_1_in));
                                    ///////////////////

                                    tmp_arg_12 = tmp_arg_12_out;
                                }
                                {
                                    double cfl_w_limit_0_in = cfl_w_limit;
                                    double dtime_0_in = dtime;
                                    double tmp_arg_11_out;

                                    ///////////////////
                                    // Tasklet code (T_l552_c552)
                                    tmp_arg_11_out = (0.85 - (cfl_w_limit_0_in * dtime_0_in));
                                    ///////////////////

                                    tmp_arg_11 = tmp_arg_11_out;
                                }
                                {
                                    double tmp_arg_11_0_in = tmp_arg_11;
                                    double tmp_arg_12_0_in = tmp_arg_12;
                                    double tmp_call_18_out;

                                    ///////////////////
                                    // Tasklet code (T_l552_c552)
                                    tmp_call_18_out = min(tmp_arg_11_0_in, tmp_arg_12_0_in);
                                    ///////////////////

                                    tmp_call_18 = tmp_call_18_out;
                                }
                                {
                                    double scalfac_exdiff_0_in = scalfac_exdiff;
                                    double tmp_call_18_0_in = tmp_call_18;
                                    double difcoef_out;

                                    ///////////////////
                                    // Tasklet code (T_l552_c552)
                                    difcoef_out = (scalfac_exdiff_0_in * tmp_call_18_0_in);
                                    ///////////////////

                                    difcoef = difcoef_out;
                                }

                            }
                            tmp_index_976 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_48) + _for_it_54) - 33)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                            {


                            }
                            tmp_index_986 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_48) + _for_it_54) + 30687)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                            {


                            }
                            tmp_index_988 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_48) + _for_it_54) + 30687)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                            {


                            }
                            tmp_index_998 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_48) + _for_it_54) + 61407)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                            {


                            }
                            tmp_index_1000 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_48) + _for_it_54) + 61407)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                            {


                            }
                            tmp_index_1010 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_48) + _for_it_54) + 92127)] - __f2dace_SOA_vn_d_0_s_79_p_prog_6);
                            {


                            }
                            tmp_index_1012 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_48) + _for_it_54) + 92127)] - __f2dace_SOA_vn_d_2_s_81_p_prog_6);
                            {


                            }
                            {


                            }
                            tmp_index_1025 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_48) + _for_it_54) + 30687)] - 1);
                            {


                            }
                            {


                            }
                            tmp_index_1034 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_48) + _for_it_54) - 33)] - 1);
                            {
                                double* v_p_int_geofac_grdiv;
                                v_p_int_geofac_grdiv = (double*)(&(p_int->geofac_grdiv)[0]);
                                double* v_v_p_patch_edges_area_edge;
                                v_v_p_patch_edges_area_edge = (double*)(&((*v_p_patch_edges)->area_edge)[0]);

                                {
                                    double difcoef_0_in = difcoef;
                                    double p_diag_0_in_ddt_vn_apc_pc_0 = v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) * tmp_index_956) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) + _for_it_53))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_94_p_diag_8) + _for_it_54)];
                                    double p_patch_0_in_edges_area_edge_0 = v_v_p_patch_edges_area_edge[(((32 * _for_it_48) + _for_it_54) - 33)];
                                    double p_int_0_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_48) + _for_it_54) - 161)];
                                    double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * ((- __f2dace_SOA_vn_d_2_s_81_p_prog_6) + _for_it_48)) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_53))) - __f2dace_SOA_vn_d_0_s_79_p_prog_6) + _for_it_54)];
                                    double p_int_1_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_48) + _for_it_54) - 129)];
                                    double p_int_2_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_48) + _for_it_54) - 97)];
                                    double p_int_3_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_48) + _for_it_54) - 65)];
                                    double p_int_4_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_48) + _for_it_54) - 33)];
                                    double p_patch_1_in_edges_tangent_orientation_0 = v_v_p_patch_edges_tangent_orientation[(((32 * _for_it_48) + _for_it_54) - 33)];
                                    double p_patch_2_in_edges_inv_primal_edge_length_0 = v_v_p_patch_edges_inv_primal_edge_length[(((32 * _for_it_48) + _for_it_54) - 33)];
                                    double p_prog_1_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_976) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_53))) + tmp_index_974)];
                                    double p_prog_2_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_988) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_53))) + tmp_index_986)];
                                    double p_prog_3_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_1000) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_53))) + tmp_index_998)];
                                    double p_prog_4_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_79_p_prog_6 * __f2dace_SA_vn_d_1_s_80_p_prog_6) * tmp_index_1012) + (__f2dace_SA_vn_d_0_s_79_p_prog_6 * ((- __f2dace_SOA_vn_d_1_s_80_p_prog_6) + _for_it_53))) + tmp_index_1010)];
                                    double zeta_0_in_0 = zeta[((_for_it_53 + (90 * tmp_index_1025)) - 1)];
                                    double zeta_1_in_0 = zeta[((_for_it_53 + (90 * tmp_index_1034)) - 1)];
                                    double p_diag_out_ddt_vn_apc_pc_0;

                                    ///////////////////
                                    // Tasklet code (T_l553_c553)
                                    p_diag_out_ddt_vn_apc_pc_0 = (p_diag_0_in_ddt_vn_apc_pc_0 + ((difcoef_0_in * p_patch_0_in_edges_area_edge_0) * ((((((p_int_0_in_geofac_grdiv_0 * p_prog_0_in_vn_0) + (p_int_1_in_geofac_grdiv_0 * p_prog_1_in_vn_0)) + (p_int_2_in_geofac_grdiv_0 * p_prog_2_in_vn_0)) + (p_int_3_in_geofac_grdiv_0 * p_prog_3_in_vn_0)) + (p_int_4_in_geofac_grdiv_0 * p_prog_4_in_vn_0)) + ((p_patch_1_in_edges_tangent_orientation_0 * p_patch_2_in_edges_inv_primal_edge_length_0) * (zeta_0_in_0 - zeta_1_in_0)))));
                                    ///////////////////

                                    v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) * tmp_index_952) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_96_p_diag_8) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_95_p_diag_8) + _for_it_53))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_94_p_diag_8) + _for_it_54)] = p_diag_out_ddt_vn_apc_pc_0;
                                }

                            }
                        }

                    }
                }

            }
        }

    }

    {


    }
    i_startblk_var_86 = v_v_p_patch_cells_start_block[12];

    {


    }
    i_endblk_var_87 = v_v_p_patch_cells_end_block[4];
    tmp_call_20 = -1.7976931348623157e+308;

    for (tmp_parfor_0 = i_startblk_var_86; (tmp_parfor_0 <= i_endblk_var_87); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
        if ((vcflmax[(tmp_parfor_0 - 1)] > tmp_call_20)) {

            tmp_call_20 = vcflmax[(tmp_parfor_0 - 1)];

        }

    }

    {
        double max_vcfl_dyn_var_94;
        double* v_p_diag_max_vcfl_dyn;
        v_p_diag_max_vcfl_dyn = (double*)(&(p_diag->max_vcfl_dyn));

        {
            double max_vcfl_dyn_var_94_out;

            ///////////////////
            // Tasklet code (T_l562_c562)
            max_vcfl_dyn_var_94_out = max(0.0, tmp_call_20);
            ///////////////////

            max_vcfl_dyn_var_94 = max_vcfl_dyn_var_94_out;
        }
        {
            double max_vcfl_dyn_var_94_0_in = max_vcfl_dyn_var_94;
            double p_diag_out_max_vcfl_dyn;

            ///////////////////
            // Tasklet code (T_l563_c563)
            p_diag_out_max_vcfl_dyn = max_vcfl_dyn_var_94_0_in;
            ///////////////////

            v_p_diag_max_vcfl_dyn[0] = p_diag_out_max_vcfl_dyn;
        }

    }

    delete[] z_w_concorr_mc;
    delete[] z_w_con_c;
    delete[] z_w_con_c_full;
    delete[] z_v_grad_w;
    delete[] z_w_v;
    delete[] zeta;
    delete[] z_ekinh;
    delete[] vcflmax;
    delete[] levmask;
    delete[] levelmask;
    delete[] cfl_clipping;
}

DACE_EXPORTED void __program_velocity_tendencies(velocity_tendencies_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_157, int __f2dace_A_z_kin_hor_e_d_1_s_158, int __f2dace_A_z_vt_ie_d_0_s_160, int __f2dace_A_z_vt_ie_d_1_s_161, int __f2dace_A_z_w_concorr_me_d_0_s_154, int __f2dace_A_z_w_concorr_me_d_1_s_155, int __f2dace_OA_z_kin_hor_e_d_0_s_157, int __f2dace_OA_z_kin_hor_e_d_1_s_158, int __f2dace_OA_z_kin_hor_e_d_2_s_159, int __f2dace_OA_z_vt_ie_d_0_s_160, int __f2dace_OA_z_vt_ie_d_1_s_161, int __f2dace_OA_z_vt_ie_d_2_s_162, int __f2dace_OA_z_w_concorr_me_d_0_s_154, int __f2dace_OA_z_w_concorr_me_d_1_s_155, int __f2dace_OA_z_w_concorr_me_d_2_s_156, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    __program_velocity_tendencies_internal(__state, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s_157, __f2dace_A_z_kin_hor_e_d_1_s_158, __f2dace_A_z_vt_ie_d_0_s_160, __f2dace_A_z_vt_ie_d_1_s_161, __f2dace_A_z_w_concorr_me_d_0_s_154, __f2dace_A_z_w_concorr_me_d_1_s_155, __f2dace_OA_z_kin_hor_e_d_0_s_157, __f2dace_OA_z_kin_hor_e_d_1_s_158, __f2dace_OA_z_kin_hor_e_d_2_s_159, __f2dace_OA_z_vt_ie_d_0_s_160, __f2dace_OA_z_vt_ie_d_1_s_161, __f2dace_OA_z_vt_ie_d_2_s_162, __f2dace_OA_z_w_concorr_me_d_0_s_154, __f2dace_OA_z_w_concorr_me_d_1_s_155, __f2dace_OA_z_w_concorr_me_d_2_s_156, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
}

DACE_EXPORTED velocity_tendencies_state_t *__dace_init_velocity_tendencies(global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_157, int __f2dace_A_z_kin_hor_e_d_1_s_158, int __f2dace_A_z_vt_ie_d_0_s_160, int __f2dace_A_z_vt_ie_d_1_s_161, int __f2dace_A_z_w_concorr_me_d_0_s_154, int __f2dace_A_z_w_concorr_me_d_1_s_155, int __f2dace_OA_z_kin_hor_e_d_0_s_157, int __f2dace_OA_z_kin_hor_e_d_1_s_158, int __f2dace_OA_z_kin_hor_e_d_2_s_159, int __f2dace_OA_z_vt_ie_d_0_s_160, int __f2dace_OA_z_vt_ie_d_1_s_161, int __f2dace_OA_z_vt_ie_d_2_s_162, int __f2dace_OA_z_w_concorr_me_d_0_s_154, int __f2dace_OA_z_w_concorr_me_d_1_s_155, int __f2dace_OA_z_w_concorr_me_d_2_s_156, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int __result = 0;
    velocity_tendencies_state_t *__state = new velocity_tendencies_state_t;


    __f2dace_SOA_area_d_0_s_2_cells_p_patch_1 = p_patch->cells->__f2dace_SOA_area_d_0_s_2;
    __f2dace_SOA_area_d_1_s_3_cells_p_patch_1 = p_patch->cells->__f2dace_SOA_area_d_1_s_3;
    __f2dace_SA_area_d_0_s_2_cells_p_patch_1 = p_patch->cells->__f2dace_SA_area_d_0_s_2;
    __f2dace_SA_area_d_1_s_3_cells_p_patch_1 = p_patch->cells->__f2dace_SA_area_d_1_s_3;
    __f2dace_SOA_w_d_0_s_76_p_prog_6 = p_prog->__f2dace_SOA_w_d_0_s_76;
    __f2dace_SOA_w_d_1_s_77_p_prog_6 = p_prog->__f2dace_SOA_w_d_1_s_77;
    __f2dace_SOA_w_d_2_s_78_p_prog_6 = p_prog->__f2dace_SOA_w_d_2_s_78;
    __f2dace_SA_w_d_0_s_76_p_prog_6 = p_prog->__f2dace_SA_w_d_0_s_76;
    __f2dace_SA_w_d_1_s_77_p_prog_6 = p_prog->__f2dace_SA_w_d_1_s_77;
    __f2dace_SA_w_d_2_s_78_p_prog_6 = p_prog->__f2dace_SA_w_d_2_s_78;
    __f2dace_SOA_vn_d_0_s_79_p_prog_6 = p_prog->__f2dace_SOA_vn_d_0_s_79;
    __f2dace_SOA_vn_d_1_s_80_p_prog_6 = p_prog->__f2dace_SOA_vn_d_1_s_80;
    __f2dace_SOA_vn_d_2_s_81_p_prog_6 = p_prog->__f2dace_SOA_vn_d_2_s_81;
    __f2dace_SA_vn_d_0_s_79_p_prog_6 = p_prog->__f2dace_SA_vn_d_0_s_79;
    __f2dace_SA_vn_d_1_s_80_p_prog_6 = p_prog->__f2dace_SA_vn_d_1_s_80;
    __f2dace_SA_vn_d_2_s_81_p_prog_6 = p_prog->__f2dace_SA_vn_d_2_s_81;
    __f2dace_SOA_ddxn_z_full_d_0_s_102_p_metrics_7 = p_metrics->__f2dace_SOA_ddxn_z_full_d_0_s_102;
    __f2dace_SOA_ddxn_z_full_d_1_s_103_p_metrics_7 = p_metrics->__f2dace_SOA_ddxn_z_full_d_1_s_103;
    __f2dace_SOA_ddxn_z_full_d_2_s_104_p_metrics_7 = p_metrics->__f2dace_SOA_ddxn_z_full_d_2_s_104;
    __f2dace_SA_ddxn_z_full_d_0_s_102_p_metrics_7 = p_metrics->__f2dace_SA_ddxn_z_full_d_0_s_102;
    __f2dace_SA_ddxn_z_full_d_1_s_103_p_metrics_7 = p_metrics->__f2dace_SA_ddxn_z_full_d_1_s_103;
    __f2dace_SA_ddxn_z_full_d_2_s_104_p_metrics_7 = p_metrics->__f2dace_SA_ddxn_z_full_d_2_s_104;
    __f2dace_SOA_ddxt_z_full_d_0_s_105_p_metrics_7 = p_metrics->__f2dace_SOA_ddxt_z_full_d_0_s_105;
    __f2dace_SOA_ddxt_z_full_d_1_s_106_p_metrics_7 = p_metrics->__f2dace_SOA_ddxt_z_full_d_1_s_106;
    __f2dace_SOA_ddxt_z_full_d_2_s_107_p_metrics_7 = p_metrics->__f2dace_SOA_ddxt_z_full_d_2_s_107;
    __f2dace_SA_ddxt_z_full_d_0_s_105_p_metrics_7 = p_metrics->__f2dace_SA_ddxt_z_full_d_0_s_105;
    __f2dace_SA_ddxt_z_full_d_1_s_106_p_metrics_7 = p_metrics->__f2dace_SA_ddxt_z_full_d_1_s_106;
    __f2dace_SA_ddxt_z_full_d_2_s_107_p_metrics_7 = p_metrics->__f2dace_SA_ddxt_z_full_d_2_s_107;
    __f2dace_SOA_ddqz_z_full_e_d_0_s_108_p_metrics_7 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_0_s_108;
    __f2dace_SOA_ddqz_z_full_e_d_1_s_109_p_metrics_7 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_1_s_109;
    __f2dace_SOA_ddqz_z_full_e_d_2_s_110_p_metrics_7 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_2_s_110;
    __f2dace_SA_ddqz_z_full_e_d_0_s_108_p_metrics_7 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_0_s_108;
    __f2dace_SA_ddqz_z_full_e_d_1_s_109_p_metrics_7 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_1_s_109;
    __f2dace_SA_ddqz_z_full_e_d_2_s_110_p_metrics_7 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_2_s_110;
    __f2dace_SOA_ddqz_z_half_d_0_s_111_p_metrics_7 = p_metrics->__f2dace_SOA_ddqz_z_half_d_0_s_111;
    __f2dace_SOA_ddqz_z_half_d_1_s_112_p_metrics_7 = p_metrics->__f2dace_SOA_ddqz_z_half_d_1_s_112;
    __f2dace_SOA_ddqz_z_half_d_2_s_113_p_metrics_7 = p_metrics->__f2dace_SOA_ddqz_z_half_d_2_s_113;
    __f2dace_SA_ddqz_z_half_d_0_s_111_p_metrics_7 = p_metrics->__f2dace_SA_ddqz_z_half_d_0_s_111;
    __f2dace_SA_ddqz_z_half_d_1_s_112_p_metrics_7 = p_metrics->__f2dace_SA_ddqz_z_half_d_1_s_112;
    __f2dace_SA_ddqz_z_half_d_2_s_113_p_metrics_7 = p_metrics->__f2dace_SA_ddqz_z_half_d_2_s_113;
    __f2dace_SOA_wgtfac_c_d_0_s_114_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfac_c_d_0_s_114;
    __f2dace_SOA_wgtfac_c_d_1_s_115_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfac_c_d_1_s_115;
    __f2dace_SOA_wgtfac_c_d_2_s_116_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfac_c_d_2_s_116;
    __f2dace_SA_wgtfac_c_d_0_s_114_p_metrics_7 = p_metrics->__f2dace_SA_wgtfac_c_d_0_s_114;
    __f2dace_SA_wgtfac_c_d_1_s_115_p_metrics_7 = p_metrics->__f2dace_SA_wgtfac_c_d_1_s_115;
    __f2dace_SA_wgtfac_c_d_2_s_116_p_metrics_7 = p_metrics->__f2dace_SA_wgtfac_c_d_2_s_116;
    __f2dace_SOA_wgtfac_e_d_0_s_117_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfac_e_d_0_s_117;
    __f2dace_SOA_wgtfac_e_d_1_s_118_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfac_e_d_1_s_118;
    __f2dace_SOA_wgtfac_e_d_2_s_119_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfac_e_d_2_s_119;
    __f2dace_SA_wgtfac_e_d_0_s_117_p_metrics_7 = p_metrics->__f2dace_SA_wgtfac_e_d_0_s_117;
    __f2dace_SA_wgtfac_e_d_1_s_118_p_metrics_7 = p_metrics->__f2dace_SA_wgtfac_e_d_1_s_118;
    __f2dace_SA_wgtfac_e_d_2_s_119_p_metrics_7 = p_metrics->__f2dace_SA_wgtfac_e_d_2_s_119;
    __f2dace_SOA_wgtfacq_e_d_0_s_120_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfacq_e_d_0_s_120;
    __f2dace_SOA_wgtfacq_e_d_1_s_121_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfacq_e_d_1_s_121;
    __f2dace_SOA_wgtfacq_e_d_2_s_122_p_metrics_7 = p_metrics->__f2dace_SOA_wgtfacq_e_d_2_s_122;
    __f2dace_SA_wgtfacq_e_d_0_s_120_p_metrics_7 = p_metrics->__f2dace_SA_wgtfacq_e_d_0_s_120;
    __f2dace_SA_wgtfacq_e_d_1_s_121_p_metrics_7 = p_metrics->__f2dace_SA_wgtfacq_e_d_1_s_121;
    __f2dace_SA_wgtfacq_e_d_2_s_122_p_metrics_7 = p_metrics->__f2dace_SA_wgtfacq_e_d_2_s_122;
    __f2dace_SOA_coeff_gradekin_d_0_s_123_p_metrics_7 = p_metrics->__f2dace_SOA_coeff_gradekin_d_0_s_123;
    __f2dace_SOA_coeff_gradekin_d_1_s_124_p_metrics_7 = p_metrics->__f2dace_SOA_coeff_gradekin_d_1_s_124;
    __f2dace_SOA_coeff_gradekin_d_2_s_125_p_metrics_7 = p_metrics->__f2dace_SOA_coeff_gradekin_d_2_s_125;
    __f2dace_SA_coeff_gradekin_d_0_s_123_p_metrics_7 = p_metrics->__f2dace_SA_coeff_gradekin_d_0_s_123;
    __f2dace_SA_coeff_gradekin_d_1_s_124_p_metrics_7 = p_metrics->__f2dace_SA_coeff_gradekin_d_1_s_124;
    __f2dace_SA_coeff_gradekin_d_2_s_125_p_metrics_7 = p_metrics->__f2dace_SA_coeff_gradekin_d_2_s_125;
    __f2dace_SOA_coeff1_dwdz_d_0_s_126_p_metrics_7 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_0_s_126;
    __f2dace_SOA_coeff1_dwdz_d_1_s_127_p_metrics_7 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_1_s_127;
    __f2dace_SOA_coeff1_dwdz_d_2_s_128_p_metrics_7 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_2_s_128;
    __f2dace_SA_coeff1_dwdz_d_0_s_126_p_metrics_7 = p_metrics->__f2dace_SA_coeff1_dwdz_d_0_s_126;
    __f2dace_SA_coeff1_dwdz_d_1_s_127_p_metrics_7 = p_metrics->__f2dace_SA_coeff1_dwdz_d_1_s_127;
    __f2dace_SA_coeff1_dwdz_d_2_s_128_p_metrics_7 = p_metrics->__f2dace_SA_coeff1_dwdz_d_2_s_128;
    __f2dace_SOA_coeff2_dwdz_d_0_s_129_p_metrics_7 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_0_s_129;
    __f2dace_SOA_coeff2_dwdz_d_1_s_130_p_metrics_7 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_1_s_130;
    __f2dace_SOA_coeff2_dwdz_d_2_s_131_p_metrics_7 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_2_s_131;
    __f2dace_SA_coeff2_dwdz_d_0_s_129_p_metrics_7 = p_metrics->__f2dace_SA_coeff2_dwdz_d_0_s_129;
    __f2dace_SA_coeff2_dwdz_d_1_s_130_p_metrics_7 = p_metrics->__f2dace_SA_coeff2_dwdz_d_1_s_130;
    __f2dace_SA_coeff2_dwdz_d_2_s_131_p_metrics_7 = p_metrics->__f2dace_SA_coeff2_dwdz_d_2_s_131;
    __f2dace_SOA_deepatmo_gradh_mc_d_0_s_132_p_metrics_7 = p_metrics->__f2dace_SOA_deepatmo_gradh_mc_d_0_s_132;
    __f2dace_SA_deepatmo_gradh_mc_d_0_s_132_p_metrics_7 = p_metrics->__f2dace_SA_deepatmo_gradh_mc_d_0_s_132;
    __f2dace_SOA_deepatmo_invr_mc_d_0_s_133_p_metrics_7 = p_metrics->__f2dace_SOA_deepatmo_invr_mc_d_0_s_133;
    __f2dace_SA_deepatmo_invr_mc_d_0_s_133_p_metrics_7 = p_metrics->__f2dace_SA_deepatmo_invr_mc_d_0_s_133;
    __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_134_p_metrics_7 = p_metrics->__f2dace_SOA_deepatmo_gradh_ifc_d_0_s_134;
    __f2dace_SA_deepatmo_gradh_ifc_d_0_s_134_p_metrics_7 = p_metrics->__f2dace_SA_deepatmo_gradh_ifc_d_0_s_134;
    __f2dace_SOA_deepatmo_invr_ifc_d_0_s_135_p_metrics_7 = p_metrics->__f2dace_SOA_deepatmo_invr_ifc_d_0_s_135;
    __f2dace_SA_deepatmo_invr_ifc_d_0_s_135_p_metrics_7 = p_metrics->__f2dace_SA_deepatmo_invr_ifc_d_0_s_135;
    __f2dace_SOA_vn_ie_ubc_d_0_s_82_p_diag_8 = p_diag->__f2dace_SOA_vn_ie_ubc_d_0_s_82;
    __f2dace_SOA_vn_ie_ubc_d_1_s_83_p_diag_8 = p_diag->__f2dace_SOA_vn_ie_ubc_d_1_s_83;
    __f2dace_SOA_vn_ie_ubc_d_2_s_84_p_diag_8 = p_diag->__f2dace_SOA_vn_ie_ubc_d_2_s_84;
    __f2dace_SA_vn_ie_ubc_d_0_s_82_p_diag_8 = p_diag->__f2dace_SA_vn_ie_ubc_d_0_s_82;
    __f2dace_SA_vn_ie_ubc_d_1_s_83_p_diag_8 = p_diag->__f2dace_SA_vn_ie_ubc_d_1_s_83;
    __f2dace_SA_vn_ie_ubc_d_2_s_84_p_diag_8 = p_diag->__f2dace_SA_vn_ie_ubc_d_2_s_84;
    __f2dace_SOA_vt_d_0_s_85_p_diag_8 = p_diag->__f2dace_SOA_vt_d_0_s_85;
    __f2dace_SOA_vt_d_1_s_86_p_diag_8 = p_diag->__f2dace_SOA_vt_d_1_s_86;
    __f2dace_SOA_vt_d_2_s_87_p_diag_8 = p_diag->__f2dace_SOA_vt_d_2_s_87;
    __f2dace_SA_vt_d_0_s_85_p_diag_8 = p_diag->__f2dace_SA_vt_d_0_s_85;
    __f2dace_SA_vt_d_1_s_86_p_diag_8 = p_diag->__f2dace_SA_vt_d_1_s_86;
    __f2dace_SA_vt_d_2_s_87_p_diag_8 = p_diag->__f2dace_SA_vt_d_2_s_87;
    __f2dace_SOA_vn_ie_d_0_s_88_p_diag_8 = p_diag->__f2dace_SOA_vn_ie_d_0_s_88;
    __f2dace_SOA_vn_ie_d_1_s_89_p_diag_8 = p_diag->__f2dace_SOA_vn_ie_d_1_s_89;
    __f2dace_SOA_vn_ie_d_2_s_90_p_diag_8 = p_diag->__f2dace_SOA_vn_ie_d_2_s_90;
    __f2dace_SA_vn_ie_d_0_s_88_p_diag_8 = p_diag->__f2dace_SA_vn_ie_d_0_s_88;
    __f2dace_SA_vn_ie_d_1_s_89_p_diag_8 = p_diag->__f2dace_SA_vn_ie_d_1_s_89;
    __f2dace_SA_vn_ie_d_2_s_90_p_diag_8 = p_diag->__f2dace_SA_vn_ie_d_2_s_90;
    __f2dace_SOA_w_concorr_c_d_0_s_91_p_diag_8 = p_diag->__f2dace_SOA_w_concorr_c_d_0_s_91;
    __f2dace_SOA_w_concorr_c_d_1_s_92_p_diag_8 = p_diag->__f2dace_SOA_w_concorr_c_d_1_s_92;
    __f2dace_SOA_w_concorr_c_d_2_s_93_p_diag_8 = p_diag->__f2dace_SOA_w_concorr_c_d_2_s_93;
    __f2dace_SA_w_concorr_c_d_0_s_91_p_diag_8 = p_diag->__f2dace_SA_w_concorr_c_d_0_s_91;
    __f2dace_SA_w_concorr_c_d_1_s_92_p_diag_8 = p_diag->__f2dace_SA_w_concorr_c_d_1_s_92;
    __f2dace_SA_w_concorr_c_d_2_s_93_p_diag_8 = p_diag->__f2dace_SA_w_concorr_c_d_2_s_93;
    __f2dace_SOA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_0_s_94;
    __f2dace_SOA_ddt_vn_apc_pc_d_1_s_95_p_diag_8 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_1_s_95;
    __f2dace_SOA_ddt_vn_apc_pc_d_2_s_96_p_diag_8 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_2_s_96;
    __f2dace_SOA_ddt_vn_apc_pc_d_3_s_97_p_diag_8 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_3_s_97;
    __f2dace_SA_ddt_vn_apc_pc_d_0_s_94_p_diag_8 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_0_s_94;
    __f2dace_SA_ddt_vn_apc_pc_d_1_s_95_p_diag_8 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_1_s_95;
    __f2dace_SA_ddt_vn_apc_pc_d_2_s_96_p_diag_8 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_2_s_96;
    __f2dace_SA_ddt_vn_apc_pc_d_3_s_97_p_diag_8 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_3_s_97;
    __f2dace_SOA_ddt_w_adv_pc_d_0_s_98_p_diag_8 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_0_s_98;
    __f2dace_SOA_ddt_w_adv_pc_d_1_s_99_p_diag_8 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_1_s_99;
    __f2dace_SOA_ddt_w_adv_pc_d_2_s_100_p_diag_8 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_2_s_100;
    __f2dace_SOA_ddt_w_adv_pc_d_3_s_101_p_diag_8 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_3_s_101;
    __f2dace_SA_ddt_w_adv_pc_d_0_s_98_p_diag_8 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_0_s_98;
    __f2dace_SA_ddt_w_adv_pc_d_1_s_99_p_diag_8 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_1_s_99;
    __f2dace_SA_ddt_w_adv_pc_d_2_s_100_p_diag_8 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_2_s_100;
    __f2dace_SA_ddt_w_adv_pc_d_3_s_101_p_diag_8 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_3_s_101;

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_velocity_tendencies(velocity_tendencies_state_t *__state)
{
    int __err = 0;
    delete __state;
    return __err;
}

/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

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

struct t_nh_prog {
    int __f2dace_SA_vn_d_0_s_94 = {};
    int __f2dace_SA_vn_d_1_s_95 = {};
    int __f2dace_SA_vn_d_2_s_96 = {};
    int __f2dace_SA_w_d_0_s_91 = {};
    int __f2dace_SA_w_d_1_s_92 = {};
    int __f2dace_SA_w_d_2_s_93 = {};
    int __f2dace_SOA_vn_d_0_s_94 = {};
    int __f2dace_SOA_vn_d_1_s_95 = {};
    int __f2dace_SOA_vn_d_2_s_96 = {};
    int __f2dace_SOA_w_d_0_s_91 = {};
    int __f2dace_SOA_w_d_1_s_92 = {};
    int __f2dace_SOA_w_d_2_s_93 = {};
    double* vn = {};
    double* w = {};
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

struct global_data_type {
    int* nflatlev = {};
    int* nrdmax = {};
};

struct t_nh_metrics {
    int __f2dace_SA_coeff1_dwdz_d_0_s_138 = {};
    int __f2dace_SA_coeff1_dwdz_d_1_s_139 = {};
    int __f2dace_SA_coeff1_dwdz_d_2_s_140 = {};
    int __f2dace_SA_coeff2_dwdz_d_0_s_141 = {};
    int __f2dace_SA_coeff2_dwdz_d_1_s_142 = {};
    int __f2dace_SA_coeff2_dwdz_d_2_s_143 = {};
    int __f2dace_SA_coeff_gradekin_d_0_s_135 = {};
    int __f2dace_SA_coeff_gradekin_d_1_s_136 = {};
    int __f2dace_SA_coeff_gradekin_d_2_s_137 = {};
    int __f2dace_SA_ddqz_z_full_e_d_0_s_120 = {};
    int __f2dace_SA_ddqz_z_full_e_d_1_s_121 = {};
    int __f2dace_SA_ddqz_z_full_e_d_2_s_122 = {};
    int __f2dace_SA_ddqz_z_half_d_0_s_123 = {};
    int __f2dace_SA_ddqz_z_half_d_1_s_124 = {};
    int __f2dace_SA_ddqz_z_half_d_2_s_125 = {};
    int __f2dace_SA_ddxn_z_full_d_0_s_114 = {};
    int __f2dace_SA_ddxn_z_full_d_1_s_115 = {};
    int __f2dace_SA_ddxn_z_full_d_2_s_116 = {};
    int __f2dace_SA_ddxt_z_full_d_0_s_117 = {};
    int __f2dace_SA_ddxt_z_full_d_1_s_118 = {};
    int __f2dace_SA_ddxt_z_full_d_2_s_119 = {};
    int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_146 = {};
    int __f2dace_SA_deepatmo_gradh_mc_d_0_s_144 = {};
    int __f2dace_SA_deepatmo_invr_ifc_d_0_s_147 = {};
    int __f2dace_SA_deepatmo_invr_mc_d_0_s_145 = {};
    int __f2dace_SA_wgtfac_c_d_0_s_126 = {};
    int __f2dace_SA_wgtfac_c_d_1_s_127 = {};
    int __f2dace_SA_wgtfac_c_d_2_s_128 = {};
    int __f2dace_SA_wgtfac_e_d_0_s_129 = {};
    int __f2dace_SA_wgtfac_e_d_1_s_130 = {};
    int __f2dace_SA_wgtfac_e_d_2_s_131 = {};
    int __f2dace_SA_wgtfacq_e_d_0_s_132 = {};
    int __f2dace_SA_wgtfacq_e_d_1_s_133 = {};
    int __f2dace_SA_wgtfacq_e_d_2_s_134 = {};
    int __f2dace_SOA_coeff1_dwdz_d_0_s_138 = {};
    int __f2dace_SOA_coeff1_dwdz_d_1_s_139 = {};
    int __f2dace_SOA_coeff1_dwdz_d_2_s_140 = {};
    int __f2dace_SOA_coeff2_dwdz_d_0_s_141 = {};
    int __f2dace_SOA_coeff2_dwdz_d_1_s_142 = {};
    int __f2dace_SOA_coeff2_dwdz_d_2_s_143 = {};
    int __f2dace_SOA_coeff_gradekin_d_0_s_135 = {};
    int __f2dace_SOA_coeff_gradekin_d_1_s_136 = {};
    int __f2dace_SOA_coeff_gradekin_d_2_s_137 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_0_s_120 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_1_s_121 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_2_s_122 = {};
    int __f2dace_SOA_ddqz_z_half_d_0_s_123 = {};
    int __f2dace_SOA_ddqz_z_half_d_1_s_124 = {};
    int __f2dace_SOA_ddqz_z_half_d_2_s_125 = {};
    int __f2dace_SOA_ddxn_z_full_d_0_s_114 = {};
    int __f2dace_SOA_ddxn_z_full_d_1_s_115 = {};
    int __f2dace_SOA_ddxn_z_full_d_2_s_116 = {};
    int __f2dace_SOA_ddxt_z_full_d_0_s_117 = {};
    int __f2dace_SOA_ddxt_z_full_d_1_s_118 = {};
    int __f2dace_SOA_ddxt_z_full_d_2_s_119 = {};
    int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_146 = {};
    int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_144 = {};
    int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_147 = {};
    int __f2dace_SOA_deepatmo_invr_mc_d_0_s_145 = {};
    int __f2dace_SOA_wgtfac_c_d_0_s_126 = {};
    int __f2dace_SOA_wgtfac_c_d_1_s_127 = {};
    int __f2dace_SOA_wgtfac_c_d_2_s_128 = {};
    int __f2dace_SOA_wgtfac_e_d_0_s_129 = {};
    int __f2dace_SOA_wgtfac_e_d_1_s_130 = {};
    int __f2dace_SOA_wgtfac_e_d_2_s_131 = {};
    int __f2dace_SOA_wgtfacq_e_d_0_s_132 = {};
    int __f2dace_SOA_wgtfacq_e_d_1_s_133 = {};
    int __f2dace_SOA_wgtfacq_e_d_2_s_134 = {};
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

struct t_nh_diag {
    int __f2dace_SA_ddt_vn_apc_pc_d_0_s_106 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_1_s_107 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_2_s_108 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_3_s_109 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_0_s_110 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_1_s_111 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_2_s_112 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_3_s_113 = {};
    int __f2dace_SA_vn_ie_d_0_s_100 = {};
    int __f2dace_SA_vn_ie_d_1_s_101 = {};
    int __f2dace_SA_vn_ie_d_2_s_102 = {};
    int __f2dace_SA_vt_d_0_s_97 = {};
    int __f2dace_SA_vt_d_1_s_98 = {};
    int __f2dace_SA_vt_d_2_s_99 = {};
    int __f2dace_SA_w_concorr_c_d_0_s_103 = {};
    int __f2dace_SA_w_concorr_c_d_1_s_104 = {};
    int __f2dace_SA_w_concorr_c_d_2_s_105 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_106 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_107 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_108 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_109 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_0_s_110 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_1_s_111 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_2_s_112 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_3_s_113 = {};
    int __f2dace_SOA_vn_ie_d_0_s_100 = {};
    int __f2dace_SOA_vn_ie_d_1_s_101 = {};
    int __f2dace_SOA_vn_ie_d_2_s_102 = {};
    int __f2dace_SOA_vt_d_0_s_97 = {};
    int __f2dace_SOA_vt_d_1_s_98 = {};
    int __f2dace_SOA_vt_d_2_s_99 = {};
    int __f2dace_SOA_w_concorr_c_d_0_s_103 = {};
    int __f2dace_SOA_w_concorr_c_d_1_s_104 = {};
    int __f2dace_SOA_w_concorr_c_d_2_s_105 = {};
    double* ddt_vn_apc_pc = {};
    double* ddt_w_adv_pc = {};
    double max_vcfl_dyn = {};
    double* vn_ie = {};
    double* vt = {};
    double* w_concorr_c = {};
};

struct velocity_tendencies_state_t {

};

void __program_velocity_tendencies_internal(velocity_tendencies_state_t*__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_151, int __f2dace_A_z_kin_hor_e_d_1_s_152, int __f2dace_A_z_vt_ie_d_0_s_154, int __f2dace_A_z_vt_ie_d_1_s_155, int __f2dace_A_z_w_concorr_me_d_0_s_148, int __f2dace_A_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_kin_hor_e_d_0_s_151, int __f2dace_OA_z_kin_hor_e_d_1_s_152, int __f2dace_OA_z_kin_hor_e_d_2_s_153, int __f2dace_OA_z_vt_ie_d_0_s_154, int __f2dace_OA_z_vt_ie_d_1_s_155, int __f2dace_OA_z_vt_ie_d_2_s_156, int __f2dace_OA_z_w_concorr_me_d_0_s_148, int __f2dace_OA_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_w_concorr_me_d_2_s_150, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    double *z_w_concorr_mc;
    z_w_concorr_mc = new double DACE_ALIGN(64)[2880];
    double *z_w_con_c;
    z_w_con_c = new double DACE_ALIGN(64)[2912];
    double *z_w_con_c_full;
    z_w_con_c_full = new double DACE_ALIGN(64)[1843200];
    double *z_v_grad_w;
    z_v_grad_w = new double DACE_ALIGN(64)[2764800];
    double *z_w_v;
    z_w_v = new double DACE_ALIGN(64)[934752];
    double *zeta;
    zeta = new double DACE_ALIGN(64)[924480];
    double *z_ekinh;
    z_ekinh = new double DACE_ALIGN(64)[1843200];
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
    cfl_clipping = new int DACE_ALIGN(64)[2912];
    double tmp_call_2;
    double tmp_call_11;
    double tmp_call_17;
    int _if_cond_12;
    int _if_cond_14;
    int _if_cond_22;
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
    int* v_v_p_patch_edges_vertex_idx;
    v_v_p_patch_edges_vertex_idx = (int*)(&((*v_p_patch_edges)->vertex_idx)[0]);
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
    t_grid_domain_decomp_info** v_v_p_patch_cells_decomp_info;
    v_v_p_patch_cells_decomp_info = (t_grid_domain_decomp_info**)(&((*v_p_patch_cells)->decomp_info));
    int* v_v_p_patch_cells_neighbor_idx;
    v_v_p_patch_cells_neighbor_idx = (int*)(&((*v_p_patch_cells)->neighbor_idx)[0]);
    int* v_v_p_patch_cells_neighbor_blk;
    v_v_p_patch_cells_neighbor_blk = (int*)(&((*v_p_patch_cells)->neighbor_blk)[0]);
    double* v_v_p_patch_edges_f_e;
    v_v_p_patch_edges_f_e = (double*)(&((*v_p_patch_edges)->f_e)[0]);
    int* v_v_v_p_patch_cells_decomp_info_owner_mask;
    v_v_v_p_patch_cells_decomp_info_owner_mask = (int*)(&((*v_v_p_patch_cells_decomp_info)->owner_mask)[0]);
    t_patch** p_patch_var_32_3;
    p_patch_var_32_3 = &p_patch;
    t_grid_edges** v_p_patch_var_32_edges;
    v_p_patch_var_32_edges = (t_grid_edges**)(&((*p_patch_var_32_3)->edges));
    int* v_v_p_patch_var_32_edges_start_index;
    v_v_p_patch_var_32_edges_start_index = (int*)(&((*v_p_patch_var_32_edges)->start_index)[0]);
    int* v_v_p_patch_var_32_edges_end_index;
    v_v_p_patch_var_32_edges_end_index = (int*)(&((*v_p_patch_var_32_edges)->end_index)[0]);
    t_patch** p_patch_var_32_0;
    p_patch_var_32_0 = &p_patch;
    t_patch** p_patch_var_23_1;
    p_patch_var_23_1 = &p_patch;
    t_grid_cells** v_p_patch_var_23_cells;
    v_p_patch_var_23_cells = (t_grid_cells**)(&((*p_patch_var_23_1)->cells));
    int* v_v_p_patch_var_23_cells_start_index;
    v_v_p_patch_var_23_cells_start_index = (int*)(&((*v_p_patch_var_23_cells)->start_index)[0]);
    int* v_v_p_patch_var_23_cells_end_index;
    v_v_p_patch_var_23_cells_end_index = (int*)(&((*v_p_patch_var_23_cells)->end_index)[0]);
    t_patch** p_patch_var_23_0;
    p_patch_var_23_0 = &p_patch;
    t_patch** p_patch_var_32_1;
    p_patch_var_32_1 = &p_patch;
    t_patch** p_patch_var_32_2;
    p_patch_var_32_2 = &p_patch;
    t_patch** ptr_patch_var_50_0;
    ptr_patch_var_50_0 = &p_patch;
    t_grid_vertices** v_ptr_patch_var_50_verts;
    v_ptr_patch_var_50_verts = (t_grid_vertices**)(&((*ptr_patch_var_50_0)->verts));
    int* v_v_ptr_patch_var_50_verts_start_block;
    v_v_ptr_patch_var_50_verts_start_block = (int*)(&((*v_ptr_patch_var_50_verts)->start_block)[0]);
    int* v_v_ptr_patch_var_50_verts_end_block;
    v_v_ptr_patch_var_50_verts_end_block = (int*)(&((*v_ptr_patch_var_50_verts)->end_block)[0]);
    int* v_v_ptr_patch_var_50_verts_edge_idx;
    v_v_ptr_patch_var_50_verts_edge_idx = (int*)(&((*v_ptr_patch_var_50_verts)->edge_idx)[0]);
    int* v_v_ptr_patch_var_50_verts_edge_blk;
    v_v_ptr_patch_var_50_verts_edge_blk = (int*)(&((*v_ptr_patch_var_50_verts)->edge_blk)[0]);
    t_patch** ptr_patch_var_68_0;
    ptr_patch_var_68_0 = &p_patch;
    t_patch** p_patch_var_41_0;
    p_patch_var_41_0 = &(*ptr_patch_var_68_0);
    t_grid_vertices** v_p_patch_var_41_verts;
    v_p_patch_var_41_verts = (t_grid_vertices**)(&((*p_patch_var_41_0)->verts));
    int* v_v_p_patch_var_41_verts_start_index;
    v_v_p_patch_var_41_verts_start_index = (int*)(&((*v_p_patch_var_41_verts)->start_index)[0]);
    int* v_v_p_patch_var_41_verts_end_index;
    v_v_p_patch_var_41_verts_end_index = (int*)(&((*v_p_patch_var_41_verts)->end_index)[0]);
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
    int _if_cond_6;
    int i_startblk_var_62_0;
    int i_endblk_var_63_0;
    int _if_cond_7;
    int i_startblk_var_86;
    int i_endblk_var_87;
    int _if_cond_9;
    int _if_cond_10;
    int i_startblk_2;
    int i_endblk_2;
    int tmp_arg_16;
    double tmp_call_18;
    int i_startblk_var_80_0;
    int i_endblk_var_81_0;
    int _for_it_0_0;
    int _for_it_1_0;
    int tmp_index_24_0;
    int tmp_index_26_0;
    int tmp_index_36_0;
    int tmp_index_38_0;
    int tmp_index_48_0;
    int tmp_index_50_0;
    int tmp_index_60_0;
    int tmp_index_62_0;
    int tmp_index_72_0;
    int tmp_index_74_0;
    int tmp_index_84_0;
    int tmp_index_86_0;
    int _for_it_2_0;
    int i_startidx_var_82_0;
    int i_endidx_var_83_0;
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
    int _for_it_16;
    int _for_it_17;
    int tmp_index_331;
    int tmp_index_333;
    int tmp_index_340;
    int tmp_index_342;
    int tmp_index_356;
    int tmp_index_358;
    int tmp_index_365;
    int tmp_index_367;
    int _for_it_18;
    int tmp_call_0_1;
    int _for_it_19;
    int _for_it_20;
    int _for_it_21;
    int _if_cond_11;
    int tmp_arg_10;
    int tmp_arg_11;
    int _if_cond_17;
    int tmp_arg_13;
    int _for_it_22;
    int _for_it_23;
    int tmp_index_409;
    int tmp_index_411;
    int tmp_index_421;
    int tmp_index_423;
    int tmp_index_433;
    int tmp_index_435;
    int _for_it_24;
    int _for_it_25;
    int tmp_index_447;
    int tmp_index_449;
    int tmp_index_459;
    int tmp_index_461;
    int tmp_index_471;
    int tmp_index_473;
    int _for_it_26;
    int _for_it_27;
    int _for_it_28;
    int _for_it_29;
    int _for_it_30;
    int _for_it_31;
    int _for_it_32;
    int _for_it_33;
    int _for_it_34;
    int clip_count;
    int _for_it_35;
    int _for_it_36;
    int _for_it_37;
    int _for_it_38;
    int _for_it_39;
    int _for_it_40;
    int tmp_index_542;
    int _for_it_41;
    int _for_it_42;
    int tmp_index_569;
    int tmp_index_573;
    int tmp_index_583;
    int tmp_index_585;
    int tmp_index_595;
    int tmp_index_597;
    int tmp_index_607;
    int tmp_index_609;
    int _for_it_43;
    int _if_cond_19;
    int _for_it_44;
    int _for_it_45;
    int tmp_index_624;
    int tmp_index_628;
    int tmp_index_643;
    int tmp_index_645;
    int tmp_index_655;
    int tmp_index_657;
    int tmp_index_667;
    int tmp_index_669;
    int i_startidx_2;
    int i_endidx_2;
    int tmp_call_13;
    int _for_it_46;
    int tmp_parfor_0;
    int tmp_call_0_0;
    int _if_cond_21;
    int tmp_arg_18;
    int _for_it_47;
    int _for_it_48;
    int tmp_index_681;
    int tmp_index_700;
    int tmp_index_702;
    int tmp_index_712;
    int tmp_index_714;
    int tmp_index_726;
    int tmp_index_728;
    int tmp_index_735;
    int tmp_index_737;
    int tmp_index_747;
    int tmp_index_749;
    int tmp_index_759;
    int tmp_index_761;
    int _for_it_49;
    int _for_it_50;
    int tmp_index_774;
    int tmp_index_793;
    int tmp_index_795;
    int tmp_index_805;
    int tmp_index_807;
    int tmp_index_820;
    int tmp_index_822;
    int tmp_index_829;
    int tmp_index_831;
    int tmp_index_842;
    int tmp_index_844;
    int tmp_index_854;
    int tmp_index_856;
    int _for_it_51;
    int _for_it_52;
    int tmp_index_883;
    int tmp_index_885;
    int tmp_index_895;
    int tmp_index_897;
    int _for_it_53;
    int tmp_index_907;
    int tmp_index_911;
    int tmp_index_929;
    int tmp_index_931;
    int tmp_index_941;
    int tmp_index_943;
    int tmp_index_953;
    int tmp_index_955;
    int tmp_index_965;
    int tmp_index_967;
    int tmp_index_978;
    int tmp_index_980;
    int tmp_index_987;
    int tmp_index_989;
    int _for_it_3_0;
    int _for_it_4_0;
    int tmp_index_98_0;
    int tmp_index_100_0;
    int tmp_index_110_0;
    int tmp_index_112_0;
    int tmp_index_122_0;
    int tmp_index_124_0;
    int tmp_index_134_0;
    int tmp_index_136_0;
    int tmp_index_146_0;
    int tmp_index_148_0;
    int tmp_index_158_0;
    int tmp_index_160_0;
    int _for_it_5_0;
    int i_endidx_var_65_0;
    int i_startidx_var_64_0;


    {
        int* v_global_data_nrdmax;
        v_global_data_nrdmax = (int*)(&(global_data->nrdmax)[0]);
        int* v_global_data_nflatlev;
        v_global_data_nflatlev = (int*)(&(global_data->nflatlev)[0]);

        {
            int global_data_0_in_nrdmax_0 = v_global_data_nrdmax[0];
            int nrdmax_jg_out;

            ///////////////////
            // Tasklet code (T_l335_c335)
            nrdmax_jg_out = global_data_0_in_nrdmax_0;
            ///////////////////

            nrdmax_jg = nrdmax_jg_out;
        }
        {
            int global_data_0_in_nflatlev_0 = v_global_data_nflatlev[0];
            int nflatlev_jg_out;

            ///////////////////
            // Tasklet code (T_l336_c336)
            nflatlev_jg_out = global_data_0_in_nflatlev_0;
            ///////////////////

            nflatlev_jg = nflatlev_jg_out;
        }
        {
            double dtime_0_in = dtime;
            double cfl_w_limit_out;

            ///////////////////
            // Tasklet code (T_l340_c340)
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
            // Tasklet code (T_l341_c341)
            scalfac_exdiff_out = (0.05 / (dtime_0_in * (0.85 - (cfl_w_limit_0_in * dtime_1_in))));
            ///////////////////

            scalfac_exdiff = scalfac_exdiff_out;
        }

    }
    _if_cond_6 = (1 - lvn_only);

    if ((_if_cond_6 == 1)) {
        {


        }
        i_startblk_var_80_0 = v_v_ptr_patch_var_68_verts_start_blk[9];
        {


        }
        i_endblk_var_81_0 = v_v_ptr_patch_var_68_verts_end_blk[2];
        for (_for_it_0_0 = i_startblk_var_80_0; (_for_it_0_0 <= i_endblk_var_81_0); _for_it_0_0 = (_for_it_0_0 + 1)) {
            if (((_for_it_0_0 == i_startblk_var_80_0) == 1)) {
                {


                }
                i_startidx_var_82_0 = v_v_p_patch_var_41_verts_start_index[9];
                i_endidx_var_83_0 = 32;
                if (((_for_it_0_0 == i_endblk_var_81_0) == 1)) {
                    {


                    }
                    i_endidx_var_83_0 = v_v_p_patch_var_41_verts_end_index[2];

                }
            } else {
                if (((_for_it_0_0 == i_endblk_var_81_0) == 1)) {

                    i_startidx_var_82_0 = 1;
                    {


                    }
                    i_endidx_var_83_0 = v_v_p_patch_var_41_verts_end_index[2];

                } else {

                    i_startidx_var_82_0 = 1;
                    i_endidx_var_83_0 = 32;

                }
            }
            for (_for_it_1_0 = 1; (_for_it_1_0 <= 91); _for_it_1_0 = (_for_it_1_0 + 1)) {
                for (_for_it_2_0 = i_startidx_var_82_0; (_for_it_2_0 <= i_endidx_var_83_0); _for_it_2_0 = (_for_it_2_0 + 1)) {
                    {


                    }
                    tmp_index_24_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_0_0) + _for_it_2_0) - 33)] - 1);
                    {


                    }
                    tmp_index_26_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_0_0) + _for_it_2_0) - 33)] - 1);
                    {


                    }
                    tmp_index_36_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 10239)] - 1);
                    {


                    }
                    tmp_index_38_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 10239)] - 1);
                    {


                    }
                    tmp_index_48_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 20511)] - 1);
                    {


                    }
                    tmp_index_50_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 20511)] - 1);
                    {


                    }
                    tmp_index_60_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 30783)] - 1);
                    {


                    }
                    tmp_index_62_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 30783)] - 1);
                    {


                    }
                    tmp_index_72_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 41055)] - 1);
                    {


                    }
                    tmp_index_74_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 41055)] - 1);
                    {


                    }
                    tmp_index_84_0 = (v_v_ptr_patch_var_68_verts_cell_idx[(((32 * _for_it_0_0) + _for_it_2_0) + 51327)] - 1);
                    {


                    }
                    tmp_index_86_0 = (v_v_ptr_patch_var_68_verts_cell_blk[(((32 * _for_it_0_0) + _for_it_2_0) + 51327)] - 1);
                    {
                        double* p_prog_w_1;
                        p_prog_w_1 = (double*)(&(p_prog->w)[0]);
                        double* p_int_cells_aw_verts_2;
                        p_int_cells_aw_verts_2 = (double*)(&(p_int->cells_aw_verts)[0]);

                        {
                            double c_int_0_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_0_0) + _for_it_2_0) - 193)];
                            double c_int_1_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_0_0) + _for_it_2_0) - 161)];
                            double c_int_2_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_0_0) + _for_it_2_0) - 129)];
                            double c_int_3_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_0_0) + _for_it_2_0) - 97)];
                            double c_int_4_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_0_0) + _for_it_2_0) - 65)];
                            double c_int_5_in_0 = p_int_cells_aw_verts_2[(((192 * _for_it_0_0) + _for_it_2_0) - 33)];
                            double p_cell_in_0_in_0 = p_prog_w_1[((((32 * _for_it_1_0) + tmp_index_24_0) + (2912 * tmp_index_26_0)) - 32)];
                            double p_cell_in_1_in_0 = p_prog_w_1[((((32 * _for_it_1_0) + tmp_index_36_0) + (2912 * tmp_index_38_0)) - 32)];
                            double p_cell_in_2_in_0 = p_prog_w_1[((((32 * _for_it_1_0) + tmp_index_48_0) + (2912 * tmp_index_50_0)) - 32)];
                            double p_cell_in_3_in_0 = p_prog_w_1[((((32 * _for_it_1_0) + tmp_index_60_0) + (2912 * tmp_index_62_0)) - 32)];
                            double p_cell_in_4_in_0 = p_prog_w_1[((((32 * _for_it_1_0) + tmp_index_72_0) + (2912 * tmp_index_74_0)) - 32)];
                            double p_cell_in_5_in_0 = p_prog_w_1[((((32 * _for_it_1_0) + tmp_index_84_0) + (2912 * tmp_index_86_0)) - 32)];
                            double p_vert_out_out_0;

                            ///////////////////
                            // Tasklet code (T_l268_c268)
                            p_vert_out_out_0 = ((((((c_int_0_in_0 * p_cell_in_0_in_0) + (c_int_1_in_0 * p_cell_in_1_in_0)) + (c_int_2_in_0 * p_cell_in_2_in_0)) + (c_int_3_in_0 * p_cell_in_3_in_0)) + (c_int_4_in_0 * p_cell_in_4_in_0)) + (c_int_5_in_0 * p_cell_in_5_in_0));
                            ///////////////////

                            z_w_v[((((2912 * _for_it_0_0) + (32 * _for_it_1_0)) + _for_it_2_0) - 2945)] = p_vert_out_out_0;
                        }

                    }

                }

            }

        }
    }

    {


    }
    i_startblk_var_62_0 = v_v_ptr_patch_var_50_verts_start_block[9];

    {


    }
    i_endblk_var_63_0 = v_v_ptr_patch_var_50_verts_end_block[2];

    for (_for_it_3_0 = i_startblk_var_62_0; (_for_it_3_0 <= i_endblk_var_63_0); _for_it_3_0 = (_for_it_3_0 + 1)) {
        if (((_for_it_3_0 == i_startblk_var_62_0) == 1)) {
            {


            }
            i_endidx_var_65_0 = 32;
            i_startidx_var_64_0 = v_v_p_patch_var_41_verts_start_index[9];
            if (((_for_it_3_0 == i_endblk_var_63_0) == 1)) {
                {


                }
                i_endidx_var_65_0 = v_v_p_patch_var_41_verts_end_index[2];

            }
        } else {
            if (((_for_it_3_0 == i_endblk_var_63_0) == 1)) {

                i_startidx_var_64_0 = 1;
                {


                }
                i_endidx_var_65_0 = v_v_p_patch_var_41_verts_end_index[2];

            } else {

                i_endidx_var_65_0 = 32;
                i_startidx_var_64_0 = 1;

            }
        }
        for (_for_it_4_0 = 1; (_for_it_4_0 <= 90); _for_it_4_0 = (_for_it_4_0 + 1)) {
            for (_for_it_5_0 = i_startidx_var_64_0; (_for_it_5_0 <= i_endidx_var_65_0); _for_it_5_0 = (_for_it_5_0 + 1)) {
                {


                }
                tmp_index_98_0 = (v_v_ptr_patch_var_50_verts_edge_idx[(((32 * _for_it_3_0) + _for_it_5_0) - 33)] - 1);
                {


                }
                tmp_index_100_0 = (v_v_ptr_patch_var_50_verts_edge_blk[(((32 * _for_it_3_0) + _for_it_5_0) - 33)] - 1);
                {


                }
                tmp_index_110_0 = (v_v_ptr_patch_var_50_verts_edge_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 10239)] - 1);
                {


                }
                tmp_index_112_0 = (v_v_ptr_patch_var_50_verts_edge_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 10239)] - 1);
                {


                }
                tmp_index_122_0 = (v_v_ptr_patch_var_50_verts_edge_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 20511)] - 1);
                {


                }
                tmp_index_124_0 = (v_v_ptr_patch_var_50_verts_edge_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 20511)] - 1);
                {


                }
                tmp_index_134_0 = (v_v_ptr_patch_var_50_verts_edge_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 30783)] - 1);
                {


                }
                tmp_index_136_0 = (v_v_ptr_patch_var_50_verts_edge_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 30783)] - 1);
                {


                }
                tmp_index_146_0 = (v_v_ptr_patch_var_50_verts_edge_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 41055)] - 1);
                {


                }
                tmp_index_148_0 = (v_v_ptr_patch_var_50_verts_edge_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 41055)] - 1);
                {


                }
                tmp_index_158_0 = (v_v_ptr_patch_var_50_verts_edge_idx[(((32 * _for_it_3_0) + _for_it_5_0) + 51327)] - 1);
                {


                }
                tmp_index_160_0 = (v_v_ptr_patch_var_50_verts_edge_blk[(((32 * _for_it_3_0) + _for_it_5_0) + 51327)] - 1);
                {
                    double* p_prog_vn_3;
                    p_prog_vn_3 = (double*)(&(p_prog->vn)[0]);
                    t_int_state** ptr_int_0;
                    ptr_int_0 = &p_int;
                    double* v_ptr_int_geofac_rot;
                    v_ptr_int_geofac_rot = (double*)(&((*ptr_int_0)->geofac_rot)[0]);

                    {
                        double ptr_int_0_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_3_0) + _for_it_5_0) - 193)];
                        double ptr_int_1_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_3_0) + _for_it_5_0) - 161)];
                        double ptr_int_2_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_3_0) + _for_it_5_0) - 129)];
                        double ptr_int_3_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_3_0) + _for_it_5_0) - 97)];
                        double ptr_int_4_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_3_0) + _for_it_5_0) - 65)];
                        double ptr_int_5_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((192 * _for_it_3_0) + _for_it_5_0) - 33)];
                        double vec_e_0_in_0 = p_prog_vn_3[((((32 * _for_it_4_0) + (2880 * tmp_index_100_0)) + tmp_index_98_0) - 32)];
                        double vec_e_1_in_0 = p_prog_vn_3[((((32 * _for_it_4_0) + tmp_index_110_0) + (2880 * tmp_index_112_0)) - 32)];
                        double vec_e_2_in_0 = p_prog_vn_3[((((32 * _for_it_4_0) + tmp_index_122_0) + (2880 * tmp_index_124_0)) - 32)];
                        double vec_e_3_in_0 = p_prog_vn_3[((((32 * _for_it_4_0) + tmp_index_134_0) + (2880 * tmp_index_136_0)) - 32)];
                        double vec_e_4_in_0 = p_prog_vn_3[((((32 * _for_it_4_0) + tmp_index_146_0) + (2880 * tmp_index_148_0)) - 32)];
                        double vec_e_5_in_0 = p_prog_vn_3[((((32 * _for_it_4_0) + tmp_index_158_0) + (2880 * tmp_index_160_0)) - 32)];
                        double rot_vec_out_0;

                        ///////////////////
                        // Tasklet code (T_l207_c207)
                        rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
                        ///////////////////

                        zeta[((((2880 * _for_it_3_0) + (32 * _for_it_4_0)) + _for_it_5_0) - 2913)] = rot_vec_out_0;
                    }

                }

            }

        }

    }
    _if_cond_7 = (istep == 1);

    if ((_if_cond_7 == 1)) {
        {


        }
        i_startblk_var_86 = v_v_p_patch_edges_start_block[18];
        {


        }
        i_endblk_var_87 = v_v_p_patch_edges_end_block[3];
        for (_for_it_6 = i_startblk_var_86; (_for_it_6 <= i_endblk_var_87); _for_it_6 = (_for_it_6 + 1)) {
            {


            }
            tmp_call_0_3 = max(1, v_v_p_patch_var_32_edges_start_index[18]);
            if ((_for_it_6 != i_startblk_var_86)) {

                i_startidx_var_88 = 1;

            } else {

                i_startidx_var_88 = tmp_call_0_3;

            }
            if ((_for_it_6 != i_endblk_var_87)) {

                i_endidx_var_89 = 32;

            } else {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_32_edges_end_index[3];

            }
            for (_for_it_7 = 1; (_for_it_7 <= 90); _for_it_7 = (_for_it_7 + 1)) {
                for (_for_it_8 = i_startidx_var_88; (_for_it_8 <= i_endidx_var_89); _for_it_8 = (_for_it_8 + 1)) {
                    {


                    }
                    tmp_index_180 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) - 33)] - 1);
                    {


                    }
                    tmp_index_182 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) - 33)] - 1);
                    {


                    }
                    tmp_index_192 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) + 30687)] - 1);
                    {


                    }
                    tmp_index_194 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) + 30687)] - 1);
                    {


                    }
                    tmp_index_204 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) + 61407)] - 1);
                    {


                    }
                    tmp_index_206 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) + 61407)] - 1);
                    {


                    }
                    tmp_index_216 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_6) + _for_it_8) + 92127)] - 1);
                    {


                    }
                    tmp_index_218 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_6) + _for_it_8) + 92127)] - 1);
                    {
                        double* v_p_int_rbf_vec_coeff_e;
                        v_p_int_rbf_vec_coeff_e = (double*)(&(p_int->rbf_vec_coeff_e)[0]);

                        {
                            double p_int_0_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 132)];
                            double p_int_1_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 131)];
                            double p_int_2_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 130)];
                            double p_int_3_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((128 * _for_it_6) + (4 * _for_it_8)) - 129)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[((((32 * _for_it_7) + tmp_index_180) + (2880 * tmp_index_182)) - 32)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[((((32 * _for_it_7) + tmp_index_192) + (2880 * tmp_index_194)) - 32)];
                            double p_prog_2_in_vn_0 = v_p_prog_vn[((((32 * _for_it_7) + tmp_index_204) + (2880 * tmp_index_206)) - 32)];
                            double p_prog_3_in_vn_0 = v_p_prog_vn[((((32 * _for_it_7) + tmp_index_216) + (2880 * tmp_index_218)) - 32)];
                            double p_diag_out_vt_0;

                            ///////////////////
                            // Tasklet code (T_l357_c357)
                            p_diag_out_vt_0 = ((((p_int_0_in_rbf_vec_coeff_e_0 * p_prog_0_in_vn_0) + (p_int_1_in_rbf_vec_coeff_e_0 * p_prog_1_in_vn_0)) + (p_int_2_in_rbf_vec_coeff_e_0 * p_prog_2_in_vn_0)) + (p_int_3_in_rbf_vec_coeff_e_0 * p_prog_3_in_vn_0));
                            ///////////////////

                            v_p_diag_vt[((((2880 * _for_it_6) + (32 * _for_it_7)) + _for_it_8) - 2913)] = p_diag_out_vt_0;
                        }

                    }

                }

            }
            for (_for_it_9 = 2; (_for_it_9 <= 90); _for_it_9 = (_for_it_9 + 1)) {
                for (_for_it_10 = i_startidx_var_88; (_for_it_10 <= i_endidx_var_89); _for_it_10 = (_for_it_10 + 1)) {
                    {

                        {
                            double p_metrics_0_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((_for_it_10 + (2912 * _for_it_6)) + (32 * _for_it_9)) - 2945)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((_for_it_10 + (2880 * _for_it_6)) + (32 * _for_it_9)) - 2913)];
                            double p_metrics_1_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((_for_it_10 + (2912 * _for_it_6)) + (32 * _for_it_9)) - 2945)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[(((_for_it_10 + (2880 * _for_it_6)) + (32 * _for_it_9)) - 2945)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l362_c362)
                            p_diag_out_vn_ie_0 = ((p_metrics_0_in_wgtfac_e_0 * p_prog_0_in_vn_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_prog_1_in_vn_0));
                            ///////////////////

                            v_p_diag_vn_ie[(((_for_it_10 + (2912 * _for_it_6)) + (32 * _for_it_9)) - 2945)] = p_diag_out_vn_ie_0;
                        }
                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((_for_it_10 + (2880 * _for_it_6)) + (32 * _for_it_9)) - 2913)];
                            double tmp_call_2_out;

                            ///////////////////
                            // Tasklet code (T_l363_c363)
                            tmp_call_2_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                            ///////////////////

                            tmp_call_2 = tmp_call_2_out;
                        }

                    }
                    {
                        double tmp_call_1;

                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((_for_it_10 + (2880 * _for_it_6)) + (32 * _for_it_9)) - 2913)];
                            double tmp_call_1_out;

                            ///////////////////
                            // Tasklet code (T_l363_c363)
                            tmp_call_1_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                            ///////////////////

                            tmp_call_1 = tmp_call_1_out;
                        }
                        {
                            double tmp_call_2_0_in = tmp_call_2;
                            double tmp_call_1_0_in = tmp_call_1;
                            double z_kin_hor_e_out_0;

                            ///////////////////
                            // Tasklet code (T_l363_c363)
                            z_kin_hor_e_out_0 = (0.5 * (tmp_call_1_0_in + tmp_call_2_0_in));
                            ///////////////////

                            z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_151 * __f2dace_A_z_kin_hor_e_d_1_s_152) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_153) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_151 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_152) + _for_it_9))) - __f2dace_OA_z_kin_hor_e_d_0_s_151) + _for_it_10)] = z_kin_hor_e_out_0;
                        }

                    }

                }

            }
            _if_cond_7 = (1 - lvn_only);
            if ((_if_cond_7 == 1)) {
                for (_for_it_11 = 2; (_for_it_11 <= 90); _for_it_11 = (_for_it_11 + 1)) {
                    for (_for_it_12 = i_startidx_var_88; (_for_it_12 <= i_endidx_var_89); _for_it_12 = (_for_it_12 + 1)) {
                        {

                            {
                                double p_metrics_0_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[((((32 * _for_it_11) + _for_it_12) + (2912 * _for_it_6)) - 2945)];
                                double p_diag_0_in_vt_0 = v_p_diag_vt[((((32 * _for_it_11) + _for_it_12) + (2880 * _for_it_6)) - 2913)];
                                double p_metrics_1_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[((((32 * _for_it_11) + _for_it_12) + (2912 * _for_it_6)) - 2945)];
                                double p_diag_1_in_vt_0 = v_p_diag_vt[((((32 * _for_it_11) + _for_it_12) + (2880 * _for_it_6)) - 2945)];
                                double z_vt_ie_out_0;

                                ///////////////////
                                // Tasklet code (T_l369_c369)
                                z_vt_ie_out_0 = ((p_metrics_0_in_wgtfac_e_0 * p_diag_0_in_vt_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_diag_1_in_vt_0));
                                ///////////////////

                                z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_154 * __f2dace_A_z_vt_ie_d_1_s_155) * ((- __f2dace_OA_z_vt_ie_d_2_s_156) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_154 * ((- __f2dace_OA_z_vt_ie_d_1_s_155) + _for_it_11))) - __f2dace_OA_z_vt_ie_d_0_s_154) + _for_it_12)] = z_vt_ie_out_0;
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
                            double p_prog_0_in_vn_0 = v_p_prog_vn[((((32 * _for_it_13) + _for_it_14) + (2880 * _for_it_6)) - 2913)];
                            double p_metrics_0_in_ddxn_z_full_0 = v_p_metrics_ddxn_z_full[((((32 * _for_it_13) + _for_it_14) + (2880 * _for_it_6)) - 2913)];
                            double p_diag_0_in_vt_0 = v_p_diag_vt[((((32 * _for_it_13) + _for_it_14) + (2880 * _for_it_6)) - 2913)];
                            double p_metrics_1_in_ddxt_z_full_0 = v_p_metrics_ddxt_z_full[((((32 * _for_it_13) + _for_it_14) + (2880 * _for_it_6)) - 2913)];
                            double z_w_concorr_me_out_0;

                            ///////////////////
                            // Tasklet code (T_l375_c375)
                            z_w_concorr_me_out_0 = ((p_prog_0_in_vn_0 * p_metrics_0_in_ddxn_z_full_0) + (p_diag_0_in_vt_0 * p_metrics_1_in_ddxt_z_full_0));
                            ///////////////////

                            z_w_concorr_me[(((((__f2dace_A_z_w_concorr_me_d_0_s_148 * __f2dace_A_z_w_concorr_me_d_1_s_149) * ((- __f2dace_OA_z_w_concorr_me_d_2_s_150) + _for_it_6)) + (__f2dace_A_z_w_concorr_me_d_0_s_148 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_149) + _for_it_13))) - __f2dace_OA_z_w_concorr_me_d_0_s_148) + _for_it_14)] = z_w_concorr_me_out_0;
                        }

                    }

                }

            }
            for (_for_it_15 = i_startidx_var_88; (_for_it_15 <= i_endidx_var_89); _for_it_15 = (_for_it_15 + 1)) {
                {

                    {
                        double p_prog_0_in_vn_0 = v_p_prog_vn[((_for_it_15 + (2880 * _for_it_6)) - 2881)];
                        double p_diag_out_vn_ie_0;

                        ///////////////////
                        // Tasklet code (T_l380_c380)
                        p_diag_out_vn_ie_0 = p_prog_0_in_vn_0;
                        ///////////////////

                        v_p_diag_vn_ie[((_for_it_15 + (2912 * _for_it_6)) - 2913)] = p_diag_out_vn_ie_0;
                    }
                    {
                        double p_diag_0_in_vt_0 = v_p_diag_vt[((_for_it_15 + (2880 * _for_it_6)) - 2881)];
                        double z_vt_ie_out_0;

                        ///////////////////
                        // Tasklet code (T_l381_c381)
                        z_vt_ie_out_0 = p_diag_0_in_vt_0;
                        ///////////////////

                        z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_154 * __f2dace_A_z_vt_ie_d_1_s_155) * ((- __f2dace_OA_z_vt_ie_d_2_s_156) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_154 * (1 - __f2dace_OA_z_vt_ie_d_1_s_155))) - __f2dace_OA_z_vt_ie_d_0_s_154) + _for_it_15)] = z_vt_ie_out_0;
                    }

                }
                {
                    double tmp_call_4;
                    double tmp_call_3;

                    {
                        double p_diag_0_in_vt_0 = v_p_diag_vt[((_for_it_15 + (2880 * _for_it_6)) - 2881)];
                        double tmp_call_4_out;

                        ///////////////////
                        // Tasklet code (T_l382_c382)
                        tmp_call_4_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                        ///////////////////

                        tmp_call_4 = tmp_call_4_out;
                    }
                    {
                        double p_prog_0_in_vn_0 = v_p_prog_vn[((_for_it_15 + (2880 * _for_it_6)) - 2881)];
                        double tmp_call_3_out;

                        ///////////////////
                        // Tasklet code (T_l382_c382)
                        tmp_call_3_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                        ///////////////////

                        tmp_call_3 = tmp_call_3_out;
                    }
                    {
                        double tmp_call_3_0_in = tmp_call_3;
                        double tmp_call_4_0_in = tmp_call_4;
                        double z_kin_hor_e_out_0;

                        ///////////////////
                        // Tasklet code (T_l382_c382)
                        z_kin_hor_e_out_0 = (0.5 * (tmp_call_3_0_in + tmp_call_4_0_in));
                        ///////////////////

                        z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_151 * __f2dace_A_z_kin_hor_e_d_1_s_152) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_153) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_151 * (1 - __f2dace_OA_z_kin_hor_e_d_1_s_152))) - __f2dace_OA_z_kin_hor_e_d_0_s_151) + _for_it_15)] = z_kin_hor_e_out_0;
                    }

                }
                {
                    double* v_p_metrics_wgtfacq_e;
                    v_p_metrics_wgtfacq_e = (double*)(&(p_metrics->wgtfacq_e)[0]);

                    {
                        double p_metrics_0_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[((_for_it_15 + (96 * _for_it_6)) - 97)];
                        double p_prog_0_in_vn_0 = v_p_prog_vn[((_for_it_15 + (2880 * _for_it_6)) - 33)];
                        double p_metrics_1_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[((_for_it_15 + (96 * _for_it_6)) - 65)];
                        double p_prog_1_in_vn_0 = v_p_prog_vn[((_for_it_15 + (2880 * _for_it_6)) - 65)];
                        double p_metrics_2_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[((_for_it_15 + (96 * _for_it_6)) - 33)];
                        double p_prog_2_in_vn_0 = v_p_prog_vn[((_for_it_15 + (2880 * _for_it_6)) - 97)];
                        double p_diag_out_vn_ie_0;

                        ///////////////////
                        // Tasklet code (T_l383_c383)
                        p_diag_out_vn_ie_0 = (((p_metrics_0_in_wgtfacq_e_0 * p_prog_0_in_vn_0) + (p_metrics_1_in_wgtfacq_e_0 * p_prog_1_in_vn_0)) + (p_metrics_2_in_wgtfacq_e_0 * p_prog_2_in_vn_0));
                        ///////////////////

                        v_p_diag_vn_ie[((_for_it_15 + (2912 * _for_it_6)) - 33)] = p_diag_out_vn_ie_0;
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
    _if_cond_9 = (1 - lvn_only);

    if ((_if_cond_9 == 1)) {
        for (_for_it_16 = i_startblk_var_86; (_for_it_16 <= i_endblk_var_87); _for_it_16 = (_for_it_16 + 1)) {
            {


            }
            tmp_call_0_2 = max(1, v_v_p_patch_var_32_edges_start_index[20]);
            if ((_for_it_16 != i_startblk_var_86)) {

                i_startidx_var_88 = 1;

            } else {

                i_startidx_var_88 = tmp_call_0_2;

            }
            if ((_for_it_16 != i_endblk_var_87)) {

                i_endidx_var_89 = 32;

            } else {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_32_edges_end_index[4];

            }
            for (_for_it_17 = 1; (_for_it_17 <= 90); _for_it_17 = (_for_it_17 + 1)) {
                for (_for_it_18 = i_startidx_var_88; (_for_it_18 <= i_endidx_var_89); _for_it_18 = (_for_it_18 + 1)) {
                    {


                    }
                    tmp_index_331 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_16) + _for_it_18) - 33)] - 1);
                    {


                    }
                    tmp_index_333 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_16) + _for_it_18) - 33)] - 1);
                    {


                    }
                    tmp_index_340 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_16) + _for_it_18) + 30687)] - 1);
                    {


                    }
                    tmp_index_342 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_16) + _for_it_18) + 30687)] - 1);
                    {


                    }
                    tmp_index_356 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_16) + _for_it_18) - 33)] - 1);
                    {


                    }
                    tmp_index_358 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_16) + _for_it_18) - 33)] - 1);
                    {


                    }
                    tmp_index_365 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_16) + _for_it_18) + 30687)] - 1);
                    {


                    }
                    tmp_index_367 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_16) + _for_it_18) + 30687)] - 1);
                    {
                        double* v_v_p_patch_edges_inv_dual_edge_length;
                        v_v_p_patch_edges_inv_dual_edge_length = (double*)(&((*v_p_patch_edges)->inv_dual_edge_length)[0]);

                        {
                            double p_diag_0_in_vn_ie_0 = v_p_diag_vn_ie[((((2912 * _for_it_16) + (32 * _for_it_17)) + _for_it_18) - 2945)];
                            double p_patch_0_in_edges_inv_dual_edge_length_0 = v_v_p_patch_edges_inv_dual_edge_length[(((32 * _for_it_16) + _for_it_18) - 33)];
                            double z_vt_ie_0_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_154 * __f2dace_A_z_vt_ie_d_1_s_155) * ((- __f2dace_OA_z_vt_ie_d_2_s_156) + _for_it_16)) + (__f2dace_A_z_vt_ie_d_0_s_154 * ((- __f2dace_OA_z_vt_ie_d_1_s_155) + _for_it_17))) - __f2dace_OA_z_vt_ie_d_0_s_154) + _for_it_18)];
                            double p_patch_1_in_edges_inv_primal_edge_length_0 = v_v_p_patch_edges_inv_primal_edge_length[(((32 * _for_it_16) + _for_it_18) - 33)];
                            double p_patch_2_in_edges_tangent_orientation_0 = v_v_p_patch_edges_tangent_orientation[(((32 * _for_it_16) + _for_it_18) - 33)];
                            double p_prog_0_in_w_0 = v_p_prog_w[((((32 * _for_it_17) + tmp_index_331) + (2912 * tmp_index_333)) - 32)];
                            double p_prog_1_in_w_0 = v_p_prog_w[((((32 * _for_it_17) + tmp_index_340) + (2912 * tmp_index_342)) - 32)];
                            double z_w_v_0_in_0 = z_w_v[((((32 * _for_it_17) + tmp_index_356) + (2912 * tmp_index_358)) - 32)];
                            double z_w_v_1_in_0 = z_w_v[((((32 * _for_it_17) + tmp_index_365) + (2912 * tmp_index_367)) - 32)];
                            double z_v_grad_w_out_0;

                            ///////////////////
                            // Tasklet code (T_l404_c404)
                            z_v_grad_w_out_0 = (((p_diag_0_in_vn_ie_0 * p_patch_0_in_edges_inv_dual_edge_length_0) * (p_prog_0_in_w_0 - p_prog_1_in_w_0)) + (((z_vt_ie_0_in_0 * p_patch_1_in_edges_inv_primal_edge_length_0) * p_patch_2_in_edges_tangent_orientation_0) * (z_w_v_0_in_0 - z_w_v_1_in_0)));
                            ///////////////////

                            z_v_grad_w[((((2880 * _for_it_16) + (32 * _for_it_17)) + _for_it_18) - 2913)] = z_v_grad_w_out_0;
                        }

                    }

                }

            }

        }
    }
    _if_cond_10 = ((1 - lvn_only) && ldeepatmo);

    if ((_if_cond_10 == 1)) {
        for (_for_it_19 = i_startblk_var_86; (_for_it_19 <= i_endblk_var_87); _for_it_19 = (_for_it_19 + 1)) {
            {


            }
            tmp_call_0_1 = max(1, v_v_p_patch_var_32_edges_start_index[20]);
            if ((_for_it_19 != i_startblk_var_86)) {

                i_startidx_var_88 = 1;

            } else {

                i_startidx_var_88 = tmp_call_0_1;

            }
            if ((_for_it_19 != i_endblk_var_87)) {

                i_endidx_var_89 = 32;

            } else {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_32_edges_end_index[4];

            }
            for (_for_it_20 = 1; (_for_it_20 <= 90); _for_it_20 = (_for_it_20 + 1)) {
                for (_for_it_21 = i_startidx_var_88; (_for_it_21 <= i_endidx_var_89); _for_it_21 = (_for_it_21 + 1)) {
                    {
                        double* v_p_metrics_deepatmo_gradh_ifc;
                        v_p_metrics_deepatmo_gradh_ifc = (double*)(&(p_metrics->deepatmo_gradh_ifc)[0]);
                        double* v_p_metrics_deepatmo_invr_ifc;
                        v_p_metrics_deepatmo_invr_ifc = (double*)(&(p_metrics->deepatmo_invr_ifc)[0]);
                        double* v_v_p_patch_edges_fn_e;
                        v_v_p_patch_edges_fn_e = (double*)(&((*v_p_patch_edges)->fn_e)[0]);

                        {
                            double z_v_grad_w_0_in_0 = z_v_grad_w[((((2880 * _for_it_19) + (32 * _for_it_20)) + _for_it_21) - 2913)];
                            double p_metrics_0_in_deepatmo_gradh_ifc_0 = v_p_metrics_deepatmo_gradh_ifc[(_for_it_20 - 1)];
                            double p_diag_0_in_vn_ie_0 = v_p_diag_vn_ie[((((2912 * _for_it_19) + (32 * _for_it_20)) + _for_it_21) - 2945)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[((((2912 * _for_it_19) + (32 * _for_it_20)) + _for_it_21) - 2945)];
                            double p_metrics_1_in_deepatmo_invr_ifc_0 = v_p_metrics_deepatmo_invr_ifc[(_for_it_20 - 1)];
                            double p_patch_0_in_edges_ft_e_0 = v_v_p_patch_edges_ft_e[(((32 * _for_it_19) + _for_it_21) - 33)];
                            double z_vt_ie_0_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_154 * __f2dace_A_z_vt_ie_d_1_s_155) * ((- __f2dace_OA_z_vt_ie_d_2_s_156) + _for_it_19)) + (__f2dace_A_z_vt_ie_d_0_s_154 * ((- __f2dace_OA_z_vt_ie_d_1_s_155) + _for_it_20))) - __f2dace_OA_z_vt_ie_d_0_s_154) + _for_it_21)];
                            double p_metrics_2_in_deepatmo_invr_ifc_0 = v_p_metrics_deepatmo_invr_ifc[(_for_it_20 - 1)];
                            double p_patch_1_in_edges_fn_e_0 = v_v_p_patch_edges_fn_e[(((32 * _for_it_19) + _for_it_21) - 33)];
                            double z_vt_ie_1_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_154 * __f2dace_A_z_vt_ie_d_1_s_155) * ((- __f2dace_OA_z_vt_ie_d_2_s_156) + _for_it_19)) + (__f2dace_A_z_vt_ie_d_0_s_154 * ((- __f2dace_OA_z_vt_ie_d_1_s_155) + _for_it_20))) - __f2dace_OA_z_vt_ie_d_0_s_154) + _for_it_21)];
                            double z_v_grad_w_out_0;

                            ///////////////////
                            // Tasklet code (T_l414_c414)
                            z_v_grad_w_out_0 = (((z_v_grad_w_0_in_0 * p_metrics_0_in_deepatmo_gradh_ifc_0) + (p_diag_0_in_vn_ie_0 * ((p_diag_1_in_vn_ie_0 * p_metrics_1_in_deepatmo_invr_ifc_0) - p_patch_0_in_edges_ft_e_0))) + (z_vt_ie_0_in_0 * ((z_vt_ie_1_in_0 * p_metrics_2_in_deepatmo_invr_ifc_0) + p_patch_1_in_edges_fn_e_0)));
                            ///////////////////

                            z_v_grad_w[((((2880 * _for_it_19) + (32 * _for_it_20)) + _for_it_21) - 2913)] = z_v_grad_w_out_0;
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

    for (_for_it_22 = i_startblk_var_86; (_for_it_22 <= i_endblk_var_87); _for_it_22 = (_for_it_22 + 1)) {
        if (((_for_it_22 == i_startblk_var_86) == 1)) {
            {


            }
            i_startidx_var_88 = max(1, v_v_p_patch_var_23_cells_start_index[12]);
            i_endidx_var_89 = 32;
            if (((_for_it_22 == i_endblk_var_87) == 1)) {
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_23_cells_end_index[3];

            }
        } else {
            if (((_for_it_22 == i_endblk_var_87) == 1)) {

                i_startidx_var_88 = 1;
                {


                }
                i_endidx_var_89 = v_v_p_patch_var_23_cells_end_index[3];

            } else {

                i_startidx_var_88 = 1;
                i_endidx_var_89 = 32;

            }
        }
        for (_for_it_23 = 1; (_for_it_23 <= 90); _for_it_23 = (_for_it_23 + 1)) {
            for (_for_it_24 = i_startidx_var_88; (_for_it_24 <= i_endidx_var_89); _for_it_24 = (_for_it_24 + 1)) {
                {


                }
                tmp_index_409 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_24) - 33)] - __f2dace_OA_z_kin_hor_e_d_0_s_151);
                {


                }
                tmp_index_411 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_24) - 33)] - __f2dace_OA_z_kin_hor_e_d_2_s_153);
                {


                }
                tmp_index_421 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_24) + 20447)] - __f2dace_OA_z_kin_hor_e_d_0_s_151);
                {


                }
                tmp_index_423 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_24) + 20447)] - __f2dace_OA_z_kin_hor_e_d_2_s_153);
                {


                }
                tmp_index_433 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_24) + 40927)] - __f2dace_OA_z_kin_hor_e_d_0_s_151);
                {


                }
                tmp_index_435 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_24) + 40927)] - __f2dace_OA_z_kin_hor_e_d_2_s_153);
                {

                    {
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_24) - 97)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_24) - 65)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_24) - 33)];
                        double z_kin_hor_e_0_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_151 * __f2dace_A_z_kin_hor_e_d_1_s_152) * tmp_index_411) + (__f2dace_A_z_kin_hor_e_d_0_s_151 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_152) + _for_it_23))) + tmp_index_409)];
                        double z_kin_hor_e_1_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_151 * __f2dace_A_z_kin_hor_e_d_1_s_152) * tmp_index_423) + (__f2dace_A_z_kin_hor_e_d_0_s_151 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_152) + _for_it_23))) + tmp_index_421)];
                        double z_kin_hor_e_2_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_151 * __f2dace_A_z_kin_hor_e_d_1_s_152) * tmp_index_435) + (__f2dace_A_z_kin_hor_e_d_0_s_151 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_152) + _for_it_23))) + tmp_index_433)];
                        double z_ekinh_out_0;

                        ///////////////////
                        // Tasklet code (T_l431_c431)
                        z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_kin_hor_e_2_in_0));
                        ///////////////////

                        z_ekinh[((((2880 * _for_it_22) + (32 * _for_it_23)) + _for_it_24) - 2913)] = z_ekinh_out_0;
                    }

                }

            }

        }
        _if_cond_11 = (istep == 1);
        if ((_if_cond_11 == 1)) {
            for (_for_it_25 = nflatlev_jg; (_for_it_25 <= 90); _for_it_25 = (_for_it_25 + 1)) {
                for (_for_it_26 = i_startidx_var_88; (_for_it_26 <= i_endidx_var_89); _for_it_26 = (_for_it_26 + 1)) {
                    {


                    }
                    tmp_index_447 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_26) - 33)] - __f2dace_OA_z_w_concorr_me_d_0_s_148);
                    {


                    }
                    tmp_index_449 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_26) - 33)] - __f2dace_OA_z_w_concorr_me_d_2_s_150);
                    {


                    }
                    tmp_index_459 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_26) + 20447)] - __f2dace_OA_z_w_concorr_me_d_0_s_148);
                    {


                    }
                    tmp_index_461 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_26) + 20447)] - __f2dace_OA_z_w_concorr_me_d_2_s_150);
                    {


                    }
                    tmp_index_471 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_26) + 40927)] - __f2dace_OA_z_w_concorr_me_d_0_s_148);
                    {


                    }
                    tmp_index_473 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_26) + 40927)] - __f2dace_OA_z_w_concorr_me_d_2_s_150);
                    {

                        {
                            double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_26) - 97)];
                            double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_26) - 65)];
                            double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_26) - 33)];
                            double z_w_concorr_me_0_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_148 * __f2dace_A_z_w_concorr_me_d_1_s_149) * tmp_index_449) + (__f2dace_A_z_w_concorr_me_d_0_s_148 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_149) + _for_it_25))) + tmp_index_447)];
                            double z_w_concorr_me_1_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_148 * __f2dace_A_z_w_concorr_me_d_1_s_149) * tmp_index_461) + (__f2dace_A_z_w_concorr_me_d_0_s_148 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_149) + _for_it_25))) + tmp_index_459)];
                            double z_w_concorr_me_2_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_148 * __f2dace_A_z_w_concorr_me_d_1_s_149) * tmp_index_473) + (__f2dace_A_z_w_concorr_me_d_0_s_148 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_149) + _for_it_25))) + tmp_index_471)];
                            double z_w_concorr_mc_out_0;

                            ///////////////////
                            // Tasklet code (T_l437_c437)
                            z_w_concorr_mc_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_w_concorr_me_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_w_concorr_me_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_w_concorr_me_2_in_0));
                            ///////////////////

                            z_w_concorr_mc[(((32 * _for_it_25) + _for_it_26) - 33)] = z_w_concorr_mc_out_0;
                        }

                    }

                }

            }
            for (_for_it_27 = (nflatlev_jg + 1); (_for_it_27 <= 90); _for_it_27 = (_for_it_27 + 1)) {
                for (_for_it_28 = i_startidx_var_88; (_for_it_28 <= i_endidx_var_89); _for_it_28 = (_for_it_28 + 1)) {
                    {
                        double* v_p_metrics_wgtfac_c;
                        v_p_metrics_wgtfac_c = (double*)(&(p_metrics->wgtfac_c)[0]);

                        {
                            double p_metrics_0_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[((((2912 * _for_it_22) + (32 * _for_it_27)) + _for_it_28) - 2945)];
                            double z_w_concorr_mc_0_in_0 = z_w_concorr_mc[(((32 * _for_it_27) + _for_it_28) - 33)];
                            double p_metrics_1_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[((((2912 * _for_it_22) + (32 * _for_it_27)) + _for_it_28) - 2945)];
                            double z_w_concorr_mc_1_in_0 = z_w_concorr_mc[(((32 * _for_it_27) + _for_it_28) - 65)];
                            double p_diag_out_w_concorr_c_0;

                            ///////////////////
                            // Tasklet code (T_l442_c442)
                            p_diag_out_w_concorr_c_0 = ((p_metrics_0_in_wgtfac_c_0 * z_w_concorr_mc_0_in_0) + ((1.0 - p_metrics_1_in_wgtfac_c_0) * z_w_concorr_mc_1_in_0));
                            ///////////////////

                            v_p_diag_w_concorr_c[((((2912 * _for_it_22) + (32 * _for_it_27)) + _for_it_28) - 2945)] = p_diag_out_w_concorr_c_0;
                        }

                    }

                }

            }
        }
        for (_for_it_29 = 1; (_for_it_29 <= 90); _for_it_29 = (_for_it_29 + 1)) {
            for (_for_it_30 = i_startidx_var_88; (_for_it_30 <= i_endidx_var_89); _for_it_30 = (_for_it_30 + 1)) {
                {

                    {
                        double p_prog_0_in_w_0 = v_p_prog_w[((((2912 * _for_it_22) + (32 * _for_it_29)) + _for_it_30) - 2945)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l448_c448)
                        z_w_con_c_out_0 = p_prog_0_in_w_0;
                        ///////////////////

                        z_w_con_c[(((32 * _for_it_29) + _for_it_30) - 33)] = z_w_con_c_out_0;
                    }

                }

            }

        }
        for (_for_it_31 = i_startidx_var_88; (_for_it_31 <= i_endidx_var_89); _for_it_31 = (_for_it_31 + 1)) {
            {

                {
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l452_c452)
                    z_w_con_c_out_0 = 0.0;
                    ///////////////////

                    z_w_con_c[(_for_it_31 + 2879)] = z_w_con_c_out_0;
                }

            }

        }
        for (_for_it_32 = 90; (_for_it_32 >= (nflatlev_jg + 1)); _for_it_32 = (_for_it_32 + -1)) {
            for (_for_it_33 = i_startidx_var_88; (_for_it_33 <= i_endidx_var_89); _for_it_33 = (_for_it_33 + 1)) {
                {

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(((32 * _for_it_32) + _for_it_33) - 33)];
                        double p_diag_0_in_w_concorr_c_0 = v_p_diag_w_concorr_c[((((2912 * _for_it_22) + (32 * _for_it_32)) + _for_it_33) - 2945)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l456_c456)
                        z_w_con_c_out_0 = (z_w_con_c_0_in_0 - p_diag_0_in_w_concorr_c_0);
                        ///////////////////

                        z_w_con_c[(((32 * _for_it_32) + _for_it_33) - 33)] = z_w_con_c_out_0;
                    }

                }

            }

        }
        tmp_arg_10 = (nrdmax_jg - 2);
        for (_for_it_34 = max(3, tmp_arg_10); (_for_it_34 <= (90 - 3)); _for_it_34 = (_for_it_34 + 1)) {
            {

                {
                    int levmask_out_0;

                    ///////////////////
                    // Tasklet code (T_l460_c460)
                    levmask_out_0 = 0;
                    ///////////////////

                    levmask[((_for_it_22 + (640 * _for_it_34)) - 641)] = levmask_out_0;
                }

            }

        }
        tmp_arg_11 = (nrdmax_jg - 2);
        {

            {
                double maxvcfl_out;

                ///////////////////
                // Tasklet code (T_l462_c462)
                maxvcfl_out = 0;
                ///////////////////

                maxvcfl = maxvcfl_out;
            }

        }
        for (_for_it_35 = max(3, tmp_arg_11); (_for_it_35 <= (90 - 3)); _for_it_35 = (_for_it_35 + 1)) {

            clip_count = 0;
            for (_for_it_36 = i_startidx_var_88; (_for_it_36 <= i_endidx_var_89); _for_it_36 = (_for_it_36 + 1)) {
                {
                    double tmp_call_7;

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(((32 * _for_it_35) + _for_it_36) - 33)];
                        double tmp_call_7_out;

                        ///////////////////
                        // Tasklet code (T_l466_c466)
                        tmp_call_7_out = abs(z_w_con_c_0_in_0);
                        ///////////////////

                        tmp_call_7 = tmp_call_7_out;
                    }
                    {
                        double cfl_w_limit_0_in = cfl_w_limit;
                        double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((2912 * _for_it_22) + (32 * _for_it_35)) + _for_it_36) - 2945)];
                        double tmp_call_7_0_in = tmp_call_7;
                        int cfl_clipping_out_0;

                        ///////////////////
                        // Tasklet code (T_l466_c466)
                        cfl_clipping_out_0 = (tmp_call_7_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_half_0));
                        ///////////////////

                        cfl_clipping[(((32 * _for_it_35) + _for_it_36) - 33)] = cfl_clipping_out_0;
                    }
                    {
                        int cfl_clipping_0_in_0 = cfl_clipping[(((32 * _for_it_35) + _for_it_36) - 33)];
                        int _if_cond_12_out;

                        ///////////////////
                        // Tasklet code (T_l467_c467)
                        _if_cond_12_out = cfl_clipping_0_in_0;
                        ///////////////////

                        _if_cond_12 = _if_cond_12_out;
                    }

                }
                if ((_if_cond_12 == 1)) {

                    clip_count = (clip_count + 1);

                }

            }
            if (((clip_count == 0) == 1)) {
                continue;
            }
            for (_for_it_37 = i_startidx_var_88; (_for_it_37 <= i_endidx_var_89); _for_it_37 = (_for_it_37 + 1)) {
                {

                    {
                        int cfl_clipping_0_in_0 = cfl_clipping[(((32 * _for_it_35) + _for_it_37) - 33)];
                        int _if_cond_14_out;

                        ///////////////////
                        // Tasklet code (T_l0_c0)
                        _if_cond_14_out = cfl_clipping_0_in_0;
                        ///////////////////

                        _if_cond_14 = _if_cond_14_out;
                    }

                }
                if ((_if_cond_14 == 1)) {
                    {
                        double tmp_call_8;

                        {
                            int levmask_out_0;

                            ///////////////////
                            // Tasklet code (T_l472_c472)
                            levmask_out_0 = 1;
                            ///////////////////

                            levmask[((_for_it_22 + (640 * _for_it_35)) - 641)] = levmask_out_0;
                        }
                        {
                            double dtime_0_in = dtime;
                            double z_w_con_c_0_in_0 = z_w_con_c[(((32 * _for_it_35) + _for_it_37) - 33)];
                            double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((2912 * _for_it_22) + (32 * _for_it_35)) + _for_it_37) - 2945)];
                            double vcfl_out;

                            ///////////////////
                            // Tasklet code (T_l473_c473)
                            vcfl_out = ((z_w_con_c_0_in_0 * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0);
                            ///////////////////

                            vcfl = vcfl_out;
                        }
                        {
                            double vcfl_0_in = vcfl;
                            double tmp_call_8_out;

                            ///////////////////
                            // Tasklet code (T_l474_c474)
                            tmp_call_8_out = abs(vcfl_0_in);
                            ///////////////////

                            tmp_call_8 = tmp_call_8_out;
                        }
                        {
                            double vcfl_0_in = vcfl;
                            int _if_cond_14_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_14_out = (vcfl_0_in < -0.85);
                            ///////////////////

                            _if_cond_14 = _if_cond_14_out;
                        }
                        {
                            double maxvcfl_0_in = maxvcfl;
                            double tmp_call_8_0_in = tmp_call_8;
                            double maxvcfl_out;

                            ///////////////////
                            // Tasklet code (T_l474_c474)
                            maxvcfl_out = max(maxvcfl_0_in, tmp_call_8_0_in);
                            ///////////////////

                            maxvcfl = maxvcfl_out;
                        }

                    }
                    if ((_if_cond_14 == 1)) {
                        {

                            {
                                double dtime_0_in = dtime;
                                double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((2912 * _for_it_22) + (32 * _for_it_35)) + _for_it_37) - 2945)];
                                double z_w_con_c_out_0;

                                ///////////////////
                                // Tasklet code (T_l476_c476)
                                z_w_con_c_out_0 = (- ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in));
                                ///////////////////

                                z_w_con_c[(((32 * _for_it_35) + _for_it_37) - 33)] = z_w_con_c_out_0;
                            }

                        }
                    } else {
                        {

                            {
                                double vcfl_0_in = vcfl;
                                int _if_cond_14_out;

                                ///////////////////
                                // Tasklet code (T_l477_c477)
                                _if_cond_14_out = (vcfl_0_in > 0.85);
                                ///////////////////

                                _if_cond_14 = _if_cond_14_out;
                            }

                        }
                        if ((_if_cond_14 == 1)) {
                            {

                                {
                                    double dtime_0_in = dtime;
                                    double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((2912 * _for_it_22) + (32 * _for_it_35)) + _for_it_37) - 2945)];
                                    double z_w_con_c_out_0;

                                    ///////////////////
                                    // Tasklet code (T_l478_c478)
                                    z_w_con_c_out_0 = ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in);
                                    ///////////////////

                                    z_w_con_c[(((32 * _for_it_35) + _for_it_37) - 33)] = z_w_con_c_out_0;
                                }

                            }
                        }
                    }
                }

            }

        }
        for (_for_it_38 = 1; (_for_it_38 <= 90); _for_it_38 = (_for_it_38 + 1)) {
            for (_for_it_39 = i_startidx_var_88; (_for_it_39 <= i_endidx_var_89); _for_it_39 = (_for_it_39 + 1)) {
                {

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(((32 * _for_it_38) + _for_it_39) - 33)];
                        double z_w_con_c_1_in_0 = z_w_con_c[(((32 * _for_it_38) + _for_it_39) - 1)];
                        double z_w_con_c_full_out_0;

                        ///////////////////
                        // Tasklet code (T_l485_c485)
                        z_w_con_c_full_out_0 = (0.5 * (z_w_con_c_0_in_0 + z_w_con_c_1_in_0));
                        ///////////////////

                        z_w_con_c_full[((((2880 * _for_it_22) + (32 * _for_it_38)) + _for_it_39) - 2913)] = z_w_con_c_full_out_0;
                    }

                }

            }

        }
        {

            {
                double maxvcfl_0_in = maxvcfl;
                double vcflmax_out_0;

                ///////////////////
                // Tasklet code (T_l488_c488)
                vcflmax_out_0 = maxvcfl_0_in;
                ///////////////////

                vcflmax[(_for_it_22 - 1)] = vcflmax_out_0;
            }

        }
        _if_cond_17 = lvn_only;
        if ((_if_cond_17 == 1)) {
            continue;
        }
        if ((((_for_it_22 < i_startblk_2) || (_for_it_22 > i_endblk_2)) == 1)) {
            continue;
        }
        if (((_for_it_22 == i_startblk_2) == 1)) {
            {


            }
            i_startidx_2 = max(1, v_v_p_patch_var_23_cells_start_index[13]);
            i_endidx_2 = 32;
            if (((_for_it_22 == i_endblk_2) == 1)) {
                {


                }
                i_endidx_2 = v_v_p_patch_var_23_cells_end_index[4];

            }
        } else {
            if (((_for_it_22 == i_endblk_2) == 1)) {

                i_startidx_2 = 1;
                {


                }
                i_endidx_2 = v_v_p_patch_var_23_cells_end_index[4];

            } else {

                i_startidx_2 = 1;
                i_endidx_2 = 32;

            }
        }
        for (_for_it_40 = 2; (_for_it_40 <= 90); _for_it_40 = (_for_it_40 + 1)) {
            for (_for_it_41 = i_startidx_2; (_for_it_41 <= i_endidx_2); _for_it_41 = (_for_it_41 + 1)) {

                tmp_index_542 = (ntnd - 1);
                {
                    double* v_p_metrics_coeff1_dwdz;
                    v_p_metrics_coeff1_dwdz = (double*)(&(p_metrics->coeff1_dwdz)[0]);
                    double* v_p_metrics_coeff2_dwdz;
                    v_p_metrics_coeff2_dwdz = (double*)(&(p_metrics->coeff2_dwdz)[0]);

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[(((32 * _for_it_40) + _for_it_41) - 33)];
                        double p_prog_0_in_w_0 = v_p_prog_w[((((2912 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) - 2977)];
                        double p_metrics_0_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[((((2880 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) - 2913)];
                        double p_prog_1_in_w_0 = v_p_prog_w[((((2912 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) - 2913)];
                        double p_metrics_1_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[((((2880 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) - 2913)];
                        double p_prog_2_in_w_0 = v_p_prog_w[((((2912 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) - 2945)];
                        double p_metrics_2_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[((((2880 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) - 2913)];
                        double p_metrics_3_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[((((2880 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) - 2913)];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l494_c494)
                        p_diag_out_ddt_w_adv_pc_0 = (- (z_w_con_c_0_in_0 * (((p_prog_0_in_w_0 * p_metrics_0_in_coeff1_dwdz_0) - (p_prog_1_in_w_0 * p_metrics_1_in_coeff2_dwdz_0)) + (p_prog_2_in_w_0 * (p_metrics_2_in_coeff2_dwdz_0 - p_metrics_3_in_coeff1_dwdz_0)))));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((2912 * _for_it_22) + (32 * _for_it_40)) + _for_it_41) + (1863680 * tmp_index_542)) - 2945)] = p_diag_out_ddt_w_adv_pc_0;
                    }

                }

            }

        }
        for (_for_it_42 = 2; (_for_it_42 <= 90); _for_it_42 = (_for_it_42 + 1)) {
            for (_for_it_43 = i_startidx_2; (_for_it_43 <= i_endidx_2); _for_it_43 = (_for_it_43 + 1)) {

                tmp_index_569 = (ntnd - 1);
                tmp_index_573 = (ntnd - 1);
                {


                }
                tmp_index_583 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_43) - 33)] - 1);
                {


                }
                tmp_index_585 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_43) - 33)] - 1);
                {


                }
                tmp_index_595 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_43) + 20447)] - 1);
                {


                }
                tmp_index_597 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_43) + 20447)] - 1);
                {


                }
                tmp_index_607 = (v_v_p_patch_cells_edge_idx[(((32 * _for_it_22) + _for_it_43) + 40927)] - 1);
                {


                }
                tmp_index_609 = (v_v_p_patch_cells_edge_blk[(((32 * _for_it_22) + _for_it_43) + 40927)] - 1);
                {

                    {
                        double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((2912 * _for_it_22) + (32 * _for_it_42)) + _for_it_43) + (1863680 * tmp_index_573)) - 2945)];
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_43) - 97)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_43) - 65)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((96 * _for_it_22) + _for_it_43) - 33)];
                        double z_v_grad_w_0_in_0 = z_v_grad_w[((((32 * _for_it_42) + tmp_index_583) + (2880 * tmp_index_585)) - 32)];
                        double z_v_grad_w_1_in_0 = z_v_grad_w[((((32 * _for_it_42) + tmp_index_595) + (2880 * tmp_index_597)) - 32)];
                        double z_v_grad_w_2_in_0 = z_v_grad_w[((((32 * _for_it_42) + tmp_index_607) + (2880 * tmp_index_609)) - 32)];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l499_c499)
                        p_diag_out_ddt_w_adv_pc_0 = (((p_diag_0_in_ddt_w_adv_pc_0 + (p_int_0_in_e_bln_c_s_0 * z_v_grad_w_0_in_0)) + (p_int_1_in_e_bln_c_s_0 * z_v_grad_w_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_v_grad_w_2_in_0));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((2912 * _for_it_22) + (32 * _for_it_42)) + _for_it_43) + (1863680 * tmp_index_569)) - 2945)] = p_diag_out_ddt_w_adv_pc_0;
                    }

                }

            }

        }
        tmp_arg_13 = (nrdmax_jg - 2);
        for (_for_it_44 = max(3, tmp_arg_13); (_for_it_44 <= (90 - 3)); _for_it_44 = (_for_it_44 + 1)) {

            _if_cond_19 = levmask[((_for_it_22 + (640 * _for_it_44)) - 641)];
            if ((_if_cond_19 == 1)) {
                for (_for_it_45 = i_startidx_2; (_for_it_45 <= i_endidx_2); _for_it_45 = (_for_it_45 + 1)) {
                    {


                    }
                    _if_cond_19 = (cfl_clipping[(((32 * _for_it_44) + _for_it_45) - 33)] && v_v_v_p_patch_cells_decomp_info_owner_mask[(((32 * _for_it_22) + _for_it_45) - 33)]);
                    if ((_if_cond_19 == 1)) {

                        tmp_index_624 = (ntnd - 1);
                        tmp_index_628 = (ntnd - 1);
                        {

                            {
                                double z_w_con_c_0_in_0 = z_w_con_c[(((32 * _for_it_44) + _for_it_45) - 33)];
                                double tmp_call_11_out;

                                ///////////////////
                                // Tasklet code (T_l507_c507)
                                tmp_call_11_out = abs(z_w_con_c_0_in_0);
                                ///////////////////

                                tmp_call_11 = tmp_call_11_out;
                            }

                        }
                        tmp_index_643 = (v_v_p_patch_cells_neighbor_idx[(((32 * _for_it_22) + _for_it_45) - 33)] - 1);
                        {
                            double tmp_call_10;
                            double tmp_arg_14;
                            double tmp_arg_15;

                            {
                                double tmp_call_11_0_in = tmp_call_11;
                                double dtime_0_in = dtime;
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((2912 * _for_it_22) + (32 * _for_it_44)) + _for_it_45) - 2945)];
                                double dtime_1_in = dtime;
                                double tmp_arg_15_out;

                                ///////////////////
                                // Tasklet code (T_l507_c507)
                                tmp_arg_15_out = (((tmp_call_11_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0) - (cfl_w_limit_0_in * dtime_1_in));
                                ///////////////////

                                tmp_arg_15 = tmp_arg_15_out;
                            }
                            {
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double dtime_0_in = dtime;
                                double tmp_arg_14_out;

                                ///////////////////
                                // Tasklet code (T_l507_c507)
                                tmp_arg_14_out = (0.85 - (cfl_w_limit_0_in * dtime_0_in));
                                ///////////////////

                                tmp_arg_14 = tmp_arg_14_out;
                            }
                            {
                                double tmp_arg_14_0_in = tmp_arg_14;
                                double tmp_arg_15_0_in = tmp_arg_15;
                                double tmp_call_10_out;

                                ///////////////////
                                // Tasklet code (T_l507_c507)
                                tmp_call_10_out = min(tmp_arg_14_0_in, tmp_arg_15_0_in);
                                ///////////////////

                                tmp_call_10 = tmp_call_10_out;
                            }
                            {
                                double scalfac_exdiff_0_in = scalfac_exdiff;
                                double tmp_call_10_0_in = tmp_call_10;
                                double difcoef_out;

                                ///////////////////
                                // Tasklet code (T_l507_c507)
                                difcoef_out = (scalfac_exdiff_0_in * tmp_call_10_0_in);
                                ///////////////////

                                difcoef = difcoef_out;
                            }

                        }
                        tmp_index_645 = (v_v_p_patch_cells_neighbor_blk[(((32 * _for_it_22) + _for_it_45) - 33)] - 1);
                        {


                        }
                        tmp_index_655 = (v_v_p_patch_cells_neighbor_idx[(((32 * _for_it_22) + _for_it_45) + 20447)] - 1);
                        {


                        }
                        tmp_index_657 = (v_v_p_patch_cells_neighbor_blk[(((32 * _for_it_22) + _for_it_45) + 20447)] - 1);
                        {


                        }
                        tmp_index_667 = (v_v_p_patch_cells_neighbor_idx[(((32 * _for_it_22) + _for_it_45) + 40927)] - 1);
                        {


                        }
                        tmp_index_669 = (v_v_p_patch_cells_neighbor_blk[(((32 * _for_it_22) + _for_it_45) + 40927)] - 1);
                        {
                            double* v_p_int_geofac_n2s;
                            v_p_int_geofac_n2s = (double*)(&(p_int->geofac_n2s)[0]);
                            double* v_v_p_patch_cells_area;
                            v_v_p_patch_cells_area = (double*)(&((*v_p_patch_cells)->area)[0]);

                            {
                                double difcoef_0_in = difcoef;
                                double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((2912 * _for_it_22) + (32 * _for_it_44)) + _for_it_45) + (1863680 * tmp_index_628)) - 2945)];
                                double p_patch_0_in_cells_area_0 = v_v_p_patch_cells_area[(((32 * _for_it_22) + _for_it_45) - 33)];
                                double p_prog_0_in_w_0 = v_p_prog_w[((((2912 * _for_it_22) + (32 * _for_it_44)) + _for_it_45) - 2945)];
                                double p_int_0_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_22) + _for_it_45) - 129)];
                                double p_int_1_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_22) + _for_it_45) - 97)];
                                double p_int_2_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_22) + _for_it_45) - 65)];
                                double p_int_3_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((128 * _for_it_22) + _for_it_45) - 33)];
                                double p_prog_1_in_w_0 = v_p_prog_w[((((32 * _for_it_44) + tmp_index_643) + (2912 * tmp_index_645)) - 32)];
                                double p_prog_2_in_w_0 = v_p_prog_w[((((32 * _for_it_44) + tmp_index_655) + (2912 * tmp_index_657)) - 32)];
                                double p_prog_3_in_w_0 = v_p_prog_w[((((32 * _for_it_44) + tmp_index_667) + (2912 * tmp_index_669)) - 32)];
                                double p_diag_out_ddt_w_adv_pc_0;

                                ///////////////////
                                // Tasklet code (T_l508_c508)
                                p_diag_out_ddt_w_adv_pc_0 = (p_diag_0_in_ddt_w_adv_pc_0 + ((difcoef_0_in * p_patch_0_in_cells_area_0) * ((((p_prog_0_in_w_0 * p_int_0_in_geofac_n2s_0) + (p_prog_1_in_w_0 * p_int_1_in_geofac_n2s_0)) + (p_prog_2_in_w_0 * p_int_2_in_geofac_n2s_0)) + (p_prog_3_in_w_0 * p_int_3_in_geofac_n2s_0))));
                                ///////////////////

                                v_p_diag_ddt_w_adv_pc[(((((2912 * _for_it_22) + (32 * _for_it_44)) + _for_it_45) + (1863680 * tmp_index_624)) - 2945)] = p_diag_out_ddt_w_adv_pc_0;
                            }

                        }
                    }

                }
            }

        }

    }
    tmp_arg_16 = (nrdmax_jg - 2);

    for (_for_it_46 = max(3, tmp_arg_16); (_for_it_46 <= (90 - 3)); _for_it_46 = (_for_it_46 + 1)) {

        tmp_call_13 = 0;
        for (tmp_parfor_0 = i_startblk_var_86; (tmp_parfor_0 <= i_endblk_var_87); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
            if ((levmask[(((640 * _for_it_46) + tmp_parfor_0) - 641)] == 1)) {

                tmp_call_13 = 1;

            }

        }
        {

            {
                int levelmask_out_0;

                ///////////////////
                // Tasklet code (T_l516_c516)
                levelmask_out_0 = tmp_call_13;
                ///////////////////

                levelmask[(_for_it_46 - 1)] = levelmask_out_0;
            }

        }

    }

    {


    }
    i_startblk_var_86 = v_v_p_patch_edges_start_block[23];

    {


    }
    i_endblk_var_87 = v_v_p_patch_edges_end_block[5];

    for (_for_it_47 = i_startblk_var_86; (_for_it_47 <= i_endblk_var_87); _for_it_47 = (_for_it_47 + 1)) {
        {


        }
        tmp_call_0_0 = max(1, v_v_p_patch_var_32_edges_start_index[23]);
        if ((_for_it_47 != i_startblk_var_86)) {

            i_startidx_var_88 = 1;

        } else {

            i_startidx_var_88 = tmp_call_0_0;

        }
        if ((_for_it_47 != i_endblk_var_87)) {

            i_endidx_var_89 = 32;

        } else {
            {


            }
            i_endidx_var_89 = v_v_p_patch_var_32_edges_end_index[5];

        }
        _if_cond_21 = (1 - ldeepatmo);
        if ((_if_cond_21 == 1)) {
            for (_for_it_48 = 1; (_for_it_48 <= 90); _for_it_48 = (_for_it_48 + 1)) {
                for (_for_it_49 = i_startidx_var_88; (_for_it_49 <= i_endidx_var_89); _for_it_49 = (_for_it_49 + 1)) {

                    tmp_index_681 = (ntnd - 1);
                    {


                    }
                    tmp_index_700 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_49) + 30687)] - 1);
                    {


                    }
                    tmp_index_702 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_49) + 30687)] - 1);
                    {


                    }
                    tmp_index_712 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_49) - 33)] - 1);
                    {


                    }
                    tmp_index_714 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_49) - 33)] - 1);
                    {


                    }
                    tmp_index_726 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_47) + _for_it_49) - 33)] - 1);
                    {


                    }
                    tmp_index_728 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_47) + _for_it_49) - 33)] - 1);
                    {


                    }
                    tmp_index_735 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_47) + _for_it_49) + 30687)] - 1);
                    {


                    }
                    tmp_index_737 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_47) + _for_it_49) + 30687)] - 1);
                    {


                    }
                    tmp_index_747 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_49) - 33)] - 1);
                    {


                    }
                    tmp_index_749 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_49) - 33)] - 1);
                    {


                    }
                    tmp_index_759 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_49) + 30687)] - 1);
                    {


                    }
                    tmp_index_761 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_49) + 30687)] - 1);
                    {

                        {
                            double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_151 * __f2dace_A_z_kin_hor_e_d_1_s_152) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_153) + _for_it_47)) + (__f2dace_A_z_kin_hor_e_d_0_s_151 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_152) + _for_it_48))) - __f2dace_OA_z_kin_hor_e_d_0_s_151) + _for_it_49)];
                            double p_metrics_0_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_49) - 65)];
                            double p_metrics_1_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_49) - 33)];
                            double p_metrics_2_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_49) - 33)];
                            double p_metrics_3_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_49) - 65)];
                            double p_diag_0_in_vt_0 = v_p_diag_vt[((((2880 * _for_it_47) + (32 * _for_it_48)) + _for_it_49) - 2913)];
                            double p_patch_0_in_edges_f_e_0 = v_v_p_patch_edges_f_e[(((32 * _for_it_47) + _for_it_49) - 33)];
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_47) + _for_it_49) - 65)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_47) + _for_it_49) - 33)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[((((2912 * _for_it_47) + (32 * _for_it_48)) + _for_it_49) - 2945)];
                            double p_diag_2_in_vn_ie_0 = v_p_diag_vn_ie[((((2912 * _for_it_47) + (32 * _for_it_48)) + _for_it_49) - 2913)];
                            double p_metrics_4_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[((((2880 * _for_it_47) + (32 * _for_it_48)) + _for_it_49) - 2913)];
                            double z_ekinh_0_in_0 = z_ekinh[((((32 * _for_it_48) + tmp_index_700) + (2880 * tmp_index_702)) - 32)];
                            double z_ekinh_1_in_0 = z_ekinh[((((32 * _for_it_48) + tmp_index_712) + (2880 * tmp_index_714)) - 32)];
                            double zeta_0_in_0 = zeta[((((32 * _for_it_48) + tmp_index_726) + (2880 * tmp_index_728)) - 32)];
                            double zeta_1_in_0 = zeta[((((32 * _for_it_48) + tmp_index_735) + (2880 * tmp_index_737)) - 32)];
                            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((((32 * _for_it_48) + tmp_index_747) + (2880 * tmp_index_749)) - 32)];
                            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((((32 * _for_it_48) + tmp_index_759) + (2880 * tmp_index_761)) - 32)];
                            double p_diag_out_ddt_vn_apc_pc_0;

                            ///////////////////
                            // Tasklet code (T_l527_c527)
                            p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
                            ///////////////////

                            v_p_diag_ddt_vn_apc_pc[(((((2880 * _for_it_47) + (32 * _for_it_48)) + _for_it_49) + (2764800 * tmp_index_681)) - 2913)] = p_diag_out_ddt_vn_apc_pc_0;
                        }

                    }

                }

            }
        } else {
            for (_for_it_50 = 1; (_for_it_50 <= 90); _for_it_50 = (_for_it_50 + 1)) {
                for (_for_it_51 = i_startidx_var_88; (_for_it_51 <= i_endidx_var_89); _for_it_51 = (_for_it_51 + 1)) {

                    tmp_index_774 = (ntnd - 1);
                    {


                    }
                    tmp_index_793 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_51) + 30687)] - 1);
                    {


                    }
                    tmp_index_795 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_51) + 30687)] - 1);
                    {


                    }
                    tmp_index_805 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_51) - 33)] - 1);
                    {


                    }
                    tmp_index_807 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_51) - 33)] - 1);
                    {


                    }
                    tmp_index_820 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_47) + _for_it_51) - 33)] - 1);
                    {


                    }
                    tmp_index_822 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_47) + _for_it_51) - 33)] - 1);
                    {


                    }
                    tmp_index_829 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_47) + _for_it_51) + 30687)] - 1);
                    {


                    }
                    tmp_index_831 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_47) + _for_it_51) + 30687)] - 1);
                    {


                    }
                    tmp_index_842 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_51) - 33)] - 1);
                    {


                    }
                    tmp_index_844 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_51) - 33)] - 1);
                    {


                    }
                    tmp_index_854 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_51) + 30687)] - 1);
                    {


                    }
                    tmp_index_856 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_51) + 30687)] - 1);
                    {
                        double* v_p_metrics_deepatmo_gradh_mc;
                        v_p_metrics_deepatmo_gradh_mc = (double*)(&(p_metrics->deepatmo_gradh_mc)[0]);
                        double* v_p_metrics_deepatmo_invr_mc;
                        v_p_metrics_deepatmo_invr_mc = (double*)(&(p_metrics->deepatmo_invr_mc)[0]);

                        {
                            double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_151 * __f2dace_A_z_kin_hor_e_d_1_s_152) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_153) + _for_it_47)) + (__f2dace_A_z_kin_hor_e_d_0_s_151 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_152) + _for_it_50))) - __f2dace_OA_z_kin_hor_e_d_0_s_151) + _for_it_51)];
                            double p_metrics_0_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_51) - 65)];
                            double p_metrics_1_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_51) - 33)];
                            double p_metrics_2_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_51) - 33)];
                            double p_metrics_3_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((64 * _for_it_47) + _for_it_51) - 65)];
                            double p_metrics_4_in_deepatmo_gradh_mc_0 = v_p_metrics_deepatmo_gradh_mc[(_for_it_50 - 1)];
                            double p_diag_0_in_vt_0 = v_p_diag_vt[((((2880 * _for_it_47) + (32 * _for_it_50)) + _for_it_51) - 2913)];
                            double p_patch_0_in_edges_f_e_0 = v_v_p_patch_edges_f_e[(((32 * _for_it_47) + _for_it_51) - 33)];
                            double p_metrics_5_in_deepatmo_gradh_mc_0 = v_p_metrics_deepatmo_gradh_mc[(_for_it_50 - 1)];
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_47) + _for_it_51) - 65)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_47) + _for_it_51) - 33)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[((((2912 * _for_it_47) + (32 * _for_it_50)) + _for_it_51) - 2945)];
                            double p_diag_2_in_vn_ie_0 = v_p_diag_vn_ie[((((2912 * _for_it_47) + (32 * _for_it_50)) + _for_it_51) - 2913)];
                            double p_metrics_6_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[((((2880 * _for_it_47) + (32 * _for_it_50)) + _for_it_51) - 2913)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[((((2880 * _for_it_47) + (32 * _for_it_50)) + _for_it_51) - 2913)];
                            double p_metrics_7_in_deepatmo_invr_mc_0 = v_p_metrics_deepatmo_invr_mc[(_for_it_50 - 1)];
                            double p_patch_1_in_edges_ft_e_0 = v_v_p_patch_edges_ft_e[(((32 * _for_it_47) + _for_it_51) - 33)];
                            double z_ekinh_0_in_0 = z_ekinh[((((32 * _for_it_50) + tmp_index_793) + (2880 * tmp_index_795)) - 32)];
                            double z_ekinh_1_in_0 = z_ekinh[((((32 * _for_it_50) + tmp_index_805) + (2880 * tmp_index_807)) - 32)];
                            double zeta_0_in_0 = zeta[((((32 * _for_it_50) + tmp_index_820) + (2880 * tmp_index_822)) - 32)];
                            double zeta_1_in_0 = zeta[((((32 * _for_it_50) + tmp_index_829) + (2880 * tmp_index_831)) - 32)];
                            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((((32 * _for_it_50) + tmp_index_842) + (2880 * tmp_index_844)) - 32)];
                            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((((32 * _for_it_50) + tmp_index_854) + (2880 * tmp_index_856)) - 32)];
                            double p_diag_out_ddt_vn_apc_pc_0;

                            ///////////////////
                            // Tasklet code (T_l540_c540)
                            p_diag_out_ddt_vn_apc_pc_0 = (- ((((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) * p_metrics_4_in_deepatmo_gradh_mc_0) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + ((0.5 * (zeta_0_in_0 + zeta_1_in_0)) * p_metrics_5_in_deepatmo_gradh_mc_0)))) + (((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * ((((p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0) / p_metrics_6_in_ddqz_z_full_e_0) + (p_prog_0_in_vn_0 * p_metrics_7_in_deepatmo_invr_mc_0)) - p_patch_1_in_edges_ft_e_0))));
                            ///////////////////

                            v_p_diag_ddt_vn_apc_pc[(((((2880 * _for_it_47) + (32 * _for_it_50)) + _for_it_51) + (2764800 * tmp_index_774)) - 2913)] = p_diag_out_ddt_vn_apc_pc_0;
                        }

                    }

                }

            }
        }
        tmp_arg_18 = (nrdmax_jg - 2);
        for (_for_it_52 = max(3, tmp_arg_18); (_for_it_52 <= (90 - 4)); _for_it_52 = (_for_it_52 + 1)) {
            {

                {
                    int levelmask_0_in_0 = levelmask[(_for_it_52 - 1)];
                    int levelmask_1_in_0 = levelmask[_for_it_52];
                    int _if_cond_22_out;

                    ///////////////////
                    // Tasklet code (T_l0_c0)
                    _if_cond_22_out = (levelmask_0_in_0 || levelmask_1_in_0);
                    ///////////////////

                    _if_cond_22 = _if_cond_22_out;
                }

            }
            if ((_if_cond_22 == 1)) {
                for (_for_it_53 = i_startidx_var_88; (_for_it_53 <= i_endidx_var_89); _for_it_53 = (_for_it_53 + 1)) {
                    {


                    }
                    tmp_index_883 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_53) - 33)] - 1);
                    {


                    }
                    tmp_index_885 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_53) - 33)] - 1);
                    {


                    }
                    tmp_index_895 = (v_v_p_patch_edges_cell_idx[(((32 * _for_it_47) + _for_it_53) + 30687)] - 1);
                    {


                    }
                    tmp_index_897 = (v_v_p_patch_edges_cell_blk[(((32 * _for_it_47) + _for_it_53) + 30687)] - 1);
                    {
                        double tmp_call_15;

                        {
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_47) + _for_it_53) - 65)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((64 * _for_it_47) + _for_it_53) - 33)];
                            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((((32 * _for_it_52) + tmp_index_883) + (2880 * tmp_index_885)) - 32)];
                            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((((32 * _for_it_52) + tmp_index_895) + (2880 * tmp_index_897)) - 32)];
                            double w_con_e_out;

                            ///////////////////
                            // Tasklet code (T_l556_c556)
                            w_con_e_out = ((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0));
                            ///////////////////

                            w_con_e = w_con_e_out;
                        }
                        {
                            double w_con_e_0_in = w_con_e;
                            double tmp_call_15_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            tmp_call_15_out = abs(w_con_e_0_in);
                            ///////////////////

                            tmp_call_15 = tmp_call_15_out;
                        }
                        {
                            double cfl_w_limit_0_in = cfl_w_limit;
                            double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[((((2880 * _for_it_47) + (32 * _for_it_52)) + _for_it_53) - 2913)];
                            double tmp_call_15_0_in = tmp_call_15;
                            int _if_cond_22_out;

                            ///////////////////
                            // Tasklet code (T_l0_c0)
                            _if_cond_22_out = (tmp_call_15_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_full_e_0));
                            ///////////////////

                            _if_cond_22 = _if_cond_22_out;
                        }

                    }
                    if ((_if_cond_22 == 1)) {
                        {

                            {
                                double w_con_e_0_in = w_con_e;
                                double tmp_call_17_out;

                                ///////////////////
                                // Tasklet code (T_l558_c558)
                                tmp_call_17_out = abs(w_con_e_0_in);
                                ///////////////////

                                tmp_call_17 = tmp_call_17_out;
                            }

                        }
                        tmp_index_907 = (ntnd - 1);
                        tmp_index_911 = (ntnd - 1);
                        {


                        }
                        tmp_index_929 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_47) + _for_it_53) - 33)] - 1);
                        {
                            double tmp_call_16;
                            double tmp_arg_19;
                            double tmp_arg_20;

                            {
                                double tmp_call_17_0_in = tmp_call_17;
                                double dtime_0_in = dtime;
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[((((2880 * _for_it_47) + (32 * _for_it_52)) + _for_it_53) - 2913)];
                                double dtime_1_in = dtime;
                                double tmp_arg_20_out;

                                ///////////////////
                                // Tasklet code (T_l558_c558)
                                tmp_arg_20_out = (((tmp_call_17_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_full_e_0) - (cfl_w_limit_0_in * dtime_1_in));
                                ///////////////////

                                tmp_arg_20 = tmp_arg_20_out;
                            }
                            {
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double dtime_0_in = dtime;
                                double tmp_arg_19_out;

                                ///////////////////
                                // Tasklet code (T_l558_c558)
                                tmp_arg_19_out = (0.85 - (cfl_w_limit_0_in * dtime_0_in));
                                ///////////////////

                                tmp_arg_19 = tmp_arg_19_out;
                            }
                            {
                                double tmp_arg_19_0_in = tmp_arg_19;
                                double tmp_arg_20_0_in = tmp_arg_20;
                                double tmp_call_16_out;

                                ///////////////////
                                // Tasklet code (T_l558_c558)
                                tmp_call_16_out = min(tmp_arg_19_0_in, tmp_arg_20_0_in);
                                ///////////////////

                                tmp_call_16 = tmp_call_16_out;
                            }
                            {
                                double scalfac_exdiff_0_in = scalfac_exdiff;
                                double tmp_call_16_0_in = tmp_call_16;
                                double difcoef_out;

                                ///////////////////
                                // Tasklet code (T_l558_c558)
                                difcoef_out = (scalfac_exdiff_0_in * tmp_call_16_0_in);
                                ///////////////////

                                difcoef = difcoef_out;
                            }

                        }
                        tmp_index_931 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_47) + _for_it_53) - 33)] - 1);
                        {


                        }
                        tmp_index_941 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_47) + _for_it_53) + 30687)] - 1);
                        {


                        }
                        tmp_index_943 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_47) + _for_it_53) + 30687)] - 1);
                        {


                        }
                        tmp_index_953 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_47) + _for_it_53) + 61407)] - 1);
                        {


                        }
                        tmp_index_955 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_47) + _for_it_53) + 61407)] - 1);
                        {


                        }
                        tmp_index_965 = (v_v_p_patch_edges_quad_idx[(((32 * _for_it_47) + _for_it_53) + 92127)] - 1);
                        {


                        }
                        tmp_index_967 = (v_v_p_patch_edges_quad_blk[(((32 * _for_it_47) + _for_it_53) + 92127)] - 1);
                        {


                        }
                        tmp_index_978 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_47) + _for_it_53) + 30687)] - 1);
                        {


                        }
                        tmp_index_980 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_47) + _for_it_53) + 30687)] - 1);
                        {


                        }
                        tmp_index_987 = (v_v_p_patch_edges_vertex_idx[(((32 * _for_it_47) + _for_it_53) - 33)] - 1);
                        {


                        }
                        tmp_index_989 = (v_v_p_patch_edges_vertex_blk[(((32 * _for_it_47) + _for_it_53) - 33)] - 1);
                        {
                            double* v_p_int_geofac_grdiv;
                            v_p_int_geofac_grdiv = (double*)(&(p_int->geofac_grdiv)[0]);
                            double* v_v_p_patch_edges_area_edge;
                            v_v_p_patch_edges_area_edge = (double*)(&((*v_p_patch_edges)->area_edge)[0]);

                            {
                                double difcoef_0_in = difcoef;
                                double p_diag_0_in_ddt_vn_apc_pc_0 = v_p_diag_ddt_vn_apc_pc[(((((2880 * _for_it_47) + (32 * _for_it_52)) + _for_it_53) + (2764800 * tmp_index_911)) - 2913)];
                                double p_patch_0_in_edges_area_edge_0 = v_v_p_patch_edges_area_edge[(((32 * _for_it_47) + _for_it_53) - 33)];
                                double p_int_0_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_47) + _for_it_53) - 161)];
                                double p_prog_0_in_vn_0 = v_p_prog_vn[((((2880 * _for_it_47) + (32 * _for_it_52)) + _for_it_53) - 2913)];
                                double p_int_1_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_47) + _for_it_53) - 129)];
                                double p_int_2_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_47) + _for_it_53) - 97)];
                                double p_int_3_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_47) + _for_it_53) - 65)];
                                double p_int_4_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((160 * _for_it_47) + _for_it_53) - 33)];
                                double p_patch_1_in_edges_tangent_orientation_0 = v_v_p_patch_edges_tangent_orientation[(((32 * _for_it_47) + _for_it_53) - 33)];
                                double p_patch_2_in_edges_inv_primal_edge_length_0 = v_v_p_patch_edges_inv_primal_edge_length[(((32 * _for_it_47) + _for_it_53) - 33)];
                                double p_prog_1_in_vn_0 = v_p_prog_vn[((((32 * _for_it_52) + tmp_index_929) + (2880 * tmp_index_931)) - 32)];
                                double p_prog_2_in_vn_0 = v_p_prog_vn[((((32 * _for_it_52) + tmp_index_941) + (2880 * tmp_index_943)) - 32)];
                                double p_prog_3_in_vn_0 = v_p_prog_vn[((((32 * _for_it_52) + tmp_index_953) + (2880 * tmp_index_955)) - 32)];
                                double p_prog_4_in_vn_0 = v_p_prog_vn[((((32 * _for_it_52) + tmp_index_965) + (2880 * tmp_index_967)) - 32)];
                                double zeta_0_in_0 = zeta[((((32 * _for_it_52) + tmp_index_978) + (2880 * tmp_index_980)) - 32)];
                                double zeta_1_in_0 = zeta[((((32 * _for_it_52) + tmp_index_987) + (2880 * tmp_index_989)) - 32)];
                                double p_diag_out_ddt_vn_apc_pc_0;

                                ///////////////////
                                // Tasklet code (T_l559_c559)
                                p_diag_out_ddt_vn_apc_pc_0 = (p_diag_0_in_ddt_vn_apc_pc_0 + ((difcoef_0_in * p_patch_0_in_edges_area_edge_0) * ((((((p_int_0_in_geofac_grdiv_0 * p_prog_0_in_vn_0) + (p_int_1_in_geofac_grdiv_0 * p_prog_1_in_vn_0)) + (p_int_2_in_geofac_grdiv_0 * p_prog_2_in_vn_0)) + (p_int_3_in_geofac_grdiv_0 * p_prog_3_in_vn_0)) + (p_int_4_in_geofac_grdiv_0 * p_prog_4_in_vn_0)) + ((p_patch_1_in_edges_tangent_orientation_0 * p_patch_2_in_edges_inv_primal_edge_length_0) * (zeta_0_in_0 - zeta_1_in_0)))));
                                ///////////////////

                                v_p_diag_ddt_vn_apc_pc[(((((2880 * _for_it_47) + (32 * _for_it_52)) + _for_it_53) + (2764800 * tmp_index_907)) - 2913)] = p_diag_out_ddt_vn_apc_pc_0;
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
    tmp_call_18 = -1.7976931348623157e+308;

    for (tmp_parfor_0 = i_startblk_var_86; (tmp_parfor_0 <= i_endblk_var_87); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
        if ((vcflmax[(tmp_parfor_0 - 1)] > tmp_call_18)) {

            tmp_call_18 = vcflmax[(tmp_parfor_0 - 1)];

        }

    }

    {
        double max_vcfl_dyn_var_94;
        double* v_p_diag_max_vcfl_dyn;
        v_p_diag_max_vcfl_dyn = (double*)(&(p_diag->max_vcfl_dyn));

        {
            double max_vcfl_dyn_var_94_out;

            ///////////////////
            // Tasklet code (T_l568_c568)
            max_vcfl_dyn_var_94_out = max(0.0, tmp_call_18);
            ///////////////////

            max_vcfl_dyn_var_94 = max_vcfl_dyn_var_94_out;
        }
        {
            double max_vcfl_dyn_var_94_0_in = max_vcfl_dyn_var_94;
            double p_diag_out_max_vcfl_dyn;

            ///////////////////
            // Tasklet code (T_l569_c569)
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

DACE_EXPORTED void __program_velocity_tendencies(velocity_tendencies_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_151, int __f2dace_A_z_kin_hor_e_d_1_s_152, int __f2dace_A_z_vt_ie_d_0_s_154, int __f2dace_A_z_vt_ie_d_1_s_155, int __f2dace_A_z_w_concorr_me_d_0_s_148, int __f2dace_A_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_kin_hor_e_d_0_s_151, int __f2dace_OA_z_kin_hor_e_d_1_s_152, int __f2dace_OA_z_kin_hor_e_d_2_s_153, int __f2dace_OA_z_vt_ie_d_0_s_154, int __f2dace_OA_z_vt_ie_d_1_s_155, int __f2dace_OA_z_vt_ie_d_2_s_156, int __f2dace_OA_z_w_concorr_me_d_0_s_148, int __f2dace_OA_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_w_concorr_me_d_2_s_150, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    __program_velocity_tendencies_internal(__state, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s_151, __f2dace_A_z_kin_hor_e_d_1_s_152, __f2dace_A_z_vt_ie_d_0_s_154, __f2dace_A_z_vt_ie_d_1_s_155, __f2dace_A_z_w_concorr_me_d_0_s_148, __f2dace_A_z_w_concorr_me_d_1_s_149, __f2dace_OA_z_kin_hor_e_d_0_s_151, __f2dace_OA_z_kin_hor_e_d_1_s_152, __f2dace_OA_z_kin_hor_e_d_2_s_153, __f2dace_OA_z_vt_ie_d_0_s_154, __f2dace_OA_z_vt_ie_d_1_s_155, __f2dace_OA_z_vt_ie_d_2_s_156, __f2dace_OA_z_w_concorr_me_d_0_s_148, __f2dace_OA_z_w_concorr_me_d_1_s_149, __f2dace_OA_z_w_concorr_me_d_2_s_150, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
}

DACE_EXPORTED velocity_tendencies_state_t *__dace_init_velocity_tendencies(global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_151, int __f2dace_A_z_kin_hor_e_d_1_s_152, int __f2dace_A_z_vt_ie_d_0_s_154, int __f2dace_A_z_vt_ie_d_1_s_155, int __f2dace_A_z_w_concorr_me_d_0_s_148, int __f2dace_A_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_kin_hor_e_d_0_s_151, int __f2dace_OA_z_kin_hor_e_d_1_s_152, int __f2dace_OA_z_kin_hor_e_d_2_s_153, int __f2dace_OA_z_vt_ie_d_0_s_154, int __f2dace_OA_z_vt_ie_d_1_s_155, int __f2dace_OA_z_vt_ie_d_2_s_156, int __f2dace_OA_z_w_concorr_me_d_0_s_148, int __f2dace_OA_z_w_concorr_me_d_1_s_149, int __f2dace_OA_z_w_concorr_me_d_2_s_150, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int __result = 0;
    velocity_tendencies_state_t *__state = new velocity_tendencies_state_t;



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

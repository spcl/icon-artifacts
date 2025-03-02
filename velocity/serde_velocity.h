#ifndef __DACE_SERDE__
#define __DACE_SERDE__

#include <algorithm>
#include <cassert>
#include <iostream>
#include <istream>
#include <optional>
#include <sstream>

#include "velocity_tendencies.h"

namespace serde {
std::string scroll_space(std::istream& s) {
  std::string out;
  while (!s.eof() && (!s.peek() || isspace(s.peek()))) {
    out += s.get();
    assert(s.good());
  }
  return out;
}

std::string read_line(std::istream& s,
                      const std::optional<std::string>& should_contain = {}) {
  if (s.eof()) return "<eof>";
  scroll_space(s);
  char bin[101];
  s.getline(bin, 100);
  assert(s.good());
  if (should_contain) {
    bool ok = (std::string(bin).find(*should_contain) != std::string::npos);
    if (!ok) {
      std::cerr << "Expected: '" << *should_contain << "'; got: '" << bin << "'"
                << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return {bin};
}

struct array_meta;
std::map<void*, array_meta>* ARRAY_META_DICT();

struct array_meta {
  int rank = 0;
  std::vector<int> size, lbound;

  int volume() const {
    return std::reduce(size.begin(), size.end(), 1, std::multiplies<int>());
  }

  template <typename T>
  T* read(std::istream& s) const;
};
std::map<void*, array_meta>* ARRAY_META_DICT() {
  static auto* M = new std::map<void*, array_meta>();
  return M;
}

template <typename T>
void read_scalar(T& x, std::istream& s) {
  if (s.eof()) return;
  scroll_space(s);
  s >> x;
}

void read_scalar(float& x, std::istream& s) {
  if (s.eof()) return;
  scroll_space(s);
  long double y;
  s >> y;
  x = y;
}

void read_scalar(double& x, std::istream& s) {
  if (s.eof()) return;
  scroll_space(s);
  long double y;
  s >> y;
  x = y;
}

void read_scalar(bool& x, std::istream& s) {
  char c;
  read_scalar(c, s);
  assert(c == '1' or c == '0');
  x = (c == '1');
}

array_meta read_array_meta(std::istream& s) {
  array_meta m;
  read_line(s, {"# rank"});  // Should contain '# rank'
  read_scalar(m.rank, s);
  m.size.resize(m.rank);
  m.lbound.resize(m.rank);
  read_line(s, {"# size"});  // Should contain '# size'
  for (int i = 0; i < m.rank; ++i) {
    read_scalar(m.size[i], s);
  }
  read_line(s, {"# lbound"});  // Should contain '# lbound'
  for (int i = 0; i < m.rank; ++i) {
    read_scalar(m.lbound[i], s);
  }
  return m;
}

template <typename T>
std::pair<array_meta, T*> read_array(std::istream& s) {
  auto m = serde::read_array_meta(s);
  auto* y = m.read<T>(s);
  return {m, y};
}

template <typename T>
T* read_pointer(std::istream& s) {
  auto [m, arr] = read_array<T>(s);
  return arr;
}

void deserialize(float* x, std::istream& s) { read_scalar(*x, s); }
void deserialize(double* x, std::istream& s) { read_scalar(*x, s); }
void deserialize(long double* x, std::istream& s) { read_scalar(*x, s); }
void deserialize(int* x, std::istream& s) { read_scalar(*x, s); }
void deserialize(long* x, std::istream& s) { read_scalar(*x, s); }
void deserialize(long long* x, std::istream& s) { read_scalar(*x, s); }
void deserialize(bool* x, std::istream& s) { read_scalar(*x, s); }
void deserialize(float& x, std::istream& s) { read_scalar(x, s); }
void deserialize(double& x, std::istream& s) { read_scalar(x, s); }
void deserialize(long double& x, std::istream& s) { read_scalar(x, s); }
void deserialize(int& x, std::istream& s) { read_scalar(x, s); }
void deserialize(long& x, std::istream& s) { read_scalar(x, s); }
void deserialize(long long& x, std::istream& s) { read_scalar(x, s); }
void deserialize(bool& x, std::istream& s) { read_scalar(x, s); }

void deserialize(global_data_type* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# nflatlev"});  // Should contain '# nflatlev'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->nflatlev = m.read<std::remove_pointer<decltype(x->nflatlev)>::type>(s);

  read_line(s, {"# lextra_diffu"});  // Should contain '# lextra_diffu'

  deserialize(&(x->lextra_diffu), s);

  read_line(s, {"# timers_level"});  // Should contain '# timers_level'

  deserialize(&(x->timers_level), s);

  read_line(s, {"# timer_solve_nh_veltend"});  // Should contain '#
                                               // timer_solve_nh_veltend'

  deserialize(&(x->timer_solve_nh_veltend), s);

  read_line(s, {"# timer_intp"});  // Should contain '# timer_intp'

  deserialize(&(x->timer_intp), s);

  read_line(s, {"# nrdmax"});  // Should contain '# nrdmax'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->nrdmax = m.read<std::remove_pointer<decltype(x->nrdmax)>::type>(s);
}

void deserialize(t_grid_domain_decomp_info* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# owner_mask"});  // Should contain '# owner_mask'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->owner_mask = m.read<std::remove_pointer<decltype(x->owner_mask)>::type>(s);
}

void deserialize(t_int_state* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# c_lin_e"});  // Should contain '# c_lin_e'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->c_lin_e = m.read<std::remove_pointer<decltype(x->c_lin_e)>::type>(s);

  read_line(s, {"# e_bln_c_s"});  // Should contain '# e_bln_c_s'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->e_bln_c_s = m.read<std::remove_pointer<decltype(x->e_bln_c_s)>::type>(s);

  read_line(s, {"# cells_aw_verts"});  // Should contain '# cells_aw_verts'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->cells_aw_verts =
      m.read<std::remove_pointer<decltype(x->cells_aw_verts)>::type>(s);

  read_line(s, {"# rbf_vec_coeff_e"});  // Should contain '# rbf_vec_coeff_e'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->rbf_vec_coeff_e =
      m.read<std::remove_pointer<decltype(x->rbf_vec_coeff_e)>::type>(s);

  read_line(s, {"# geofac_grdiv"});  // Should contain '# geofac_grdiv'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->geofac_grdiv =
      m.read<std::remove_pointer<decltype(x->geofac_grdiv)>::type>(s);

  read_line(s, {"# geofac_rot"});  // Should contain '# geofac_rot'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->geofac_rot = m.read<std::remove_pointer<decltype(x->geofac_rot)>::type>(s);

  read_line(s, {"# geofac_n2s"});  // Should contain '# geofac_n2s'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->geofac_n2s = m.read<std::remove_pointer<decltype(x->geofac_n2s)>::type>(s);
}

void deserialize(t_grid_cells* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# neighbor_idx"});  // Should contain '# neighbor_idx'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->neighbor_idx =
      m.read<std::remove_pointer<decltype(x->neighbor_idx)>::type>(s);

  read_line(s, {"# neighbor_blk"});  // Should contain '# neighbor_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->neighbor_blk =
      m.read<std::remove_pointer<decltype(x->neighbor_blk)>::type>(s);

  read_line(s, {"# edge_idx"});  // Should contain '# edge_idx'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->edge_idx = m.read<std::remove_pointer<decltype(x->edge_idx)>::type>(s);

  read_line(s, {"# edge_blk"});  // Should contain '# edge_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->edge_blk = m.read<std::remove_pointer<decltype(x->edge_blk)>::type>(s);

  read_line(s, {"# area"});  // Should contain '# area'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->area = nullptr;
  x->area = read_pointer<std::remove_pointer<decltype(x->area)>::type>(s);

  read_line(s, {"# start_index"});  // Should contain '# start_index'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->start_index =
      m.read<std::remove_pointer<decltype(x->start_index)>::type>(s);

  read_line(s, {"# end_index"});  // Should contain '# end_index'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  read_line(s, {"# start_block"});  // Should contain '# start_block'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->start_block =
      m.read<std::remove_pointer<decltype(x->start_block)>::type>(s);

  read_line(s, {"# end_block"});  // Should contain '# end_block'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->end_block = m.read<std::remove_pointer<decltype(x->end_block)>::type>(s);

  read_line(s, {"# decomp_info"});  // Should contain '# decomp_info'

  x->decomp_info = new std::remove_pointer<decltype(x->decomp_info)>::type;
  deserialize(x->decomp_info, s);
}

void deserialize(t_grid_edges* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# cell_idx"});  // Should contain '# cell_idx'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->cell_idx = m.read<std::remove_pointer<decltype(x->cell_idx)>::type>(s);

  read_line(s, {"# cell_blk"});  // Should contain '# cell_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->cell_blk = m.read<std::remove_pointer<decltype(x->cell_blk)>::type>(s);

  read_line(s, {"# vertex_idx"});  // Should contain '# vertex_idx'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->vertex_idx = m.read<std::remove_pointer<decltype(x->vertex_idx)>::type>(s);

  read_line(s, {"# vertex_blk"});  // Should contain '# vertex_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->vertex_blk = m.read<std::remove_pointer<decltype(x->vertex_blk)>::type>(s);

  read_line(
      s, {"# tangent_orientation"});  // Should contain '# tangent_orientation'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->tangent_orientation =
      m.read<std::remove_pointer<decltype(x->tangent_orientation)>::type>(s);

  read_line(s, {"# quad_idx"});  // Should contain '# quad_idx'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->quad_idx = m.read<std::remove_pointer<decltype(x->quad_idx)>::type>(s);

  read_line(s, {"# quad_blk"});  // Should contain '# quad_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->quad_blk = m.read<std::remove_pointer<decltype(x->quad_blk)>::type>(s);

  read_line(s, {"# inv_primal_edge_length"});  // Should contain '#
                                               // inv_primal_edge_length'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->inv_primal_edge_length =
      m.read<std::remove_pointer<decltype(x->inv_primal_edge_length)>::type>(s);

  read_line(
      s,
      {"# inv_dual_edge_length"});  // Should contain '# inv_dual_edge_length'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->inv_dual_edge_length =
      m.read<std::remove_pointer<decltype(x->inv_dual_edge_length)>::type>(s);

  read_line(s, {"# area_edge"});  // Should contain '# area_edge'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->area_edge = m.read<std::remove_pointer<decltype(x->area_edge)>::type>(s);

  read_line(s, {"# f_e"});  // Should contain '# f_e'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->f_e = m.read<std::remove_pointer<decltype(x->f_e)>::type>(s);

  read_line(s, {"# fn_e"});  // Should contain '# fn_e'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->fn_e = m.read<std::remove_pointer<decltype(x->fn_e)>::type>(s);

  read_line(s, {"# ft_e"});  // Should contain '# ft_e'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->ft_e = m.read<std::remove_pointer<decltype(x->ft_e)>::type>(s);

  read_line(s, {"# start_index"});  // Should contain '# start_index'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->start_index =
      m.read<std::remove_pointer<decltype(x->start_index)>::type>(s);

  read_line(s, {"# end_index"});  // Should contain '# end_index'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  read_line(s, {"# start_block"});  // Should contain '# start_block'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->start_block =
      m.read<std::remove_pointer<decltype(x->start_block)>::type>(s);

  read_line(s, {"# end_block"});  // Should contain '# end_block'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->end_block = m.read<std::remove_pointer<decltype(x->end_block)>::type>(s);
}

void deserialize(t_grid_vertices* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# cell_idx"});  // Should contain '# cell_idx'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->cell_idx = m.read<std::remove_pointer<decltype(x->cell_idx)>::type>(s);

  read_line(s, {"# cell_blk"});  // Should contain '# cell_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->cell_blk = m.read<std::remove_pointer<decltype(x->cell_blk)>::type>(s);

  read_line(s, {"# edge_idx"});  // Should contain '# edge_idx'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->edge_idx = m.read<std::remove_pointer<decltype(x->edge_idx)>::type>(s);

  read_line(s, {"# edge_blk"});  // Should contain '# edge_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->edge_blk = m.read<std::remove_pointer<decltype(x->edge_blk)>::type>(s);

  read_line(s, {"# start_index"});  // Should contain '# start_index'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->start_index =
      m.read<std::remove_pointer<decltype(x->start_index)>::type>(s);

  read_line(s, {"# end_index"});  // Should contain '# end_index'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  read_line(s, {"# start_blk"});  // Should contain '# start_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->start_blk = m.read<std::remove_pointer<decltype(x->start_blk)>::type>(s);

  read_line(s, {"# start_block"});  // Should contain '# start_block'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->start_block =
      m.read<std::remove_pointer<decltype(x->start_block)>::type>(s);

  read_line(s, {"# end_blk"});  // Should contain '# end_blk'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->end_blk = m.read<std::remove_pointer<decltype(x->end_blk)>::type>(s);

  read_line(s, {"# end_block"});  // Should contain '# end_block'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->end_block = m.read<std::remove_pointer<decltype(x->end_block)>::type>(s);
}

void deserialize(t_patch* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# cells"});  // Should contain '# cells'

  x->cells = new std::remove_pointer<decltype(x->cells)>::type;
  deserialize(x->cells, s);

  read_line(s, {"# edges"});  // Should contain '# edges'

  x->edges = new std::remove_pointer<decltype(x->edges)>::type;
  deserialize(x->edges, s);

  read_line(s, {"# verts"});  // Should contain '# verts'

  x->verts = new std::remove_pointer<decltype(x->verts)>::type;
  deserialize(x->verts, s);
}

void deserialize(t_nh_prog* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# w"});  // Should contain '# w'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->w = nullptr;
  x->w = read_pointer<std::remove_pointer<decltype(x->w)>::type>(s);

  read_line(s, {"# vn"});  // Should contain '# vn'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->vn = nullptr;
  x->vn = read_pointer<std::remove_pointer<decltype(x->vn)>::type>(s);
}

void deserialize(t_nh_diag* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# vn_ie_ubc"});  // Should contain '# vn_ie_ubc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->vn_ie_ubc = nullptr;
  x->vn_ie_ubc =
      read_pointer<std::remove_pointer<decltype(x->vn_ie_ubc)>::type>(s);

  read_line(s, {"# vt"});  // Should contain '# vt'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->vt = nullptr;
  x->vt = read_pointer<std::remove_pointer<decltype(x->vt)>::type>(s);

  read_line(s, {"# vn_ie"});  // Should contain '# vn_ie'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->vn_ie = nullptr;
  x->vn_ie = read_pointer<std::remove_pointer<decltype(x->vn_ie)>::type>(s);

  read_line(s, {"# w_concorr_c"});  // Should contain '# w_concorr_c'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->w_concorr_c = nullptr;
  x->w_concorr_c =
      read_pointer<std::remove_pointer<decltype(x->w_concorr_c)>::type>(s);

  read_line(s, {"# ddt_vn_apc_pc"});  // Should contain '# ddt_vn_apc_pc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->ddt_vn_apc_pc = nullptr;
  x->ddt_vn_apc_pc =
      read_pointer<std::remove_pointer<decltype(x->ddt_vn_apc_pc)>::type>(s);

  read_line(s, {"# ddt_w_adv_pc"});  // Should contain '# ddt_w_adv_pc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->ddt_w_adv_pc = nullptr;
  x->ddt_w_adv_pc =
      read_pointer<std::remove_pointer<decltype(x->ddt_w_adv_pc)>::type>(s);

  read_line(s, {"# max_vcfl_dyn"});  // Should contain '# max_vcfl_dyn'

  deserialize(&(x->max_vcfl_dyn), s);
}

void deserialize(t_nh_metrics* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# ddxn_z_full"});  // Should contain '# ddxn_z_full'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->ddxn_z_full = nullptr;
  x->ddxn_z_full =
      read_pointer<std::remove_pointer<decltype(x->ddxn_z_full)>::type>(s);

  read_line(s, {"# ddxt_z_full"});  // Should contain '# ddxt_z_full'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->ddxt_z_full = nullptr;
  x->ddxt_z_full =
      read_pointer<std::remove_pointer<decltype(x->ddxt_z_full)>::type>(s);

  read_line(s, {"# ddqz_z_full_e"});  // Should contain '# ddqz_z_full_e'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->ddqz_z_full_e = nullptr;
  x->ddqz_z_full_e =
      read_pointer<std::remove_pointer<decltype(x->ddqz_z_full_e)>::type>(s);

  read_line(s, {"# ddqz_z_half"});  // Should contain '# ddqz_z_half'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->ddqz_z_half = nullptr;
  x->ddqz_z_half =
      read_pointer<std::remove_pointer<decltype(x->ddqz_z_half)>::type>(s);

  read_line(s, {"# wgtfac_c"});  // Should contain '# wgtfac_c'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->wgtfac_c = nullptr;
  x->wgtfac_c =
      read_pointer<std::remove_pointer<decltype(x->wgtfac_c)>::type>(s);

  read_line(s, {"# wgtfac_e"});  // Should contain '# wgtfac_e'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->wgtfac_e = nullptr;
  x->wgtfac_e =
      read_pointer<std::remove_pointer<decltype(x->wgtfac_e)>::type>(s);

  read_line(s, {"# wgtfacq_e"});  // Should contain '# wgtfacq_e'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->wgtfacq_e = nullptr;
  x->wgtfacq_e =
      read_pointer<std::remove_pointer<decltype(x->wgtfacq_e)>::type>(s);

  read_line(s, {"# coeff_gradekin"});  // Should contain '# coeff_gradekin'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->coeff_gradekin = nullptr;
  x->coeff_gradekin =
      read_pointer<std::remove_pointer<decltype(x->coeff_gradekin)>::type>(s);

  read_line(s, {"# coeff1_dwdz"});  // Should contain '# coeff1_dwdz'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->coeff1_dwdz = nullptr;
  x->coeff1_dwdz =
      read_pointer<std::remove_pointer<decltype(x->coeff1_dwdz)>::type>(s);

  read_line(s, {"# coeff2_dwdz"});  // Should contain '# coeff2_dwdz'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->coeff2_dwdz = nullptr;
  x->coeff2_dwdz =
      read_pointer<std::remove_pointer<decltype(x->coeff2_dwdz)>::type>(s);

  read_line(s,
            {"# deepatmo_gradh_mc"});  // Should contain '# deepatmo_gradh_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->deepatmo_gradh_mc = nullptr;
  x->deepatmo_gradh_mc =
      read_pointer<std::remove_pointer<decltype(x->deepatmo_gradh_mc)>::type>(
          s);

  read_line(s, {"# deepatmo_invr_mc"});  // Should contain '# deepatmo_invr_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->deepatmo_invr_mc = nullptr;
  x->deepatmo_invr_mc =
      read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_mc)>::type>(s);

  read_line(s,
            {"# deepatmo_gradh_ifc"});  // Should contain '# deepatmo_gradh_ifc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->deepatmo_gradh_ifc = nullptr;
  x->deepatmo_gradh_ifc =
      read_pointer<std::remove_pointer<decltype(x->deepatmo_gradh_ifc)>::type>(
          s);

  read_line(s,
            {"# deepatmo_invr_ifc"});  // Should contain '# deepatmo_invr_ifc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  // read_line(s, {"=>"});  // Should contain '=> ...'
  // x->deepatmo_invr_ifc = nullptr;
  x->deepatmo_invr_ifc =
      read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_ifc)>::type>(
          s);
}

template <typename T>
void add_line(const T& x, std::ostream& s, bool trailing_newline = true) {
  s << x;
  if (trailing_newline) s << std::endl;
}
void add_line(long long x, std::ostream& s, bool trailing_newline = true) {
  s << x;
  if (trailing_newline) s << std::endl;
}
void add_line(long double x, std::ostream& s, bool trailing_newline = true) {
  s << x;
  if (trailing_newline) s << std::endl;
}
void add_line(bool x, std::ostream& s, bool trailing_newline = true) {
  add_line(int(x), s, trailing_newline);
}
template <typename T>
std::string serialize(const T* x) {
  std::stringstream s;
  add_line(*x, s, false);
  return s.str();
}
std::string serialize(int x) { return std::to_string(x); }
std::string serialize(long x) { return std::to_string(x); }
std::string serialize(long long x) { return std::to_string(x); }
std::string serialize(float x) { return std::to_string(x); }
std::string serialize(double x) { return std::to_string(x); }
std::string serialize(long double x) { return std::to_string(x); }
std::string serialize(bool x) { return serialize(int(x)); }

std::string serialize(const global_data_type* x) {
  std::stringstream s;
  add_line("# nflatlev", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->nflatlev];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->nflatlev[i]), s);
    }
  }

  add_line("# lextra_diffu", s);
  add_line(serialize(x->lextra_diffu), s);
  add_line("# timers_level", s);
  add_line(serialize(x->timers_level), s);
  add_line("# timer_solve_nh_veltend", s);
  add_line(serialize(x->timer_solve_nh_veltend), s);
  add_line("# timer_intp", s);
  add_line(serialize(x->timer_intp), s);
  add_line("# nrdmax", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->nrdmax];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->nrdmax[i]), s);
    }
  }

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_grid_domain_decomp_info* x) {
  std::stringstream s;
  add_line("# owner_mask", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->owner_mask];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->owner_mask[i]), s);
    }
  }

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_int_state* x) {
  std::stringstream s;
  add_line("# c_lin_e", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->c_lin_e];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->c_lin_e[i]), s);
    }
  }

  add_line("# e_bln_c_s", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->e_bln_c_s];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->e_bln_c_s[i]), s);
    }
  }

  add_line("# cells_aw_verts", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->cells_aw_verts];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->cells_aw_verts[i]), s);
    }
  }

  add_line("# rbf_vec_coeff_e", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->rbf_vec_coeff_e];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->rbf_vec_coeff_e[i]), s);
    }
  }

  add_line("# geofac_grdiv", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->geofac_grdiv];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->geofac_grdiv[i]), s);
    }
  }

  add_line("# geofac_rot", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->geofac_rot];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->geofac_rot[i]), s);
    }
  }

  add_line("# geofac_n2s", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->geofac_n2s];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->geofac_n2s[i]), s);
    }
  }

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_grid_cells* x) {
  std::stringstream s;
  add_line("# neighbor_idx", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->neighbor_idx];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->neighbor_idx[i]), s);
    }
  }

  add_line("# neighbor_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->neighbor_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->neighbor_blk[i]), s);
    }
  }

  add_line("# edge_idx", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->edge_idx];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->edge_idx[i]), s);
    }
  }

  add_line("# edge_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->edge_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->edge_blk[i]), s);
    }
  }

  add_line("# area", s);

  add_line("# assoc", s);
  add_line(serialize(x->area != nullptr), s);

  add_line("=> missing", s);
  add_line("# start_index", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->start_index];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->start_index[i]), s);
    }
  }

  add_line("# end_index", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->end_index];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->end_index[i]), s);
    }
  }

  add_line("# start_block", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->start_block];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->start_block[i]), s);
    }
  }

  add_line("# end_block", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->end_block];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->end_block[i]), s);
    }
  }

  add_line("# decomp_info", s);
  add_line(serialize(x->decomp_info), s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_grid_edges* x) {
  std::stringstream s;
  add_line("# cell_idx", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->cell_idx];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->cell_idx[i]), s);
    }
  }

  add_line("# cell_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->cell_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->cell_blk[i]), s);
    }
  }

  add_line("# vertex_idx", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->vertex_idx];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->vertex_idx[i]), s);
    }
  }

  add_line("# vertex_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->vertex_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->vertex_blk[i]), s);
    }
  }

  add_line("# tangent_orientation", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->tangent_orientation];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->tangent_orientation[i]), s);
    }
  }

  add_line("# quad_idx", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->quad_idx];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->quad_idx[i]), s);
    }
  }

  add_line("# quad_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->quad_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->quad_blk[i]), s);
    }
  }

  add_line("# inv_primal_edge_length", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->inv_primal_edge_length];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->inv_primal_edge_length[i]), s);
    }
  }

  add_line("# inv_dual_edge_length", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->inv_dual_edge_length];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->inv_dual_edge_length[i]), s);
    }
  }

  add_line("# area_edge", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->area_edge];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->area_edge[i]), s);
    }
  }

  add_line("# f_e", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->f_e];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->f_e[i]), s);
    }
  }

  add_line("# fn_e", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->fn_e];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->fn_e[i]), s);
    }
  }

  add_line("# ft_e", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->ft_e];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->ft_e[i]), s);
    }
  }

  add_line("# start_index", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->start_index];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->start_index[i]), s);
    }
  }

  add_line("# end_index", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->end_index];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->end_index[i]), s);
    }
  }

  add_line("# start_block", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->start_block];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->start_block[i]), s);
    }
  }

  add_line("# end_block", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->end_block];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->end_block[i]), s);
    }
  }

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_grid_vertices* x) {
  std::stringstream s;
  add_line("# cell_idx", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->cell_idx];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->cell_idx[i]), s);
    }
  }

  add_line("# cell_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->cell_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->cell_blk[i]), s);
    }
  }

  add_line("# edge_idx", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->edge_idx];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->edge_idx[i]), s);
    }
  }

  add_line("# edge_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->edge_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->edge_blk[i]), s);
    }
  }

  add_line("# start_index", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->start_index];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->start_index[i]), s);
    }
  }

  add_line("# end_index", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->end_index];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->end_index[i]), s);
    }
  }

  add_line("# start_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->start_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->start_blk[i]), s);
    }
  }

  add_line("# start_block", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->start_block];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->start_block[i]), s);
    }
  }

  add_line("# end_blk", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->end_blk];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->end_blk[i]), s);
    }
  }

  add_line("# end_block", s);

  {
    const array_meta& m = (*ARRAY_META_DICT())[x->end_block];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->end_block[i]), s);
    }
  }

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_patch* x) {
  std::stringstream s;
  add_line("# cells", s);
  add_line(serialize(x->cells), s);
  add_line("# edges", s);
  add_line(serialize(x->edges), s);
  add_line("# verts", s);
  add_line(serialize(x->verts), s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_nh_prog* x) {
  std::stringstream s;
  add_line("# w", s);

  add_line("# assoc", s);
  add_line(serialize(x->w != nullptr), s);

  add_line("=> missing", s);
  add_line("# vn", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn != nullptr), s);

  add_line("=> missing", s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_nh_diag* x) {
  std::stringstream s;
  add_line("# vn_ie_ubc", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ie_ubc != nullptr), s);

  add_line("=> missing", s);
  add_line("# vt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vt != nullptr), s);

  add_line("=> missing", s);
  add_line("# vn_ie", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ie != nullptr), s);

  add_line("=> missing", s);
  add_line("# w_concorr_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->w_concorr_c != nullptr), s);

  add_line("=> missing", s);
  add_line("# ddt_vn_apc_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_apc_pc != nullptr), s);

  add_line("=> missing", s);
  add_line("# ddt_w_adv_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_w_adv_pc != nullptr), s);

  add_line("=> missing", s);
  add_line("# max_vcfl_dyn", s);
  add_line(serialize(x->max_vcfl_dyn), s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_nh_metrics* x) {
  std::stringstream s;
  add_line("# ddxn_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddxn_z_full != nullptr), s);

  add_line("=> missing", s);
  add_line("# ddxt_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddxt_z_full != nullptr), s);

  add_line("=> missing", s);
  add_line("# ddqz_z_full_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddqz_z_full_e != nullptr), s);

  add_line("=> missing", s);
  add_line("# ddqz_z_half", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddqz_z_half != nullptr), s);

  add_line("=> missing", s);
  add_line("# wgtfac_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfac_c != nullptr), s);

  add_line("=> missing", s);
  add_line("# wgtfac_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfac_e != nullptr), s);

  add_line("=> missing", s);
  add_line("# wgtfacq_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfacq_e != nullptr), s);

  add_line("=> missing", s);
  add_line("# coeff_gradekin", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff_gradekin != nullptr), s);

  add_line("=> missing", s);
  add_line("# coeff1_dwdz", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff1_dwdz != nullptr), s);

  add_line("=> missing", s);
  add_line("# coeff2_dwdz", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff2_dwdz != nullptr), s);

  add_line("=> missing", s);
  add_line("# deepatmo_gradh_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_gradh_mc != nullptr), s);

  add_line("=> missing", s);
  add_line("# deepatmo_invr_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_invr_mc != nullptr), s);

  add_line("=> missing", s);
  add_line("# deepatmo_gradh_ifc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_gradh_ifc != nullptr), s);

  add_line("=> missing", s);
  add_line("# deepatmo_invr_ifc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_invr_ifc != nullptr), s);

  add_line("=> missing", s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

template <typename T>
T* array_meta::read(std::istream& s) const {
  read_line(s, {"# entries"});
  auto* buf = new T[volume()];
  for (int i = 0; i < volume(); ++i) {
    deserialize(&buf[i], s);
  }
  (*ARRAY_META_DICT())[buf] = *this;
  return buf;
}

void deserialize_global_data(global_data_type* g, std::istream& s) {}

template <typename T>
std::string serialize_array(T* arr) {
  const auto m = (*ARRAY_META_DICT())[static_cast<void*>(arr)];
  std::stringstream s;
  add_line("# rank", s);
  add_line(m.rank, s);
  add_line("# size", s);
  for (auto i : m.size) add_line(i, s);
  add_line("# lbound", s);
  for (auto i : m.lbound) add_line(i, s);
  add_line("# entries", s);
  for (int i = 0; i < m.volume(); ++i) add_line(serialize(arr[i]), s);
  return s.str();
}
}  // namespace serde

#endif  // __DACE_SERDE__
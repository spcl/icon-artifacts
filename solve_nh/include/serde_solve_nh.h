#ifndef __DACE_SERDE__
#define __DACE_SERDE__

#include <algorithm>
#include <cassert>
#include <format>
#include <iostream>
#include <istream>
#include <map>
#include <optional>
#include <ranges>
#include <set>
#include <sstream>
#include <string_view>
#include <vector>

#include "solve_nh.h"

namespace serde {
std::vector<std::string_view> split(std::string_view s, char delim) {
  std::vector<std::string_view> parts;
  for (int start_pos = 0, next_pos; start_pos < s.length();
       start_pos = next_pos + 1) {
    next_pos = s.find(delim, start_pos);
    if (next_pos == s.npos) {
      parts.push_back({s.begin() + start_pos, s.length() - start_pos});
      break;
    }
    parts.push_back(
        {s.begin() + start_pos, static_cast<size_t>(next_pos - start_pos)});
  }
  return parts;
}

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
std::pair<array_meta, T*> read_pointer(std::istream& s) {
  read_line(s, {"# missing"});  // Should contain '# missing'
  int missing;
  read_scalar(missing, s);
  assert(missing == 1);
  return read_array<T>(s);
}

template <typename T>
std::string serialize_array(T* arr);

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

  read_line(s, {"# e_flx_avg"});  // Should contain '# e_flx_avg'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->e_flx_avg = m.read<std::remove_pointer<decltype(x->e_flx_avg)>::type>(s);

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

  read_line(s, {"# geofac_div"});  // Should contain '# geofac_div'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->geofac_div = m.read<std::remove_pointer<decltype(x->geofac_div)>::type>(s);

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

  read_line(s, {"# geofac_grg"});  // Should contain '# geofac_grg'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->geofac_grg = m.read<std::remove_pointer<decltype(x->geofac_grg)>::type>(s);

  read_line(s, {"# pos_on_tplane_e"});  // Should contain '# pos_on_tplane_e'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->pos_on_tplane_e =
      m.read<std::remove_pointer<decltype(x->pos_on_tplane_e)>::type>(s);

  read_line(s, {"# nudgecoeff_e"});  // Should contain '# nudgecoeff_e'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->nudgecoeff_e =
      m.read<std::remove_pointer<decltype(x->nudgecoeff_e)>::type>(s);
}

void deserialize(t_tangent_vectors* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# v1"});  // Should contain '# v1'

  deserialize(&(x->v1), s);

  read_line(s, {"# v2"});  // Should contain '# v2'

  deserialize(&(x->v2), s);
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

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->area)>::type>(s);
    x->__f2dace_SA_area_d_0_s_64 = m.size.at(0);
    x->__f2dace_SA_area_d_1_s_65 = m.size.at(1);
    x->__f2dace_SOA_area_d_0_s_64 = m.lbound.at(0);
    x->__f2dace_SOA_area_d_1_s_65 = m.lbound.at(1);
    x->area = arr;
  }

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

  read_line(s,
            {"# primal_normal_cell"});  // Should contain '# primal_normal_cell'

  m = read_array_meta(s);

  // TODO: THIS IS POTENTIALLY BUGGY, BECAUSE IT IS NOT REALLY TESTED.
  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->primal_normal_cell =
      m.read<std::remove_pointer<decltype(x->primal_normal_cell)>::type>(s);

  read_line(s, {"# dual_normal_cell"});  // Should contain '# dual_normal_cell'

  m = read_array_meta(s);

  // TODO: THIS IS POTENTIALLY BUGGY, BECAUSE IT IS NOT REALLY TESTED.
  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->dual_normal_cell =
      m.read<std::remove_pointer<decltype(x->dual_normal_cell)>::type>(s);

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

  read_line(s, {"# refin_ctrl"});  // Should contain '# refin_ctrl'

  m = read_array_meta(s);

  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->refin_ctrl = m.read<std::remove_pointer<decltype(x->refin_ctrl)>::type>(s);

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

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->w)>::type>(s);
    x->__f2dace_SA_w_d_0_s_282 = m.size.at(0);
    x->__f2dace_SA_w_d_1_s_283 = m.size.at(1);
    x->__f2dace_SA_w_d_2_s_284 = m.size.at(2);
    x->__f2dace_SOA_w_d_0_s_282 = m.lbound.at(0);
    x->__f2dace_SOA_w_d_1_s_283 = m.lbound.at(1);
    x->__f2dace_SOA_w_d_2_s_284 = m.lbound.at(2);
    x->w = arr;
  }

  read_line(s, {"# vn"});  // Should contain '# vn'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vn)>::type>(s);
    x->__f2dace_SA_vn_d_0_s_285 = m.size.at(0);
    x->__f2dace_SA_vn_d_1_s_286 = m.size.at(1);
    x->__f2dace_SA_vn_d_2_s_287 = m.size.at(2);
    x->__f2dace_SOA_vn_d_0_s_285 = m.lbound.at(0);
    x->__f2dace_SOA_vn_d_1_s_286 = m.lbound.at(1);
    x->__f2dace_SOA_vn_d_2_s_287 = m.lbound.at(2);
    x->vn = arr;
  }

  read_line(s, {"# rho"});  // Should contain '# rho'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho)>::type>(s);
    x->__f2dace_SA_rho_d_0_s_288 = m.size.at(0);
    x->__f2dace_SA_rho_d_1_s_289 = m.size.at(1);
    x->__f2dace_SA_rho_d_2_s_290 = m.size.at(2);
    x->__f2dace_SOA_rho_d_0_s_288 = m.lbound.at(0);
    x->__f2dace_SOA_rho_d_1_s_289 = m.lbound.at(1);
    x->__f2dace_SOA_rho_d_2_s_290 = m.lbound.at(2);
    x->rho = arr;
  }

  read_line(s, {"# exner"});  // Should contain '# exner'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner)>::type>(s);
    x->__f2dace_SA_exner_d_0_s_291 = m.size.at(0);
    x->__f2dace_SA_exner_d_1_s_292 = m.size.at(1);
    x->__f2dace_SA_exner_d_2_s_293 = m.size.at(2);
    x->__f2dace_SOA_exner_d_0_s_291 = m.lbound.at(0);
    x->__f2dace_SOA_exner_d_1_s_292 = m.lbound.at(1);
    x->__f2dace_SOA_exner_d_2_s_293 = m.lbound.at(2);
    x->exner = arr;
  }

  read_line(s, {"# theta_v"});  // Should contain '# theta_v'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v)>::type>(s);
    x->__f2dace_SA_theta_v_d_0_s_294 = m.size.at(0);
    x->__f2dace_SA_theta_v_d_1_s_295 = m.size.at(1);
    x->__f2dace_SA_theta_v_d_2_s_296 = m.size.at(2);
    x->__f2dace_SOA_theta_v_d_0_s_294 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_d_1_s_295 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_d_2_s_296 = m.lbound.at(2);
    x->theta_v = arr;
  }
}

void deserialize(t_nh_diag* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# exner_pr"});  // Should contain '# exner_pr'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_pr)>::type>(s);
    x->__f2dace_SA_exner_pr_d_0_s_297 = m.size.at(0);
    x->__f2dace_SA_exner_pr_d_1_s_298 = m.size.at(1);
    x->__f2dace_SA_exner_pr_d_2_s_299 = m.size.at(2);
    x->__f2dace_SOA_exner_pr_d_0_s_297 = m.lbound.at(0);
    x->__f2dace_SOA_exner_pr_d_1_s_298 = m.lbound.at(1);
    x->__f2dace_SOA_exner_pr_d_2_s_299 = m.lbound.at(2);
    x->exner_pr = arr;
  }

  read_line(s, {"# mass_fl_e"});  // Should contain '# mass_fl_e'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mass_fl_e)>::type>(s);
    x->__f2dace_SA_mass_fl_e_d_0_s_300 = m.size.at(0);
    x->__f2dace_SA_mass_fl_e_d_1_s_301 = m.size.at(1);
    x->__f2dace_SA_mass_fl_e_d_2_s_302 = m.size.at(2);
    x->__f2dace_SOA_mass_fl_e_d_0_s_300 = m.lbound.at(0);
    x->__f2dace_SOA_mass_fl_e_d_1_s_301 = m.lbound.at(1);
    x->__f2dace_SOA_mass_fl_e_d_2_s_302 = m.lbound.at(2);
    x->mass_fl_e = arr;
  }

  read_line(s, {"# rho_ic"});  // Should contain '# rho_ic'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ic)>::type>(s);
    x->__f2dace_SA_rho_ic_d_0_s_303 = m.size.at(0);
    x->__f2dace_SA_rho_ic_d_1_s_304 = m.size.at(1);
    x->__f2dace_SA_rho_ic_d_2_s_305 = m.size.at(2);
    x->__f2dace_SOA_rho_ic_d_0_s_303 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ic_d_1_s_304 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ic_d_2_s_305 = m.lbound.at(2);
    x->rho_ic = arr;
  }

  read_line(s, {"# theta_v_ic"});  // Should contain '# theta_v_ic'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v_ic)>::type>(s);
    x->__f2dace_SA_theta_v_ic_d_0_s_306 = m.size.at(0);
    x->__f2dace_SA_theta_v_ic_d_1_s_307 = m.size.at(1);
    x->__f2dace_SA_theta_v_ic_d_2_s_308 = m.size.at(2);
    x->__f2dace_SOA_theta_v_ic_d_0_s_306 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_ic_d_1_s_307 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_ic_d_2_s_308 = m.lbound.at(2);
    x->theta_v_ic = arr;
  }

  read_line(s, {"# grf_tend_vn"});  // Should contain '# grf_tend_vn'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_vn)>::type>(s);
    x->__f2dace_SA_grf_tend_vn_d_0_s_309 = m.size.at(0);
    x->__f2dace_SA_grf_tend_vn_d_1_s_310 = m.size.at(1);
    x->__f2dace_SA_grf_tend_vn_d_2_s_311 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_vn_d_0_s_309 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_vn_d_1_s_310 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_vn_d_2_s_311 = m.lbound.at(2);
    x->grf_tend_vn = arr;
  }

  read_line(s, {"# grf_tend_w"});  // Should contain '# grf_tend_w'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_w)>::type>(s);
    x->__f2dace_SA_grf_tend_w_d_0_s_312 = m.size.at(0);
    x->__f2dace_SA_grf_tend_w_d_1_s_313 = m.size.at(1);
    x->__f2dace_SA_grf_tend_w_d_2_s_314 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_w_d_0_s_312 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_w_d_1_s_313 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_w_d_2_s_314 = m.lbound.at(2);
    x->grf_tend_w = arr;
  }

  read_line(s, {"# grf_tend_rho"});  // Should contain '# grf_tend_rho'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_rho)>::type>(s);
    x->__f2dace_SA_grf_tend_rho_d_0_s_315 = m.size.at(0);
    x->__f2dace_SA_grf_tend_rho_d_1_s_316 = m.size.at(1);
    x->__f2dace_SA_grf_tend_rho_d_2_s_317 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_rho_d_0_s_315 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_rho_d_1_s_316 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_rho_d_2_s_317 = m.lbound.at(2);
    x->grf_tend_rho = arr;
  }

  read_line(s, {"# grf_tend_thv"});  // Should contain '# grf_tend_thv'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_thv)>::type>(s);
    x->__f2dace_SA_grf_tend_thv_d_0_s_318 = m.size.at(0);
    x->__f2dace_SA_grf_tend_thv_d_1_s_319 = m.size.at(1);
    x->__f2dace_SA_grf_tend_thv_d_2_s_320 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_thv_d_0_s_318 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_thv_d_1_s_319 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_thv_d_2_s_320 = m.lbound.at(2);
    x->grf_tend_thv = arr;
  }

  read_line(s, {"# vn_incr"});  // Should contain '# vn_incr'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_incr)>::type>(s);
    x->__f2dace_SA_vn_incr_d_0_s_321 = m.size.at(0);
    x->__f2dace_SA_vn_incr_d_1_s_322 = m.size.at(1);
    x->__f2dace_SA_vn_incr_d_2_s_323 = m.size.at(2);
    x->__f2dace_SOA_vn_incr_d_0_s_321 = m.lbound.at(0);
    x->__f2dace_SOA_vn_incr_d_1_s_322 = m.lbound.at(1);
    x->__f2dace_SOA_vn_incr_d_2_s_323 = m.lbound.at(2);
    x->vn_incr = arr;
  }

  read_line(s, {"# exner_incr"});  // Should contain '# exner_incr'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_incr)>::type>(s);
    x->__f2dace_SA_exner_incr_d_0_s_324 = m.size.at(0);
    x->__f2dace_SA_exner_incr_d_1_s_325 = m.size.at(1);
    x->__f2dace_SA_exner_incr_d_2_s_326 = m.size.at(2);
    x->__f2dace_SOA_exner_incr_d_0_s_324 = m.lbound.at(0);
    x->__f2dace_SOA_exner_incr_d_1_s_325 = m.lbound.at(1);
    x->__f2dace_SOA_exner_incr_d_2_s_326 = m.lbound.at(2);
    x->exner_incr = arr;
  }

  read_line(s, {"# rho_incr"});  // Should contain '# rho_incr'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_incr)>::type>(s);
    x->__f2dace_SA_rho_incr_d_0_s_327 = m.size.at(0);
    x->__f2dace_SA_rho_incr_d_1_s_328 = m.size.at(1);
    x->__f2dace_SA_rho_incr_d_2_s_329 = m.size.at(2);
    x->__f2dace_SOA_rho_incr_d_0_s_327 = m.lbound.at(0);
    x->__f2dace_SOA_rho_incr_d_1_s_328 = m.lbound.at(1);
    x->__f2dace_SOA_rho_incr_d_2_s_329 = m.lbound.at(2);
    x->rho_incr = arr;
  }

  read_line(s, {"# vt"});  // Should contain '# vt'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vt)>::type>(s);
    x->__f2dace_SA_vt_d_0_s_330 = m.size.at(0);
    x->__f2dace_SA_vt_d_1_s_331 = m.size.at(1);
    x->__f2dace_SA_vt_d_2_s_332 = m.size.at(2);
    x->__f2dace_SOA_vt_d_0_s_330 = m.lbound.at(0);
    x->__f2dace_SOA_vt_d_1_s_331 = m.lbound.at(1);
    x->__f2dace_SOA_vt_d_2_s_332 = m.lbound.at(2);
    x->vt = arr;
  }

  read_line(s, {"# ddt_exner_phy"});  // Should contain '# ddt_exner_phy'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_exner_phy)>::type>(s);
    x->__f2dace_SA_ddt_exner_phy_d_0_s_333 = m.size.at(0);
    x->__f2dace_SA_ddt_exner_phy_d_1_s_334 = m.size.at(1);
    x->__f2dace_SA_ddt_exner_phy_d_2_s_335 = m.size.at(2);
    x->__f2dace_SOA_ddt_exner_phy_d_0_s_333 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_exner_phy_d_1_s_334 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_exner_phy_d_2_s_335 = m.lbound.at(2);
    x->ddt_exner_phy = arr;
  }

  read_line(s, {"# ddt_vn_phy"});  // Should contain '# ddt_vn_phy'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_phy)>::type>(s);
    x->__f2dace_SA_ddt_vn_phy_d_0_s_336 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_phy_d_1_s_337 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_phy_d_2_s_338 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_phy_d_0_s_336 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_phy_d_1_s_337 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_phy_d_2_s_338 = m.lbound.at(2);
    x->ddt_vn_phy = arr;
  }

  read_line(s, {"# exner_dyn_incr"});  // Should contain '# exner_dyn_incr'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_dyn_incr)>::type>(s);
    x->__f2dace_SA_exner_dyn_incr_d_0_s_339 = m.size.at(0);
    x->__f2dace_SA_exner_dyn_incr_d_1_s_340 = m.size.at(1);
    x->__f2dace_SA_exner_dyn_incr_d_2_s_341 = m.size.at(2);
    x->__f2dace_SOA_exner_dyn_incr_d_0_s_339 = m.lbound.at(0);
    x->__f2dace_SOA_exner_dyn_incr_d_1_s_340 = m.lbound.at(1);
    x->__f2dace_SOA_exner_dyn_incr_d_2_s_341 = m.lbound.at(2);
    x->exner_dyn_incr = arr;
  }

  read_line(s, {"# vn_ie"});  // Should contain '# vn_ie'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ie)>::type>(s);
    x->__f2dace_SA_vn_ie_d_0_s_342 = m.size.at(0);
    x->__f2dace_SA_vn_ie_d_1_s_343 = m.size.at(1);
    x->__f2dace_SA_vn_ie_d_2_s_344 = m.size.at(2);
    x->__f2dace_SOA_vn_ie_d_0_s_342 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ie_d_1_s_343 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ie_d_2_s_344 = m.lbound.at(2);
    x->vn_ie = arr;
  }

  read_line(s, {"# w_concorr_c"});  // Should contain '# w_concorr_c'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->w_concorr_c)>::type>(s);
    x->__f2dace_SA_w_concorr_c_d_0_s_345 = m.size.at(0);
    x->__f2dace_SA_w_concorr_c_d_1_s_346 = m.size.at(1);
    x->__f2dace_SA_w_concorr_c_d_2_s_347 = m.size.at(2);
    x->__f2dace_SOA_w_concorr_c_d_0_s_345 = m.lbound.at(0);
    x->__f2dace_SOA_w_concorr_c_d_1_s_346 = m.lbound.at(1);
    x->__f2dace_SOA_w_concorr_c_d_2_s_347 = m.lbound.at(2);
    x->w_concorr_c = arr;
  }

  read_line(s, {"# mass_fl_e_sv"});  // Should contain '# mass_fl_e_sv'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mass_fl_e_sv)>::type>(s);
    x->__f2dace_SA_mass_fl_e_sv_d_0_s_348 = m.size.at(0);
    x->__f2dace_SA_mass_fl_e_sv_d_1_s_349 = m.size.at(1);
    x->__f2dace_SA_mass_fl_e_sv_d_2_s_350 = m.size.at(2);
    x->__f2dace_SOA_mass_fl_e_sv_d_0_s_348 = m.lbound.at(0);
    x->__f2dace_SOA_mass_fl_e_sv_d_1_s_349 = m.lbound.at(1);
    x->__f2dace_SOA_mass_fl_e_sv_d_2_s_350 = m.lbound.at(2);
    x->mass_fl_e_sv = arr;
  }

  read_line(s, {"# ddt_vn_apc_pc"});  // Should contain '# ddt_vn_apc_pc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_apc_pc)>::type>(s);
    x->__f2dace_SA_ddt_vn_apc_pc_d_0_s_351 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_apc_pc_d_1_s_352 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_apc_pc_d_2_s_353 = m.size.at(2);
    x->__f2dace_SA_ddt_vn_apc_pc_d_3_s_354 = m.size.at(3);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_0_s_351 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_1_s_352 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_2_s_353 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_3_s_354 = m.lbound.at(3);
    x->ddt_vn_apc_pc = arr;
  }

  read_line(s, {"# ddt_w_adv_pc"});  // Should contain '# ddt_w_adv_pc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_w_adv_pc)>::type>(s);
    x->__f2dace_SA_ddt_w_adv_pc_d_0_s_355 = m.size.at(0);
    x->__f2dace_SA_ddt_w_adv_pc_d_1_s_356 = m.size.at(1);
    x->__f2dace_SA_ddt_w_adv_pc_d_2_s_357 = m.size.at(2);
    x->__f2dace_SA_ddt_w_adv_pc_d_3_s_358 = m.size.at(3);
    x->__f2dace_SOA_ddt_w_adv_pc_d_0_s_355 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_w_adv_pc_d_1_s_356 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_w_adv_pc_d_2_s_357 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_w_adv_pc_d_3_s_358 = m.lbound.at(3);
    x->ddt_w_adv_pc = arr;
  }

  read_line(s, {"# max_vcfl_dyn"});  // Should contain '# max_vcfl_dyn'

  deserialize(&(x->max_vcfl_dyn), s);
}

void deserialize(t_nh_ref* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# vn_ref"});  // Should contain '# vn_ref'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ref)>::type>(s);
    x->__f2dace_SA_vn_ref_d_0_s_359 = m.size.at(0);
    x->__f2dace_SA_vn_ref_d_1_s_360 = m.size.at(1);
    x->__f2dace_SA_vn_ref_d_2_s_361 = m.size.at(2);
    x->__f2dace_SOA_vn_ref_d_0_s_359 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ref_d_1_s_360 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ref_d_2_s_361 = m.lbound.at(2);
    x->vn_ref = arr;
  }

  read_line(s, {"# w_ref"});  // Should contain '# w_ref'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->w_ref)>::type>(s);
    x->__f2dace_SA_w_ref_d_0_s_362 = m.size.at(0);
    x->__f2dace_SA_w_ref_d_1_s_363 = m.size.at(1);
    x->__f2dace_SA_w_ref_d_2_s_364 = m.size.at(2);
    x->__f2dace_SOA_w_ref_d_0_s_362 = m.lbound.at(0);
    x->__f2dace_SOA_w_ref_d_1_s_363 = m.lbound.at(1);
    x->__f2dace_SOA_w_ref_d_2_s_364 = m.lbound.at(2);
    x->w_ref = arr;
  }
}

void deserialize(t_nh_metrics* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# rayleigh_w"});  // Should contain '# rayleigh_w'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rayleigh_w)>::type>(s);
    x->__f2dace_SA_rayleigh_w_d_0_s_365 = m.size.at(0);
    x->__f2dace_SOA_rayleigh_w_d_0_s_365 = m.lbound.at(0);
    x->rayleigh_w = arr;
  }

  read_line(s, {"# rayleigh_vn"});  // Should contain '# rayleigh_vn'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rayleigh_vn)>::type>(s);
    x->__f2dace_SA_rayleigh_vn_d_0_s_366 = m.size.at(0);
    x->__f2dace_SOA_rayleigh_vn_d_0_s_366 = m.lbound.at(0);
    x->rayleigh_vn = arr;
  }

  read_line(s, {"# scalfac_dd3d"});  // Should contain '# scalfac_dd3d'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->scalfac_dd3d)>::type>(s);
    x->__f2dace_SA_scalfac_dd3d_d_0_s_367 = m.size.at(0);
    x->__f2dace_SOA_scalfac_dd3d_d_0_s_367 = m.lbound.at(0);
    x->scalfac_dd3d = arr;
  }

  read_line(s, {"# hmask_dd3d"});  // Should contain '# hmask_dd3d'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->hmask_dd3d)>::type>(s);
    x->__f2dace_SA_hmask_dd3d_d_0_s_368 = m.size.at(0);
    x->__f2dace_SA_hmask_dd3d_d_1_s_369 = m.size.at(1);
    x->__f2dace_SOA_hmask_dd3d_d_0_s_368 = m.lbound.at(0);
    x->__f2dace_SOA_hmask_dd3d_d_1_s_369 = m.lbound.at(1);
    x->hmask_dd3d = arr;
  }

  read_line(s, {"# vwind_expl_wgt"});  // Should contain '# vwind_expl_wgt'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vwind_expl_wgt)>::type>(s);
    x->__f2dace_SA_vwind_expl_wgt_d_0_s_370 = m.size.at(0);
    x->__f2dace_SA_vwind_expl_wgt_d_1_s_371 = m.size.at(1);
    x->__f2dace_SOA_vwind_expl_wgt_d_0_s_370 = m.lbound.at(0);
    x->__f2dace_SOA_vwind_expl_wgt_d_1_s_371 = m.lbound.at(1);
    x->vwind_expl_wgt = arr;
  }

  read_line(s, {"# vwind_impl_wgt"});  // Should contain '# vwind_impl_wgt'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vwind_impl_wgt)>::type>(s);
    x->__f2dace_SA_vwind_impl_wgt_d_0_s_372 = m.size.at(0);
    x->__f2dace_SA_vwind_impl_wgt_d_1_s_373 = m.size.at(1);
    x->__f2dace_SOA_vwind_impl_wgt_d_0_s_372 = m.lbound.at(0);
    x->__f2dace_SOA_vwind_impl_wgt_d_1_s_373 = m.lbound.at(1);
    x->vwind_impl_wgt = arr;
  }

  read_line(s, {"# ddxn_z_full"});  // Should contain '# ddxn_z_full'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddxn_z_full)>::type>(s);
    x->__f2dace_SA_ddxn_z_full_d_0_s_374 = m.size.at(0);
    x->__f2dace_SA_ddxn_z_full_d_1_s_375 = m.size.at(1);
    x->__f2dace_SA_ddxn_z_full_d_2_s_376 = m.size.at(2);
    x->__f2dace_SOA_ddxn_z_full_d_0_s_374 = m.lbound.at(0);
    x->__f2dace_SOA_ddxn_z_full_d_1_s_375 = m.lbound.at(1);
    x->__f2dace_SOA_ddxn_z_full_d_2_s_376 = m.lbound.at(2);
    x->ddxn_z_full = arr;
  }

  read_line(s, {"# ddxt_z_full"});  // Should contain '# ddxt_z_full'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddxt_z_full)>::type>(s);
    x->__f2dace_SA_ddxt_z_full_d_0_s_377 = m.size.at(0);
    x->__f2dace_SA_ddxt_z_full_d_1_s_378 = m.size.at(1);
    x->__f2dace_SA_ddxt_z_full_d_2_s_379 = m.size.at(2);
    x->__f2dace_SOA_ddxt_z_full_d_0_s_377 = m.lbound.at(0);
    x->__f2dace_SOA_ddxt_z_full_d_1_s_378 = m.lbound.at(1);
    x->__f2dace_SOA_ddxt_z_full_d_2_s_379 = m.lbound.at(2);
    x->ddxt_z_full = arr;
  }

  read_line(s, {"# ddqz_z_full_e"});  // Should contain '# ddqz_z_full_e'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_full_e)>::type>(s);
    x->__f2dace_SA_ddqz_z_full_e_d_0_s_380 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_full_e_d_1_s_381 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_full_e_d_2_s_382 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_full_e_d_0_s_380 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_full_e_d_1_s_381 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_full_e_d_2_s_382 = m.lbound.at(2);
    x->ddqz_z_full_e = arr;
  }

  read_line(s, {"# ddqz_z_half"});  // Should contain '# ddqz_z_half'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_half)>::type>(s);
    x->__f2dace_SA_ddqz_z_half_d_0_s_383 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_half_d_1_s_384 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_half_d_2_s_385 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_half_d_0_s_383 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_half_d_1_s_384 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_half_d_2_s_385 = m.lbound.at(2);
    x->ddqz_z_half = arr;
  }

  read_line(s, {"# inv_ddqz_z_full"});  // Should contain '# inv_ddqz_z_full'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->inv_ddqz_z_full)>::type>(
            s);
    x->__f2dace_SA_inv_ddqz_z_full_d_0_s_386 = m.size.at(0);
    x->__f2dace_SA_inv_ddqz_z_full_d_1_s_387 = m.size.at(1);
    x->__f2dace_SA_inv_ddqz_z_full_d_2_s_388 = m.size.at(2);
    x->__f2dace_SOA_inv_ddqz_z_full_d_0_s_386 = m.lbound.at(0);
    x->__f2dace_SOA_inv_ddqz_z_full_d_1_s_387 = m.lbound.at(1);
    x->__f2dace_SOA_inv_ddqz_z_full_d_2_s_388 = m.lbound.at(2);
    x->inv_ddqz_z_full = arr;
  }

  read_line(s, {"# wgtfac_c"});  // Should contain '# wgtfac_c'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfac_c)>::type>(s);
    x->__f2dace_SA_wgtfac_c_d_0_s_389 = m.size.at(0);
    x->__f2dace_SA_wgtfac_c_d_1_s_390 = m.size.at(1);
    x->__f2dace_SA_wgtfac_c_d_2_s_391 = m.size.at(2);
    x->__f2dace_SOA_wgtfac_c_d_0_s_389 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfac_c_d_1_s_390 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfac_c_d_2_s_391 = m.lbound.at(2);
    x->wgtfac_c = arr;
  }

  read_line(s, {"# wgtfac_e"});  // Should contain '# wgtfac_e'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfac_e)>::type>(s);
    x->__f2dace_SA_wgtfac_e_d_0_s_392 = m.size.at(0);
    x->__f2dace_SA_wgtfac_e_d_1_s_393 = m.size.at(1);
    x->__f2dace_SA_wgtfac_e_d_2_s_394 = m.size.at(2);
    x->__f2dace_SOA_wgtfac_e_d_0_s_392 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfac_e_d_1_s_393 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfac_e_d_2_s_394 = m.lbound.at(2);
    x->wgtfac_e = arr;
  }

  read_line(s, {"# wgtfacq_c"});  // Should contain '# wgtfacq_c'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq_c)>::type>(s);
    x->__f2dace_SA_wgtfacq_c_d_0_s_395 = m.size.at(0);
    x->__f2dace_SA_wgtfacq_c_d_1_s_396 = m.size.at(1);
    x->__f2dace_SA_wgtfacq_c_d_2_s_397 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq_c_d_0_s_395 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq_c_d_1_s_396 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq_c_d_2_s_397 = m.lbound.at(2);
    x->wgtfacq_c = arr;
  }

  read_line(s, {"# wgtfacq_e"});  // Should contain '# wgtfacq_e'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq_e)>::type>(s);
    x->__f2dace_SA_wgtfacq_e_d_0_s_398 = m.size.at(0);
    x->__f2dace_SA_wgtfacq_e_d_1_s_399 = m.size.at(1);
    x->__f2dace_SA_wgtfacq_e_d_2_s_400 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq_e_d_0_s_398 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq_e_d_1_s_399 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq_e_d_2_s_400 = m.lbound.at(2);
    x->wgtfacq_e = arr;
  }

  read_line(s, {"# wgtfacq1_c"});  // Should contain '# wgtfacq1_c'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq1_c)>::type>(s);
    x->__f2dace_SA_wgtfacq1_c_d_0_s_401 = m.size.at(0);
    x->__f2dace_SA_wgtfacq1_c_d_1_s_402 = m.size.at(1);
    x->__f2dace_SA_wgtfacq1_c_d_2_s_403 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq1_c_d_0_s_401 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq1_c_d_1_s_402 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq1_c_d_2_s_403 = m.lbound.at(2);
    x->wgtfacq1_c = arr;
  }

  read_line(s, {"# coeff_gradekin"});  // Should contain '# coeff_gradekin'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff_gradekin)>::type>(s);
    x->__f2dace_SA_coeff_gradekin_d_0_s_404 = m.size.at(0);
    x->__f2dace_SA_coeff_gradekin_d_1_s_405 = m.size.at(1);
    x->__f2dace_SA_coeff_gradekin_d_2_s_406 = m.size.at(2);
    x->__f2dace_SOA_coeff_gradekin_d_0_s_404 = m.lbound.at(0);
    x->__f2dace_SOA_coeff_gradekin_d_1_s_405 = m.lbound.at(1);
    x->__f2dace_SOA_coeff_gradekin_d_2_s_406 = m.lbound.at(2);
    x->coeff_gradekin = arr;
  }

  read_line(s, {"# coeff1_dwdz"});  // Should contain '# coeff1_dwdz'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff1_dwdz)>::type>(s);
    x->__f2dace_SA_coeff1_dwdz_d_0_s_407 = m.size.at(0);
    x->__f2dace_SA_coeff1_dwdz_d_1_s_408 = m.size.at(1);
    x->__f2dace_SA_coeff1_dwdz_d_2_s_409 = m.size.at(2);
    x->__f2dace_SOA_coeff1_dwdz_d_0_s_407 = m.lbound.at(0);
    x->__f2dace_SOA_coeff1_dwdz_d_1_s_408 = m.lbound.at(1);
    x->__f2dace_SOA_coeff1_dwdz_d_2_s_409 = m.lbound.at(2);
    x->coeff1_dwdz = arr;
  }

  read_line(s, {"# coeff2_dwdz"});  // Should contain '# coeff2_dwdz'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff2_dwdz)>::type>(s);
    x->__f2dace_SA_coeff2_dwdz_d_0_s_410 = m.size.at(0);
    x->__f2dace_SA_coeff2_dwdz_d_1_s_411 = m.size.at(1);
    x->__f2dace_SA_coeff2_dwdz_d_2_s_412 = m.size.at(2);
    x->__f2dace_SOA_coeff2_dwdz_d_0_s_410 = m.lbound.at(0);
    x->__f2dace_SOA_coeff2_dwdz_d_1_s_411 = m.lbound.at(1);
    x->__f2dace_SOA_coeff2_dwdz_d_2_s_412 = m.lbound.at(2);
    x->coeff2_dwdz = arr;
  }

  read_line(s, {"# zdiff_gradp"});  // Should contain '# zdiff_gradp'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->zdiff_gradp)>::type>(s);
    x->__f2dace_SA_zdiff_gradp_d_0_s_413 = m.size.at(0);
    x->__f2dace_SA_zdiff_gradp_d_1_s_414 = m.size.at(1);
    x->__f2dace_SA_zdiff_gradp_d_2_s_415 = m.size.at(2);
    x->__f2dace_SA_zdiff_gradp_d_3_s_416 = m.size.at(3);
    x->__f2dace_SOA_zdiff_gradp_d_0_s_413 = m.lbound.at(0);
    x->__f2dace_SOA_zdiff_gradp_d_1_s_414 = m.lbound.at(1);
    x->__f2dace_SOA_zdiff_gradp_d_2_s_415 = m.lbound.at(2);
    x->__f2dace_SOA_zdiff_gradp_d_3_s_416 = m.lbound.at(3);
    x->zdiff_gradp = arr;
  }

  read_line(s, {"# coeff_gradp"});  // Should contain '# coeff_gradp'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff_gradp)>::type>(s);
    x->__f2dace_SA_coeff_gradp_d_0_s_417 = m.size.at(0);
    x->__f2dace_SA_coeff_gradp_d_1_s_418 = m.size.at(1);
    x->__f2dace_SA_coeff_gradp_d_2_s_419 = m.size.at(2);
    x->__f2dace_SA_coeff_gradp_d_3_s_420 = m.size.at(3);
    x->__f2dace_SOA_coeff_gradp_d_0_s_417 = m.lbound.at(0);
    x->__f2dace_SOA_coeff_gradp_d_1_s_418 = m.lbound.at(1);
    x->__f2dace_SOA_coeff_gradp_d_2_s_419 = m.lbound.at(2);
    x->__f2dace_SOA_coeff_gradp_d_3_s_420 = m.lbound.at(3);
    x->coeff_gradp = arr;
  }

  read_line(s, {"# exner_exfac"});  // Should contain '# exner_exfac'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_exfac)>::type>(s);
    x->__f2dace_SA_exner_exfac_d_0_s_421 = m.size.at(0);
    x->__f2dace_SA_exner_exfac_d_1_s_422 = m.size.at(1);
    x->__f2dace_SA_exner_exfac_d_2_s_423 = m.size.at(2);
    x->__f2dace_SOA_exner_exfac_d_0_s_421 = m.lbound.at(0);
    x->__f2dace_SOA_exner_exfac_d_1_s_422 = m.lbound.at(1);
    x->__f2dace_SOA_exner_exfac_d_2_s_423 = m.lbound.at(2);
    x->exner_exfac = arr;
  }

  read_line(s, {"# theta_ref_mc"});  // Should contain '# theta_ref_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_ref_mc)>::type>(s);
    x->__f2dace_SA_theta_ref_mc_d_0_s_424 = m.size.at(0);
    x->__f2dace_SA_theta_ref_mc_d_1_s_425 = m.size.at(1);
    x->__f2dace_SA_theta_ref_mc_d_2_s_426 = m.size.at(2);
    x->__f2dace_SOA_theta_ref_mc_d_0_s_424 = m.lbound.at(0);
    x->__f2dace_SOA_theta_ref_mc_d_1_s_425 = m.lbound.at(1);
    x->__f2dace_SOA_theta_ref_mc_d_2_s_426 = m.lbound.at(2);
    x->theta_ref_mc = arr;
  }

  read_line(s, {"# theta_ref_me"});  // Should contain '# theta_ref_me'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_ref_me)>::type>(s);
    x->__f2dace_SA_theta_ref_me_d_0_s_427 = m.size.at(0);
    x->__f2dace_SA_theta_ref_me_d_1_s_428 = m.size.at(1);
    x->__f2dace_SA_theta_ref_me_d_2_s_429 = m.size.at(2);
    x->__f2dace_SOA_theta_ref_me_d_0_s_427 = m.lbound.at(0);
    x->__f2dace_SOA_theta_ref_me_d_1_s_428 = m.lbound.at(1);
    x->__f2dace_SOA_theta_ref_me_d_2_s_429 = m.lbound.at(2);
    x->theta_ref_me = arr;
  }

  read_line(s, {"# theta_ref_ic"});  // Should contain '# theta_ref_ic'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_ref_ic)>::type>(s);
    x->__f2dace_SA_theta_ref_ic_d_0_s_430 = m.size.at(0);
    x->__f2dace_SA_theta_ref_ic_d_1_s_431 = m.size.at(1);
    x->__f2dace_SA_theta_ref_ic_d_2_s_432 = m.size.at(2);
    x->__f2dace_SOA_theta_ref_ic_d_0_s_430 = m.lbound.at(0);
    x->__f2dace_SOA_theta_ref_ic_d_1_s_431 = m.lbound.at(1);
    x->__f2dace_SOA_theta_ref_ic_d_2_s_432 = m.lbound.at(2);
    x->theta_ref_ic = arr;
  }

  read_line(s, {"# exner_ref_mc"});  // Should contain '# exner_ref_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_ref_mc)>::type>(s);
    x->__f2dace_SA_exner_ref_mc_d_0_s_433 = m.size.at(0);
    x->__f2dace_SA_exner_ref_mc_d_1_s_434 = m.size.at(1);
    x->__f2dace_SA_exner_ref_mc_d_2_s_435 = m.size.at(2);
    x->__f2dace_SOA_exner_ref_mc_d_0_s_433 = m.lbound.at(0);
    x->__f2dace_SOA_exner_ref_mc_d_1_s_434 = m.lbound.at(1);
    x->__f2dace_SOA_exner_ref_mc_d_2_s_435 = m.lbound.at(2);
    x->exner_ref_mc = arr;
  }

  read_line(s, {"# rho_ref_mc"});  // Should contain '# rho_ref_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ref_mc)>::type>(s);
    x->__f2dace_SA_rho_ref_mc_d_0_s_436 = m.size.at(0);
    x->__f2dace_SA_rho_ref_mc_d_1_s_437 = m.size.at(1);
    x->__f2dace_SA_rho_ref_mc_d_2_s_438 = m.size.at(2);
    x->__f2dace_SOA_rho_ref_mc_d_0_s_436 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ref_mc_d_1_s_437 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ref_mc_d_2_s_438 = m.lbound.at(2);
    x->rho_ref_mc = arr;
  }

  read_line(s, {"# rho_ref_me"});  // Should contain '# rho_ref_me'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ref_me)>::type>(s);
    x->__f2dace_SA_rho_ref_me_d_0_s_439 = m.size.at(0);
    x->__f2dace_SA_rho_ref_me_d_1_s_440 = m.size.at(1);
    x->__f2dace_SA_rho_ref_me_d_2_s_441 = m.size.at(2);
    x->__f2dace_SOA_rho_ref_me_d_0_s_439 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ref_me_d_1_s_440 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ref_me_d_2_s_441 = m.lbound.at(2);
    x->rho_ref_me = arr;
  }

  read_line(s,
            {"# d_exner_dz_ref_ic"});  // Should contain '# d_exner_dz_ref_ic'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->d_exner_dz_ref_ic)>::type>(
            s);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_0_s_442 = m.size.at(0);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_1_s_443 = m.size.at(1);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_2_s_444 = m.size.at(2);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_0_s_442 = m.lbound.at(0);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_1_s_443 = m.lbound.at(1);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_2_s_444 = m.lbound.at(2);
    x->d_exner_dz_ref_ic = arr;
  }

  read_line(s, {"# d2dexdz2_fac1_mc"});  // Should contain '# d2dexdz2_fac1_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->d2dexdz2_fac1_mc)>::type>(
            s);
    x->__f2dace_SA_d2dexdz2_fac1_mc_d_0_s_445 = m.size.at(0);
    x->__f2dace_SA_d2dexdz2_fac1_mc_d_1_s_446 = m.size.at(1);
    x->__f2dace_SA_d2dexdz2_fac1_mc_d_2_s_447 = m.size.at(2);
    x->__f2dace_SOA_d2dexdz2_fac1_mc_d_0_s_445 = m.lbound.at(0);
    x->__f2dace_SOA_d2dexdz2_fac1_mc_d_1_s_446 = m.lbound.at(1);
    x->__f2dace_SOA_d2dexdz2_fac1_mc_d_2_s_447 = m.lbound.at(2);
    x->d2dexdz2_fac1_mc = arr;
  }

  read_line(s, {"# d2dexdz2_fac2_mc"});  // Should contain '# d2dexdz2_fac2_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->d2dexdz2_fac2_mc)>::type>(
            s);
    x->__f2dace_SA_d2dexdz2_fac2_mc_d_0_s_448 = m.size.at(0);
    x->__f2dace_SA_d2dexdz2_fac2_mc_d_1_s_449 = m.size.at(1);
    x->__f2dace_SA_d2dexdz2_fac2_mc_d_2_s_450 = m.size.at(2);
    x->__f2dace_SOA_d2dexdz2_fac2_mc_d_0_s_448 = m.lbound.at(0);
    x->__f2dace_SOA_d2dexdz2_fac2_mc_d_1_s_449 = m.lbound.at(1);
    x->__f2dace_SOA_d2dexdz2_fac2_mc_d_2_s_450 = m.lbound.at(2);
    x->d2dexdz2_fac2_mc = arr;
  }

  read_line(s, {"# pg_exdist"});  // Should contain '# pg_exdist'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_exdist)>::type>(s);
    x->__f2dace_SA_pg_exdist_d_0_s_451 = m.size.at(0);
    x->__f2dace_SOA_pg_exdist_d_0_s_451 = m.lbound.at(0);
    x->pg_exdist = arr;
  }

  read_line(s, {"# vertidx_gradp"});  // Should contain '# vertidx_gradp'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vertidx_gradp)>::type>(s);
    x->__f2dace_SA_vertidx_gradp_d_0_s_452 = m.size.at(0);
    x->__f2dace_SA_vertidx_gradp_d_1_s_453 = m.size.at(1);
    x->__f2dace_SA_vertidx_gradp_d_2_s_454 = m.size.at(2);
    x->__f2dace_SA_vertidx_gradp_d_3_s_455 = m.size.at(3);
    x->__f2dace_SOA_vertidx_gradp_d_0_s_452 = m.lbound.at(0);
    x->__f2dace_SOA_vertidx_gradp_d_1_s_453 = m.lbound.at(1);
    x->__f2dace_SOA_vertidx_gradp_d_2_s_454 = m.lbound.at(2);
    x->__f2dace_SOA_vertidx_gradp_d_3_s_455 = m.lbound.at(3);
    x->vertidx_gradp = arr;
  }

  read_line(s, {"# pg_edgeidx"});  // Should contain '# pg_edgeidx'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_edgeidx)>::type>(s);
    x->__f2dace_SA_pg_edgeidx_d_0_s_456 = m.size.at(0);
    x->__f2dace_SOA_pg_edgeidx_d_0_s_456 = m.lbound.at(0);
    x->pg_edgeidx = arr;
  }

  read_line(s, {"# pg_edgeblk"});  // Should contain '# pg_edgeblk'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_edgeblk)>::type>(s);
    x->__f2dace_SA_pg_edgeblk_d_0_s_457 = m.size.at(0);
    x->__f2dace_SOA_pg_edgeblk_d_0_s_457 = m.lbound.at(0);
    x->pg_edgeblk = arr;
  }

  read_line(s, {"# pg_vertidx"});  // Should contain '# pg_vertidx'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_vertidx)>::type>(s);
    x->__f2dace_SA_pg_vertidx_d_0_s_458 = m.size.at(0);
    x->__f2dace_SOA_pg_vertidx_d_0_s_458 = m.lbound.at(0);
    x->pg_vertidx = arr;
  }

  read_line(s, {"# bdy_halo_c_idx"});  // Should contain '# bdy_halo_c_idx'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->bdy_halo_c_idx)>::type>(s);
    x->__f2dace_SA_bdy_halo_c_idx_d_0_s_459 = m.size.at(0);
    x->__f2dace_SOA_bdy_halo_c_idx_d_0_s_459 = m.lbound.at(0);
    x->bdy_halo_c_idx = arr;
  }

  read_line(s, {"# bdy_halo_c_blk"});  // Should contain '# bdy_halo_c_blk'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->bdy_halo_c_blk)>::type>(s);
    x->__f2dace_SA_bdy_halo_c_blk_d_0_s_460 = m.size.at(0);
    x->__f2dace_SOA_bdy_halo_c_blk_d_0_s_460 = m.lbound.at(0);
    x->bdy_halo_c_blk = arr;
  }

  read_line(s,
            {"# deepatmo_gradh_mc"});  // Should contain '# deepatmo_gradh_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_gradh_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_gradh_mc_d_0_s_461 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_gradh_mc_d_0_s_461 = m.lbound.at(0);
    x->deepatmo_gradh_mc = arr;
  }

  read_line(s, {"# deepatmo_divh_mc"});  // Should contain '# deepatmo_divh_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_divh_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_divh_mc_d_0_s_462 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_divh_mc_d_0_s_462 = m.lbound.at(0);
    x->deepatmo_divh_mc = arr;
  }

  read_line(s, {"# deepatmo_invr_mc"});  // Should contain '# deepatmo_invr_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_invr_mc_d_0_s_463 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_invr_mc_d_0_s_463 = m.lbound.at(0);
    x->deepatmo_invr_mc = arr;
  }

  read_line(s,
            {"# deepatmo_divzu_mc"});  // Should contain '# deepatmo_divzu_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_divzu_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_divzu_mc_d_0_s_464 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_divzu_mc_d_0_s_464 = m.lbound.at(0);
    x->deepatmo_divzu_mc = arr;
  }

  read_line(s,
            {"# deepatmo_divzl_mc"});  // Should contain '# deepatmo_divzl_mc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_divzl_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_divzl_mc_d_0_s_465 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_divzl_mc_d_0_s_465 = m.lbound.at(0);
    x->deepatmo_divzl_mc = arr;
  }

  read_line(s,
            {"# deepatmo_gradh_ifc"});  // Should contain '# deepatmo_gradh_ifc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<
        std::remove_pointer<decltype(x->deepatmo_gradh_ifc)>::type>(s);
    x->__f2dace_SA_deepatmo_gradh_ifc_d_0_s_466 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_gradh_ifc_d_0_s_466 = m.lbound.at(0);
    x->deepatmo_gradh_ifc = arr;
  }

  read_line(s,
            {"# deepatmo_invr_ifc"});  // Should contain '# deepatmo_invr_ifc'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_ifc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_invr_ifc_d_0_s_467 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_invr_ifc_d_0_s_467 = m.lbound.at(0);
    x->deepatmo_invr_ifc = arr;
  }

  read_line(s, {"# mask_prog_halo_c"});  // Should contain '# mask_prog_halo_c'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mask_prog_halo_c)>::type>(
            s);
    x->__f2dace_SA_mask_prog_halo_c_d_0_s_468 = m.size.at(0);
    x->__f2dace_SA_mask_prog_halo_c_d_1_s_469 = m.size.at(1);
    x->__f2dace_SOA_mask_prog_halo_c_d_0_s_468 = m.lbound.at(0);
    x->__f2dace_SOA_mask_prog_halo_c_d_1_s_469 = m.lbound.at(1);
    x->mask_prog_halo_c = arr;
  }
}

void deserialize(t_nh_state* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# prog"});  // Should contain '# prog'

  m = read_array_meta(s);

  // TODO: THIS IS POTENTIALLY BUGGY, BECAUSE IT IS NOT REALLY TESTED.
  // We only need to allocate a volume of contiguous memory, and let DaCe
  // interpret (assuming it follows the same protocol as us).
  x->prog = m.read<std::remove_pointer<decltype(x->prog)>::type>(s);

  read_line(s, {"# diag"});  // Should contain '# diag'

  x->diag = new std::remove_pointer<decltype(x->diag)>::type;
  deserialize(x->diag, s);

  read_line(s, {"# ref"});  // Should contain '# ref'

  x->ref = new std::remove_pointer<decltype(x->ref)>::type;
  deserialize(x->ref, s);

  read_line(s, {"# metrics"});  // Should contain '# metrics'

  x->metrics = new std::remove_pointer<decltype(x->metrics)>::type;
  deserialize(x->metrics, s);
}

void deserialize(t_prepare_adv* x, std::istream& s) {
  bool yep;
  array_meta m;
  read_line(s, {"# mass_flx_me"});  // Should contain '# mass_flx_me'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mass_flx_me)>::type>(s);
    x->__f2dace_SA_mass_flx_me_d_0_s_482 = m.size.at(0);
    x->__f2dace_SA_mass_flx_me_d_1_s_483 = m.size.at(1);
    x->__f2dace_SA_mass_flx_me_d_2_s_484 = m.size.at(2);
    x->__f2dace_SOA_mass_flx_me_d_0_s_482 = m.lbound.at(0);
    x->__f2dace_SOA_mass_flx_me_d_1_s_483 = m.lbound.at(1);
    x->__f2dace_SOA_mass_flx_me_d_2_s_484 = m.lbound.at(2);
    x->mass_flx_me = arr;
  }

  read_line(s, {"# mass_flx_ic"});  // Should contain '# mass_flx_ic'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mass_flx_ic)>::type>(s);
    x->__f2dace_SA_mass_flx_ic_d_0_s_485 = m.size.at(0);
    x->__f2dace_SA_mass_flx_ic_d_1_s_486 = m.size.at(1);
    x->__f2dace_SA_mass_flx_ic_d_2_s_487 = m.size.at(2);
    x->__f2dace_SOA_mass_flx_ic_d_0_s_485 = m.lbound.at(0);
    x->__f2dace_SOA_mass_flx_ic_d_1_s_486 = m.lbound.at(1);
    x->__f2dace_SOA_mass_flx_ic_d_2_s_487 = m.lbound.at(2);
    x->mass_flx_ic = arr;
  }

  read_line(s, {"# vol_flx_ic"});  // Should contain '# vol_flx_ic'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vol_flx_ic)>::type>(s);
    x->__f2dace_SA_vol_flx_ic_d_0_s_488 = m.size.at(0);
    x->__f2dace_SA_vol_flx_ic_d_1_s_489 = m.size.at(1);
    x->__f2dace_SA_vol_flx_ic_d_2_s_490 = m.size.at(2);
    x->__f2dace_SOA_vol_flx_ic_d_0_s_488 = m.lbound.at(0);
    x->__f2dace_SOA_vol_flx_ic_d_1_s_489 = m.lbound.at(1);
    x->__f2dace_SOA_vol_flx_ic_d_2_s_490 = m.lbound.at(2);
    x->vol_flx_ic = arr;
  }

  read_line(s, {"# vn_traj"});  // Should contain '# vn_traj'

  read_line(s, {"# assoc"});  // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_traj)>::type>(s);
    x->__f2dace_SA_vn_traj_d_0_s_491 = m.size.at(0);
    x->__f2dace_SA_vn_traj_d_1_s_492 = m.size.at(1);
    x->__f2dace_SA_vn_traj_d_2_s_493 = m.size.at(2);
    x->__f2dace_SOA_vn_traj_d_0_s_491 = m.lbound.at(0);
    x->__f2dace_SOA_vn_traj_d_1_s_492 = m.lbound.at(1);
    x->__f2dace_SOA_vn_traj_d_2_s_493 = m.lbound.at(2);
    x->vn_traj = arr;
  }
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
  s << std::setprecision(20) << x;
  if (trailing_newline) s << std::endl;
}
void add_line(bool x, std::ostream& s, bool trailing_newline = true) {
  add_line(int(x), s, trailing_newline);
}
template <typename T>
std::string serialize(const T* x) {
  if constexpr (std::is_pointer_v<T>) {
    return serialize(*x);
  } else {
    std::stringstream s;
    add_line(*x, s, false);
    return s.str();
  }
}
std::string serialize(int x) {
  std::stringstream s;
  s << x;
  return s.str();
}
std::string serialize(long x) {
  std::stringstream s;
  s << x;
  return s.str();
}
std::string serialize(long long x) {
  std::stringstream s;
  s << x;
  return s.str();
}
std::string serialize(float x) {
  std::stringstream s;
  s << std::setprecision(20) << x;
  return s.str();
}
std::string serialize(double x) {
  std::stringstream s;
  s << std::setprecision(20) << x;
  return s.str();
}
std::string serialize(long double x) {
  std::stringstream s;
  s << std::setprecision(20) << x;
  return s.str();
}
std::string serialize(bool x) { return serialize(int(x)); }

std::string serialize(const t_grid_domain_decomp_info* x) {
  std::stringstream s;
  add_line("# owner_mask", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->owner_mask);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->c_lin_e);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->e_bln_c_s);
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

  add_line("# e_flx_avg", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->e_flx_avg);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->e_flx_avg[i]), s);
    }
  }

  add_line("# cells_aw_verts", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->cells_aw_verts);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->rbf_vec_coeff_e);
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

  add_line("# geofac_div", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->geofac_div);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->geofac_div[i]), s);
    }
  }

  add_line("# geofac_grdiv", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->geofac_grdiv);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->geofac_rot);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->geofac_n2s);
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

  add_line("# geofac_grg", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->geofac_grg);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->geofac_grg[i]), s);
    }
  }

  add_line("# pos_on_tplane_e", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->pos_on_tplane_e);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->pos_on_tplane_e[i]), s);
    }
  }

  add_line("# nudgecoeff_e", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->nudgecoeff_e);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->nudgecoeff_e[i]), s);
    }
  }

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_tangent_vectors* x) {
  std::stringstream s;
  add_line("# v1", s);
  add_line(serialize(x->v1), s);
  add_line("# v2", s);
  add_line(serialize(x->v2), s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_grid_cells* x) {
  std::stringstream s;
  add_line("# neighbor_idx", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->neighbor_idx);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->neighbor_blk);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->edge_idx);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->edge_blk);
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

  if (x->area) add_line(serialize_array(x->area), s);

  add_line("# start_index", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->start_index);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->end_index);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->start_blk);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->start_block);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->end_blk);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->end_block);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->cell_idx);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->cell_blk);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->vertex_idx);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->vertex_blk);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->tangent_orientation);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->quad_idx);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->quad_blk);
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

  add_line("# primal_normal_cell", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->primal_normal_cell);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->primal_normal_cell[i]), s);
    }
  }

  add_line("# dual_normal_cell", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->dual_normal_cell);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->dual_normal_cell[i]), s);
    }
  }

  add_line("# inv_primal_edge_length", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->inv_primal_edge_length);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->inv_dual_edge_length);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->area_edge);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->f_e);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->fn_e);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->ft_e);
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

  add_line("# refin_ctrl", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->refin_ctrl);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->refin_ctrl[i]), s);
    }
  }

  add_line("# start_index", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->start_index);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->end_index);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->start_block);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->end_block);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->cell_idx);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->cell_blk);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->edge_idx);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->edge_blk);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->start_index);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->end_index);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->start_block);
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
    const array_meta& m = ARRAY_META_DICT()->at(x->end_block);
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

  if (x->w) add_line(serialize_array(x->w), s);

  add_line("# vn", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn != nullptr), s);

  if (x->vn) add_line(serialize_array(x->vn), s);

  add_line("# rho", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho != nullptr), s);

  if (x->rho) add_line(serialize_array(x->rho), s);

  add_line("# exner", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner != nullptr), s);

  if (x->exner) add_line(serialize_array(x->exner), s);

  add_line("# theta_v", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_v != nullptr), s);

  if (x->theta_v) add_line(serialize_array(x->theta_v), s);

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_nh_diag* x) {
  std::stringstream s;
  add_line("# exner_pr", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_pr != nullptr), s);

  if (x->exner_pr) add_line(serialize_array(x->exner_pr), s);

  add_line("# mass_fl_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->mass_fl_e != nullptr), s);

  if (x->mass_fl_e) add_line(serialize_array(x->mass_fl_e), s);

  add_line("# rho_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_ic != nullptr), s);

  if (x->rho_ic) add_line(serialize_array(x->rho_ic), s);

  add_line("# theta_v_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_v_ic != nullptr), s);

  if (x->theta_v_ic) add_line(serialize_array(x->theta_v_ic), s);

  add_line("# grf_tend_vn", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_vn != nullptr), s);

  if (x->grf_tend_vn) add_line(serialize_array(x->grf_tend_vn), s);

  add_line("# grf_tend_w", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_w != nullptr), s);

  if (x->grf_tend_w) add_line(serialize_array(x->grf_tend_w), s);

  add_line("# grf_tend_rho", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_rho != nullptr), s);

  if (x->grf_tend_rho) add_line(serialize_array(x->grf_tend_rho), s);

  add_line("# grf_tend_thv", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_thv != nullptr), s);

  if (x->grf_tend_thv) add_line(serialize_array(x->grf_tend_thv), s);

  add_line("# vn_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_incr != nullptr), s);

  if (x->vn_incr) add_line(serialize_array(x->vn_incr), s);

  add_line("# exner_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_incr != nullptr), s);

  if (x->exner_incr) add_line(serialize_array(x->exner_incr), s);

  add_line("# rho_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_incr != nullptr), s);

  if (x->rho_incr) add_line(serialize_array(x->rho_incr), s);

  add_line("# vt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vt != nullptr), s);

  if (x->vt) add_line(serialize_array(x->vt), s);

  add_line("# ddt_exner_phy", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_exner_phy != nullptr), s);

  if (x->ddt_exner_phy) add_line(serialize_array(x->ddt_exner_phy), s);

  add_line("# ddt_vn_phy", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_phy != nullptr), s);

  if (x->ddt_vn_phy) add_line(serialize_array(x->ddt_vn_phy), s);

  add_line("# exner_dyn_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_dyn_incr != nullptr), s);

  if (x->exner_dyn_incr) add_line(serialize_array(x->exner_dyn_incr), s);

  add_line("# vn_ie", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ie != nullptr), s);

  if (x->vn_ie) add_line(serialize_array(x->vn_ie), s);

  add_line("# w_concorr_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->w_concorr_c != nullptr), s);

  if (x->w_concorr_c) add_line(serialize_array(x->w_concorr_c), s);

  add_line("# mass_fl_e_sv", s);

  add_line("# assoc", s);
  add_line(serialize(x->mass_fl_e_sv != nullptr), s);

  if (x->mass_fl_e_sv) add_line(serialize_array(x->mass_fl_e_sv), s);

  add_line("# ddt_vn_apc_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_apc_pc != nullptr), s);

  if (x->ddt_vn_apc_pc) add_line(serialize_array(x->ddt_vn_apc_pc), s);

  add_line("# ddt_w_adv_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_w_adv_pc != nullptr), s);

  if (x->ddt_w_adv_pc) add_line(serialize_array(x->ddt_w_adv_pc), s);

  add_line("# max_vcfl_dyn", s);
  add_line(serialize(x->max_vcfl_dyn), s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_nh_ref* x) {
  std::stringstream s;
  add_line("# vn_ref", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ref != nullptr), s);

  if (x->vn_ref) add_line(serialize_array(x->vn_ref), s);

  add_line("# w_ref", s);

  add_line("# assoc", s);
  add_line(serialize(x->w_ref != nullptr), s);

  if (x->w_ref) add_line(serialize_array(x->w_ref), s);

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_nh_metrics* x) {
  std::stringstream s;
  add_line("# rayleigh_w", s);

  add_line("# assoc", s);
  add_line(serialize(x->rayleigh_w != nullptr), s);

  if (x->rayleigh_w) add_line(serialize_array(x->rayleigh_w), s);

  add_line("# rayleigh_vn", s);

  add_line("# assoc", s);
  add_line(serialize(x->rayleigh_vn != nullptr), s);

  if (x->rayleigh_vn) add_line(serialize_array(x->rayleigh_vn), s);

  add_line("# scalfac_dd3d", s);

  add_line("# assoc", s);
  add_line(serialize(x->scalfac_dd3d != nullptr), s);

  if (x->scalfac_dd3d) add_line(serialize_array(x->scalfac_dd3d), s);

  add_line("# hmask_dd3d", s);

  add_line("# assoc", s);
  add_line(serialize(x->hmask_dd3d != nullptr), s);

  if (x->hmask_dd3d) add_line(serialize_array(x->hmask_dd3d), s);

  add_line("# vwind_expl_wgt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vwind_expl_wgt != nullptr), s);

  if (x->vwind_expl_wgt) add_line(serialize_array(x->vwind_expl_wgt), s);

  add_line("# vwind_impl_wgt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vwind_impl_wgt != nullptr), s);

  if (x->vwind_impl_wgt) add_line(serialize_array(x->vwind_impl_wgt), s);

  add_line("# ddxn_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddxn_z_full != nullptr), s);

  if (x->ddxn_z_full) add_line(serialize_array(x->ddxn_z_full), s);

  add_line("# ddxt_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddxt_z_full != nullptr), s);

  if (x->ddxt_z_full) add_line(serialize_array(x->ddxt_z_full), s);

  add_line("# ddqz_z_full_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddqz_z_full_e != nullptr), s);

  if (x->ddqz_z_full_e) add_line(serialize_array(x->ddqz_z_full_e), s);

  add_line("# ddqz_z_half", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddqz_z_half != nullptr), s);

  if (x->ddqz_z_half) add_line(serialize_array(x->ddqz_z_half), s);

  add_line("# inv_ddqz_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->inv_ddqz_z_full != nullptr), s);

  if (x->inv_ddqz_z_full) add_line(serialize_array(x->inv_ddqz_z_full), s);

  add_line("# wgtfac_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfac_c != nullptr), s);

  if (x->wgtfac_c) add_line(serialize_array(x->wgtfac_c), s);

  add_line("# wgtfac_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfac_e != nullptr), s);

  if (x->wgtfac_e) add_line(serialize_array(x->wgtfac_e), s);

  add_line("# wgtfacq_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfacq_c != nullptr), s);

  if (x->wgtfacq_c) add_line(serialize_array(x->wgtfacq_c), s);

  add_line("# wgtfacq_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfacq_e != nullptr), s);

  if (x->wgtfacq_e) add_line(serialize_array(x->wgtfacq_e), s);

  add_line("# wgtfacq1_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfacq1_c != nullptr), s);

  if (x->wgtfacq1_c) add_line(serialize_array(x->wgtfacq1_c), s);

  add_line("# coeff_gradekin", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff_gradekin != nullptr), s);

  if (x->coeff_gradekin) add_line(serialize_array(x->coeff_gradekin), s);

  add_line("# coeff1_dwdz", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff1_dwdz != nullptr), s);

  if (x->coeff1_dwdz) add_line(serialize_array(x->coeff1_dwdz), s);

  add_line("# coeff2_dwdz", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff2_dwdz != nullptr), s);

  if (x->coeff2_dwdz) add_line(serialize_array(x->coeff2_dwdz), s);

  add_line("# zdiff_gradp", s);

  add_line("# assoc", s);
  add_line(serialize(x->zdiff_gradp != nullptr), s);

  if (x->zdiff_gradp) add_line(serialize_array(x->zdiff_gradp), s);

  add_line("# coeff_gradp", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff_gradp != nullptr), s);

  if (x->coeff_gradp) add_line(serialize_array(x->coeff_gradp), s);

  add_line("# exner_exfac", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_exfac != nullptr), s);

  if (x->exner_exfac) add_line(serialize_array(x->exner_exfac), s);

  add_line("# theta_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_ref_mc != nullptr), s);

  if (x->theta_ref_mc) add_line(serialize_array(x->theta_ref_mc), s);

  add_line("# theta_ref_me", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_ref_me != nullptr), s);

  if (x->theta_ref_me) add_line(serialize_array(x->theta_ref_me), s);

  add_line("# theta_ref_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_ref_ic != nullptr), s);

  if (x->theta_ref_ic) add_line(serialize_array(x->theta_ref_ic), s);

  add_line("# exner_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_ref_mc != nullptr), s);

  if (x->exner_ref_mc) add_line(serialize_array(x->exner_ref_mc), s);

  add_line("# rho_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_ref_mc != nullptr), s);

  if (x->rho_ref_mc) add_line(serialize_array(x->rho_ref_mc), s);

  add_line("# rho_ref_me", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_ref_me != nullptr), s);

  if (x->rho_ref_me) add_line(serialize_array(x->rho_ref_me), s);

  add_line("# d_exner_dz_ref_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->d_exner_dz_ref_ic != nullptr), s);

  if (x->d_exner_dz_ref_ic) add_line(serialize_array(x->d_exner_dz_ref_ic), s);

  add_line("# d2dexdz2_fac1_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->d2dexdz2_fac1_mc != nullptr), s);

  if (x->d2dexdz2_fac1_mc) add_line(serialize_array(x->d2dexdz2_fac1_mc), s);

  add_line("# d2dexdz2_fac2_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->d2dexdz2_fac2_mc != nullptr), s);

  if (x->d2dexdz2_fac2_mc) add_line(serialize_array(x->d2dexdz2_fac2_mc), s);

  add_line("# pg_exdist", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_exdist != nullptr), s);

  if (x->pg_exdist) add_line(serialize_array(x->pg_exdist), s);

  add_line("# vertidx_gradp", s);

  add_line("# assoc", s);
  add_line(serialize(x->vertidx_gradp != nullptr), s);

  if (x->vertidx_gradp) add_line(serialize_array(x->vertidx_gradp), s);

  add_line("# pg_edgeidx", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_edgeidx != nullptr), s);

  if (x->pg_edgeidx) add_line(serialize_array(x->pg_edgeidx), s);

  add_line("# pg_edgeblk", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_edgeblk != nullptr), s);

  if (x->pg_edgeblk) add_line(serialize_array(x->pg_edgeblk), s);

  add_line("# pg_vertidx", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_vertidx != nullptr), s);

  if (x->pg_vertidx) add_line(serialize_array(x->pg_vertidx), s);

  add_line("# bdy_halo_c_idx", s);

  add_line("# assoc", s);
  add_line(serialize(x->bdy_halo_c_idx != nullptr), s);

  if (x->bdy_halo_c_idx) add_line(serialize_array(x->bdy_halo_c_idx), s);

  add_line("# bdy_halo_c_blk", s);

  add_line("# assoc", s);
  add_line(serialize(x->bdy_halo_c_blk != nullptr), s);

  if (x->bdy_halo_c_blk) add_line(serialize_array(x->bdy_halo_c_blk), s);

  add_line("# deepatmo_gradh_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_gradh_mc != nullptr), s);

  if (x->deepatmo_gradh_mc) add_line(serialize_array(x->deepatmo_gradh_mc), s);

  add_line("# deepatmo_divh_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_divh_mc != nullptr), s);

  if (x->deepatmo_divh_mc) add_line(serialize_array(x->deepatmo_divh_mc), s);

  add_line("# deepatmo_invr_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_invr_mc != nullptr), s);

  if (x->deepatmo_invr_mc) add_line(serialize_array(x->deepatmo_invr_mc), s);

  add_line("# deepatmo_divzu_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_divzu_mc != nullptr), s);

  if (x->deepatmo_divzu_mc) add_line(serialize_array(x->deepatmo_divzu_mc), s);

  add_line("# deepatmo_divzl_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_divzl_mc != nullptr), s);

  if (x->deepatmo_divzl_mc) add_line(serialize_array(x->deepatmo_divzl_mc), s);

  add_line("# deepatmo_gradh_ifc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_gradh_ifc != nullptr), s);

  if (x->deepatmo_gradh_ifc)
    add_line(serialize_array(x->deepatmo_gradh_ifc), s);

  add_line("# deepatmo_invr_ifc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_invr_ifc != nullptr), s);

  if (x->deepatmo_invr_ifc) add_line(serialize_array(x->deepatmo_invr_ifc), s);

  add_line("# mask_prog_halo_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->mask_prog_halo_c != nullptr), s);

  if (x->mask_prog_halo_c) add_line(serialize_array(x->mask_prog_halo_c), s);

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_nh_state* x) {
  std::stringstream s;
  add_line("# prog", s);

  {
    const array_meta& m = ARRAY_META_DICT()->at(x->prog);
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i = 0; i < m.volume(); ++i) {
      add_line(serialize(x->prog[i]), s);
    }
  }

  add_line("# diag", s);
  add_line(serialize(x->diag), s);
  add_line("# ref", s);
  add_line(serialize(x->ref), s);
  add_line("# metrics", s);
  add_line(serialize(x->metrics), s);
  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

std::string serialize(const t_prepare_adv* x) {
  std::stringstream s;
  add_line("# mass_flx_me", s);

  add_line("# assoc", s);
  add_line(serialize(x->mass_flx_me != nullptr), s);

  if (x->mass_flx_me) add_line(serialize_array(x->mass_flx_me), s);

  add_line("# mass_flx_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->mass_flx_ic != nullptr), s);

  if (x->mass_flx_ic) add_line(serialize_array(x->mass_flx_ic), s);

  add_line("# vol_flx_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->vol_flx_ic != nullptr), s);

  if (x->vol_flx_ic) add_line(serialize_array(x->vol_flx_ic), s);

  add_line("# vn_traj", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_traj != nullptr), s);

  if (x->vn_traj) add_line(serialize_array(x->vn_traj), s);

  std::string out = s.str();
  if (out.length() > 0) out.pop_back();
  return out;
}

template <typename T>
T* array_meta::read(std::istream& s) const {
  auto* buf = new T[volume()];
  if constexpr (std::is_pointer_v<T>) {
    auto* bufc = read<std::remove_pointer_t<T>>(s);
    for (int i = 0; i < volume(); ++i) {
      buf[i] = &bufc[i];
    }
  } else {
    read_line(s, {"# entries"});
    for (int i = 0; i < volume(); ++i) {
      deserialize(&buf[i], s);
    }
    (*ARRAY_META_DICT())[buf] = *this;
  }
  return buf;
}

template <typename T>
std::string serialize_array(T* arr) {
  const auto m = ARRAY_META_DICT()->at(static_cast<void*>(arr));
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

void deserialize_global_data(global_data_type* g, std::istream& s) {
  read_line(s, "# ldeepatmo_var_0");
  deserialize(g->ldeepatmo_var_0, s);

  read_line(s, "# l_limited_area");
  deserialize(g->l_limited_area, s);

  {
    read_line(s, "# nflatlev");
    auto [m, arr] = read_array<int>(s);
    g->nflatlev = arr;
  }

  read_line(s, "# is_iau_active");
  deserialize(g->is_iau_active, s);

  read_line(s, "# iau_wgt_dyn");
  deserialize(g->iau_wgt_dyn, s);

  read_line(s, "# nudge_max_coeff");
  deserialize(g->nudge_max_coeff, s);

  read_line(s, "# process_mpi_all_size");
  deserialize(g->process_mpi_all_size, s);

  read_line(s, "# i_am_accel_node");
  deserialize(g->i_am_accel_node, s);

  read_line(s, "# itime_scheme");
  deserialize(g->itime_scheme, s);

  {
    read_line(s, "# ndyn_substeps_var");
    auto [m, arr] = read_array<int>(s);
    g->ndyn_substeps_var = arr;
  }

  read_line(s, "# lextra_diffu");
  deserialize(g->lextra_diffu, s);

  read_line(s, "# divdamp_fac");
  deserialize(g->divdamp_fac, s);

  read_line(s, "# divdamp_fac2");
  deserialize(g->divdamp_fac2, s);

  read_line(s, "# divdamp_fac3");
  deserialize(g->divdamp_fac3, s);

  read_line(s, "# divdamp_fac4");
  deserialize(g->divdamp_fac4, s);

  read_line(s, "# divdamp_z");
  deserialize(g->divdamp_z, s);

  read_line(s, "# divdamp_z2");
  deserialize(g->divdamp_z2, s);

  read_line(s, "# divdamp_z3");
  deserialize(g->divdamp_z3, s);

  read_line(s, "# divdamp_z4");
  deserialize(g->divdamp_z4, s);

  read_line(s, "# divdamp_fac_o2");
  deserialize(g->divdamp_fac_o2, s);

  read_line(s, "# divdamp_order");
  deserialize(g->divdamp_order, s);

  read_line(s, "# divdamp_type");
  deserialize(g->divdamp_type, s);

  read_line(s, "# rayleigh_type");
  deserialize(g->rayleigh_type, s);

  read_line(s, "# rhotheta_offctr");
  deserialize(g->rhotheta_offctr, s);

  read_line(s, "# veladv_offctr");
  deserialize(g->veladv_offctr, s);

  read_line(s, "# iadv_rhotheta");
  deserialize(g->iadv_rhotheta, s);

  read_line(s, "# igradp_method");
  deserialize(g->igradp_method, s);

  {
    read_line(s, "# kstart_dd3d");
    auto [m, arr] = read_array<int>(s);
    g->kstart_dd3d = arr;
  }

  {
    read_line(s, "# kstart_moist");
    auto [m, arr] = read_array<int>(s);
    g->kstart_moist = arr;
  }

  read_line(s, "# nproma_var_103");
  deserialize(g->nproma_var_103, s);

  read_line(s, "# p_test_run");
  deserialize(g->p_test_run, s);

  read_line(s, "# timers_level");
  deserialize(g->timers_level, s);

  read_line(s, "# timer_solve_nh_veltend");
  deserialize(g->timer_solve_nh_veltend, s);

  read_line(s, "# timer_solve_nh_cellcomp");
  deserialize(g->timer_solve_nh_cellcomp, s);

  read_line(s, "# timer_solve_nh_exch");
  deserialize(g->timer_solve_nh_exch, s);

  read_line(s, "# timer_intp");
  deserialize(g->timer_intp, s);

  {
    read_line(s, "# vct_a");
    auto [m, arr] = read_array<double>(s);
    g->vct_a = arr;
  }

  {
    read_line(s, "# nrdmax");
    auto [m, arr] = read_array<int>(s);
    g->nrdmax = arr;
  }

  {
    read_line(s, "# nflat_gradp");
    auto [m, arr] = read_array<int>(s);
    g->nflat_gradp = arr;
  }
}

std::string serialize_global_data(const global_data_type* g) {
  std::stringstream s;

  add_line(serialize(g->ldeepatmo_var_0), s);

  add_line(serialize(g->l_limited_area), s);

  add_line(serialize_array(g->nflatlev), s);

  add_line(serialize(g->is_iau_active), s);

  add_line(serialize(g->iau_wgt_dyn), s);

  add_line(serialize(g->nudge_max_coeff), s);

  add_line(serialize(g->process_mpi_all_size), s);

  add_line(serialize(g->i_am_accel_node), s);

  add_line(serialize(g->itime_scheme), s);

  add_line(serialize_array(g->ndyn_substeps_var), s);

  add_line(serialize(g->lextra_diffu), s);

  add_line(serialize(g->divdamp_fac), s);

  add_line(serialize(g->divdamp_fac2), s);

  add_line(serialize(g->divdamp_fac3), s);

  add_line(serialize(g->divdamp_fac4), s);

  add_line(serialize(g->divdamp_z), s);

  add_line(serialize(g->divdamp_z2), s);

  add_line(serialize(g->divdamp_z3), s);

  add_line(serialize(g->divdamp_z4), s);

  add_line(serialize(g->divdamp_fac_o2), s);

  add_line(serialize(g->divdamp_order), s);

  add_line(serialize(g->divdamp_type), s);

  add_line(serialize(g->rayleigh_type), s);

  add_line(serialize(g->rhotheta_offctr), s);

  add_line(serialize(g->veladv_offctr), s);

  add_line(serialize(g->iadv_rhotheta), s);

  add_line(serialize(g->igradp_method), s);

  add_line(serialize_array(g->kstart_dd3d), s);

  add_line(serialize_array(g->kstart_moist), s);

  add_line(serialize(g->nproma_var_103), s);

  add_line(serialize(g->p_test_run), s);

  add_line(serialize(g->timers_level), s);

  add_line(serialize(g->timer_solve_nh_veltend), s);

  add_line(serialize(g->timer_solve_nh_cellcomp), s);

  add_line(serialize(g->timer_solve_nh_exch), s);

  add_line(serialize(g->timer_intp), s);

  add_line(serialize_array(g->vct_a), s);

  add_line(serialize_array(g->nrdmax), s);

  add_line(serialize_array(g->nflat_gradp), s);

  return s.str();
}

enum class SerializationType { INVALID, PLAIN, CONST_INJECTION, F90_MODULE };

std::string serialize_consistent_global_data(
    std::vector<const global_data_type*>& gs,
    SerializationType serialization_type = SerializationType::INVALID) {
  assert(serialization_type != SerializationType::INVALID);
  if (gs.empty()) return "";

  std::map<std::string, std::set<std::string>> consistent;
  for (const auto* g : gs) {
    consistent["mo_dynamics_config.ldeepatmo_var_0"].insert(
        (g->ldeepatmo_var_0 ? ".true." : ".false."));

    consistent["mo_grid_config.l_limited_area"].insert(
        (g->l_limited_area ? ".true." : ".false."));

    consistent["mo_initicon_config.is_iau_active"].insert(
        (g->is_iau_active ? ".true." : ".false."));

    consistent["mo_initicon_config.iau_wgt_dyn"].insert(
        serialize(g->iau_wgt_dyn));

    consistent["mo_interpol_config.nudge_max_coeff"].insert(
        serialize(g->nudge_max_coeff));

    consistent["mo_mpi.process_mpi_all_size"].insert(
        serialize(g->process_mpi_all_size));

    consistent["mo_mpi.i_am_accel_node"].insert(
        (g->i_am_accel_node ? ".true." : ".false."));

    consistent["mo_nonhydrostatic_config.itime_scheme"].insert(
        serialize(g->itime_scheme));

    consistent["mo_nonhydrostatic_config.lextra_diffu"].insert(
        (g->lextra_diffu ? ".true." : ".false."));

    consistent["mo_nonhydrostatic_config.divdamp_fac"].insert(
        serialize(g->divdamp_fac));

    consistent["mo_nonhydrostatic_config.divdamp_fac2"].insert(
        serialize(g->divdamp_fac2));

    consistent["mo_nonhydrostatic_config.divdamp_fac3"].insert(
        serialize(g->divdamp_fac3));

    consistent["mo_nonhydrostatic_config.divdamp_fac4"].insert(
        serialize(g->divdamp_fac4));

    consistent["mo_nonhydrostatic_config.divdamp_z"].insert(
        serialize(g->divdamp_z));

    consistent["mo_nonhydrostatic_config.divdamp_z2"].insert(
        serialize(g->divdamp_z2));

    consistent["mo_nonhydrostatic_config.divdamp_z3"].insert(
        serialize(g->divdamp_z3));

    consistent["mo_nonhydrostatic_config.divdamp_z4"].insert(
        serialize(g->divdamp_z4));

    consistent["mo_nonhydrostatic_config.divdamp_fac_o2"].insert(
        serialize(g->divdamp_fac_o2));

    consistent["mo_nonhydrostatic_config.divdamp_order"].insert(
        serialize(g->divdamp_order));

    consistent["mo_nonhydrostatic_config.divdamp_type"].insert(
        serialize(g->divdamp_type));

    consistent["mo_nonhydrostatic_config.rayleigh_type"].insert(
        serialize(g->rayleigh_type));

    consistent["mo_nonhydrostatic_config.rhotheta_offctr"].insert(
        serialize(g->rhotheta_offctr));

    consistent["mo_nonhydrostatic_config.veladv_offctr"].insert(
        serialize(g->veladv_offctr));

    consistent["mo_nonhydrostatic_config.iadv_rhotheta"].insert(
        serialize(g->iadv_rhotheta));

    consistent["mo_nonhydrostatic_config.igradp_method"].insert(
        serialize(g->igradp_method));

    consistent["mo_parallel_config.nproma_var_103"].insert(
        serialize(g->nproma_var_103));

    consistent["mo_parallel_config.p_test_run"].insert(
        (g->p_test_run ? ".true." : ".false."));

    consistent["mo_run_config.timers_level"].insert(serialize(g->timers_level));

    consistent["mo_timer.timer_solve_nh_veltend"].insert(
        serialize(g->timer_solve_nh_veltend));

    consistent["mo_timer.timer_solve_nh_cellcomp"].insert(
        serialize(g->timer_solve_nh_cellcomp));

    consistent["mo_timer.timer_solve_nh_exch"].insert(
        serialize(g->timer_solve_nh_exch));

    consistent["mo_timer.timer_intp"].insert(serialize(g->timer_intp));
  }

  std::stringstream s;
  if (serialization_type == SerializationType::F90_MODULE) {
    s << R"(
module global_data_assertion
contains
subroutine assert_global_data()
)";
    for (const auto& [k, vs] : consistent) {
      std::vector<std::string_view> parts = split(k, '.');
      assert(parts.size() == 2);
      const auto mname = std::string_view(parts[0]);
      s << "use " << mname << std::endl;
    }
    s << R"(
implicit none
)";
  }
  for (const auto& [k, vs] : consistent) {
    if (vs.size() != 1) continue;
    const auto& v = *vs.begin();
    if (serialization_type == SerializationType::PLAIN) {
      s << k << " = " << v << std::endl;
    } else if (serialization_type == SerializationType::CONST_INJECTION) {
      const std::string vval =
          (v == ".true." ? "1" : (v == ".false." ? "0" : v));
      s << R"({ "type": "ConstInstanceInjection", "scope": null, )";
      s << R"("root": ")" << k << R"(", "component": null, "value": ")" << vval
        << R"(" })" << std::endl;
    } else if (serialization_type == SerializationType::F90_MODULE) {
      std::vector<std::string_view> parts = split(k, '.');
      assert(parts.size() == 2);
      const auto vname = std::string_view(parts[1]);
      const auto neqop =
          (v == ".true." || v == ".false.") ? " .neqv. " : " .ne. ";
      s << "if (" << vname << neqop << v << ") then" << std::endl;
      s << R"(	print *, "mismatched )" << vname << "; want " << v
        << R"(, got: ", )" << vname << std::endl;
      s << "	call abort" << std::endl << "endif" << std::endl;
    }
  }
  if (serialization_type == SerializationType::F90_MODULE) {
    s << R"(
end subroutine assert_global_data
end module global_data_assertion
)";
  }
  return s.str();
}

}  // namespace serde

#endif  // __DACE_SERDE__
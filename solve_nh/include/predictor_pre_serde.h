#ifndef __DACE_PREDICTOR_PRE_SERDE__
#define __DACE_PREDICTOR_PRE_SERDE__

#include <algorithm>
#include <cassert>
#include <format>
#include <iomanip>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <optional>
#include <ranges>
#include <set>
#include <sstream>
#include <string_view>
#include <vector>

namespace predictor_pre {
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

std::string scroll_space(std::istream &s) {
  std::string out;
  while (!s.eof() && (!s.peek() || isspace(s.peek()))) {
    out += s.get();
    assert(s.good());
  }
  return out;
}

std::string read_line(std::istream &s,
                      const std::optional<std::string> &should_contain = {}) {
  if (s.eof())
    return "<eof>";
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
std::map<void *, array_meta> *ARRAY_META_DICT();

struct array_meta {
  int rank = 0;
  std::vector<int> size, lbound;

  int volume() const {
    return std::reduce(size.begin(), size.end(), 1, std::multiplies<int>());
  }

  template <typename T> T *read(std::istream &s) const;
};
std::map<void *, array_meta> *ARRAY_META_DICT() {
  static auto *M = new std::map<void *, array_meta>();
  return M;
}
template <typename T> const array_meta &ARRAY_META_DICT_AT(T *a) {
  if constexpr (std::is_pointer_v<T>) {
    return ARRAY_META_DICT_AT(*a);
  } else {
    return ARRAY_META_DICT()->at(a);
  }
}

template <typename T> void read_scalar(T &x, std::istream &s) {
  if (s.eof())
    return;
  scroll_space(s);
  s >> x;
}

void read_scalar(float &x, std::istream &s) {
  if (s.eof())
    return;
  scroll_space(s);
  long double y;
  s >> y;
  x = y;
}

void read_scalar(double &x, std::istream &s) {
  if (s.eof())
    return;
  scroll_space(s);
  long double y;
  s >> y;
  x = y;
}

void read_scalar(bool &x, std::istream &s) {
  char c;
  read_scalar(c, s);
  assert(c == '1' or c == '0');
  x = (c == '1');
}

array_meta read_array_meta(std::istream &s) {
  array_meta m;
  read_line(s, {"# rank"}); // Should contain '# rank'
  read_scalar(m.rank, s);
  m.size.resize(m.rank);
  m.lbound.resize(m.rank);
  read_line(s, {"# size"}); // Should contain '# size'
  for (int i = 0; i < m.rank; ++i) {
    read_scalar(m.size[i], s);
  }
  read_line(s, {"# lbound"}); // Should contain '# lbound'
  for (int i = 0; i < m.rank; ++i) {
    read_scalar(m.lbound[i], s);
  }
  return m;
}

template <typename T> std::pair<array_meta, T *> read_array(std::istream &s) {
  auto m = read_array_meta(s);
  auto *y = m.read<T>(s);
  return {m, y};
}

template <typename T> std::pair<array_meta, T *> read_pointer(std::istream &s) {
  read_line(s, {"# missing"}); // Should contain '# missing'
  int missing;
  read_scalar(missing, s);
  assert(missing == 1);
  return read_array<T>(s);
}

template <typename T> std::string serialize_array(T *arr);

void deserialize(float *x, std::istream &s) { read_scalar(*x, s); }
void deserialize(double *x, std::istream &s) { read_scalar(*x, s); }
void deserialize(long double *x, std::istream &s) { read_scalar(*x, s); }
void deserialize(int *x, std::istream &s) { read_scalar(*x, s); }
void deserialize(long *x, std::istream &s) { read_scalar(*x, s); }
void deserialize(long long *x, std::istream &s) { read_scalar(*x, s); }
void deserialize(bool *x, std::istream &s) { read_scalar(*x, s); }
void deserialize(float &x, std::istream &s) { read_scalar(x, s); }
void deserialize(double &x, std::istream &s) { read_scalar(x, s); }
void deserialize(long double &x, std::istream &s) { read_scalar(x, s); }
void deserialize(int &x, std::istream &s) { read_scalar(x, s); }
void deserialize(long &x, std::istream &s) { read_scalar(x, s); }
void deserialize(long long &x, std::istream &s) { read_scalar(x, s); }
void deserialize(bool &x, std::istream &s) { read_scalar(x, s); }

void deserialize(t_grid_domain_decomp_info *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# owner_mask"}); // Should contain '# owner_mask'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_owner_mask_d_0_s_62 = m.size[0];
    x->__f2dace_SA_owner_mask_d_1_s_63 = m.size[1];
    x->__f2dace_SOA_owner_mask_d_0_s_62 = m.lbound[0];
    x->__f2dace_SOA_owner_mask_d_1_s_63 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->owner_mask =
        m.read<std::remove_pointer<decltype(x->owner_mask)>::type>(s);

  } // CONCLUDING IF
}

void deserialize(t_int_state *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# c_lin_e"}); // Should contain '# c_lin_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_c_lin_e_d_0_s_93 = m.size[0];
    x->__f2dace_SA_c_lin_e_d_1_s_94 = m.size[1];
    x->__f2dace_SA_c_lin_e_d_2_s_95 = m.size[2];
    x->__f2dace_SOA_c_lin_e_d_0_s_93 = m.lbound[0];
    x->__f2dace_SOA_c_lin_e_d_1_s_94 = m.lbound[1];
    x->__f2dace_SOA_c_lin_e_d_2_s_95 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->c_lin_e = m.read<std::remove_pointer<decltype(x->c_lin_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# e_bln_c_s"}); // Should contain '# e_bln_c_s'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_e_bln_c_s_d_0_s_96 = m.size[0];
    x->__f2dace_SA_e_bln_c_s_d_1_s_97 = m.size[1];
    x->__f2dace_SA_e_bln_c_s_d_2_s_98 = m.size[2];
    x->__f2dace_SOA_e_bln_c_s_d_0_s_96 = m.lbound[0];
    x->__f2dace_SOA_e_bln_c_s_d_1_s_97 = m.lbound[1];
    x->__f2dace_SOA_e_bln_c_s_d_2_s_98 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->e_bln_c_s = m.read<std::remove_pointer<decltype(x->e_bln_c_s)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# cells_aw_verts"}); // Should contain '# cells_aw_verts'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cells_aw_verts_d_0_s_99 = m.size[0];
    x->__f2dace_SA_cells_aw_verts_d_1_s_100 = m.size[1];
    x->__f2dace_SA_cells_aw_verts_d_2_s_101 = m.size[2];
    x->__f2dace_SOA_cells_aw_verts_d_0_s_99 = m.lbound[0];
    x->__f2dace_SOA_cells_aw_verts_d_1_s_100 = m.lbound[1];
    x->__f2dace_SOA_cells_aw_verts_d_2_s_101 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cells_aw_verts =
        m.read<std::remove_pointer<decltype(x->cells_aw_verts)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# rbf_vec_coeff_e"}); // Should contain '# rbf_vec_coeff_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_rbf_vec_coeff_e_d_0_s_102 = m.size[0];
    x->__f2dace_SA_rbf_vec_coeff_e_d_1_s_103 = m.size[1];
    x->__f2dace_SA_rbf_vec_coeff_e_d_2_s_104 = m.size[2];
    x->__f2dace_SOA_rbf_vec_coeff_e_d_0_s_102 = m.lbound[0];
    x->__f2dace_SOA_rbf_vec_coeff_e_d_1_s_103 = m.lbound[1];
    x->__f2dace_SOA_rbf_vec_coeff_e_d_2_s_104 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->rbf_vec_coeff_e =
        m.read<std::remove_pointer<decltype(x->rbf_vec_coeff_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# geofac_grdiv"}); // Should contain '# geofac_grdiv'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_geofac_grdiv_d_0_s_105 = m.size[0];
    x->__f2dace_SA_geofac_grdiv_d_1_s_106 = m.size[1];
    x->__f2dace_SA_geofac_grdiv_d_2_s_107 = m.size[2];
    x->__f2dace_SOA_geofac_grdiv_d_0_s_105 = m.lbound[0];
    x->__f2dace_SOA_geofac_grdiv_d_1_s_106 = m.lbound[1];
    x->__f2dace_SOA_geofac_grdiv_d_2_s_107 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->geofac_grdiv =
        m.read<std::remove_pointer<decltype(x->geofac_grdiv)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# geofac_rot"}); // Should contain '# geofac_rot'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_geofac_rot_d_0_s_108 = m.size[0];
    x->__f2dace_SA_geofac_rot_d_1_s_109 = m.size[1];
    x->__f2dace_SA_geofac_rot_d_2_s_110 = m.size[2];
    x->__f2dace_SOA_geofac_rot_d_0_s_108 = m.lbound[0];
    x->__f2dace_SOA_geofac_rot_d_1_s_109 = m.lbound[1];
    x->__f2dace_SOA_geofac_rot_d_2_s_110 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->geofac_rot =
        m.read<std::remove_pointer<decltype(x->geofac_rot)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# geofac_n2s"}); // Should contain '# geofac_n2s'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_geofac_n2s_d_0_s_111 = m.size[0];
    x->__f2dace_SA_geofac_n2s_d_1_s_112 = m.size[1];
    x->__f2dace_SA_geofac_n2s_d_2_s_113 = m.size[2];
    x->__f2dace_SOA_geofac_n2s_d_0_s_111 = m.lbound[0];
    x->__f2dace_SOA_geofac_n2s_d_1_s_112 = m.lbound[1];
    x->__f2dace_SOA_geofac_n2s_d_2_s_113 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->geofac_n2s =
        m.read<std::remove_pointer<decltype(x->geofac_n2s)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# geofac_grg"}); // Should contain '# geofac_grg'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_geofac_grg_d_0_s_114 = m.size[0];
    x->__f2dace_SA_geofac_grg_d_1_s_115 = m.size[1];
    x->__f2dace_SA_geofac_grg_d_2_s_116 = m.size[2];
    x->__f2dace_SA_geofac_grg_d_3_s_117 = m.size[3];
    x->__f2dace_SOA_geofac_grg_d_0_s_114 = m.lbound[0];
    x->__f2dace_SOA_geofac_grg_d_1_s_115 = m.lbound[1];
    x->__f2dace_SOA_geofac_grg_d_2_s_116 = m.lbound[2];
    x->__f2dace_SOA_geofac_grg_d_3_s_117 = m.lbound[3];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->geofac_grg =
        m.read<std::remove_pointer<decltype(x->geofac_grg)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# pos_on_tplane_e"}); // Should contain '# pos_on_tplane_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_pos_on_tplane_e_d_0_s_118 = m.size[0];
    x->__f2dace_SA_pos_on_tplane_e_d_1_s_119 = m.size[1];
    x->__f2dace_SA_pos_on_tplane_e_d_2_s_120 = m.size[2];
    x->__f2dace_SA_pos_on_tplane_e_d_3_s_121 = m.size[3];
    x->__f2dace_SOA_pos_on_tplane_e_d_0_s_118 = m.lbound[0];
    x->__f2dace_SOA_pos_on_tplane_e_d_1_s_119 = m.lbound[1];
    x->__f2dace_SOA_pos_on_tplane_e_d_2_s_120 = m.lbound[2];
    x->__f2dace_SOA_pos_on_tplane_e_d_3_s_121 = m.lbound[3];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->pos_on_tplane_e =
        m.read<std::remove_pointer<decltype(x->pos_on_tplane_e)>::type>(s);

  } // CONCLUDING IF
}

void deserialize(t_tangent_vectors *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# v1"}); // Should contain '# v1'

  deserialize(&(x->v1), s);

  read_line(s, {"# v2"}); // Should contain '# v2'

  deserialize(&(x->v2), s);
}

void deserialize(t_grid_cells *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# neighbor_idx"}); // Should contain '# neighbor_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_neighbor_idx_d_0_s_202 = m.size[0];
    x->__f2dace_SA_neighbor_idx_d_1_s_203 = m.size[1];
    x->__f2dace_SA_neighbor_idx_d_2_s_204 = m.size[2];
    x->__f2dace_SOA_neighbor_idx_d_0_s_202 = m.lbound[0];
    x->__f2dace_SOA_neighbor_idx_d_1_s_203 = m.lbound[1];
    x->__f2dace_SOA_neighbor_idx_d_2_s_204 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->neighbor_idx =
        m.read<std::remove_pointer<decltype(x->neighbor_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# neighbor_blk"}); // Should contain '# neighbor_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_neighbor_blk_d_0_s_205 = m.size[0];
    x->__f2dace_SA_neighbor_blk_d_1_s_206 = m.size[1];
    x->__f2dace_SA_neighbor_blk_d_2_s_207 = m.size[2];
    x->__f2dace_SOA_neighbor_blk_d_0_s_205 = m.lbound[0];
    x->__f2dace_SOA_neighbor_blk_d_1_s_206 = m.lbound[1];
    x->__f2dace_SOA_neighbor_blk_d_2_s_207 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->neighbor_blk =
        m.read<std::remove_pointer<decltype(x->neighbor_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_idx"}); // Should contain '# edge_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_idx_d_0_s_208 = m.size[0];
    x->__f2dace_SA_edge_idx_d_1_s_209 = m.size[1];
    x->__f2dace_SA_edge_idx_d_2_s_210 = m.size[2];
    x->__f2dace_SOA_edge_idx_d_0_s_208 = m.lbound[0];
    x->__f2dace_SOA_edge_idx_d_1_s_209 = m.lbound[1];
    x->__f2dace_SOA_edge_idx_d_2_s_210 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_idx = m.read<std::remove_pointer<decltype(x->edge_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_blk"}); // Should contain '# edge_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_blk_d_0_s_211 = m.size[0];
    x->__f2dace_SA_edge_blk_d_1_s_212 = m.size[1];
    x->__f2dace_SA_edge_blk_d_2_s_213 = m.size[2];
    x->__f2dace_SOA_edge_blk_d_0_s_211 = m.lbound[0];
    x->__f2dace_SOA_edge_blk_d_1_s_212 = m.lbound[1];
    x->__f2dace_SOA_edge_blk_d_2_s_213 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_blk = m.read<std::remove_pointer<decltype(x->edge_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# area"}); // Should contain '# area'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->area)>::type>(s);
    x->__f2dace_SA_area_d_0_s_214 = m.size.at(0);
    x->__f2dace_SA_area_d_1_s_215 = m.size.at(1);
    x->__f2dace_SOA_area_d_0_s_214 = m.lbound.at(0);
    x->__f2dace_SOA_area_d_1_s_215 = m.lbound.at(1);
    x->area = arr;
  }

  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_216 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_216 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->start_index =
        m.read<std::remove_pointer<decltype(x->start_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# end_index"}); // Should contain '# end_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_end_index_d_0_s_217 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_217 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_blk"}); // Should contain '# start_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_blk_d_0_s_218 = m.size[0];
    x->__f2dace_SA_start_blk_d_1_s_219 = m.size[1];
    x->__f2dace_SOA_start_blk_d_0_s_218 = m.lbound[0];
    x->__f2dace_SOA_start_blk_d_1_s_219 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->start_blk = m.read<std::remove_pointer<decltype(x->start_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_220 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_220 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->start_block =
        m.read<std::remove_pointer<decltype(x->start_block)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# end_blk"}); // Should contain '# end_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_end_blk_d_0_s_221 = m.size[0];
    x->__f2dace_SA_end_blk_d_1_s_222 = m.size[1];
    x->__f2dace_SOA_end_blk_d_0_s_221 = m.lbound[0];
    x->__f2dace_SOA_end_blk_d_1_s_222 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_blk = m.read<std::remove_pointer<decltype(x->end_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# end_block"}); // Should contain '# end_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_end_block_d_0_s_223 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_223 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_block = m.read<std::remove_pointer<decltype(x->end_block)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# decomp_info"}); // Should contain '# decomp_info'

  x->decomp_info = new std::remove_pointer<decltype(x->decomp_info)>::type;
  deserialize(x->decomp_info, s);
}

void deserialize(t_grid_edges *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# cell_idx"}); // Should contain '# cell_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cell_idx_d_0_s_224 = m.size[0];
    x->__f2dace_SA_cell_idx_d_1_s_225 = m.size[1];
    x->__f2dace_SA_cell_idx_d_2_s_226 = m.size[2];
    x->__f2dace_SOA_cell_idx_d_0_s_224 = m.lbound[0];
    x->__f2dace_SOA_cell_idx_d_1_s_225 = m.lbound[1];
    x->__f2dace_SOA_cell_idx_d_2_s_226 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_idx = m.read<std::remove_pointer<decltype(x->cell_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# cell_blk"}); // Should contain '# cell_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cell_blk_d_0_s_227 = m.size[0];
    x->__f2dace_SA_cell_blk_d_1_s_228 = m.size[1];
    x->__f2dace_SA_cell_blk_d_2_s_229 = m.size[2];
    x->__f2dace_SOA_cell_blk_d_0_s_227 = m.lbound[0];
    x->__f2dace_SOA_cell_blk_d_1_s_228 = m.lbound[1];
    x->__f2dace_SOA_cell_blk_d_2_s_229 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_blk = m.read<std::remove_pointer<decltype(x->cell_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# vertex_idx"}); // Should contain '# vertex_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_vertex_idx_d_0_s_230 = m.size[0];
    x->__f2dace_SA_vertex_idx_d_1_s_231 = m.size[1];
    x->__f2dace_SA_vertex_idx_d_2_s_232 = m.size[2];
    x->__f2dace_SOA_vertex_idx_d_0_s_230 = m.lbound[0];
    x->__f2dace_SOA_vertex_idx_d_1_s_231 = m.lbound[1];
    x->__f2dace_SOA_vertex_idx_d_2_s_232 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->vertex_idx =
        m.read<std::remove_pointer<decltype(x->vertex_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# vertex_blk"}); // Should contain '# vertex_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_vertex_blk_d_0_s_233 = m.size[0];
    x->__f2dace_SA_vertex_blk_d_1_s_234 = m.size[1];
    x->__f2dace_SA_vertex_blk_d_2_s_235 = m.size[2];
    x->__f2dace_SOA_vertex_blk_d_0_s_233 = m.lbound[0];
    x->__f2dace_SOA_vertex_blk_d_1_s_234 = m.lbound[1];
    x->__f2dace_SOA_vertex_blk_d_2_s_235 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->vertex_blk =
        m.read<std::remove_pointer<decltype(x->vertex_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(
      s, {"# tangent_orientation"}); // Should contain '# tangent_orientation'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_tangent_orientation_d_0_s_236 = m.size[0];
    x->__f2dace_SA_tangent_orientation_d_1_s_237 = m.size[1];
    x->__f2dace_SOA_tangent_orientation_d_0_s_236 = m.lbound[0];
    x->__f2dace_SOA_tangent_orientation_d_1_s_237 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->tangent_orientation =
        m.read<std::remove_pointer<decltype(x->tangent_orientation)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# quad_idx"}); // Should contain '# quad_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_quad_idx_d_0_s_238 = m.size[0];
    x->__f2dace_SA_quad_idx_d_1_s_239 = m.size[1];
    x->__f2dace_SA_quad_idx_d_2_s_240 = m.size[2];
    x->__f2dace_SOA_quad_idx_d_0_s_238 = m.lbound[0];
    x->__f2dace_SOA_quad_idx_d_1_s_239 = m.lbound[1];
    x->__f2dace_SOA_quad_idx_d_2_s_240 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->quad_idx = m.read<std::remove_pointer<decltype(x->quad_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# quad_blk"}); // Should contain '# quad_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_quad_blk_d_0_s_241 = m.size[0];
    x->__f2dace_SA_quad_blk_d_1_s_242 = m.size[1];
    x->__f2dace_SA_quad_blk_d_2_s_243 = m.size[2];
    x->__f2dace_SOA_quad_blk_d_0_s_241 = m.lbound[0];
    x->__f2dace_SOA_quad_blk_d_1_s_242 = m.lbound[1];
    x->__f2dace_SOA_quad_blk_d_2_s_243 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->quad_blk = m.read<std::remove_pointer<decltype(x->quad_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s,
            {"# primal_normal_cell"}); // Should contain '# primal_normal_cell'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_primal_normal_cell_d_0_s_244 = m.size[0];
    x->__f2dace_SA_primal_normal_cell_d_1_s_245 = m.size[1];
    x->__f2dace_SA_primal_normal_cell_d_2_s_246 = m.size[2];
    x->__f2dace_SOA_primal_normal_cell_d_0_s_244 = m.lbound[0];
    x->__f2dace_SOA_primal_normal_cell_d_1_s_245 = m.lbound[1];
    x->__f2dace_SOA_primal_normal_cell_d_2_s_246 = m.lbound[2];
    // TODO: THIS IS POTENTIALLY BUGGY, BECAUSE IT IS NOT REALLY TESTED.
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->primal_normal_cell =
        m.read<std::remove_pointer<decltype(x->primal_normal_cell)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# dual_normal_cell"}); // Should contain '# dual_normal_cell'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_dual_normal_cell_d_0_s_247 = m.size[0];
    x->__f2dace_SA_dual_normal_cell_d_1_s_248 = m.size[1];
    x->__f2dace_SA_dual_normal_cell_d_2_s_249 = m.size[2];
    x->__f2dace_SOA_dual_normal_cell_d_0_s_247 = m.lbound[0];
    x->__f2dace_SOA_dual_normal_cell_d_1_s_248 = m.lbound[1];
    x->__f2dace_SOA_dual_normal_cell_d_2_s_249 = m.lbound[2];
    // TODO: THIS IS POTENTIALLY BUGGY, BECAUSE IT IS NOT REALLY TESTED.
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->dual_normal_cell =
        m.read<std::remove_pointer<decltype(x->dual_normal_cell)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# inv_primal_edge_length"}); // Should contain '#
                                              // inv_primal_edge_length'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_inv_primal_edge_length_d_0_s_250 = m.size[0];
    x->__f2dace_SA_inv_primal_edge_length_d_1_s_251 = m.size[1];
    x->__f2dace_SOA_inv_primal_edge_length_d_0_s_250 = m.lbound[0];
    x->__f2dace_SOA_inv_primal_edge_length_d_1_s_251 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->inv_primal_edge_length =
        m.read<std::remove_pointer<decltype(x->inv_primal_edge_length)>::type>(
            s);

  } // CONCLUDING IF
  read_line(
      s, {"# inv_dual_edge_length"}); // Should contain '# inv_dual_edge_length'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_inv_dual_edge_length_d_0_s_252 = m.size[0];
    x->__f2dace_SA_inv_dual_edge_length_d_1_s_253 = m.size[1];
    x->__f2dace_SOA_inv_dual_edge_length_d_0_s_252 = m.lbound[0];
    x->__f2dace_SOA_inv_dual_edge_length_d_1_s_253 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->inv_dual_edge_length =
        m.read<std::remove_pointer<decltype(x->inv_dual_edge_length)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# area_edge"}); // Should contain '# area_edge'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_area_edge_d_0_s_254 = m.size[0];
    x->__f2dace_SA_area_edge_d_1_s_255 = m.size[1];
    x->__f2dace_SOA_area_edge_d_0_s_254 = m.lbound[0];
    x->__f2dace_SOA_area_edge_d_1_s_255 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->area_edge = m.read<std::remove_pointer<decltype(x->area_edge)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# f_e"}); // Should contain '# f_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_f_e_d_0_s_256 = m.size[0];
    x->__f2dace_SA_f_e_d_1_s_257 = m.size[1];
    x->__f2dace_SOA_f_e_d_0_s_256 = m.lbound[0];
    x->__f2dace_SOA_f_e_d_1_s_257 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->f_e = m.read<std::remove_pointer<decltype(x->f_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# fn_e"}); // Should contain '# fn_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_fn_e_d_0_s_258 = m.size[0];
    x->__f2dace_SA_fn_e_d_1_s_259 = m.size[1];
    x->__f2dace_SOA_fn_e_d_0_s_258 = m.lbound[0];
    x->__f2dace_SOA_fn_e_d_1_s_259 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->fn_e = m.read<std::remove_pointer<decltype(x->fn_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# ft_e"}); // Should contain '# ft_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_ft_e_d_0_s_260 = m.size[0];
    x->__f2dace_SA_ft_e_d_1_s_261 = m.size[1];
    x->__f2dace_SOA_ft_e_d_0_s_260 = m.lbound[0];
    x->__f2dace_SOA_ft_e_d_1_s_261 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->ft_e = m.read<std::remove_pointer<decltype(x->ft_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_262 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_262 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->start_index =
        m.read<std::remove_pointer<decltype(x->start_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# end_index"}); // Should contain '# end_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_end_index_d_0_s_263 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_263 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_264 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_264 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->start_block =
        m.read<std::remove_pointer<decltype(x->start_block)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# end_block"}); // Should contain '# end_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_end_block_d_0_s_265 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_265 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_block = m.read<std::remove_pointer<decltype(x->end_block)>::type>(s);

  } // CONCLUDING IF
}

void deserialize(t_grid_vertices *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# cell_idx"}); // Should contain '# cell_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cell_idx_d_0_s_266 = m.size[0];
    x->__f2dace_SA_cell_idx_d_1_s_267 = m.size[1];
    x->__f2dace_SA_cell_idx_d_2_s_268 = m.size[2];
    x->__f2dace_SOA_cell_idx_d_0_s_266 = m.lbound[0];
    x->__f2dace_SOA_cell_idx_d_1_s_267 = m.lbound[1];
    x->__f2dace_SOA_cell_idx_d_2_s_268 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_idx = m.read<std::remove_pointer<decltype(x->cell_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# cell_blk"}); // Should contain '# cell_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cell_blk_d_0_s_269 = m.size[0];
    x->__f2dace_SA_cell_blk_d_1_s_270 = m.size[1];
    x->__f2dace_SA_cell_blk_d_2_s_271 = m.size[2];
    x->__f2dace_SOA_cell_blk_d_0_s_269 = m.lbound[0];
    x->__f2dace_SOA_cell_blk_d_1_s_270 = m.lbound[1];
    x->__f2dace_SOA_cell_blk_d_2_s_271 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_blk = m.read<std::remove_pointer<decltype(x->cell_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_idx"}); // Should contain '# edge_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_idx_d_0_s_272 = m.size[0];
    x->__f2dace_SA_edge_idx_d_1_s_273 = m.size[1];
    x->__f2dace_SA_edge_idx_d_2_s_274 = m.size[2];
    x->__f2dace_SOA_edge_idx_d_0_s_272 = m.lbound[0];
    x->__f2dace_SOA_edge_idx_d_1_s_273 = m.lbound[1];
    x->__f2dace_SOA_edge_idx_d_2_s_274 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_idx = m.read<std::remove_pointer<decltype(x->edge_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_blk"}); // Should contain '# edge_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_blk_d_0_s_275 = m.size[0];
    x->__f2dace_SA_edge_blk_d_1_s_276 = m.size[1];
    x->__f2dace_SA_edge_blk_d_2_s_277 = m.size[2];
    x->__f2dace_SOA_edge_blk_d_0_s_275 = m.lbound[0];
    x->__f2dace_SOA_edge_blk_d_1_s_276 = m.lbound[1];
    x->__f2dace_SOA_edge_blk_d_2_s_277 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_blk = m.read<std::remove_pointer<decltype(x->edge_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_278 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_278 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->start_index =
        m.read<std::remove_pointer<decltype(x->start_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# end_index"}); // Should contain '# end_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_end_index_d_0_s_279 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_279 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_280 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_280 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->start_block =
        m.read<std::remove_pointer<decltype(x->start_block)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# end_block"}); // Should contain '# end_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_end_block_d_0_s_281 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_281 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_block = m.read<std::remove_pointer<decltype(x->end_block)>::type>(s);

  } // CONCLUDING IF
}

void deserialize(t_patch *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# id"}); // Should contain '# id'

  deserialize(&(x->id), s);

  read_line(s, {"# n_childdom"}); // Should contain '# n_childdom'

  deserialize(&(x->n_childdom), s);

  read_line(s, {"# nblks_c"}); // Should contain '# nblks_c'

  deserialize(&(x->nblks_c), s);

  read_line(s, {"# nblks_e"}); // Should contain '# nblks_e'

  deserialize(&(x->nblks_e), s);

  read_line(s, {"# nblks_v"}); // Should contain '# nblks_v'

  deserialize(&(x->nblks_v), s);

  read_line(s, {"# nlev"}); // Should contain '# nlev'

  deserialize(&(x->nlev), s);

  read_line(s, {"# nlevp1"}); // Should contain '# nlevp1'

  deserialize(&(x->nlevp1), s);

  read_line(s, {"# nshift"}); // Should contain '# nshift'

  deserialize(&(x->nshift), s);

  read_line(s, {"# cells"}); // Should contain '# cells'

  x->cells = new std::remove_pointer<decltype(x->cells)>::type;
  deserialize(x->cells, s);

  read_line(s, {"# edges"}); // Should contain '# edges'

  x->edges = new std::remove_pointer<decltype(x->edges)>::type;
  deserialize(x->edges, s);

  read_line(s, {"# verts"}); // Should contain '# verts'

  x->verts = new std::remove_pointer<decltype(x->verts)>::type;
  deserialize(x->verts, s);
}

void deserialize(t_nh_prog *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# w"}); // Should contain '# w'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->w)>::type>(s);
    x->__f2dace_SA_w_d_0_s_516 = m.size.at(0);
    x->__f2dace_SA_w_d_1_s_517 = m.size.at(1);
    x->__f2dace_SA_w_d_2_s_518 = m.size.at(2);
    x->__f2dace_SOA_w_d_0_s_516 = m.lbound.at(0);
    x->__f2dace_SOA_w_d_1_s_517 = m.lbound.at(1);
    x->__f2dace_SOA_w_d_2_s_518 = m.lbound.at(2);
    x->w = arr;
  }

  read_line(s, {"# vn"}); // Should contain '# vn'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vn)>::type>(s);
    x->__f2dace_SA_vn_d_0_s_519 = m.size.at(0);
    x->__f2dace_SA_vn_d_1_s_520 = m.size.at(1);
    x->__f2dace_SA_vn_d_2_s_521 = m.size.at(2);
    x->__f2dace_SOA_vn_d_0_s_519 = m.lbound.at(0);
    x->__f2dace_SOA_vn_d_1_s_520 = m.lbound.at(1);
    x->__f2dace_SOA_vn_d_2_s_521 = m.lbound.at(2);
    x->vn = arr;
  }

  read_line(s, {"# rho"}); // Should contain '# rho'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho)>::type>(s);
    x->__f2dace_SA_rho_d_0_s_522 = m.size.at(0);
    x->__f2dace_SA_rho_d_1_s_523 = m.size.at(1);
    x->__f2dace_SA_rho_d_2_s_524 = m.size.at(2);
    x->__f2dace_SOA_rho_d_0_s_522 = m.lbound.at(0);
    x->__f2dace_SOA_rho_d_1_s_523 = m.lbound.at(1);
    x->__f2dace_SOA_rho_d_2_s_524 = m.lbound.at(2);
    x->rho = arr;
  }

  read_line(s, {"# exner"}); // Should contain '# exner'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner)>::type>(s);
    x->__f2dace_SA_exner_d_0_s_525 = m.size.at(0);
    x->__f2dace_SA_exner_d_1_s_526 = m.size.at(1);
    x->__f2dace_SA_exner_d_2_s_527 = m.size.at(2);
    x->__f2dace_SOA_exner_d_0_s_525 = m.lbound.at(0);
    x->__f2dace_SOA_exner_d_1_s_526 = m.lbound.at(1);
    x->__f2dace_SOA_exner_d_2_s_527 = m.lbound.at(2);
    x->exner = arr;
  }

  read_line(s, {"# theta_v"}); // Should contain '# theta_v'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v)>::type>(s);
    x->__f2dace_SA_theta_v_d_0_s_528 = m.size.at(0);
    x->__f2dace_SA_theta_v_d_1_s_529 = m.size.at(1);
    x->__f2dace_SA_theta_v_d_2_s_530 = m.size.at(2);
    x->__f2dace_SOA_theta_v_d_0_s_528 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_d_1_s_529 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_d_2_s_530 = m.lbound.at(2);
    x->theta_v = arr;
  }
}

void deserialize(t_nh_diag *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# exner_pr"}); // Should contain '# exner_pr'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_pr)>::type>(s);
    x->__f2dace_SA_exner_pr_d_0_s_531 = m.size.at(0);
    x->__f2dace_SA_exner_pr_d_1_s_532 = m.size.at(1);
    x->__f2dace_SA_exner_pr_d_2_s_533 = m.size.at(2);
    x->__f2dace_SOA_exner_pr_d_0_s_531 = m.lbound.at(0);
    x->__f2dace_SOA_exner_pr_d_1_s_532 = m.lbound.at(1);
    x->__f2dace_SOA_exner_pr_d_2_s_533 = m.lbound.at(2);
    x->exner_pr = arr;
  }

  read_line(s, {"# rho_ic"}); // Should contain '# rho_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ic)>::type>(s);
    x->__f2dace_SA_rho_ic_d_0_s_534 = m.size.at(0);
    x->__f2dace_SA_rho_ic_d_1_s_535 = m.size.at(1);
    x->__f2dace_SA_rho_ic_d_2_s_536 = m.size.at(2);
    x->__f2dace_SOA_rho_ic_d_0_s_534 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ic_d_1_s_535 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ic_d_2_s_536 = m.lbound.at(2);
    x->rho_ic = arr;
  }

  read_line(s, {"# theta_v_ic"}); // Should contain '# theta_v_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v_ic)>::type>(s);
    x->__f2dace_SA_theta_v_ic_d_0_s_537 = m.size.at(0);
    x->__f2dace_SA_theta_v_ic_d_1_s_538 = m.size.at(1);
    x->__f2dace_SA_theta_v_ic_d_2_s_539 = m.size.at(2);
    x->__f2dace_SOA_theta_v_ic_d_0_s_537 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_ic_d_1_s_538 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_ic_d_2_s_539 = m.lbound.at(2);
    x->theta_v_ic = arr;
  }

  read_line(s, {"# grf_tend_vn"}); // Should contain '# grf_tend_vn'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_vn)>::type>(s);
    x->__f2dace_SA_grf_tend_vn_d_0_s_540 = m.size.at(0);
    x->__f2dace_SA_grf_tend_vn_d_1_s_541 = m.size.at(1);
    x->__f2dace_SA_grf_tend_vn_d_2_s_542 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_vn_d_0_s_540 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_vn_d_1_s_541 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_vn_d_2_s_542 = m.lbound.at(2);
    x->grf_tend_vn = arr;
  }

  read_line(s, {"# grf_tend_mflx"}); // Should contain '# grf_tend_mflx'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_mflx)>::type>(s);
    x->__f2dace_SA_grf_tend_mflx_d_0_s_543 = m.size.at(0);
    x->__f2dace_SA_grf_tend_mflx_d_1_s_544 = m.size.at(1);
    x->__f2dace_SA_grf_tend_mflx_d_2_s_545 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_mflx_d_0_s_543 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_mflx_d_1_s_544 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_mflx_d_2_s_545 = m.lbound.at(2);
    x->grf_tend_mflx = arr;
  }

  read_line(s, {"# grf_bdy_mflx"}); // Should contain '# grf_bdy_mflx'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_bdy_mflx)>::type>(s);
    x->__f2dace_SA_grf_bdy_mflx_d_0_s_546 = m.size.at(0);
    x->__f2dace_SA_grf_bdy_mflx_d_1_s_547 = m.size.at(1);
    x->__f2dace_SA_grf_bdy_mflx_d_2_s_548 = m.size.at(2);
    x->__f2dace_SOA_grf_bdy_mflx_d_0_s_546 = m.lbound.at(0);
    x->__f2dace_SOA_grf_bdy_mflx_d_1_s_547 = m.lbound.at(1);
    x->__f2dace_SOA_grf_bdy_mflx_d_2_s_548 = m.lbound.at(2);
    x->grf_bdy_mflx = arr;
  }

  read_line(s, {"# vn_ie_int"}); // Should contain '# vn_ie_int'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ie_int)>::type>(s);
    x->__f2dace_SA_vn_ie_int_d_0_s_549 = m.size.at(0);
    x->__f2dace_SA_vn_ie_int_d_1_s_550 = m.size.at(1);
    x->__f2dace_SA_vn_ie_int_d_2_s_551 = m.size.at(2);
    x->__f2dace_SOA_vn_ie_int_d_0_s_549 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ie_int_d_1_s_550 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ie_int_d_2_s_551 = m.lbound.at(2);
    x->vn_ie_int = arr;
  }

  read_line(s, {"# vn_ie_ubc"}); // Should contain '# vn_ie_ubc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ie_ubc)>::type>(s);
    x->__f2dace_SA_vn_ie_ubc_d_0_s_552 = m.size.at(0);
    x->__f2dace_SA_vn_ie_ubc_d_1_s_553 = m.size.at(1);
    x->__f2dace_SA_vn_ie_ubc_d_2_s_554 = m.size.at(2);
    x->__f2dace_SOA_vn_ie_ubc_d_0_s_552 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ie_ubc_d_1_s_553 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ie_ubc_d_2_s_554 = m.lbound.at(2);
    x->vn_ie_ubc = arr;
  }

  read_line(s, {"# vn_incr"}); // Should contain '# vn_incr'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_incr)>::type>(s);
    x->__f2dace_SA_vn_incr_d_0_s_555 = m.size.at(0);
    x->__f2dace_SA_vn_incr_d_1_s_556 = m.size.at(1);
    x->__f2dace_SA_vn_incr_d_2_s_557 = m.size.at(2);
    x->__f2dace_SOA_vn_incr_d_0_s_555 = m.lbound.at(0);
    x->__f2dace_SOA_vn_incr_d_1_s_556 = m.lbound.at(1);
    x->__f2dace_SOA_vn_incr_d_2_s_557 = m.lbound.at(2);
    x->vn_incr = arr;
  }

  read_line(s, {"# vt"}); // Should contain '# vt'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vt)>::type>(s);
    x->__f2dace_SA_vt_d_0_s_558 = m.size.at(0);
    x->__f2dace_SA_vt_d_1_s_559 = m.size.at(1);
    x->__f2dace_SA_vt_d_2_s_560 = m.size.at(2);
    x->__f2dace_SOA_vt_d_0_s_558 = m.lbound.at(0);
    x->__f2dace_SOA_vt_d_1_s_559 = m.lbound.at(1);
    x->__f2dace_SOA_vt_d_2_s_560 = m.lbound.at(2);
    x->vt = arr;
  }

  read_line(s, {"# ddt_vn_phy"}); // Should contain '# ddt_vn_phy'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_phy)>::type>(s);
    x->__f2dace_SA_ddt_vn_phy_d_0_s_561 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_phy_d_1_s_562 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_phy_d_2_s_563 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_phy_d_0_s_561 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_phy_d_1_s_562 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_phy_d_2_s_563 = m.lbound.at(2);
    x->ddt_vn_phy = arr;
  }

  read_line(s, {"# vn_ie"}); // Should contain '# vn_ie'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ie)>::type>(s);
    x->__f2dace_SA_vn_ie_d_0_s_564 = m.size.at(0);
    x->__f2dace_SA_vn_ie_d_1_s_565 = m.size.at(1);
    x->__f2dace_SA_vn_ie_d_2_s_566 = m.size.at(2);
    x->__f2dace_SOA_vn_ie_d_0_s_564 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ie_d_1_s_565 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ie_d_2_s_566 = m.lbound.at(2);
    x->vn_ie = arr;
  }

  read_line(s, {"# w_concorr_c"}); // Should contain '# w_concorr_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->w_concorr_c)>::type>(s);
    x->__f2dace_SA_w_concorr_c_d_0_s_567 = m.size.at(0);
    x->__f2dace_SA_w_concorr_c_d_1_s_568 = m.size.at(1);
    x->__f2dace_SA_w_concorr_c_d_2_s_569 = m.size.at(2);
    x->__f2dace_SOA_w_concorr_c_d_0_s_567 = m.lbound.at(0);
    x->__f2dace_SOA_w_concorr_c_d_1_s_568 = m.lbound.at(1);
    x->__f2dace_SOA_w_concorr_c_d_2_s_569 = m.lbound.at(2);
    x->w_concorr_c = arr;
  }

  read_line(s, {"# ddt_vn_apc_pc"}); // Should contain '# ddt_vn_apc_pc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_apc_pc)>::type>(s);
    x->__f2dace_SA_ddt_vn_apc_pc_d_0_s_570 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_apc_pc_d_1_s_571 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_apc_pc_d_2_s_572 = m.size.at(2);
    x->__f2dace_SA_ddt_vn_apc_pc_d_3_s_573 = m.size.at(3);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_0_s_570 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_1_s_571 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_2_s_572 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_3_s_573 = m.lbound.at(3);
    x->ddt_vn_apc_pc = arr;
  }

  read_line(s, {"# ddt_vn_cor_pc"}); // Should contain '# ddt_vn_cor_pc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_cor_pc)>::type>(s);
    x->__f2dace_SA_ddt_vn_cor_pc_d_0_s_574 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_cor_pc_d_1_s_575 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_cor_pc_d_2_s_576 = m.size.at(2);
    x->__f2dace_SA_ddt_vn_cor_pc_d_3_s_577 = m.size.at(3);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_0_s_574 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_1_s_575 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_2_s_576 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_3_s_577 = m.lbound.at(3);
    x->ddt_vn_cor_pc = arr;
  }

  read_line(s, {"# ddt_w_adv_pc"}); // Should contain '# ddt_w_adv_pc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_w_adv_pc)>::type>(s);
    x->__f2dace_SA_ddt_w_adv_pc_d_0_s_578 = m.size.at(0);
    x->__f2dace_SA_ddt_w_adv_pc_d_1_s_579 = m.size.at(1);
    x->__f2dace_SA_ddt_w_adv_pc_d_2_s_580 = m.size.at(2);
    x->__f2dace_SA_ddt_w_adv_pc_d_3_s_581 = m.size.at(3);
    x->__f2dace_SOA_ddt_w_adv_pc_d_0_s_578 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_w_adv_pc_d_1_s_579 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_w_adv_pc_d_2_s_580 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_w_adv_pc_d_3_s_581 = m.lbound.at(3);
    x->ddt_w_adv_pc = arr;
  }

  read_line(s, {"# ddt_vn_dyn"}); // Should contain '# ddt_vn_dyn'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_dyn)>::type>(s);
    x->__f2dace_SA_ddt_vn_dyn_d_0_s_582 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_dyn_d_1_s_583 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_dyn_d_2_s_584 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_dyn_d_0_s_582 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_dyn_d_1_s_583 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_dyn_d_2_s_584 = m.lbound.at(2);
    x->ddt_vn_dyn = arr;
  }

  read_line(s, {"# ddt_vn_grf"}); // Should contain '# ddt_vn_grf'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_grf)>::type>(s);
    x->__f2dace_SA_ddt_vn_grf_d_0_s_585 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_grf_d_1_s_586 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_grf_d_2_s_587 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_grf_d_0_s_585 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_grf_d_1_s_586 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_grf_d_2_s_587 = m.lbound.at(2);
    x->ddt_vn_grf = arr;
  }

  read_line(s, {"# ddt_vn_dyn_is_associated"}); // Should contain '#
                                                // ddt_vn_dyn_is_associated'

  deserialize(&(x->ddt_vn_dyn_is_associated), s);

  read_line(s, {"# ddt_vn_adv_is_associated"}); // Should contain '#
                                                // ddt_vn_adv_is_associated'

  deserialize(&(x->ddt_vn_adv_is_associated), s);

  read_line(s, {"# ddt_vn_cor_is_associated"}); // Should contain '#
                                                // ddt_vn_cor_is_associated'

  deserialize(&(x->ddt_vn_cor_is_associated), s);

  read_line(s, {"# ddt_vn_grf_is_associated"}); // Should contain '#
                                                // ddt_vn_grf_is_associated'

  deserialize(&(x->ddt_vn_grf_is_associated), s);

  read_line(s, {"# max_vcfl_dyn"}); // Should contain '# max_vcfl_dyn'

  deserialize(&(x->max_vcfl_dyn), s);
}

void deserialize(t_nh_ref *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# vn_ref"}); // Should contain '# vn_ref'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ref)>::type>(s);
    x->__f2dace_SA_vn_ref_d_0_s_588 = m.size.at(0);
    x->__f2dace_SA_vn_ref_d_1_s_589 = m.size.at(1);
    x->__f2dace_SA_vn_ref_d_2_s_590 = m.size.at(2);
    x->__f2dace_SOA_vn_ref_d_0_s_588 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ref_d_1_s_589 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ref_d_2_s_590 = m.lbound.at(2);
    x->vn_ref = arr;
  }
}

void deserialize(t_nh_metrics *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# rayleigh_vn"}); // Should contain '# rayleigh_vn'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rayleigh_vn)>::type>(s);
    x->__f2dace_SA_rayleigh_vn_d_0_s_591 = m.size.at(0);
    x->__f2dace_SOA_rayleigh_vn_d_0_s_591 = m.lbound.at(0);
    x->rayleigh_vn = arr;
  }

  read_line(s, {"# vwind_expl_wgt"}); // Should contain '# vwind_expl_wgt'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vwind_expl_wgt)>::type>(s);
    x->__f2dace_SA_vwind_expl_wgt_d_0_s_592 = m.size.at(0);
    x->__f2dace_SA_vwind_expl_wgt_d_1_s_593 = m.size.at(1);
    x->__f2dace_SOA_vwind_expl_wgt_d_0_s_592 = m.lbound.at(0);
    x->__f2dace_SOA_vwind_expl_wgt_d_1_s_593 = m.lbound.at(1);
    x->vwind_expl_wgt = arr;
  }

  read_line(s, {"# ddxn_z_full"}); // Should contain '# ddxn_z_full'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddxn_z_full)>::type>(s);
    x->__f2dace_SA_ddxn_z_full_d_0_s_594 = m.size.at(0);
    x->__f2dace_SA_ddxn_z_full_d_1_s_595 = m.size.at(1);
    x->__f2dace_SA_ddxn_z_full_d_2_s_596 = m.size.at(2);
    x->__f2dace_SOA_ddxn_z_full_d_0_s_594 = m.lbound.at(0);
    x->__f2dace_SOA_ddxn_z_full_d_1_s_595 = m.lbound.at(1);
    x->__f2dace_SOA_ddxn_z_full_d_2_s_596 = m.lbound.at(2);
    x->ddxn_z_full = arr;
  }

  read_line(s, {"# ddxt_z_full"}); // Should contain '# ddxt_z_full'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddxt_z_full)>::type>(s);
    x->__f2dace_SA_ddxt_z_full_d_0_s_597 = m.size.at(0);
    x->__f2dace_SA_ddxt_z_full_d_1_s_598 = m.size.at(1);
    x->__f2dace_SA_ddxt_z_full_d_2_s_599 = m.size.at(2);
    x->__f2dace_SOA_ddxt_z_full_d_0_s_597 = m.lbound.at(0);
    x->__f2dace_SOA_ddxt_z_full_d_1_s_598 = m.lbound.at(1);
    x->__f2dace_SOA_ddxt_z_full_d_2_s_599 = m.lbound.at(2);
    x->ddxt_z_full = arr;
  }

  read_line(s, {"# ddqz_z_full_e"}); // Should contain '# ddqz_z_full_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_full_e)>::type>(s);
    x->__f2dace_SA_ddqz_z_full_e_d_0_s_600 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_full_e_d_1_s_601 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_full_e_d_2_s_602 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_full_e_d_0_s_600 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_full_e_d_1_s_601 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_full_e_d_2_s_602 = m.lbound.at(2);
    x->ddqz_z_full_e = arr;
  }

  read_line(s, {"# ddqz_z_half"}); // Should contain '# ddqz_z_half'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_half)>::type>(s);
    x->__f2dace_SA_ddqz_z_half_d_0_s_603 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_half_d_1_s_604 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_half_d_2_s_605 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_half_d_0_s_603 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_half_d_1_s_604 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_half_d_2_s_605 = m.lbound.at(2);
    x->ddqz_z_half = arr;
  }

  read_line(s, {"# inv_ddqz_z_full"}); // Should contain '# inv_ddqz_z_full'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->inv_ddqz_z_full)>::type>(
            s);
    x->__f2dace_SA_inv_ddqz_z_full_d_0_s_606 = m.size.at(0);
    x->__f2dace_SA_inv_ddqz_z_full_d_1_s_607 = m.size.at(1);
    x->__f2dace_SA_inv_ddqz_z_full_d_2_s_608 = m.size.at(2);
    x->__f2dace_SOA_inv_ddqz_z_full_d_0_s_606 = m.lbound.at(0);
    x->__f2dace_SOA_inv_ddqz_z_full_d_1_s_607 = m.lbound.at(1);
    x->__f2dace_SOA_inv_ddqz_z_full_d_2_s_608 = m.lbound.at(2);
    x->inv_ddqz_z_full = arr;
  }

  read_line(s, {"# wgtfac_c"}); // Should contain '# wgtfac_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfac_c)>::type>(s);
    x->__f2dace_SA_wgtfac_c_d_0_s_609 = m.size.at(0);
    x->__f2dace_SA_wgtfac_c_d_1_s_610 = m.size.at(1);
    x->__f2dace_SA_wgtfac_c_d_2_s_611 = m.size.at(2);
    x->__f2dace_SOA_wgtfac_c_d_0_s_609 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfac_c_d_1_s_610 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfac_c_d_2_s_611 = m.lbound.at(2);
    x->wgtfac_c = arr;
  }

  read_line(s, {"# wgtfac_e"}); // Should contain '# wgtfac_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfac_e)>::type>(s);
    x->__f2dace_SA_wgtfac_e_d_0_s_612 = m.size.at(0);
    x->__f2dace_SA_wgtfac_e_d_1_s_613 = m.size.at(1);
    x->__f2dace_SA_wgtfac_e_d_2_s_614 = m.size.at(2);
    x->__f2dace_SOA_wgtfac_e_d_0_s_612 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfac_e_d_1_s_613 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfac_e_d_2_s_614 = m.lbound.at(2);
    x->wgtfac_e = arr;
  }

  read_line(s, {"# wgtfacq_c"}); // Should contain '# wgtfacq_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq_c)>::type>(s);
    x->__f2dace_SA_wgtfacq_c_d_0_s_615 = m.size.at(0);
    x->__f2dace_SA_wgtfacq_c_d_1_s_616 = m.size.at(1);
    x->__f2dace_SA_wgtfacq_c_d_2_s_617 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq_c_d_0_s_615 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq_c_d_1_s_616 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq_c_d_2_s_617 = m.lbound.at(2);
    x->wgtfacq_c = arr;
  }

  read_line(s, {"# wgtfacq_e"}); // Should contain '# wgtfacq_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq_e)>::type>(s);
    x->__f2dace_SA_wgtfacq_e_d_0_s_618 = m.size.at(0);
    x->__f2dace_SA_wgtfacq_e_d_1_s_619 = m.size.at(1);
    x->__f2dace_SA_wgtfacq_e_d_2_s_620 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq_e_d_0_s_618 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq_e_d_1_s_619 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq_e_d_2_s_620 = m.lbound.at(2);
    x->wgtfacq_e = arr;
  }

  read_line(s, {"# wgtfacq1_c"}); // Should contain '# wgtfacq1_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq1_c)>::type>(s);
    x->__f2dace_SA_wgtfacq1_c_d_0_s_621 = m.size.at(0);
    x->__f2dace_SA_wgtfacq1_c_d_1_s_622 = m.size.at(1);
    x->__f2dace_SA_wgtfacq1_c_d_2_s_623 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq1_c_d_0_s_621 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq1_c_d_1_s_622 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq1_c_d_2_s_623 = m.lbound.at(2);
    x->wgtfacq1_c = arr;
  }

  read_line(s, {"# coeff_gradekin"}); // Should contain '# coeff_gradekin'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff_gradekin)>::type>(s);
    x->__f2dace_SA_coeff_gradekin_d_0_s_624 = m.size.at(0);
    x->__f2dace_SA_coeff_gradekin_d_1_s_625 = m.size.at(1);
    x->__f2dace_SA_coeff_gradekin_d_2_s_626 = m.size.at(2);
    x->__f2dace_SOA_coeff_gradekin_d_0_s_624 = m.lbound.at(0);
    x->__f2dace_SOA_coeff_gradekin_d_1_s_625 = m.lbound.at(1);
    x->__f2dace_SOA_coeff_gradekin_d_2_s_626 = m.lbound.at(2);
    x->coeff_gradekin = arr;
  }

  read_line(s, {"# coeff1_dwdz"}); // Should contain '# coeff1_dwdz'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff1_dwdz)>::type>(s);
    x->__f2dace_SA_coeff1_dwdz_d_0_s_627 = m.size.at(0);
    x->__f2dace_SA_coeff1_dwdz_d_1_s_628 = m.size.at(1);
    x->__f2dace_SA_coeff1_dwdz_d_2_s_629 = m.size.at(2);
    x->__f2dace_SOA_coeff1_dwdz_d_0_s_627 = m.lbound.at(0);
    x->__f2dace_SOA_coeff1_dwdz_d_1_s_628 = m.lbound.at(1);
    x->__f2dace_SOA_coeff1_dwdz_d_2_s_629 = m.lbound.at(2);
    x->coeff1_dwdz = arr;
  }

  read_line(s, {"# coeff2_dwdz"}); // Should contain '# coeff2_dwdz'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff2_dwdz)>::type>(s);
    x->__f2dace_SA_coeff2_dwdz_d_0_s_630 = m.size.at(0);
    x->__f2dace_SA_coeff2_dwdz_d_1_s_631 = m.size.at(1);
    x->__f2dace_SA_coeff2_dwdz_d_2_s_632 = m.size.at(2);
    x->__f2dace_SOA_coeff2_dwdz_d_0_s_630 = m.lbound.at(0);
    x->__f2dace_SOA_coeff2_dwdz_d_1_s_631 = m.lbound.at(1);
    x->__f2dace_SOA_coeff2_dwdz_d_2_s_632 = m.lbound.at(2);
    x->coeff2_dwdz = arr;
  }

  read_line(s, {"# zdiff_gradp"}); // Should contain '# zdiff_gradp'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->zdiff_gradp)>::type>(s);
    x->__f2dace_SA_zdiff_gradp_d_0_s_633 = m.size.at(0);
    x->__f2dace_SA_zdiff_gradp_d_1_s_634 = m.size.at(1);
    x->__f2dace_SA_zdiff_gradp_d_2_s_635 = m.size.at(2);
    x->__f2dace_SA_zdiff_gradp_d_3_s_636 = m.size.at(3);
    x->__f2dace_SOA_zdiff_gradp_d_0_s_633 = m.lbound.at(0);
    x->__f2dace_SOA_zdiff_gradp_d_1_s_634 = m.lbound.at(1);
    x->__f2dace_SOA_zdiff_gradp_d_2_s_635 = m.lbound.at(2);
    x->__f2dace_SOA_zdiff_gradp_d_3_s_636 = m.lbound.at(3);
    x->zdiff_gradp = arr;
  }

  read_line(s, {"# coeff_gradp"}); // Should contain '# coeff_gradp'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff_gradp)>::type>(s);
    x->__f2dace_SA_coeff_gradp_d_0_s_637 = m.size.at(0);
    x->__f2dace_SA_coeff_gradp_d_1_s_638 = m.size.at(1);
    x->__f2dace_SA_coeff_gradp_d_2_s_639 = m.size.at(2);
    x->__f2dace_SA_coeff_gradp_d_3_s_640 = m.size.at(3);
    x->__f2dace_SOA_coeff_gradp_d_0_s_637 = m.lbound.at(0);
    x->__f2dace_SOA_coeff_gradp_d_1_s_638 = m.lbound.at(1);
    x->__f2dace_SOA_coeff_gradp_d_2_s_639 = m.lbound.at(2);
    x->__f2dace_SOA_coeff_gradp_d_3_s_640 = m.lbound.at(3);
    x->coeff_gradp = arr;
  }

  read_line(s, {"# exner_exfac"}); // Should contain '# exner_exfac'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_exfac)>::type>(s);
    x->__f2dace_SA_exner_exfac_d_0_s_641 = m.size.at(0);
    x->__f2dace_SA_exner_exfac_d_1_s_642 = m.size.at(1);
    x->__f2dace_SA_exner_exfac_d_2_s_643 = m.size.at(2);
    x->__f2dace_SOA_exner_exfac_d_0_s_641 = m.lbound.at(0);
    x->__f2dace_SOA_exner_exfac_d_1_s_642 = m.lbound.at(1);
    x->__f2dace_SOA_exner_exfac_d_2_s_643 = m.lbound.at(2);
    x->exner_exfac = arr;
  }

  read_line(s, {"# theta_ref_mc"}); // Should contain '# theta_ref_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_ref_mc)>::type>(s);
    x->__f2dace_SA_theta_ref_mc_d_0_s_644 = m.size.at(0);
    x->__f2dace_SA_theta_ref_mc_d_1_s_645 = m.size.at(1);
    x->__f2dace_SA_theta_ref_mc_d_2_s_646 = m.size.at(2);
    x->__f2dace_SOA_theta_ref_mc_d_0_s_644 = m.lbound.at(0);
    x->__f2dace_SOA_theta_ref_mc_d_1_s_645 = m.lbound.at(1);
    x->__f2dace_SOA_theta_ref_mc_d_2_s_646 = m.lbound.at(2);
    x->theta_ref_mc = arr;
  }

  read_line(s, {"# theta_ref_me"}); // Should contain '# theta_ref_me'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_ref_me)>::type>(s);
    x->__f2dace_SA_theta_ref_me_d_0_s_647 = m.size.at(0);
    x->__f2dace_SA_theta_ref_me_d_1_s_648 = m.size.at(1);
    x->__f2dace_SA_theta_ref_me_d_2_s_649 = m.size.at(2);
    x->__f2dace_SOA_theta_ref_me_d_0_s_647 = m.lbound.at(0);
    x->__f2dace_SOA_theta_ref_me_d_1_s_648 = m.lbound.at(1);
    x->__f2dace_SOA_theta_ref_me_d_2_s_649 = m.lbound.at(2);
    x->theta_ref_me = arr;
  }

  read_line(s, {"# theta_ref_ic"}); // Should contain '# theta_ref_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_ref_ic)>::type>(s);
    x->__f2dace_SA_theta_ref_ic_d_0_s_650 = m.size.at(0);
    x->__f2dace_SA_theta_ref_ic_d_1_s_651 = m.size.at(1);
    x->__f2dace_SA_theta_ref_ic_d_2_s_652 = m.size.at(2);
    x->__f2dace_SOA_theta_ref_ic_d_0_s_650 = m.lbound.at(0);
    x->__f2dace_SOA_theta_ref_ic_d_1_s_651 = m.lbound.at(1);
    x->__f2dace_SOA_theta_ref_ic_d_2_s_652 = m.lbound.at(2);
    x->theta_ref_ic = arr;
  }

  read_line(s, {"# exner_ref_mc"}); // Should contain '# exner_ref_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_ref_mc)>::type>(s);
    x->__f2dace_SA_exner_ref_mc_d_0_s_653 = m.size.at(0);
    x->__f2dace_SA_exner_ref_mc_d_1_s_654 = m.size.at(1);
    x->__f2dace_SA_exner_ref_mc_d_2_s_655 = m.size.at(2);
    x->__f2dace_SOA_exner_ref_mc_d_0_s_653 = m.lbound.at(0);
    x->__f2dace_SOA_exner_ref_mc_d_1_s_654 = m.lbound.at(1);
    x->__f2dace_SOA_exner_ref_mc_d_2_s_655 = m.lbound.at(2);
    x->exner_ref_mc = arr;
  }

  read_line(s, {"# rho_ref_mc"}); // Should contain '# rho_ref_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ref_mc)>::type>(s);
    x->__f2dace_SA_rho_ref_mc_d_0_s_656 = m.size.at(0);
    x->__f2dace_SA_rho_ref_mc_d_1_s_657 = m.size.at(1);
    x->__f2dace_SA_rho_ref_mc_d_2_s_658 = m.size.at(2);
    x->__f2dace_SOA_rho_ref_mc_d_0_s_656 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ref_mc_d_1_s_657 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ref_mc_d_2_s_658 = m.lbound.at(2);
    x->rho_ref_mc = arr;
  }

  read_line(s, {"# rho_ref_me"}); // Should contain '# rho_ref_me'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ref_me)>::type>(s);
    x->__f2dace_SA_rho_ref_me_d_0_s_659 = m.size.at(0);
    x->__f2dace_SA_rho_ref_me_d_1_s_660 = m.size.at(1);
    x->__f2dace_SA_rho_ref_me_d_2_s_661 = m.size.at(2);
    x->__f2dace_SOA_rho_ref_me_d_0_s_659 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ref_me_d_1_s_660 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ref_me_d_2_s_661 = m.lbound.at(2);
    x->rho_ref_me = arr;
  }

  read_line(s, {"# d_exner_dz_ref_ic"}); // Should contain '# d_exner_dz_ref_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->d_exner_dz_ref_ic)>::type>(
            s);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_0_s_662 = m.size.at(0);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_1_s_663 = m.size.at(1);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_2_s_664 = m.size.at(2);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_0_s_662 = m.lbound.at(0);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_1_s_663 = m.lbound.at(1);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_2_s_664 = m.lbound.at(2);
    x->d_exner_dz_ref_ic = arr;
  }

  read_line(s, {"# d2dexdz2_fac1_mc"}); // Should contain '# d2dexdz2_fac1_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->d2dexdz2_fac1_mc)>::type>(
            s);
    x->__f2dace_SA_d2dexdz2_fac1_mc_d_0_s_665 = m.size.at(0);
    x->__f2dace_SA_d2dexdz2_fac1_mc_d_1_s_666 = m.size.at(1);
    x->__f2dace_SA_d2dexdz2_fac1_mc_d_2_s_667 = m.size.at(2);
    x->__f2dace_SOA_d2dexdz2_fac1_mc_d_0_s_665 = m.lbound.at(0);
    x->__f2dace_SOA_d2dexdz2_fac1_mc_d_1_s_666 = m.lbound.at(1);
    x->__f2dace_SOA_d2dexdz2_fac1_mc_d_2_s_667 = m.lbound.at(2);
    x->d2dexdz2_fac1_mc = arr;
  }

  read_line(s, {"# d2dexdz2_fac2_mc"}); // Should contain '# d2dexdz2_fac2_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->d2dexdz2_fac2_mc)>::type>(
            s);
    x->__f2dace_SA_d2dexdz2_fac2_mc_d_0_s_668 = m.size.at(0);
    x->__f2dace_SA_d2dexdz2_fac2_mc_d_1_s_669 = m.size.at(1);
    x->__f2dace_SA_d2dexdz2_fac2_mc_d_2_s_670 = m.size.at(2);
    x->__f2dace_SOA_d2dexdz2_fac2_mc_d_0_s_668 = m.lbound.at(0);
    x->__f2dace_SOA_d2dexdz2_fac2_mc_d_1_s_669 = m.lbound.at(1);
    x->__f2dace_SOA_d2dexdz2_fac2_mc_d_2_s_670 = m.lbound.at(2);
    x->d2dexdz2_fac2_mc = arr;
  }

  read_line(s, {"# pg_exdist"}); // Should contain '# pg_exdist'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_exdist)>::type>(s);
    x->__f2dace_SA_pg_exdist_d_0_s_671 = m.size.at(0);
    x->__f2dace_SOA_pg_exdist_d_0_s_671 = m.lbound.at(0);
    x->pg_exdist = arr;
  }

  read_line(s, {"# vertidx_gradp"}); // Should contain '# vertidx_gradp'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vertidx_gradp)>::type>(s);
    x->__f2dace_SA_vertidx_gradp_d_0_s_672 = m.size.at(0);
    x->__f2dace_SA_vertidx_gradp_d_1_s_673 = m.size.at(1);
    x->__f2dace_SA_vertidx_gradp_d_2_s_674 = m.size.at(2);
    x->__f2dace_SA_vertidx_gradp_d_3_s_675 = m.size.at(3);
    x->__f2dace_SOA_vertidx_gradp_d_0_s_672 = m.lbound.at(0);
    x->__f2dace_SOA_vertidx_gradp_d_1_s_673 = m.lbound.at(1);
    x->__f2dace_SOA_vertidx_gradp_d_2_s_674 = m.lbound.at(2);
    x->__f2dace_SOA_vertidx_gradp_d_3_s_675 = m.lbound.at(3);
    x->vertidx_gradp = arr;
  }

  read_line(s, {"# pg_edgeidx"}); // Should contain '# pg_edgeidx'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_edgeidx)>::type>(s);
    x->__f2dace_SA_pg_edgeidx_d_0_s_676 = m.size.at(0);
    x->__f2dace_SOA_pg_edgeidx_d_0_s_676 = m.lbound.at(0);
    x->pg_edgeidx = arr;
  }

  read_line(s, {"# pg_edgeblk"}); // Should contain '# pg_edgeblk'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_edgeblk)>::type>(s);
    x->__f2dace_SA_pg_edgeblk_d_0_s_677 = m.size.at(0);
    x->__f2dace_SOA_pg_edgeblk_d_0_s_677 = m.lbound.at(0);
    x->pg_edgeblk = arr;
  }

  read_line(s, {"# pg_vertidx"}); // Should contain '# pg_vertidx'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->pg_vertidx)>::type>(s);
    x->__f2dace_SA_pg_vertidx_d_0_s_678 = m.size.at(0);
    x->__f2dace_SOA_pg_vertidx_d_0_s_678 = m.lbound.at(0);
    x->pg_vertidx = arr;
  }

  read_line(s, {"# bdy_mflx_e_idx"}); // Should contain '# bdy_mflx_e_idx'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->bdy_mflx_e_idx)>::type>(s);
    x->__f2dace_SA_bdy_mflx_e_idx_d_0_s_679 = m.size.at(0);
    x->__f2dace_SOA_bdy_mflx_e_idx_d_0_s_679 = m.lbound.at(0);
    x->bdy_mflx_e_idx = arr;
  }

  read_line(s, {"# bdy_mflx_e_blk"}); // Should contain '# bdy_mflx_e_blk'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->bdy_mflx_e_blk)>::type>(s);
    x->__f2dace_SA_bdy_mflx_e_blk_d_0_s_680 = m.size.at(0);
    x->__f2dace_SOA_bdy_mflx_e_blk_d_0_s_680 = m.lbound.at(0);
    x->bdy_mflx_e_blk = arr;
  }

  read_line(s, {"# deepatmo_gradh_mc"}); // Should contain '# deepatmo_gradh_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_gradh_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_gradh_mc_d_0_s_681 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_gradh_mc_d_0_s_681 = m.lbound.at(0);
    x->deepatmo_gradh_mc = arr;
  }

  read_line(s, {"# deepatmo_invr_mc"}); // Should contain '# deepatmo_invr_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_invr_mc_d_0_s_682 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_invr_mc_d_0_s_682 = m.lbound.at(0);
    x->deepatmo_invr_mc = arr;
  }

  read_line(s,
            {"# deepatmo_gradh_ifc"}); // Should contain '# deepatmo_gradh_ifc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<
        std::remove_pointer<decltype(x->deepatmo_gradh_ifc)>::type>(s);
    x->__f2dace_SA_deepatmo_gradh_ifc_d_0_s_683 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_gradh_ifc_d_0_s_683 = m.lbound.at(0);
    x->deepatmo_gradh_ifc = arr;
  }

  read_line(s, {"# deepatmo_invr_ifc"}); // Should contain '# deepatmo_invr_ifc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_ifc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_invr_ifc_d_0_s_684 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_invr_ifc_d_0_s_684 = m.lbound.at(0);
    x->deepatmo_invr_ifc = arr;
  }

  read_line(s, {"# pg_listdim"}); // Should contain '# pg_listdim'

  deserialize(&(x->pg_listdim), s);

  read_line(s, {"# bdy_mflx_e_dim"}); // Should contain '# bdy_mflx_e_dim'

  deserialize(&(x->bdy_mflx_e_dim), s);
}

void deserialize(t_nh_state *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# prog"}); // Should contain '# prog'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_prog_d_0_s_685 = m.size[0];
    x->__f2dace_SOA_prog_d_0_s_685 = m.lbound[0];
    // TODO: THIS IS POTENTIALLY BUGGY, BECAUSE IT IS NOT REALLY TESTED.
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->prog = m.read<std::remove_pointer<decltype(x->prog)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# diag"}); // Should contain '# diag'

  x->diag = new std::remove_pointer<decltype(x->diag)>::type;
  deserialize(x->diag, s);

  read_line(s, {"# ref"}); // Should contain '# ref'

  x->ref = new std::remove_pointer<decltype(x->ref)>::type;
  deserialize(x->ref, s);

  read_line(s, {"# metrics"}); // Should contain '# metrics'

  x->metrics = new std::remove_pointer<decltype(x->metrics)>::type;
  deserialize(x->metrics, s);
}

void deserialize(t_prepare_adv *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# mass_flx_me"}); // Should contain '# mass_flx_me'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mass_flx_me)>::type>(s);
    x->__f2dace_SA_mass_flx_me_d_0_s_707 = m.size.at(0);
    x->__f2dace_SA_mass_flx_me_d_1_s_708 = m.size.at(1);
    x->__f2dace_SA_mass_flx_me_d_2_s_709 = m.size.at(2);
    x->__f2dace_SOA_mass_flx_me_d_0_s_707 = m.lbound.at(0);
    x->__f2dace_SOA_mass_flx_me_d_1_s_708 = m.lbound.at(1);
    x->__f2dace_SOA_mass_flx_me_d_2_s_709 = m.lbound.at(2);
    x->mass_flx_me = arr;
  }
}

template <typename T>
void add_line(const T &x, std::ostream &s, bool trailing_newline = true) {
  s << x;
  if (trailing_newline)
    s << std::endl;
}
void add_line(long long x, std::ostream &s, bool trailing_newline = true) {
  s << x;
  if (trailing_newline)
    s << std::endl;
}
void add_line(long double x, std::ostream &s, bool trailing_newline = true) {
  s << std::setprecision(20) << x;
  if (trailing_newline)
    s << std::endl;
}
void add_line(bool x, std::ostream &s, bool trailing_newline = true) {
  add_line(int(x), s, trailing_newline);
}
template <typename T> std::string serialize(const T *x) {
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

std::string serialize(const t_grid_domain_decomp_info *x) {
  std::stringstream s;
  add_line("# owner_mask", s);

  add_line("# alloc", s);
  add_line(serialize(x->owner_mask != nullptr), s);
  if (x->owner_mask) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->owner_mask);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->owner_mask[i]), s);
      }
    }

  } // CONCLUDING IF
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_int_state *x) {
  std::stringstream s;
  add_line("# c_lin_e", s);

  add_line("# alloc", s);
  add_line(serialize(x->c_lin_e != nullptr), s);
  if (x->c_lin_e) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->c_lin_e);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->c_lin_e[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# e_bln_c_s", s);

  add_line("# alloc", s);
  add_line(serialize(x->e_bln_c_s != nullptr), s);
  if (x->e_bln_c_s) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->e_bln_c_s);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->e_bln_c_s[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# cells_aw_verts", s);

  add_line("# alloc", s);
  add_line(serialize(x->cells_aw_verts != nullptr), s);
  if (x->cells_aw_verts) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->cells_aw_verts);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->cells_aw_verts[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# rbf_vec_coeff_e", s);

  add_line("# alloc", s);
  add_line(serialize(x->rbf_vec_coeff_e != nullptr), s);
  if (x->rbf_vec_coeff_e) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->rbf_vec_coeff_e);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->rbf_vec_coeff_e[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# geofac_grdiv", s);

  add_line("# alloc", s);
  add_line(serialize(x->geofac_grdiv != nullptr), s);
  if (x->geofac_grdiv) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->geofac_grdiv);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->geofac_grdiv[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# geofac_rot", s);

  add_line("# alloc", s);
  add_line(serialize(x->geofac_rot != nullptr), s);
  if (x->geofac_rot) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->geofac_rot);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->geofac_rot[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# geofac_n2s", s);

  add_line("# alloc", s);
  add_line(serialize(x->geofac_n2s != nullptr), s);
  if (x->geofac_n2s) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->geofac_n2s);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->geofac_n2s[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# geofac_grg", s);

  add_line("# alloc", s);
  add_line(serialize(x->geofac_grg != nullptr), s);
  if (x->geofac_grg) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->geofac_grg);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->geofac_grg[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# pos_on_tplane_e", s);

  add_line("# alloc", s);
  add_line(serialize(x->pos_on_tplane_e != nullptr), s);
  if (x->pos_on_tplane_e) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->pos_on_tplane_e);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->pos_on_tplane_e[i]), s);
      }
    }

  } // CONCLUDING IF
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_tangent_vectors *x) {
  std::stringstream s;
  add_line("# v1", s);
  add_line(serialize(x->v1), s);
  add_line("# v2", s);
  add_line(serialize(x->v2), s);
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_grid_cells *x) {
  std::stringstream s;
  add_line("# neighbor_idx", s);

  add_line("# alloc", s);
  add_line(serialize(x->neighbor_idx != nullptr), s);
  if (x->neighbor_idx) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->neighbor_idx);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->neighbor_idx[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# neighbor_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->neighbor_blk != nullptr), s);
  if (x->neighbor_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->neighbor_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->neighbor_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# edge_idx", s);

  add_line("# alloc", s);
  add_line(serialize(x->edge_idx != nullptr), s);
  if (x->edge_idx) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->edge_idx);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->edge_idx[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# edge_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->edge_blk != nullptr), s);
  if (x->edge_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->edge_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->edge_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# area", s);

  add_line("# assoc", s);
  add_line(serialize(x->area != nullptr), s);

  if (x->area)
    add_line(serialize_array(x->area), s);

  add_line("# start_index", s);

  add_line("# alloc", s);
  add_line(serialize(x->start_index != nullptr), s);
  if (x->start_index) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->start_index);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->start_index[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# end_index", s);

  add_line("# alloc", s);
  add_line(serialize(x->end_index != nullptr), s);
  if (x->end_index) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->end_index);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->end_index[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# start_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->start_blk != nullptr), s);
  if (x->start_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->start_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->start_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# start_block", s);

  add_line("# alloc", s);
  add_line(serialize(x->start_block != nullptr), s);
  if (x->start_block) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->start_block);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->start_block[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# end_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->end_blk != nullptr), s);
  if (x->end_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->end_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->end_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# end_block", s);

  add_line("# alloc", s);
  add_line(serialize(x->end_block != nullptr), s);
  if (x->end_block) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->end_block);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->end_block[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# decomp_info", s);
  add_line(serialize(x->decomp_info), s);
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_grid_edges *x) {
  std::stringstream s;
  add_line("# cell_idx", s);

  add_line("# alloc", s);
  add_line(serialize(x->cell_idx != nullptr), s);
  if (x->cell_idx) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->cell_idx);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->cell_idx[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# cell_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->cell_blk != nullptr), s);
  if (x->cell_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->cell_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->cell_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# vertex_idx", s);

  add_line("# alloc", s);
  add_line(serialize(x->vertex_idx != nullptr), s);
  if (x->vertex_idx) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->vertex_idx);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->vertex_idx[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# vertex_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->vertex_blk != nullptr), s);
  if (x->vertex_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->vertex_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->vertex_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# tangent_orientation", s);

  add_line("# alloc", s);
  add_line(serialize(x->tangent_orientation != nullptr), s);
  if (x->tangent_orientation) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->tangent_orientation);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->tangent_orientation[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# quad_idx", s);

  add_line("# alloc", s);
  add_line(serialize(x->quad_idx != nullptr), s);
  if (x->quad_idx) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->quad_idx);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->quad_idx[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# quad_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->quad_blk != nullptr), s);
  if (x->quad_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->quad_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->quad_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# primal_normal_cell", s);

  add_line("# alloc", s);
  add_line(serialize(x->primal_normal_cell != nullptr), s);
  if (x->primal_normal_cell) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->primal_normal_cell);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->primal_normal_cell[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# dual_normal_cell", s);

  add_line("# alloc", s);
  add_line(serialize(x->dual_normal_cell != nullptr), s);
  if (x->dual_normal_cell) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->dual_normal_cell);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->dual_normal_cell[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# inv_primal_edge_length", s);

  add_line("# alloc", s);
  add_line(serialize(x->inv_primal_edge_length != nullptr), s);
  if (x->inv_primal_edge_length) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->inv_primal_edge_length);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->inv_primal_edge_length[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# inv_dual_edge_length", s);

  add_line("# alloc", s);
  add_line(serialize(x->inv_dual_edge_length != nullptr), s);
  if (x->inv_dual_edge_length) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->inv_dual_edge_length);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->inv_dual_edge_length[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# area_edge", s);

  add_line("# alloc", s);
  add_line(serialize(x->area_edge != nullptr), s);
  if (x->area_edge) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->area_edge);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->area_edge[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# f_e", s);

  add_line("# alloc", s);
  add_line(serialize(x->f_e != nullptr), s);
  if (x->f_e) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->f_e);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->f_e[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# fn_e", s);

  add_line("# alloc", s);
  add_line(serialize(x->fn_e != nullptr), s);
  if (x->fn_e) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->fn_e);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->fn_e[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# ft_e", s);

  add_line("# alloc", s);
  add_line(serialize(x->ft_e != nullptr), s);
  if (x->ft_e) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->ft_e);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->ft_e[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# start_index", s);

  add_line("# alloc", s);
  add_line(serialize(x->start_index != nullptr), s);
  if (x->start_index) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->start_index);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->start_index[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# end_index", s);

  add_line("# alloc", s);
  add_line(serialize(x->end_index != nullptr), s);
  if (x->end_index) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->end_index);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->end_index[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# start_block", s);

  add_line("# alloc", s);
  add_line(serialize(x->start_block != nullptr), s);
  if (x->start_block) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->start_block);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->start_block[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# end_block", s);

  add_line("# alloc", s);
  add_line(serialize(x->end_block != nullptr), s);
  if (x->end_block) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->end_block);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->end_block[i]), s);
      }
    }

  } // CONCLUDING IF
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_grid_vertices *x) {
  std::stringstream s;
  add_line("# cell_idx", s);

  add_line("# alloc", s);
  add_line(serialize(x->cell_idx != nullptr), s);
  if (x->cell_idx) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->cell_idx);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->cell_idx[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# cell_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->cell_blk != nullptr), s);
  if (x->cell_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->cell_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->cell_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# edge_idx", s);

  add_line("# alloc", s);
  add_line(serialize(x->edge_idx != nullptr), s);
  if (x->edge_idx) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->edge_idx);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->edge_idx[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# edge_blk", s);

  add_line("# alloc", s);
  add_line(serialize(x->edge_blk != nullptr), s);
  if (x->edge_blk) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->edge_blk);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->edge_blk[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# start_index", s);

  add_line("# alloc", s);
  add_line(serialize(x->start_index != nullptr), s);
  if (x->start_index) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->start_index);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->start_index[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# end_index", s);

  add_line("# alloc", s);
  add_line(serialize(x->end_index != nullptr), s);
  if (x->end_index) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->end_index);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->end_index[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# start_block", s);

  add_line("# alloc", s);
  add_line(serialize(x->start_block != nullptr), s);
  if (x->start_block) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->start_block);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->start_block[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# end_block", s);

  add_line("# alloc", s);
  add_line(serialize(x->end_block != nullptr), s);
  if (x->end_block) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->end_block);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->end_block[i]), s);
      }
    }

  } // CONCLUDING IF
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_patch *x) {
  std::stringstream s;
  add_line("# id", s);
  add_line(serialize(x->id), s);
  add_line("# n_childdom", s);
  add_line(serialize(x->n_childdom), s);
  add_line("# nblks_c", s);
  add_line(serialize(x->nblks_c), s);
  add_line("# nblks_e", s);
  add_line(serialize(x->nblks_e), s);
  add_line("# nblks_v", s);
  add_line(serialize(x->nblks_v), s);
  add_line("# nlev", s);
  add_line(serialize(x->nlev), s);
  add_line("# nlevp1", s);
  add_line(serialize(x->nlevp1), s);
  add_line("# nshift", s);
  add_line(serialize(x->nshift), s);
  add_line("# cells", s);
  add_line(serialize(x->cells), s);
  add_line("# edges", s);
  add_line(serialize(x->edges), s);
  add_line("# verts", s);
  add_line(serialize(x->verts), s);
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_prog *x) {
  std::stringstream s;
  add_line("# w", s);

  add_line("# assoc", s);
  add_line(serialize(x->w != nullptr), s);

  if (x->w)
    add_line(serialize_array(x->w), s);

  add_line("# vn", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn != nullptr), s);

  if (x->vn)
    add_line(serialize_array(x->vn), s);

  add_line("# rho", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho != nullptr), s);

  if (x->rho)
    add_line(serialize_array(x->rho), s);

  add_line("# exner", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner != nullptr), s);

  if (x->exner)
    add_line(serialize_array(x->exner), s);

  add_line("# theta_v", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_v != nullptr), s);

  if (x->theta_v)
    add_line(serialize_array(x->theta_v), s);

  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_diag *x) {
  std::stringstream s;
  add_line("# exner_pr", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_pr != nullptr), s);

  if (x->exner_pr)
    add_line(serialize_array(x->exner_pr), s);

  add_line("# rho_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_ic != nullptr), s);

  if (x->rho_ic)
    add_line(serialize_array(x->rho_ic), s);

  add_line("# theta_v_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_v_ic != nullptr), s);

  if (x->theta_v_ic)
    add_line(serialize_array(x->theta_v_ic), s);

  add_line("# grf_tend_vn", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_vn != nullptr), s);

  if (x->grf_tend_vn)
    add_line(serialize_array(x->grf_tend_vn), s);

  add_line("# grf_tend_mflx", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_mflx != nullptr), s);

  if (x->grf_tend_mflx)
    add_line(serialize_array(x->grf_tend_mflx), s);

  add_line("# grf_bdy_mflx", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_bdy_mflx != nullptr), s);

  if (x->grf_bdy_mflx)
    add_line(serialize_array(x->grf_bdy_mflx), s);

  add_line("# vn_ie_int", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ie_int != nullptr), s);

  if (x->vn_ie_int)
    add_line(serialize_array(x->vn_ie_int), s);

  add_line("# vn_ie_ubc", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ie_ubc != nullptr), s);

  if (x->vn_ie_ubc)
    add_line(serialize_array(x->vn_ie_ubc), s);

  add_line("# vn_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_incr != nullptr), s);

  if (x->vn_incr)
    add_line(serialize_array(x->vn_incr), s);

  add_line("# vt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vt != nullptr), s);

  if (x->vt)
    add_line(serialize_array(x->vt), s);

  add_line("# ddt_vn_phy", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_phy != nullptr), s);

  if (x->ddt_vn_phy)
    add_line(serialize_array(x->ddt_vn_phy), s);

  add_line("# vn_ie", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ie != nullptr), s);

  if (x->vn_ie)
    add_line(serialize_array(x->vn_ie), s);

  add_line("# w_concorr_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->w_concorr_c != nullptr), s);

  if (x->w_concorr_c)
    add_line(serialize_array(x->w_concorr_c), s);

  add_line("# ddt_vn_apc_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_apc_pc != nullptr), s);

  if (x->ddt_vn_apc_pc)
    add_line(serialize_array(x->ddt_vn_apc_pc), s);

  add_line("# ddt_vn_cor_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_cor_pc != nullptr), s);

  if (x->ddt_vn_cor_pc)
    add_line(serialize_array(x->ddt_vn_cor_pc), s);

  add_line("# ddt_w_adv_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_w_adv_pc != nullptr), s);

  if (x->ddt_w_adv_pc)
    add_line(serialize_array(x->ddt_w_adv_pc), s);

  add_line("# ddt_vn_dyn", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_dyn != nullptr), s);

  if (x->ddt_vn_dyn)
    add_line(serialize_array(x->ddt_vn_dyn), s);

  add_line("# ddt_vn_grf", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_grf != nullptr), s);

  if (x->ddt_vn_grf)
    add_line(serialize_array(x->ddt_vn_grf), s);

  add_line("# ddt_vn_dyn_is_associated", s);
  add_line(serialize(x->ddt_vn_dyn_is_associated), s);
  add_line("# ddt_vn_adv_is_associated", s);
  add_line(serialize(x->ddt_vn_adv_is_associated), s);
  add_line("# ddt_vn_cor_is_associated", s);
  add_line(serialize(x->ddt_vn_cor_is_associated), s);
  add_line("# ddt_vn_grf_is_associated", s);
  add_line(serialize(x->ddt_vn_grf_is_associated), s);
  add_line("# max_vcfl_dyn", s);
  add_line(serialize(x->max_vcfl_dyn), s);
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_ref *x) {
  std::stringstream s;
  add_line("# vn_ref", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ref != nullptr), s);

  if (x->vn_ref)
    add_line(serialize_array(x->vn_ref), s);

  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_metrics *x) {
  std::stringstream s;
  add_line("# rayleigh_vn", s);

  add_line("# assoc", s);
  add_line(serialize(x->rayleigh_vn != nullptr), s);

  if (x->rayleigh_vn)
    add_line(serialize_array(x->rayleigh_vn), s);

  add_line("# vwind_expl_wgt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vwind_expl_wgt != nullptr), s);

  if (x->vwind_expl_wgt)
    add_line(serialize_array(x->vwind_expl_wgt), s);

  add_line("# ddxn_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddxn_z_full != nullptr), s);

  if (x->ddxn_z_full)
    add_line(serialize_array(x->ddxn_z_full), s);

  add_line("# ddxt_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddxt_z_full != nullptr), s);

  if (x->ddxt_z_full)
    add_line(serialize_array(x->ddxt_z_full), s);

  add_line("# ddqz_z_full_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddqz_z_full_e != nullptr), s);

  if (x->ddqz_z_full_e)
    add_line(serialize_array(x->ddqz_z_full_e), s);

  add_line("# ddqz_z_half", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddqz_z_half != nullptr), s);

  if (x->ddqz_z_half)
    add_line(serialize_array(x->ddqz_z_half), s);

  add_line("# inv_ddqz_z_full", s);

  add_line("# assoc", s);
  add_line(serialize(x->inv_ddqz_z_full != nullptr), s);

  if (x->inv_ddqz_z_full)
    add_line(serialize_array(x->inv_ddqz_z_full), s);

  add_line("# wgtfac_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfac_c != nullptr), s);

  if (x->wgtfac_c)
    add_line(serialize_array(x->wgtfac_c), s);

  add_line("# wgtfac_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfac_e != nullptr), s);

  if (x->wgtfac_e)
    add_line(serialize_array(x->wgtfac_e), s);

  add_line("# wgtfacq_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfacq_c != nullptr), s);

  if (x->wgtfacq_c)
    add_line(serialize_array(x->wgtfacq_c), s);

  add_line("# wgtfacq_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfacq_e != nullptr), s);

  if (x->wgtfacq_e)
    add_line(serialize_array(x->wgtfacq_e), s);

  add_line("# wgtfacq1_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfacq1_c != nullptr), s);

  if (x->wgtfacq1_c)
    add_line(serialize_array(x->wgtfacq1_c), s);

  add_line("# coeff_gradekin", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff_gradekin != nullptr), s);

  if (x->coeff_gradekin)
    add_line(serialize_array(x->coeff_gradekin), s);

  add_line("# coeff1_dwdz", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff1_dwdz != nullptr), s);

  if (x->coeff1_dwdz)
    add_line(serialize_array(x->coeff1_dwdz), s);

  add_line("# coeff2_dwdz", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff2_dwdz != nullptr), s);

  if (x->coeff2_dwdz)
    add_line(serialize_array(x->coeff2_dwdz), s);

  add_line("# zdiff_gradp", s);

  add_line("# assoc", s);
  add_line(serialize(x->zdiff_gradp != nullptr), s);

  if (x->zdiff_gradp)
    add_line(serialize_array(x->zdiff_gradp), s);

  add_line("# coeff_gradp", s);

  add_line("# assoc", s);
  add_line(serialize(x->coeff_gradp != nullptr), s);

  if (x->coeff_gradp)
    add_line(serialize_array(x->coeff_gradp), s);

  add_line("# exner_exfac", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_exfac != nullptr), s);

  if (x->exner_exfac)
    add_line(serialize_array(x->exner_exfac), s);

  add_line("# theta_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_ref_mc != nullptr), s);

  if (x->theta_ref_mc)
    add_line(serialize_array(x->theta_ref_mc), s);

  add_line("# theta_ref_me", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_ref_me != nullptr), s);

  if (x->theta_ref_me)
    add_line(serialize_array(x->theta_ref_me), s);

  add_line("# theta_ref_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_ref_ic != nullptr), s);

  if (x->theta_ref_ic)
    add_line(serialize_array(x->theta_ref_ic), s);

  add_line("# exner_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_ref_mc != nullptr), s);

  if (x->exner_ref_mc)
    add_line(serialize_array(x->exner_ref_mc), s);

  add_line("# rho_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_ref_mc != nullptr), s);

  if (x->rho_ref_mc)
    add_line(serialize_array(x->rho_ref_mc), s);

  add_line("# rho_ref_me", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_ref_me != nullptr), s);

  if (x->rho_ref_me)
    add_line(serialize_array(x->rho_ref_me), s);

  add_line("# d_exner_dz_ref_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->d_exner_dz_ref_ic != nullptr), s);

  if (x->d_exner_dz_ref_ic)
    add_line(serialize_array(x->d_exner_dz_ref_ic), s);

  add_line("# d2dexdz2_fac1_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->d2dexdz2_fac1_mc != nullptr), s);

  if (x->d2dexdz2_fac1_mc)
    add_line(serialize_array(x->d2dexdz2_fac1_mc), s);

  add_line("# d2dexdz2_fac2_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->d2dexdz2_fac2_mc != nullptr), s);

  if (x->d2dexdz2_fac2_mc)
    add_line(serialize_array(x->d2dexdz2_fac2_mc), s);

  add_line("# pg_exdist", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_exdist != nullptr), s);

  if (x->pg_exdist)
    add_line(serialize_array(x->pg_exdist), s);

  add_line("# vertidx_gradp", s);

  add_line("# assoc", s);
  add_line(serialize(x->vertidx_gradp != nullptr), s);

  if (x->vertidx_gradp)
    add_line(serialize_array(x->vertidx_gradp), s);

  add_line("# pg_edgeidx", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_edgeidx != nullptr), s);

  if (x->pg_edgeidx)
    add_line(serialize_array(x->pg_edgeidx), s);

  add_line("# pg_edgeblk", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_edgeblk != nullptr), s);

  if (x->pg_edgeblk)
    add_line(serialize_array(x->pg_edgeblk), s);

  add_line("# pg_vertidx", s);

  add_line("# assoc", s);
  add_line(serialize(x->pg_vertidx != nullptr), s);

  if (x->pg_vertidx)
    add_line(serialize_array(x->pg_vertidx), s);

  add_line("# bdy_mflx_e_idx", s);

  add_line("# assoc", s);
  add_line(serialize(x->bdy_mflx_e_idx != nullptr), s);

  if (x->bdy_mflx_e_idx)
    add_line(serialize_array(x->bdy_mflx_e_idx), s);

  add_line("# bdy_mflx_e_blk", s);

  add_line("# assoc", s);
  add_line(serialize(x->bdy_mflx_e_blk != nullptr), s);

  if (x->bdy_mflx_e_blk)
    add_line(serialize_array(x->bdy_mflx_e_blk), s);

  add_line("# deepatmo_gradh_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_gradh_mc != nullptr), s);

  if (x->deepatmo_gradh_mc)
    add_line(serialize_array(x->deepatmo_gradh_mc), s);

  add_line("# deepatmo_invr_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_invr_mc != nullptr), s);

  if (x->deepatmo_invr_mc)
    add_line(serialize_array(x->deepatmo_invr_mc), s);

  add_line("# deepatmo_gradh_ifc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_gradh_ifc != nullptr), s);

  if (x->deepatmo_gradh_ifc)
    add_line(serialize_array(x->deepatmo_gradh_ifc), s);

  add_line("# deepatmo_invr_ifc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_invr_ifc != nullptr), s);

  if (x->deepatmo_invr_ifc)
    add_line(serialize_array(x->deepatmo_invr_ifc), s);

  add_line("# pg_listdim", s);
  add_line(serialize(x->pg_listdim), s);
  add_line("# bdy_mflx_e_dim", s);
  add_line(serialize(x->bdy_mflx_e_dim), s);
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_state *x) {
  std::stringstream s;
  add_line("# prog", s);

  add_line("# alloc", s);
  add_line(serialize(x->prog != nullptr), s);
  if (x->prog) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->prog);
      add_line("# rank", s);
      add_line(m.rank, s);
      add_line("# size", s);
      for (auto i : m.size)
        add_line(i, s);
      add_line("# lbound", s);
      for (auto i : m.lbound)
        add_line(i, s);
      add_line("# entries", s);
      for (int i = 0; i < m.volume(); ++i) {
        add_line(serialize(x->prog[i]), s);
      }
    }

  } // CONCLUDING IF
  add_line("# diag", s);
  add_line(serialize(x->diag), s);
  add_line("# ref", s);
  add_line(serialize(x->ref), s);
  add_line("# metrics", s);
  add_line(serialize(x->metrics), s);
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_prepare_adv *x) {
  std::stringstream s;
  add_line("# mass_flx_me", s);

  add_line("# assoc", s);
  add_line(serialize(x->mass_flx_me != nullptr), s);

  if (x->mass_flx_me)
    add_line(serialize_array(x->mass_flx_me), s);

  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

template <typename T> T *array_meta::read(std::istream &s) const {
  auto *buf = new T[volume()];
  if constexpr (std::is_pointer_v<T>) {
    auto *bufc = read<std::remove_pointer_t<T>>(s);
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

template <typename T> std::string serialize_array(T *arr) {
  const auto m = ARRAY_META_DICT_AT(static_cast<void *>(arr));
  std::stringstream s;
  add_line("# rank", s);
  add_line(m.rank, s);
  add_line("# size", s);
  for (auto i : m.size)
    add_line(i, s);
  add_line("# lbound", s);
  for (auto i : m.lbound)
    add_line(i, s);
  add_line("# entries", s);
  for (int i = 0; i < m.volume(); ++i)
    add_line(serialize(arr[i]), s);
  return s.str();
}

void deserialize_global_data(global_data_type *g, std::istream &s) {

  read_line(s, "# ldeepatmo");
  deserialize(g->ldeepatmo, s);

  read_line(s, "# l_limited_area");
  deserialize(g->l_limited_area, s);

  read_line(s, "# grf_intmethod_e");
  deserialize(g->grf_intmethod_e, s);

  {
    read_line(s, "# nflatlev");
    auto [m, arr] = read_array<int>(s);
    g->nflatlev = arr;
  }

  read_line(s, "# is_iau_active");
  deserialize(g->is_iau_active, s);

  read_line(s, "# iau_wgt_dyn");
  deserialize(g->iau_wgt_dyn, s);

  read_line(s, "# i_am_accel_node");
  deserialize(g->i_am_accel_node, s);

  read_line(s, "# itime_scheme");
  deserialize(g->itime_scheme, s);

  read_line(s, "# lextra_diffu");
  deserialize(g->lextra_diffu, s);

  read_line(s, "# rayleigh_type");
  deserialize(g->rayleigh_type, s);

  read_line(s, "# iadv_rhotheta");
  deserialize(g->iadv_rhotheta, s);

  read_line(s, "# igradp_method");
  deserialize(g->igradp_method, s);

  {
    read_line(s, "# kstart_dd3d");
    auto [m, arr] = read_array<int>(s);
    g->kstart_dd3d = arr;
  }

  read_line(s, "# nproma");
  deserialize(g->nproma, s);

  read_line(s, "# lvert_nest");
  deserialize(g->lvert_nest, s);

  read_line(s, "# timers_level");
  deserialize(g->timers_level, s);

  read_line(s, "# timer_solve_nh_veltend");
  deserialize(g->timer_solve_nh_veltend, s);

  read_line(s, "# timer_solve_nh_cellcomp");
  deserialize(g->timer_solve_nh_cellcomp, s);

  read_line(s, "# timer_solve_nh_vnupd");
  deserialize(g->timer_solve_nh_vnupd, s);

  read_line(s, "# timer_intp");
  deserialize(g->timer_intp, s);

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

std::string serialize_global_data(const global_data_type *g) {
  std::stringstream s;

  add_line(serialize(g->ldeepatmo), s);

  add_line(serialize(g->l_limited_area), s);

  add_line(serialize(g->grf_intmethod_e), s);

  add_line(serialize_array(g->nflatlev), s);

  add_line(serialize(g->is_iau_active), s);

  add_line(serialize(g->iau_wgt_dyn), s);

  add_line(serialize(g->i_am_accel_node), s);

  add_line(serialize(g->itime_scheme), s);

  add_line(serialize(g->lextra_diffu), s);

  add_line(serialize(g->rayleigh_type), s);

  add_line(serialize(g->iadv_rhotheta), s);

  add_line(serialize(g->igradp_method), s);

  add_line(serialize_array(g->kstart_dd3d), s);

  add_line(serialize(g->nproma), s);

  add_line(serialize(g->lvert_nest), s);

  add_line(serialize(g->timers_level), s);

  add_line(serialize(g->timer_solve_nh_veltend), s);

  add_line(serialize(g->timer_solve_nh_cellcomp), s);

  add_line(serialize(g->timer_solve_nh_vnupd), s);

  add_line(serialize(g->timer_intp), s);

  add_line(serialize_array(g->nrdmax), s);

  add_line(serialize_array(g->nflat_gradp), s);

  return s.str();
}

enum class SerializationType { INVALID, PLAIN, CONST_INJECTION, F90_MODULE };

std::string serialize_consistent_global_data(
    std::vector<const global_data_type *> &gs,
    SerializationType serialization_type = SerializationType::INVALID) {
  assert(serialization_type != SerializationType::INVALID);
  if (gs.empty())
    return "";

  std::map<std::string, std::set<std::string>> consistent;
  for (const auto *g : gs) {

    consistent["mo_dynamics_config.ldeepatmo"].insert(
        (g->ldeepatmo ? ".true." : ".false."));

    consistent["mo_grid_config.l_limited_area"].insert(
        (g->l_limited_area ? ".true." : ".false."));

    consistent["mo_gridref_config.grf_intmethod_e"].insert(
        serialize(g->grf_intmethod_e));

    consistent["mo_initicon_config.is_iau_active"].insert(
        (g->is_iau_active ? ".true." : ".false."));

    consistent["mo_initicon_config.iau_wgt_dyn"].insert(
        serialize(g->iau_wgt_dyn));

    consistent["mo_mpi.i_am_accel_node"].insert(
        (g->i_am_accel_node ? ".true." : ".false."));

    consistent["mo_nonhydrostatic_config.itime_scheme"].insert(
        serialize(g->itime_scheme));

    consistent["mo_nonhydrostatic_config.lextra_diffu"].insert(
        (g->lextra_diffu ? ".true." : ".false."));

    consistent["mo_nonhydrostatic_config.rayleigh_type"].insert(
        serialize(g->rayleigh_type));

    consistent["mo_nonhydrostatic_config.iadv_rhotheta"].insert(
        serialize(g->iadv_rhotheta));

    consistent["mo_nonhydrostatic_config.igradp_method"].insert(
        serialize(g->igradp_method));

    consistent["mo_parallel_config.nproma"].insert(serialize(g->nproma));

    consistent["mo_run_config.lvert_nest"].insert(
        (g->lvert_nest ? ".true." : ".false."));

    consistent["mo_run_config.timers_level"].insert(serialize(g->timers_level));

    consistent["mo_timer.timer_solve_nh_veltend"].insert(
        serialize(g->timer_solve_nh_veltend));

    consistent["mo_timer.timer_solve_nh_cellcomp"].insert(
        serialize(g->timer_solve_nh_cellcomp));

    consistent["mo_timer.timer_solve_nh_vnupd"].insert(
        serialize(g->timer_solve_nh_vnupd));

    consistent["mo_timer.timer_intp"].insert(serialize(g->timer_intp));
  }

  std::stringstream s;
  if (serialization_type == SerializationType::F90_MODULE) {
    s << R"(
module global_data_assertion
contains
subroutine assert_global_data()
)";
    for (const auto &[k, vs] : consistent) {
      std::vector<std::string_view> parts = split(k, '.');
      assert(parts.size() == 2);
      const auto mname = std::string_view(parts[0]);
      s << "use " << mname << std::endl;
    }
    s << R"(
implicit none
)";
  }
  for (const auto &[k, vs] : consistent) {
    if (vs.size() != 1)
      continue;
    const auto &v = *vs.begin();
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

} // namespace predictor_pre

#endif // __DACE_PREDICTOR_PRE_SERDE__
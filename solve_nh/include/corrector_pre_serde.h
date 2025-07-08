#ifndef __DACE_CORRECTOR_PRE_SERDE__
#define __DACE_CORRECTOR_PRE_SERDE__

#include <algorithm>
#include <cassert>
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

namespace corrector_pre {
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
std::pair<std::map<void *, array_meta> *, std::unique_lock<std::mutex>>
ARRAY_META_DICT();

struct array_meta {
  int rank = 0;
  std::vector<int> size, lbound;

  int volume() const {
    return std::reduce(size.begin(), size.end(), 1, std::multiplies<int>());
  }

  template <typename T> T *read(std::istream &s) const;
};
std::pair<std::map<void *, array_meta> *, std::unique_lock<std::mutex>>
ARRAY_META_DICT() {
  static auto *M = new std::map<void *, array_meta>();
  static std::mutex mu;
  std::unique_lock<std::mutex> lock(mu);
  return std::make_pair(M, std::move(lock));
}
template <typename T> const array_meta &ARRAY_META_DICT_AT(T *a) {
  if constexpr (std::is_pointer_v<T>) {
    return ARRAY_META_DICT_AT(*a);
  } else {
    auto [M, lock] = ARRAY_META_DICT();
    return M->at(a);
  }
}

void read_scalar(long double &x, std::istream &s) {
  if (s.eof())
    return;
  scroll_space(s);

  std::string line;
  assert(std::getline(s, line));
  assert(!line.empty());

  // Find the position to insert 'E' if needed (looking for exponent sign from
  // right)
  for (int i = line.length() - 1; i >= 0; --i) {
    char current_char = line[i];
    if (current_char == '+' || current_char == '-') {
      // Found a potential exponent sign. Check preceding character.
      if (i > 0 && (std::isdigit(line[i - 1]) || line[i - 1] == '.') &&
          !(line[i - 1] == 'E' || line[i - 1] == 'e' || line[i - 1] == 'D' ||
            line[i - 1] == 'd')) {
        line.insert(i, "E"); // Insert 'E' and break
        break;
      }
    } else if (current_char == 'E' || current_char == 'e' ||
               current_char == 'D' || current_char == 'd') {
      // Already standard scientific notation, no insertion needed.
      break; // Exit loop
    }
  }

  // Parse the (potentially modified) string
  std::istringstream iss(line);
  iss >> x;
  if (iss.fail())
    x = 0;
}

void read_scalar(float &x, std::istream &s) {
  long double xx;
  read_scalar(xx, s);
  x = static_cast<float>(xx);
}

void read_scalar(double &x, std::istream &s) {
  long double xx;
  read_scalar(xx, s);
  x = static_cast<double>(xx);
}

template <typename T> void read_scalar(T &x, std::istream &s) {
  if (s.eof())
    return;
  scroll_space(s);
  s >> x;
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
    x->__f2dace_SA_owner_mask_d_0_s_32 = m.size[0];
    x->__f2dace_SA_owner_mask_d_1_s_33 = m.size[1];
    x->__f2dace_SOA_owner_mask_d_0_s_32 = m.lbound[0];
    x->__f2dace_SOA_owner_mask_d_1_s_33 = m.lbound[1];
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
    x->__f2dace_SA_c_lin_e_d_0_s_54 = m.size[0];
    x->__f2dace_SA_c_lin_e_d_1_s_55 = m.size[1];
    x->__f2dace_SA_c_lin_e_d_2_s_56 = m.size[2];
    x->__f2dace_SOA_c_lin_e_d_0_s_54 = m.lbound[0];
    x->__f2dace_SOA_c_lin_e_d_1_s_55 = m.lbound[1];
    x->__f2dace_SOA_c_lin_e_d_2_s_56 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->c_lin_e = m.read<std::remove_pointer<decltype(x->c_lin_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# e_bln_c_s"}); // Should contain '# e_bln_c_s'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_e_bln_c_s_d_0_s_57 = m.size[0];
    x->__f2dace_SA_e_bln_c_s_d_1_s_58 = m.size[1];
    x->__f2dace_SA_e_bln_c_s_d_2_s_59 = m.size[2];
    x->__f2dace_SOA_e_bln_c_s_d_0_s_57 = m.lbound[0];
    x->__f2dace_SOA_e_bln_c_s_d_1_s_58 = m.lbound[1];
    x->__f2dace_SOA_e_bln_c_s_d_2_s_59 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->e_bln_c_s = m.read<std::remove_pointer<decltype(x->e_bln_c_s)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# cells_aw_verts"}); // Should contain '# cells_aw_verts'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cells_aw_verts_d_0_s_60 = m.size[0];
    x->__f2dace_SA_cells_aw_verts_d_1_s_61 = m.size[1];
    x->__f2dace_SA_cells_aw_verts_d_2_s_62 = m.size[2];
    x->__f2dace_SOA_cells_aw_verts_d_0_s_60 = m.lbound[0];
    x->__f2dace_SOA_cells_aw_verts_d_1_s_61 = m.lbound[1];
    x->__f2dace_SOA_cells_aw_verts_d_2_s_62 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cells_aw_verts =
        m.read<std::remove_pointer<decltype(x->cells_aw_verts)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# geofac_grdiv"}); // Should contain '# geofac_grdiv'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_geofac_grdiv_d_0_s_63 = m.size[0];
    x->__f2dace_SA_geofac_grdiv_d_1_s_64 = m.size[1];
    x->__f2dace_SA_geofac_grdiv_d_2_s_65 = m.size[2];
    x->__f2dace_SOA_geofac_grdiv_d_0_s_63 = m.lbound[0];
    x->__f2dace_SOA_geofac_grdiv_d_1_s_64 = m.lbound[1];
    x->__f2dace_SOA_geofac_grdiv_d_2_s_65 = m.lbound[2];
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
    x->__f2dace_SA_geofac_rot_d_0_s_66 = m.size[0];
    x->__f2dace_SA_geofac_rot_d_1_s_67 = m.size[1];
    x->__f2dace_SA_geofac_rot_d_2_s_68 = m.size[2];
    x->__f2dace_SOA_geofac_rot_d_0_s_66 = m.lbound[0];
    x->__f2dace_SOA_geofac_rot_d_1_s_67 = m.lbound[1];
    x->__f2dace_SOA_geofac_rot_d_2_s_68 = m.lbound[2];
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
    x->__f2dace_SA_geofac_n2s_d_0_s_69 = m.size[0];
    x->__f2dace_SA_geofac_n2s_d_1_s_70 = m.size[1];
    x->__f2dace_SA_geofac_n2s_d_2_s_71 = m.size[2];
    x->__f2dace_SOA_geofac_n2s_d_0_s_69 = m.lbound[0];
    x->__f2dace_SOA_geofac_n2s_d_1_s_70 = m.lbound[1];
    x->__f2dace_SOA_geofac_n2s_d_2_s_71 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->geofac_n2s =
        m.read<std::remove_pointer<decltype(x->geofac_n2s)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# nudgecoeff_e"}); // Should contain '# nudgecoeff_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_nudgecoeff_e_d_0_s_72 = m.size[0];
    x->__f2dace_SA_nudgecoeff_e_d_1_s_73 = m.size[1];
    x->__f2dace_SOA_nudgecoeff_e_d_0_s_72 = m.lbound[0];
    x->__f2dace_SOA_nudgecoeff_e_d_1_s_73 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->nudgecoeff_e =
        m.read<std::remove_pointer<decltype(x->nudgecoeff_e)>::type>(s);

  } // CONCLUDING IF
}

void deserialize(t_grid_cells *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# neighbor_idx"}); // Should contain '# neighbor_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_neighbor_idx_d_0_s_144 = m.size[0];
    x->__f2dace_SA_neighbor_idx_d_1_s_145 = m.size[1];
    x->__f2dace_SA_neighbor_idx_d_2_s_146 = m.size[2];
    x->__f2dace_SOA_neighbor_idx_d_0_s_144 = m.lbound[0];
    x->__f2dace_SOA_neighbor_idx_d_1_s_145 = m.lbound[1];
    x->__f2dace_SOA_neighbor_idx_d_2_s_146 = m.lbound[2];
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
    x->__f2dace_SA_neighbor_blk_d_0_s_147 = m.size[0];
    x->__f2dace_SA_neighbor_blk_d_1_s_148 = m.size[1];
    x->__f2dace_SA_neighbor_blk_d_2_s_149 = m.size[2];
    x->__f2dace_SOA_neighbor_blk_d_0_s_147 = m.lbound[0];
    x->__f2dace_SOA_neighbor_blk_d_1_s_148 = m.lbound[1];
    x->__f2dace_SOA_neighbor_blk_d_2_s_149 = m.lbound[2];
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
    x->__f2dace_SA_edge_idx_d_0_s_150 = m.size[0];
    x->__f2dace_SA_edge_idx_d_1_s_151 = m.size[1];
    x->__f2dace_SA_edge_idx_d_2_s_152 = m.size[2];
    x->__f2dace_SOA_edge_idx_d_0_s_150 = m.lbound[0];
    x->__f2dace_SOA_edge_idx_d_1_s_151 = m.lbound[1];
    x->__f2dace_SOA_edge_idx_d_2_s_152 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_idx = m.read<std::remove_pointer<decltype(x->edge_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_blk"}); // Should contain '# edge_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_blk_d_0_s_153 = m.size[0];
    x->__f2dace_SA_edge_blk_d_1_s_154 = m.size[1];
    x->__f2dace_SA_edge_blk_d_2_s_155 = m.size[2];
    x->__f2dace_SOA_edge_blk_d_0_s_153 = m.lbound[0];
    x->__f2dace_SOA_edge_blk_d_1_s_154 = m.lbound[1];
    x->__f2dace_SOA_edge_blk_d_2_s_155 = m.lbound[2];
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
    x->__f2dace_SA_area_d_0_s_156 = m.size.at(0);
    x->__f2dace_SA_area_d_1_s_157 = m.size.at(1);
    x->__f2dace_SOA_area_d_0_s_156 = m.lbound.at(0);
    x->__f2dace_SOA_area_d_1_s_157 = m.lbound.at(1);
    x->area = arr;
  }

  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_158 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_158 = m.lbound[0];
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
    x->__f2dace_SA_end_index_d_0_s_159 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_159 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_160 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_160 = m.lbound[0];
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
    x->__f2dace_SA_end_block_d_0_s_161 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_161 = m.lbound[0];
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
    x->__f2dace_SA_cell_idx_d_0_s_162 = m.size[0];
    x->__f2dace_SA_cell_idx_d_1_s_163 = m.size[1];
    x->__f2dace_SA_cell_idx_d_2_s_164 = m.size[2];
    x->__f2dace_SOA_cell_idx_d_0_s_162 = m.lbound[0];
    x->__f2dace_SOA_cell_idx_d_1_s_163 = m.lbound[1];
    x->__f2dace_SOA_cell_idx_d_2_s_164 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_idx = m.read<std::remove_pointer<decltype(x->cell_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# cell_blk"}); // Should contain '# cell_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cell_blk_d_0_s_165 = m.size[0];
    x->__f2dace_SA_cell_blk_d_1_s_166 = m.size[1];
    x->__f2dace_SA_cell_blk_d_2_s_167 = m.size[2];
    x->__f2dace_SOA_cell_blk_d_0_s_165 = m.lbound[0];
    x->__f2dace_SOA_cell_blk_d_1_s_166 = m.lbound[1];
    x->__f2dace_SOA_cell_blk_d_2_s_167 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_blk = m.read<std::remove_pointer<decltype(x->cell_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# vertex_idx"}); // Should contain '# vertex_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_vertex_idx_d_0_s_168 = m.size[0];
    x->__f2dace_SA_vertex_idx_d_1_s_169 = m.size[1];
    x->__f2dace_SA_vertex_idx_d_2_s_170 = m.size[2];
    x->__f2dace_SOA_vertex_idx_d_0_s_168 = m.lbound[0];
    x->__f2dace_SOA_vertex_idx_d_1_s_169 = m.lbound[1];
    x->__f2dace_SOA_vertex_idx_d_2_s_170 = m.lbound[2];
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
    x->__f2dace_SA_vertex_blk_d_0_s_171 = m.size[0];
    x->__f2dace_SA_vertex_blk_d_1_s_172 = m.size[1];
    x->__f2dace_SA_vertex_blk_d_2_s_173 = m.size[2];
    x->__f2dace_SOA_vertex_blk_d_0_s_171 = m.lbound[0];
    x->__f2dace_SOA_vertex_blk_d_1_s_172 = m.lbound[1];
    x->__f2dace_SOA_vertex_blk_d_2_s_173 = m.lbound[2];
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
    x->__f2dace_SA_tangent_orientation_d_0_s_174 = m.size[0];
    x->__f2dace_SA_tangent_orientation_d_1_s_175 = m.size[1];
    x->__f2dace_SOA_tangent_orientation_d_0_s_174 = m.lbound[0];
    x->__f2dace_SOA_tangent_orientation_d_1_s_175 = m.lbound[1];
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
    x->__f2dace_SA_quad_idx_d_0_s_176 = m.size[0];
    x->__f2dace_SA_quad_idx_d_1_s_177 = m.size[1];
    x->__f2dace_SA_quad_idx_d_2_s_178 = m.size[2];
    x->__f2dace_SOA_quad_idx_d_0_s_176 = m.lbound[0];
    x->__f2dace_SOA_quad_idx_d_1_s_177 = m.lbound[1];
    x->__f2dace_SOA_quad_idx_d_2_s_178 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->quad_idx = m.read<std::remove_pointer<decltype(x->quad_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# quad_blk"}); // Should contain '# quad_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_quad_blk_d_0_s_179 = m.size[0];
    x->__f2dace_SA_quad_blk_d_1_s_180 = m.size[1];
    x->__f2dace_SA_quad_blk_d_2_s_181 = m.size[2];
    x->__f2dace_SOA_quad_blk_d_0_s_179 = m.lbound[0];
    x->__f2dace_SOA_quad_blk_d_1_s_180 = m.lbound[1];
    x->__f2dace_SOA_quad_blk_d_2_s_181 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->quad_blk = m.read<std::remove_pointer<decltype(x->quad_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# inv_primal_edge_length"}); // Should contain '#
                                              // inv_primal_edge_length'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_inv_primal_edge_length_d_0_s_182 = m.size[0];
    x->__f2dace_SA_inv_primal_edge_length_d_1_s_183 = m.size[1];
    x->__f2dace_SOA_inv_primal_edge_length_d_0_s_182 = m.lbound[0];
    x->__f2dace_SOA_inv_primal_edge_length_d_1_s_183 = m.lbound[1];
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
    x->__f2dace_SA_inv_dual_edge_length_d_0_s_184 = m.size[0];
    x->__f2dace_SA_inv_dual_edge_length_d_1_s_185 = m.size[1];
    x->__f2dace_SOA_inv_dual_edge_length_d_0_s_184 = m.lbound[0];
    x->__f2dace_SOA_inv_dual_edge_length_d_1_s_185 = m.lbound[1];
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
    x->__f2dace_SA_area_edge_d_0_s_186 = m.size[0];
    x->__f2dace_SA_area_edge_d_1_s_187 = m.size[1];
    x->__f2dace_SOA_area_edge_d_0_s_186 = m.lbound[0];
    x->__f2dace_SOA_area_edge_d_1_s_187 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->area_edge = m.read<std::remove_pointer<decltype(x->area_edge)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# f_e"}); // Should contain '# f_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_f_e_d_0_s_188 = m.size[0];
    x->__f2dace_SA_f_e_d_1_s_189 = m.size[1];
    x->__f2dace_SOA_f_e_d_0_s_188 = m.lbound[0];
    x->__f2dace_SOA_f_e_d_1_s_189 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->f_e = m.read<std::remove_pointer<decltype(x->f_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# fn_e"}); // Should contain '# fn_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_fn_e_d_0_s_190 = m.size[0];
    x->__f2dace_SA_fn_e_d_1_s_191 = m.size[1];
    x->__f2dace_SOA_fn_e_d_0_s_190 = m.lbound[0];
    x->__f2dace_SOA_fn_e_d_1_s_191 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->fn_e = m.read<std::remove_pointer<decltype(x->fn_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# ft_e"}); // Should contain '# ft_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_ft_e_d_0_s_192 = m.size[0];
    x->__f2dace_SA_ft_e_d_1_s_193 = m.size[1];
    x->__f2dace_SOA_ft_e_d_0_s_192 = m.lbound[0];
    x->__f2dace_SOA_ft_e_d_1_s_193 = m.lbound[1];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->ft_e = m.read<std::remove_pointer<decltype(x->ft_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_194 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_194 = m.lbound[0];
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
    x->__f2dace_SA_end_index_d_0_s_195 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_195 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_196 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_196 = m.lbound[0];
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
    x->__f2dace_SA_end_block_d_0_s_197 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_197 = m.lbound[0];
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
    x->__f2dace_SA_cell_idx_d_0_s_198 = m.size[0];
    x->__f2dace_SA_cell_idx_d_1_s_199 = m.size[1];
    x->__f2dace_SA_cell_idx_d_2_s_200 = m.size[2];
    x->__f2dace_SOA_cell_idx_d_0_s_198 = m.lbound[0];
    x->__f2dace_SOA_cell_idx_d_1_s_199 = m.lbound[1];
    x->__f2dace_SOA_cell_idx_d_2_s_200 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_idx = m.read<std::remove_pointer<decltype(x->cell_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# cell_blk"}); // Should contain '# cell_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_cell_blk_d_0_s_201 = m.size[0];
    x->__f2dace_SA_cell_blk_d_1_s_202 = m.size[1];
    x->__f2dace_SA_cell_blk_d_2_s_203 = m.size[2];
    x->__f2dace_SOA_cell_blk_d_0_s_201 = m.lbound[0];
    x->__f2dace_SOA_cell_blk_d_1_s_202 = m.lbound[1];
    x->__f2dace_SOA_cell_blk_d_2_s_203 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->cell_blk = m.read<std::remove_pointer<decltype(x->cell_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_idx"}); // Should contain '# edge_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_idx_d_0_s_204 = m.size[0];
    x->__f2dace_SA_edge_idx_d_1_s_205 = m.size[1];
    x->__f2dace_SA_edge_idx_d_2_s_206 = m.size[2];
    x->__f2dace_SOA_edge_idx_d_0_s_204 = m.lbound[0];
    x->__f2dace_SOA_edge_idx_d_1_s_205 = m.lbound[1];
    x->__f2dace_SOA_edge_idx_d_2_s_206 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_idx = m.read<std::remove_pointer<decltype(x->edge_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_blk"}); // Should contain '# edge_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_blk_d_0_s_207 = m.size[0];
    x->__f2dace_SA_edge_blk_d_1_s_208 = m.size[1];
    x->__f2dace_SA_edge_blk_d_2_s_209 = m.size[2];
    x->__f2dace_SOA_edge_blk_d_0_s_207 = m.lbound[0];
    x->__f2dace_SOA_edge_blk_d_1_s_208 = m.lbound[1];
    x->__f2dace_SOA_edge_blk_d_2_s_209 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_blk = m.read<std::remove_pointer<decltype(x->edge_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_210 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_210 = m.lbound[0];
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
    x->__f2dace_SA_end_index_d_0_s_211 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_211 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_212 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_212 = m.lbound[0];
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
    x->__f2dace_SA_end_block_d_0_s_213 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_213 = m.lbound[0];
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
    x->__f2dace_SA_w_d_0_s_354 = m.size.at(0);
    x->__f2dace_SA_w_d_1_s_355 = m.size.at(1);
    x->__f2dace_SA_w_d_2_s_356 = m.size.at(2);
    x->__f2dace_SOA_w_d_0_s_354 = m.lbound.at(0);
    x->__f2dace_SOA_w_d_1_s_355 = m.lbound.at(1);
    x->__f2dace_SOA_w_d_2_s_356 = m.lbound.at(2);
    x->w = arr;
  }

  read_line(s, {"# vn"}); // Should contain '# vn'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vn)>::type>(s);
    x->__f2dace_SA_vn_d_0_s_357 = m.size.at(0);
    x->__f2dace_SA_vn_d_1_s_358 = m.size.at(1);
    x->__f2dace_SA_vn_d_2_s_359 = m.size.at(2);
    x->__f2dace_SOA_vn_d_0_s_357 = m.lbound.at(0);
    x->__f2dace_SOA_vn_d_1_s_358 = m.lbound.at(1);
    x->__f2dace_SOA_vn_d_2_s_359 = m.lbound.at(2);
    x->vn = arr;
  }

  read_line(s, {"# rho"}); // Should contain '# rho'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho)>::type>(s);
    x->__f2dace_SA_rho_d_0_s_360 = m.size.at(0);
    x->__f2dace_SA_rho_d_1_s_361 = m.size.at(1);
    x->__f2dace_SA_rho_d_2_s_362 = m.size.at(2);
    x->__f2dace_SOA_rho_d_0_s_360 = m.lbound.at(0);
    x->__f2dace_SOA_rho_d_1_s_361 = m.lbound.at(1);
    x->__f2dace_SOA_rho_d_2_s_362 = m.lbound.at(2);
    x->rho = arr;
  }

  read_line(s, {"# theta_v"}); // Should contain '# theta_v'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v)>::type>(s);
    x->__f2dace_SA_theta_v_d_0_s_363 = m.size.at(0);
    x->__f2dace_SA_theta_v_d_1_s_364 = m.size.at(1);
    x->__f2dace_SA_theta_v_d_2_s_365 = m.size.at(2);
    x->__f2dace_SOA_theta_v_d_0_s_363 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_d_1_s_364 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_d_2_s_365 = m.lbound.at(2);
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
    x->__f2dace_SA_exner_pr_d_0_s_366 = m.size.at(0);
    x->__f2dace_SA_exner_pr_d_1_s_367 = m.size.at(1);
    x->__f2dace_SA_exner_pr_d_2_s_368 = m.size.at(2);
    x->__f2dace_SOA_exner_pr_d_0_s_366 = m.lbound.at(0);
    x->__f2dace_SOA_exner_pr_d_1_s_367 = m.lbound.at(1);
    x->__f2dace_SOA_exner_pr_d_2_s_368 = m.lbound.at(2);
    x->exner_pr = arr;
  }

  read_line(s, {"# rho_ic"}); // Should contain '# rho_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ic)>::type>(s);
    x->__f2dace_SA_rho_ic_d_0_s_369 = m.size.at(0);
    x->__f2dace_SA_rho_ic_d_1_s_370 = m.size.at(1);
    x->__f2dace_SA_rho_ic_d_2_s_371 = m.size.at(2);
    x->__f2dace_SOA_rho_ic_d_0_s_369 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ic_d_1_s_370 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ic_d_2_s_371 = m.lbound.at(2);
    x->rho_ic = arr;
  }

  read_line(s, {"# theta_v_ic"}); // Should contain '# theta_v_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v_ic)>::type>(s);
    x->__f2dace_SA_theta_v_ic_d_0_s_372 = m.size.at(0);
    x->__f2dace_SA_theta_v_ic_d_1_s_373 = m.size.at(1);
    x->__f2dace_SA_theta_v_ic_d_2_s_374 = m.size.at(2);
    x->__f2dace_SOA_theta_v_ic_d_0_s_372 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_ic_d_1_s_373 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_ic_d_2_s_374 = m.lbound.at(2);
    x->theta_v_ic = arr;
  }

  read_line(s, {"# vn_incr"}); // Should contain '# vn_incr'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_incr)>::type>(s);
    x->__f2dace_SA_vn_incr_d_0_s_375 = m.size.at(0);
    x->__f2dace_SA_vn_incr_d_1_s_376 = m.size.at(1);
    x->__f2dace_SA_vn_incr_d_2_s_377 = m.size.at(2);
    x->__f2dace_SOA_vn_incr_d_0_s_375 = m.lbound.at(0);
    x->__f2dace_SOA_vn_incr_d_1_s_376 = m.lbound.at(1);
    x->__f2dace_SOA_vn_incr_d_2_s_377 = m.lbound.at(2);
    x->vn_incr = arr;
  }

  read_line(s, {"# vt"}); // Should contain '# vt'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vt)>::type>(s);
    x->__f2dace_SA_vt_d_0_s_378 = m.size.at(0);
    x->__f2dace_SA_vt_d_1_s_379 = m.size.at(1);
    x->__f2dace_SA_vt_d_2_s_380 = m.size.at(2);
    x->__f2dace_SOA_vt_d_0_s_378 = m.lbound.at(0);
    x->__f2dace_SOA_vt_d_1_s_379 = m.lbound.at(1);
    x->__f2dace_SOA_vt_d_2_s_380 = m.lbound.at(2);
    x->vt = arr;
  }

  read_line(s, {"# ddt_vn_phy"}); // Should contain '# ddt_vn_phy'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_phy)>::type>(s);
    x->__f2dace_SA_ddt_vn_phy_d_0_s_381 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_phy_d_1_s_382 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_phy_d_2_s_383 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_phy_d_0_s_381 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_phy_d_1_s_382 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_phy_d_2_s_383 = m.lbound.at(2);
    x->ddt_vn_phy = arr;
  }

  read_line(s, {"# vn_ie"}); // Should contain '# vn_ie'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ie)>::type>(s);
    x->__f2dace_SA_vn_ie_d_0_s_384 = m.size.at(0);
    x->__f2dace_SA_vn_ie_d_1_s_385 = m.size.at(1);
    x->__f2dace_SA_vn_ie_d_2_s_386 = m.size.at(2);
    x->__f2dace_SOA_vn_ie_d_0_s_384 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ie_d_1_s_385 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ie_d_2_s_386 = m.lbound.at(2);
    x->vn_ie = arr;
  }

  read_line(s, {"# w_concorr_c"}); // Should contain '# w_concorr_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->w_concorr_c)>::type>(s);
    x->__f2dace_SA_w_concorr_c_d_0_s_387 = m.size.at(0);
    x->__f2dace_SA_w_concorr_c_d_1_s_388 = m.size.at(1);
    x->__f2dace_SA_w_concorr_c_d_2_s_389 = m.size.at(2);
    x->__f2dace_SOA_w_concorr_c_d_0_s_387 = m.lbound.at(0);
    x->__f2dace_SOA_w_concorr_c_d_1_s_388 = m.lbound.at(1);
    x->__f2dace_SOA_w_concorr_c_d_2_s_389 = m.lbound.at(2);
    x->w_concorr_c = arr;
  }

  read_line(s, {"# ddt_vn_apc_pc"}); // Should contain '# ddt_vn_apc_pc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_apc_pc)>::type>(s);
    x->__f2dace_SA_ddt_vn_apc_pc_d_0_s_390 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_apc_pc_d_1_s_391 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_apc_pc_d_2_s_392 = m.size.at(2);
    x->__f2dace_SA_ddt_vn_apc_pc_d_3_s_393 = m.size.at(3);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_0_s_390 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_1_s_391 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_2_s_392 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_vn_apc_pc_d_3_s_393 = m.lbound.at(3);
    x->ddt_vn_apc_pc = arr;
  }

  read_line(s, {"# ddt_vn_cor_pc"}); // Should contain '# ddt_vn_cor_pc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_cor_pc)>::type>(s);
    x->__f2dace_SA_ddt_vn_cor_pc_d_0_s_394 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_cor_pc_d_1_s_395 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_cor_pc_d_2_s_396 = m.size.at(2);
    x->__f2dace_SA_ddt_vn_cor_pc_d_3_s_397 = m.size.at(3);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_0_s_394 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_1_s_395 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_2_s_396 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_vn_cor_pc_d_3_s_397 = m.lbound.at(3);
    x->ddt_vn_cor_pc = arr;
  }

  read_line(s, {"# ddt_w_adv_pc"}); // Should contain '# ddt_w_adv_pc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_w_adv_pc)>::type>(s);
    x->__f2dace_SA_ddt_w_adv_pc_d_0_s_398 = m.size.at(0);
    x->__f2dace_SA_ddt_w_adv_pc_d_1_s_399 = m.size.at(1);
    x->__f2dace_SA_ddt_w_adv_pc_d_2_s_400 = m.size.at(2);
    x->__f2dace_SA_ddt_w_adv_pc_d_3_s_401 = m.size.at(3);
    x->__f2dace_SOA_ddt_w_adv_pc_d_0_s_398 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_w_adv_pc_d_1_s_399 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_w_adv_pc_d_2_s_400 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_w_adv_pc_d_3_s_401 = m.lbound.at(3);
    x->ddt_w_adv_pc = arr;
  }

  read_line(s, {"# ddt_vn_dyn"}); // Should contain '# ddt_vn_dyn'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_dyn)>::type>(s);
    x->__f2dace_SA_ddt_vn_dyn_d_0_s_402 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_dyn_d_1_s_403 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_dyn_d_2_s_404 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_dyn_d_0_s_402 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_dyn_d_1_s_403 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_dyn_d_2_s_404 = m.lbound.at(2);
    x->ddt_vn_dyn = arr;
  }

  read_line(s, {"# ddt_vn_dmp"}); // Should contain '# ddt_vn_dmp'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_dmp)>::type>(s);
    x->__f2dace_SA_ddt_vn_dmp_d_0_s_405 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_dmp_d_1_s_406 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_dmp_d_2_s_407 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_dmp_d_0_s_405 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_dmp_d_1_s_406 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_dmp_d_2_s_407 = m.lbound.at(2);
    x->ddt_vn_dmp = arr;
  }

  read_line(s, {"# ddt_vn_adv"}); // Should contain '# ddt_vn_adv'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_adv)>::type>(s);
    x->__f2dace_SA_ddt_vn_adv_d_0_s_408 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_adv_d_1_s_409 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_adv_d_2_s_410 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_adv_d_0_s_408 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_adv_d_1_s_409 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_adv_d_2_s_410 = m.lbound.at(2);
    x->ddt_vn_adv = arr;
  }

  read_line(s, {"# ddt_vn_cor"}); // Should contain '# ddt_vn_cor'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_cor)>::type>(s);
    x->__f2dace_SA_ddt_vn_cor_d_0_s_411 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_cor_d_1_s_412 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_cor_d_2_s_413 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_cor_d_0_s_411 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_cor_d_1_s_412 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_cor_d_2_s_413 = m.lbound.at(2);
    x->ddt_vn_cor = arr;
  }

  read_line(s, {"# ddt_vn_pgr"}); // Should contain '# ddt_vn_pgr'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_pgr)>::type>(s);
    x->__f2dace_SA_ddt_vn_pgr_d_0_s_414 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_pgr_d_1_s_415 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_pgr_d_2_s_416 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_pgr_d_0_s_414 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_pgr_d_1_s_415 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_pgr_d_2_s_416 = m.lbound.at(2);
    x->ddt_vn_pgr = arr;
  }

  read_line(s, {"# ddt_vn_phd"}); // Should contain '# ddt_vn_phd'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_phd)>::type>(s);
    x->__f2dace_SA_ddt_vn_phd_d_0_s_417 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_phd_d_1_s_418 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_phd_d_2_s_419 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_phd_d_0_s_417 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_phd_d_1_s_418 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_phd_d_2_s_419 = m.lbound.at(2);
    x->ddt_vn_phd = arr;
  }

  read_line(s, {"# ddt_vn_iau"}); // Should contain '# ddt_vn_iau'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_iau)>::type>(s);
    x->__f2dace_SA_ddt_vn_iau_d_0_s_420 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_iau_d_1_s_421 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_iau_d_2_s_422 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_iau_d_0_s_420 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_iau_d_1_s_421 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_iau_d_2_s_422 = m.lbound.at(2);
    x->ddt_vn_iau = arr;
  }

  read_line(s, {"# ddt_vn_ray"}); // Should contain '# ddt_vn_ray'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_vn_ray)>::type>(s);
    x->__f2dace_SA_ddt_vn_ray_d_0_s_423 = m.size.at(0);
    x->__f2dace_SA_ddt_vn_ray_d_1_s_424 = m.size.at(1);
    x->__f2dace_SA_ddt_vn_ray_d_2_s_425 = m.size.at(2);
    x->__f2dace_SOA_ddt_vn_ray_d_0_s_423 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_vn_ray_d_1_s_424 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_vn_ray_d_2_s_425 = m.lbound.at(2);
    x->ddt_vn_ray = arr;
  }

  read_line(s, {"# ddt_vn_dyn_is_associated"}); // Should contain '#
                                                // ddt_vn_dyn_is_associated'

  deserialize(&(x->ddt_vn_dyn_is_associated), s);

  read_line(s, {"# ddt_vn_dmp_is_associated"}); // Should contain '#
                                                // ddt_vn_dmp_is_associated'

  deserialize(&(x->ddt_vn_dmp_is_associated), s);

  read_line(s, {"# ddt_vn_adv_is_associated"}); // Should contain '#
                                                // ddt_vn_adv_is_associated'

  deserialize(&(x->ddt_vn_adv_is_associated), s);

  read_line(s, {"# ddt_vn_cor_is_associated"}); // Should contain '#
                                                // ddt_vn_cor_is_associated'

  deserialize(&(x->ddt_vn_cor_is_associated), s);

  read_line(s, {"# ddt_vn_pgr_is_associated"}); // Should contain '#
                                                // ddt_vn_pgr_is_associated'

  deserialize(&(x->ddt_vn_pgr_is_associated), s);

  read_line(s, {"# ddt_vn_phd_is_associated"}); // Should contain '#
                                                // ddt_vn_phd_is_associated'

  deserialize(&(x->ddt_vn_phd_is_associated), s);

  read_line(s, {"# ddt_vn_iau_is_associated"}); // Should contain '#
                                                // ddt_vn_iau_is_associated'

  deserialize(&(x->ddt_vn_iau_is_associated), s);

  read_line(s, {"# ddt_vn_ray_is_associated"}); // Should contain '#
                                                // ddt_vn_ray_is_associated'

  deserialize(&(x->ddt_vn_ray_is_associated), s);

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
    x->__f2dace_SA_vn_ref_d_0_s_426 = m.size.at(0);
    x->__f2dace_SA_vn_ref_d_1_s_427 = m.size.at(1);
    x->__f2dace_SA_vn_ref_d_2_s_428 = m.size.at(2);
    x->__f2dace_SOA_vn_ref_d_0_s_426 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ref_d_1_s_427 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ref_d_2_s_428 = m.lbound.at(2);
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
    x->__f2dace_SA_rayleigh_vn_d_0_s_429 = m.size.at(0);
    x->__f2dace_SOA_rayleigh_vn_d_0_s_429 = m.lbound.at(0);
    x->rayleigh_vn = arr;
  }

  read_line(s, {"# scalfac_dd3d"}); // Should contain '# scalfac_dd3d'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->scalfac_dd3d)>::type>(s);
    x->__f2dace_SA_scalfac_dd3d_d_0_s_430 = m.size.at(0);
    x->__f2dace_SOA_scalfac_dd3d_d_0_s_430 = m.lbound.at(0);
    x->scalfac_dd3d = arr;
  }

  read_line(s, {"# hmask_dd3d"}); // Should contain '# hmask_dd3d'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->hmask_dd3d)>::type>(s);
    x->__f2dace_SA_hmask_dd3d_d_0_s_431 = m.size.at(0);
    x->__f2dace_SA_hmask_dd3d_d_1_s_432 = m.size.at(1);
    x->__f2dace_SOA_hmask_dd3d_d_0_s_431 = m.lbound.at(0);
    x->__f2dace_SOA_hmask_dd3d_d_1_s_432 = m.lbound.at(1);
    x->hmask_dd3d = arr;
  }

  read_line(s, {"# vwind_expl_wgt"}); // Should contain '# vwind_expl_wgt'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vwind_expl_wgt)>::type>(s);
    x->__f2dace_SA_vwind_expl_wgt_d_0_s_433 = m.size.at(0);
    x->__f2dace_SA_vwind_expl_wgt_d_1_s_434 = m.size.at(1);
    x->__f2dace_SOA_vwind_expl_wgt_d_0_s_433 = m.lbound.at(0);
    x->__f2dace_SOA_vwind_expl_wgt_d_1_s_434 = m.lbound.at(1);
    x->vwind_expl_wgt = arr;
  }

  read_line(s, {"# ddqz_z_full_e"}); // Should contain '# ddqz_z_full_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_full_e)>::type>(s);
    x->__f2dace_SA_ddqz_z_full_e_d_0_s_435 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_full_e_d_1_s_436 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_full_e_d_2_s_437 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_full_e_d_0_s_435 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_full_e_d_1_s_436 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_full_e_d_2_s_437 = m.lbound.at(2);
    x->ddqz_z_full_e = arr;
  }

  read_line(s, {"# ddqz_z_half"}); // Should contain '# ddqz_z_half'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_half)>::type>(s);
    x->__f2dace_SA_ddqz_z_half_d_0_s_438 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_half_d_1_s_439 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_half_d_2_s_440 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_half_d_0_s_438 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_half_d_1_s_439 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_half_d_2_s_440 = m.lbound.at(2);
    x->ddqz_z_half = arr;
  }

  read_line(s, {"# wgtfac_c"}); // Should contain '# wgtfac_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfac_c)>::type>(s);
    x->__f2dace_SA_wgtfac_c_d_0_s_441 = m.size.at(0);
    x->__f2dace_SA_wgtfac_c_d_1_s_442 = m.size.at(1);
    x->__f2dace_SA_wgtfac_c_d_2_s_443 = m.size.at(2);
    x->__f2dace_SOA_wgtfac_c_d_0_s_441 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfac_c_d_1_s_442 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfac_c_d_2_s_443 = m.lbound.at(2);
    x->wgtfac_c = arr;
  }

  read_line(s, {"# coeff_gradekin"}); // Should contain '# coeff_gradekin'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff_gradekin)>::type>(s);
    x->__f2dace_SA_coeff_gradekin_d_0_s_444 = m.size.at(0);
    x->__f2dace_SA_coeff_gradekin_d_1_s_445 = m.size.at(1);
    x->__f2dace_SA_coeff_gradekin_d_2_s_446 = m.size.at(2);
    x->__f2dace_SOA_coeff_gradekin_d_0_s_444 = m.lbound.at(0);
    x->__f2dace_SOA_coeff_gradekin_d_1_s_445 = m.lbound.at(1);
    x->__f2dace_SOA_coeff_gradekin_d_2_s_446 = m.lbound.at(2);
    x->coeff_gradekin = arr;
  }

  read_line(s, {"# coeff1_dwdz"}); // Should contain '# coeff1_dwdz'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff1_dwdz)>::type>(s);
    x->__f2dace_SA_coeff1_dwdz_d_0_s_447 = m.size.at(0);
    x->__f2dace_SA_coeff1_dwdz_d_1_s_448 = m.size.at(1);
    x->__f2dace_SA_coeff1_dwdz_d_2_s_449 = m.size.at(2);
    x->__f2dace_SOA_coeff1_dwdz_d_0_s_447 = m.lbound.at(0);
    x->__f2dace_SOA_coeff1_dwdz_d_1_s_448 = m.lbound.at(1);
    x->__f2dace_SOA_coeff1_dwdz_d_2_s_449 = m.lbound.at(2);
    x->coeff1_dwdz = arr;
  }

  read_line(s, {"# coeff2_dwdz"}); // Should contain '# coeff2_dwdz'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->coeff2_dwdz)>::type>(s);
    x->__f2dace_SA_coeff2_dwdz_d_0_s_450 = m.size.at(0);
    x->__f2dace_SA_coeff2_dwdz_d_1_s_451 = m.size.at(1);
    x->__f2dace_SA_coeff2_dwdz_d_2_s_452 = m.size.at(2);
    x->__f2dace_SOA_coeff2_dwdz_d_0_s_450 = m.lbound.at(0);
    x->__f2dace_SOA_coeff2_dwdz_d_1_s_451 = m.lbound.at(1);
    x->__f2dace_SOA_coeff2_dwdz_d_2_s_452 = m.lbound.at(2);
    x->coeff2_dwdz = arr;
  }

  read_line(s, {"# theta_ref_mc"}); // Should contain '# theta_ref_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_ref_mc)>::type>(s);
    x->__f2dace_SA_theta_ref_mc_d_0_s_453 = m.size.at(0);
    x->__f2dace_SA_theta_ref_mc_d_1_s_454 = m.size.at(1);
    x->__f2dace_SA_theta_ref_mc_d_2_s_455 = m.size.at(2);
    x->__f2dace_SOA_theta_ref_mc_d_0_s_453 = m.lbound.at(0);
    x->__f2dace_SOA_theta_ref_mc_d_1_s_454 = m.lbound.at(1);
    x->__f2dace_SOA_theta_ref_mc_d_2_s_455 = m.lbound.at(2);
    x->theta_ref_mc = arr;
  }

  read_line(s, {"# d_exner_dz_ref_ic"}); // Should contain '# d_exner_dz_ref_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->d_exner_dz_ref_ic)>::type>(
            s);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_0_s_456 = m.size.at(0);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_1_s_457 = m.size.at(1);
    x->__f2dace_SA_d_exner_dz_ref_ic_d_2_s_458 = m.size.at(2);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_0_s_456 = m.lbound.at(0);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_1_s_457 = m.lbound.at(1);
    x->__f2dace_SOA_d_exner_dz_ref_ic_d_2_s_458 = m.lbound.at(2);
    x->d_exner_dz_ref_ic = arr;
  }

  read_line(s, {"# deepatmo_gradh_mc"}); // Should contain '# deepatmo_gradh_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_gradh_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_gradh_mc_d_0_s_459 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_gradh_mc_d_0_s_459 = m.lbound.at(0);
    x->deepatmo_gradh_mc = arr;
  }

  read_line(s, {"# deepatmo_invr_mc"}); // Should contain '# deepatmo_invr_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_invr_mc_d_0_s_460 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_invr_mc_d_0_s_460 = m.lbound.at(0);
    x->deepatmo_invr_mc = arr;
  }

  read_line(s,
            {"# deepatmo_gradh_ifc"}); // Should contain '# deepatmo_gradh_ifc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<
        std::remove_pointer<decltype(x->deepatmo_gradh_ifc)>::type>(s);
    x->__f2dace_SA_deepatmo_gradh_ifc_d_0_s_461 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_gradh_ifc_d_0_s_461 = m.lbound.at(0);
    x->deepatmo_gradh_ifc = arr;
  }

  read_line(s, {"# deepatmo_invr_ifc"}); // Should contain '# deepatmo_invr_ifc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_invr_ifc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_invr_ifc_d_0_s_462 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_invr_ifc_d_0_s_462 = m.lbound.at(0);
    x->deepatmo_invr_ifc = arr;
  }
}

void deserialize(t_nh_state *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# prog"}); // Should contain '# prog'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_prog_d_0_s_463 = m.size[0];
    x->__f2dace_SOA_prog_d_0_s_463 = m.lbound[0];
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
  add_line("# nudgecoeff_e", s);

  add_line("# alloc", s);
  add_line(serialize(x->nudgecoeff_e != nullptr), s);
  if (x->nudgecoeff_e) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->nudgecoeff_e);
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
        add_line(serialize(x->nudgecoeff_e[i]), s);
      }
    }

  } // CONCLUDING IF
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

  add_line("# ddt_vn_dmp", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_dmp != nullptr), s);

  if (x->ddt_vn_dmp)
    add_line(serialize_array(x->ddt_vn_dmp), s);

  add_line("# ddt_vn_adv", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_adv != nullptr), s);

  if (x->ddt_vn_adv)
    add_line(serialize_array(x->ddt_vn_adv), s);

  add_line("# ddt_vn_cor", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_cor != nullptr), s);

  if (x->ddt_vn_cor)
    add_line(serialize_array(x->ddt_vn_cor), s);

  add_line("# ddt_vn_pgr", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_pgr != nullptr), s);

  if (x->ddt_vn_pgr)
    add_line(serialize_array(x->ddt_vn_pgr), s);

  add_line("# ddt_vn_phd", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_phd != nullptr), s);

  if (x->ddt_vn_phd)
    add_line(serialize_array(x->ddt_vn_phd), s);

  add_line("# ddt_vn_iau", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_iau != nullptr), s);

  if (x->ddt_vn_iau)
    add_line(serialize_array(x->ddt_vn_iau), s);

  add_line("# ddt_vn_ray", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_vn_ray != nullptr), s);

  if (x->ddt_vn_ray)
    add_line(serialize_array(x->ddt_vn_ray), s);

  add_line("# ddt_vn_dyn_is_associated", s);
  add_line(serialize(x->ddt_vn_dyn_is_associated), s);
  add_line("# ddt_vn_dmp_is_associated", s);
  add_line(serialize(x->ddt_vn_dmp_is_associated), s);
  add_line("# ddt_vn_adv_is_associated", s);
  add_line(serialize(x->ddt_vn_adv_is_associated), s);
  add_line("# ddt_vn_cor_is_associated", s);
  add_line(serialize(x->ddt_vn_cor_is_associated), s);
  add_line("# ddt_vn_pgr_is_associated", s);
  add_line(serialize(x->ddt_vn_pgr_is_associated), s);
  add_line("# ddt_vn_phd_is_associated", s);
  add_line(serialize(x->ddt_vn_phd_is_associated), s);
  add_line("# ddt_vn_iau_is_associated", s);
  add_line(serialize(x->ddt_vn_iau_is_associated), s);
  add_line("# ddt_vn_ray_is_associated", s);
  add_line(serialize(x->ddt_vn_ray_is_associated), s);
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

  add_line("# scalfac_dd3d", s);

  add_line("# assoc", s);
  add_line(serialize(x->scalfac_dd3d != nullptr), s);

  if (x->scalfac_dd3d)
    add_line(serialize_array(x->scalfac_dd3d), s);

  add_line("# hmask_dd3d", s);

  add_line("# assoc", s);
  add_line(serialize(x->hmask_dd3d != nullptr), s);

  if (x->hmask_dd3d)
    add_line(serialize_array(x->hmask_dd3d), s);

  add_line("# vwind_expl_wgt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vwind_expl_wgt != nullptr), s);

  if (x->vwind_expl_wgt)
    add_line(serialize_array(x->vwind_expl_wgt), s);

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

  add_line("# wgtfac_c", s);

  add_line("# assoc", s);
  add_line(serialize(x->wgtfac_c != nullptr), s);

  if (x->wgtfac_c)
    add_line(serialize_array(x->wgtfac_c), s);

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

  add_line("# theta_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_ref_mc != nullptr), s);

  if (x->theta_ref_mc)
    add_line(serialize_array(x->theta_ref_mc), s);

  add_line("# d_exner_dz_ref_ic", s);

  add_line("# assoc", s);
  add_line(serialize(x->d_exner_dz_ref_ic != nullptr), s);

  if (x->d_exner_dz_ref_ic)
    add_line(serialize_array(x->d_exner_dz_ref_ic), s);

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
  }
  auto [M, lock] = ARRAY_META_DICT();
  (*M)[buf] = *this;
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

  read_line(s, "# divdamp_fac");
  deserialize(g->divdamp_fac, s);

  read_line(s, "# divdamp_fac_o2");
  deserialize(g->divdamp_fac_o2, s);

  read_line(s, "# divdamp_order");
  deserialize(g->divdamp_order, s);

  read_line(s, "# divdamp_type");
  deserialize(g->divdamp_type, s);

  read_line(s, "# rayleigh_type");
  deserialize(g->rayleigh_type, s);

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
}

std::string serialize_global_data(const global_data_type *g) {
  std::stringstream s;

  add_line(serialize(g->ldeepatmo), s);

  add_line(serialize(g->l_limited_area), s);

  add_line(serialize_array(g->nflatlev), s);

  add_line(serialize(g->is_iau_active), s);

  add_line(serialize(g->iau_wgt_dyn), s);

  add_line(serialize(g->i_am_accel_node), s);

  add_line(serialize(g->itime_scheme), s);

  add_line(serialize(g->lextra_diffu), s);

  add_line(serialize(g->divdamp_fac), s);

  add_line(serialize(g->divdamp_fac_o2), s);

  add_line(serialize(g->divdamp_order), s);

  add_line(serialize(g->divdamp_type), s);

  add_line(serialize(g->rayleigh_type), s);

  add_line(serialize_array(g->kstart_dd3d), s);

  add_line(serialize(g->nproma), s);

  add_line(serialize(g->lvert_nest), s);

  add_line(serialize(g->timers_level), s);

  add_line(serialize(g->timer_solve_nh_veltend), s);

  add_line(serialize(g->timer_solve_nh_cellcomp), s);

  add_line(serialize(g->timer_solve_nh_vnupd), s);

  add_line(serialize(g->timer_intp), s);

  add_line(serialize_array(g->nrdmax), s);

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

    consistent["mo_nonhydrostatic_config.divdamp_fac"].insert(
        serialize(g->divdamp_fac));

    consistent["mo_nonhydrostatic_config.divdamp_fac_o2"].insert(
        serialize(g->divdamp_fac_o2));

    consistent["mo_nonhydrostatic_config.divdamp_order"].insert(
        serialize(g->divdamp_order));

    consistent["mo_nonhydrostatic_config.divdamp_type"].insert(
        serialize(g->divdamp_type));

    consistent["mo_nonhydrostatic_config.rayleigh_type"].insert(
        serialize(g->rayleigh_type));

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

} // namespace corrector_pre

#endif // __DACE_CORRECTOR_PRE_SERDE__
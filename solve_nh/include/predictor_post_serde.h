#ifndef __DACE_PREDICTOR_POST_SERDE__
#define __DACE_PREDICTOR_POST_SERDE__

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

namespace predictor_post {
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

void deserialize(t_int_state *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# e_bln_c_s"}); // Should contain '# e_bln_c_s'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_e_bln_c_s_d_0_s_15 = m.size[0];
    x->__f2dace_SA_e_bln_c_s_d_1_s_16 = m.size[1];
    x->__f2dace_SA_e_bln_c_s_d_2_s_17 = m.size[2];
    x->__f2dace_SOA_e_bln_c_s_d_0_s_15 = m.lbound[0];
    x->__f2dace_SOA_e_bln_c_s_d_1_s_16 = m.lbound[1];
    x->__f2dace_SOA_e_bln_c_s_d_2_s_17 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->e_bln_c_s = m.read<std::remove_pointer<decltype(x->e_bln_c_s)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# e_flx_avg"}); // Should contain '# e_flx_avg'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_e_flx_avg_d_0_s_18 = m.size[0];
    x->__f2dace_SA_e_flx_avg_d_1_s_19 = m.size[1];
    x->__f2dace_SA_e_flx_avg_d_2_s_20 = m.size[2];
    x->__f2dace_SOA_e_flx_avg_d_0_s_18 = m.lbound[0];
    x->__f2dace_SOA_e_flx_avg_d_1_s_19 = m.lbound[1];
    x->__f2dace_SOA_e_flx_avg_d_2_s_20 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->e_flx_avg = m.read<std::remove_pointer<decltype(x->e_flx_avg)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# rbf_vec_coeff_e"}); // Should contain '# rbf_vec_coeff_e'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_rbf_vec_coeff_e_d_0_s_21 = m.size[0];
    x->__f2dace_SA_rbf_vec_coeff_e_d_1_s_22 = m.size[1];
    x->__f2dace_SA_rbf_vec_coeff_e_d_2_s_23 = m.size[2];
    x->__f2dace_SOA_rbf_vec_coeff_e_d_0_s_21 = m.lbound[0];
    x->__f2dace_SOA_rbf_vec_coeff_e_d_1_s_22 = m.lbound[1];
    x->__f2dace_SOA_rbf_vec_coeff_e_d_2_s_23 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->rbf_vec_coeff_e =
        m.read<std::remove_pointer<decltype(x->rbf_vec_coeff_e)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# geofac_div"}); // Should contain '# geofac_div'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_geofac_div_d_0_s_24 = m.size[0];
    x->__f2dace_SA_geofac_div_d_1_s_25 = m.size[1];
    x->__f2dace_SA_geofac_div_d_2_s_26 = m.size[2];
    x->__f2dace_SOA_geofac_div_d_0_s_24 = m.lbound[0];
    x->__f2dace_SOA_geofac_div_d_1_s_25 = m.lbound[1];
    x->__f2dace_SOA_geofac_div_d_2_s_26 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->geofac_div =
        m.read<std::remove_pointer<decltype(x->geofac_div)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# geofac_grdiv"}); // Should contain '# geofac_grdiv'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_geofac_grdiv_d_0_s_27 = m.size[0];
    x->__f2dace_SA_geofac_grdiv_d_1_s_28 = m.size[1];
    x->__f2dace_SA_geofac_grdiv_d_2_s_29 = m.size[2];
    x->__f2dace_SOA_geofac_grdiv_d_0_s_27 = m.lbound[0];
    x->__f2dace_SOA_geofac_grdiv_d_1_s_28 = m.lbound[1];
    x->__f2dace_SOA_geofac_grdiv_d_2_s_29 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->geofac_grdiv =
        m.read<std::remove_pointer<decltype(x->geofac_grdiv)>::type>(s);

  } // CONCLUDING IF
}

void deserialize(t_grid_cells *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# edge_idx"}); // Should contain '# edge_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_idx_d_0_s_50 = m.size[0];
    x->__f2dace_SA_edge_idx_d_1_s_51 = m.size[1];
    x->__f2dace_SA_edge_idx_d_2_s_52 = m.size[2];
    x->__f2dace_SOA_edge_idx_d_0_s_50 = m.lbound[0];
    x->__f2dace_SOA_edge_idx_d_1_s_51 = m.lbound[1];
    x->__f2dace_SOA_edge_idx_d_2_s_52 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_idx = m.read<std::remove_pointer<decltype(x->edge_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# edge_blk"}); // Should contain '# edge_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_edge_blk_d_0_s_53 = m.size[0];
    x->__f2dace_SA_edge_blk_d_1_s_54 = m.size[1];
    x->__f2dace_SA_edge_blk_d_2_s_55 = m.size[2];
    x->__f2dace_SOA_edge_blk_d_0_s_53 = m.lbound[0];
    x->__f2dace_SOA_edge_blk_d_1_s_54 = m.lbound[1];
    x->__f2dace_SOA_edge_blk_d_2_s_55 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->edge_blk = m.read<std::remove_pointer<decltype(x->edge_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_56 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_56 = m.lbound[0];
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
    x->__f2dace_SA_end_index_d_0_s_57 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_57 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_58 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_58 = m.lbound[0];
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
    x->__f2dace_SA_end_block_d_0_s_59 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_59 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_block = m.read<std::remove_pointer<decltype(x->end_block)>::type>(s);

  } // CONCLUDING IF
}

void deserialize(t_grid_edges *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# quad_idx"}); // Should contain '# quad_idx'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_quad_idx_d_0_s_60 = m.size[0];
    x->__f2dace_SA_quad_idx_d_1_s_61 = m.size[1];
    x->__f2dace_SA_quad_idx_d_2_s_62 = m.size[2];
    x->__f2dace_SOA_quad_idx_d_0_s_60 = m.lbound[0];
    x->__f2dace_SOA_quad_idx_d_1_s_61 = m.lbound[1];
    x->__f2dace_SOA_quad_idx_d_2_s_62 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->quad_idx = m.read<std::remove_pointer<decltype(x->quad_idx)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# quad_blk"}); // Should contain '# quad_blk'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_quad_blk_d_0_s_63 = m.size[0];
    x->__f2dace_SA_quad_blk_d_1_s_64 = m.size[1];
    x->__f2dace_SA_quad_blk_d_2_s_65 = m.size[2];
    x->__f2dace_SOA_quad_blk_d_0_s_63 = m.lbound[0];
    x->__f2dace_SOA_quad_blk_d_1_s_64 = m.lbound[1];
    x->__f2dace_SOA_quad_blk_d_2_s_65 = m.lbound[2];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->quad_blk = m.read<std::remove_pointer<decltype(x->quad_blk)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_index"}); // Should contain '# start_index'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_index_d_0_s_66 = m.size[0];
    x->__f2dace_SOA_start_index_d_0_s_66 = m.lbound[0];
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
    x->__f2dace_SA_end_index_d_0_s_67 = m.size[0];
    x->__f2dace_SOA_end_index_d_0_s_67 = m.lbound[0];
    // We only need to allocate a volume of contiguous memory, and let DaCe
    // interpret (assuming it follows the same protocol as us).
    x->end_index = m.read<std::remove_pointer<decltype(x->end_index)>::type>(s);

  } // CONCLUDING IF
  read_line(s, {"# start_block"}); // Should contain '# start_block'

  read_line(s, {"# alloc"}); // Should contain '# alloc'
  deserialize(&yep, s);
  if (yep) { // BEGINING IF

    m = read_array_meta(s);
    x->__f2dace_SA_start_block_d_0_s_68 = m.size[0];
    x->__f2dace_SOA_start_block_d_0_s_68 = m.lbound[0];
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
    x->__f2dace_SA_end_block_d_0_s_69 = m.size[0];
    x->__f2dace_SOA_end_block_d_0_s_69 = m.lbound[0];
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

  read_line(s, {"# cells"}); // Should contain '# cells'

  x->cells = new std::remove_pointer<decltype(x->cells)>::type;
  deserialize(x->cells, s);

  read_line(s, {"# edges"}); // Should contain '# edges'

  x->edges = new std::remove_pointer<decltype(x->edges)>::type;
  deserialize(x->edges, s);
}

void deserialize(t_nh_prog *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# w"}); // Should contain '# w'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->w)>::type>(s);
    x->__f2dace_SA_w_d_0_s_192 = m.size.at(0);
    x->__f2dace_SA_w_d_1_s_193 = m.size.at(1);
    x->__f2dace_SA_w_d_2_s_194 = m.size.at(2);
    x->__f2dace_SOA_w_d_0_s_192 = m.lbound.at(0);
    x->__f2dace_SOA_w_d_1_s_193 = m.lbound.at(1);
    x->__f2dace_SOA_w_d_2_s_194 = m.lbound.at(2);
    x->w = arr;
  }

  read_line(s, {"# vn"}); // Should contain '# vn'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vn)>::type>(s);
    x->__f2dace_SA_vn_d_0_s_195 = m.size.at(0);
    x->__f2dace_SA_vn_d_1_s_196 = m.size.at(1);
    x->__f2dace_SA_vn_d_2_s_197 = m.size.at(2);
    x->__f2dace_SOA_vn_d_0_s_195 = m.lbound.at(0);
    x->__f2dace_SOA_vn_d_1_s_196 = m.lbound.at(1);
    x->__f2dace_SOA_vn_d_2_s_197 = m.lbound.at(2);
    x->vn = arr;
  }

  read_line(s, {"# rho"}); // Should contain '# rho'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho)>::type>(s);
    x->__f2dace_SA_rho_d_0_s_198 = m.size.at(0);
    x->__f2dace_SA_rho_d_1_s_199 = m.size.at(1);
    x->__f2dace_SA_rho_d_2_s_200 = m.size.at(2);
    x->__f2dace_SOA_rho_d_0_s_198 = m.lbound.at(0);
    x->__f2dace_SOA_rho_d_1_s_199 = m.lbound.at(1);
    x->__f2dace_SOA_rho_d_2_s_200 = m.lbound.at(2);
    x->rho = arr;
  }

  read_line(s, {"# exner"}); // Should contain '# exner'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner)>::type>(s);
    x->__f2dace_SA_exner_d_0_s_201 = m.size.at(0);
    x->__f2dace_SA_exner_d_1_s_202 = m.size.at(1);
    x->__f2dace_SA_exner_d_2_s_203 = m.size.at(2);
    x->__f2dace_SOA_exner_d_0_s_201 = m.lbound.at(0);
    x->__f2dace_SOA_exner_d_1_s_202 = m.lbound.at(1);
    x->__f2dace_SOA_exner_d_2_s_203 = m.lbound.at(2);
    x->exner = arr;
  }

  read_line(s, {"# theta_v"}); // Should contain '# theta_v'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v)>::type>(s);
    x->__f2dace_SA_theta_v_d_0_s_204 = m.size.at(0);
    x->__f2dace_SA_theta_v_d_1_s_205 = m.size.at(1);
    x->__f2dace_SA_theta_v_d_2_s_206 = m.size.at(2);
    x->__f2dace_SOA_theta_v_d_0_s_204 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_d_1_s_205 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_d_2_s_206 = m.lbound.at(2);
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
    x->__f2dace_SA_exner_pr_d_0_s_207 = m.size.at(0);
    x->__f2dace_SA_exner_pr_d_1_s_208 = m.size.at(1);
    x->__f2dace_SA_exner_pr_d_2_s_209 = m.size.at(2);
    x->__f2dace_SOA_exner_pr_d_0_s_207 = m.lbound.at(0);
    x->__f2dace_SOA_exner_pr_d_1_s_208 = m.lbound.at(1);
    x->__f2dace_SOA_exner_pr_d_2_s_209 = m.lbound.at(2);
    x->exner_pr = arr;
  }

  read_line(s, {"# mass_fl_e"}); // Should contain '# mass_fl_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mass_fl_e)>::type>(s);
    x->__f2dace_SA_mass_fl_e_d_0_s_210 = m.size.at(0);
    x->__f2dace_SA_mass_fl_e_d_1_s_211 = m.size.at(1);
    x->__f2dace_SA_mass_fl_e_d_2_s_212 = m.size.at(2);
    x->__f2dace_SOA_mass_fl_e_d_0_s_210 = m.lbound.at(0);
    x->__f2dace_SOA_mass_fl_e_d_1_s_211 = m.lbound.at(1);
    x->__f2dace_SOA_mass_fl_e_d_2_s_212 = m.lbound.at(2);
    x->mass_fl_e = arr;
  }

  read_line(s, {"# rho_ic"}); // Should contain '# rho_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ic)>::type>(s);
    x->__f2dace_SA_rho_ic_d_0_s_213 = m.size.at(0);
    x->__f2dace_SA_rho_ic_d_1_s_214 = m.size.at(1);
    x->__f2dace_SA_rho_ic_d_2_s_215 = m.size.at(2);
    x->__f2dace_SOA_rho_ic_d_0_s_213 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ic_d_1_s_214 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ic_d_2_s_215 = m.lbound.at(2);
    x->rho_ic = arr;
  }

  read_line(s, {"# theta_v_ic"}); // Should contain '# theta_v_ic'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v_ic)>::type>(s);
    x->__f2dace_SA_theta_v_ic_d_0_s_216 = m.size.at(0);
    x->__f2dace_SA_theta_v_ic_d_1_s_217 = m.size.at(1);
    x->__f2dace_SA_theta_v_ic_d_2_s_218 = m.size.at(2);
    x->__f2dace_SOA_theta_v_ic_d_0_s_216 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_ic_d_1_s_217 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_ic_d_2_s_218 = m.lbound.at(2);
    x->theta_v_ic = arr;
  }

  read_line(s, {"# grf_tend_w"}); // Should contain '# grf_tend_w'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_w)>::type>(s);
    x->__f2dace_SA_grf_tend_w_d_0_s_219 = m.size.at(0);
    x->__f2dace_SA_grf_tend_w_d_1_s_220 = m.size.at(1);
    x->__f2dace_SA_grf_tend_w_d_2_s_221 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_w_d_0_s_219 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_w_d_1_s_220 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_w_d_2_s_221 = m.lbound.at(2);
    x->grf_tend_w = arr;
  }

  read_line(s, {"# grf_tend_rho"}); // Should contain '# grf_tend_rho'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_rho)>::type>(s);
    x->__f2dace_SA_grf_tend_rho_d_0_s_222 = m.size.at(0);
    x->__f2dace_SA_grf_tend_rho_d_1_s_223 = m.size.at(1);
    x->__f2dace_SA_grf_tend_rho_d_2_s_224 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_rho_d_0_s_222 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_rho_d_1_s_223 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_rho_d_2_s_224 = m.lbound.at(2);
    x->grf_tend_rho = arr;
  }

  read_line(s, {"# grf_bdy_mflx"}); // Should contain '# grf_bdy_mflx'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_bdy_mflx)>::type>(s);
    x->__f2dace_SA_grf_bdy_mflx_d_0_s_225 = m.size.at(0);
    x->__f2dace_SA_grf_bdy_mflx_d_1_s_226 = m.size.at(1);
    x->__f2dace_SA_grf_bdy_mflx_d_2_s_227 = m.size.at(2);
    x->__f2dace_SOA_grf_bdy_mflx_d_0_s_225 = m.lbound.at(0);
    x->__f2dace_SOA_grf_bdy_mflx_d_1_s_226 = m.lbound.at(1);
    x->__f2dace_SOA_grf_bdy_mflx_d_2_s_227 = m.lbound.at(2);
    x->grf_bdy_mflx = arr;
  }

  read_line(s, {"# grf_tend_thv"}); // Should contain '# grf_tend_thv'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->grf_tend_thv)>::type>(s);
    x->__f2dace_SA_grf_tend_thv_d_0_s_228 = m.size.at(0);
    x->__f2dace_SA_grf_tend_thv_d_1_s_229 = m.size.at(1);
    x->__f2dace_SA_grf_tend_thv_d_2_s_230 = m.size.at(2);
    x->__f2dace_SOA_grf_tend_thv_d_0_s_228 = m.lbound.at(0);
    x->__f2dace_SOA_grf_tend_thv_d_1_s_229 = m.lbound.at(1);
    x->__f2dace_SOA_grf_tend_thv_d_2_s_230 = m.lbound.at(2);
    x->grf_tend_thv = arr;
  }

  read_line(s, {"# vn_ie_ubc"}); // Should contain '# vn_ie_ubc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ie_ubc)>::type>(s);
    x->__f2dace_SA_vn_ie_ubc_d_0_s_231 = m.size.at(0);
    x->__f2dace_SA_vn_ie_ubc_d_1_s_232 = m.size.at(1);
    x->__f2dace_SA_vn_ie_ubc_d_2_s_233 = m.size.at(2);
    x->__f2dace_SOA_vn_ie_ubc_d_0_s_231 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ie_ubc_d_1_s_232 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ie_ubc_d_2_s_233 = m.lbound.at(2);
    x->vn_ie_ubc = arr;
  }

  read_line(s, {"# w_ubc"}); // Should contain '# w_ubc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->w_ubc)>::type>(s);
    x->__f2dace_SA_w_ubc_d_0_s_234 = m.size.at(0);
    x->__f2dace_SA_w_ubc_d_1_s_235 = m.size.at(1);
    x->__f2dace_SA_w_ubc_d_2_s_236 = m.size.at(2);
    x->__f2dace_SOA_w_ubc_d_0_s_234 = m.lbound.at(0);
    x->__f2dace_SOA_w_ubc_d_1_s_235 = m.lbound.at(1);
    x->__f2dace_SOA_w_ubc_d_2_s_236 = m.lbound.at(2);
    x->w_ubc = arr;
  }

  read_line(s, {"# theta_v_ic_ubc"}); // Should contain '# theta_v_ic_ubc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->theta_v_ic_ubc)>::type>(s);
    x->__f2dace_SA_theta_v_ic_ubc_d_0_s_237 = m.size.at(0);
    x->__f2dace_SA_theta_v_ic_ubc_d_1_s_238 = m.size.at(1);
    x->__f2dace_SA_theta_v_ic_ubc_d_2_s_239 = m.size.at(2);
    x->__f2dace_SOA_theta_v_ic_ubc_d_0_s_237 = m.lbound.at(0);
    x->__f2dace_SOA_theta_v_ic_ubc_d_1_s_238 = m.lbound.at(1);
    x->__f2dace_SOA_theta_v_ic_ubc_d_2_s_239 = m.lbound.at(2);
    x->theta_v_ic_ubc = arr;
  }

  read_line(s, {"# rho_ic_ubc"}); // Should contain '# rho_ic_ubc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_ic_ubc)>::type>(s);
    x->__f2dace_SA_rho_ic_ubc_d_0_s_240 = m.size.at(0);
    x->__f2dace_SA_rho_ic_ubc_d_1_s_241 = m.size.at(1);
    x->__f2dace_SA_rho_ic_ubc_d_2_s_242 = m.size.at(2);
    x->__f2dace_SOA_rho_ic_ubc_d_0_s_240 = m.lbound.at(0);
    x->__f2dace_SOA_rho_ic_ubc_d_1_s_241 = m.lbound.at(1);
    x->__f2dace_SOA_rho_ic_ubc_d_2_s_242 = m.lbound.at(2);
    x->rho_ic_ubc = arr;
  }

  read_line(s, {"# mflx_ic_ubc"}); // Should contain '# mflx_ic_ubc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->mflx_ic_ubc)>::type>(s);
    x->__f2dace_SA_mflx_ic_ubc_d_0_s_243 = m.size.at(0);
    x->__f2dace_SA_mflx_ic_ubc_d_1_s_244 = m.size.at(1);
    x->__f2dace_SA_mflx_ic_ubc_d_2_s_245 = m.size.at(2);
    x->__f2dace_SOA_mflx_ic_ubc_d_0_s_243 = m.lbound.at(0);
    x->__f2dace_SOA_mflx_ic_ubc_d_1_s_244 = m.lbound.at(1);
    x->__f2dace_SOA_mflx_ic_ubc_d_2_s_245 = m.lbound.at(2);
    x->mflx_ic_ubc = arr;
  }

  read_line(s, {"# exner_incr"}); // Should contain '# exner_incr'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_incr)>::type>(s);
    x->__f2dace_SA_exner_incr_d_0_s_246 = m.size.at(0);
    x->__f2dace_SA_exner_incr_d_1_s_247 = m.size.at(1);
    x->__f2dace_SA_exner_incr_d_2_s_248 = m.size.at(2);
    x->__f2dace_SOA_exner_incr_d_0_s_246 = m.lbound.at(0);
    x->__f2dace_SOA_exner_incr_d_1_s_247 = m.lbound.at(1);
    x->__f2dace_SOA_exner_incr_d_2_s_248 = m.lbound.at(2);
    x->exner_incr = arr;
  }

  read_line(s, {"# rho_incr"}); // Should contain '# rho_incr'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rho_incr)>::type>(s);
    x->__f2dace_SA_rho_incr_d_0_s_249 = m.size.at(0);
    x->__f2dace_SA_rho_incr_d_1_s_250 = m.size.at(1);
    x->__f2dace_SA_rho_incr_d_2_s_251 = m.size.at(2);
    x->__f2dace_SOA_rho_incr_d_0_s_249 = m.lbound.at(0);
    x->__f2dace_SOA_rho_incr_d_1_s_250 = m.lbound.at(1);
    x->__f2dace_SOA_rho_incr_d_2_s_251 = m.lbound.at(2);
    x->rho_incr = arr;
  }

  read_line(s, {"# vt"}); // Should contain '# vt'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] = read_pointer<std::remove_pointer<decltype(x->vt)>::type>(s);
    x->__f2dace_SA_vt_d_0_s_252 = m.size.at(0);
    x->__f2dace_SA_vt_d_1_s_253 = m.size.at(1);
    x->__f2dace_SA_vt_d_2_s_254 = m.size.at(2);
    x->__f2dace_SOA_vt_d_0_s_252 = m.lbound.at(0);
    x->__f2dace_SOA_vt_d_1_s_253 = m.lbound.at(1);
    x->__f2dace_SOA_vt_d_2_s_254 = m.lbound.at(2);
    x->vt = arr;
  }

  read_line(s, {"# ddt_exner_phy"}); // Should contain '# ddt_exner_phy'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_exner_phy)>::type>(s);
    x->__f2dace_SA_ddt_exner_phy_d_0_s_255 = m.size.at(0);
    x->__f2dace_SA_ddt_exner_phy_d_1_s_256 = m.size.at(1);
    x->__f2dace_SA_ddt_exner_phy_d_2_s_257 = m.size.at(2);
    x->__f2dace_SOA_ddt_exner_phy_d_0_s_255 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_exner_phy_d_1_s_256 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_exner_phy_d_2_s_257 = m.lbound.at(2);
    x->ddt_exner_phy = arr;
  }

  read_line(s, {"# exner_dyn_incr"}); // Should contain '# exner_dyn_incr'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_dyn_incr)>::type>(s);
    x->__f2dace_SA_exner_dyn_incr_d_0_s_258 = m.size.at(0);
    x->__f2dace_SA_exner_dyn_incr_d_1_s_259 = m.size.at(1);
    x->__f2dace_SA_exner_dyn_incr_d_2_s_260 = m.size.at(2);
    x->__f2dace_SOA_exner_dyn_incr_d_0_s_258 = m.lbound.at(0);
    x->__f2dace_SOA_exner_dyn_incr_d_1_s_259 = m.lbound.at(1);
    x->__f2dace_SOA_exner_dyn_incr_d_2_s_260 = m.lbound.at(2);
    x->exner_dyn_incr = arr;
  }

  read_line(s, {"# vn_ie"}); // Should contain '# vn_ie'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vn_ie)>::type>(s);
    x->__f2dace_SA_vn_ie_d_0_s_261 = m.size.at(0);
    x->__f2dace_SA_vn_ie_d_1_s_262 = m.size.at(1);
    x->__f2dace_SA_vn_ie_d_2_s_263 = m.size.at(2);
    x->__f2dace_SOA_vn_ie_d_0_s_261 = m.lbound.at(0);
    x->__f2dace_SOA_vn_ie_d_1_s_262 = m.lbound.at(1);
    x->__f2dace_SOA_vn_ie_d_2_s_263 = m.lbound.at(2);
    x->vn_ie = arr;
  }

  read_line(s, {"# w_concorr_c"}); // Should contain '# w_concorr_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->w_concorr_c)>::type>(s);
    x->__f2dace_SA_w_concorr_c_d_0_s_264 = m.size.at(0);
    x->__f2dace_SA_w_concorr_c_d_1_s_265 = m.size.at(1);
    x->__f2dace_SA_w_concorr_c_d_2_s_266 = m.size.at(2);
    x->__f2dace_SOA_w_concorr_c_d_0_s_264 = m.lbound.at(0);
    x->__f2dace_SOA_w_concorr_c_d_1_s_265 = m.lbound.at(1);
    x->__f2dace_SOA_w_concorr_c_d_2_s_266 = m.lbound.at(2);
    x->w_concorr_c = arr;
  }

  read_line(s, {"# ddt_w_adv_pc"}); // Should contain '# ddt_w_adv_pc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddt_w_adv_pc)>::type>(s);
    x->__f2dace_SA_ddt_w_adv_pc_d_0_s_267 = m.size.at(0);
    x->__f2dace_SA_ddt_w_adv_pc_d_1_s_268 = m.size.at(1);
    x->__f2dace_SA_ddt_w_adv_pc_d_2_s_269 = m.size.at(2);
    x->__f2dace_SA_ddt_w_adv_pc_d_3_s_270 = m.size.at(3);
    x->__f2dace_SOA_ddt_w_adv_pc_d_0_s_267 = m.lbound.at(0);
    x->__f2dace_SOA_ddt_w_adv_pc_d_1_s_268 = m.lbound.at(1);
    x->__f2dace_SOA_ddt_w_adv_pc_d_2_s_269 = m.lbound.at(2);
    x->__f2dace_SOA_ddt_w_adv_pc_d_3_s_270 = m.lbound.at(3);
    x->ddt_w_adv_pc = arr;
  }
}

void deserialize(t_nh_ref *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# w_ref"}); // Should contain '# w_ref'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->w_ref)>::type>(s);
    x->__f2dace_SA_w_ref_d_0_s_271 = m.size.at(0);
    x->__f2dace_SA_w_ref_d_1_s_272 = m.size.at(1);
    x->__f2dace_SA_w_ref_d_2_s_273 = m.size.at(2);
    x->__f2dace_SOA_w_ref_d_0_s_271 = m.lbound.at(0);
    x->__f2dace_SOA_w_ref_d_1_s_272 = m.lbound.at(1);
    x->__f2dace_SOA_w_ref_d_2_s_273 = m.lbound.at(2);
    x->w_ref = arr;
  }
}

void deserialize(t_nh_metrics *x, std::istream &s) {
  bool yep;
  array_meta m;
  read_line(s, {"# rayleigh_w"}); // Should contain '# rayleigh_w'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->rayleigh_w)>::type>(s);
    x->__f2dace_SA_rayleigh_w_d_0_s_274 = m.size.at(0);
    x->__f2dace_SOA_rayleigh_w_d_0_s_274 = m.lbound.at(0);
    x->rayleigh_w = arr;
  }

  read_line(s, {"# vwind_expl_wgt"}); // Should contain '# vwind_expl_wgt'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vwind_expl_wgt)>::type>(s);
    x->__f2dace_SA_vwind_expl_wgt_d_0_s_275 = m.size.at(0);
    x->__f2dace_SA_vwind_expl_wgt_d_1_s_276 = m.size.at(1);
    x->__f2dace_SOA_vwind_expl_wgt_d_0_s_275 = m.lbound.at(0);
    x->__f2dace_SOA_vwind_expl_wgt_d_1_s_276 = m.lbound.at(1);
    x->vwind_expl_wgt = arr;
  }

  read_line(s, {"# vwind_impl_wgt"}); // Should contain '# vwind_impl_wgt'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->vwind_impl_wgt)>::type>(s);
    x->__f2dace_SA_vwind_impl_wgt_d_0_s_277 = m.size.at(0);
    x->__f2dace_SA_vwind_impl_wgt_d_1_s_278 = m.size.at(1);
    x->__f2dace_SOA_vwind_impl_wgt_d_0_s_277 = m.lbound.at(0);
    x->__f2dace_SOA_vwind_impl_wgt_d_1_s_278 = m.lbound.at(1);
    x->vwind_impl_wgt = arr;
  }

  read_line(s, {"# ddxn_z_full"}); // Should contain '# ddxn_z_full'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddxn_z_full)>::type>(s);
    x->__f2dace_SA_ddxn_z_full_d_0_s_279 = m.size.at(0);
    x->__f2dace_SA_ddxn_z_full_d_1_s_280 = m.size.at(1);
    x->__f2dace_SA_ddxn_z_full_d_2_s_281 = m.size.at(2);
    x->__f2dace_SOA_ddxn_z_full_d_0_s_279 = m.lbound.at(0);
    x->__f2dace_SOA_ddxn_z_full_d_1_s_280 = m.lbound.at(1);
    x->__f2dace_SOA_ddxn_z_full_d_2_s_281 = m.lbound.at(2);
    x->ddxn_z_full = arr;
  }

  read_line(s, {"# ddxt_z_full"}); // Should contain '# ddxt_z_full'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddxt_z_full)>::type>(s);
    x->__f2dace_SA_ddxt_z_full_d_0_s_282 = m.size.at(0);
    x->__f2dace_SA_ddxt_z_full_d_1_s_283 = m.size.at(1);
    x->__f2dace_SA_ddxt_z_full_d_2_s_284 = m.size.at(2);
    x->__f2dace_SOA_ddxt_z_full_d_0_s_282 = m.lbound.at(0);
    x->__f2dace_SOA_ddxt_z_full_d_1_s_283 = m.lbound.at(1);
    x->__f2dace_SOA_ddxt_z_full_d_2_s_284 = m.lbound.at(2);
    x->ddxt_z_full = arr;
  }

  read_line(s, {"# ddqz_z_full_e"}); // Should contain '# ddqz_z_full_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_full_e)>::type>(s);
    x->__f2dace_SA_ddqz_z_full_e_d_0_s_285 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_full_e_d_1_s_286 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_full_e_d_2_s_287 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_full_e_d_0_s_285 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_full_e_d_1_s_286 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_full_e_d_2_s_287 = m.lbound.at(2);
    x->ddqz_z_full_e = arr;
  }

  read_line(s, {"# ddqz_z_half"}); // Should contain '# ddqz_z_half'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->ddqz_z_half)>::type>(s);
    x->__f2dace_SA_ddqz_z_half_d_0_s_288 = m.size.at(0);
    x->__f2dace_SA_ddqz_z_half_d_1_s_289 = m.size.at(1);
    x->__f2dace_SA_ddqz_z_half_d_2_s_290 = m.size.at(2);
    x->__f2dace_SOA_ddqz_z_half_d_0_s_288 = m.lbound.at(0);
    x->__f2dace_SOA_ddqz_z_half_d_1_s_289 = m.lbound.at(1);
    x->__f2dace_SOA_ddqz_z_half_d_2_s_290 = m.lbound.at(2);
    x->ddqz_z_half = arr;
  }

  read_line(s, {"# inv_ddqz_z_full"}); // Should contain '# inv_ddqz_z_full'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->inv_ddqz_z_full)>::type>(
            s);
    x->__f2dace_SA_inv_ddqz_z_full_d_0_s_291 = m.size.at(0);
    x->__f2dace_SA_inv_ddqz_z_full_d_1_s_292 = m.size.at(1);
    x->__f2dace_SA_inv_ddqz_z_full_d_2_s_293 = m.size.at(2);
    x->__f2dace_SOA_inv_ddqz_z_full_d_0_s_291 = m.lbound.at(0);
    x->__f2dace_SOA_inv_ddqz_z_full_d_1_s_292 = m.lbound.at(1);
    x->__f2dace_SOA_inv_ddqz_z_full_d_2_s_293 = m.lbound.at(2);
    x->inv_ddqz_z_full = arr;
  }

  read_line(s, {"# wgtfac_c"}); // Should contain '# wgtfac_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfac_c)>::type>(s);
    x->__f2dace_SA_wgtfac_c_d_0_s_294 = m.size.at(0);
    x->__f2dace_SA_wgtfac_c_d_1_s_295 = m.size.at(1);
    x->__f2dace_SA_wgtfac_c_d_2_s_296 = m.size.at(2);
    x->__f2dace_SOA_wgtfac_c_d_0_s_294 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfac_c_d_1_s_295 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfac_c_d_2_s_296 = m.lbound.at(2);
    x->wgtfac_c = arr;
  }

  read_line(s, {"# wgtfac_e"}); // Should contain '# wgtfac_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfac_e)>::type>(s);
    x->__f2dace_SA_wgtfac_e_d_0_s_297 = m.size.at(0);
    x->__f2dace_SA_wgtfac_e_d_1_s_298 = m.size.at(1);
    x->__f2dace_SA_wgtfac_e_d_2_s_299 = m.size.at(2);
    x->__f2dace_SOA_wgtfac_e_d_0_s_297 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfac_e_d_1_s_298 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfac_e_d_2_s_299 = m.lbound.at(2);
    x->wgtfac_e = arr;
  }

  read_line(s, {"# wgtfacq_c"}); // Should contain '# wgtfacq_c'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq_c)>::type>(s);
    x->__f2dace_SA_wgtfacq_c_d_0_s_300 = m.size.at(0);
    x->__f2dace_SA_wgtfacq_c_d_1_s_301 = m.size.at(1);
    x->__f2dace_SA_wgtfacq_c_d_2_s_302 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq_c_d_0_s_300 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq_c_d_1_s_301 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq_c_d_2_s_302 = m.lbound.at(2);
    x->wgtfacq_c = arr;
  }

  read_line(s, {"# wgtfacq_e"}); // Should contain '# wgtfacq_e'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->wgtfacq_e)>::type>(s);
    x->__f2dace_SA_wgtfacq_e_d_0_s_303 = m.size.at(0);
    x->__f2dace_SA_wgtfacq_e_d_1_s_304 = m.size.at(1);
    x->__f2dace_SA_wgtfacq_e_d_2_s_305 = m.size.at(2);
    x->__f2dace_SOA_wgtfacq_e_d_0_s_303 = m.lbound.at(0);
    x->__f2dace_SOA_wgtfacq_e_d_1_s_304 = m.lbound.at(1);
    x->__f2dace_SOA_wgtfacq_e_d_2_s_305 = m.lbound.at(2);
    x->wgtfacq_e = arr;
  }

  read_line(s, {"# exner_ref_mc"}); // Should contain '# exner_ref_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->exner_ref_mc)>::type>(s);
    x->__f2dace_SA_exner_ref_mc_d_0_s_306 = m.size.at(0);
    x->__f2dace_SA_exner_ref_mc_d_1_s_307 = m.size.at(1);
    x->__f2dace_SA_exner_ref_mc_d_2_s_308 = m.size.at(2);
    x->__f2dace_SOA_exner_ref_mc_d_0_s_306 = m.lbound.at(0);
    x->__f2dace_SOA_exner_ref_mc_d_1_s_307 = m.lbound.at(1);
    x->__f2dace_SOA_exner_ref_mc_d_2_s_308 = m.lbound.at(2);
    x->exner_ref_mc = arr;
  }

  read_line(s, {"# bdy_mflx_e_idx"}); // Should contain '# bdy_mflx_e_idx'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->bdy_mflx_e_idx)>::type>(s);
    x->__f2dace_SA_bdy_mflx_e_idx_d_0_s_309 = m.size.at(0);
    x->__f2dace_SOA_bdy_mflx_e_idx_d_0_s_309 = m.lbound.at(0);
    x->bdy_mflx_e_idx = arr;
  }

  read_line(s, {"# bdy_mflx_e_blk"}); // Should contain '# bdy_mflx_e_blk'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->bdy_mflx_e_blk)>::type>(s);
    x->__f2dace_SA_bdy_mflx_e_blk_d_0_s_310 = m.size.at(0);
    x->__f2dace_SOA_bdy_mflx_e_blk_d_0_s_310 = m.lbound.at(0);
    x->bdy_mflx_e_blk = arr;
  }

  read_line(s, {"# deepatmo_divh_mc"}); // Should contain '# deepatmo_divh_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_divh_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_divh_mc_d_0_s_311 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_divh_mc_d_0_s_311 = m.lbound.at(0);
    x->deepatmo_divh_mc = arr;
  }

  read_line(s, {"# deepatmo_divzu_mc"}); // Should contain '# deepatmo_divzu_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_divzu_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_divzu_mc_d_0_s_312 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_divzu_mc_d_0_s_312 = m.lbound.at(0);
    x->deepatmo_divzu_mc = arr;
  }

  read_line(s, {"# deepatmo_divzl_mc"}); // Should contain '# deepatmo_divzl_mc'

  read_line(s, {"# assoc"}); // Should contain '# assoc'
  deserialize(&yep, s);

  if (yep) {
    auto [m, arr] =
        read_pointer<std::remove_pointer<decltype(x->deepatmo_divzl_mc)>::type>(
            s);
    x->__f2dace_SA_deepatmo_divzl_mc_d_0_s_313 = m.size.at(0);
    x->__f2dace_SOA_deepatmo_divzl_mc_d_0_s_313 = m.lbound.at(0);
    x->deepatmo_divzl_mc = arr;
  }

  read_line(s, {"# bdy_mflx_e_dim"}); // Should contain '# bdy_mflx_e_dim'

  deserialize(&(x->bdy_mflx_e_dim), s);
}

void deserialize(t_nh_state *x, std::istream &s) {
  bool yep;
  array_meta m;
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

std::string serialize(const t_int_state *x) {
  std::stringstream s;
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
  add_line("# e_flx_avg", s);

  add_line("# alloc", s);
  add_line(serialize(x->e_flx_avg != nullptr), s);
  if (x->e_flx_avg) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->e_flx_avg);
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
        add_line(serialize(x->e_flx_avg[i]), s);
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
  add_line("# geofac_div", s);

  add_line("# alloc", s);
  add_line(serialize(x->geofac_div != nullptr), s);
  if (x->geofac_div) { // BEGINING IF

    {
      const array_meta &m = ARRAY_META_DICT_AT(x->geofac_div);
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
        add_line(serialize(x->geofac_div[i]), s);
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
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_grid_cells *x) {
  std::stringstream s;
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

std::string serialize(const t_grid_edges *x) {
  std::stringstream s;
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
  add_line("# cells", s);
  add_line(serialize(x->cells), s);
  add_line("# edges", s);
  add_line(serialize(x->edges), s);
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

  add_line("# mass_fl_e", s);

  add_line("# assoc", s);
  add_line(serialize(x->mass_fl_e != nullptr), s);

  if (x->mass_fl_e)
    add_line(serialize_array(x->mass_fl_e), s);

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

  add_line("# grf_tend_w", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_w != nullptr), s);

  if (x->grf_tend_w)
    add_line(serialize_array(x->grf_tend_w), s);

  add_line("# grf_tend_rho", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_rho != nullptr), s);

  if (x->grf_tend_rho)
    add_line(serialize_array(x->grf_tend_rho), s);

  add_line("# grf_bdy_mflx", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_bdy_mflx != nullptr), s);

  if (x->grf_bdy_mflx)
    add_line(serialize_array(x->grf_bdy_mflx), s);

  add_line("# grf_tend_thv", s);

  add_line("# assoc", s);
  add_line(serialize(x->grf_tend_thv != nullptr), s);

  if (x->grf_tend_thv)
    add_line(serialize_array(x->grf_tend_thv), s);

  add_line("# vn_ie_ubc", s);

  add_line("# assoc", s);
  add_line(serialize(x->vn_ie_ubc != nullptr), s);

  if (x->vn_ie_ubc)
    add_line(serialize_array(x->vn_ie_ubc), s);

  add_line("# w_ubc", s);

  add_line("# assoc", s);
  add_line(serialize(x->w_ubc != nullptr), s);

  if (x->w_ubc)
    add_line(serialize_array(x->w_ubc), s);

  add_line("# theta_v_ic_ubc", s);

  add_line("# assoc", s);
  add_line(serialize(x->theta_v_ic_ubc != nullptr), s);

  if (x->theta_v_ic_ubc)
    add_line(serialize_array(x->theta_v_ic_ubc), s);

  add_line("# rho_ic_ubc", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_ic_ubc != nullptr), s);

  if (x->rho_ic_ubc)
    add_line(serialize_array(x->rho_ic_ubc), s);

  add_line("# mflx_ic_ubc", s);

  add_line("# assoc", s);
  add_line(serialize(x->mflx_ic_ubc != nullptr), s);

  if (x->mflx_ic_ubc)
    add_line(serialize_array(x->mflx_ic_ubc), s);

  add_line("# exner_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_incr != nullptr), s);

  if (x->exner_incr)
    add_line(serialize_array(x->exner_incr), s);

  add_line("# rho_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->rho_incr != nullptr), s);

  if (x->rho_incr)
    add_line(serialize_array(x->rho_incr), s);

  add_line("# vt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vt != nullptr), s);

  if (x->vt)
    add_line(serialize_array(x->vt), s);

  add_line("# ddt_exner_phy", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_exner_phy != nullptr), s);

  if (x->ddt_exner_phy)
    add_line(serialize_array(x->ddt_exner_phy), s);

  add_line("# exner_dyn_incr", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_dyn_incr != nullptr), s);

  if (x->exner_dyn_incr)
    add_line(serialize_array(x->exner_dyn_incr), s);

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

  add_line("# ddt_w_adv_pc", s);

  add_line("# assoc", s);
  add_line(serialize(x->ddt_w_adv_pc != nullptr), s);

  if (x->ddt_w_adv_pc)
    add_line(serialize_array(x->ddt_w_adv_pc), s);

  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_ref *x) {
  std::stringstream s;
  add_line("# w_ref", s);

  add_line("# assoc", s);
  add_line(serialize(x->w_ref != nullptr), s);

  if (x->w_ref)
    add_line(serialize_array(x->w_ref), s);

  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_metrics *x) {
  std::stringstream s;
  add_line("# rayleigh_w", s);

  add_line("# assoc", s);
  add_line(serialize(x->rayleigh_w != nullptr), s);

  if (x->rayleigh_w)
    add_line(serialize_array(x->rayleigh_w), s);

  add_line("# vwind_expl_wgt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vwind_expl_wgt != nullptr), s);

  if (x->vwind_expl_wgt)
    add_line(serialize_array(x->vwind_expl_wgt), s);

  add_line("# vwind_impl_wgt", s);

  add_line("# assoc", s);
  add_line(serialize(x->vwind_impl_wgt != nullptr), s);

  if (x->vwind_impl_wgt)
    add_line(serialize_array(x->vwind_impl_wgt), s);

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

  add_line("# exner_ref_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->exner_ref_mc != nullptr), s);

  if (x->exner_ref_mc)
    add_line(serialize_array(x->exner_ref_mc), s);

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

  add_line("# deepatmo_divh_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_divh_mc != nullptr), s);

  if (x->deepatmo_divh_mc)
    add_line(serialize_array(x->deepatmo_divh_mc), s);

  add_line("# deepatmo_divzu_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_divzu_mc != nullptr), s);

  if (x->deepatmo_divzu_mc)
    add_line(serialize_array(x->deepatmo_divzu_mc), s);

  add_line("# deepatmo_divzl_mc", s);

  add_line("# assoc", s);
  add_line(serialize(x->deepatmo_divzl_mc != nullptr), s);

  if (x->deepatmo_divzl_mc)
    add_line(serialize_array(x->deepatmo_divzl_mc), s);

  add_line("# bdy_mflx_e_dim", s);
  add_line(serialize(x->bdy_mflx_e_dim), s);
  std::string out = s.str();
  if (out.length() > 0)
    out.pop_back();
  return out;
}

std::string serialize(const t_nh_state *x) {
  std::stringstream s;
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

  {
    read_line(s, "# ndyn_substeps_var");
    auto [m, arr] = read_array<int>(s);
    g->ndyn_substeps_var = arr;
  }

  read_line(s, "# divdamp_type");
  deserialize(g->divdamp_type, s);

  read_line(s, "# rayleigh_type");
  deserialize(g->rayleigh_type, s);

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

  read_line(s, "# nproma");
  deserialize(g->nproma, s);

  read_line(s, "# timers_level");
  deserialize(g->timers_level, s);

  read_line(s, "# timer_solve_nh_edgecomp");
  deserialize(g->timer_solve_nh_edgecomp, s);

  read_line(s, "# timer_solve_nh_vimpl");
  deserialize(g->timer_solve_nh_vimpl, s);

  {
    read_line(s, "# nrdmax");
    auto [m, arr] = read_array<int>(s);
    g->nrdmax = arr;
  }
}

std::string serialize_global_data(const global_data_type *g) {
  std::stringstream s;

  add_line(serialize(g->l_limited_area), s);

  add_line(serialize(g->grf_intmethod_e), s);

  add_line(serialize_array(g->nflatlev), s);

  add_line(serialize(g->is_iau_active), s);

  add_line(serialize(g->iau_wgt_dyn), s);

  add_line(serialize_array(g->ndyn_substeps_var), s);

  add_line(serialize(g->divdamp_type), s);

  add_line(serialize(g->rayleigh_type), s);

  add_line(serialize_array(g->kstart_dd3d), s);

  add_line(serialize_array(g->kstart_moist), s);

  add_line(serialize(g->nproma), s);

  add_line(serialize(g->timers_level), s);

  add_line(serialize(g->timer_solve_nh_edgecomp), s);

  add_line(serialize(g->timer_solve_nh_vimpl), s);

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

    consistent["mo_grid_config.l_limited_area"].insert(
        (g->l_limited_area ? ".true." : ".false."));

    consistent["mo_gridref_config.grf_intmethod_e"].insert(
        serialize(g->grf_intmethod_e));

    consistent["mo_initicon_config.is_iau_active"].insert(
        (g->is_iau_active ? ".true." : ".false."));

    consistent["mo_initicon_config.iau_wgt_dyn"].insert(
        serialize(g->iau_wgt_dyn));

    consistent["mo_nonhydrostatic_config.divdamp_type"].insert(
        serialize(g->divdamp_type));

    consistent["mo_nonhydrostatic_config.rayleigh_type"].insert(
        serialize(g->rayleigh_type));

    consistent["mo_parallel_config.nproma"].insert(serialize(g->nproma));

    consistent["mo_run_config.timers_level"].insert(serialize(g->timers_level));

    consistent["mo_timer.timer_solve_nh_edgecomp"].insert(
        serialize(g->timer_solve_nh_edgecomp));

    consistent["mo_timer.timer_solve_nh_vimpl"].insert(
        serialize(g->timer_solve_nh_vimpl));
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

} // namespace predictor_post

#endif // __DACE_PREDICTOR_POST_SERDE__
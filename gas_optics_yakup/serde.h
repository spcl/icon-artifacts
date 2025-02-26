#ifndef __DACE_SERDE__
#define __DACE_SERDE__

#include <cassert>
#include <istream>
#include <iostream>
#include <sstream>
#include <optional>
#include <algorithm>

#include "gas_optics.h"

namespace serde {
    std::string scroll_space(std::istream& s) {
        std::string out;
        while (!s.eof() && (!s.peek() || isspace(s.peek()))) {
            out += s.get();
            assert(s.good());
        }
        return out;
    }

    std::string read_line(std::istream& s, const std::optional<std::string>& should_contain = {}) {
        if (s.eof()) return "<eof>";
        scroll_space(s);
        char bin[101];
        s.getline(bin, 100);
        assert(s.good());
        if (should_contain) {
            bool ok = (std::string(bin).find(*should_contain) != std::string::npos);
            if (!ok) {
                std::cerr << "Expected: '" << *should_contain << "'; got: '" << bin << "'" << std::endl;
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

        int volume() const {  return std::reduce(size.begin(), size.end(), 1, std::multiplies<int>()) ; }

        template<typename T> T* read(std::istream& s) const;
    };
    std::map<void*, array_meta>* ARRAY_META_DICT() {
        static auto* M = new std::map<void*, array_meta>();
        return M;
    }

    template<typename T>
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
        assert (c == '1' or c == '0');
        x = (c == '1');
    }

    array_meta read_array_meta(std::istream& s) {
        array_meta m;
        read_line(s, {"# rank"});  // Should contain '# rank'
        read_scalar(m.rank, s);
        m.size.resize(m.rank);
        m.lbound.resize(m.rank);
        read_line(s, {"# size"});  // Should contain '# size'
        for (int i=0; i<m.rank; ++i) {
            read_scalar(m.size[i], s);
        }
        read_line(s, {"# lbound"});  // Should contain '# lbound'
        for (int i=0; i<m.rank; ++i) {
            read_scalar(m.lbound[i], s);
        }
        return m;
    }

    template<typename T>
    std::pair<array_meta, T*> read_array(std::istream& s) {
        auto m = serde::read_array_meta(s);
        auto* y = m.read<T>(s);
        return {m, y};
    }

    
void deserialize(float* x, std::istream& s) {
    read_scalar(*x, s);
}
void deserialize(double* x, std::istream& s) {
    read_scalar(*x, s);
}
void deserialize(long double* x, std::istream& s) {
    read_scalar(*x, s);
}
void deserialize(int* x, std::istream& s) {
    read_scalar(*x, s);
}
void deserialize(long* x, std::istream& s) {
    read_scalar(*x, s);
}
void deserialize(long long* x, std::istream& s) {
    read_scalar(*x, s);
}
void deserialize(bool* x, std::istream& s) {
    read_scalar(*x, s);
}
void deserialize(float& x, std::istream& s) {
    read_scalar(x, s);
}
void deserialize(double& x, std::istream& s) {
    read_scalar(x, s);
}
void deserialize(long double& x, std::istream& s) {
    read_scalar(x, s);
}
void deserialize(int& x, std::istream& s) {
    read_scalar(x, s);
}
void deserialize(long& x, std::istream& s) {
    read_scalar(x, s);
}
void deserialize(long long& x, std::istream& s) {
    read_scalar(x, s);
}
void deserialize(bool& x, std::istream& s) {
    read_scalar(x, s);
}


void deserialize(gas_type* x, std::istream& s) {
    bool yep;
    array_meta m;
    read_line(s, {"# mixing_ratio"});  // Should contain '# mixing_ratio'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->mixing_ratio = m.read<std::remove_pointer<decltype(x ->mixing_ratio)>::type>(s);

}


void deserialize(config_type* x, std::istream& s) {
    bool yep;
    array_meta m;
    read_line(s, {"# i_band_from_g_lw"});  // Should contain '# i_band_from_g_lw'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->i_band_from_g_lw = m.read<std::remove_pointer<decltype(x ->i_band_from_g_lw)>::type>(s);

read_line(s, {"# i_band_from_reordered_g_sw"});  // Should contain '# i_band_from_reordered_g_sw'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->i_band_from_reordered_g_sw = m.read<std::remove_pointer<decltype(x ->i_band_from_reordered_g_sw)>::type>(s);

}


void deserialize(thermodynamics_type* x, std::istream& s) {
    bool yep;
    array_meta m;
    read_line(s, {"# temperature_fl"});  // Should contain '# temperature_fl'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->temperature_fl = m.read<std::remove_pointer<decltype(x ->temperature_fl)>::type>(s);

read_line(s, {"# pressure_hl"});  // Should contain '# pressure_hl'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->pressure_hl = m.read<std::remove_pointer<decltype(x ->pressure_hl)>::type>(s);

read_line(s, {"# temperature_hl"});  // Should contain '# temperature_hl'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->temperature_hl = m.read<std::remove_pointer<decltype(x ->temperature_hl)>::type>(s);

read_line(s, {"# pressure_fl"});  // Should contain '# pressure_fl'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->pressure_fl = m.read<std::remove_pointer<decltype(x ->pressure_fl)>::type>(s);

}


void deserialize(single_level_type* x, std::istream& s) {
    bool yep;
    array_meta m;
    read_line(s, {"# skin_temperature"});  // Should contain '# skin_temperature'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->skin_temperature = m.read<std::remove_pointer<decltype(x ->skin_temperature)>::type>(s);

read_line(s, {"# spectral_solar_scaling"});  // Should contain '# spectral_solar_scaling'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->spectral_solar_scaling = m.read<std::remove_pointer<decltype(x ->spectral_solar_scaling)>::type>(s);

read_line(s, {"# cos_sza"});  // Should contain '# cos_sza'

m = read_array_meta(s);


// We only need to allocate a volume of contiguous memory, and let DaCe interpret (assuming it follows the same protocol 
// as us).
x ->cos_sza = m.read<std::remove_pointer<decltype(x ->cos_sza)>::type>(s);

}

    
template<typename T>
void add_line(const T& x, std::ostream& s, bool trailing_newline=true) {
    s << x;
    if (trailing_newline) s << std::endl;
}
void add_line(long long x, std::ostream& s, bool trailing_newline=true) {
    s << x;
    if (trailing_newline) s << std::endl;
}
void add_line(long double x, std::ostream& s, bool trailing_newline=true) {
    s << x;
    if (trailing_newline) s << std::endl;
}
void add_line(bool x, std::ostream& s, bool trailing_newline=true) {
    add_line(int(x), s, trailing_newline);
}
template<typename T>
std::string serialize(const T* x) {
    std::stringstream s;
    add_line(*x, s, false);
    return s.str();
}
std::string serialize(int x) {
    return std::to_string(x);
}
std::string serialize(long x) {
    return std::to_string(x);
}
std::string serialize(long long x) {
    return std::to_string(x);
}
std::string serialize(float x) {
    return std::to_string(x);
}
std::string serialize(double x) {
    return std::to_string(x);
}
std::string serialize(long double x) {
    return std::to_string(x);
}
std::string serialize(bool x) {
    return serialize(int(x));
}


std::string serialize(const gas_type* x) {
    std::stringstream s;
    add_line("# mixing_ratio", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->mixing_ratio];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->mixing_ratio[i]), s);
    }
}

    std::string out = s.str();
    if (out.length() > 0) out.pop_back();
    return out;
}


std::string serialize(const config_type* x) {
    std::stringstream s;
    add_line("# i_band_from_g_lw", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->i_band_from_g_lw];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->i_band_from_g_lw[i]), s);
    }
}

add_line("# i_band_from_reordered_g_sw", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->i_band_from_reordered_g_sw];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->i_band_from_reordered_g_sw[i]), s);
    }
}

    std::string out = s.str();
    if (out.length() > 0) out.pop_back();
    return out;
}


std::string serialize(const thermodynamics_type* x) {
    std::stringstream s;
    add_line("# temperature_fl", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->temperature_fl];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->temperature_fl[i]), s);
    }
}

add_line("# pressure_hl", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->pressure_hl];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->pressure_hl[i]), s);
    }
}

add_line("# temperature_hl", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->temperature_hl];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->temperature_hl[i]), s);
    }
}

add_line("# pressure_fl", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->pressure_fl];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->pressure_fl[i]), s);
    }
}

    std::string out = s.str();
    if (out.length() > 0) out.pop_back();
    return out;
}


std::string serialize(const single_level_type* x) {
    std::stringstream s;
    add_line("# skin_temperature", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->skin_temperature];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->skin_temperature[i]), s);
    }
}

add_line("# spectral_solar_scaling", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->spectral_solar_scaling];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->spectral_solar_scaling[i]), s);
    }
}

add_line("# cos_sza", s);

{
    const array_meta& m = (*ARRAY_META_DICT())[x->cos_sza];
    add_line("# rank", s);
    add_line(m.rank, s);
    add_line("# size", s);
    for (auto i : m.size) add_line(i, s);
    add_line("# lbound", s);
    for (auto i : m.lbound) add_line(i, s);
    add_line("# entries", s);
    for (int i=0; i<m.volume(); ++i) {
        add_line(serialize(x->cos_sza[i]), s);
    }
}

    std::string out = s.str();
    if (out.length() > 0) out.pop_back();
    return out;
}


    template<typename T>
    T* array_meta::read(std::istream& s) const {
        read_line(s, {"# entries"});
        auto* buf = new T[volume()];
        for (int i=0; i<volume(); ++i) {
            deserialize(&buf[i], s);
        }
        (*ARRAY_META_DICT())[buf] = *this;
        return buf;
    }

    
void deserialize_global_data(global_data_type* g, std::istream& s) {
    
{
    read_line(s, "# fracrefa_var_107");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_107 = arr;
}


{
    read_line(s, "# fracrefb_var_108");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_108 = arr;
}


{
    read_line(s, "# absa_var_109");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_109 = arr;
}


{
    read_line(s, "# absb_var_110");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_110 = arr;
}


{
    read_line(s, "# ka_mn2_var_111");
    auto [m, arr] = read_array<double>(s);
    g->ka_mn2_var_111 = arr;
}


{
    read_line(s, "# kb_mn2");
    auto [m, arr] = read_array<double>(s);
    g->kb_mn2 = arr;
}


{
    read_line(s, "# selfref_var_112");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_112 = arr;
}


{
    read_line(s, "# forref_var_113");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_113 = arr;
}


{
    read_line(s, "# fracrefa_var_114");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_114 = arr;
}


{
    read_line(s, "# fracrefb_var_115");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_115 = arr;
}


{
    read_line(s, "# absa_var_116");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_116 = arr;
}


{
    read_line(s, "# absb_var_117");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_117 = arr;
}


{
    read_line(s, "# selfref_var_118");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_118 = arr;
}


{
    read_line(s, "# forref_var_119");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_119 = arr;
}


{
    read_line(s, "# fracrefa_var_120");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_120 = arr;
}


{
    read_line(s, "# fracrefb_var_121");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_121 = arr;
}


{
    read_line(s, "# absa_var_122");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_122 = arr;
}


{
    read_line(s, "# absb_var_123");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_123 = arr;
}


{
    read_line(s, "# ka_mo2");
    auto [m, arr] = read_array<double>(s);
    g->ka_mo2 = arr;
}


{
    read_line(s, "# kb_mo2");
    auto [m, arr] = read_array<double>(s);
    g->kb_mo2 = arr;
}


{
    read_line(s, "# selfref_var_124");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_124 = arr;
}


{
    read_line(s, "# forref_var_125");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_125 = arr;
}


{
    read_line(s, "# fracrefa_var_126");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_126 = arr;
}


{
    read_line(s, "# absa_var_127");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_127 = arr;
}


{
    read_line(s, "# selfref_var_128");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_128 = arr;
}


{
    read_line(s, "# forref_var_129");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_129 = arr;
}


{
    read_line(s, "# fracrefa_var_130");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_130 = arr;
}


{
    read_line(s, "# fracrefb_var_131");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_131 = arr;
}


{
    read_line(s, "# absa_var_132");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_132 = arr;
}


{
    read_line(s, "# selfref_var_133");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_133 = arr;
}


{
    read_line(s, "# forref_var_134");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_134 = arr;
}


{
    read_line(s, "# ka_mco2_var_135");
    auto [m, arr] = read_array<double>(s);
    g->ka_mco2_var_135 = arr;
}


{
    read_line(s, "# ka_mco");
    auto [m, arr] = read_array<double>(s);
    g->ka_mco = arr;
}


{
    read_line(s, "# kb_mo3");
    auto [m, arr] = read_array<double>(s);
    g->kb_mo3 = arr;
}


{
    read_line(s, "# fracrefa_var_136");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_136 = arr;
}


{
    read_line(s, "# fracrefb_var_137");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_137 = arr;
}


{
    read_line(s, "# absa_var_138");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_138 = arr;
}


{
    read_line(s, "# absb_var_139");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_139 = arr;
}


{
    read_line(s, "# selfref_var_140");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_140 = arr;
}


{
    read_line(s, "# forref_var_141");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_141 = arr;
}


{
    read_line(s, "# fracrefa_var_142");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_142 = arr;
}


{
    read_line(s, "# absa_var_143");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_143 = arr;
}


{
    read_line(s, "# ka_mn2_var_144");
    auto [m, arr] = read_array<double>(s);
    g->ka_mn2_var_144 = arr;
}


{
    read_line(s, "# selfref_var_145");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_145 = arr;
}


{
    read_line(s, "# forref_var_146");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_146 = arr;
}


{
    read_line(s, "# fracrefa_var_147");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_147 = arr;
}


{
    read_line(s, "# fracrefb_var_148");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_148 = arr;
}


{
    read_line(s, "# absa_var_149");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_149 = arr;
}


{
    read_line(s, "# absb_var_150");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_150 = arr;
}


{
    read_line(s, "# selfref_var_151");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_151 = arr;
}


{
    read_line(s, "# forref_var_152");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_152 = arr;
}


{
    read_line(s, "# fracrefa_var_153");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_153 = arr;
}


{
    read_line(s, "# fracrefb_var_154");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_154 = arr;
}


{
    read_line(s, "# absa_var_155");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_155 = arr;
}


{
    read_line(s, "# absb_var_156");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_156 = arr;
}


{
    read_line(s, "# selfref_var_157");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_157 = arr;
}


{
    read_line(s, "# forref_var_158");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_158 = arr;
}


{
    read_line(s, "# fracrefa_var_159");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_159 = arr;
}


{
    read_line(s, "# fracrefb_var_160");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_160 = arr;
}


{
    read_line(s, "# ka_mn2o_var_161");
    auto [m, arr] = read_array<double>(s);
    g->ka_mn2o_var_161 = arr;
}


{
    read_line(s, "# kb_mn2o_var_162");
    auto [m, arr] = read_array<double>(s);
    g->kb_mn2o_var_162 = arr;
}


{
    read_line(s, "# absa_var_163");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_163 = arr;
}


{
    read_line(s, "# absb_var_164");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_164 = arr;
}


{
    read_line(s, "# selfref_var_165");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_165 = arr;
}


{
    read_line(s, "# forref_var_166");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_166 = arr;
}


{
    read_line(s, "# fracrefa_var_167");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_167 = arr;
}


{
    read_line(s, "# fracrefb_var_168");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_168 = arr;
}


{
    read_line(s, "# absa_var_169");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_169 = arr;
}


{
    read_line(s, "# absb_var_170");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_170 = arr;
}


{
    read_line(s, "# selfref_var_171");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_171 = arr;
}


{
    read_line(s, "# forref_var_172");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_172 = arr;
}


{
    read_line(s, "# fracrefa_var_173");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_173 = arr;
}


{
    read_line(s, "# fracrefb_var_174");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_174 = arr;
}


{
    read_line(s, "# ccl4");
    auto [m, arr] = read_array<double>(s);
    g->ccl4 = arr;
}


{
    read_line(s, "# absa_var_175");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_175 = arr;
}


{
    read_line(s, "# absb_var_176");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_176 = arr;
}


{
    read_line(s, "# ka_mo3_var_177");
    auto [m, arr] = read_array<double>(s);
    g->ka_mo3_var_177 = arr;
}


{
    read_line(s, "# selfref_var_178");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_178 = arr;
}


{
    read_line(s, "# forref_var_179");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_179 = arr;
}


{
    read_line(s, "# fracrefa_var_180");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_180 = arr;
}


{
    read_line(s, "# cfc11adj");
    auto [m, arr] = read_array<double>(s);
    g->cfc11adj = arr;
}


{
    read_line(s, "# cfc12_var_181");
    auto [m, arr] = read_array<double>(s);
    g->cfc12_var_181 = arr;
}


{
    read_line(s, "# absa_var_182");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_182 = arr;
}


{
    read_line(s, "# selfref_var_183");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_183 = arr;
}


{
    read_line(s, "# ka_mco2_var_184");
    auto [m, arr] = read_array<double>(s);
    g->ka_mco2_var_184 = arr;
}


{
    read_line(s, "# forref_var_185");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_185 = arr;
}


{
    read_line(s, "# fracrefa_var_186");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_186 = arr;
}


{
    read_line(s, "# fracrefb_var_187");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_187 = arr;
}


{
    read_line(s, "# absa_var_188");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_188 = arr;
}


{
    read_line(s, "# absb_var_189");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_189 = arr;
}


{
    read_line(s, "# selfref_var_190");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_190 = arr;
}


{
    read_line(s, "# ka_mco2_var_191");
    auto [m, arr] = read_array<double>(s);
    g->ka_mco2_var_191 = arr;
}


{
    read_line(s, "# kb_mco2_var_192");
    auto [m, arr] = read_array<double>(s);
    g->kb_mco2_var_192 = arr;
}


{
    read_line(s, "# forref_var_193");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_193 = arr;
}


{
    read_line(s, "# fracrefa_var_194");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_194 = arr;
}


{
    read_line(s, "# fracrefb_var_195");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_195 = arr;
}


{
    read_line(s, "# cfc12_var_196");
    auto [m, arr] = read_array<double>(s);
    g->cfc12_var_196 = arr;
}


{
    read_line(s, "# cfc22adj");
    auto [m, arr] = read_array<double>(s);
    g->cfc22adj = arr;
}


{
    read_line(s, "# absa_var_197");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_197 = arr;
}


{
    read_line(s, "# absb_var_198");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_198 = arr;
}


{
    read_line(s, "# ka_mco2_var_199");
    auto [m, arr] = read_array<double>(s);
    g->ka_mco2_var_199 = arr;
}


{
    read_line(s, "# ka_mn2o_var_200");
    auto [m, arr] = read_array<double>(s);
    g->ka_mn2o_var_200 = arr;
}


{
    read_line(s, "# ka_mo3_var_201");
    auto [m, arr] = read_array<double>(s);
    g->ka_mo3_var_201 = arr;
}


{
    read_line(s, "# kb_mco2_var_202");
    auto [m, arr] = read_array<double>(s);
    g->kb_mco2_var_202 = arr;
}


{
    read_line(s, "# kb_mn2o_var_203");
    auto [m, arr] = read_array<double>(s);
    g->kb_mn2o_var_203 = arr;
}


{
    read_line(s, "# selfref_var_204");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_204 = arr;
}


{
    read_line(s, "# forref_var_205");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_205 = arr;
}


{
    read_line(s, "# fracrefa_var_206");
    auto [m, arr] = read_array<double>(s);
    g->fracrefa_var_206 = arr;
}


{
    read_line(s, "# fracrefb_var_207");
    auto [m, arr] = read_array<double>(s);
    g->fracrefb_var_207 = arr;
}


{
    read_line(s, "# absa_var_208");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_208 = arr;
}


{
    read_line(s, "# absb_var_209");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_209 = arr;
}


{
    read_line(s, "# ka_mn2o_var_210");
    auto [m, arr] = read_array<double>(s);
    g->ka_mn2o_var_210 = arr;
}


{
    read_line(s, "# kb_mn2o_var_211");
    auto [m, arr] = read_array<double>(s);
    g->kb_mn2o_var_211 = arr;
}


{
    read_line(s, "# selfref_var_212");
    auto [m, arr] = read_array<double>(s);
    g->selfref_var_212 = arr;
}


{
    read_line(s, "# forref_var_213");
    auto [m, arr] = read_array<double>(s);
    g->forref_var_213 = arr;
}


{
    read_line(s, "# preflog_var_214");
    auto [m, arr] = read_array<double>(s);
    g->preflog_var_214 = arr;
}


{
    read_line(s, "# tref_var_215");
    auto [m, arr] = read_array<double>(s);
    g->tref_var_215 = arr;
}


{
    read_line(s, "# chi_mls");
    auto [m, arr] = read_array<double>(s);
    g->chi_mls = arr;
}


{
    read_line(s, "# nspa_var_216");
    auto [m, arr] = read_array<int>(s);
    g->nspa_var_216 = arr;
}


{
    read_line(s, "# nspb_var_217");
    auto [m, arr] = read_array<int>(s);
    g->nspb_var_217 = arr;
}


{
    read_line(s, "# delwave");
    auto [m, arr] = read_array<double>(s);
    g->delwave = arr;
}


{
    read_line(s, "# totplnk");
    auto [m, arr] = read_array<double>(s);
    g->totplnk = arr;
}


read_line(s, "# rayl_var_218");
deserialize(g->rayl_var_218, s);


read_line(s, "# strrat1");
deserialize(g->strrat1, s);


read_line(s, "# layreffr_var_219");
deserialize(g->layreffr_var_219, s);


{
    read_line(s, "# absa_var_220");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_220 = arr;
}


{
    read_line(s, "# absb_var_221");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_221 = arr;
}


{
    read_line(s, "# selfrefc_var_222");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_222 = arr;
}


{
    read_line(s, "# forrefc_var_223");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_223 = arr;
}


{
    read_line(s, "# sfluxrefc_var_224");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_224 = arr;
}


read_line(s, "# rayl_var_225");
deserialize(g->rayl_var_225, s);


read_line(s, "# strrat_var_226");
deserialize(g->strrat_var_226, s);


read_line(s, "# layreffr_var_227");
deserialize(g->layreffr_var_227, s);


{
    read_line(s, "# absa_var_228");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_228 = arr;
}


{
    read_line(s, "# absb_var_229");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_229 = arr;
}


{
    read_line(s, "# selfrefc_var_230");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_230 = arr;
}


{
    read_line(s, "# forrefc_var_231");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_231 = arr;
}


{
    read_line(s, "# sfluxrefc_var_232");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_232 = arr;
}


read_line(s, "# rayl_var_233");
deserialize(g->rayl_var_233, s);


read_line(s, "# strrat_var_234");
deserialize(g->strrat_var_234, s);


read_line(s, "# layreffr_var_235");
deserialize(g->layreffr_var_235, s);


{
    read_line(s, "# absa_var_236");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_236 = arr;
}


{
    read_line(s, "# absb_var_237");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_237 = arr;
}


{
    read_line(s, "# selfrefc_var_238");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_238 = arr;
}


{
    read_line(s, "# forrefc_var_239");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_239 = arr;
}


{
    read_line(s, "# sfluxrefc_var_240");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_240 = arr;
}


read_line(s, "# rayl_var_241");
deserialize(g->rayl_var_241, s);


read_line(s, "# strrat_var_242");
deserialize(g->strrat_var_242, s);


read_line(s, "# layreffr_var_243");
deserialize(g->layreffr_var_243, s);


{
    read_line(s, "# absa_var_244");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_244 = arr;
}


{
    read_line(s, "# absb_var_245");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_245 = arr;
}


{
    read_line(s, "# selfrefc_var_246");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_246 = arr;
}


{
    read_line(s, "# forrefc_var_247");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_247 = arr;
}


{
    read_line(s, "# sfluxrefc_var_248");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_248 = arr;
}


read_line(s, "# rayl_var_249");
deserialize(g->rayl_var_249, s);


read_line(s, "# layreffr_var_250");
deserialize(g->layreffr_var_250, s);


{
    read_line(s, "# absa_var_251");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_251 = arr;
}


{
    read_line(s, "# absb_var_252");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_252 = arr;
}


{
    read_line(s, "# selfrefc_var_253");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_253 = arr;
}


{
    read_line(s, "# forrefc_var_254");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_254 = arr;
}


{
    read_line(s, "# sfluxrefc_var_255");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_255 = arr;
}


{
    read_line(s, "# absch4c");
    auto [m, arr] = read_array<double>(s);
    g->absch4c = arr;
}


read_line(s, "# rayl_var_256");
deserialize(g->rayl_var_256, s);


read_line(s, "# strrat_var_257");
deserialize(g->strrat_var_257, s);


read_line(s, "# layreffr_var_258");
deserialize(g->layreffr_var_258, s);


{
    read_line(s, "# absa_var_259");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_259 = arr;
}


{
    read_line(s, "# absb_var_260");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_260 = arr;
}


{
    read_line(s, "# selfrefc_var_261");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_261 = arr;
}


{
    read_line(s, "# forrefc_var_262");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_262 = arr;
}


{
    read_line(s, "# sfluxrefc_var_263");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_263 = arr;
}


read_line(s, "# rayl_var_264");
deserialize(g->rayl_var_264, s);


read_line(s, "# strrat_var_265");
deserialize(g->strrat_var_265, s);


read_line(s, "# layreffr_var_266");
deserialize(g->layreffr_var_266, s);


{
    read_line(s, "# absa_var_267");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_267 = arr;
}


{
    read_line(s, "# absb_var_268");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_268 = arr;
}


{
    read_line(s, "# selfrefc_var_269");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_269 = arr;
}


{
    read_line(s, "# forrefc_var_270");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_270 = arr;
}


{
    read_line(s, "# sfluxrefc_var_271");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_271 = arr;
}


read_line(s, "# givfac");
deserialize(g->givfac, s);


read_line(s, "# layreffr_var_272");
deserialize(g->layreffr_var_272, s);


{
    read_line(s, "# absa_var_273");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_273 = arr;
}


{
    read_line(s, "# selfrefc_var_274");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_274 = arr;
}


{
    read_line(s, "# forrefc_var_275");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_275 = arr;
}


{
    read_line(s, "# sfluxrefc_var_276");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_276 = arr;
}


{
    read_line(s, "# raylc_var_277");
    auto [m, arr] = read_array<double>(s);
    g->raylc_var_277 = arr;
}


read_line(s, "# strrat_var_278");
deserialize(g->strrat_var_278, s);


read_line(s, "# layreffr_var_279");
deserialize(g->layreffr_var_279, s);


{
    read_line(s, "# absa_var_280");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_280 = arr;
}


{
    read_line(s, "# absb_var_281");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_281 = arr;
}


{
    read_line(s, "# selfrefc_var_282");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_282 = arr;
}


{
    read_line(s, "# forrefc_var_283");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_283 = arr;
}


{
    read_line(s, "# sfluxrefc_var_284");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_284 = arr;
}


{
    read_line(s, "# abso3ac_var_285");
    auto [m, arr] = read_array<double>(s);
    g->abso3ac_var_285 = arr;
}


{
    read_line(s, "# abso3bc_var_286");
    auto [m, arr] = read_array<double>(s);
    g->abso3bc_var_286 = arr;
}


{
    read_line(s, "# raylac");
    auto [m, arr] = read_array<double>(s);
    g->raylac = arr;
}


{
    read_line(s, "# raylbc");
    auto [m, arr] = read_array<double>(s);
    g->raylbc = arr;
}


read_line(s, "# layreffr_var_287");
deserialize(g->layreffr_var_287, s);


{
    read_line(s, "# absa_var_288");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_288 = arr;
}


{
    read_line(s, "# sfluxrefc_var_289");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_289 = arr;
}


{
    read_line(s, "# raylc_var_290");
    auto [m, arr] = read_array<double>(s);
    g->raylc_var_290 = arr;
}


{
    read_line(s, "# abso3ac_var_291");
    auto [m, arr] = read_array<double>(s);
    g->abso3ac_var_291 = arr;
}


{
    read_line(s, "# abso3bc_var_292");
    auto [m, arr] = read_array<double>(s);
    g->abso3bc_var_292 = arr;
}


{
    read_line(s, "# sfluxrefc_var_293");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_293 = arr;
}


{
    read_line(s, "# raylc_var_294");
    auto [m, arr] = read_array<double>(s);
    g->raylc_var_294 = arr;
}


read_line(s, "# scalekur");
deserialize(g->scalekur, s);


read_line(s, "# layreffr_var_295");
deserialize(g->layreffr_var_295, s);


{
    read_line(s, "# absa_var_296");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_296 = arr;
}


{
    read_line(s, "# absb_var_297");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_297 = arr;
}


{
    read_line(s, "# sfluxrefc_var_298");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_298 = arr;
}


{
    read_line(s, "# raylc_var_299");
    auto [m, arr] = read_array<double>(s);
    g->raylc_var_299 = arr;
}


read_line(s, "# rayl_var_300");
deserialize(g->rayl_var_300, s);


read_line(s, "# strrat_var_301");
deserialize(g->strrat_var_301, s);


read_line(s, "# layreffr_var_302");
deserialize(g->layreffr_var_302, s);


{
    read_line(s, "# absa_var_303");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_303 = arr;
}


{
    read_line(s, "# absb_var_304");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_304 = arr;
}


{
    read_line(s, "# sfluxrefc_var_305");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_305 = arr;
}


read_line(s, "# rayl_var_306");
deserialize(g->rayl_var_306, s);


read_line(s, "# layreffr_var_307");
deserialize(g->layreffr_var_307, s);


{
    read_line(s, "# absa_var_308");
    auto [m, arr] = read_array<double>(s);
    g->absa_var_308 = arr;
}


{
    read_line(s, "# absb_var_309");
    auto [m, arr] = read_array<double>(s);
    g->absb_var_309 = arr;
}


{
    read_line(s, "# selfrefc_var_310");
    auto [m, arr] = read_array<double>(s);
    g->selfrefc_var_310 = arr;
}


{
    read_line(s, "# forrefc_var_311");
    auto [m, arr] = read_array<double>(s);
    g->forrefc_var_311 = arr;
}


{
    read_line(s, "# sfluxrefc_var_312");
    auto [m, arr] = read_array<double>(s);
    g->sfluxrefc_var_312 = arr;
}


{
    read_line(s, "# absh2oc");
    auto [m, arr] = read_array<double>(s);
    g->absh2oc = arr;
}


{
    read_line(s, "# absco2c");
    auto [m, arr] = read_array<double>(s);
    g->absco2c = arr;
}


{
    read_line(s, "# nspa_var_313");
    auto [m, arr] = read_array<int>(s);
    g->nspa_var_313 = arr;
}


{
    read_line(s, "# nspb_var_314");
    auto [m, arr] = read_array<int>(s);
    g->nspb_var_314 = arr;
}


{
    read_line(s, "# preflog_var_315");
    auto [m, arr] = read_array<double>(s);
    g->preflog_var_315 = arr;
}


{
    read_line(s, "# tref_var_316");
    auto [m, arr] = read_array<double>(s);
    g->tref_var_316 = arr;
}


{
    read_line(s, "# ngc");
    auto [m, arr] = read_array<int>(s);
    g->ngc = arr;
}

}

}  // namesepace serde

#endif // __DACE_SERDE__
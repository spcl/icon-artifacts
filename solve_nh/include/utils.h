#ifndef __STANDALONE_UTILS_H__
#define __STANDALONE_UTILS_H__

#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <vector>

namespace standalone_utils {

template <std::ostream &CS> struct AtomicStream {
  std::ostringstream s;
  template <typename T> AtomicStream &operator<<(const T &t) {
    s << t;
    return *this;
  }
  AtomicStream &operator<<(std::ostream &(*manip)(std::ostream &)) {
    s << manip;
    return *this;
  }
  ~AtomicStream() {
    static std::mutex g;
    std::lock_guard<std::mutex> lock(g);
    CS << s.str();
  }
};
using acout = AtomicStream<std::cout>;
using acerr = AtomicStream<std::cerr>;

template <typename F> auto spawn(std::vector<std::jthread> &pool, F &&f) {
  using R = std::invoke_result_t<F>;

  std::promise<R> prom;
  std::future<R> fut = prom.get_future();

  pool.emplace_back([p = std::move(prom), func = std::forward<F>(f)]() mutable {
    try {
      p.set_value(func());
    } catch (...) {
      p.set_exception(std::current_exception());
    }
  });
  return fut;
}

std::ifstream open_ifstream(const std::filesystem::path &ROOT,
                            const std::string &name, int timestep) {
  const std::filesystem::path datapath =
      ROOT / (name + "." + std::to_string(timestep) + ".data");
  if (!std::filesystem::exists(datapath)) {
    acerr() << "Cannot find: " << datapath << std::endl;
    exit(EXIT_FAILURE);
  }
  acout() << "Reading from: " << datapath << std::endl;
  return std::ifstream{datapath};
}

std::ofstream open_ofstream(const std::filesystem::path &ROOT,
                            const std::string &name, int timestep,
                            const std::string &suffix) {
  const std::filesystem::path datapath(name + "_" + std::to_string(timestep) +
                                       "." + suffix);
  acout() << "Writing to: " << ROOT / datapath << std::endl;
  return std::ofstream{ROOT / datapath};
}

} // namespace standalone_utils

// --- Macro for 'read' function templates ---
// Generates the primary template for read (for classes/arithmetic types)
// and its specialization for global_data_type.
#define GENERATE_READ_FUNCTIONS()                                              \
  template <typename T>                                                        \
  std::enable_if_t<std::is_pointer_v<T>, T> read(                              \
      const std::filesystem::path &ROOT, const std::string &name,              \
      int timestep) {                                                          \
    auto data = open_ifstream(ROOT, name, timestep);                           \
    using Pointee = std::remove_pointer_t<T>;                                  \
    auto result = read_array<Pointee>(data);                                   \
    auto &m = std::get<0>(result);                                             \
    auto &arr = std::get<1>(result);                                           \
    return arr;                                                                \
  }                                                                            \
                                                                               \
  template <typename T>                                                        \
  std::enable_if_t<std::is_class_v<T> || std::is_arithmetic_v<T>, T> read(     \
      const std::filesystem::path &ROOT, const std::string &name,              \
      int timestep) {                                                          \
    auto data = open_ifstream(ROOT, name, timestep);                           \
    T t{};                                                                     \
    deserialize(&t, data);                                                     \
    return t;                                                                  \
  }                                                                            \
                                                                               \
  template <>                                                                  \
  global_data_type read<global_data_type>(const std::filesystem::path &ROOT,   \
                                          const std::string &name,             \
                                          int timestep) {                      \
    auto data = open_ifstream(ROOT, name, timestep);                           \
    global_data_type t{};                                                      \
    deserialize_global_data(&t, data);                                         \
    return t;                                                                  \
  }

// --- Macro for 'got_want_pair' function templates ---
// Generates the two primary templates (pointer and non-pointer)
// and the specialization for global_data_type.
#define GENERATE_GOT_WANT_PAIR_FUNCTIONS()                                     \
  template <typename T>                                                        \
  std::enable_if_t<std::is_pointer_v<T>, void> got_want_pair(                  \
      T got, T want, const std::string &name, int timestep,                    \
      const std::filesystem::path &ROOT) {                                     \
    std::jthread tgot([&] {                                                    \
      open_ofstream(ROOT, name, timestep, "got")                               \
          << serialize_array(got) << std::endl;                                \
    });                                                                        \
    std::jthread twant([&] {                                                   \
      open_ofstream(ROOT, name, timestep, "want")                              \
          << serialize_array(want) << std::endl;                               \
    });                                                                        \
  }                                                                            \
                                                                               \
  template <typename T>                                                        \
  std::enable_if_t<std::is_class_v<T> || std::is_arithmetic_v<T>, void>        \
  got_want_pair(const T &got, const T &want, const std::string &name,          \
                int timestep, const std::filesystem::path &ROOT) {             \
    std::jthread tgot([&] {                                                    \
      open_ofstream(ROOT, name, timestep, "got")                               \
          << serialize(&got) << std::endl;                                     \
    });                                                                        \
    std::jthread twant([&] {                                                   \
      open_ofstream(ROOT, name, timestep, "want")                              \
          << serialize(&want) << std::endl;                                    \
    });                                                                        \
  }                                                                            \
                                                                               \
  template <>                                                                  \
  void got_want_pair(const global_data_type &got,                              \
                     const global_data_type &want, const std::string &name,    \
                     int timestep, const std::filesystem::path &ROOT) {        \
    std::jthread tgot([&] {                                                    \
      open_ofstream(ROOT, name, timestep, "got")                               \
          << serialize_global_data(&got) << std::endl;                         \
    });                                                                        \
    std::jthread twant([&] {                                                   \
      open_ofstream(ROOT, name, timestep, "want")                              \
          << serialize_global_data(&want) << std::endl;                        \
    });                                                                        \
  }

// --- Macro for the t0_t1_pair function template (no specialization needed) ---
#define GENERATE_T0_T1_PAIR_FUNCTION()                                         \
  template <typename T>                                                        \
  std::pair<T, T> t0_t1_pair(const std::filesystem::path &ROOT,                \
                             const std::string &name, int timestep) {          \
    std::vector<std::jthread> pool;                                            \
    /* Using a dummy spawn for example; replace with your actual spawn */      \
    auto ft0 =                                                                 \
        spawn(pool, [&] { return read<T>(ROOT, name + ".t0", timestep); });    \
    auto ft1 =                                                                 \
        spawn(pool, [&] { return read<T>(ROOT, name + ".t1", timestep); });    \
    return {ft0.get(), ft1.get()};                                             \
  }

#define GENERATE_ALL_SERIALIZATION_HELPERS()                                   \
  GENERATE_READ_FUNCTIONS()                                                    \
  GENERATE_T0_T1_PAIR_FUNCTION()                                               \
  GENERATE_GOT_WANT_PAIR_FUNCTIONS()

#endif // __STANDALONE_UTILS_H__
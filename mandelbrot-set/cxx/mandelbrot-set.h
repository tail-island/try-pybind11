#include <cmath>
#include <complex>
#include <generator>
#include <ranges>
#include <vector>

namespace mandelbrot_set {

constexpr auto H = 1024;
constexpr auto W = 1024;

constexpr auto IMAG_MIN = -2.0f;
constexpr auto IMAG_MAX =  2.0f;

constexpr auto REAL_MIN = -2.0f;
constexpr auto REAL_MAX =  2.0f;

inline auto divergence_count(const std::complex<float> &c) noexcept {
  auto z = std::complex(0.0f, 0.0f);

  for (const auto &i : std::views::iota(0, 100)) {
    if (std::abs(z) >= 2) {
      return i;
    }

    z = std::pow(z, 2) + c;
  }

  return 0;
}

inline auto mandelbrot_set() noexcept {
  const auto f = [] -> std::generator<int> {
    for (const auto &imag : std::views::iota(0, H) | std::views::transform([](const auto &y) { return IMAG_MIN + (IMAG_MAX - IMAG_MIN) / (H - 1) * y; })) {
      for (const auto &real : std::views::iota(0, W) | std::views::transform([](const auto &x) { return REAL_MIN + (REAL_MAX - REAL_MIN) / (W - 1) * x; })) {
        co_yield divergence_count(std::complex(real, imag));
      }
    }
  };

  return f() | std::ranges::to<std::vector>();
}

} // namespace mandelbrot_set

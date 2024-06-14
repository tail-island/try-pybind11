#include <cmath>
#include <complex>
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
  auto result = std::vector<int>{};

  result.reserve(H * W);

  for (const auto &i : std::views::iota(0, H)) {
    for (const auto &j : std::views::iota(0, W)) {
      result.emplace_back(divergence_count(std::complex(IMAG_MIN + (IMAG_MAX - IMAG_MIN) / (W - 1) * j,
                                                        REAL_MIN + (REAL_MAX - REAL_MIN) / (H - 1) * i)));
    }
  }

  return result;
}

} // namespace mandelbrot_set

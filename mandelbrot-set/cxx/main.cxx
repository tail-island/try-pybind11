#include <chrono>
#include <iostream>
#include <iterator>
#include <ranges>

#include "mandelbrot-set.h"

template <typename T>
inline auto timeit(T functor) noexcept {
  auto t = static_cast<std::size_t>(0);

  for (const auto &_ : std::views::iota(0, 10)) {
    const auto starting_time = std::chrono::system_clock::now();

    functor();

    t += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - starting_time).count();
  }

  std::cerr << (static_cast<float>(t) / 1'000'000 / 10) << " sec" << std::endl;
}


int main(int argc, char **argv) {
  timeit([] {
    mandelbrot_set::mandelbrot_set();
  });

  const auto mandelbrot_set = mandelbrot_set::mandelbrot_set();

  auto it = std::begin(mandelbrot_set);

  for (auto i = 0; i < mandelbrot_set::H; ++i, it += mandelbrot_set::W) {
    std::copy(it, it + mandelbrot_set::W, std::ostream_iterator<float>(std::cout, "\t"));
    std::cout << std::endl;
  }

  return 0;
}

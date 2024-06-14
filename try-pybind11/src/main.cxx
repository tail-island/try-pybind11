#include <iostream>
#include <iterator>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <range/v3/all.hpp>
#include <vector>

auto add(int x, int y) noexcept {
  return x + y;
}

constexpr auto magic_number = 123;
constexpr auto magic_word = "456";

auto get_range_list(int n) noexcept {
  auto result = std::vector<int>{};

  for (const auto &i : ranges::views::iota(0, n)) {
    result.emplace_back(i);
  }

  return result;
}

// このやり方は駄目。
auto replace_list_value_1(std::vector<int> &vector, int index, int value) noexcept {
  std::copy(std::begin(vector), std::end(vector), std::ostream_iterator<float>(std::cout, "\t"));
  std::cout << std::endl;

  vector[index] = value;

  std::copy(std::begin(vector), std::end(vector), std::ostream_iterator<float>(std::cout, "\t"));
  std::cout << std::endl;
}

// 動くけど、効率が悪い。
auto replace_list_value_2(std::vector<int> &vector, int index, int value) noexcept {
  vector[index] = value;

  return vector;
}

class MyList {
  std::vector<int> vector_;

public:
  MyList(int n) noexcept : vector_{} {
    vector_.reserve(n);

    for (const auto &i : ranges::views::iota(0, n)) {
      vector_.emplace_back(i);
    }
  }

  const auto &vector() const noexcept {
    return vector_;
  }

  auto replace_value(int index, int value) noexcept {
    vector_[index] = value;
  }
};

auto array_sum(const pybind11::array_t<int> &array) noexcept {
  const auto array_ = array.unchecked<2>();  // 2は2次元配列の2。

  auto result = 0;

  for (const auto &i: ranges::views::iota(static_cast<pybind11::ssize_t>(0), array_.shape(0))) {
    for (const auto &j: ranges::views::iota(static_cast<pybind11::ssize_t>(1), array_.shape(0))) {
      result += array_(i, j);
    }
  }

  return result;
}

PYBIND11_MODULE(try_pybind11, module) {
  module.def("add_1", &add);
  module.def("add_2", &add, pybind11::arg("x"), pybind11::arg("y"));
  module.def("add_3", &add, pybind11::arg("x") = 3, pybind11::arg("y") = 4);

  module.attr("magic_number") = magic_number;
  module.attr("magic_word") = magic_word;

  module.def("get_range_list", &get_range_list);

  module.def("replace_list_value_1", &replace_list_value_1);
  module.def("replace_list_value_2", &replace_list_value_2);

  pybind11::class_<MyList>(module, "MyList")
    .def(pybind11::init([](int n) {
      return MyList(n);
    }))
    .def_property_readonly("vector", &MyList::vector)
    .def("replace_value", &MyList::replace_value);

  module.def("array_sum", &array_sum);
}

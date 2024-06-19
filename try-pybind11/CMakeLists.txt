cmake_minimum_required(VERSION 3.18)

project(try_pybind11 LANGUAGES CXX)

find_package(Boost REQUIRED)

include(cmake/pybind11.cmake)

pybind11_add_module(try_pybind11
    src/main.cxx
)

target_compile_features(try_pybind11 PRIVATE
    cxx_std_23
)

target_compile_options(try_pybind11 PRIVATE
    $<$<CXX_COMPILER_ID:GNU>: -flto=auto>
)

target_link_libraries(try_pybind11 PRIVATE
    Boost::headers
    pybind11::headers
)

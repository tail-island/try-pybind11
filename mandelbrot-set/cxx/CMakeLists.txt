cmake_minimum_required(VERSION 3.18)

project(mandelbrot-set LANGUAGES CXX)

add_executable(mandelbrot-set
    main.cxx
    mandelbrot-set.h
)

target_compile_features(mandelbrot-set PRIVATE
    cxx_std_23
)

target_compile_options(mandelbrot-set PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>: /arch:AVX2 /fp:fast>
    $<$<CXX_COMPILER_ID:GNU>: -march=native>
    # $<$<CXX_COMPILER_ID:GNU>: -march=native -ffast-math>
)

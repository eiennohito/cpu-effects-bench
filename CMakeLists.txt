cmake_minimum_required (VERSION 2.8.11)
project (benchmark)

set(BENCHMARK_ENABLE_TESTING OFF)

add_subdirectory(gbench)

add_compile_options("-std=c++14")

add_subdirectory(noopt)
add_subdirectory(opt)


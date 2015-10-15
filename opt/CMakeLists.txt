add_compile_options("-march=native")

include_directories("../gbench/include/")

add_executable(cache cache.cpp)
target_link_libraries(cache benchmark)

add_executable(branches branches.cpp)
target_link_libraries(branches benchmark)
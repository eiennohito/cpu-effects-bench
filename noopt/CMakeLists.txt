
include_directories("../gbench/include/")

set(CMAKE_CXX_FLAGS_RELEASE "-O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O0 -g")

add_executable(superscalar superscalar.cpp)
target_link_libraries(superscalar benchmark)

add_executable(branches noopt/branches.cpp)
target_link_libraries(branches benchmark)
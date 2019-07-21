cmake_minimum_required(VERSION 3.10)

project(mathsmerise LANGUAGES CXX)
set(mm_cmake_dir "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
list(INSERT CMAKE_MODULE_PATH 0 "${mm_cmake_dir}")

include(mmHeaderOnlyLibrary)
# find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_subdirectory(thirdparty/catch2)
add_subdirectory(graph)
add_subdirectory(test)
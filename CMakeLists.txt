cmake_minimum_required(VERSION 3.10)

project(mathsmerise LANGUAGES CXX)

set(cmake_utils_dir "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
list(INSERT CMAKE_MODULE_PATH 0 "${cmake_utils_dir}")

# Use FetchContent to make visible cmake-lemmata contents
# to cmake
include(FetchContent)
FetchContent_Declare(
    cmake-lemmata
    GIT_REPOSITORY https://github.com/PenguinLemma/cmake-lemmata.git
)
FetchContent_GetProperties(cmake-lemmata)
if(NOT cmake-lemmata_POPULATED)
  FetchContent_Populate(cmake-lemmata)
  list(INSERT CMAKE_MODULE_PATH 0 "${cmake_utils_dir}/cmake-lemmata")
endif()

include(libraryAdditionLemma)
include(mathsmeriseCompilerOptions)

add_subdirectory(thirdparty/catch2)
add_subdirectory(graph)
add_subdirectory(test)
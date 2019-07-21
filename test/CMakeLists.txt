set(MM_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graph_test.cpp
)

add_executable(mm_test ${MM_TEST_SOURCES})

target_include_directories(mm_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mm_test
    mm::graph
    Catch2::Catch
)

target_compile_features(mm_test
    PUBLIC cxx_std_17
)

target_compile_options(mm_test
    PRIVATE -Wall -Wextra -Wpedantic -Werror
)
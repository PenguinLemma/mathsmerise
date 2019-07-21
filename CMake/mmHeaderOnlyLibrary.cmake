#[==[.md
# `mmHeaderOnlyLibrary`

This module includes functions to add a header only libraries.

## Usage

This can be called from the CMakeLists.txt on the root dir
of the library. Note that the header we want to have as
header only library must be in ${CMAKE_CURRENT_SOURCE_DIR}/include

```
mm_add_header_only_library(
    <lib-name>
    NAMESPACE <namespace-ended-with::>
    SOURCES <file1> ... <filen>
    LINKED_LIBS <lib1> ... <libn>
)
```

#]==]

function (mm_add_header_only_library name)
    # Parse arguments, notice we are requiring CMake version
    # later than or equal to 3.10, which is later than
    # version 3.5, when `cmake_parse_arguments` was introduced
    # as builtin command (so we don't need to include any
    # module)
    cmake_parse_arguments(_mm_hol
        "" # no option arguments
        "NAMESPACE" # single-value arguments
        "SOURCES;LINKED_LIBS" # multi-value arguments
        ${ARGN}
    )
    add_library(${name} INTERFACE)

    target_include_directories(${name}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )

    target_sources(${name}
        INTERFACE ${_mm_hol_SOURCES}
    )

    target_compile_features(${name}
        INTERFACE cxx_std_17)

    target_link_libraries(${name}
        INTERFACE ${_mm_hol_LINKED_LIBS}
    )

    add_library(${_mm_hol_NAMESPACE}${name}
        ALIAS ${name}
    )

endfunction()
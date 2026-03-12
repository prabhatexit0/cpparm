cmake_minimum_required(VERSION 3.24)
project(cpparm LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Prefer Clang
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(WARNING "This project is designed for Clang. Current compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Optimization flags for release builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
set(CMAKE_ASM_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")

# Keep debug info in RelWithDebInfo for profiling
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG -march=native")

# Fetch dependencies (Google Test + Google Benchmark)
include(cmake/FetchDeps.cmake)

# --- Library: arm_ops (handwritten AArch64 assembly) ---
add_library(arm_ops
    src/arm/memcpy_arm.S
    src/arm/vector_add_arm.S
    src/arm/thunk_arm.S
)
target_include_directories(arm_ops PUBLIC src/include)

# --- Library: stl_ops (STL / C++ implementations) ---
add_library(stl_ops
    src/stl/memcpy_stl.cpp
    src/stl/vector_add_stl.cpp
    src/stl/thunk_stl.cpp
)
target_include_directories(stl_ops PUBLIC src/include)

# --- Tests ---
enable_testing()
add_subdirectory(test)

# --- Benchmarks ---
add_subdirectory(bench)

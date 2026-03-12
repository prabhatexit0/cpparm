#!/bin/bash
set -euo pipefail

PROJECT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"
BUILD_TYPE="${1:-Release}"

echo "=== Building cpparm (${BUILD_TYPE}) ==="

CMAKE="$(command -v cmake || echo /opt/homebrew/bin/cmake)"

"${CMAKE}" -S "${PROJECT_DIR}" -B "${BUILD_DIR}" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DCMAKE_CXX_COMPILER="$(which clang++)" \
    -DCMAKE_C_COMPILER="$(which clang)"

"${CMAKE}" --build "${BUILD_DIR}" --parallel

echo ""
echo "=== Build complete ==="
echo "  Tests:      ${BUILD_DIR}/test/cpparm_tests"
echo "  Benchmarks: ${BUILD_DIR}/bench/cpparm_bench"
echo ""
echo "Run tests:      cd ${BUILD_DIR} && ctest --output-on-failure"
echo "Run benchmarks: ${BUILD_DIR}/bench/cpparm_bench"

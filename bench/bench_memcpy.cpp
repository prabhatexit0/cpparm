#include <benchmark/benchmark.h>
#include <cstdint>
#include <numeric>
#include <vector>

#include "cpparm/arm_ops.h"
#include "cpparm/stl_ops.h"

static void BM_ArmMemcpy(benchmark::State& state) {
    const size_t n = state.range(0);
    std::vector<uint8_t> src(n);
    std::iota(src.begin(), src.end(), 0);
    std::vector<uint8_t> dst(n);

    for (auto _ : state) {
        arm_memcpy(dst.data(), src.data(), n);
        benchmark::DoNotOptimize(dst.data());
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * n);
    state.SetLabel("ARM");
}

static void BM_StlMemcpy(benchmark::State& state) {
    const size_t n = state.range(0);
    std::vector<uint8_t> src(n);
    std::iota(src.begin(), src.end(), 0);
    std::vector<uint8_t> dst(n);

    for (auto _ : state) {
        stl_ops::stl_memcpy(dst.data(), src.data(), n);
        benchmark::DoNotOptimize(dst.data());
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * n);
    state.SetLabel("STL");
}

// Register benchmarks with various sizes: 64B -> 16MB
BENCHMARK(BM_ArmMemcpy)->RangeMultiplier(4)->Range(64, 1 << 24);
BENCHMARK(BM_StlMemcpy)->RangeMultiplier(4)->Range(64, 1 << 24);

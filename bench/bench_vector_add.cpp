#include <benchmark/benchmark.h>
#include <numeric>
#include <vector>

#include "cpparm/arm_ops.h"
#include "cpparm/stl_ops.h"

static void BM_ArmVectorAdd(benchmark::State& state) {
    const size_t n = state.range(0);
    std::vector<float> a(n), b(n), dst(n);
    std::iota(a.begin(), a.end(), 1.0f);
    std::iota(b.begin(), b.end(), 100.0f);

    for (auto _ : state) {
        arm_vector_add_f32(dst.data(), a.data(), b.data(), n);
        benchmark::DoNotOptimize(dst.data());
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * n * sizeof(float) * 3);
    state.SetLabel("ARM NEON");
}

static void BM_StlVectorAdd(benchmark::State& state) {
    const size_t n = state.range(0);
    std::vector<float> a(n), b(n), dst(n);
    std::iota(a.begin(), a.end(), 1.0f);
    std::iota(b.begin(), b.end(), 100.0f);

    for (auto _ : state) {
        stl_ops::stl_vector_add_f32(dst.data(), a.data(), b.data(), n);
        benchmark::DoNotOptimize(dst.data());
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * n * sizeof(float) * 3);
    state.SetLabel("STL transform");
}

// Raw loop for comparison — lets the compiler auto-vectorize
static void BM_RawLoopVectorAdd(benchmark::State& state) {
    const size_t n = state.range(0);
    std::vector<float> a(n), b(n), dst(n);
    std::iota(a.begin(), a.end(), 1.0f);
    std::iota(b.begin(), b.end(), 100.0f);

    for (auto _ : state) {
        for (size_t i = 0; i < n; ++i) {
            dst[i] = a[i] + b[i];
        }
        benchmark::DoNotOptimize(dst.data());
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * n * sizeof(float) * 3);
    state.SetLabel("Raw loop");
}

BENCHMARK(BM_ArmVectorAdd)->RangeMultiplier(4)->Range(16, 1 << 20);
BENCHMARK(BM_StlVectorAdd)->RangeMultiplier(4)->Range(16, 1 << 20);
BENCHMARK(BM_RawLoopVectorAdd)->RangeMultiplier(4)->Range(16, 1 << 20);

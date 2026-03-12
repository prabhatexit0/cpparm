#include <benchmark/benchmark.h>
#include <cstdint>
#include <functional>

#include "cpparm/arm_ops.h"
#include "cpparm/stl_ops.h"

static uint64_t increment(uint64_t x) {
    return x + 1;
}

// --- ARM assembly thunk: minimal indirect call ---
static void BM_ArmThunk(benchmark::State& state) {
    uint64_t val = 0;
    for (auto _ : state) {
        val = arm_thunk_call(increment, val);
        benchmark::DoNotOptimize(val);
    }
}

// --- C++ function pointer (compiler-generated indirect call) ---
static void BM_FnPtrThunk(benchmark::State& state) {
    uint64_t val = 0;
    for (auto _ : state) {
        val = stl_ops::fnptr_call(increment, val);
        benchmark::DoNotOptimize(val);
    }
}

// --- std::function (type-erased, heap-possible thunk) ---
static void BM_StdFunctionThunk(benchmark::State& state) {
    std::function<uint64_t(uint64_t)> fn = increment;
    uint64_t val = 0;
    for (auto _ : state) {
        val = stl_ops::std_function_call(fn, val);
        benchmark::DoNotOptimize(val);
    }
}

// --- Virtual dispatch thunk ---
static void BM_VirtualThunk(benchmark::State& state) {
    auto callable = stl_ops::CallableImpl<uint64_t(*)(uint64_t)>(increment);
    uint64_t val = 0;
    for (auto _ : state) {
        val = stl_ops::virtual_call(callable, val);
        benchmark::DoNotOptimize(val);
    }
}

// --- Direct call baseline (no indirection at all) ---
static void BM_DirectCall(benchmark::State& state) {
    uint64_t val = 0;
    for (auto _ : state) {
        val = increment(val);
        benchmark::DoNotOptimize(val);
    }
}

BENCHMARK(BM_DirectCall);
BENCHMARK(BM_ArmThunk);
BENCHMARK(BM_FnPtrThunk);
BENCHMARK(BM_StdFunctionThunk);
BENCHMARK(BM_VirtualThunk);

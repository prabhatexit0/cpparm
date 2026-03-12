#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>

namespace stl_ops {

// STL memcpy wrapper
void stl_memcpy(void* dst, const void* src, size_t n);

// STL-style vector add using std::transform
void stl_vector_add_f32(float* dst, const float* a, const float* b, size_t n);

// std::function-based indirect call (heavy thunk)
uint64_t std_function_call(const std::function<uint64_t(uint64_t)>& fn, uint64_t arg);

// Function pointer call (C++ baseline for thunk comparison)
uint64_t fnptr_call(uint64_t (*fn)(uint64_t), uint64_t arg);

// Virtual dispatch thunk via base class
struct ICallable {
    virtual uint64_t call(uint64_t arg) = 0;
    virtual ~ICallable() = default;
};

template <typename F>
struct CallableImpl : ICallable {
    F fn;
    explicit CallableImpl(F f) : fn(std::move(f)) {}
    uint64_t call(uint64_t arg) override { return fn(arg); }
};

uint64_t virtual_call(ICallable& callable, uint64_t arg);

} // namespace stl_ops

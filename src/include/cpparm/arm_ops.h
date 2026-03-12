#pragma once
#include <cstddef>
#include <cstdint>

extern "C" {

// Hand-written AArch64 memcpy: copies n bytes from src to dst
void arm_memcpy(void* dst, const void* src, size_t n);

// Hand-written AArch64 NEON vector add: dst[i] = a[i] + b[i], for n floats
void arm_vector_add_f32(float* dst, const float* a, const float* b, size_t n);

// Hand-written AArch64 thunk: calls a function pointer through an indirect branch
// Used to measure indirect call overhead
uint64_t arm_thunk_call(uint64_t (*fn)(uint64_t), uint64_t arg);

}

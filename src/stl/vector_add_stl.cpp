#include "cpparm/stl_ops.h"
#include <algorithm>

namespace stl_ops {

void stl_vector_add_f32(float* dst, const float* a, const float* b, size_t n) {
    std::transform(a, a + n, b, dst, std::plus<float>{});
}

} // namespace stl_ops

#include "cpparm/stl_ops.h"
#include <algorithm>
#include <cstring>

namespace stl_ops {

void stl_memcpy(void* dst, const void* src, size_t n) {
    std::memcpy(dst, src, n);
}

} // namespace stl_ops

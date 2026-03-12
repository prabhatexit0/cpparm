#include "cpparm/stl_ops.h"

namespace stl_ops {

uint64_t std_function_call(const std::function<uint64_t(uint64_t)>& fn, uint64_t arg) {
    return fn(arg);
}

uint64_t fnptr_call(uint64_t (*fn)(uint64_t), uint64_t arg) {
    return fn(arg);
}

uint64_t virtual_call(ICallable& callable, uint64_t arg) {
    return callable.call(arg);
}

} // namespace stl_ops

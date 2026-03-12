#include <gtest/gtest.h>
#include <cstdint>

#include "cpparm/arm_ops.h"
#include "cpparm/stl_ops.h"

static uint64_t double_it(uint64_t x) {
    return x * 2;
}

static uint64_t add_42(uint64_t x) {
    return x + 42;
}

TEST(ThunkTest, ArmThunkCallsCorrectly) {
    EXPECT_EQ(arm_thunk_call(double_it, 5), 10u);
    EXPECT_EQ(arm_thunk_call(double_it, 0), 0u);
    EXPECT_EQ(arm_thunk_call(add_42, 0), 42u);
    EXPECT_EQ(arm_thunk_call(add_42, 100), 142u);
}

TEST(ThunkTest, FnPtrCallMatchesArm) {
    EXPECT_EQ(stl_ops::fnptr_call(double_it, 21), arm_thunk_call(double_it, 21));
    EXPECT_EQ(stl_ops::fnptr_call(add_42, 58), arm_thunk_call(add_42, 58));
}

TEST(ThunkTest, StdFunctionCallMatchesArm) {
    std::function<uint64_t(uint64_t)> fn = double_it;
    EXPECT_EQ(stl_ops::std_function_call(fn, 7), arm_thunk_call(double_it, 7));
}

TEST(ThunkTest, VirtualCallMatchesArm) {
    auto callable = stl_ops::CallableImpl<uint64_t(*)(uint64_t)>(double_it);
    EXPECT_EQ(stl_ops::virtual_call(callable, 11), arm_thunk_call(double_it, 11));
}

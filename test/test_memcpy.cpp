#include <gtest/gtest.h>
#include <cstdint>
#include <numeric>
#include <vector>

#include "cpparm/arm_ops.h"
#include "cpparm/stl_ops.h"

class MemcpyTest : public ::testing::TestWithParam<size_t> {};

TEST_P(MemcpyTest, ArmMatchesStl) {
    const size_t n = GetParam();
    std::vector<uint8_t> src(n);
    std::iota(src.begin(), src.end(), 0);

    std::vector<uint8_t> dst_arm(n, 0);
    std::vector<uint8_t> dst_stl(n, 0);

    arm_memcpy(dst_arm.data(), src.data(), n);
    stl_ops::stl_memcpy(dst_stl.data(), src.data(), n);

    EXPECT_EQ(dst_arm, dst_stl);
}

TEST_P(MemcpyTest, ArmCopiesCorrectly) {
    const size_t n = GetParam();
    std::vector<uint8_t> src(n);
    std::iota(src.begin(), src.end(), 42);

    std::vector<uint8_t> dst(n, 0);
    arm_memcpy(dst.data(), src.data(), n);

    EXPECT_EQ(dst, src);
}

INSTANTIATE_TEST_SUITE_P(
    Sizes, MemcpyTest,
    ::testing::Values(0, 1, 7, 15, 16, 31, 32, 63, 64, 100, 256, 1024, 4096, 65536)
);

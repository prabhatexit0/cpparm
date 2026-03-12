#include <gtest/gtest.h>
#include <cmath>
#include <numeric>
#include <vector>

#include "cpparm/arm_ops.h"
#include "cpparm/stl_ops.h"

class VectorAddTest : public ::testing::TestWithParam<size_t> {};

TEST_P(VectorAddTest, ArmMatchesStl) {
    const size_t n = GetParam();
    std::vector<float> a(n), b(n);
    std::iota(a.begin(), a.end(), 1.0f);
    std::iota(b.begin(), b.end(), 100.0f);

    std::vector<float> dst_arm(n, 0.0f);
    std::vector<float> dst_stl(n, 0.0f);

    arm_vector_add_f32(dst_arm.data(), a.data(), b.data(), n);
    stl_ops::stl_vector_add_f32(dst_stl.data(), a.data(), b.data(), n);

    for (size_t i = 0; i < n; ++i) {
        EXPECT_FLOAT_EQ(dst_arm[i], dst_stl[i]) << "Mismatch at index " << i;
    }
}

TEST_P(VectorAddTest, ArmProducesCorrectResults) {
    const size_t n = GetParam();
    std::vector<float> a(n, 1.5f);
    std::vector<float> b(n, 2.5f);
    std::vector<float> dst(n, 0.0f);

    arm_vector_add_f32(dst.data(), a.data(), b.data(), n);

    for (size_t i = 0; i < n; ++i) {
        EXPECT_FLOAT_EQ(dst[i], 4.0f) << "Mismatch at index " << i;
    }
}

INSTANTIATE_TEST_SUITE_P(
    Sizes, VectorAddTest,
    ::testing::Values(0, 1, 3, 4, 7, 8, 15, 16, 17, 32, 64, 100, 1024)
);

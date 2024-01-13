#ifndef TESTS_COMMON_HPP
#define TESTS_COMMON_HPP

#include <gtest/gtest.h>

#include "Maths.hpp"

#define ABS_ERROR 0.001f

inline void EXPECT_EQ_VEC4(const Vec4& vec, const float x, const float y, const float z, const float w)
{
    EXPECT_NEAR(vec.x, x, ABS_ERROR);
    EXPECT_NEAR(vec.y, y, ABS_ERROR);
    EXPECT_NEAR(vec.z, z, ABS_ERROR);
    EXPECT_NEAR(vec.w, w, ABS_ERROR);
}

inline void EXPECT_EQ_VEC3(const Vec3& vec, const float x, const float y, const float z)
{
    EXPECT_NEAR(vec.x, x, ABS_ERROR);
    EXPECT_NEAR(vec.y, y, ABS_ERROR);
    EXPECT_NEAR(vec.z, z, ABS_ERROR);
}

#endif // TESTS_COMMON_HPP
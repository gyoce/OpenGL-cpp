#include "TestsCommon.hpp"

TEST(Vec3, Vec3Construction)
{
    Vec3 vec{ 1.0f, 2.0f, 3.0f };
    EXPECT_EQ_VEC3(vec, 1.0f, 2.0f, 3.0f);
}

TEST(Vec3, Vec3Multiplication)
{
    Vec3 vec{ 1.0f, 2.0f, 3.0f };
    Vec3 vecResult = vec * 3.0f;
    EXPECT_EQ_VEC3(vecResult, 3.0f, 6.0f, 9.0f);
}

TEST(Vec3, Vec3Addition)
{
    Vec3 vec1{ 1.0f, 2.0f, 3.0f };
    Vec3 vec2{ 4.0f, 5.0f, 6.0f };
    Vec3 vecResult = vec1 + vec2;
    EXPECT_EQ_VEC3(vecResult, 5.0f, 7.0f, 9.0f);

    vec1 += vec2;
    EXPECT_EQ_VEC3(vec1, 5.0f, 7.0f, 9.0f);
}

TEST(Vec3, Vec3Length)
{
    Vec3 vec{ 4.0f, 0.0f, 3.0f };
    float length = vec.Length();
    EXPECT_EQ(length, 5.0f);
}

TEST(Vec3, Vec3Normalize)
{
    Vec3 vec{ 3.0f, 0.0f, 4.0f };
    Vec3 vnorm = vec.Normalize();
    EXPECT_EQ_VEC3(vnorm, 3.0f / 5.0f, 0.0f, 4.0f / 5.0f);
}

TEST(Vec3, Vec3NormalizedLength)
{
    Vec3 vec{ 1.0f, 3.0f, 7.0f };
    Vec3 vnorm = vec.Normalize();
    float length = vnorm.Length();
    EXPECT_EQ(length, 1.0f);
}
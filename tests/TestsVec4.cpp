#include "TestsCommon.hpp"

TEST(Vec4, Vec4Construction)
{
    Vec4 vec{ 1.0f, 2.0f, 3.0f, 4.0f };
    EXPECT_EQ_VEC4(vec, 1.0f, 2.0f, 3.0f, 4.0f);
}

TEST(Vec4, Vec4Multiplication)
{
    Vec4 vec{ 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4 vecResult = vec * 3.0f;
    EXPECT_EQ_VEC4(vecResult, 3.0f, 6.0f, 9.0f, 12.0f);
}

TEST(Vec4, Vec4Addition)
{
    Vec4 vec1{ 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4 vec2{ 4.0f, 5.0f, 6.0f, 7.0f };
    Vec4 vecResult = vec1 + vec2;
    EXPECT_EQ_VEC4(vecResult, 5.0f, 7.0f, 9.0f, 11.0f);

    vec1 += vec2;
    EXPECT_EQ_VEC4(vec1, 5.0f, 7.0f, 9.0f, 11.0f);
}

TEST(Vec4, Vec4Length)
{
    Vec4 vec{ 4.0f, 2.0f, 3.0f, 1.0f };
    float length = vec.Length();
    EXPECT_EQ(length, sqrt(30.0f));
}

TEST(Vec4, Vec4Normalize)
{
    Vec4 vec{ 3.0f, 1.0f, 4.0f, 2.0f };
    Vec4 vnorm = vec.Normalize();
    float length = sqrt(30.0f);
    EXPECT_EQ_VEC4(vnorm, 3.0f / length, 1.0f / length, 4.0f / length, 2.0f / length);
}

TEST(Vec4, Vec4NormalizedLength)
{
    Vec4 vec{ 1.0f, 3.0f, 7.0f, 2.0f };
    Vec4 vnorm = vec.Normalize();
    float length = vnorm.Length();
    EXPECT_EQ(length, 1.0f);
}
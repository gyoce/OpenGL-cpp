#include "TestsCommon.hpp"

TEST(Mat4, Mat4Identity)
{
    Mat4 mat = Mat4{ 2.0f };
    EXPECT_EQ_VEC4(mat[0], 2.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ_VEC4(mat[1], 0.0f, 2.0f, 0.0f, 0.0f);
    EXPECT_EQ_VEC4(mat[2], 0.0f, 0.0f, 2.0f, 0.0f);
    EXPECT_EQ_VEC4(mat[3], 0.0f, 0.0f, 0.0f, 2.0f);
}

TEST(Mat4, Mat4TranslateVec3)
{
    Mat4 mat{};
    mat[0].x = 1.0f; mat[1].x = 0.0f; mat[2].x = 1.0f; mat[3].x = 5.0f;
    mat[0].y = 2.0f; mat[1].y = 1.0f; mat[2].y = 0.0f; mat[3].y = 0.0f;
    mat[0].z = 3.0f; mat[1].z = 0.0f; mat[2].z = 1.0f; mat[3].z = 0.0f;
    mat[0].w = 4.0f; mat[1].w = 1.0f; mat[2].w = 1.0f; mat[3].w = 5.0f;

    Vec3 v = Vec3{ 2.0f, 3.0f, 0.0f };
    Mat4 matRes = mat.Translate(v);

    EXPECT_EQ_VEC4(matRes[0], 1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_EQ_VEC4(matRes[1], 0.0f, 1.0f, 0.0f, 1.0f);
    EXPECT_EQ_VEC4(matRes[2], 1.0f, 0.0f, 1.0f, 1.0f);
    EXPECT_EQ_VEC4(matRes[3], 7.0f, 7.0f, 6.0f, 16.0f);
}

TEST(Mat4, Mat4RotateVec3)
{
    Mat4 mat{};
    mat[0].x = 1.0f; mat[1].x = 0.0f; mat[2].x = 1.0f; mat[3].x = 5.0f;
    mat[0].y = 2.0f; mat[1].y = 1.0f; mat[2].y = 0.0f; mat[3].y = 0.0f;
    mat[0].z = 3.0f; mat[1].z = 0.0f; mat[2].z = 1.0f; mat[3].z = 0.0f;
    mat[0].w = 4.0f; mat[1].w = 1.0f; mat[2].w = 1.0f; mat[3].w = 5.0f;

    Vec3 v = Vec3{ 2.0f, 3.0f, 1.0f };
    float nightyDegreesInRadians = 1.5708f;
    Mat4 matRes = mat.Rotate(nightyDegreesInRadians, v);

    EXPECT_EQ_VEC4(matRes[0], -0.373212f, 1.26726f, 0.198216f, 1.17976f);
    EXPECT_EQ_VEC4(matRes[1], 0.910118f, 0.965477f, 1.23274f, 2.03691f);
    EXPECT_EQ_VEC4(matRes[2], 1.01607f, 1.56904f, 2.90535f, 3.52976f);
    EXPECT_EQ_VEC4(matRes[3], 5.0f, 0.0f, 0.0f, 5.0f);
}
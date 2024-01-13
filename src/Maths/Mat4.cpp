#include "Mat4.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

Mat4::Mat4(const Mat4& m)
{
    col[0] = m.col[0];
    col[1] = m.col[1];
    col[2] = m.col[2];
    col[3] = m.col[3];
}

Mat4::Mat4(const float a)
{
    col[0].x = a;
    col[1].y = a;
    col[2].z = a;
    col[3].w = a;
}

Mat4 Mat4::Translate(const Vec3& v) const
{
    Mat4 mat = { *this };
    mat[3] = mat[0] * v.x + mat[1] * v.y + mat[2] * v.z + mat[3];
    return mat;
}

Mat4 Mat4::Rotate(const float angle, const Vec3& v) const
{
    const float c = cos(angle);
    const float s = sin(angle);
    const Vec3 vnorm = v.Normalize();
    const float tmp = 1 - c;

    Mat4 rotate;
    rotate[0] = Vec4{ c + vnorm.x * vnorm.x * tmp, vnorm.y * vnorm.x * tmp + vnorm.z * s, vnorm.z * vnorm.x * tmp - vnorm.y * s, 0 };
    rotate[1] = Vec4{ vnorm.x * vnorm.y * tmp - vnorm.z * s, c + vnorm.y * vnorm.y * tmp, vnorm.z * vnorm.y * tmp + vnorm.x * s, 0 };
    rotate[2] = Vec4{ vnorm.x * vnorm.z * tmp + vnorm.y * s, vnorm.y * vnorm.z * tmp - vnorm.x * s, c + vnorm.z * vnorm.z * tmp, 0 };
    rotate[3] = Vec4{ 0, 0, 0, 1 };

    Mat4 res;
    res[0] = col[0] * rotate[0].x + col[1] * rotate[0].y + col[2] * rotate[0].z;
    res[1] = col[0] * rotate[1].x + col[1] * rotate[1].y + col[2] * rotate[1].z;
    res[2] = col[0] * rotate[2].x + col[1] * rotate[2].y + col[2] * rotate[2].z;
    res[3] = col[3];
    return res; 
}

const GLfloat* Mat4::ValuePtr() const
{
    return &col[0].x;
}

Vec4& Mat4::operator[](const int index)
{
    assert(index >= 0 && index <= 3 && "Mat4 index need to between 0 and 3");
    return col[index];
}

void Mat4::Print() const
{
    std::cout << "[" << "\n";
    std::cout << "  " << col[0].x << " " << col[1].x << " " << col[2].x << " " << col[3].x << "\n";
    std::cout << "  " << col[0].y << " " << col[1].y << " " << col[2].y << " " << col[3].y << "\n";
    std::cout << "  " << col[0].z << " " << col[1].z << " " << col[2].z << " " << col[3].z << "\n";
    std::cout << "  " << col[0].w << " " << col[1].w << " " << col[2].w << " " << col[3].w << "\n";
    std::cout << "]\n";
}
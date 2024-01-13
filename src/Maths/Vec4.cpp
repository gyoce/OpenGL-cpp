#include "Vec4.hpp"

#include <cmath>

Vec4::Vec4()
    : x(0), y(0), z(0), w(0) {  }

Vec4::Vec4(const float x, const float y, const float z, const float w)
    : x(x), y(y), z(z), w(w) {  }

Vec4 Vec4::operator*(const float a) const
{
    return Vec4{ x * a, y * a, z * a, w * a };
}

Vec4 Vec4::operator+(const Vec4& other) const
{
    return Vec4{ x + other.x, y + other.y, z + other.z, w + other.w };
}

Vec4& Vec4::operator+=(const Vec4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

float Vec4::Length() const
{
    return sqrt(x * x + y * y + z * z + w * w);
}

Vec4 Vec4::Normalize() const
{
    const float length = Length();
    return Vec4{ x / length, y / length, z / length, w / length };
}
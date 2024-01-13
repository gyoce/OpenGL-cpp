#include "Vec3.hpp"

#include <cmath>

Vec3::Vec3(const float x, const float y, const float z)
    : x(x), y(y), z(z) {  }

Vec3 Vec3::operator*(const float a) const
{
    return Vec3{ x * a, y * a, z * a };
}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3{ x + other.x, y + other.y, z + other.z };
}

Vec3& Vec3::operator+=(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

float Vec3::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::Normalize() const
{
    const float length = Length();
    return Vec3{ x / length, y / length, z / length };
}
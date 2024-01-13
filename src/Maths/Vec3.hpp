#ifndef VEC3_HPP
#define VEC3_HPP

struct Vec3
{
    Vec3(float x, float y, float z);

    Vec3 operator*(float a) const;
    Vec3 operator+(const Vec3& other) const;
    Vec3& operator+=(const Vec3& other);

    float Length() const;
    Vec3 Normalize() const;

    float x, y, z;
};

#endif // VEC3_HPP
#ifndef VEC4_HPP
#define VEC4_HPP

struct Vec4
{
    Vec4();
    Vec4(float x, float y, float z, float w);

    Vec4 operator*(float a) const;
    Vec4 operator+(const Vec4& other) const;
    Vec4& operator+=(const Vec4& other);

    float Length() const;
    Vec4 Normalize() const;

    float x, y, z, w;
};

#endif // VEC4_HPP
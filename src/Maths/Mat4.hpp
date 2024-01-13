#ifndef MAT4_HPP
#define MAT4_HPP

#include "Vec4.hpp"
#include "Vec3.hpp"
#include "glad/glad.h"

class Mat4
{
public:
    Mat4() = default;
    Mat4(const Mat4& m);
    Mat4(float a);

    Mat4 Translate(const Vec3& v) const;
    Mat4 Rotate(float angle, const Vec3& v) const;

    const GLfloat* ValuePtr() const;

    Vec4& operator[](int index);

    void Print() const;

private:
    Vec4 col[4]{};
};

#endif // MAT4_HPP
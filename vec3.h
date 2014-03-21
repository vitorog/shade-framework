#ifndef VEC3_H
#define VEC3_H

class Vec3
{
public:
    Vec3();
    Vec3(float x, float y, float z);
    float Magnitude();
    void Normalize();
    void operator=(const Vec3&);
    Vec3 operator+(const Vec3&);
    Vec3 operator-(const Vec3&);
    Vec3 operator*(const float);
    Vec3 operator*(const Vec3&);
    float Dot(const Vec3&);
    Vec3 Cross(const Vec3&);
    float x_;
    float y_;
    float z_;
};

#endif // VEC3_H

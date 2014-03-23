#include "vec3.h"

#include <cmath>

Vec3::Vec3() :
    x_(0),
    y_(0),
    z_(0)
{
}

Vec3::Vec3(float x, float y, float z) :
    x_(x),
    y_(y),
    z_(z)
{
}

float Vec3::Magnitude()
{
    return sqrt(x_*x_ + y_*y_ + z_*z_);
}

void Vec3::Normalize()
{
    float mag = Magnitude();
    x_ /= mag;
    y_ /= mag;
    z_ /= mag;
}

void Vec3::operator =(const Vec3 &b)
{
    x_ = b.x_;
    y_ = b.y_;
    z_ = b.z_;
}

Vec3 Vec3::operator +(const Vec3 &b)
{
    Vec3 result;
    result.x_ = x_ + b.x_;
    result.y_ = y_ + b.y_;
    result.z_ = z_ + b.z_;
    return result;
}

Vec3 Vec3::operator -(const Vec3 &b)
{
    Vec3 result;
    result.x_ = x_ - b.x_;
    result.y_ = y_ - b.y_;
    result.z_ = z_ - b.z_;
    return result;
}

Vec3 Vec3::operator *(const float b)
{
    Vec3 result;
    result.x_ = x_*b;
    result.y_ = y_*b;
    result.z_ = z_*b;
    return result;
}

Vec3 Vec3::operator*(const Vec3 &b)
{
    Vec3 result;
    result.x_ = x_*b.x_;
    result.y_ = y_*b.y_;
    result.z_ = z_*b.z_;
    return result;
}

float Vec3::Dot(const Vec3 &b)
{
    return x_*b.x_ + y_*b.y_ + z_*b.z_;
}

Vec3 Vec3::Cross(const Vec3 &b)
{
    Vec3 result;
    result.x_ = y_*b.z_ - z_*b.y_;
    result.y_ = x_*b.z_ - z_*b.x_;
    result.z_ = x_*b.y_ - y_*b.x_;
    return result;
}

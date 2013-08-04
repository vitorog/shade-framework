#include "point3.h"

Point3::Point3() :
    x_(0),
    y_(0),
    z_(0)
{
}

Point3::Point3(float x, float y, float z) :
    x_(x),
    y_(y),
    z_(z)
{
}

Vec3 Point3::operator -(const Point3 &b)
{
    Vec3 result;
    result.x_ = x_ - b.x_;
    result.y_ = y_ - b.y_;
    result.z_ = z_ - b.z_;
    return result;
}

Point3 Point3::operator +(const Vec3 &b)
{
    Point3 result;
    result.x_ = x_ + b.x_;
    result.y_ = y_ + b.y_;
    result.z_ = z_ + b.z_;
    return result;
}

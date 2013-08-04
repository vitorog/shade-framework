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
    result.x_ = b.x_ - x_;
    result.y_ = b.y_ - y_;
    result.z_ = b.z_ - z_;
    return result;
}

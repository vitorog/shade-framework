#ifndef POINT3_H
#define POINT3_H

#include "vec3.h"

class Point3
{
public:
    Point3();
    Point3(float x, float y, float z);
    Vec3 operator-(const Point3&);
    float x_;
    float y_;
    float z_;
};

#endif // POINT3_H

#include "camera.h"

#include <cmath>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

Camera::Camera()
{

}

Camera::Camera(glm::vec3 position, glm::vec3 view_direction, glm::vec3 up_direction) :
    position_(position),
    view_direction_(view_direction),
    up_direction_(up_direction)
{
    w_ = glm::normalize(view_direction_ * (-1.0f));
    u_ = glm::normalize(glm::cross(view_direction_,up_direction_));
    v_ = glm::normalize(up_direction_);

    left_ = -1.0f;
    right_ = 1.0f;
    bottom_ = -1.0f;
    top_  = 1.0f;
    num_x_ = 640;
    num_y_ = 640;
    plane_distance_ = 1.0f;
    fov_x_ = 45.0f;
    fov_y_ = 45.0f;

//    fov_x_ = 180.0f;
//    fov_y_ = 90.0f;
//    float half_fov_x = fov_x_ / 2.0f;
//    float half_fov_y = fov_y_ / 2.0f;
//    left_ = - tan(half_fov_x)*plane_distance_;
//    right_ = tan(half_fov_x)*plane_distance_;
//    top_ =  tan(half_fov_y)*plane_distance_;
//    bottom_ = - tan(half_fov_y)*plane_distance_;
}

glm::vec3 Camera::GetPixelCoordinates(int i, int j)
{
    float u = ((left_ + (right_ - left_)*(i+0.5)) / num_x_);
    float v = ((bottom_ + (top_ - bottom_)*(j+0.5)) / num_y_);
    return glm::vec3(u,v,0);
}

glm::vec3 Camera::GetScreenPlanePoint(int i, int j)
{

    glm::vec3 xy_coords = GetPixelCoordinates(i, j);
    glm::vec3 point = (u_ * xy_coords.x) + (v_ * xy_coords.y) + (position_ + (view_direction_ * plane_distance_));
    return point;
}

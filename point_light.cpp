#include "point_light.h"

PointLight::PointLight()
{
}

PointLight::PointLight(glm::vec3 position, Material material) :
    position_(position),
    material_(material)
{
}

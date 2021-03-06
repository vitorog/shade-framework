#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm/glm.hpp"

#include "utils.h"
#include "texture2d.h"


class Material
{
public:
    Material();
    std::string name_;
    glm::vec3 ka_;
    glm::vec3 kd_;
    glm::vec3 ks_;
    float tr_;
    float ns_;
    int illum_;
    Texture2D map_kd_;
//    std::string map_kd_;
};

#endif // MATERIAL_H

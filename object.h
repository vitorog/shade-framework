#ifndef OBJECT_H
#define OBJECT_H


#include "material.h"
#include "mesh.h"

class Object
{
public:
    Object();
    Object(glm::vec3 position);
    glm::vec3 position_;
    Mesh *mesh_;
    Material *material_;
};

#endif // OBJECT_H

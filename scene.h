#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "camera.h"
#include "object.h"
#include "point_light.h"

class Scene
{
public:
    Scene();
    PointLight *light_;
    std::vector<Object*> objects_;    
    Camera *camera_;
};

#endif // SCENE_H

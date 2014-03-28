#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <map>
#include <glm/glm.hpp>

#include "utils.h"
#include "material.h"

class Object;

class OBJLoader
{
public:
    OBJLoader();
    Object* Load(const std::string &path); //TODO: Add support to multiple objects loading
private:
    Material* LoadMTL(const std::string &path);
    std::string obj_file_dir_;
};

#endif // SCENELOADER_H

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
    std::vector<Object*> Load(const std::string &path);
private:
    std::map<std::string, Material*> LoadMTL(const std::string &path);
    std::string obj_file_dir_;
};

#endif // SCENELOADER_H

#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <map>
#include <glm/glm.hpp>

#include "utils.h"
#include "material.h"

class SceneLoader
{
public:
    SceneLoader();
    int Load(const std::string &path);

//private:
    bool tri_faces_;
    glm::vec3 center_;
    std::vector<glm::vec3> vertices_;
    std::vector<glm::vec3> normals_;
    std::vector<glm::vec2> text_coords_;
    std::vector<int> vertices_index_;
    std::vector<int> normals_index_;
    std::vector<int> text_coords_index_;
    std::map<std::string, int> materials_id_;
    std::vector<Material> materials_;
    std::string scene_dir_;
    bool has_texture_;
};

#endif // SCENELOADER_H

#include "obj_loader.h"

#include <iostream>
#include <fstream>
#include <cmath>

#include "debug.h"
#include "mesh.h"
#include "object.h"

OBJLoader::OBJLoader()
{
}

std::vector<Object*> OBJLoader::Load(const std::string &path)
{
    std::vector<Object*> objects;
    Object *curr_obj = NULL;
    Mesh *curr_mesh = NULL;
    std::map<std::string, Material*> materials;

    double min_x=0,min_y=0,min_z=0,max_x=0,max_y=0,max_z=0;
    int ret = 0;    
    int vertex_index_shift = 0;
    int normal_index_shift = 0;
    int tex_coords_index_shift = 0;
    std::ifstream file(path.c_str());
    if(file.is_open()){
        std::string line;
        while( std::getline(file, line) ){
            std::vector<std::string> tokens = Split(line, ' ');
            if(!tokens.empty()){
                std::string line_id = tokens.at(0);
                tokens.erase(tokens.begin());
                //Material file line
                if( line_id == "mtllib" ){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    obj_file_dir_ = GetFilePath(path);
                    std::string material_path;
                    material_path.append(obj_file_dir_);
                    material_path.append(tokens.at(0));
                    materials = LoadMTL(material_path);
                    if(materials.empty()){
                        ret = -1;
                        break;
                    }
                }
                //New object
                if( line_id == "o" ){
                    if(tokens.size() != 1){
                        ret = -1;
                        break;
                    }
                    if(curr_obj != NULL){
                        vertex_index_shift += curr_mesh->vertices_.size();
                        normal_index_shift += curr_mesh->normals_.size();
                        tex_coords_index_shift += curr_mesh->text_coords_.size();
                    }
                    curr_obj = new Object();
                    curr_mesh = new Mesh();
                    curr_obj->mesh_ = curr_mesh;
                    objects.push_back(curr_obj);

                }                
                //Material setting line
                if( line_id == "usemtl"){
                    if(tokens.size() != 1){
                        ret = -1;
                        break;
                    }
                    curr_obj->material_ = materials[tokens.at(0)];
                }
                //Vertice line
                if( line_id == "v" ){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    double x = atof(tokens.at(0).c_str());
                    double y = atof(tokens.at(1).c_str());
                    double z = atof(tokens.at(2).c_str());
                    if(x <= min_x){
                        min_x = x;
                    }
                    if(x >= max_x){
                        max_x = x;
                    }
                    if(y <= min_y){
                        min_y = y;
                    }
                    if(y >= max_y){
                        max_y = y;
                    }
                    if(z <= min_z){
                        min_z = z;
                    }
                    if(z >= max_z){
                        max_z = max_z;
                    }

                    glm::vec3 vertice((float)x,(float)y,(float)z);
                    curr_mesh->vertices_.push_back(vertice);
                }
                //Vertice normal line
                if( line_id == "vn" ){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    glm::vec3 normal(atof(tokens.at(0).c_str()),
                                     atof(tokens.at(1).c_str()),
                                     atof(tokens.at(2).c_str()));
                    curr_mesh->normals_.push_back(normal);
                }
                //Vertice texture coordinate line
                if( line_id == "vt" ){
                    if(tokens.size() != 2){
                        ret = -1;
                        break;
                    }
                    glm::vec2 text_coord(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()));
                    curr_mesh->text_coords_.push_back(text_coord);
                }
                //Face line
                if( line_id == "f" ){
                    if(tokens.size() == 3){
                        curr_mesh->tri_faces_ = true;
                    }else if(tokens.size() == 4){
                        curr_mesh->tri_faces_ = false;
                    }else{
                        ret = -1;
                        break;
                    }
                    //The "Face" line contains the indexes of the
                    //vertices, normals and texture coordinates,
                    //separated by a '/' character
                    std::vector<std::string>::iterator it = tokens.begin();
                    for(; it != tokens.end(); it++){
                        std::vector<std::string> face_tokens = Split((*it), '/');
                        if((*it).find("//") != std::string::npos){
                            if(face_tokens.size() != 2){
                                DEBUG_MESSAGE("Missing normals or texture coordinates")
                                        ret = -1;
                                goto EndLoop;
                            }
                            curr_mesh->vertices_index_.push_back(atoi(face_tokens.at(0).c_str()) - vertex_index_shift);
                            curr_mesh->normals_index_.push_back(atoi(face_tokens.at(1).c_str()) - normal_index_shift);
                        }else{
                            if(face_tokens.size() != 3){
                                DEBUG_MESSAGE("Missing normals or texture coordinates")
                                        ret = -1;
                                goto EndLoop;
                            }
                            curr_mesh->vertices_index_.push_back(atoi(face_tokens.at(0).c_str())- vertex_index_shift);
                            curr_mesh->text_coords_index_.push_back(atoi(face_tokens.at(1).c_str()) - tex_coords_index_shift);
                            curr_mesh->normals_index_.push_back(atoi(face_tokens.at(2).c_str()) - normal_index_shift);
                        }
                    }
                }
            }
        }
EndLoop:
        file.close();
    }else{
        DEBUG_MESSAGE("Failed to open obj file.")
        ret = -1;
    }
    if(ret == -1){
        std::vector<Object*>::iterator it = objects.begin();
        for(; it != objects.end(); it++){
            delete (*it);
        }
        objects.clear();
        DEBUG_MESSAGE("Failed to load obj file.")
    }
    return objects;
}

std::map<std::string, Material*> OBJLoader::LoadMTL(const std::string &path)
{
    std::map<std::string, Material*> materials;
    Material *curr_mat = NULL;
    int ret = 0;
    std::ifstream file(path.c_str());
    if(file.is_open()){
        std::string line;
        while( std::getline(file, line) ){
            std::vector<std::string> tokens = Split(line, ' ');
            if(!tokens.empty()){
                std::string line_id = tokens.at(0);
                tokens.erase(tokens.begin());
                //Name
                if( line_id == "newmtl" ){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    curr_mat = new Material();
                    curr_mat->name_ = tokens.at(0);
                    materials.insert(std::pair<std::string, Material*>(curr_mat->name_, curr_mat ));
                }
                //Ka line
                if(line_id == "Ka"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    curr_mat->ka_ = glm::vec3(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()),
                                         atof(tokens.at(2).c_str()));

                }
                //Kd line
                if(line_id == "Kd"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    float test = atof(tokens.at(0).c_str());
                    curr_mat->kd_ = glm::vec3(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()),
                                         atof(tokens.at(2).c_str()));

                }
                //Ks line
                if(line_id == "Ks"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    curr_mat->ks_ = glm::vec3(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()),
                                         atof(tokens.at(2).c_str()));

                }
                //Tr line
                if(line_id == "Tr"){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    curr_mat->tr_ = atof(tokens.at(0).c_str());
                }
                //Diffuse texture
                if(line_id == "map_Kd"){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    //                    mat->map_kd_ = tokens.at(0);
                }
            }

        }
        file.close();
    }else{
        DEBUG_MESSAGE("Failed to open material file");
        ret = -1;
    }

    if(ret != -1){
        return materials;
    }else{        
        DEBUG_MESSAGE("Failed to load material.")
        std::map<std::string, Material*>::iterator it = materials.begin();
        for(; it != materials.end(); it++){
            delete (*it).second;
        }
        materials.clear();
    }
}

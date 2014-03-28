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

Object* OBJLoader::Load(const std::string &path)
{
    Object *obj = new Object();
    Mesh *mesh = new Mesh();
    Material *mat = new Material();

    double min_x=0,min_y=0,min_z=0,max_x=0,max_y=0,max_z=0;
    int ret = 0;
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
                    //                    materials_id_.insert(std::pair<std::string, int>(tokens.at(0),materials_id_.size()));


                    obj_file_dir_ = GetFilePath(path);
                    std::string material_path;
                    material_path.append(obj_file_dir_);
                    material_path.append(tokens.at(0));
                    mat = LoadMTL(material_path);
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
                    mesh->vertices_.push_back(vertice);
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
                    mesh->normals_.push_back(normal);
                }
                //Vertice texture coordinate line
                if( line_id == "vt" ){
                    if(tokens.size() != 2){
                        ret = -1;
                        break;
                    }
                    glm::vec2 text_coord(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()));
                    mesh->text_coords_.push_back(text_coord);
                }
                //Face line
                if( line_id == "f" ){
                    if(tokens.size() == 3){
                        mesh->tri_faces_ = true;
                    }else if(tokens.size() == 4){
                        mesh->tri_faces_ = false;
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
                            mesh->vertices_index_.push_back(atoi(face_tokens.at(0).c_str()));
                            mesh->normals_index_.push_back(atoi(face_tokens.at(1).c_str()));
                        }else{
                            if(face_tokens.size() != 3){
                                DEBUG_MESSAGE("Missing normals or texture coordinates")
                                        ret = -1;
                                goto EndLoop;
                            }
                            mesh->vertices_index_.push_back(atoi(face_tokens.at(0).c_str()));
                            mesh->text_coords_index_.push_back(atoi(face_tokens.at(1).c_str()));
                            mesh->normals_index_.push_back(atoi(face_tokens.at(2).c_str()));
                        }
                    }
                }
            }
        }
EndLoop:
        file.close();
        double center_x = (max_x + min_x)/2.0f;
        double center_y = (max_y + min_y)/2.0f;
        double center_z = (max_z + min_z)/2.0f;
        //TODO: Implement a bounding box...
        obj->position_ = glm::vec3(center_x,center_y,center_z);
        obj->mesh_ = mesh;
        obj->material_ = mat;
    }else{
        ret = -1;
    }
    if(ret != -1){
        return obj;
    }else{
        delete obj;
        delete mesh;
        delete mat;
        DEBUG_MESSAGE("Failed to load obj file.")
        return NULL;
    }
}

Material* OBJLoader::LoadMTL(const std::string &path)
{
    Material *mat = new Material();
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
                    mat->name_ = tokens.at(0);
                }
                //Ka line
                if(line_id == "Ka"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    mat->ka_ = glm::vec3(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()),
                                         atof(tokens.at(2).c_str()));

                }
                //Kd line
                if(line_id == "Kd"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    mat->kd_ = glm::vec3(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()),
                                         atof(tokens.at(2).c_str()));

                }
                //Ks line
                if(line_id == "Ks"){
                    if(tokens.size() != 3){
                        ret = -1;
                        break;
                    }
                    mat->ks_ = glm::vec3(atof(tokens.at(0).c_str()),
                                         atof(tokens.at(1).c_str()),
                                         atof(tokens.at(2).c_str()));

                }
                //Tr line
                if(line_id == "Tr"){
                    if(tokens.empty()){
                        ret = -1;
                        break;
                    }
                    mat->tr_ = atof(tokens.at(0).c_str());
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
        ret = -1;
    }

    if(ret != -1){
            return mat;
    }else{
        delete mat;
        DEBUG_MESSAGE("Failed to load material.")
        return NULL;
    }

}

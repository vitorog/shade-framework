#include "shader_program.h"
#include "debug.h"

#include <fstream>
#include <cstring>

ShaderProgram::ShaderProgram()
{
    handle_ = glCreateProgram();
}

std::string ShaderProgram::GetLastLog()
{
    return last_log_;
}

void ShaderProgram::Use()
{
    glUseProgram(handle_);
}

bool ShaderProgram::CompileShaderFromSource(const std::string &source, ShaderType type)
{
    GLuint shader_handle = glCreateShader(type);
    if(shader_handle == 0){
        DEBUG_MESSAGE("Failed to create shader.");
        return false;
    }
    const GLchar* source_array[] = {source.c_str()};
    glShaderSource( shader_handle, 1, source_array, NULL );
    glCompileShader( shader_handle );

    GLint result;
    glGetShaderiv( shader_handle, GL_COMPILE_STATUS, &result );
    if( result == GL_FALSE ){
        //TOOD: Debug message
        GLint log_length;
        glGetShaderiv( shader_handle, GL_INFO_LOG_LENGTH, &log_length);
        if( log_length > 0){
            char* log = new char[log_length];
            GLsizei written;
            glGetShaderInfoLog( shader_handle, log_length, &written, log);
            DEBUG_MESSAGE(log);
            last_log_ = std::string(log);
            delete[] log;
        }
    }else{
        shaders_handles_.push_back(shader_handle);
    }
}

bool ShaderProgram::CompileShaderFromFile(const std::string &path, ShaderType type)
{
    GLchar* source = LoadShaderSource(path);
    bool ret = false;
    if(source != NULL){
        ret = CompileShaderFromSource(source, type);
        delete[] source;
    }
    return ret;
}

GLuint ShaderProgram::GetHandle()
{
    return handle_;
}

GLchar* ShaderProgram::LoadShaderSource(const std::string &path)
{
    std::ifstream file_shader_source;
    file_shader_source.open(path.c_str());
    if(file_shader_source.is_open()){
        std::string line;
        std::string shader_source;
        while(file_shader_source.good()){
            getline(file_shader_source, line);
            shader_source.append(line);
            shader_source.append("\n");
        }
        file_shader_source.close();
        GLchar* shader_source_ptr = new GLchar[shader_source.size()];
        memcpy(shader_source_ptr,shader_source.c_str(),shader_source.size());
        shader_source_ptr[shader_source.size() - 1] = '\0'; //We can replace the last char (a \n) with the NULL-termination char.
        return shader_source_ptr;
    }
    return NULL;
}

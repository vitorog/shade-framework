#include "shader_program.h"
#include "debug.h"

#include <fstream>
#include <cstring>

ShaderProgram::ShaderProgram()
{
    handle_ = glCreateProgram();
}

std::string ShaderProgram::GetLastLog() const
{
    return last_log_;
}

void ShaderProgram::Use() const
{
    if(linked_){
        glUseProgram(handle_);
        DEBUG_MESSAGE("Using shader program.");
    }else{
        DEBUG_MESSAGE("Can't use a shader program that is not linked.");
    }
}

void ShaderProgram::Link()
{
    glLinkProgram( handle_ );
    GLint status;
    glGetProgramiv( handle_, GL_LINK_STATUS, &status );
    if( status == GL_FALSE ){
        linked_ = false;
        DEBUG_MESSAGE("Failed to link shader program");
        GLint log_length;
        glGetProgramiv( handle_, GL_INFO_LOG_LENGTH, &log_length );
        if( log_length > 0 ){
            char *log = new char[log_length];
            GLsizei written;
            glGetProgramInfoLog(handle_, log_length, &written, log);
            DEBUG_MESSAGE(log);
            delete[] log;
        }
    }else{
        linked_ = true;
        DEBUG_MESSAGE("Shader program linked successfully.");
    }
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
        shaders_handles_.push_back( shader_handle );
        glAttachShader( handle_, shader_handle );
    }
    return result == GL_TRUE ? true : false;
}

bool ShaderProgram::CompileShaderFromFile(const std::string &path, ShaderType type)
{
    GLchar* source = LoadShaderSource(path);
    bool ret = false;
    if(source != NULL){
        ret = CompileShaderFromSource(source, type);
        delete[] source;
    }else{
        DEBUG_MESSAGE("Could not load shader source.");
    }
    return ret;
}

std::map< std::string, GLint > ShaderProgram::GetActiveUniformsMap() const
{
    std::map< std::string, GLint > active_uniforms;
    GLint max_length, num_uniforms;
    glGetProgramiv( handle_, GL_ACTIVE_UNIFORMS, &num_uniforms );
    glGetProgramiv( handle_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length );
    GLint written, size, location;
    GLenum type;
    GLchar* name = new char[max_length];
    for( int i = 0; i < num_uniforms; i++ ){
        glGetActiveUniform( handle_, i, max_length, &written, &size, &type, name );
        location = glGetUniformLocation( handle_, name);
        active_uniforms[name] = location;
        DEBUG_MESSAGE("Uniform " << name << " - Location " << location);
    }
    return active_uniforms;

}

std::map< std::string, GLint > ShaderProgram::GetActiveAttribsMap() const
{
    std::map< std::string, GLint > active_attribs;
    GLint max_length, num_attribs;
    glGetProgramiv( handle_, GL_ACTIVE_ATTRIBUTES, &num_attribs );
    glGetProgramiv( handle_, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length );
    GLint written, size, location;
    GLenum type;
    GLchar* name = new char[max_length];
    for( int i = 0; i < num_attribs; i++ ){
        glGetActiveUniform( handle_, i, max_length, &written, &size, &type, name );
        location = glGetUniformLocation( handle_, name);
        active_attribs[name] = location;
        DEBUG_MESSAGE("Attrib " << name << " - Location " << location);
    }
    return active_attribs;
}

void ShaderProgram::BindAttribLocation( GLuint location, const std::string name ) const
{
    if(!linked_){
        glBindAttribLocation( handle_, location, name.c_str() );
    }else{
        DEBUG_MESSAGE("Attempted to bind attribute after linking the program.");
    }
}

GLuint ShaderProgram::GetHandle() const
{
    return handle_;
}

GLchar* ShaderProgram::LoadShaderSource(const std::string &path) const
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

void ShaderProgram::SetUniform(const std::string name, const glm::vec3 &v)
{
    GLint location = glGetUniformLocation( handle_, name.c_str() );
    if(location != -1){
        glUniform3fv(location, 3, &v[0]);
    }else{
        DEBUG_MESSAGE("Uniform variable " << name << " not found.");
    }
}

void ShaderProgram::SetUniform(const std::string name, const glm::vec4 &v)
{
    GLint location = glGetUniformLocation( handle_, name.c_str() );
    if(location != -1){
        glUniform4fv(location, 4, &v[0]);
    }else{
        DEBUG_MESSAGE("Uniform variable " << name << " not found.");
    }
}

void ShaderProgram::SetUniform(const std::string name, const glm::mat3 &m)
{
    GLint location = glGetUniformLocation( handle_, name.c_str() );
    if(location != -1){
        glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
    }else{
        DEBUG_MESSAGE("Uniform variable " << name << " not found.");
    }
}

void ShaderProgram::SetUniform(const std::string name, const glm::mat4 &m)
{
    GLint location = glGetUniformLocation( handle_, name.c_str() );
    if(location != -1){
        glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
    }else{
        DEBUG_MESSAGE("Uniform variable " << name << " not found.");
    }
}

void ShaderProgram::SetUniform(const std::string name, const float f)
{
    GLint location = glGetUniformLocation( handle_, name.c_str() );
    if(location != -1){
        glUniform1f(location, f);
    }else{
        DEBUG_MESSAGE("Uniform variable " << name << " not found.");
    }
}

void ShaderProgram::SetUniform(const std::string name, const int i)
{
    GLint location = glGetUniformLocation( handle_, name.c_str() );
    if(location != -1){
        glUniform1i(location, i);
    }else{
        DEBUG_MESSAGE("Uniform variable " << name << " not found.");
    }
}

void ShaderProgram::SetUniform(const std::string name, const bool b)
{
    GLint location = glGetUniformLocation( handle_, name.c_str() );
    if(location != -1){
        glUniform1ui(location, b);
    }else{
        DEBUG_MESSAGE("Uniform variable " << name << " not found.");
    }
}

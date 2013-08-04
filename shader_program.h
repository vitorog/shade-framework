#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

/*
 *This class is heavily inspired on the OpenGL 4 Shading Language Cookbook's
*/

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>

#include <string>
#include <list>
#include <map>

enum ShaderType {
    kVertexShader = GL_VERTEX_SHADER,
    kFragmentShader = GL_FRAGMENT_SHADER
};

class ShaderProgram
{
public:
    ShaderProgram();
    std::string GetLastLog() const;
    GLuint GetHandle() const;
    void Use()  const;
    void Link();
    bool CompileShaderFromSource(const std::string& source, ShaderType);
    bool CompileShaderFromFile(const std::string& path, ShaderType);
    std::map< std::string, GLint > GetActiveUniformsMap() const;
    std::map< std::string, GLint > GetActiveAttribsMap() const;
    void BindAttribLocation( GLuint location, const std::string name ) const;
    void SetUniform(const std::string name, const glm::vec3& v);
    void SetUniform(const std::string name, const glm::vec4& v);
    void SetUniform(const std::string name, const glm::mat3& m);
    void SetUniform(const std::string name, const glm::mat4& m);
    void SetUniform(const std::string name, const float f);
    void SetUniform(const std::string name, const int i);
    void SetUniform(const std::string name, const bool b);
private:
    GLchar* LoadShaderSource(const std::string& path) const;
    GLuint handle_;
    std::string last_log_;
    std::list<GLuint> shaders_handles_;
    bool linked_;
};

#endif // SHADER_PROGRAM_H


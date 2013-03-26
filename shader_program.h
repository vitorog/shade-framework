#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
#include <list>

enum ShaderType {
    kVertexShader = GL_VERTEX_SHADER,
    kFragmentShader = GL_FRAGMENT_SHADER
};

class ShaderProgram
{
public:
    ShaderProgram();
    std::string GetLastLog();
    GLuint GetHandle();
    void Use();
    bool CompileShaderFromSource(const std::string& source, ShaderType);
    bool CompileShaderFromFile(const std::string& path, ShaderType);
private:
    GLchar* LoadShaderSource(const std::string& path);
    GLuint handle_;
    std::string last_log_;
    std::list<GLuint> shaders_handles_;
};

#endif // SHADER_PROGRAM_H

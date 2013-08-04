#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <GL/glew.h>
#include <GL/gl.h>

#include <map>
#include <string>
#include <vector>

class GLContext
{
public:
    GLContext();
    bool InitGL();
    std::map<std::string, const GLubyte*> GetGLInfo() const;
    std::vector<const GLubyte*> GetGLExtensions() const;
};

#endif // GL_CONTEXT_H

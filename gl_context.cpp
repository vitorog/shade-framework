#include "gl_context.h"

#include "debug.h"

GLContext::GLContext()
{
}

bool GLContext::InitGL()
{
    GLenum error = glewInit();
    if( error != GLEW_OK ){
      const GLubyte* error_string = glewGetErrorString(error);
      DEBUG_MESSAGE("GLEW failed to initialize: ");
      DEBUG_MESSAGE(error_string);
      return false;
    }   
    glClearColor(0.4f,0.4f,0.4f,1.0f);
    error = glGetError();
    if(error != GL_NO_ERROR){
      return false;
    }
    return true;
}

std::map<std::string, const GLubyte*> GLContext::GetGLInfo() const
{
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *glsl_version = glGetString( GL_SHADING_LANGUAGE_VERSION );

    DEBUG_MESSAGE("Vendor: " << vendor);
    DEBUG_MESSAGE("Renderer: " << renderer);
    DEBUG_MESSAGE("GLSL Version: " << glsl_version);

    std::map<std::string, const GLubyte* > info;
    info["Vendor"] = vendor;
    info["Renderer"] = renderer;
    info["GLSL Version"] = glsl_version;
    return info;
}

std::vector<const GLubyte*> GLContext::GetGLExtensions() const
{
    GLint num_extensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
    std::vector<const GLubyte*> extensions;
    for(int i = 0; i < num_extensions; i++){
      const GLubyte* extension_name = glGetStringi( GL_EXTENSIONS, i);
      extensions.push_back( extension_name );
      DEBUG_MESSAGE(extensions[i]);
    }
    return extensions;
}

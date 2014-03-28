project(shade-framework)
cmake_minimum_required(VERSION 2.8)
include_directories("../../../Libs/glm-0.9.5.2/glm") #TODO: Change this hardcoded path
include_directories("../../../Libs/glew-1.10.0_mingw/include")

set(HEADERS
debug.h
gl_context.h
shader_program.h
point3.h
vec3.h
material.h
obj_loader.h
utils.h
scene.h
mesh.h
object.h
point_light.h
camera.h
texture2d.h
)

set(SOURCES
gl_context.cpp
shader_program.cpp
point3.cpp
vec3.cpp
material.cpp
obj_loader.cpp
utils.cpp
scene.cpp
mesh.cpp
object.cpp
point_light.cpp
camera.cpp
texture2d.cpp
)

aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
#target_link_libraries(${PROJECT_NAME} GLEW GL SDL SDL_image)
if(UNIX)
target_link_libraries(${PROJECT_NAME} GLEW GL)
else(UNIX)
set(GLEW_INCLUDE_DIR F:/Development/Libs/glew-1.10.0_mingw/include)
set(GLEW_LIBRARY F:/Development/Libs/glew-1.10.0_mingw/lib/libglew32.dll.a)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
endif(UNIX)

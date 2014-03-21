project(shade-framework)
cmake_minimum_required(VERSION 2.8)
include_directories("/home/vitor/glm/glm-0.9.5.2/glm") #TODO: Change this hardcoded path

set(HEADERS
debug.h
gl_context.h
shader_program.h
point3.h
vec3.h
material.h
model.h
utils.h
)

set(SOURCES
gl_context.cpp
shader_program.cpp
point3.cpp
vec3.cpp
material.cpp
model.cpp
utils.cpp
)

aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
#target_link_libraries(${PROJECT_NAME} GLEW GL SDL SDL_image)
target_link_libraries(${PROJECT_NAME} GLEW GL)


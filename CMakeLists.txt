project(shade-framework)
cmake_minimum_required(VERSION 2.8)
include_directories("/home/vitor/glm-0.9.4.3/") #TODO: Change this hardcoded path

set(HEADERS
debug.h
)

aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${HEADERS})
target_link_libraries(${PROJECT_NAME} GLEW GL SDL SDL_image)


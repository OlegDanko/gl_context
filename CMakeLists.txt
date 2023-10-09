cmake_minimum_required(VERSION 3.5)

project(game_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_library(gl_context
    src/Shader.cpp
    src/GLContext.cpp
    src/ShaderProgram.cpp
    src/VertexArrayObject.cpp
    src/Texture.cpp
    src/BufferObject.cpp
)
target_link_libraries(gl_context
    OpenGL::GL
    GLEW::GLEW
)
target_include_directories(gl_context PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_compile_options(gl_context PRIVATE -Wall -Wextra -Wpedantic -Werror)

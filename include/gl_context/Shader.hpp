#pragma once

#include <GL/glew.h>
#include <string>

struct Shader {
    GLint id;
    Shader(const std::string& code, GLuint type);
    ~Shader();
    static Shader make_vertex(const std::string& code);
    static Shader make_fragment(const std::string& code);
};

#pragma once

#include <string>
#include <GL/glew.h>

struct Shader {
    GLint id;
    Shader(const std::string& code, GLuint type);
    ~Shader();
    static Shader make_vertex(const std::string& code);
    static Shader make_fragment(const std::string& code);
};

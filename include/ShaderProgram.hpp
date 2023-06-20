#pragma once

#include "Shader.hpp"

#include <glm/glm.hpp>

class ShaderProgram
{
    GLuint program;

public:
    ShaderProgram(Shader vertex, Shader fragment);
    ~ShaderProgram();

    void use() const;

    void set_uniform(GLuint ID, const int   val) const;
    void set_uniform(GLuint ID, const float val) const;
    void set_uniform(GLuint ID, const glm::vec2  val) const;
    void set_uniform(GLuint ID, const glm::vec3  val) const;
    void set_uniform(GLuint ID, const glm::vec4  val) const;
    void set_uniform(GLuint ID, const glm::mat4  val) const;

    void set_uniformv(GLuint ID, const int*   val, GLsizei count = 1) const;
    void set_uniformv(GLuint ID, const float* val, GLsizei count = 1) const;
    void set_uniformv(GLuint ID, const glm::vec2*  val, GLsizei count = 1) const;
    void set_uniformv(GLuint ID, const glm::vec3*  val, GLsizei count = 1) const;
    void set_uniformv(GLuint ID, const glm::vec4*  val, GLsizei count = 1) const;
    void set_uniformv(GLuint ID, const glm::mat4*  val, GLsizei count = 1) const;
};

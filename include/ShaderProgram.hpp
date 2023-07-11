#pragma once

#include "Shader.hpp"

#include <glm/glm.hpp>
#include <stdexcept>

class ShaderProgram
{
    GLuint program;

    void attach_shader(const Shader& s) {
        glAttachShader(program, s.id);
    }
    void detach_shader(const Shader& s) {
        glAttachShader(program, s.id);
    }

public:
    template<typename ...SHADERS>
    ShaderProgram(const SHADERS& ...shaders) {
        program = glCreateProgram();
        (attach_shader(shaders), ...);
        glLinkProgram(program);

        GLint result = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        int info_log_length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

        if (info_log_length <= 0 ) {
            (detach_shader(shaders), ...);
            return;
        }

        std::string error_msg(info_log_length+1, '\0');
        glGetProgramInfoLog(program, info_log_length, NULL, &error_msg[0]);
        throw std::runtime_error("Error linking program:\n" + error_msg + "\n");
    }
//    ShaderProgram(Shader vertex, Shader fragment);
    ~ShaderProgram();

    void use() const;

    void set_uniform(GLuint ID, const int   val) const;
    void set_uniform(GLuint ID, const GLuint val) const;
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
    void set_uniformv(GLuint ID, const glm::mat2*  val, GLsizei count = 1) const;
    void set_uniformv(GLuint ID, const glm::mat3*  val, GLsizei count = 1) const;
    void set_uniformv(GLuint ID, const glm::mat4*  val, GLsizei count = 1) const;
};

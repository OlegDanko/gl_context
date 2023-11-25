#pragma once

#include "Shader.hpp"
#include "BoundResource.hpp"

#include <glm/glm.hpp>
#include <stdexcept>

class ShaderProgram
{
    GLuint id;

    void attach_shader(const Shader& s);
    void detach_shader(const Shader& s);

public:
    template<typename ...SHADERS>
    ShaderProgram(const SHADERS& ...shaders) {
        id = glCreateProgram();
        (attach_shader(shaders), ...);
        glLinkProgram(id);

        GLint result = GL_FALSE;
        glGetProgramiv(id, GL_LINK_STATUS, &result);
        int info_log_length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_log_length);

        if (info_log_length <= 0 ) {
            (detach_shader(shaders), ...);
            return;
        }

        std::string error_msg(info_log_length+1, '\0');
        glGetProgramInfoLog(id, info_log_length, NULL, &error_msg[0]);
        throw std::runtime_error("Error linking program:\n" + error_msg + "\n");
    }
    ~ShaderProgram();

    struct InUse : BoundResource<ShaderProgram> {
        InUse(GLuint id);
        ~InUse();

        const InUse& set_uniform(GLuint ID, const int   val) const;
        const InUse& set_uniform(GLuint ID, const GLuint val) const;
        const InUse& set_uniform(GLuint ID, const float val) const;
        const InUse& set_uniform(GLuint ID, const glm::vec2& val) const;
        const InUse& set_uniform(GLuint ID, const glm::vec3& val) const;
        const InUse& set_uniform(GLuint ID, const glm::vec4& val) const;
        const InUse& set_uniform(GLuint ID, const glm::mat4& val) const;
        const InUse& set_uniform(GLuint ID, const glm::ivec2& val) const;
        const InUse& set_uniform(GLuint ID, const glm::ivec3& val) const;
        const InUse& set_uniform(GLuint ID, const glm::ivec4& val) const;

        const InUse& set_uniformv(GLuint ID, const int*   val, GLsizei count = 1) const;
        const InUse& set_uniformv(GLuint ID, const float* val, GLsizei count = 1) const;
        const InUse& set_uniformv(GLuint ID, const glm::vec2*  val, GLsizei count = 1) const;
        const InUse& set_uniformv(GLuint ID, const glm::vec3*  val, GLsizei count = 1) const;
        const InUse& set_uniformv(GLuint ID, const glm::vec4*  val, GLsizei count = 1) const;
        const InUse& set_uniformv(GLuint ID, const glm::mat2*  val, GLsizei count = 1) const;
        const InUse& set_uniformv(GLuint ID, const glm::mat3*  val, GLsizei count = 1) const;
        const InUse& set_uniformv(GLuint ID, const glm::mat4*  val, GLsizei count = 1) const;
    };

    InUse use() const;
};

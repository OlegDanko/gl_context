#include "ShaderProgram.hpp"
#include <stdexcept>

ShaderProgram::ShaderProgram(Shader vertex, Shader fragment) {
    program = glCreateProgram();
    glAttachShader(program, vertex.id);
    glAttachShader(program, fragment.id);
    glLinkProgram(program);

    GLint result = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    int info_log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length <= 0 ) {
        glDetachShader(program, vertex.id);
        glDetachShader(program, fragment.id);
        return;
    }

    std::string error_msg(info_log_length+1, '\0');
    glGetProgramInfoLog(program, info_log_length, NULL, &error_msg[0]);
    throw std::runtime_error("Error linking program:\n" + error_msg + "\n");
}

ShaderProgram::~ShaderProgram(){ glDeleteProgram(program); }

void ShaderProgram::use() const { glUseProgram(program); }

void ShaderProgram::set_uniform(GLuint ID, const int val) const {
    glUniform1i(ID, val);
}
void ShaderProgram::set_uniform(GLuint ID, const float val) const {
    glUniform1f(ID, val);
}
void ShaderProgram::set_uniform(GLuint ID, const glm::vec2 val) const {
    glUniform2f(ID, val.x, val.y);
}
void ShaderProgram::set_uniform(GLuint ID, const glm::vec3 val) const {
    glUniform3f(ID, val.x, val.y, val.z);

}
void ShaderProgram::set_uniform(GLuint ID, const glm::vec4 val) const {
    glUniform4f(ID, val.x, val.y, val.z, val.a);
}

void ShaderProgram::set_uniformv(GLuint ID, const int *val, GLsizei count) const {
    glUniform1iv(ID, count, val);
}

void ShaderProgram::set_uniformv(GLuint ID, const float *val, GLsizei count) const {
    glUniform1fv(ID, count, val);
}

void ShaderProgram::set_uniformv(GLuint ID, const glm::vec2 *val, GLsizei count) const {
    glUniform2fv(ID, count, &val[0][0]);
}

void ShaderProgram::set_uniformv(GLuint ID, const glm::vec3 *val, GLsizei count) const {
    glUniform3fv(ID, count, &val[0][0]);
}

void ShaderProgram::set_uniformv(GLuint ID, const glm::vec4 *val, GLsizei count) const {
    glUniform4fv(ID, count, &val[0][0]);
}

void ShaderProgram::set_uniformv(GLuint ID, const glm::mat4 *val, GLsizei count) const {
    glUniformMatrix4fv(ID, count, GL_FALSE, (GLfloat*)val);
}

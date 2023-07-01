#include "ShaderProgram.hpp"
#include <stdexcept>

ShaderProgram::~ShaderProgram(){ glDeleteProgram(program); }

void ShaderProgram::use() const { glUseProgram(program); }

void ShaderProgram::set_uniform(GLuint ID, const int val) const {
    glUniform1i(ID, val);
}
void ShaderProgram::set_uniform(GLuint ID, const GLuint val) const {
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

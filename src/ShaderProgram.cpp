#include <gl_context/ShaderProgram.hpp>

#include <stdexcept>

template<>
bool BoundResource<ShaderProgram>::bound = false;

void ShaderProgram::attach_shader(const Shader &s) {
    glAttachShader(id, s.id);
}

void ShaderProgram::detach_shader(const Shader &s) {
    glAttachShader(id, s.id);
}

ShaderProgram::~ShaderProgram(){ glDeleteProgram(id); }

ShaderProgram::InUse ShaderProgram::use() const { return {id}; }

const ShaderProgram::InUse& ShaderProgram::InUse::set_uniform(GLuint ID, const int val) const {
    glUniform1i(ID, val);
    return *this;
}
const ShaderProgram::InUse& ShaderProgram::InUse::set_uniform(GLuint ID, const GLuint val) const {
    glUniform1i(ID, val);
    return *this;
}
const ShaderProgram::InUse& ShaderProgram::InUse::set_uniform(GLuint ID, const float val) const {
    glUniform1f(ID, val);
    return *this;
}
const ShaderProgram::InUse& ShaderProgram::InUse::set_uniform(GLuint ID, const glm::vec2 val) const {
    glUniform2f(ID, val.x, val.y);
    return *this;
}
const ShaderProgram::InUse& ShaderProgram::InUse::set_uniform(GLuint ID, const glm::vec3 val) const {
    glUniform3f(ID, val.x, val.y, val.z);
    return *this;
}
const ShaderProgram::InUse& ShaderProgram::InUse::set_uniform(GLuint ID, const glm::vec4 val) const {
    glUniform4f(ID, val.x, val.y, val.z, val.a);
    return *this;
}

const ShaderProgram::InUse& ShaderProgram::InUse::set_uniformv(GLuint ID, const int *val, GLsizei count) const {
    glUniform1iv(ID, count, val);
    return *this;
}
const ShaderProgram::InUse& ShaderProgram::InUse::set_uniformv(GLuint ID, const float *val, GLsizei count) const {
    glUniform1fv(ID, count, val);
    return *this;
}

const ShaderProgram::InUse& ShaderProgram::InUse::set_uniformv(GLuint ID, const glm::vec2 *val, GLsizei count) const {
    glUniform2fv(ID, count, &val[0][0]);
    return *this;
}

const ShaderProgram::InUse& ShaderProgram::InUse::set_uniformv(GLuint ID, const glm::vec3 *val, GLsizei count) const {
    glUniform3fv(ID, count, &val[0][0]);
    return *this;
}

const ShaderProgram::InUse& ShaderProgram::InUse::set_uniformv(GLuint ID, const glm::vec4 *val, GLsizei count) const {
    glUniform4fv(ID, count, &val[0][0]);
    return *this;
}

const ShaderProgram::InUse& ShaderProgram::InUse::set_uniformv(GLuint ID, const glm::mat4 *val, GLsizei count) const {
    glUniformMatrix4fv(ID, count, GL_FALSE, (GLfloat*)val);
    return *this;
}

ShaderProgram::InUse::InUse(GLuint id) : BoundResource<ShaderProgram>() {
    glUseProgram(id);
}


ShaderProgram::InUse::~InUse() {
    glUseProgram(0);
}

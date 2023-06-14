#include "VertexArrayObject.hpp"
#include <numeric>

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &id);
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &id);
}

void VertexArrayObject::bind() {
    glBindVertexArray(id);
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
}

void VertexArrayObject::_init_vertex_attrib_pointer(GLuint location,
                                                    GLuint size,
                                                    GLuint offset,
                                                    GLuint stride,
                                                    bool enable) {
    glVertexAttribPointer(location,
                          size,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          reinterpret_cast<GLvoid*>(offset));
    if(enable)
        glEnableVertexAttribArray(location);
}

void VertexArrayObject::add_array_buffer(VertexBufferObject &vbo,
                                         GLuint location,
                                         GLuint size,
                                         GLuint offset,
                                         GLuint stride,
                                         GLuint divisor) {
    bind();
    vbo.bind();
    _init_vertex_attrib_pointer(location, size, offset, stride);
    glVertexAttribDivisor(location, divisor);
    vbo.unbind();
    unbind();
}

void VertexArrayObject::add_array_buffer(VertexBufferObject &vbo,
                                         std::vector<AttribPointerParams> params,
                                         GLuint stride) {
    if(stride == 0) {
        stride = std::accumulate(params.begin(),
                                 params.end(),
                                 0,
                                 [](auto s, auto p) { return s + p.size*sizeof(GLfloat); });
    }

    bind();
    vbo.bind();
    GLuint offset{0};
    for(auto p : params) {
        _init_vertex_attrib_pointer(p.location, p.size, offset, stride);
        offset += p.size*sizeof(GLfloat);
    }

    vbo.unbind();
    unbind();
}

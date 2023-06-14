#pragma once

#include "BufferObject.hpp"

using VertexBufferObject = BufferObject<GL_ARRAY_BUFFER>;

struct VertexArrayObject {
    GLuint id;
    VertexArrayObject();
    ~VertexArrayObject();
    void bind();
    void unbind();

    struct AttribPointerParams {
        GLuint location;
        GLuint size;
    };

    void _init_vertex_attrib_pointer(GLuint location, GLuint size, GLuint offset, GLuint stride, bool enable = true);

    void add_array_buffer(VertexBufferObject& vbo, GLuint location, GLuint size, GLuint offset = 0, GLuint stride = 0, GLuint divisor = 0);

    void add_array_buffer(VertexBufferObject& vbo, std::vector<AttribPointerParams> params, GLuint stride = 0);

};

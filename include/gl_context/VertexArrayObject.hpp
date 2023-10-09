#pragma once

#include "BufferObject.hpp"

struct VertexArrayObject {
    GLuint id;
    VertexArrayObject();
    ~VertexArrayObject();

    struct AttribPointerParams {
        GLuint location;
        GLuint size;
        GLuint divisor = 0;
    };

    struct Bound : BoundResource<VertexArrayObject> {
        Bound(GLuint id) : BoundResource<VertexArrayObject>() {
            glBindVertexArray(id);
        }
        ~Bound() {
            glBindVertexArray(0);
        }

        void _init_vertex_attrib_pointer(GLuint location,
                                         GLuint size,
                                         GLuint offset,
                                         GLuint stride,
                                         bool enable = true);

        void add_array_buffer(ArrayBufferObject& vbo,
                              GLuint location,
                              GLuint size,
                              GLuint offset = 0,
                              GLuint stride = 0,
                              GLuint divisor = 0);

        void add_array_buffer(ArrayBufferObject& vbo,
                              std::vector<AttribPointerParams> params,
                              GLuint stride = 0);
    };

    Bound bind();
};

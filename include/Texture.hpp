#pragma once

#include <VertexArrayObject.hpp>
#include <type_traits>

template<GLuint type>
struct Texture {
    GLuint id;
    Texture() {
        glGenTextures(1, &id);
    }
    ~Texture() {
        glDeleteTextures(1, &id);
    }
    void bind() {
        glBindTexture(type, id);
    }
    std::enable_if_t<type == GL_TEXTURE_BUFFER, void>
    tex_buffer(VertexBufferObject& vbo, GLuint format) {
        glTexBuffer(GL_TEXTURE_BUFFER, format, vbo.id);
    }
    void bind_image(GLuint bind_id,
                    GLuint access,
                    GLuint format,
                    GLuint level = 0,
                    GLuint layered = GL_FALSE,
                    GLuint layer = 0) {
        glBindImageTexture(bind_id, id, level, layered, layer, access, format);
    }
};

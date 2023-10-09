#pragma once

#include "BufferObject.hpp"

#include <type_traits>

struct Texture {
    GLuint id;
    Texture();
    ~Texture();

    void bind_image(GLuint bind_id,
                    GLuint access,
                    GLuint format,
                    GLuint level = 0,
                    GLuint layered = GL_FALSE,
                    GLuint layer = 0);

    template<GLuint type>
    struct Bound : BoundResource<Texture> {
        using base_t = BoundResource<Texture>;

        Bound(GLuint id) : base_t() {
            glBindTexture(type, id);
        }

        std::enable_if_t<type == GL_TEXTURE_BUFFER, Bound&>
        tex_buffer(ArrayBufferObject& vbo, GLuint format) {
            glTexBuffer(type, format, vbo.id);
            return *this;
        }
    };

    template<GLuint type>
    Bound<type> bind() {
        return {id};
    }
};

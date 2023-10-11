#pragma once

#include "BoundTexture.hpp"

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
    auto bind() {
        return BoundTexture<tex_type_to_typename_t<type>>{id};
    }
};

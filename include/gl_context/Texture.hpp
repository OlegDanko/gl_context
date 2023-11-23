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


    template<GLint type>
    auto bind() {
        return BoundTexture<type>{id};
    }
};

#pragma once
#include "BufferObject.hpp"

#include <type_traits>

template<GLuint> struct BoundTexAny;
template<GLuint> struct BoundTexBuffer;
template<GLuint> struct BoundTex2D;

template<GLuint type>
struct tex_type_to_typename {
    using type_t =
        std::conditional_t<type == GL_TEXTURE_BUFFER, BoundTexBuffer<GL_TEXTURE_BUFFER>,
        std::conditional_t<type == GL_TEXTURE_2D, BoundTex2D<GL_TEXTURE_2D>,
        void>>;
};

template<GLuint type>
using tex_type_to_typename_t = typename tex_type_to_typename<type>::type_t;

struct Texture;

// The purpose of this implementation is:
// Make sure that the intended GL texture is bound when texture operations are performed
// Only provide the functions that are appropriate to a given GL texture type
template<typename T>
struct BoundTexture;

template<GLuint type>
struct BoundTexture<BoundTexAny<type>> : BoundResource<Texture>{
    using base_t = BoundResource<Texture>;

    BoundTexture(GLuint id) : base_t() {
        glBindTexture(type, id);
    }
};


template<GLuint type>
struct BoundTexture<BoundTexBuffer<type>> : BoundTexture<BoundTexAny<type>> {
    auto& tex_buffer(ArrayBufferObject& vbo, GLuint format) {
        glTexBuffer(type, format, vbo.id);
        return *this;
    }
};

template<GLuint type>
struct BoundTexture<BoundTex2D<type>> : BoundTexture<BoundTexAny<type>> {
    auto& tex_image_2d(std::vector<uint8_t>& img, int width, int height) {
        glTexImage2D(type,
                     0,
                     GL_R32F,
                     width,
                     height,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     &img.front());
        return *this;
    }
};


//std::cout << *std::min_element(fm_cpu.begin(), fm_cpu.end()) << " "
//          << *std::max_element(fm_cpu.begin(), fm_cpu.end()) << std::endl;


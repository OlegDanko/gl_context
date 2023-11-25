#pragma once
#include "BufferObject.hpp"

#include <type_traits>

template<typename T, typename ...Ts>
constexpr bool is_one_of(T&& t, Ts&&...ts) {
    return (...||(t == ts));
}

template<typename T> constexpr GLint type_to_type_code();
template<typename T> constexpr GLint type_to_channels_code();
template<typename T> constexpr GLint type_to_internal_code();


struct Texture;

template<GLint type>
struct BoundTexture : BoundResource<Texture>{
    using base_t = BoundResource<Texture>;

    BoundTexture(GLuint id) : base_t() {
        glBindTexture(type, id);
    }
    auto& tex_buffer(ArrayBufferObject& vbo, GLuint format) {
        static_assert(is_one_of(type, GL_TEXTURE_BUFFER));
        glTexBuffer(type, format, vbo.id);
        return *this;
    }

    template<typename T>
    auto& tex_image_2d(std::vector<T>& img, int width, int height) {
        static_assert(is_one_of(type, GL_TEXTURE_2D));
        glTexImage2D(type,
                     0,
                     type_to_internal_code<T>(),
                     width,
                     height,
                     0,
                     type_to_channels_code<T>(),
                     type_to_type_code<T>(),
                     &img.front());
        return *this;
    }
    template<typename T>
    auto& tex_image_3d(std::vector<T>& img, int width, int height, int depth) {
        static_assert(is_one_of(type, GL_TEXTURE_3D));
        glTexImage3D(type,
                     0,
                     type_to_internal_code<T>(),
                     width,
                     height,
                     depth,
                     0,
                     type_to_channels_code<T>(),
                     type_to_type_code<T>(),
                     &img.front());
        return *this;
    }
    template<typename T>
    auto& tex_storage_2d(int width, int height) {
        static_assert(is_one_of(type, GL_TEXTURE_2D));
        glTexStorage2D(type,
                       1,
                       type_to_internal_code<T>(),
                       width,
                       height);
        return *this;
    }
    template<typename T>
    auto& tex_storage_3d(int width, int height, int depth) {
        static_assert(is_one_of(type, GL_TEXTURE_3D));
        glTexStorage3D(type,
                       1,
                       type_to_internal_code<T>(),
                       width,
                       height,
                       depth);
        return *this;
    }
    template<typename T>
    auto& get_tex_image(std::vector<T>& img) {
        static_assert(is_one_of(type, GL_TEXTURE_2D, GL_TEXTURE_3D));
        glGetTexImage(type,
                      0,
                      type_to_channels_code<T>(),
                      type_to_type_code<T>(),
                      &img.front());
        return *this;
    }
};


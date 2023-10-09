#pragma once

#include "BoundResource.hpp"

#include <GL/glew.h>
#include <vector>
#include <cstring>
#include <iostream>

struct BufferObject {
    GLuint id;

    BufferObject();

    template<GLuint type>
    struct Bound : BoundResource<BufferObject> {
        using base_t = BoundResource<BufferObject>;
        Bound(GLuint id) : base_t() {
            base_t::bound = true;
            glBindBuffer(type, id);
        }
        ~Bound() {
            base_t::bound = false;
        }
        template<typename T>
        Bound& init(size_t count) {
            std::vector<T> vec(count);
            upload(vec);
            return *this;
        }

        template<typename T>
        Bound& upload(const std::vector<T>& data, size_t count = 0) {
            if(count == 0)
                count = data.size();

            glBufferData(type, sizeof(T)*count, &data.at(0), GL_DYNAMIC_DRAW);
            return *this;
        }

        template<typename T>
        Bound& update(const std::vector<T>& data, size_t count = 0, size_t offset = 0) {
            if(count == 0)
                count = data.size();

            glBufferSubData(type, offset, sizeof(T)*count, &data.at(0));
            return *this;
        }

        template<typename T>
        Bound& download(std::vector<T>& data, size_t count = 0, size_t offset = 0) {
            if(count == 0)
                count = data.size();

            glGetBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(T)*data.size(), &data.at(0));
            return *this;
        }
    };

    template<GLuint type>
    Bound<type> bind() {
        return {id};
    }
};

template<GLuint type>
struct BufferObjectConstType : BufferObject {
    auto bind() {
        return BufferObject::bind<type>();
    }
};

using ArrayBufferObject = BufferObjectConstType<GL_ARRAY_BUFFER>;

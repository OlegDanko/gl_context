#pragma once

#include <GL/glew.h>
#include <vector>
#include <cstring>
#include <iostream>

template<GLuint TYPE>
struct BufferObject {
    GLuint id;

    template<typename T>
    void load(const std::vector<T>& data) {
        bind();
        glBufferData(TYPE, sizeof(T)*data.size(), &data.at(0), GL_DYNAMIC_DRAW);
        unbind();
    }

    template<typename T>
    void update(const std::vector<T>& data, size_t count = 0, size_t offset = 0) {
        if(count == 0)
            count = data.size();

        bind();
        glBufferSubData(TYPE, offset, sizeof(T)*count, &data.at(0));
        unbind();
    }

    BufferObject() {
        glGenBuffers(1, &id);
    }
    void bind() {
        glBindBuffer(TYPE, id);
    }
    void unbind() {
        glBindBuffer(TYPE, 0);
    }
};

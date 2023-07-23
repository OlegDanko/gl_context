#pragma once

#include <GL/glew.h>
#include <vector>
#include <cstring>
#include <iostream>

template<GLuint TYPE>
struct BufferObject {
    GLuint id;

    template<typename T>
    void init(size_t count) {
        std::vector<T> vec(count);
        upload(vec);
    }

    template<typename T>
    void upload(const T* data_ptr, size_t count) {
        bind();
        glBufferData(TYPE, sizeof(T)*count, data_ptr, GL_STATIC_DRAW);
        unbind();
    }

    template<typename T>
    void upload(const std::vector<T>& data, size_t count = 0) {
        if(count == 0)
            count = data.size();

        upload(&data.at(0), count);
    }

    template<typename T>
    void update(const T* data_ptr, size_t count, size_t offset = 0) {
        bind();
        glBufferSubData(TYPE, offset, sizeof(T)*count, data_ptr);
        unbind();
    }

    template<typename T>
    void update(const std::vector<T>& data, size_t count = 0, size_t offset = 0) {
        if(count == 0) {
            if(data.size() == 0)
                return;
            count = data.size();
        }

        update(&data.at(0), count, offset);
    }

    template<typename T>
    void download(std::vector<T>& data, size_t count = 0, size_t offset = 0) {
        if(count == 0)
            count = data.size();

        bind();
        glGetBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(T)*data.size(), &data.at(0));
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

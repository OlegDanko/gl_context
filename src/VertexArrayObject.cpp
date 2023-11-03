#include <gl_context/VertexArrayObject.hpp>
#include <numeric>

template<>
int BoundResource<VertexArrayObject>::bound = 0;

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &id);
}

VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &id);
}

VertexArrayObject::Bound VertexArrayObject::bind()
{
    return {id};
}

VertexArrayObject::Bound&
VertexArrayObject::Bound::_init_vertex_attrib_pointer(GLuint location,
                                                      GLuint size,
                                                      GLuint offset,
                                                      GLuint stride,
                                                      bool enable) {
    glVertexAttribPointer(location,
                          size,
                          GL_FLOAT,
                          GL_FALSE,
                          stride,
                          reinterpret_cast<GLvoid*>(offset));
    if(enable)
        glEnableVertexAttribArray(location);

    return *this;
}

VertexArrayObject::Bound&
VertexArrayObject::Bound::add_array_buffer(ArrayBufferObject &vbo,
                                           GLuint location,
                                           GLuint size,
                                           GLuint offset,
                                           GLuint stride,
                                           GLuint divisor) {
    auto b = vbo.bind();
    _init_vertex_attrib_pointer(location, size, offset, stride);
    glVertexAttribDivisor(location, divisor);

    return *this;
}

VertexArrayObject::Bound&
VertexArrayObject::Bound::add_array_buffer(ArrayBufferObject &vbo,
                                           std::vector<AttribPointerParams> params,
                                           GLuint stride) {
    if(stride == 0) {
        stride = std::accumulate(params.begin(),
                                 params.end(),
                                 0,
                                 [](auto s, auto p) { return s + p.size; }) * sizeof(GLfloat);
    }

    auto b = vbo.bind();
    GLuint offset{0};
    for(auto p : params) {
        _init_vertex_attrib_pointer(p.location,
                                    p.size,
                                    offset * sizeof(GLfloat),
                                    stride);
        offset += p.size;
        glVertexAttribDivisor(p.location, p.divisor);
    }

    return *this;
}

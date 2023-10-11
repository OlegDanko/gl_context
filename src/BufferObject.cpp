#include <gl_context/BufferObject.hpp>

template<>
int BoundResource<BufferObject>::bound = 0;


BufferObject::BufferObject() {
    glGenBuffers(1, &id);
}

#include <gl_context/BufferObject.hpp>

template<>
bool BoundResource<BufferObject>::bound = false;


BufferObject::BufferObject() {
    glGenBuffers(1, &id);
}

#include <gl_context/Texture.hpp>

template<>
bool BoundResource<Texture>::bound = false;

Texture::Texture() {
    glGenTextures(1, &id);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind_image(GLuint bind_id,
                         GLuint access,
                         GLuint format,
                         GLuint level,
                         GLuint layered,
                         GLuint layer) {
    glBindImageTexture(bind_id, id, level, layered, layer, access, format);
}

#include <gl_context/Texture.hpp>

template<>
int BoundResource<Texture>::bound = 0;

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

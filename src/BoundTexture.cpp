#include <gl_context/BoundTexture.hpp>

template<> GLint type_to_type_code<GLbyte>() { return GL_BYTE; }
template<> GLint type_to_type_code<GLubyte>() { return GL_UNSIGNED_BYTE; }
template<> GLint type_to_type_code<GLint>() { return GL_INT; }
template<> GLint type_to_type_code<GLfloat>() { return GL_FLOAT; }

template<> GLint type_to_channels_code<GLbyte>() { return GL_RED_INTEGER; }
template<> GLint type_to_channels_code<GLubyte>() { return GL_RED_INTEGER; }
template<> GLint type_to_channels_code<GLint>() { return GL_RED_INTEGER; }
template<> GLint type_to_channels_code<GLfloat>() { return GL_RED; }

template<> GLint type_to_internal_code<GLbyte>() { return GL_R8I; }
template<> GLint type_to_internal_code<GLubyte>() { return GL_R8UI; }
template<> GLint type_to_internal_code<GLint>() { return GL_R32I; }
template<> GLint type_to_internal_code<GLfloat>() { return GL_R32F; }

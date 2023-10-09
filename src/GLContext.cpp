#include <gl_context/GLContext.hpp>
#include <stdexcept>

GLContext::GLContext() {
    GLenum err = glewInit();
    if(err != GLEW_OK)
        throw std::runtime_error("Couldn't initialize GLEW");
}

GLContext &GLContext::get() {
    static GLContext ctx;
    return ctx;
}

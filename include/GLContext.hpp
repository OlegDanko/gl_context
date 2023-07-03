#pragma once
#include <GL/glew.h>

class GLContext {
    GLContext();
public:
    static GLContext& get();
};

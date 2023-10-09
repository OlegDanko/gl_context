#include <gl_context/Shader.hpp>

#include <stdexcept>
#include <iostream>

Shader::Shader(const std::string &code, GLuint type) {
    id = glCreateShader(type);
    auto c_code = code.c_str();
    glShaderSource(id, 1, &c_code , NULL);
    glCompileShader(id);

    GLint result = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    int info_log_length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length <= 0 ) return;

    std::string error_msg(info_log_length+1, '\0');
    glGetShaderInfoLog(id, info_log_length, NULL, &error_msg[0]);
    std::cout << error_msg << std::endl;
    throw std::runtime_error("Error compiling shader:\n" + error_msg + "\n");
}

Shader::~Shader() {
    if(id < 0) return;
    glDeleteShader(id);
}

Shader Shader::make_vertex(const std::string &code) {
    return Shader(code, GL_VERTEX_SHADER);
}

Shader Shader::make_fragment(const std::string &code) {
    return Shader(code, GL_FRAGMENT_SHADER);
}

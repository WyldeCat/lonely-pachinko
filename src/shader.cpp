//
// shader.cpp
//

#include "shader.hpp"

Shader::Shader(GLenum shader_type, const std::string& source_url)
    : shader_type_(shader_type)
{
    std::string source_str = file_to_str(source_url);
    const char *source_ptr = source_str.c_str();

	shader_ = glCreateShader(shader_type_);
    glShaderSource(shader_, 1, &source_ptr, NULL);
    glCompileShader(shader_);

    if (!check_shader()) {
        glDeleteShader(shader_);
        shader_ = -1;
    }
}

Shader::~Shader()
{
    glDeleteShader(shader_);
}

GLuint Shader::GetShader()
{
    return shader_;
}

#include <iostream>
bool Shader::check_shader()
{
	// TODO : Not implemented
    GLint state;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &state);
    if (GL_FALSE == state) {
        int infologLength = 0;
        glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &infologLength);
        if (infologLength > 1) {
            int charsWritten = 0;
            char *infoLog = new char[infologLength];
            glGetShaderInfoLog(shader_, infologLength, &charsWritten, infoLog);
            std::cout << infoLog << std::endl;
            delete[] infoLog;
        }
        return false;
    }
    return true;
}


std::string Shader::file_to_str(const std::string& source_url)
{
    std::ifstream file(source_url);

    if (!file.is_open()) return "";

    return std::string(std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>());
}

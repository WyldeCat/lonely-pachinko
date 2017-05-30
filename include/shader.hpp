//
// shader.hpp
//

#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "GL/glew.h"

#include <string>
#include <fstream>

class Shader {
public:
    Shader(GLenum, const std::string& );
    // create, set and compile
    
    ~Shader();
    // delete

    GLuint GetShader();

private:
    friend class Simulator;
    static std::string file_to_str(const std::string& source_url);

    bool check_shader();

    GLuint shader_;
    GLenum shader_type_;
};

#endif

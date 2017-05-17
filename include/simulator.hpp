//
// simulator.hpp
//

#ifndef _SIMULATOR_HPP_
#define _SIMULATOR_HPP_

#include "../libs/physics-engine/src/phy_engine.hpp"

/* opengl */
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

/* STL */
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

/* custom class */
#include "object.hpp"
#include "shader.hpp"

class Simulator {
public:
    Simulator(int w, int h, const char* title); 
    // create GL Context

    ~Simulator();
  
    bool Initialize(const std::string& xml_url); 
    // load xml initalizing objects
                                              
    void Start();

private:
    bool check_program();
    void render();
    void pause();

    int frame_;
  
    // glfw
    GLFWwindow* window_;
    
    // glew
    GLuint shader_program_; 
    GLuint vertex_buffer_object_;

    // for test
    std::vector<glm::vec3> vertices_; 
    std::vector<std::unique_ptr<Object>> objects_;

};

#endif
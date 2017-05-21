//
// simulator.hpp
//

#ifndef _SIMULATOR_HPP_
#define _SIMULATOR_HPP_

#include "../libs/physics-engine/src/phy_engine.hpp"

/* pugi xml */
#include "../libs/pugixml-1.8/src/pugixml.hpp"

/* opengl */
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

/* STL */
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <iostream>

/* custom class */
#include "object.hpp"
#include "shader.hpp"

class Simulator {
public:
    // create GL Context
    Simulator() {}
    ~Simulator() {}

    void Init(int width, int height, glm::vec3 pos, const char* title);
                        
    static void Start();
    static bool Initialize(const std::string& xml_url);
    static void KeyCallback(int key, int scancode, int action, int mods);
    static void MouseMovCallback(double x, double y);
    static void Release();

private:
    static Simulator* instance;
    Simulator(int w, int h, glm::vec3 pos, const char* title);

    void start();
    bool initialize(const std::string& xml_url);
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_mov_callback(double x, double y);
   
    void load_shaders(const pugi::xml_node& shader_list);
    void load_objects(const pugi::xml_node& obj_list);
    void load_lights(const pugi::xml_node& light_list);

    void process_input();
    bool check_program();
    
    void calc_camera(glm::mat4 &, glm::vec3 &n, glm::vec3 &v, glm::vec3 &pos);
    void render();
    void pause();

    GLFWwindow* window_;
    
    GLuint shader_program_; 
    GLuint vertex_buffer_object_;

    glm::mat4 camera_;
    glm::mat4 world_;
    
    glm::mat4 Rx_; // for camera roatation
    glm::mat4 RRx_;
    glm::mat4 Ry_;
    glm::mat4 RRy_;
    glm::mat4 Rz_;
    glm::mat4 RRz_;

    glm::vec3 pos_;
    glm::vec3 target_;
    glm::vec3 view_up_;
    glm::vec3 axis_vert;
    glm::vec3 axis_horz;

    std::vector<std::unique_ptr<Object>> objects_;

    GLdouble prev_x;
    GLdouble prev_y;

    short key_stat[300]; // GL_PRESS, GL_REPEAT, GL_RELEASE
    bool first_touch;

    // for test
    std::vector<glm::vec3> vertices_;
};

#endif

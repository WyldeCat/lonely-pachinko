#include "simulator.hpp"

#include <iostream>

Simulator::Simulator(int width, int height, const char *title)
{
    window_ = NULL;

    if (!glfwInit()) {
        // TODO : error log
        exit(EXIT_FAILURE);
    }

    window_ = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window_) {
        // TODO : error log
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
}

Simulator::~Simulator()
{
    glDeleteProgram(shader_program_);
    glfwDestroyWindow(window_);
    glfwTerminate();
}

bool Simulator::Initialize(const std::string& xml_url)
{
    glewInit();

    glClearColor(1, 1, 1, 1);
    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE); // just for sure
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    std::vector<std::unique_ptr<Shader>> shaders;
    
    // test codes
    shaders.push_back(std::make_unique<Shader>(GL_VERTEX_SHADER,
        "../../../shaders/basic_shader.glvs"));
    shaders.push_back(std::make_unique<Shader>(GL_FRAGMENT_SHADER,
        "../../../shaders/basic_shader.glfs"));
    //

    shader_program_ = glCreateProgram();

    std::for_each(shaders.begin(), shaders.end(),
        [&](std::unique_ptr<Shader>& ptr) {
        glAttachShader(shader_program_, ptr->GetShader());
    });

    glLinkProgram(shader_program_);

    std::for_each(shaders.begin(), shaders.end(),
        [&](std::unique_ptr<Shader>& ptr) {
        glDetachShader(shader_program_, ptr->GetShader());
    });

    if (!check_program()) {
        // TODO : error log
        return false;
    }

    // test codes
    vertices_ = std::vector<glm::vec3>{
        glm::vec3(-0.5f, -0.5f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f),
        glm::vec3(0.5f, 0.5f, 0.f)
    };
    //

    glCreateBuffers(1, &vertex_buffer_object_);
    // test codes
    glNamedBufferData(vertex_buffer_object_, vertices_.size() * sizeof(glm::vec3),
        &vertices_[0], GL_STATIC_DRAW);

    return true;
}

void Simulator::Start()
{
    while (!glfwWindowShouldClose(window_)) {
        render();
        glfwSwapBuffers(window_);
    }
}

void Simulator::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, NULL);

    // test code
    glDrawArrays(GL_TRIANGLES, 0, vertices_.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}

void Simulator::pause()
{
    // TODO : Not implemented
}

bool Simulator::check_program()
{
    // TODO : Not implemented
    return true;
}
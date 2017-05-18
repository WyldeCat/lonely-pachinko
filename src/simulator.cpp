#include "simulator.hpp"

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

    glClearColor(0, 0, 0, 1);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // just for sure
    //glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    std::vector<std::unique_ptr<Shader>> shaders;
    
    // test codes
    shaders.push_back(std::make_unique<Shader>(GL_VERTEX_SHADER,
        "shaders/basic_shader.glvs"));
    shaders.push_back(std::make_unique<Shader>(GL_FRAGMENT_SHADER,
        "shaders/basic_shader.glfs"));
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
    glm::vec3 target(0, 0, 0); // target
    glm::vec3 v(-1, 2, -1);  // view-up vector
    glm::vec3 pos(0.3, 0.3, 0.3);

    v = glm::normalize(v);

    calc_camera(camera_, target, v, pos);
    
    vertices_ = std::vector<glm::vec3>{
      glm::vec3(0.0f, 0.0f, -0.1f),
      glm::vec3(0.3f, 0.0f, -0.1f),
      glm::vec3(0.0f, 0.3f, -0.1f),

      glm::vec3(0.3f, 0.0f, -0.1f),
      glm::vec3(0.3f, 0.3f, -0.1f),
      glm::vec3(0.0f, 0.3f, -0.1f),

      glm::vec3(0.3f, 0.0f, -0.1f),
      glm::vec3(0.3f, 0.0f, -0.4f),
      glm::vec3(0.3f, 0.3f, -0.1),

      glm::vec3(0.3f, 0.3f, -0.1),
      glm::vec3(0.3f, 0.0f, -0.4f),
      glm::vec3(0.3f, 0.3f, -0.4f)
    };
    	
	// glCreateBuffers(1, &vertex_buffer_object_);
	// glNamedBufferData(vertex_buffer_object_, vertices_.size() * sizeof(glm::vec3),
	//     &vertices_[0], GL_STATIC_DRAW);
	// iris 6100 doesn't support opengl 4.5 on windows

	glGenBuffers(1, &vertex_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
	// test codes
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), &vertices_[0], GL_STATIC_DRAW);

    return true;
}

void Simulator::Start()
{
    while (!glfwWindowShouldClose(window_)) {
        render();
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Simulator::calc_camera(glm::mat4 &mat, glm::vec3 &target, glm::vec3 &v,
    glm::vec3 &pos)
{
    // suppose u,v are normal
    glm::mat4 mat_tmp;
    glm::vec3 n = target - pos;
    n *= -1;
    glm::vec3 u = glm::cross(v, n);

    n = glm::normalize(n);
    u = glm::normalize(u);

    mat_tmp[0][0] = mat_tmp[1][1] = mat_tmp[2][2] = mat_tmp[3][3] = 1;
    mat_tmp[0][3] = -pos[0], mat_tmp[1][3] = -pos[1], mat_tmp[2][3] = -pos[2];

    mat[0][0] = u[0], mat[0][1] = u[1], mat[0][2] = u[2], mat[0][3] = 0;
    mat[1][0] = v[0], mat[1][1] = v[1], mat[1][2] = v[2], mat[1][3] = 0;
    mat[2][0] = n[0], mat[2][1] = n[1], mat[2][2] = n[2], mat[2][3] = 0;
    mat[3][0] = 0.0f, mat[3][1] = 0.0f, mat[3][2] = 0.0f, mat[3][3] = 1.0f;

    mat = mat_tmp * mat;
}

void Simulator::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program_);

    // pass camera matrix to shader
    GLint location = glGetUniformLocationARB(shader_program_, "wld2cam");
    glUniformMatrix4fvARB(location, 1, false, &camera_[0][0]);

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
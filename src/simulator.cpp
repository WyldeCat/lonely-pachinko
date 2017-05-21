#include "simulator.hpp"

#define _key_on(key) (key == GLFW_PRESS || key == GLFW_REPEAT )
#define PI 3.14159265

Simulator* Simulator::instance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Simulator::KeyCallback(key, scancode, action, mods);
}

void mouse_mov_callback(GLFWwindow* window, double x, double y)
{
    Simulator::MouseMovCallback(x, y);
}

void Simulator::Init(int w, int h, const char* title)
{
    instance = new Simulator(w, h, title);
}

void Simulator::Release()
{
    delete instance;
}

void Simulator::KeyCallback(int key, int scancode, int action, int mods)
{
    instance->key_callback(key, scancode, action, mods);
}

void Simulator::key_callback(int key, int scancode, int action, int mods)
{
    // have to calculate pos, considering target
    if (key < 0) return;
    if (key_stat[key] == action) return;
    key_stat[key] = action;
    process_input();
}

void Simulator::MouseMovCallback(double x, double y)
{
    instance->mouse_mov_callback(x, y);
}

void print_mat(glm::mat4 &x)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << x[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Simulator::mouse_mov_callback(double x, double y)
{
    int width, height;
    glfwGetWindowSize(window_, &width, &height);

    if (first_touch) {
        first_touch = false;
        glfwSetCursorPos(window_, width / 2, height / 2);
        return;
    }
    
    double delta_x = -(x - width / 2) / (width / 2);
    double delta_y = -(y - height / 2) / (height / 2); 
    if (delta_x == 0 && delta_y == 0) return;
    
    double sin_x = glm::sin(delta_x * 90 * PI / 180);
    double sin_y = glm::sin(delta_y * 90 * PI / 180);
    double cos_x = glm::cos(delta_x * 90 * PI / 180);
    double cos_y = glm::cos(delta_y * 90 * PI / 180);
    double d, l;

    glm::vec4 t;

    if (delta_y != 0) {

        d = glm::sqrt(axis_horz.y * axis_horz.y + axis_horz.z * axis_horz.z);
       
        RRx_[1][1] = RRx_[2][2] = Rx_[1][1] =
            Rx_[2][2] = (d != 0) ? (axis_horz.z / d) : 1;
        RRx_[2][1] = Rx_[1][2] = (d != 0) ? (axis_horz.y / d) : 0;
        RRx_[1][2] = Rx_[2][1] = (d != 0) ? (-axis_horz.y / d) : 0;

        RRy_[0][0] = RRy_[2][2] = Ry_[0][0] = Ry_[2][2] = d;
        RRy_[2][0] = Ry_[0][2] = axis_horz.x;
        RRy_[0][2] = Ry_[2][0] = -axis_horz.x;

        Rz_[0][0] = Rz_[1][1] = cos_y;
        Rz_[0][1] = sin_y;
        Rz_[1][0] = -sin_y;

        target_ -= pos_;

        t = glm::vec4(target_, 1);
        t = RRx_ * RRy_ * Rz_ * Ry_ * Rx_ * t;
       
        target_.x = t.x + pos_.x;
        target_.y = t.y + pos_.y;
        target_.z = t.z + pos_.z;

        view_up_ = glm::normalize(glm::cross(axis_horz, target_ - pos_));

    }
    if (delta_x != 0) {
        
        d = glm::sqrt(axis_vert.y * axis_vert.y + axis_vert.z * axis_vert.z);
       
        RRx_[1][1] = RRx_[2][2] = Rx_[1][1] =
            Rx_[2][2] = (d != 0) ? (axis_vert.z / d) : 1;
        RRx_[2][1] = Rx_[1][2] = (d != 0) ? (axis_vert.y / d) : 0;
        RRx_[1][2] = Rx_[2][1] = (d != 0) ? (-axis_vert.y / d) : 0;

        RRy_[0][0] = RRy_[2][2] = Ry_[0][0] = Ry_[2][2] = d;
        RRy_[2][0] = Ry_[0][2] = axis_vert.x;
        RRy_[0][2] = Ry_[2][0] = -axis_vert.x;

        RRz_[0][0] = RRz_[1][1] = Rz_[0][0] = Rz_[1][1] = cos_x;
        RRz_[1][0] = Rz_[0][1] = sin_x;
        RRz_[0][1] = Rz_[1][0] = -sin_x;

        target_ -= pos_;
        t = glm::vec4(target_, 1);
        t = glm::inverse(Rx_) * glm::inverse(Ry_)
            * Rz_ * Ry_ * Rx_ * t;
        target_.x = t.x + pos_.x;
        target_.y = t.y + pos_.y;
        target_.z = t.z + pos_.z;

        t = glm::vec4(axis_horz, 1);
        t = glm::inverse(Rx_) * glm::inverse(Ry_)
            * Rz_ * Ry_ * Rx_ * t;
        axis_horz.x = t.x;
        axis_horz.z = t.z;
        axis_horz = glm::normalize(axis_horz);
         
    }
    
    glfwSetCursorPos(window_, width / 2, height / 2);
    process_input();
}

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

    glfwSetKeyCallback(window_, ::key_callback);
    glfwSetCursorPosCallback(window_, ::mouse_mov_callback);

    target_ = glm::vec3(0, 0, 0);
    view_up_ = glm::normalize(glm::vec3(0, 1, 0));
    pos_ = glm::vec3(1, 0, 1);
    axis_horz = glm::vec3(1, 0, -1);
    axis_horz = glm::normalize(axis_horz);
    axis_vert = glm::vec3(0, 1, 0);
    axis_vert = glm::normalize(axis_vert);

    calc_camera(camera_, target_, view_up_, pos_);

    world_ = glm::mat4(0.0);
    world_[0][0] = world_[1][1] = world_[2][2] = 0.01;
    world_[3][3] = 1;

    Rx_[0][0] = Rx_[1][1] = Rx_[2][2] = Rx_[3][3] = 1;
    RRx_[0][0] = RRx_[1][1] = RRx_[2][2] = RRx_[3][3] = 1;
    Ry_[1][1] = Ry_[3][3] = 1;
    RRy_[1][1] = RRy_[3][3] = 1;
    Rz_[2][2] = Rz_[3][3] = 1;
    RRz_[2][2] = RRz_[3][3] = 1;

    first_touch = true;

    for (int i = 0; i < 300; i++) key_stat[i] = -1;
}

bool Simulator::Initialize(const std::string& xml_url)
{
    return instance->initialize(xml_url);
}

bool Simulator::initialize(const std::string& xml_url)
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
    
    vertices_ = std::vector<glm::vec3>{
      glm::vec3(0.0f, 0.0f, -10.0f),
      glm::vec3(10.0f, 0.0f, -10.0f),
      glm::vec3(0.0f, 10.0f, -10.0f),

      glm::vec3(10.0f, 0.0f, -10.0f),
      glm::vec3(10.0f, 10.0f, -10.0f),
      glm::vec3(0.0f, 10.0f, -10.0f),

      glm::vec3(10.0f, 0.0f, -10.0f),
      glm::vec3(10.0f, 0.0f, -20.0f),
      glm::vec3(10.0f, 10.0f, -10.0f),

      glm::vec3(10.0f, 10.0f, -10.0f),
      glm::vec3(10.0f, 0.0f, -20.0f),
      glm::vec3(10.0f, 10.0f, -20.0f)
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
    instance->start();
}

void Simulator::start()
{
    while (!glfwWindowShouldClose(window_)) {
        process_input();
        render();
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Simulator::process_input()
{
    if (_key_on(key_stat[87])) {
        glm::vec3 tmp = glm::normalize(target_ - pos_);
        tmp *= 0.01;
        pos_ += tmp;
        target_ += tmp;
    }
    if (_key_on(key_stat[65])) {
        axis_horz *= 0.01;
        pos_ -= axis_horz;
        target_ -= axis_horz;
        axis_horz *= 100;
    }
    if (_key_on(key_stat[83])) {
        glm::vec3 tmp = glm::normalize(target_ - pos_);
        tmp *= 0.01;
        pos_ -= tmp;
        target_ -= tmp;
    }
    if (_key_on(key_stat[68])) {
        axis_horz *= 0.01;
        pos_ += axis_horz;
        target_ += axis_horz;
        axis_horz *= 100;
    }

    calc_camera(camera_, target_, view_up_, pos_);
}
void Simulator::calc_camera(glm::mat4 &mat, glm::vec3 &target, glm::vec3 &v,
    glm::vec3 &pos)
{
    // suppose target and v are normalized

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
    GLint loc_cam = glGetUniformLocationARB(shader_program_, "wld2cam");
    glUniformMatrix4fvARB(loc_cam, 1, true, &camera_[0][0]);

    GLint loc_wld = glGetUniformLocationARB(shader_program_, "obj2wld");
    glUniformMatrix4fvARB(loc_wld, 1, true, &world_[0][0]);

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
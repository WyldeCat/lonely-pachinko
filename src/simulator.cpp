//
// simulator.cpp
//

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

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &target, 
    const glm::vec3 &axis_vert, const glm::vec3& axis_horz)
    : pos_(pos)
    , target_(target)
    , axis_vert_(axis_vert)
    , axis_horz_(axis_horz)
{
    calculate();
}

void Camera::Update(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &axis_horz)
{
    pos_ = pos;
    target_ = target;
    axis_horz_ = axis_horz;

    view_up_ = glm::normalize(glm::cross(axis_horz_, target_ - pos_));

    calculate();
}

glm::mat4& Camera::GetMatrix() { return mat_; }

void Camera::calculate()
{
    // suppose target and v are normalized
    glm::vec3 &v = view_up_;
    glm::mat4 mat_tmp;
    glm::vec3 n = target_ - pos_;
    n *= -1;
    glm::vec3 u = glm::cross(v, n);

    n = glm::normalize(n);
    u = glm::normalize(u);

    mat_tmp[0][0] = mat_tmp[1][1] = mat_tmp[2][2] = mat_tmp[3][3] = 1;
    mat_tmp[0][3] = -pos_[0], mat_tmp[1][3] = -pos_[1], mat_tmp[2][3] = -pos_[2];

    mat_[0][0] = u[0], mat_[0][1] = u[1], mat_[0][2] = u[2], mat_[0][3] = 0;
    mat_[1][0] = v[0], mat_[1][1] = v[1], mat_[1][2] = v[2], mat_[1][3] = 0;
    mat_[2][0] = n[0], mat_[2][1] = n[1], mat_[2][2] = n[2], mat_[2][3] = 0;
    mat_[3][0] = 0.0f, mat_[3][1] = 0.0f, mat_[3][2] = 0.0f, mat_[3][3] = 1.0f;

    mat_ = mat_tmp * mat_;
}

void Simulator::Init(int w, int h, glm::vec3 pos, const char* title)
{
    instance = new Simulator(w, h, pos, title);
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
    if (first_touch) {
        first_touch = false;
        glfwSetCursorPos(window_, width_ / 2, height_ / 2);
        return;
    }
    
    double delta_x = -(x - width_ / 2) / (width_ / 2);
    double delta_y = -(y - height_ / 2) / (height_ / 2); 
    if (delta_x == 0 && delta_y == 0) return;
    
    double sin_x = glm::sin(delta_x * 90 * PI / 180);
    double sin_y = glm::sin(delta_y * 90 * PI / 180);
    double cos_x = glm::cos(delta_x * 90 * PI / 180);
    double cos_y = glm::cos(delta_y * 90 * PI / 180);
    double d, l;

    glm::vec4 t;
    glm::vec3 axis_horz = curr_camera_.axis_horz_;
    glm::vec3 axis_vert = curr_camera_.axis_vert_;
    glm::vec3 target = curr_camera_.target_;
    glm::vec3 pos = curr_camera_.pos_; // Bad codes :(

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

        target -= pos;

        t = glm::vec4(target, 1);
        t = RRx_ * RRy_ * Rz_ * Ry_ * Rx_ * t;
       
        target.x = t.x + pos.x;
        target.y = t.y + pos.y;
        target.z = t.z + pos.z;

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

        target -= pos;
        t = glm::vec4(target, 1);
        t = glm::inverse(Rx_) * glm::inverse(Ry_)
            * Rz_ * Ry_ * Rx_ * t;
        target.x = t.x + pos.x;
        target.y = t.y + pos.y;
        target.z = t.z + pos.z;

        t = glm::vec4(axis_horz, 1);
        t = glm::inverse(Rx_) * glm::inverse(Ry_)
            * Rz_ * Ry_ * Rx_ * t;
        axis_horz.x = t.x;
        axis_horz.z = t.z;
        axis_horz = glm::normalize(axis_horz);
         
    }
    
    glfwSetCursorPos(window_, width_ / 2, height_ / 2);
    curr_camera_.Update(pos, target, axis_horz);
}

Simulator::Simulator(int width, int height, glm::vec3 pos, const char *title)
    : width_(width)
    , height_(height)
    , curr_camera_(pos, glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0))
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

    glewInit();

    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE); // just for sure
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

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

void Simulator::load_shaders(const pugi::xml_node& shader_list)
{
    std::vector<std::unique_ptr<Shader>> shaders;

    for (auto shader = shader_list.child("shader"); shader;
        shader = shader.next_sibling("shader")) {
        GLenum type;

        if (!strcmp("frag", shader.attribute("type").value())) {
            type = GL_FRAGMENT_SHADER;
        }
        else if (!strcmp("vert", shader.attribute("type").value())) {
            type = GL_VERTEX_SHADER;
        }
        else if (!strcmp("compute", shader.attribute("type").value())) {
            type = GL_COMPUTE_SHADER;
        }

        std::cout << "Load shader : " << shader.first_child().value() << std::endl;
        shaders.push_back(std::make_unique<Shader>(type,
            shader.first_child().value()));
    }

    shader_program_ = glCreateProgram();
    compute_program_ = glCreateProgram();

    std::for_each(shaders.begin(), shaders.end(),
        [&](std::unique_ptr<Shader>& ptr) {
        if (ptr->shader_type_ == GL_VERTEX_SHADER ||
            ptr->shader_type_ == GL_FRAGMENT_SHADER) {
            glAttachShader(shader_program_, ptr->GetShader());
        } else {
            glAttachShader(compute_program_, ptr->GetShader());
        }
    });

    glLinkProgram(shader_program_);
    glLinkProgram(compute_program_);

    std::for_each(shaders.begin(), shaders.end(),
        [&](std::unique_ptr<Shader>& ptr) {
        if (ptr->shader_type_ == GL_VERTEX_SHADER ||
            ptr->shader_type_ == GL_FRAGMENT_SHADER) {
            glDetachShader(shader_program_, ptr->GetShader());
        }
        else {
            glDetachShader(compute_program_, ptr->GetShader());
        }
    });
}

void Simulator::load_objects(const pugi::xml_node& obj_list)
{
    for (auto object = obj_list.child("object"); object;
        object = object.next_sibling()) {
        if (!strcmp(object.attribute("type").value(), "mesh")) {
            objects_.push_back(
                std::unique_ptr<Object>(new Mesh(object.child("file").first_child().value())
            ));
        }
    }
}

bool Simulator::initialize(const std::string& xml_url)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("config.xml");

    auto simulator = doc.child("simulator");
    auto shader_list = simulator.child("shader-list");
    auto object_list = simulator.child("object-list");

    int scale = simulator.attribute("scale").as_int();

    std::cout << "Scale : " << scale << std::endl;

    load_shaders(shader_list);
    load_objects(object_list);
    
    if (!check_program()) {
        // TODO : error log
        return false;
    }
    
    for (auto& object : objects_)
    {
        auto mesh = dynamic_cast<Mesh*>(object.get());
        if (mesh) {
            // TODO : It only supports vertex with normal
            for (auto& face : mesh->GetFaces()) {
                auto vertex = face->GetVertices().begin();
                auto normal = face->GetNormals().begin();
                for (;vertex != face->GetVertices().end(); vertex++, normal++) {
                    // the number of vertex has to 3
                    vertices_.push_back((*vertex)->pos_);
                    vertices_.push_back(*(*normal));
                }
            }
        } else {
            // TODO : Not implemented
            std::cout << "not mesh!!" << std::endl;
        }
    }

    // for compute shader
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width_, height_, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
     
	glGenBuffers(1, &vertex_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
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
        compute();
        render();
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Simulator::process_input()
{
    glm::vec3 axis_horz = curr_camera_.axis_horz_;
    glm::vec3 target = curr_camera_.target_;
    glm::vec3 pos = curr_camera_.pos_;

    if (_key_on(key_stat[87])) {
        glm::vec3 tmp = glm::normalize(target - pos);
        tmp *= 0.01;
        pos += tmp;
        target += tmp;
    }
    if (_key_on(key_stat[65])) {
        axis_horz *= 0.01;
        pos -= axis_horz;
        target -= axis_horz;
        axis_horz *= 100;
    }
    if (_key_on(key_stat[83])) {
        glm::vec3 tmp = glm::normalize(target - pos);
        tmp *= 0.01;
        pos -= tmp;
        target -= tmp;
    }
    if (_key_on(key_stat[68])) {
        axis_horz *= 0.01;
        pos += axis_horz;
        target += axis_horz;
        axis_horz *= 100;
    }

    curr_camera_.Update(pos, target, axis_horz);
}

void Simulator::compute()
{
    // TODO : Not implemented
    // invoke compute shader
}

void Simulator::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program_);

    // pass camera matrix to shader
    GLint loc_cam = glGetUniformLocationARB(shader_program_, "wld2cam");
    glUniformMatrix4fvARB(loc_cam, 1, true, &curr_camera_.mat_[0][0]);

    GLint loc_wld = glGetUniformLocationARB(shader_program_, "obj2wld");
    glUniformMatrix4fvARB(loc_wld, 1, true, &world_[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
    glEnableVertexAttribArray(0); // vertex pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1); // vertex normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindTexture(GL_TEXTURE_2D, texture_);
    glDrawArrays(GL_TRIANGLES, 0, vertices_.size());

    glBindTexture(GL_TEXTURE_2D, 0);
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
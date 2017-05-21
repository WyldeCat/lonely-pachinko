//
// object.hpp
//

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLM/glm.hpp"

class Object {
// interface class
public:
    virtual void Draw() = 0;
    virtual ~Object() = default;
};

class Sphere : public Object /* */ {
public:
    virtual void Draw();
private:

};

class Vertex {
public:
    Vertex(glm::vec3& pos);
    glm::vec3 pos_;
    glm::vec3 normal_;
};

class Face : public Object {
public:
    virtual void Draw();
private:
    std::vector<std::shared_ptr<Vertex>> vertices;
};


class Mesh : public Object {
public:
    virtual void Draw();
    Mesh(const std::string& obj_file);

private:
    std::vector<std::unique_ptr<Face>> faces_;
    std::vector<std::shared_ptr<Vertex>> vertices_;

    std::vector<std::shared_ptr<glm::vec3>> v_normals_;
    std::vector<std::shared_ptr<glm::vec2>> textures_;
};

#endif

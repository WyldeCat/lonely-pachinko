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
#include <algorithm>
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
    float radius_;
};

class Vertex {
public:
    Vertex(glm::vec3& pos);
    glm::vec3 pos_;
    glm::vec3 normal_;
};

class Token {
public:
    Token(const std::string& token)
    {
        char t, f;
        std::string ttt;
        v_ = t_ = n_ = -1;
        std::stringstream ss(token);
        ss >> v_ >> t >>  t_ >> t >> n_;
        if (ss.fail()) {
            ss.clear();
            ss.str(token);
            ss >> v_ >> t >> f >> n_;
            if (ss.fail()) {
                ss.clear();
                ss.str(token);
                ss >> v_;
            }
        }
    }
    int v_, t_, n_;
};




class Mesh : public Object {
public:
    class Face : public Object {
    public:
        Face(std::vector<Token>& tokens, Mesh& mesh);

        virtual void Draw();

        const std::vector<int>& GetVertices() { return vertices_; }
        const std::vector<int>& GetNormals() { return normals_; }
        const std::vector<int>& GetTextures() { return textures_; }

        int GetVertexIdx(int idx) { return vertices_[idx]; }
        
        std::shared_ptr<Vertex> GetVertex(int idx)
        {
            return mesh_.vertices_[vertices_[idx]];
        }
        std::shared_ptr<glm::vec3> GetNormal(int idx)
        {
            return mesh_.normals_[normals_[idx]];
        }
        std::shared_ptr<glm::vec2> GetTexture(int idx)
        {
            return mesh_.textures_[textures_[idx]];
        }

    private:
        Mesh& mesh_;

        std::vector<int> vertices_;
        std::vector<int> normals_;
        std::vector<int> textures_;
    };

    virtual void Draw();
    Mesh(const std::string& obj_file);

    const std::vector<std::unique_ptr<Face>>& GetFaces() { return faces_; }

private:
    std::vector<std::unique_ptr<Face>> faces_;
    std::vector<std::shared_ptr<Vertex>> vertices_;

    std::vector<std::shared_ptr<glm::vec3>> normals_;
    std::vector<std::shared_ptr<glm::vec2>> textures_;
};

#endif

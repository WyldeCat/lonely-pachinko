//
// object.cpp
//

#include "object.hpp"

Vertex::Vertex(glm::vec3 &pos)
    : pos_(pos)
{
}

Mesh::Face::Face(std::vector<Token>& tokens, Mesh& mesh)
    : mesh_(mesh)
{
    std::for_each(tokens.begin(), tokens.end(), [&](Token &token) {
        if (token.v_ != -1) vertices_.push_back(token.v_ - 1);
        if (token.n_ != -1) normals_.push_back(token.n_ - 1);
        if (token.t_ != -1) textures_.push_back(token.t_ - 1);
    });
}

void Mesh::Face::Draw()
{
    // TODO : Not implemented
}

Mesh::Mesh(const std::string& obj_file)
{
    std::fstream obj(obj_file);
    if (obj.is_open()) {
        for (std::string line; std::getline(obj, line);) {
            if (line[0] == '#' || line.size() == 0) continue;
            std::stringstream stream(line);
            std::string token;
            stream >> token;

            if (!token.compare("v")) {
                float x, y, z;
                stream >> x >> y >> z;
                vertices_.push_back(std::make_shared<Vertex>(glm::vec3(x, y, z)));
            }
            else if (!token.compare("vn")) {
                float x, y, z;
                stream >> x >> y >> z;
                normals_.push_back(std::make_shared<glm::vec3>(x, y, z));
            }
            else if (!token.compare("vt")) {
                float x, y;
                stream >> x >> y;
                textures_.push_back(std::make_shared<glm::vec2>(x, y));
            }
            else if (!token.compare("f")) {
                std::string token;
                std::vector<Token> tokens;
                
                while (stream >> token) tokens.push_back(Token(token));
                faces_.push_back(std::make_unique<Face>(tokens, *this));
            }
        }
        obj.close();
    } else {
        std::cerr << "# ERR: Can't open " << obj_file.data() << std::endl;
    }
} 

void Mesh::Draw()
{
    // TODO : Not implemented
}

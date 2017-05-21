//
// object.cpp
//

#include "object.hpp"

Vertex::Vertex(glm::vec3 &pos)
    : pos_(pos)
{
}

void Mesh::Draw()
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
            stream << token;

            // TODO : Not implemented

            if (!token.compare("v")) {
                float x, y, z;
                stream << x << y << z;
                vertices_.push_back(std::make_shared<Vertex>(glm::vec3(x,y,z)));
            } else if (!token.compare("vn")) {
                
            } else if (!token.compare("vt")) {

            } else if (!token.compare("f")) {

            }
            // doesn't support else
        }
        obj.close();
    } else {
        std::cerr << "# ERR: Can't open " << obj_file.data() << std::endl;
    }
}
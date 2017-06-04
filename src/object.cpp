//
// object.cpp
//

#include "object.hpp"

Sphere::Sphere(const glm::vec3& pos, float radius)
    : radius_(radius)
    , pos_(pos)
{
}

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

Mesh::Mesh(const std::string& obj_file, const std::string& texture_file,
    int material_idx)
    : material_idx_(material_idx)
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

    load_texture(texture_file);
} 

void Mesh::load_texture(const std::string& texture_file)
{
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int data_pos;     // Position in the file where the actual data begins
    unsigned int image_size;   // = width*height*3
                              // Actual RGB data
    
    FILE *file = fopen(texture_file.data(), "rb");
    fread(header, 1, 54, file);

    data_pos = *(int*)&(header[0x0A]);
    image_size = *(int*)&(header[0x22]);
    width_ = *(int*)&(header[0x12]);
    height_ = *(int*)&(header[0x16]);

    texture_ = new unsigned char[image_size];

    fread(texture_, 1, image_size, file);
    fclose(file);
}
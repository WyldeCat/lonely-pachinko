#include "header.hpp"

int main(int argc, char* argv[])
{
    Simulator::Init(1080, 1080, glm::vec3(0,0,0), "lonely_pachinko");
    
    if (Simulator::Initialize("config.xml")) {
        Simulator::Start();
    }

    return 0;
}

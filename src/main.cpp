#include "header.hpp"

int main(int argc, char* argv[])
{
    Simulator::Init(1024, 1024, glm::vec3(0.5,0,0.5), "lonely_pachinko");
    
    if (Simulator::Initialize("config.xml")) {
        Simulator::Start();
    }

    return 0;
}

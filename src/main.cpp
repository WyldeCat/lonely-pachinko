#include "header.hpp"

int main(int argc, char* argv[])
{
    Simulator simulator;
    simulator.Init(1080, 1080, glm::vec3(0,0,0), "lonely_pachinko");
    
    if (simulator.Initialize("config.xml")) {
        simulator.Start();
    }

    return 0;
}

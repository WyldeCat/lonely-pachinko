#include "header.hpp"

int main(int argc, char* argv[])
{
    Simulator simulator;
    simulator.Init(720, 720, "lonely_pachinko");
    
    if (simulator.Initialize("test.xml")) {
        simulator.Start();
    }

    return 0;
}

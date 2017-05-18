#include "header.hpp"

int main(int argc, char* argv[])
{
    Simulator simulator(640, 480, "lonely_pachinko");
    
    if (simulator.Initialize("test")) {
        simulator.Start();
    }

    return 0;
}

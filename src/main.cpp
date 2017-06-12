#include "header.hpp"

int main(int argc, char* argv[])
{
    Simulator::Init(1024, 1024, "lonely_pachinko", 60);
    
    if (Simulator::Initialize("config.xml")) {
        Simulator::Start();
    }

    return 0;
}

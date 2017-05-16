#include<iostream>
#include "phy_engine.hpp"
using namespace std;

__declspec (dllexport) void print()
{
	cout << "HELLO" << endl;
}


#pragma once

#ifdef PHYSICSENGINE_EXPORTS
#define PHYSICSENGINE_API __declspec(dllexport) 
#else
#define PHYSICSENGINE_API __declspec(dllimport) 
#endif

#include <string>
#include <assert.h>
#include <cmath>

#include "math.hpp"
#include "point_mass.hpp"
#include "rigid_body.hpp"
#include "plane.hpp"
#include "phy_engine.hpp"
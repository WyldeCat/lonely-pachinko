#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#define GLFW_DLL
#define GLFW_INCLUDE_GLU

/* OpenGL */
#ifdef __APPLE__
  // Because of version difference between Mac and Win,
  // can't support mac
#else 
  #include "GL/glew.h"
  #include "GLFW/glfw3.h"
#endif

/* Simulator */
#include "simulator.hpp"

/* STL */
#include <iostream>

#endif

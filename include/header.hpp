#ifndef _HEADER_HPP_
#define _HEADER_HPP_

/* OpenGL */
#ifdef __APPLE__
  // Because of version difference between Mac and Win,
  // can't support mac
#else 
  #include <Windows.h>
  #include <GL/glew.h>
  #include <GL/glut.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

/* Simulator */
#include "simulator.hpp"

/* Else */
#include <iostream>

#endif

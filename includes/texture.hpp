#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "colors.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

GLuint loadBMP(const char *imagepath);

#endif
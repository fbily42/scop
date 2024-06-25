#ifndef SHADERS_HPP
#define SHADERS_HPP

#include "colors.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath);

#endif
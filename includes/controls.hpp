#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "colors.h"
#include <GLFW/glfw3.h>
#include "mat4.hpp"
#include "vec3.hpp"

Mat4	getViewMatrix();
Mat4	getProjectionMatrix();
void	computeMatricesFromInputs(GLFWwindow* window, float width, float height);

#endif
#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include "colors.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "vec2.hpp"
#include "vec3.hpp"

void	loadOBJ(
	const char * path,
	std::vector<Vec3>& out_vertices,
	std::vector<Vec2>& out_uvs,
	std::vector<Vec3>& out_normals
);

#endif
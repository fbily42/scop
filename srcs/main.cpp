#include <iostream>
#include "colors.h"
#include <GLFW/glfw3.h>

int main() {

	if (!glfwInit()) {
		std::cerr << RED << "Failed to initialize GLFW." << RESET << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Test 01", NULL, NULL);
	if (window == NULL) {
		std::cerr << RED << "Failed to open GLFW window." << RESET << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
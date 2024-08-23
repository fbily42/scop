#include <iostream>
#include "shaders.hpp"
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "controls.hpp"
#include "objLoader.hpp"

int main() {

	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << RED << "Failed to initialize GLFW." << RESET << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Scop", NULL, NULL);
	if (window == NULL) {
		std::cerr << RED << "Failed to open GLFW window." << RESET << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << RED << "Failed to initialize GLEW." << RESET << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set cursor in the middle of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// create a Vertex Array Object and set it as the current one
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Compile and load shaders
	GLuint programID = LoadShaders("./shaders/SimpleVertexShader.vertexshader", "./shaders/SimpleFragmentShader.fragmentshader");
	
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Identity matrix for model
	Mat4 Model;

	std::vector<Vec3> vertices;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	loadOBJ("./3DObj/cubeTuto.obj", vertices, uvs, normals);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), &vertices[0], GL_STATIC_DRAW);

	// GLuint colorbuffer;
	// glGenBuffers(1, &colorbuffer);
	// glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MPV matrix from keyboard and mouse input
		computeMatricesFromInputs(window, 1024, 768);
		Mat4 Projection = getProjectionMatrix();
		Mat4 View = getViewMatrix();
		Mat4 MVP = Projection * View * Model;

		// Send our transformation to the currently bound shader, in MVP uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, MVP.getFirstElement());

		// Attribute buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Colors
		// glEnableVertexAttribArray(1);
		// glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		// glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glDisableVertexAttribArray(0);
		// glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glfwDestroyWindow(window);
	glDeleteBuffers(1, &vertexbuffer);
	// glDeleteBuffers(1, &colorbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	//Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
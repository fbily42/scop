#include <iostream>
#include "shaders.hpp"
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

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
	window = glfwCreateWindow(1024, 768, "3D Triangle", NULL, NULL);
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

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// create a Vertex Array Object and set it as the current one
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Compile and load shaders
	GLuint programID = LoadShaders("./shaders/SimpleVertexShader.vertexshader", "./shaders/SimpleFragmentShader.fragmentshader");
	
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Mat4 Projection = Mat4::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera Matrix
	Mat4 View = Mat4::lookAt(
		Vec3(4,3,3), // Camera is at (4,3,3) in World Space
		Vec3(0,0,0), // Looks at the origin
		Vec3(0,1,0) // Head is up
	);

	// Identity matrix for model
	Mat4 Model;

	//ModelViewProjection : multiplication of our 3 matrices
	// Mat4 MVP = Projection * View * Model;
	Mat4 MVP = Projection * View * Model;

	// Our triangle vertexs
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, in MVP uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, MVP.getFirstElement());

		// Attribute buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glfwDestroyWindow(window);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	//Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
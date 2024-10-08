#include "scop.hpp"

int main(int argc, char *argv[]) {

	float rotationAngle = 0.0f;
	float blendFactor = 0.0f;
	bool useTexture = false;
	bool keyPressed = false;
	bool colorKeyPressed = false;
	bool useColors = false;

	if (argc != 2) {
		std::cerr << RED << "Use: ./scop <path_to_3D_object>" << RESET << std::endl;
		return -1;
	}

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
	window = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL);
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
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set cursor in the middle of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, WIDTH/2, HEIGHT/2);

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

	GLuint programID;
	try
	{	// Compile and load shaders
		programID = LoadShaders("./shaders/SimpleVertexShader.vertexshader", "./shaders/SimpleFragmentShader.fragmentshader");
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Identity matrix for model
	Mat4 Model;

	// Load texture
	GLuint Texture;
	try
	{
		Texture = loadBMP("./texture/unicornTexture.bmp");
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	
	GLuint blendFactorID = glGetUniformLocation(programID, "blendFactor");
	GLuint textureID = glGetUniformLocation(programID, "textureSampler");

	// Read .obj file
	std::vector<Vec3> vertices;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	try
	{
		loadOBJ(argv[1], vertices, uvs, normals);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
		glfwDestroyWindow(window);
		glDeleteTextures(1, &Texture);
		glDeleteProgram(programID);
		glfwTerminate();
		return -1;
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vec2), &uvs[0], GL_STATIC_DRAW);

	// Generate random colors
	GLfloat g_color_buffer_data[vertices.size() * 3];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.2f, 0.9f);
	for (unsigned int v = 0; v < vertices.size(); v++) {
		g_color_buffer_data[3 * v + 0] = dis(gen);
		g_color_buffer_data[3 * v + 1] = dis(gen);
		g_color_buffer_data[3 * v + 2] = dis(gen);
	}

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	// Generate grey shades
	GLfloat grey_buffer_data[vertices.size() * 3];
	for (unsigned int v = 0; v < vertices.size(); v++) {
		float grey = dis(gen);
		grey_buffer_data[3 * v + 0] = grey;
		grey_buffer_data[3 * v + 1] = grey;
		grey_buffer_data[3 * v + 2] = grey;
	}

	GLuint greybuffer;
	glGenBuffers(1, &greybuffer);
	glBindBuffer(GL_ARRAY_BUFFER, greybuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(grey_buffer_data), grey_buffer_data, GL_STATIC_DRAW);
	
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {

		// Switch between colors/grey and texture
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !keyPressed) {
			useTexture = !useTexture;
			keyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) {
        	keyPressed = false;
		}

		// Switch between colors and grey
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !colorKeyPressed && !useTexture) {
			useColors = !useColors;
			colorKeyPressed = true;
		}
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
			colorKeyPressed = false;
		}

		// Used for smoother transition between colors and texture
		if (useTexture && blendFactor < 1.0f) {
			blendFactor += 0.01f;
		} else if (!useTexture && blendFactor > 0.0f) {
			blendFactor -= 0.01f;
		}
		blendFactor = std::clamp(blendFactor, 0.0f, 1.0f);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MPV matrix from keyboard and mouse input
		computeMatricesFromInputs(window, WIDTH, HEIGHT);
		Mat4 Projection = getProjectionMatrix();
		Mat4 View = getViewMatrix();

		//Rotate on itself
		rotationAngle += 0.2f;
		Model = Model.transformObject(vertices, rotationAngle, Vec3(0.0f,1.0f,0.0f));
		
		Mat4 MVP = Projection * View * Model;

		// Send our transformation to the currently bound shader, in MVP uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, MVP.getFirstElement());

		glUniform1f(blendFactorID, blendFactor);
		if (useTexture || blendFactor > 0.0f) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture);
			glUniform1i(textureID, 0);
		}

		// Attribute buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Colors-Grey
		glEnableVertexAttribArray(1);
		if (useColors) {
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		} else {
			glBindBuffer(GL_ARRAY_BUFFER, greybuffer);
		}
		glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		// UVs
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glfwDestroyWindow(window);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteBuffers(1, &greybuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteTextures(1, &Texture);
	glDeleteProgram(programID);

	//Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
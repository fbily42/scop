#include "controls.hpp"

Mat4 ViewMatrix;
Mat4 ProjectionMatrix;

Mat4 getViewMatrix() {
	return ViewMatrix;
}

Mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

Vec3 position(0,0,5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 90.0f;
float speed = 3.0f;
float mouseSpeed = 0.005f;

void computeMatricesFromInputs(GLFWwindow* window, float width, float height) {

	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = static_cast <float> (currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width / 2, height / 2);

	horizontalAngle += mouseSpeed * static_cast <float> (width / 2 - xpos);
	verticalAngle += mouseSpeed * static_cast <float> (height / 2 - ypos);

	Vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	Vec3 right(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14/2.0f)
	);

	Vec3 up(right.cross(direction));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	ProjectionMatrix = Mat4::perspective(initialFoV, width / height, 0.1f, 100.0f);

	ViewMatrix = Mat4::lookAt(
		position,
		position + direction,
		up
	);

	lastTime = currentTime;
}
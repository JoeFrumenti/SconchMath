#include "InputManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

InputManager::InputManager() {
	window = Window::getInstance().get();
}

glm::vec3 InputManager::getMouseMovement() {
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	int winWidth, winHeight;
	glfwGetWindowSize(window, &winWidth, &winHeight);

	// Convert to normalized -1..1 range, flip Y so up is positive
	float x = (float)(mouseX / winWidth) * 2.0f - 1.0f;

	return glm::vec3(x, 0, 0);
}



glm::vec3 InputManager::getInput() {
	int x = 0;
	int y = 0;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		x++;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		x--;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		y++;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		y--;
	return glm::vec3(x, y,0);
}

glm::vec3 InputManager::getInputWASD() {
	int x = 0;
	int y = 0;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		x++;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		x--;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		y++;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		y--;
	return glm::vec3(x, y, 0);
}

bool InputManager::isE() {
	return glfwGetKey(window, GLFW_KEY_E);
}
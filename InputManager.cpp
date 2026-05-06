#include "InputManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

InputManager::InputManager() {
	window = Window::getInstance().get();
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
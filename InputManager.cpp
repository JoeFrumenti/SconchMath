#include "InputManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

InputManager::InputManager(GLFWwindow* w) {
	window = w;

}

glm::vec2 InputManager::getInput() {
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
	return glm::vec2(x, y);
}
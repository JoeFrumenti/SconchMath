#include "InputManager.h"



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

int InputManager::getPressedKey() {
	// GLFW key range: 32 (SPACE) to 348 (last defined key)
	for (int key = 32; key <= GLFW_KEY_LAST; key++) {
		int state = glfwGetKey(window, key);

		if (state == GLFW_PRESS) {
			// Only return the key if it wasn't already held last frame
			if (heldKeys.find(key) == heldKeys.end()) {
				heldKeys.insert(key);
				return key;
			}
		}
		else if (state == GLFW_RELEASE) {
			heldKeys.erase(key);
		}
	}

	return -1; // No new key pressed this frame
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
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_set>

#include "Window.h"


class InputManager {
private:
	GLFWwindow* window;
	std::unordered_set<int> heldKeys;

public: 
	InputManager();
	glm::vec3 getInput();
	glm::vec3 getInputWASD();
	glm::vec3 getMouseMovement();

	static InputManager& getInstance() {
		static InputManager instance;
		return instance;
	}

	int getPressedKey();

	bool isE();


};
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class InputManager {
private:
	GLFWwindow* window;

public: 

	InputManager(GLFWwindow* w);
	glm::vec2 getInput();


};
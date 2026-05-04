#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
	unsigned int SCR_WIDTH = 450;
	unsigned int SCR_HEIGHT = 800;
	GLFWwindow* window;


public:
	Window();
	static Window& getInstance() {
		static Window instance;
		return instance;
	}
	void initWindow();

	GLFWwindow* get();

};
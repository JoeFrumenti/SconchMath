#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Character.h"

#include "Shaders/shader.h"

#include <string>
#include <map>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Text {
private:

	int scale = 50;

	// settings
	const unsigned int SCR_WIDTH = 9 * scale;
	const unsigned int SCR_HEIGHT = 16 * scale;

	unsigned int VAO, VBO;
	std::map<char, Character> Characters;
public:
	void RenderText(Shader& s, std::string text, float x, float y, float scale,
		glm::vec3 color);
	Text(Shader* textShader);
};
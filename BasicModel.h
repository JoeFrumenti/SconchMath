#pragma once

#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include "InputManager.h"

#include <iostream>

class BasicModel : public UD {
private:
	Model* ourModel;
	glm::mat4 model;

	glm::vec3 pos;
	float angle;
	glm::vec3 rot;
	glm::vec3 sca = glm::vec3(1.0f, 1.0f, 1.0f);


	Shader* shader;

	glm::vec3 velocity = glm::vec3(0.25f, 0.25f, 0.0f);
	bool isInput = false;

public:

	BasicModel(Shader* shade, char* path);

	void setInput(bool inp);

	void Update() override;

	void Draw() override;
	void translate(glm::vec3 translation);

	void rotate(float a, glm::vec3 translation);

	void scale(glm::vec3 translation);

	glm::vec3 getPos() override;
};
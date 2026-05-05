#pragma once

#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>
#include <vector>

#include "SoundManager.h"

#include "CollisionManager.h"
#include "Text.h"

#include <cmath>

#include "InputManager.h"

class BouncingCube : public UD {

private:
	Model* ourModel;

	glm::mat4 model;

	SoundManager& soundMan = SoundManager::getInstance();

	string coinString = "x12";

	bool isInput = false;

	Shader* shader;

	Shader* textShader;
	Text* vs;

	int player = 1;

public:

	Model* getModel();
	void setPlayer(int p);
	BouncingCube(Shader* shade, std::string path, Shader* ts);
	float dot(glm::vec2 a, glm::vec2 b);
	void Collide(Collision col);
	void screenBounce();
	void Update() override;
	void Draw() override;
	void translate(glm::vec3 translation);
	void drawText() override;
};
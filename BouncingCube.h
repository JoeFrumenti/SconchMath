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


public:

	Model* getModel();
	BouncingCube(Shader* shade, std::string path, Shader* ts);
	void Collide(Collision col);
	void screenBounce();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
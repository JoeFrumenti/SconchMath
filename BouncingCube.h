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
#include "ShaderCollection.h"
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
	

public:
	~BouncingCube();
	Model* getModel();
	BouncingCube(std::string path);
	void Collide(Collision col);
	void screenBounce();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
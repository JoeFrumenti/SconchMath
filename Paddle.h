#pragma once
#include "UD.h"
#include "Model.h"
#include "ShaderCollection.h"
#include "BouncingCube.h"
#include "InputManager.h"
#include "BallContainer.h"
class Paddle : public UD {
private:
	InputManager input = InputManager::getInstance();

	Model* ourModel;
	glm::mat4 model;
	Shader* shader;

	glm::vec3 lastPos;

	float speed = .5f;
public:
	Paddle();
	void Update() override;
	void Draw() override;
	void Collide(Collision col) override;
};

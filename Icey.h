#pragma once
#include "BouncingCube.h"
#include <algorithm>

class Icey : public UD {
private:
	Model* ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/ice.obj");
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	CollisionManager& cm = CollisionManager::getInstance();
	glm::mat4 model;
	float freezeTime = 1;

public:
	Icey();

	void setParent(UD* parent) override;

	void Update();
	void Draw();
	void drawText();

	void Collide(Collision col) override;
};
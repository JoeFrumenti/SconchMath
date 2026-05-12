#pragma once
#pragma once
#include "UD.h"
#include "CollisionManager.h"
#include "GameManager.h"
#include "Projectile.h"

class Orbital :public UD {
protected:
	bool isActive = false;
	Model* ourModel;
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	glm::mat4 model;
	int bounces = 0;
	CollisionManager& cm = CollisionManager::getInstance();
	float debuffTime = 1.0f;
public:
	void setParent(UD*) override;
	void launch();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
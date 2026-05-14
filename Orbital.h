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
	BouncingCube* Parent;
	
public:
	void setParent(BouncingCube*);
	void launch();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
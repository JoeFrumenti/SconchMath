#pragma once
#include "BouncingCube.h"
#include "Orbital.h"
#include <algorithm>

class Icey : public Orbital {
private:
	
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	CollisionManager& cm = CollisionManager::getInstance();
	glm::mat4 model;
	float freezeTime = 1;

public:
	Icey();




	void Collide(Collision col) override;
};
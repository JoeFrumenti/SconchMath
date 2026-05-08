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
#include "MyTimer.h"

class BouncingCube : public UD {

private:
	Model* ourModel;
	glm::mat4 model;
	glm::vec4 color = glm::vec4(1,1, 1, 1);
	SoundManager& soundMan = SoundManager::getInstance();
	
	Shader* shader;
	Shader* textShader;
	
	bool loser = false;
	float loserScale = 1.0f;
	
	MyTimer& timer = MyTimer::getInstance();

	float freezeStartTime = 0;
	float freezeDuration = 0;
	bool isFrozen = false;
	glm::vec3 frozenVelocity;

	bool isSlowed;
	float slowTimer;
	float slowCap;

public:
	~BouncingCube();
	Model* getModel();
	BouncingCube(std::string path);
	void Collide(Collision col);
	void screenBounce();
	void Update() override;
	void Draw() override;
	void drawText() override;
	void lose();
	void freeze(float);
	void slow(float);

	bool getFrozen() { return isFrozen; }
	glm::vec3 getFrozenVelocity() { return frozenVelocity; }
};
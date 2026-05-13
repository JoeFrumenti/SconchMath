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

struct PlayerStats {
	std::string winSound;
	std::string name;
	float debuffTime = 1.0f;
	int coins = 0;

};


class BouncingCube : public UD {

private:
	Model* ourModel;
	glm::mat4 model;
	glm::vec4 color = glm::vec4(1,1, 1, 1);
	SoundManager& soundMan = SoundManager::getInstance();
	PlayerStats stats;
	
	Shader* shader;
	Shader* textShader;
	
	bool loser = false;
	float loserScale = 1.0f;
	
	MyTimer& timer = MyTimer::getInstance();

	float freezeStartTime = 0;
	float freezeDuration = 0;
	bool isFrozen = false;
	glm::vec3 frozenVelocity;

	bool isSlowed = false;
	float slowTimer = 0;
	float slowCap = 0;

	float speed = .25f;

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
	void win();

	bool getFrozen() { return isFrozen; }
	bool getSlow() { return isSlowed; }
	glm::vec3 getFrozenVelocity() { return frozenVelocity; }

	PlayerStats& getStats() { return this->stats; }
};
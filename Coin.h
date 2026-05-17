#pragma once

#include "UD.h"
#include "Model.h"
#include "ShaderCollection.h"

#include <iostream>


#include "SoundManager.h"

#include "CollisionManager.h"
#include "UDManager.h"


class Coin : public UD {
private:
	Model* ourModel;
	glm::mat4 model;
	glm::vec3 pos;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 white = glm::vec4(.2f, .2f, .2f, 1.0f);

	Shader* shader;

	CollisionManager& cm = CollisionManager::getInstance();
	UDManager& UDMan = UDManager::getInstance();

	SoundManager& soundMan = SoundManager::getInstance();

	double timer = .1;
	bool timerRunning = false;

	int collisions = 0;
	float scaling = 1.2f;

public:

	Coin();
	Coin(int i);
	~Coin();

	void Update() override;

	void Draw() override;
	void translate(glm::vec3 t);
	glm::vec3 getPos();

	void Collide(Collision col) override;

};
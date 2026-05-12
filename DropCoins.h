#pragma once
#include "BouncingCube.h"
#include "Coin.h"

class DropCoins : public UD {
private:
	CollisionManager& cm = CollisionManager::getInstance();
	glm::vec3 lastPos;
	int idNum = 300;
	Shader* modelShader;
	UDManager& UDMan = UDManager::getInstance();

public:
	DropCoins();

	void setParent(UD* parent) override;

	void Update();
	void Draw() override;
	void drawText() override;
};
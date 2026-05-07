#pragma once
#include "UD.h"
#include "BouncingCube.h"
#include "Text.h"
#include "BasicModel.h"


class PlayerManager: public UD {
private:
	InputManager& input = InputManager::getInstance();

	glm::vec2 textPos = glm::vec2(135.0f,729.0f);

	BouncingCube* p1;
	BouncingCube* p2;
	int winner = 0;
	UDManager& UDMan = UDManager::getInstance();
	CollisionManager& cm = CollisionManager::getInstance();
	std::string message = "100    = WIN";
	Text* display;
	float loserScale = 1.0f;
	BasicModel* coin;

public:
	PlayerManager(BouncingCube* a, BouncingCube* b);

	void Update() override;
	void Draw() override;
	void drawText() override;
};
#pragma once
#include "UD.h"
#include "BouncingCube.h"
#include "Text.h"
#include "BasicModel.h"
#include <iomanip>

class PlayerManager: public UD {
private:
	InputManager& input = InputManager::getInstance();

	glm::vec2 textPos = glm::vec2(135.0f,729.0f);
	glm::vec2 p1Stats = glm::vec2(32.0f, 177.0f);
	glm::vec2 p2Stats = glm::vec2(305.0f, 177.0f);

	std::string p1StatMsg = "Slow time: 1";
	std::string p2StatMsg = "Freeze time : 1";

	BouncingCube* p1;
	BouncingCube* p2;
	int winner = 0;
	UDManager& UDMan = UDManager::getInstance();
	CollisionManager& cm = CollisionManager::getInstance();
	std::string message = "100    = WIN";
	Text* display;
	float loserScale = 1.0f;
	BasicModel* coin;

	std::ostringstream oss;

public:
	PlayerManager(BouncingCube* a, BouncingCube* b);
	PlayerManager();
	void Update() override;
	void Draw() override;
	void drawText() override;

	BouncingCube* getp1() { return p1; }
	BouncingCube* getp2() { return p2; }
};
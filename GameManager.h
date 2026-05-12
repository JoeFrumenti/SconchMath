#pragma once
#include "UD.h"
#include "BouncingCube.h"
#include "Text.h"
#include "BasicModel.h"
#include <iomanip>

class GameManager: public UD {
private:
	InputManager& input = InputManager::getInstance();

	glm::vec2 textPos = glm::vec2(135.0f,729.0f);
	
	glm::vec2 p2Stats = glm::vec2(305.0f, 177.0f);

	std::string p1StatMsg = "Slow time: 1";
	std::string p2StatMsg = "Freeze time : 1";

	BouncingCube* players[4] = { NULL,NULL,NULL,NULL };
	int winner = 0;
	UDManager& UDMan = UDManager::getInstance();
	CollisionManager& cm = CollisionManager::getInstance();
	std::string message = "100    = WIN";
	Text* display;
	float loserScale = 1.0f;
	BasicModel* coin;

	float UDtimer = 0;
	std::ostringstream oss;

public:
	GameManager(BouncingCube* a, BouncingCube* b);
	GameManager();
	void Update() override;
	void Draw() override;
	void drawText() override;

	void setp1(BouncingCube* player) { players[0] = player; }
	void setp2(BouncingCube* player) { players[1] = player; }

	BouncingCube* getp1() { return players[0]; }
	BouncingCube* getp2() { return players[1]; }

	static GameManager& getInstance() {
		static GameManager instance;
		return instance;
	}
};
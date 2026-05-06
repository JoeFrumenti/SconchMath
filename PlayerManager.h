#pragma once
#include "UD.h"
#include "BouncingCube.h"
#include "Text.h"
#include "BasicModel.h"


class PlayerManager: public UD {
private:
	InputManager& input = InputManager::getInstance();

	BouncingCube* p1;
	BouncingCube* p2;
	bool win = false;
	UDManager& UDMan = UDManager::getInstance();
	CollisionManager& cm = CollisionManager::getInstance();
	std::string message = "100    = WIN";
	Text* display;
	float textScale = 1.0f;
	BasicModel* coin;

public:
	PlayerManager(BouncingCube* a, BouncingCube* b);

	void Update() override;
	void Draw() override;
	void drawText() override;
};
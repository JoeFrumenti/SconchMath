#pragma once
#include "UD.h"
#include "CollisionManager.h"
#include "PlayerManager.h"

class Launcher:public UD {
private:
	UD* projectile;
	CollisionManager& cm = CollisionManager::getInstance();
	float launchTimer = 0;
	PlayerManager* playMan;
public:
	void setParent(UD*) override;
	Launcher(UD*, PlayerManager*);
	void launch();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
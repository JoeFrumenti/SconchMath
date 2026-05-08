#pragma once
#include "UD.h"
#include "CollisionManager.h"

class Launcher:public UD {
private:
	UD* projectile;
	CollisionManager& cm = CollisionManager::getInstance();
	float launchTimer = 0;
public:
	void setParent(UD*) override;
	Launcher(UD*);
	void launch();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
#pragma once
#include "BouncingCube.h"

class CoinPickup : public UD {
private:
	CollisionManager& cm = CollisionManager::getInstance();

public:
	CoinPickup();

	void setParent(UD* parent) override;

	void Update();
	void Draw();
	void drawText();

	void Collide(Collision col) override;
};
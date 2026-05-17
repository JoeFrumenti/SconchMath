#pragma once
#include "Projectile.h"
#include "Coin.h"
#include "UDManager.h"

class MoneyLine : public Projectile {
private:
	MyTimer& myTimer = MyTimer::getInstance();
	float timer = 0.0f;
	int coinsDropped = 0;
public:
	MoneyLine(BouncingCube* parent);


	void Update() override;
	void Draw() override;
};


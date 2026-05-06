#pragma once
#include "UD.h"
#include "BouncingCube.h"

class PlayerManager: public UD {
private:
	BouncingCube* p1;
	BouncingCube* p2;

public:
	PlayerManager(BouncingCube* a, BouncingCube* b);

	void Update() override;
	void Draw() override;
};
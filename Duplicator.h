#pragma once
#include "UD.h"
#include "BouncingCube.h"
class Duplicator : public UD {
	Duplicator();
	
	void Update() override;
	void Collide(Collision col) override;
	
};
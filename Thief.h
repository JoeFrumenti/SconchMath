#pragma once
#include "Projectile.h"
#include "UD.h"
#include "Model.h"
#include "BouncingCube.h"
class Thief : public Projectile {
private:
	bool stolen = false;
	bool touchingParent = false;
public:
	Thief(BouncingCube* parent);


	void Collide(Collision col) override;
	void Update() override;
	void exitCollision(Collision col) override;
		 
};


#pragma once
#include "UD.h"
#include "Model.h"
#include "Projectile.h"
#include "BouncingCube.h"
#include <random>

#include <algorithm>
class SlimeBall : public Projectile {


public:
	SlimeBall(BouncingCube* parent);


	void Collide(Collision col) override;

	void Update() override;

};
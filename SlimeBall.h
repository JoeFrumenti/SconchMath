#pragma once
#include "UD.h"
#include "Model.h"
#include "Projectile.h"
#include "BouncingCube.h"

#include <algorithm>
class SlimeBall : public Projectile {


public:
	SlimeBall();



	void Collide(Collision col) override;


};
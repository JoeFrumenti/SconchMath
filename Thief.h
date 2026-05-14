#pragma once

class Thief : public Projectile {
public:
	Thief(BouncingCube* parent);


	void Collide(Collision col) override;


};


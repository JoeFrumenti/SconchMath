#pragma once
#include "UD.h"

class Launcher:public UD {
private:
	UD* projectile;
	float launchTimer = 0;
public:
	void setParent(UD*) override;
	Launcher(UD*);
	void launch();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
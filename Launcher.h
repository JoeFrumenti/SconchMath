#pragma once
#include "UD.h"

class Launcher:public UD {
private:
	UD* projectile;
public:
	void setParent(UD*) override;
	Launcher(UD*);
	void launch();
	void Update() override;
	void Draw() override;
	void drawText() override;
};
#pragma once
#include "UD.h"
#include "Model.h"
#include "ShaderCollection.h"
#include "BouncingCube.h"
#include "InputManager.h"
class Paddle : public UD {
private:
	InputManager input = InputManager::getInstance();
public:
	Paddle();
	void Update() override;
	void Draw() override;
	void Collide(Collision col) override;
};

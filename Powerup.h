#pragma once
#include "CollisionManager.h"
#include "Model.h"
#include "ShaderCollection.h"
#include "MyTimer.h"
class Powerup :public UD {
private:
	Model* ourModel;
	glm::mat4 mMatrix;
	Shader* shader;
	int type = 0;
	float myTimer = 0;

public:
	Powerup(int type);
	void Update() override;
	void Draw() override;
	int getType() { return type; }
};

#pragma once
#include "UD.h"
#include "CollisionManager.h"
#include "Model.h"
#include "ShaderCollection.h"

class Block : public UD {
private:
	glm::mat4 model;
	Model* ourModel;
	Shader* shader;
public:
	Block();
	void Update() override;
	void Draw() override;
	void Collide(Collision col) override;
};
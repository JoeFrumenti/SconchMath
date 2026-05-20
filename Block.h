#pragma once
#include "UD.h"
#include "CollisionManager.h"
#include "Model.h"
#include "ShaderCollection.h"
#include "BouncingCube.h"
#include "BlockGrid.h"
#include <random>

class Block : public UD {
private:
	glm::mat4 model;
	Model* ourModel;
	Shader* shader;
	int hp = 2;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f,1.0f);
	BlockGrid* grid;
public:
	Block(BlockGrid*);
	void Update() override;
	void Draw() override;
	void Collide(Collision col) override;
	void spawnCube();
};
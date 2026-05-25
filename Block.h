#pragma once
#include "UD.h"
#include "CollisionManager.h"
#include "Model.h"
#include "ShaderCollection.h"
#include "BouncingCube.h"
#include "BlockGrid.h"
#include "Powerup.h"
#include <random>

class Block : public UD {
private:
	glm::mat4 model;
	Model* ourModel;
	Shader* shader;
	int hp = 1;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f,1.0f);
	BlockGrid* grid;
	glm::vec2 cell;
	
	float spawned = false;

public:
	Block(BlockGrid*);
	void Update() override;
	void Draw() override;
	void Collide(Collision col) override;
	void spawnCube();
	void setCell(int m, int n) { cell = glm::vec2(m, n); }
	glm::vec2 getCell() { return cell; }
	void setIron();
	glm::vec3 getCollisionPoint(BouncingCube* ball);
	glm::vec3 getBounceDirection(BouncingCube* ball);

	bool isCollide(glm::vec3 ball, float w, float h);
};
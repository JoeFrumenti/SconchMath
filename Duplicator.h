#pragma once
#include "UD.h"
#include "BouncingCube.h"
#include <random>
class Duplicator : public UD {

private:
	Model* ourModel;
	glm::mat4 model;
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
	Shader* shader;
public:
	Duplicator();
	
	void Update() override;
	void Collide(Collision col) override;
	void Draw() override;
	float randomFloat(float, float);
};
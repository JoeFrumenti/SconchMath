#pragma once

#include "UD.h"
#include "Model.h"
#include "ShaderCollection.h"

#include <iostream>
#include <vector>


#include "CollisionManager.h"
#include "InputManager.h"



class DebugCube : public UD {

	/*-6, 8
	6,-11.25*/
private:
	Model* ourModel;
	glm::mat4 model;
	Shader* shader;

	bool isInput = false;


	glm::vec3 velocity = glm::vec3(0.25f, 0.25f, 0.0f);

	CollisionManager& cm = CollisionManager::getInstance();
	InputManager& input = InputManager::getInstance();




public:

	void setInput(bool inp);

	DebugCube();


	void Update() override;

	void Draw() override;
	void Collide(Collision col) override;

	void translate(glm::vec3 translation);
};

#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>
#include <vector>


#include "CollisionManager.h"
#include "InputManager.h"



class DebugCube : public UD {


private:
	Model* ourModel;
	glm::mat4 model;
	glm::vec3 pos;
	Shader* shader;

	InputManager* input;

	glm::vec3 velocity = glm::vec3(0.25f, 0.25f,0.0f);

	CollisionManager& cm = CollisionManager::getInstance();

	


public:

	DebugCube(Shader* shade, InputManager* i) {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = shade;
		cm.addObject1(this);
		input = i;
	}

	
	glm::vec2 getPos() override {
		return pos;
	}

	void Update() override {
		pos += input->getInput() * velocity;

		if (input->isE())
			std::cout << pos.x << " " << pos.y << std::endl;


		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
	}

	void Draw() override {
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}
};
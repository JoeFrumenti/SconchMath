
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


	glm::vec3 velocity = glm::vec3(-0.25f, -0.35f, 0.0f);

	CollisionManager& cm = CollisionManager::getInstance();


	std::vector<int> pitches = { 0, 2, 4, 6, 7 };
	int pitch = 0;


public:

	DebugCube(Shader* shade, InputManager* input) {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = shade;
		cm.addObject1(this);
	}

	
	glm::vec2 getPos() override {
		return pos;
	}

	void Update() override {
		
	}

	void Draw() override {
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}
};
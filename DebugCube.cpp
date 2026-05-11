
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
	glm::vec3 pos;
	Shader* shader;

	bool isInput = false;


	glm::vec3 velocity = glm::vec3(0.25f, 0.25f,0.0f);

	CollisionManager& cm = CollisionManager::getInstance();
	InputManager& input = InputManager::getInstance();

	


public:

	void setInput(bool inp) {
		isInput = inp;
	}

	DebugCube() {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = ShaderCollection::getInstance().getShader("Model");
		tags.push_back("debug");
		tags.push_back(" cube ");
		this->width = 1;
		this->height = 1;
		cm.addObject(this);
	}

	
	glm::vec3 getPos() override {
		return pos;
	}

	void Update() override {
		pos += input.getInput() * glm::vec3(.25, .25, .25);
		if (input.isE()) {
			std::cout << pos.x << " " << pos.y << std::endl;
		}


		lastPos = pos;

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, scale);
	}

	void Draw() override {
		shader->setVec4("color", glm::vec4(1.0f,1.0f,1.0f,1.0f));
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	void Collide(Collision col) {
		for (auto& tag : col.obj->getTags())
		{
			if(tag == "debug")
			{
				UD* obj = col.obj;
				if (obj->getLastPos().x + obj->getWidth() < pos.x - width ||
					obj->getLastPos().x - obj->getWidth() > pos.x + width)
					std::cout << "LR";
				if (obj->getLastPos().y + obj->getHeight() < pos.y - height ||
					obj->getLastPos().y - obj->getHeight() > pos.y + height)
					std::cout << "TB";
			}
		}
	}
	

	void translate(glm::vec3 translation) {
		pos += translation;
	}
};
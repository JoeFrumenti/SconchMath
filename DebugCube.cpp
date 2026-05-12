
#include "UD.h"
#include "Model.h"
#include "ShaderCollection.h"

#include <iostream>
#include "DebugCube.h"
void DebugCube::setInput(bool inp) {
	isInput = inp;
}

DebugCube::DebugCube() {
		
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj");
	pos = glm::vec3(.0f, .0f, .0f);
	shader = ShaderCollection::getInstance().getShader("Model");
	tags.push_back("debug");
	tags.push_back(" cube ");
	this->width = 1;
	this->height = 1;
	cm.addObject(this);
}

	

void DebugCube::Update() {
	pos += input.getInput() * glm::vec3(.25, .25, .25);
	if (input.isE()) {
		std::cout << pos.x << " " << pos.y << std::endl;
	}


	lastPos = pos;

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);
}

void DebugCube::Draw(){
	shader->setVec4("color", glm::vec4(1.0f,1.0f,1.0f,1.0f));
	shader->setMat4("model", model);
	ourModel->Draw(*shader);
}

void DebugCube::Collide(Collision col) {
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
	

void DebugCube::translate(glm::vec3 translation) {
	pos += translation;
}

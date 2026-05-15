#include "Coin.h"

Coin::Coin() {
	
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
	pos = glm::vec3(.0f,.0f,.0f);
	shader = ShaderCollection::getInstance().getShader("Model");
	this->width = 0.25f * scaling;
	this->height = 0.35f * scaling;
	tags.push_back("coin");
	soundMan.addSound("coin", "C:/Users/joefr/source/repos/SconchMath/assets/audio/chime3.wav");
	cm.addObject(this);
}


void Coin::Update() {
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos); 
	model = glm::rotate(model, (float)glfwGetTime() * 3, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.3f * scaling, 0.3f * scaling, .3f * scaling));

	if (timerRunning && (glfwGetTime() - timer >= 0.3f)) {
		cm.addObject(this);
		timerRunning = false;
	}
}

void Coin::Draw() {
	shader->setMat4("model", model);
	shader->setVec4("color", color);
	ourModel->Draw(*shader);
	shader->setVec4("color", white);
}

void Coin::translate(glm::vec3 translation) {
	pos += translation;
}

glm::vec3 Coin::getPos() {
	return pos;
}

void Coin::Collide(Collision col)  {
	for (auto& tag : col.obj->getTags())
	{
		if (tag == "CoinPickup") {

			soundMan.playSound("coin", 0);
			color = glm::vec4(1.0f, .0f, .0f, 1.0f);
			cm.removeObject(getId());
			if (++collisions < 2) {
				timer = glfwGetTime();
				timerRunning = true;
			}
			else
				UDMan.removeObject(ID);
		}
	}
}

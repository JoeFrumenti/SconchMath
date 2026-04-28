
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>


#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"

#include "CollisionManager.h"
#include "UDManager.h"


class Coin : public UD {
private:
	Model* ourModel;
	glm::mat4 model;
	glm::vec3 pos;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 white = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Shader* shader;

	CollisionManager& cm = CollisionManager::getInstance();
	UDManager& UDMan = UDManager::getInstance();

	SoundDevice* mysounddevice = SoundDevice::get();
	uint32_t sound2 = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/chime2.wav");

	SoundSource mySpeaker;

	double timer = .1;
	bool timerRunning = false;

	int collisions = 0;

public:

	Coin(Shader* shade) {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f,.0f,.0f);
		shader = shade;
		this->width = 0.5f;
		this->height = 0.7f;
		cm.addObject(this);
	}


	void Update() override{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos); 
		model = glm::rotate(model, (float)glfwGetTime() * 3, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, .65f));

		if (timerRunning && (glfwGetTime() - timer >= 0.3f)) {
			cm.addObject(this);
			timerRunning = false;
		}

	}

	void Draw() override{
		shader->setMat4("model", model);
		shader->setVec4("color", color);
		ourModel->Draw(*shader);
		shader->setVec4("color", white);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}

	void Collide(Collision col) override {
		mySpeaker.Play(sound2);
		color = glm::vec4(1.0f, .0f, .0f, 1.0f);
		cm.removeObject(ID);
		if (++collisions < 2) {
			timer = glfwGetTime();
			timerRunning = true;
		}
		else
			UDMan.removeObject(ID);
	}

	glm::vec3 getPos() override{
		return pos;
	}
};
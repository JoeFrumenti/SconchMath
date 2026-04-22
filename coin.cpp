
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>


#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"


class Coin : public UD {
private:
	Model* ourModel;
	glm::mat4 model;

	glm::vec3 pos;

	Shader* shader;


	SoundDevice* mysounddevice = SoundDevice::get();
	uint32_t sound2 = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/chime2.wav");

	SoundSource mySpeaker;

public:

	Coin(Shader* shade) {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f,.0f,.0f);
		shader = shade;
	}


	void Update() override{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos); 
		model = glm::rotate(model, (float)glfwGetTime() * 3, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f, 0.45f, .45f));	
	}

	void Draw() override{
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}

	void Collide() override {
		mySpeaker.Play(sound2);
	}

	glm::vec2 getPos() override{
		return pos;
	}
};

#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>


#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"



class BouncingCube : public UD {
private:
	Model* ourModel;
	glm::mat4 model;

	glm::vec3 pos;

	Shader* shader;
	glm::vec3 velocity = glm::vec3(0.1f, 0.1f, 0.0f);


	SoundDevice* mysounddevice = SoundDevice::get();
	uint32_t sound1 = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/chime.wav");

	SoundSource mySpeaker;

public:

	BouncingCube(Shader* shade) {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = shade;
	}

	void screenBounce() {
		float scale = 0.65f;
		float boundsX = 8.8f * scale;
		float boundsY = 16.7f * scale;

		pos += velocity;

		if (pos.x >= boundsX || pos.x <= -boundsX) {
			mySpeaker.Play(sound1);
			velocity.x = -velocity.x;

		}
		if (pos.y >= boundsY || pos.y <= -boundsY) {
			mySpeaker.Play(sound1);
			velocity.y = -velocity.y;

		}


	}


	void Update() override {
		screenBounce();

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.3f, .7f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	}

	void Draw() override {
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}
};
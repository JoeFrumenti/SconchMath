
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>
#include <vector>

#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"

#include "CollisionManager.h"



class BouncingCube : public UD {

private:
	Model* ourModel;
	glm::mat4 model;

	glm::vec3 pos;

	Shader* shader;
	glm::vec3 velocity = glm::vec3(-0.25f, -0.35f, 0.0f);

	CollisionManager& cm = CollisionManager::getInstance();

	SoundDevice* mysounddevice = SoundDevice::get();
	uint32_t sound1 = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/chime.wav");

	SoundSource mySpeaker;

	std::vector<int> pitches = {0, 2, 4, 6, 7};
	int pitch = 0;


public:

	BouncingCube(Shader* shade, char* path) {
		

		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = shade;
		cm.addObject1(this);
		tags.push_back("bcube");
		this->width = 1;
		this->height = 1;
		cm.addObject(this);
	}

	void Collide(Collision col) {
		
		for (auto& tag : col.obj->getTags())
		{
			if (tag == "bcube")
			{
				mySpeaker.Play(sound1);
				UD* obj = col.obj;
				if (obj->getLastPos().x + obj->getWidth() <= lastPos.x - width && velocity.x < 0) {
					
					velocity.x = -velocity.x;
				}
				if (obj->getLastPos().x - obj->getWidth() >= lastPos.x + width && velocity.x > 0) {
					
					velocity.x = -velocity.x;
				}
					
				if (obj->getLastPos().y + obj->getHeight() <= lastPos.y - height && velocity.y < 0)
				{
					velocity.y = -velocity.y;
				}
				if (obj->getLastPos().y - obj->getHeight() >= lastPos.y + height && velocity.y > 0)
				{
					velocity.y = -velocity.y;
				}

				//pos += velocity;
			}
		}
	}


	void screenBounce() {
		float scale = 0.65f;
		float boundsX = 8.8f * scale;
		float boundsY = 16.7f * scale;

		

		

		pos += velocity;

		if (pos.x >= boundsX || pos.x <= -boundsX) {
			pitch = rand() % pitches.size();
			alSourcef(sound1, AL_PITCH, pow(2.0, pitches[pitch] / 12.0));
			mySpeaker.Play(sound1);
			velocity.x = -velocity.x;

		}
		if (pos.y >= boundsY || pos.y <= -boundsY) {
			pitch = rand() % pitches.size();
			alSourcef(sound1, AL_PITCH, pow(2.0, pitches[pitch] / 12.0));
			mySpeaker.Play(sound1);
			velocity.y = -velocity.y;

		}

	}
	glm::vec3 getPos() override {
		return pos;
	}

	void Update() override {
		lastPos = pos;
		screenBounce();

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.3f, .7f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, .8f));
		
	}

	void Draw() override {
		shader->setMat4("model", model);
		shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ourModel->Draw(*shader);
	}

	void setVelocity(glm::vec3 vel) {
		velocity = vel;
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}
};
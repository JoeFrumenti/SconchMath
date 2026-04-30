
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>
#include <vector>

#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"

#include "CollisionManager.h"
#include "Text.h"


#include "InputManager.h"

class BouncingCube : public UD {

private:
	Model* ourModel;
	Model* coin;

	glm::mat4 model;
	glm::vec3 pos;

	glm::mat4 cModel;
	glm::vec3 cPos = glm::vec3(-5.25f, 8.75f, 1.0f);;
	glm::vec3 cScale = glm::vec3(.515f, .465001f, .001f);

	glm::vec2 tPos = glm::vec2(69.25f, 678.25f);
	float tScale = .7925f;

	glm::vec3 velocity = glm::vec3(-0.25f, -0.35f, 0.0f);

	SoundDevice* mysounddevice = SoundDevice::get();
	uint32_t sound1 = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/chime.wav");

	SoundSource mySpeaker;

	glm::mat4 copyModel;
	glm::vec3 cmPos = glm::vec3(.0f,.0f,.0f);
	glm::vec3 cmSca = glm::vec3(.0f,.0f,.0f);

	std::vector<int> pitches = {0, 2, 4, 6, 7};
	int pitch = 0;


	InputManager* input;
	glm::vec3 coinVelocity = glm::vec3(0.25f, 0.25f, 0.0f);
	bool isInput = false;

	Shader* shader;
	Text* textManager;
	Shader* textShader;

	int player;


public:

	void setPlayer(int p) {
		player = p;

		if (player == 2) {
			cPos = glm::vec3(3.25f, 8.75f, 1.0f);
			tPos = glm::vec2(352.75, 678.25);
		}
	}

	void setInput(bool inp) {
		isInput = inp;
	}
	BouncingCube(Shader* shade, char* path, Shader* ts, InputManager* i) {
		
		player = 1;
		textShader = ts;
		textManager = new Text(textShader);

		CollisionManager& cm = CollisionManager::getInstance();

		ID = 0;
		ourModel = new Model(path);

		char path2[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj";
		coin = new Model(path2);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = shade;
		cm.addObject1(this);
		tags.push_back("bcube");
		this->width = 1;
		this->height = 1;
		cm.addObject(this);
		input = i;
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

		if (isInput) {
			tPos += glm::vec2(input->getInput().x, input->getInput().y) * glm::vec2(5.25f,5.25f);
			tScale += input->getInputWASD().x * 0.0025;

			if (input->isE()) {
				std::cout << tPos.x << " " << tPos.y << " "
					<< tScale << " " << tScale << std::endl;
			}
		}

		cModel = glm::mat4(1.0f);
		model = glm::mat4(1.0f);

		model = glm::translate(model, pos);
		cModel = glm::translate(cModel, cPos);
		
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.3f, .7f, 0.0f));

		cModel = glm::scale(cModel, cScale);
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, .8f));
		
	}

	void Draw() override {
		shader->setMat4("model", model);
		shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ourModel->Draw(*shader);
		shader->setMat4("model", copyModel);

		shader->setMat4("model", cModel);
		coin->Draw(*shader);
	}

	void setVelocity(glm::vec3 vel) {
		velocity = vel;
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}

	void drawText() override {

		float scale = 1.0f;

		textShader->use();
		textManager->RenderText(*textShader, "x12", tPos.x, tPos.y, tScale,
			glm::vec3(1.0, 1.0f, 1.0f));
	}
};
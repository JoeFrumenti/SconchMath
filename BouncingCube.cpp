
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>
#include <vector>

#include "SoundManager.h"

#include "CollisionManager.h"
#include "Text.h"

#include <cmath>

#include "InputManager.h"

class BouncingCube : public UD {

private:
	Model* ourModel;
	Model* coin;

	glm::mat4 model;

	glm::mat4 cModel;
	glm::vec3 cPos = glm::vec3(-5.25f, 8.75f, 1.0f);;
	glm::vec3 cScale = glm::vec3(.515f, .465001f, .465f);


	SoundManager& soundMan = SoundManager::getInstance();

	glm::mat4 copyModel;
	glm::vec3 cmPos = glm::vec3(-4.25f,10.25f,1.0f);
	glm::vec3 cmSca = glm::vec3(.715f,.715f,.715f);

	string coinString = "x12";


	bool isInput = false;

	Shader* shader;

	Shader* textShader;
	Text* vs;

	int player = 1;

public:

	void setPlayer(int p) {
		player = p;

		if (player == 2) {
			cPos = glm::vec3(3.25f, 8.75f, 1.0f);
			cmPos.x = -cmPos.x;
		}
	}

	void setInput(bool inp) {
		isInput = inp;
	}

	BouncingCube(Shader* shade, std::string path, Shader* ts) {
		velocity = glm::vec3(-0.25f, -0.35f, 0.0f);
		soundMan.addSound("bounce", "C:/Users/joefr/source/repos/SconchMath/assets/chime.wav");

		textShader = ts;


		vs = new Text(textShader, "C:/Windows/Fonts/BOD_B.TTF");

		CollisionManager& cm = CollisionManager::getInstance();

		ourModel = new Model(path);

		coin = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
		shader = shade;
		tags.push_back("bcube");
		this->width = 1.0f;
		this->height = 1.0f;
		cm.addObject(this);
	}

	float dot(glm::vec2 a, glm::vec2 b) {
		return a.x * b.x + a.y * b.y;
	}

	void Collide(Collision col) {
		
		for (auto& tag : col.obj->getTags())
		{
			if (tag == "coin") {
				stats["coins"]++;
			}
			if (tag == "bcube")
			{

				if(player == 1) soundMan.playSong("bounce");

				UD* obj = col.obj;

				const float dx = obj->getPos().x - pos.x;
				const float dy = obj->getPos().y - pos.y;
				const float dist = std::sqrt(dx * dx + dy * dy);

				const float nx = dx / dist;
				const float ny = dy / dist;

				const float dvx = obj->getVelocity().x - velocity.x;
				const float dvy = obj->getVelocity().y - velocity.y;
				const float dvn = dvx * nx + dvy * ny;

				if (dvn >= 0) return;  // already separating, skip

				obj->setVelocity(glm::vec3(obj->getVelocity().x - dvn * nx,
					obj->getVelocity().y - dvn * ny, .0f));
				velocity.x += dvn * nx;
				velocity.y += dvn * ny;
				

				
			}
		}
	}


	void screenBounce() {
		float scale = 0.65f;
		float boundsX = 8.8f * scale;
		float boundsY = 16.7f * scale;

		
		pos += velocity;

		if (pos.x + width >= 6 || pos.x - width <= -6) {
			
			soundMan.playSong("bounce");
			velocity.x = -velocity.x;
			pos.x += velocity.x;

		}
		if (pos.y + height >= 7.75 || pos.y - height <= -11.25) {
			soundMan.playSong("bounce");
			velocity.y = -velocity.y;
			pos.y += velocity.y;
		}

	}

	void Update() override {
		for(UD* child : children) {
			child->Update();
		}
		
		lastPos = pos;



		screenBounce();

		cModel = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
		copyModel = glm::mat4(1.0f);

		model = glm::translate(model, pos);
		cModel = glm::translate(cModel, cPos);
		copyModel = glm::translate(copyModel, cmPos);

		cModel = glm::rotate(cModel, (float)glfwGetTime() / 2, glm::vec3(.0f, 1.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.3f, .7f, 0.0f));
		copyModel = glm::rotate(copyModel, (float)glfwGetTime()/2, glm::vec3(.0f, 1.0f, 0.0f));

		cModel = glm::scale(cModel, cScale);
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, .8f));
		copyModel = glm::scale(copyModel, cmSca);
	}

	void Draw() override {
		for (UD* child : children) {
			child->Draw();
		}

		shader->setMat4("model", model);
		shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ourModel->Draw(*shader);
		shader->setMat4("model", copyModel);
		ourModel->Draw(*shader);

		shader->setMat4("model", cModel);
		coin->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}

	void drawText() override {
		for (UD* child : children) {
			child->drawText();
		}

		float scale = 1.0f;

		textShader->use();
		

		vs->RenderText(*textShader, "VS", 211, 725, 1.0f,
			glm::vec3(1.0, 1.0f, 1.0f));
	}
};
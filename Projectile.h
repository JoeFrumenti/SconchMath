#pragma once
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"
#include "ShaderCollection.h"
#include "CollisionManager.h"
class Projectile: public UD {
protected:
	bool isActive = false;
	Model* ourModel;
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	glm::mat4 model;
	int bounces = 0;
	CollisionManager& cm = CollisionManager::getInstance();
	float debuffTime = 1.0f;

	bool shrinkDie = false;
public:
	


	virtual void screenBounce() {
		float scale = 0.65f;
		float boundsX = 8.8f * scale;
		float boundsY = 16.7f * scale;
		

		pos += velocity;

		if (pos.x + width >= 6 || pos.x - width <= -6) {

			velocity.x = -velocity.x;
			pos.x += velocity.x;
			bounces++;

		}
		if (pos.y + height >= 8 || pos.y - height <= -5.5) {
			
			velocity.y = -velocity.y;
			pos.y += velocity.y;
			bounces++;
		}
		if (bounces >= 2) {
			//isActive = false;
			bounces = 0;
			shrinkDie = true;
		}

	}
	
	virtual void Update() override {
		if (shrinkDie) {
			scale -= glm::vec3(1.0f/15.0f, 1.0f / 15.0f, 1.0f / 15.0f);
			if (scale.x <= 0) {
				shrinkDie = false;
				isActive = false;
				cm.removeObject(this->getId());
			}
		}

		else if (isActive) {
			screenBounce();
		}
			model = glm::mat4(1.0f);
			model = glm::translate(model, pos);
			model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, height * scale.z));
		
	}

	virtual void Draw() override{
		if(isActive){
			shader->setMat4("model", model);
			ourModel->Draw(*shader);
		}
	}

	virtual void setParent(UD* p) override {
		Parent = p;
	}

	virtual void setActive(bool a) {
		isActive = a;
		if (isActive) {
			pos = Parent->getPos();
		}
	}
	virtual bool getActive() {
		return isActive;
	}

};
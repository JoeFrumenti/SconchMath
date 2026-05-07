#pragma once
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"
#include "ShaderCollection.h"
class Projectile: public UD {
protected:
	bool isActive = false;
	Model* ourModel;
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	glm::mat4 model;
public:
	


	virtual void screenBounce() {
		float scale = 0.65f;
		float boundsX = 8.8f * scale;
		float boundsY = 16.7f * scale;
		

		pos += velocity;

		if (pos.x + width >= 6 || pos.x - width <= -6) {

			velocity.x = -velocity.x;
			pos.x += velocity.x;

		}
		if (pos.y + height >= 7.75 || pos.y - height <= -11.25) {
			
			velocity.y = -velocity.y;
			pos.y += velocity.y;
		}

	}
	
	virtual void Update() override {
		screenBounce();
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);

	}

	virtual void Draw() override{
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	virtual void setParent(UD* p) override {
		Parent = p;
	}

};
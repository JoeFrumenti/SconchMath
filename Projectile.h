#pragma once
#include "UD.h"
#include "Model.h"
#include "ShaderCollection.h"
#include "CollisionManager.h"
#include "GameManager.h"
#include <random>

class Projectile: public UD {
protected:
	bool isActive = false;
	Model* ourModel;
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	glm::mat4 model;
	int bounces = 0;
	CollisionManager& cm = CollisionManager::getInstance();
	GameManager& gameMan = GameManager::getInstance();
	BouncingCube* Parent;

	int maxBounces = 1;
	bool shrinkDie = false;
	bool seekParent = false;

public:
	Projectile() = default;
	Projectile(BouncingCube* parent) { Parent = parent; };


	void seekParentPls() {

		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<float> dist(-.25f, .25f);
		float value = dist(rng);



		float x1 = getPos().x;
		float x2 = Parent->getPos().x;
		float y1 = getPos().y;
		float y2 = Parent->getPos().y;



		float dx = x2 - x1 + dist(rng);
		float dy = y2 - y1 + dist(rng);

		float norm = std::sqrt(dx * dx + dy * dy);

		glm::vec3 pVel = glm::vec3(dx / norm, dy / norm, 0) * glm::vec3(0.5f);

		setVelocity(pVel);

		if (dx <= 0.2 && dy <= 0.2)
			shrinkDie = true;
	}

	void shrinkDiePls() {
		scale -= glm::vec3(1.0f / 15.0f, 1.0f / 15.0f, 1.0f / 15.0f);
		if (scale.x <= 0) {
			shrinkDie = false;
			isActive = false;
			cm.removeObject(this->getId());
		}	
	}


	virtual void screenBounce() {
		float boundsX = 5.72;
		float boundsY = 10.855;
		

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
		if (bounces >= maxBounces) {
			velocity = glm::vec3(0);
			bounces = 0;
			shrinkDie = true;
		}

	}
	
	void seekEnemy() {

		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<float> dist(-.25f, .25f);
		float value = dist(rng);



		float x1 = Parent->getPos().x;
		float x2 = gameMan.getp2()->getPos().x;
		float y1 = Parent->getPos().y;
		float y2 = gameMan.getp2()->getPos().y;



		float dx = x2 - x1 + dist(rng);
		float dy = y2 - y1 + dist(rng);

		float norm = std::sqrt(dx * dx + dy * dy);

		glm::vec3 pVel = glm::vec3(dx / norm, dy / norm, 0) * glm::vec3(0.5f);

		setVelocity(pVel);
	}

	virtual void Draw() override{
		if(isActive && !Parent->getLoser()){
			shader->setMat4("model", model);
			shader->setVec4("color", glm::vec4(1));
			ourModel->Draw(*shader);
		}
	}

	virtual void setParent(BouncingCube* p) {
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
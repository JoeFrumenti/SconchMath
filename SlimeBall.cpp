#include "SlimeBall.h"
#include <random>


SlimeBall::SlimeBall(BouncingCube* parent) : Projectile(parent) {
	Parent = parent;
	
	pos = Parent->getPos();
	width = 0.5;
	height = 0.5;
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/slimeball.obj");
	velocity = glm::vec3(-0.11f, 0.24f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1);
	

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

	setScale(glm::vec3(1, 1, 1));
	isActive = true;

	cm.addObject(this);
}

	

void SlimeBall::Collide(Collision col){
	for (auto& tag : col.obj->getTags()) {
		BouncingCube* par = dynamic_cast<BouncingCube*>(Parent);
		BouncingCube* obj = dynamic_cast<BouncingCube*>(col.obj);
		if (tag == "bcube" && col.obj != Parent) {
			if (!obj->getSlow()) {

				(obj)->slow(par->getStats().debuffTime);
				par->getStats().debuffTime += 0.2f;
				isActive = false;
				bounces = 0;
				//cm.removeObject(this->getId());

				shrinkDie = true;
			}
		}
	}
}


#include "SlimeBall.h"



SlimeBall::SlimeBall(BouncingCube* parent) : Projectile(parent) {
	Parent = parent;
	
	maxBounces = 3;

	pos = Parent->getPos();
	width = 0.5;
	height = 0.5;
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/slimeball.obj");
	velocity = glm::vec3(-0.11f, 0.24f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1);
	

	seekEnemy();

	setScale(glm::vec3(1, 1, 1));
	isActive = true;

	cm.addObject(this);
}

void SlimeBall::Update() {
	if (Parent->getLoser()) {
		UDManager::getInstance().queueRemoval(ID);
		CollisionManager::getInstance().removeObject(ID);
	}

	if (shrinkDie) {
		scale -= glm::vec3(1.0f / 15.0f, 1.0f / 15.0f, 1.0f / 15.0f);
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
				//

			}
			shrinkDie = true;
			cm.removeObject(this->getId());
		}
	}
}


#include "Thief.h"

Thief::Thief(BouncingCube* parent) {
	Parent = parent;

	setVariance(0.0f);
	pos = Parent->getPos();
	width = 0.5;
	height = 0.5;
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/net.obj");
	scale = glm::vec3(1.0f, 1.0f, 1);

	seekEnemy();

	setScale(glm::vec3(1, 1, 1));
	isActive = true;
	seekParent = false;
	cm.addObject(this);
}

void Thief::exitCollision(Collision col) {
	if (col.obj == Parent)
		touchingParent = false;
}

void Thief::Collide(Collision col){
	if (col.obj == Parent)
		touchingParent = true;

	for (auto& tag : col.obj->getTags()) {
		if (tag == "bcube" && col.obj != Parent && !stolen) {
			dynamic_cast<BouncingCube*>(col.obj)->getStats().coins-= Parent->getStats().debuffTime;
			SoundManager::getInstance().playSound("bonk",0);
			seekParent = true;
			stolen = true;
			if (touchingParent)
			{
				Parent->getStats().coins+= Parent->getStats().debuffTime;
				Parent->getStats().debuffTime+=1;
				velocity = glm::vec3(.0f);
				die();
			}
		}
		if (tag == "bcube" && col.obj == Parent && stolen) {
			Parent->getStats().coins+= Parent->getStats().debuffTime;
			Parent->getStats().debuffTime+=1;
			velocity = glm::vec3(.0f);
			die();
		}
	}
}

void Thief::Update() {
	if (!seekParent)
		screenBounce();
	else 
		seekParentPls();
	
	if (shrinkDie)
		shrinkDiePls();


	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, height * scale.z));
}
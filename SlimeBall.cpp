#include "SlimeBall.h"


SlimeBall::SlimeBall() {
	width = 0.5;
	height = 0.5;
	//std::cout << "NEW SLIMEBALL\n";
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/slimeball.obj");
	velocity = glm::vec3(-0.11f, 0.24f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1);
		
}

	

void SlimeBall::Collide(Collision col){
	for (auto& tag : col.obj->getTags()) {
		BouncingCube* par = dynamic_cast<BouncingCube*>(Parent);
		BouncingCube* obj = dynamic_cast<BouncingCube*>(col.obj);
		if (tag == "bcube" && col.obj != Parent) {
			if (!obj->getSlow()) {

				(obj)->slow(par->getDebuffTime());
				par->addDebuffTime(0.2f);
				isActive = false;
				bounces = 0;
				//cm.removeObject(this->getId());

				shrinkDie = true;
			}
		}
	}
}


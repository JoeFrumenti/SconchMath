#include "Projectile.h"
#include "Thief.h"
#include "UD.h"
#include "Model.h"
#include "BouncingCube.h"

Thief::Thief(BouncingCube* parent) {
	Parent = parent;

	pos = Parent->getPos();
	width = 0.5;
	height = 0.5;
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/slimeball.obj");
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
			dynamic_cast<BouncingCube*>(col.obj)->getStats().coins--;
			seekParent = true;
			stolen = true;
			if (touchingParent)
			{
				Parent->getStats().coins++;
				velocity = glm::vec3(.0f);
				shrinkDie = true;
			}
		}
		if (tag == "bcube" && col.obj == Parent && stolen) {
			Parent->getStats().coins++;
			velocity = glm::vec3(.0f);
			shrinkDie = true;
		}
	}
}

void Thief::Update() {
	if (!seekParent)
		screenBounce();
	else 
		seekParentPls();
	
	if (shrinkDie && !seekParent)
		shrinkDiePls();


	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, height * scale.z));
}
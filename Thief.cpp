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

	cm.addObject(this);
}

void Thief::Collide(Collision col){

}

void Thief::Update() {
	screenBounce();



	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, height * scale.z));
}
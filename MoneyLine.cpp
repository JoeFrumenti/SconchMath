#include "MoneyLine.h"

MoneyLine::MoneyLine(BouncingCube* parent) {
	Parent = parent;

	setVariance(0.0f);
	pos = Parent->getPos();
	width = 0.5;
	height = 0.5;
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/net.obj");
	scale = glm::vec3(.0f, .0f, 0.0f);
	velocity = Parent->getVelocity() * glm::vec3(1.4f);



	cm.addObject(this);
}

void MoneyLine::Update() {
	timer += myTimer.getDeltaTime();
	screenBounce();
	if (timer >= 0.4f) {
		coinsDropped++;
		timer = 0.0f;
		Coin* coin = new Coin(1);
		coin->translate(pos);
		UDManager::getInstance().addUD(coin);
	}
	if (coinsDropped >= 4) {
		isActive = false;
		UDManager::getInstance().queueRemoval(ID);
	}
}

void MoneyLine::Draw() {

}
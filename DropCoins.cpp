#include "DropCoins.h"

DropCoins::DropCoins() {
	lastPos = pos;
	modelShader = ShaderCollection::getInstance().getShader("Model");
}

void DropCoins::setParent(UD* parent){
	this->Parent = parent;
}

void DropCoins::Update() {
	pos = Parent->getPos();
	if (glm::distance(pos, lastPos) >= 4) {
		Coin* coin = new Coin();
		coin->translate(pos);
		UDMan.addUD(coin);
		lastPos = pos;
	}
}
void DropCoins::Draw(){

}
void DropCoins::drawText(){

}

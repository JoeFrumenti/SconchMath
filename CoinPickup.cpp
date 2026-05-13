
#include "CoinPickup.h"

CoinPickup::CoinPickup() {
	tags.push_back("CoinPickup");
}

void CoinPickup::setParent(UD* parent){
	this->Parent = parent;
	width = Parent->getWidth();
	height = Parent->getHeight();
	cm.addObject(this);
	UDManager::getInstance().addUD(this);

}

void CoinPickup::Update() {/*
	std::cout << "UPDATING COIN PICKUP\n";*/
	pos = Parent->getPos();
	//std::cout << width << "\n";
}
void CoinPickup::Draw() {

}
void CoinPickup::drawText() {

}

void CoinPickup::Collide(Collision col){
		
	for (auto& tag : col.obj->getTags())
	{
		if (tag == "coin") {
			dynamic_cast<BouncingCube*>(Parent)->getStats().coins ++;
		}
	}
}

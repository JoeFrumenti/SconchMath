#include "BouncingCube.h"

class CoinPickup: public UD {
private:
	CollisionManager& cm = CollisionManager::getInstance();

public:
	CoinPickup() {
		tags.push_back("CoinPickup");
	}

	void setParent(UD* parent) override {
		this->Parent = parent;
		width = Parent->getWidth();
		height = Parent->getHeight();
		cm.addObject(this);
	}

	void Update() {/*
		std::cout << "UPDATING COIN PICKUP\n";*/
		pos = Parent->getPos();
		//std::cout << width << "\n";
	}
	void Draw() {

	}
	void drawText() {

	}

	void Collide(Collision col) override {
		
		for (auto& tag : col.obj->getTags())
		{
			if (tag == "coin") {
				Parent->getStats()["coins"]++;
			}
		}
	}
};
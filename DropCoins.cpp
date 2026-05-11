#include "BouncingCube.h"
#include "Coin.h"

class DropCoins : public UD {
private:
	CollisionManager& cm = CollisionManager::getInstance();
	glm::vec3 lastPos;
	int idNum = 300;
	Shader* modelShader;
	UDManager& UDMan = UDManager::getInstance();

public:
	DropCoins(Shader* s) {
		lastPos = pos;
		modelShader = s;
	}

	void setParent(UD* parent) override {
		this->Parent = parent;
	}

	void Update() {
		pos = Parent->getPos();
		if (glm::distance(pos, lastPos) >= 4) {
			Coin* coin = new Coin();
			coin->setId(idNum++);
			coin->translate(pos);
			UDMan.addUD(coin);
			lastPos = pos;
		}
	}
	void Draw() override {

	}
	void drawText() override {

	}
};
#include "PlayerManager.h"

PlayerManager::PlayerManager(BouncingCube* a, BouncingCube* b) {
	p1 = a;
	p2 = b;
}

void PlayerManager::Update() {
	if (p1->getStats()["coins"] >= 10) {
		p2->setScale(glm::vec3(.0f, .0f, .0f));
	}
	if (p2->getStats()["coins"] >= 10) {
		p1->setScale(glm::vec3(.0f, .0f, .0f));
	}
}

void PlayerManager::Draw() {

}

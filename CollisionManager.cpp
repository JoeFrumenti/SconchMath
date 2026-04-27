#pragma once

#include "CollisionManager.h"
#include "point.h"

CollisionManager::CollisionManager() {}

void CollisionManager::addObject(UD* object) {
	objects.push_back(object);
}

void CollisionManager::addObject1(UD* object) {
	objects1.push_back(object);
}

void CollisionManager::addObject2(UD* coin) {
	objects2.push_back(coin);
}

void CollisionManager::checkCollision2D() {
	for (auto& obj1 : objects) {
		for (auto& obj2 : objects){
			if (obj1->getId() != obj2->getId()) {
				std::cout << obj1->getId() << "\n";
			}
		}
	}
}

void CollisionManager::checkCollision() {
	auto& objManager = UDManager::getInstance();
	float coinsize = 1.7;
	for (auto& obj : objects1) {
		glm::vec2 objCenter = obj->getPos();
		for (auto& coin : objects2) {
			//std::cout << "CHECKING COINS!\n" << coin->getId() << std::endl;
			glm::vec2 coinCenter = coin->getPos();
			if (objCenter.x > coinCenter.x - coinsize
				&& objCenter.x < coinCenter.x + coinsize
				&& objCenter.y <coinCenter.y + coinsize
				&& objCenter.y >coinCenter.y - coinsize)
			{
				//coin->Collide();
				//objManager.removeObject(coin->getId());
				//removeObject(coin->getId());
			}
		}
	}
}

void CollisionManager::removeObject(int id) {
	
	std::vector<UD*> temp;
	for (auto& obj : objects2) {

		if (obj->getId() != id) {
			temp.push_back(obj);
		}
		/*else
			std::cout << "Removing " << id << std::endl;*/

		objects2 = temp;
	}
}

bool CollisionManager::inBox(Point point, glm::vec3 pos, float w, float h) {
	if (point.x < pos.x + w &&
		point.x > pos.x - w &&
		point.y < pos.y + h &&
		point.y > pos.y - h)
		return true;
	return false;
}

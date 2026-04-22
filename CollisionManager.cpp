#pragma once

#include "CollisionManager.h"

CollisionManager::CollisionManager() {}

void CollisionManager::addObject1(UD* object) {
	objects1.push_back(object);
}

void CollisionManager::addObject2(UD* coin) {
	objects2.push_back(coin);
}

void CollisionManager::checkCollision() {
	auto& objManager = UDManager::getInstance();
	float coinsize = 1.4;
	for (auto& obj : objects1) {
		glm::vec2 objCenter = obj.getPos();
		for (UD* coin : objects2) {

			glm::vec2 coinCenter = coin.getPos();
			if (objCenter.x > coinCenter.x - coinsize
				&& objCenter.x < coinCenter.x + coinsize
				&& objCenter.y <coinCenter.y + coinsize
				&& objCenter.y >coinCenter.y - coinsize)
			{
				coin.Collide();
				//objManager.removeObject(coin.getId());
				removeObject(coin.getId());
			}

		}
	}
}

CollisionManager* CollisionManager::getInstance() {
	if (instancePtr == nullptr) {
		std::lock_guard<std::mutex> lock(mtx);
		if (instancePtr == nullptr) {
			instancePtr = new CollisionManager();
		}
	}
	return instancePtr;
}

void CollisionManager::removeObject(int id) {

	std::vector<UD> temp;
	for (UD& obj : objects2) {

		if (obj.getId() != id) {
			temp.push_back(obj);
		}

		objects2 = temp;
	}
}

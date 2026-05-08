#pragma once

#include "CollisionManager.h"

int frames = 0;
CollisionManager::CollisionManager() {}

void CollisionManager::addObject(UD* object) {
	objects.push_back(object);
}

void CollisionManager::checkCollision2D() {
	frames++;
	for (int i = 0; i < objects.size(); i++) {
		for (int j = i + 1; j < objects.size(); j++) {
			UD* a = objects[i];
			UD* b = objects[j];

			bool overlapX = std::abs(a->getPos().x - b->getPos().x) < (a->getWidth() + b->getWidth());
			bool overlapY = std::abs(a->getPos().y - b->getPos().y) < (a->getHeight() + b->getHeight());

			if (overlapX && overlapY) {
				Collision col1(a);
				Collision col2(b);
				a->Collide(col2);
				b->Collide(col1);
			}
		}
	}

}


void CollisionManager::removeObject(int id) {
	
	std::vector<UD*> temp;
	for (auto& obj : objects) {

		if (obj->getId() != id) {
			temp.push_back(obj);
		}

		objects = temp;
	}
}

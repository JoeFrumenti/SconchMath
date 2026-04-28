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
	std::vector<UD*> UDcollisions;
	std::vector<Collision> cols;

	for (auto& obj1 : objects) {
		for (auto& obj2 : objects){
			if (obj1->getId() != obj2->getId()) {
				glm::vec2 pos1 = obj1->getPos();
				float w1 = obj1->getWidth();
				float h1 = obj1->getHeight();

				glm::vec2 pos2a = obj2->getPos();
				float w2 = obj2->getWidth();
				float h2 = obj2->getHeight();

				Point UR(pos1.x + w1, pos1.y + h1);
				Point UL(pos1.x - w1, pos1.y + h1);
				Point BR(pos1.x + w1, pos1.y - h1);
				Point BL(pos1.x - w1, pos1.y - h1);

				if (inBox(UR, obj2->getPos(), w2, h2) ||
					inBox(UL, obj2->getPos(), w2, h2) ||
					inBox(BR, obj2->getPos(), w2, h2) ||
					inBox(BL, obj2->getPos(), w2, h2)) 
					{
						
						Collision col(obj2);
						cols.push_back(col);
						UDcollisions.push_back(obj1);
						
					}
					
				
			}
		}
	}

	for (int i = 0; i < cols.size(); i++) {
		UDcollisions[i]->Collide(cols[i]);
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
			if (objCenter.x >= coinCenter.x - coinsize
				&& objCenter.x <= coinCenter.x + coinsize
				&& objCenter.y <= coinCenter.y + coinsize
				&& objCenter.y >= coinCenter.y - coinsize)
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
	for (auto& obj : objects) {

		if (obj->getId() != id) {
			temp.push_back(obj);
		}
		/*else
			std::cout << "Removing " << id << std::endl;*/

		objects = temp;
	}
}

bool CollisionManager::inBox(Point point, glm::vec3 pos, float w, float h) {
	if (point.x <= pos.x + w &&
		point.x >= pos.x - w &&
		point.y <= pos.y + h &&
		point.y >= pos.y - h)
		return true;
	return false;
}

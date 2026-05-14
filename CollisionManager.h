#pragma once

#include "UD.h"
#include "UDManager.h"
#include <vector>
#include <string>
#include <set>

#include "Collision.h"

class CollisionManager {
private:
	std::vector<UD*> objects;

	std::set<std::pair<UD*, UD*>> activeCollisions;


public:

	CollisionManager();

	static CollisionManager& getInstance() {
		static CollisionManager instance;
		return instance;
	}


	void addObject(UD* object);
	void checkCollision2D();

	void removeObject(int id);
};
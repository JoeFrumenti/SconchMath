#pragma once

#include "UD.h"
#include "UDManager.h"
#include <vector>
#include <string>

#include "Collision.h"

class CollisionManager {
private:
	std::vector<UD*> objects;
	std::vector<UD*> objects1;
	std::vector<UD*> objects2;


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
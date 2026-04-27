#pragma once

#include "UD.h"
#include "UDManager.h"
#include <vector>
#include <mutex>
#include <string>

#include "Collision.h"
#include "point.h"

class CollisionManager {
private:
	std::vector<UD*> objects;
	std::vector<UD*> objects1;
	std::vector<UD*> objects2;
	static CollisionManager* instancePtr;

	static std::mutex mtx;

public:

	CollisionManager();

	static CollisionManager& getInstance() {
		static CollisionManager instance;
		return instance;
	}

	bool inBox(Point p, glm::vec3 pos, float w, float h);

	void addObject(UD* object);

	void addObject1(UD* object);

	void addObject2(UD* coin);

	void checkCollision();

	void checkCollision2D();

	void removeObject(int id);
};
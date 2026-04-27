#pragma once

#include "UD.h"
#include "UDManager.h"
#include <vector>
#include <mutex>
#include <string>

struct Collision {
	std::vector<std::string> tags;
	glm::vec2 pos;
};

class CollisionManager {
private:
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
	void addObject1(UD* object);

	void addObject2(UD* coin);

	void checkCollision();

	void removeObject(int id);
};
#pragma once

#include "UD.h"
#include "UDManager.h"
#include <vector>
#include <mutex>



class CollisionManager {
private:
	std::vector<UD*> objects1;
	std::vector<UD*> objects2;
	static CollisionManager* instancePtr;

	static std::mutex mtx;

public:

	CollisionManager();
	static CollisionManager* getInstance();

	void addObject1(UD* object);

	void addObject2(UD* coin);

	void checkCollision();

	void removeObject(int id);
};
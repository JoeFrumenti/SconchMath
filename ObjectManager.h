#pragma once
#include <GameObject.h>
#include <vector>

class ObjectManager {
private:
	std::vector<GameObject> objects;

	ObjectManager() {}
public:

	static ObjectManager& getInstance() {
		static ObjectManager instance;  // created once, lives forever
		return instance;
	}

	void addObject(GameObject obj);
	void renderObjects();
	void removeObject(int id);
};

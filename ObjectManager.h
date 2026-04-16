#pragma once
#include <GameObject.h>
#include <vector>

class ObjectManager {
private:
	std::vector<GameObject> objects;
public:
	ObjectManager();
	void addObject(GameObject obj);
	void renderObjects();
	void removeObject(const GameObject target);
};

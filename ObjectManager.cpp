#include <GameObject.h>
#include <vector>
#include "ObjectManager.h"


void ObjectManager::addObject(GameObject obj) {
	objects.push_back(obj);
	
}
void ObjectManager::renderObjects() {
	for (auto& obj : objects) {
		obj.render();
	}
}

void ObjectManager::removeObject(int id) {
	
	std::vector<GameObject> temp;
	for (GameObject& obj : objects) {
		
		if (obj.id != id) {
			temp.push_back(obj);
		}
	}
	objects = temp;
}
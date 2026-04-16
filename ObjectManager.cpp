#include <GameObject.h>
#include <vector>
#include "ObjectManager.h"

int idSlot = 0;

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
	std::cout << "Checking id of " << id << "\n";
	for (GameObject& obj : objects) {
		
		if (obj.id != id) {
			std::cout << "not removing " << obj.id << "\n";
			temp.push_back(obj);
		}
		else
			std::cout << "Removing " << obj.id << "\n";
	}
	objects = temp;
}
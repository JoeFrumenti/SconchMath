#include <GameObject.h>
#include <vector>
#include "ObjectManager.h"

ObjectManager::ObjectManager() {

}
void ObjectManager::addObject(GameObject obj) {
	objects.push_back(obj);
}
void ObjectManager::renderObjects() {
	for (auto& obj : objects) {
		obj.render();
	}
}

void ObjectManager::removeObject(const GameObject target) {
    objects.erase(
        std::remove_if(objects.begin(), objects.end(), [&](const GameObject& obj) {
            return &obj == &target;  
            }),
        objects.end()
    );
}
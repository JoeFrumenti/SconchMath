#include "UDManager.h"

void UDManager::addUD(UD* newUD)
{
	newUD->setId(nextID);
	UDs[nextID++] = newUD;
}

void UDManager::drawUDs() {
	for (const auto& kv : UDs) {
		kv.second->Draw();
	}
}

void UDManager::updateUDs(){
	for (int id : remQ) {
		removeObject(id);
	}
	for (const auto& kv : UDs) {
		kv.second->Update();
	}
}

void UDManager::queueRemoval(int id) {
	remQ.push_back(id);
}

void UDManager::removeObject(int id) {
	//UDs.erase(id);
	std::map<int, UD*> temp;
	for (auto& obj : UDs) {
		if (obj.first != id)
			temp.insert(obj);
	}
	UDs = temp;

}

void UDManager::drawText() {
	for (const auto& kv : UDs) {
		kv.second->drawText();
	}
}
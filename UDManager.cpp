#include "UDManager.h"

void UDManager::addUD(UD* newUD)
{
	 UDs[newUD->getId()] = newUD;
}

void UDManager::drawUDs() {
	for (const auto& kv : UDs) {
		kv.second->Draw();
	}
}

void UDManager::updateUDs(){
	for (const auto& kv : UDs) {
		kv.second->Update();
	}
}

void UDManager::removeObject(int id) {

	UDs.erase(id);
}
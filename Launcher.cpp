#include "Launcher.h"
#include "SlimeBall.h"
#include "MyTimer.h"
#include "SoundManager.h"

void Launcher::setParent(BouncingCube* parent){
		this->Parent = parent;
}

void Launcher::Update() {
	
	this->launchTimer += timer.getDeltaTime();
	if (launchTimer >= 1.9){
		std::cout << "\nLaunching Parent";
		UDManager::getInstance().addUD(Launch(Parent));
		
		launchTimer = 0;
	}
	

}

void Launcher::Draw() {}


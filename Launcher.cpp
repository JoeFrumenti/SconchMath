#include "Launcher.h"
#include "SlimeBall.h"
#include "MyTimer.h"
#include "SoundManager.h"

MyTimer& timer = MyTimer::getInstance();

SlimeBall* sb;


void Launcher::setParent(BouncingCube* parent){
		this->Parent = parent;
}





void Launcher::Update() {
	
	if (!sb->getActive()) {
		launchTimer += timer.getDeltaTime();
		if (launchTimer >= 1.9){
			Launch(Parent);
			launchTimer = 0;
		}
	}

}

void Launcher::Draw() {}


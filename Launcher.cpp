#include "Launcher.h"
#include "SlimeBall.cpp"
#include "MyTimer.h"

MyTimer& timer = MyTimer::getInstance();

SlimeBall* sb;

void Launcher::setParent(UD* parent) {
		this->Parent = parent;
		projectile->setParent(Parent);
}

Launcher::Launcher(UD* p) {
	projectile = p;
	launchTimer = glfwGetTime();
	children.push_back(projectile);
	sb = dynamic_cast<SlimeBall*>(projectile);
	
}

void Launcher::launch() {
	sb->setActive(true);
	
}

void Launcher::Update() {
	
	if (!sb->getActive()) {
		launchTimer += timer.getDeltaTime();
		if (launchTimer >= 1)
		{
			launch();
			launchTimer = 0;
		}
	}

	for (auto& child : children) {
		child->Update();
	}


}

void Launcher::Draw() {
	for (auto& child : children) {
		child->Draw();
	}
}

void Launcher::drawText() {

}

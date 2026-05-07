#include "Launcher.h"
#include "SlimeBall.cpp"
void Launcher::setParent(UD* parent) {
		this->Parent = parent;
}

Launcher::Launcher(UD* p) {
	projectile = p;
	launchTimer = glfwGetTime();
}

void Launcher::launch() {
	dynamic_cast<SlimeBall*>(projectile)->test();
	children.push_back(projectile);
}

void Launcher::Update() {
	for (auto& child : children) {
		child->Update();
	}

	if (glfwGetTime() - 1 > launchTimer) {
		launchTimer = glfwGetTime();
		launch();
	}

}

void Launcher::Draw() {
	for (auto& child : children) {
		child->Draw();
	}
}

void Launcher::drawText() {

}

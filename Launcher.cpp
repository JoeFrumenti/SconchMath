#include "Launcher.h"

void Launcher::setParent(UD* parent) {
		this->Parent = parent;
}

Launcher::Launcher(UD* p) {
	projectile = p;
}

void Launcher::launch() {

}

void Launcher::Update() {
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

#include "Launcher.h"
#include "SlimeBall.cpp"
#include "MyTimer.h"
#include <random>
#include "SoundManager.h"

MyTimer& timer = MyTimer::getInstance();

SlimeBall* sb;

void Launcher::setParent(UD* parent) {
		this->Parent = parent;
		projectile->setParent(Parent);

}

Launcher::Launcher(UD* p, PlayerManager* pm) {
	projectile = p;
	launchTimer = glfwGetTime();
	children.push_back(projectile);
	sb = dynamic_cast<SlimeBall*>(projectile);
	tags.push_back("Launcher");
	playMan = pm;
	
}

void Launcher::launch() {
	SoundManager::getInstance().playSound("cork",0);

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> dist(-.25f, .25f);
	float value = dist(rng);
	
	
	float x1 = Parent->getPos().x;
	float x2 = playMan->getp2()->getPos().x;
	float y1 = Parent->getPos().y;
	float y2 = playMan->getp2()->getPos().y;



	float dx = x2 - x1 + dist(rng);
	float dy = y2 - y1 + dist(rng);

	float norm = std::sqrt(dx * dx + dy * dy);

	glm::vec3 pVel = glm::vec3(dx / norm, dy / norm, 0) * glm::vec3(0.5f);
	
	sb->setVelocity(pVel);
	
	sb->setScale(glm::vec3(1, 1, 1));
	sb->setActive(true);
	cm.addObject(sb);
}

void Launcher::Update() {
	
	if (!sb->getActive()) {
		launchTimer += timer.getDeltaTime();
		if (launchTimer >= 1.9)
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

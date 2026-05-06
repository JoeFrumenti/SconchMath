#include "PlayerManager.h"

PlayerManager::PlayerManager(BouncingCube* a, BouncingCube* b) {
	p1 = a;
	p2 = b;

	display = new Text(ShaderCollection::getInstance().getShader("Text"), "C:/Windows/Fonts/BOD_B.TTF");

	pos = glm::vec3(135.0f, 729.0f, 0.f);
	textScale = 0.716;
}

void PlayerManager::Update() {
	pos += input.getInput() * glm::vec3(3.0f,3.0f,3.0f);
	textScale += input.getInputWASD().x * 0.001f;



	if (input.isE()) {
		std::cout << pos.x << " " << pos.y << " " << textScale;
	}
		

	/*if (!win)
	{

		if (p1->getStats()["coins"] >= 10) {
			p2->setScale(glm::vec3(.0f, .0f, .0f));
			UDMan.removeObject(p2->getId());
			cm.removeObject(p2->getId());
			win = true;
		}

		if (p2->getStats()["coins"] >= 10) {
			p1->setScale(glm::vec3(.0f, .0f, .0f));
			UDMan.removeObject(p1->getId());
			cm.removeObject(p1->getId());
			delete p1;
			win = true;
		}
	}*/
}

void PlayerManager::Draw() {

}

void PlayerManager::drawText() {
	display->RenderText(message, pos.x, pos.y, textScale,
		glm::vec3(1.0, 1.0f, 1.0f));
}

#include "PlayerManager.h"

PlayerManager::PlayerManager(BouncingCube* a, BouncingCube* b) {
	p1 = a;
	p2 = b;

	display = new Text(ShaderCollection::getInstance().getShader("Text"), "C:/Windows/Fonts/BOD_B.TTF");

	coin = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
	coin->translate(glm::vec3(-0.75f, 10.5f, .25f));
	coin->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));
	coin->scale(glm::vec3(0.36f, 0.36f, 0.36f));
}

void PlayerManager::Update() {
	
	coin->Update();
	

	if (winner == 0)
	{

		if (p1->getStats()["coins"] >= 100) {
			
			cm.removeObject(p2->getId());
			winner = 1;
		}

		if (p2->getStats()["coins"] >= 100) {
			
			cm.removeObject(p1->getId());
			winner = 2;
		}
	}
	else if (winner == 1) {
		loserScale -= 1.0f / 60.0f;
		p2->setScale(glm::vec3(loserScale, loserScale, loserScale));
		if (loserScale <= 0) {
			loserScale = 0;
			UDMan.removeObject(p2->getId());
			delete p2;
			winner = 3;
		}

	}

	else if (winner == 2) {
		loserScale -= 1.0f / 60.0f;
		p1->setScale(glm::vec3(loserScale, loserScale, loserScale));
		if (loserScale <= 0) {
			loserScale = 0;
			UDMan.removeObject(p1->getId());
			delete p1;
			winner = 3;
		}
			
	}
}

void PlayerManager::Draw() {
	coin->Draw();
}

void PlayerManager::drawText() {
	display->RenderText(message, 135.0f, 729.0f, 0.716f,
		glm::vec3(1.0, 1.0f, 1.0f));
}

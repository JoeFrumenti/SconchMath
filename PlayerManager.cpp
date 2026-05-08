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
	textPos.x += input.getInput().x;
	if (input.isE())
		std::cout << textPos.x << std::endl;

	if (winner == 0)
	{

		if (p1->getStats()["coins"] >= 100) {
			p2->lose();
			winner = 1;
			message = "WINNER: RED";
		}

		if (p2->getStats()["coins"] >= 100) {
			p1->lose();
			winner = 2;
			message = "WINNER: BLUE";
			textPos.x = 63;
		}
	}

}

void PlayerManager::Draw() {
	if(winner ==0)
		coin->Draw();
}

void PlayerManager::drawText() {
	display->RenderText(message, textPos.x, textPos.y, 0.716f,
		glm::vec3(1.0, 1.0f, 1.0f));
}

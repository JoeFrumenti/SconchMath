#include "PlayerManager.h"
#include <iomanip>

PlayerManager::PlayerManager(BouncingCube* a, BouncingCube* b) {
	p1 = a;
	p2 = b;

	display = new Text(ShaderCollection::getInstance().getShader("Text"), "C:/Windows/Fonts/BOD_B.TTF");

	coin = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
	coin->translate(glm::vec3(-0.75f, 10.5f, .25f));
	coin->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));
	coin->scale(glm::vec3(0.36f, 0.36f, 0.36f));
}

PlayerManager::PlayerManager() {

}

void PlayerManager::Update() {
	
	coin->Update();


	oss.str("");
	oss << std::fixed << std::setprecision(1) << p1->getDebuffTime();
	p1StatMsg = "Slime time: " + oss.str();


	oss.str("");
	oss << std::fixed << std::setprecision(1) << p2->getDebuffTime();
	p2StatMsg = "Freeze time: " + oss.str();

	p1Stats += glm::vec2(input.getInputWASD().x, input.getInputWASD().y);
	p2Stats += glm::vec2(input.getInput().x, input.getInput().y);
	if (input.isE())
		std::cout << p1Stats.x << " " << p1Stats.y <<  " " << p2Stats.x << std::endl;

	if (winner == 0)
	{

		if (p1->getStats()["coins"] >= 100) {
			p2->lose();
			winner = 1;
			message = "WINNER: SLIMEBALL";
			SoundManager::getInstance().playSound("slimewins",0);
			
		}

		if (p2->getStats()["coins"] >= 100) {
			p1->lose();
			winner = 2;
			message = "WINNER: ICE";
			textPos.x = 63;
			SoundManager::getInstance().playSound("icewins", 0);
			
		}
	}
	else {
		UDtimer += MyTimer::getInstance().getDeltaTime();
		if (UDtimer >= 1) {
			if (winner == 1)
				p1->win();
			else if (winner == 2)
				p2->win();
			winner = 3;
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
	display->RenderText(p1StatMsg, p1Stats.x, p1Stats.y, 0.4f,
		glm::vec3(.0, 1.0f, .0f));
	display->RenderText(p2StatMsg, p2Stats.x, p2Stats.y, 0.4f,
		glm::vec3(.0, .0f, 1.0f));
}

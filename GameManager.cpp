#include "GameManager.h"
#include <iomanip>

GameManager::GameManager(BouncingCube* a, BouncingCube* b) {
	

	players[0] = a;
	players[1] = b;

	std::cout << "Debuff time: " << players[0]->getDebuffTime() << "\n";

	display = new Text(ShaderCollection::getInstance().getShader("Text"), "C:/Windows/Fonts/BOD_B.TTF");
	coin = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
	coin->translate(glm::vec3(-0.75f, 10.5f, .25f));
	coin->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));
	coin->scale(glm::vec3(0.36f, 0.36f, 0.36f));
}

GameManager::GameManager() {
	display = new Text(ShaderCollection::getInstance().getShader("Text"), "C:/Windows/Fonts/BOD_B.TTF");
	coin = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
}

void GameManager::Update() {
	
	coin->Update();

	

	oss.str("");
	oss << std::fixed << std::setprecision(1) << players[1]->getDebuffTime();
	p2StatMsg = "Freeze time: " + oss.str();


	if (winner == 0)
	{

		if (players[0]->getStats()["coins"] >= 100) {
			players[1]->lose();
			winner = 1;
			message = "WINNER: SLIME";
			SoundManager::getInstance().playSound("slimewins",0);
			
		}

		if (players[1]->getStats()["coins"] >= 100) {
			players[0]->lose();
			winner = 2;
			message = "WINNER: ICE";
			textPos.x = 63;
			SoundManager::getInstance().playSound("icewins", 0);
			
		}
	}
	else if (winner == 1) {
		players[0]->win();
		winner = 3;
	}
	else if (winner == 2) {
		players[1]->win();
		winner = 3;
	}

}

void GameManager::Draw() {
	if(winner ==0)
		coin->Draw();
}

void GameManager::drawText() {
	display->RenderText(message, textPos.x, textPos.y, 0.716f,
		glm::vec3(1.0, 1.0f, 1.0f));
	
	display->RenderText(p2StatMsg, p2Stats.x, p2Stats.y, 0.4f,
		glm::vec3(.0, .0f, 1.0f));
}

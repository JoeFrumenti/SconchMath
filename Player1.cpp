#include "Player1.h"

Player1::Player1(){
	coinShader = ShaderCollection::getInstance().getShader("Model");
	textShader = ShaderCollection::getInstance().getShader("Text");
	textManager = new Text(textShader, "C:/Windows/Fonts/comic.ttf");
	coin = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
	parentModel = NULL;
	UDManager::getInstance().addUD(this);
		
}

void Player1::setParent(UD* parent){
	this->Parent = parent;
	coins = dynamic_cast<BouncingCube*>(Parent)->getStats()["coins"];
	parentModel = dynamic_cast<BouncingCube*>(Parent)->getModel();
}

void Player1::Update(){
	cModel = glm::mat4(1.0f);
	cModel = glm::translate(cModel, glm::vec3(-5.25f, 8.75f, 1.0f));
	cModel = glm::rotate(cModel, (float)glfwGetTime() / 2, glm::vec3(.0f, 1.0f, 0.0f));
	cModel = glm::scale(cModel, glm::vec3(.515f, .465001f, .465f));

	copyModel = glm::mat4(1.0f);
	copyModel = glm::translate(copyModel, glm::vec3(-4.25f, 10.25f, 1.0f));
	copyModel = glm::rotate(copyModel, (float)glfwGetTime() / 2, glm::vec3(.0f, 1.0f, 0.0f));
	copyModel = glm::scale(copyModel, Parent->getScale());

	coins = dynamic_cast<BouncingCube*>(Parent)->getStats()["coins"];
	coinString = "x" + std::to_string(coins);

	oss.str("");
	oss << std::fixed << std::setprecision(1) << gameMan.getp1()->getStats()["debuffTime"];
	p1StatMsg = "Slime time: " + oss.str();
}

void Player1::Draw(){
	coinShader->use();

	coinShader->setMat4("model", cModel);
	coinShader->setVec4("color", glm::vec4(1.0f,1.0f,1.0f,1.0f));
	coin->Draw(*coinShader);

	coinShader->setMat4("model", copyModel);
	parentModel->Draw(*coinShader);
}

void Player1::drawText(){
	textShader->use();
	textManager->RenderText(coinString, 69.25f, 678.25f, .7825f,
		glm::vec3(1.0, 1.0f, 1.0f));

	textManager->RenderText(p1StatMsg, p1Stats.x, p1Stats.y, 0.4f,
		glm::vec3(.0, 1.0f, .0f));
}

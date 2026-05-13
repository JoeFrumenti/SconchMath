#pragma once
#include "GameManager.h"
#include "UD.h"
#include "Text.h"
#include "Model.h"
#include "BouncingCube.h"
#include "ShaderCollection.h"

class BouncingCube;


class Player2 : public UD {

private:
	int coins = 0;
	Text* textManager;
	Shader* textShader;
	Shader* coinShader;

	glm::mat4 cModel;
	glm::mat4 copyModel;
	std::string coinString;
	std::string p2StatMsg;
	std::ostringstream oss;
	glm::vec2 p2Stats = glm::vec2(305.0f, 177.0f);

	Model* coin;
	Model* parentModel;

	GameManager& gameMan = GameManager::getInstance();
public:

	Player2();

	void setParent(UD* parent) override;

	void Update() override;

	void Draw() override;

	void drawText() override;

};
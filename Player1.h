#pragma once
#include "GameManager.h"
#include "UD.h"
#include "Text.h"
#include "Model.h"
#include "BouncingCube.h"
#include "ShaderCollection.h"
#include <iomanip>

class BouncingCube;


class Player1 : public UD {

private:
	int coins = 0;
	Text* textManager;
	Shader* textShader;
	Shader* coinShader;

	glm::vec2 p1Stats = glm::vec2(32.0f, 177.0f);

	glm::mat4 cModel;
	glm::mat4 copyModel;
	std::string coinString;
	std::string p1StatMsg;

	Model* coin;
	Model* parentModel;
	std::ostringstream oss;

	GameManager& gameMan = GameManager::getInstance();
public:

	Player1();
	void setParent(UD* parent) override;
	void Update() override;

	void Draw() override;

	void drawText() override;
};
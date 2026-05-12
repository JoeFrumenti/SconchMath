#pragma once
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

	Model* coin;
	Model* parentModel;
public:

	Player2();

	void setParent(UD* parent) override;

	void Update() override;

	void Draw() override;

	void drawText() override;

};
#include "UD.h"
#include "Text.h"

class Player1 : public UD {

private:
	int coins = 0;
	Text* textManager;
	Shader* textShader;

	std::string coinString;
	glm::vec2 tPos = glm::vec2(69.25f, 678.25f);
	float tScale = .7925f;
public:

	Player1(Shader* ts) {
		textShader = ts;
		textManager = new Text(textShader, "C:/Windows/Fonts/comic.ttf");
	}

	void setParent(UD* parent) override {
		this->Parent = parent;
		coins = parent->getStats()["coins"];
	}

	void Update() override {
		coins = Parent->getStats()["coins"];
		coinString = "x" + std::to_string(coins);
	}

	void Draw() override {

	}

	void drawText() override{
		textShader->use();
		textManager->RenderText(*textShader, coinString, tPos.x, tPos.y, tScale,
			glm::vec3(1.0, 1.0f, 1.0f));
	}

};
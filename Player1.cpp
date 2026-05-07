#include "UD.h"
#include "Text.h"
#include "Model.h"
#include "BouncingCube.h"
#include "ShaderCollection.h"

class BouncingCube;


class Player1 : public UD {

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

	Player1() {
		coinShader = ShaderCollection::getInstance().getShader("Model");
		textShader = ShaderCollection::getInstance().getShader("Text");
		textManager = new Text(textShader, "C:/Windows/Fonts/comic.ttf");
		coin = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj");
		parentModel = NULL;
		
	}

	void setParent(UD* parent) override {
		this->Parent = parent;
		coins = parent->getStats()["coins"];
		parentModel = dynamic_cast<BouncingCube*>(Parent)->getModel();
	}

	void Update() override {
		cModel = glm::mat4(1.0f);
		cModel = glm::translate(cModel, glm::vec3(-5.25f, 8.75f, 1.0f));
		cModel = glm::rotate(cModel, (float)glfwGetTime() / 2, glm::vec3(.0f, 1.0f, 0.0f));
		cModel = glm::scale(cModel, glm::vec3(.515f, .465001f, .465f));

		copyModel = glm::mat4(1.0f);
		copyModel = glm::translate(copyModel, glm::vec3(-4.25f, 10.25f, 1.0f));
		copyModel = glm::rotate(copyModel, (float)glfwGetTime() / 2, glm::vec3(.0f, 1.0f, 0.0f));
		copyModel = glm::scale(copyModel, glm::vec3(.715f, .715f, .715f) * Parent->getScale());

		coins = Parent->getStats()["coins"];
		coinString = "x" + std::to_string(coins);
	}

	void Draw() override {
		coinShader->use();

		coinShader->setMat4("model", cModel);
		coinShader->setVec4("color", glm::vec4(1.0f,1.0f,1.0f,1.0f));
		coin->Draw(*coinShader);

		coinShader->setMat4("model", copyModel);
		parentModel->Draw(*coinShader);
	}

	void drawText() override{
		textShader->use();
		textManager->RenderText(coinString, 69.25f, 678.25f, .7825f,
			glm::vec3(1.0, 1.0f, 1.0f));
	}

};
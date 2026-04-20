
#include "UD.h"
#include "Model.h"

#include <iostream>

class Coin : public UD {
private:
	Model* ourModel;
	glm::mat4 model;

	glm::vec3 pos;

public:

	Coin() {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f,.0f,.0f);
	}


	void Update() override{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos); 
		model = glm::rotate(model, (float)glfwGetTime() * 3, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.05f, .1f));	
	}

	void Draw(Shader* shader) override{
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}
};
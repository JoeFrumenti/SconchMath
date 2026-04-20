#include "UD.h"
#include "Model.h"

#include <iostream>

class Coin : public UD {
private:
	Model* ourModel;
	glm::mat4 model;

public:

	Coin() {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj";

		ourModel = new Model(path);
	}

	void Update() override{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.1f, 0.07f, .1f));	// it's a bit too big for our scene, so scale it down
	}

	void Draw(Shader* shader) override{
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}
};
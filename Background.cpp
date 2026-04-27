
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include <iostream>

class Background : public UD {
private:
	Model* ourModel;
	glm::mat4 model;

	glm::vec3 pos;

	Shader* shader;

public:

	Background(Shader* shade) {
		char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundPB.obj";
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = shade;

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(.0f,-10.0f,-3.0f));
		model = glm::rotate(model, 3.1415926536f, glm::vec3(.0f, .0f, 1.0f));
	}


	void Update() override {
		
	}

	void Draw() override {
		shader->setMat4("model", model);
		ourModel->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}

	glm::vec3 getPos() override {
		return pos;
	}
};
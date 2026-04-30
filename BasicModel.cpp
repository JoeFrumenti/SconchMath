
#include "UD.h"
#include "Model.h"
#include "Shaders/shader.h"

#include "InputManager.h"

#include <iostream>

class BasicModel : public UD {
private:
	Model* ourModel;
	glm::mat4 model;

	glm::vec3 pos;
	float angle;
	glm::vec3 rot;
	glm::vec3 sca = glm::vec3(1.0f,1.0f,1.0f);
	

	Shader* shader;

	InputManager* input;
	glm::vec3 velocity = glm::vec3(0.25f, 0.25f, 0.0f);
	bool isInput = false;

public:

	BasicModel(Shader* shade, char* path, InputManager* i) {
		ID = 0;
		ourModel = new Model(path);
		pos = glm::vec3(.0f, .0f, .0f);
		shader = shade;
		angle = 0;
		input = i;
		
	}

	void setInput(bool inp) {
		isInput = inp;
	}

	void Update() override {
		if (isInput) {
			pos += input->getInput() * velocity;
			sca += input->getInputWASD() * glm::vec3(0.0025f, 0.0025f, 0.0025f);

			if (input->isE()) {
				std::cout << pos.x << " " << pos.y << " "
					<< sca.x << " " << sca.y << std::endl;
			}
		}

		
		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		model = glm::rotate(model, angle, rot);
		model = glm::scale(model, sca);
	}

	void Draw() override {

		shader->use();
		
		shader->setMat4("model", model);
		shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ourModel->Draw(*shader);
	}

	void translate(glm::vec3 translation) {
		pos += translation;
	}

	void rotate(float a, glm::vec3 translation) {
		angle += a;
		rot += translation;
	}

	void scale(glm::vec3 translation) {
		sca.x *= translation.x;
		sca.y *= translation.y;
		sca.z *= translation.z;

	}

	glm::vec3 getPos() override {
		return pos;
	}
};
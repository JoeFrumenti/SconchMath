
#include "BasicModel.h"

BasicModel::BasicModel(Shader* shade, char* path) {
	ID = 0;
	ourModel = new Model(path);
	pos = glm::vec3(.0f, .0f, .0f);
	shader = shade;
	angle = 0;
		
}

void BasicModel::setInput(bool inp) {
	isInput = inp;
}

void BasicModel::Update() {
		

		
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, angle, rot);
	model = glm::scale(model, sca);
}

void BasicModel::Draw() {

	shader->use();
		
	shader->setMat4("model", model);
	shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ourModel->Draw(*shader);
}

void BasicModel::translate(glm::vec3 translation) {
	pos += translation;
}

void BasicModel::rotate(float a, glm::vec3 translation) {
	angle += a;
	rot += translation;
}

void BasicModel::scale(glm::vec3 translation) {
	sca.x *= translation.x;
	sca.y *= translation.y;
	sca.z *= translation.z;

}

glm::vec3 BasicModel::getPos() {
	return pos;
}

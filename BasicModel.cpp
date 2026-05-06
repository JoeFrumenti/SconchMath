
#include "BasicModel.h"

BasicModel::BasicModel(std::string path) {
	ID = 0;
	ourModel = new Model(path.c_str());
	pos = glm::vec3(.0f, .0f, .0f);
	shader = ShaderCollection::getInstance().getShader("Model");
	angle = 0;
	sca = glm::vec3(1.0f,1.0f,1.0f);
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

glm::vec3 BasicModel::getScale() {
	return sca;
}

#include "Icey.h"




void Orbital::setParent(UD* parent) {
	this->Parent = parent;
	width = 0.5;
	height = 0.5;
	cm.addObject(this);

}

void Orbital::Update() {
	pos = Parent->getPos() + glm::vec3(cos(glfwGetTime() * 6) * 2.8, sin(glfwGetTime() * 6) * 2.8, .0f);

	model = glm::mat4(1.0f);
	model = glm::translate(model, getPos());
	model = glm::scale(model, glm::vec3(getWidth(), getHeight(), 0.5));


}
void Orbital::Draw() {
	shader->use();
	shader->setMat4("model", model);
	shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ourModel->Draw(*shader);

}
void Orbital::drawText() {

}



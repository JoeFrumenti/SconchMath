#include "Icey.h"




void Orbital::setParent(BouncingCube* parent) {
	this->Parent = parent;
	width = 0.5;
	height = 0.5;
	cm.addObject(this);

}

void Orbital::Update() {
	if (Parent->getLoser()) {
		UDManager::getInstance().queueRemoval(ID);
		CollisionManager::getInstance().removeObject(ID);
		return;
	}
	pos = Parent->getPos() + glm::vec3(cos(glfwGetTime() * 6) * 2.8, sin(glfwGetTime() * 6) * 2.8, .0f);

	model = glm::mat4(1.0f);
	model = glm::translate(model, getPos());
	model = glm::scale(model, glm::vec3(getWidth(), getHeight(), 0.5));


}
void Orbital::Draw() {
	if (Parent->getLoser())
		return;
	shader->use();
	shader->setMat4("model", model);
	shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ourModel->Draw(*shader);

}
void Orbital::drawText() {

}



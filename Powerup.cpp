#include "Powerup.h"

Powerup::Powerup(int type) {
	tags.push_back("powerup");
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/powerup.obj");
	shader = ShaderCollection::getInstance().getShader("Model");

	this->type = type;

	CollisionManager::getInstance().addObject(this);
	UDManager::getInstance().addUD(this);
}

void Powerup::Draw() {
	mMatrix = glm::mat4(1.0f);
	mMatrix = glm::translate(mMatrix, pos);
	mMatrix = glm::rotate(mMatrix, 3.14159265358979f / 2, glm::vec3(1.0f, .0f, .0f));
	mMatrix = glm::scale(mMatrix, glm::vec3(0.5f));


	shader->setMat4("model", mMatrix);
	shader->setVec4("color", glm::vec4(1.0f));

	ourModel->Draw(*shader);

}

void Powerup::Update() {
	pos.y -= .1f;
}
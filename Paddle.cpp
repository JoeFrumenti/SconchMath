#include "Paddle.h"

Paddle::Paddle() {
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/paddle.obj");
	shader = ShaderCollection::getInstance().getShader("Model");

	width = .6f;
	height = 0.6f;
}

void Paddle::Update() {
	pos += InputManager::getInstance().getInput() * speed;
}

void Paddle::Draw() {
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, scale);


	shader->use();

	shader->setMat4("model", model);
	ourModel->Draw(*shader);
}

void Paddle::Collide(Collision col) {

}
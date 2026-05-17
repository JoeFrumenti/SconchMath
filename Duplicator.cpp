#include "Duplicator.h"


Duplicator::Duplicator() {
	
	UDManager::getInstance().addUD(this);
	CollisionManager::getInstance().addObject(this);
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj");
	shader = ShaderCollection::getInstance().getShader("Model");
	width = 0.5f;
	height = 0.5f;
	tags.push_back("bcube");

}

float Duplicator::randomFloat(float min, float max) {
	
		static std::mt19937 gen(std::random_device{}());
		std::uniform_real_distribution<float> dist(min, max);
		return dist(gen);
	
}

void Duplicator::Update() {
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.3f, .7f, 0.0f));
	model = glm::scale(model, scale);
}

void Duplicator::Collide(Collision col) {
	for (auto& tag : col.obj->getTags()) {
		if (tag == "bcube") {
			BouncingCube* cube = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
			cube->setScale(glm::vec3(0.4f));
			cube->addTag("bcube");
			cube->setVelocity(glm::normalize(glm::vec3(randomFloat(-1.0f,1.0f), randomFloat(-1.0f,0.0f), 0.0f)) * glm::vec3(0.25f));

			UDManager::getInstance().addUD(cube);
		}
	}
}

void Duplicator::Draw() {
	shader->use();
	shader->setMat4("model", model);
	shader->setVec4("color", color);
	ourModel->Draw(*shader);
}
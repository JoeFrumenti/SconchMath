#include "BouncingCube.h"

class Icey : public UD {
private:
	Model* ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/ice.obj");
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	CollisionManager& cm = CollisionManager::getInstance();
	glm::mat4 model;

public:
	Icey() {
		tags.push_back("Icey");
	}

	void setParent(UD* parent) override {
		this->Parent = parent;
		width = 0.5;
		height = 0.5;
		cm.addObject(this);
	}

	void Update() {
		
		pos = Parent->getPos() + glm::vec3(cos(glfwGetTime() * 4) * 2, sin(glfwGetTime() * 4) * 2, .0f);

		model = glm::mat4(1.0f);
		model = glm::translate(model, getPos());
		model = glm::scale(model, glm::vec3(getWidth(), getHeight(), 0.5));

	}
	void Draw() {
		shader->use();
		shader->setMat4("model", model);
		shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ourModel->Draw(*shader);
		
	}
	void drawText() {

	}

	void Collide(Collision col) override {

		for (auto& tag : col.obj->getTags())
		{
			if (tag == "bcube" && col.obj != Parent) {
				dynamic_cast<BouncingCube*>(col.obj)->freeze(1);
			}
		}
	}
};
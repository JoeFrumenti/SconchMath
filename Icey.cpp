#include "BouncingCube.h"

class Icey : public UD {
private:
	Model* ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
	Shader* shader = ShaderCollection::getInstance().getShader("Model");

	glm::mat4 model;

public:
	Icey() {
		tags.push_back("Icey");
	}

	void setParent(UD* parent) override {
		this->Parent = parent;
		width = Parent->getWidth();
		height = Parent->getHeight();
		
	}

	void Update() {
		
		pos = Parent->getPos() + glm::vec3(cos(glfwGetTime()), sin(glfwGetTime()), .0f);

		model = glm::mat4(1.0f);
		model = glm::translate(model, pos);
		
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
			if (tag == "coin") {
				Parent->getStats()["coins"]++;
			}
		}
	}
};
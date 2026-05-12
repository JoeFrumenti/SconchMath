#include "BouncingCube.h"
#include <algorithm>

class Icey : public UD {
private:
	Model* ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/ice.obj");
	Shader* shader = ShaderCollection::getInstance().getShader("Model");
	CollisionManager& cm = CollisionManager::getInstance();
	glm::mat4 model;
	float freezeTime = 1;
	
public:
	Icey() {
		tags.push_back("Icey");
		width = 0.5;
		height = 0.5;
		UDManager::getInstance().addUD(this);
	}

	void setParent(UD* parent) override {
		this->Parent = parent;
		width = 0.5;
		height = 0.5;
		cm.addObject(this);
		
	}

	void Update() {
		
		pos = Parent->getPos() + glm::vec3(cos(glfwGetTime() * 6) * 2.8, sin(glfwGetTime() * 6) * 2.8, .0f);

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
		BouncingCube* ob = dynamic_cast<BouncingCube*>(col.obj);
		BouncingCube* par = dynamic_cast<BouncingCube*>(Parent);

		for (auto& tag : col.obj->getTags())
		{
			if (tag == "bcube" && col.obj != Parent && !(ob->getFrozen())) {
				
				ob->freeze(par->getDebuffTime());
				par->addDebuffTime(0.2f);
				freezeTime = std::min(freezeTime + 0.3f, 2.0f);

			}
		}
	}
};
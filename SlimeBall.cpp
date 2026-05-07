#include "UD.h"
#include "Model.h"
#include "Projectile.h"
class SlimeBall : public Projectile {

public:
	SlimeBall() {
		width = 0.7;
		height = 0.7;
		ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere2.obj");
		velocity = glm::vec3(-0.11f, 0.24f, 0.0f);
	}

	

	void Collide(Collision col) override {
		for (auto& tag : col.obj->getTags()) {
			if (tag == "bcube" && col.obj != Parent)
				std::cout << "SLIME!";
		}
	}

	void test() {
		std::cout << "TEST\n";
	}

};
#include "UD.h"
#include "Model.h"
#include "Projectile.h"
#include "BouncingCube.h"
class SlimeBall : public Projectile {

public:
	SlimeBall() {
		width = 0.7;
		height = 0.7;
		std::cout << "NEW SLIMEBALL\n";
		ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/slimeball.obj");
		velocity = glm::vec3(-0.11f, 0.24f, 0.0f);
		
	}

	

	void Collide(Collision col) override {
		for (auto& tag : col.obj->getTags()) {
			if (tag == "bcube" && col.obj != Parent) {
				std::cout << "Slowing!\n";
				dynamic_cast<BouncingCube*>(col.obj)->slow(1);
				isActive = false;
				bounces = 0;
				cm.removeObject(this->getId());
			}
		}
	}


};
#include "Paddle.h"

Paddle::Paddle() {
	ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/paddle.obj");
	shader = ShaderCollection::getInstance().getShader("Model");

	width = 1.9f;
	height = .2f;
	CollisionManager::getInstance().addObject(this);
}

void Paddle::Update() {
	lastPos = pos;
	velocity = InputManager::getInstance().getMouseMovement() * speed;
	pos = glm::vec3(velocity.x * 8, pos.y, pos.z);
	
	velocity = pos - lastPos;
}

void Paddle::Draw() {
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, 3.14159265f / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, scale);


	shader->use();

	shader->setMat4("model", model);
	shader->setVec4("color", glm::vec4(1));
	ourModel->Draw(*shader);
}

void Paddle::Collide(Collision col) {
	for (auto& tag : col.obj->getTags()) {
		if (tag == "bcube") {
			BouncingCube* cube = dynamic_cast<BouncingCube*>(col.obj);
			if (cube->getPos().y >= pos.y) {
				float diff = cube->getPos().x - pos.x;
				
				float angle = diff / width * 70.0f;

				float angleRad = glm::radians(angle);

				float speed = glm::length(cube->getVelocity());
				glm::vec3 newDir = glm::normalize(glm::vec3(
					glm::sin(angleRad),
					1.0f,
					0.0f
				));

				cube->setVelocity(newDir * speed);

			}
			else {
				float diff = cube->getPos().x - pos.x;
				int sign = (diff > 0) - (diff < 0);
				cube->setVelocity(cube->getVelocity() * glm::vec3(-2 * sign, 1, 1) + velocity);
				cube->translate(cube->getVelocity());
			}

		}
		else if (tag == "powerup") {
			
			BallContainer::getInstance().multiplyBalls(2);
			UDManager::getInstance().removeObject(col.obj->getId());
			CollisionManager::getInstance().removeObject(col.obj->getId());
			
		}
	}
}
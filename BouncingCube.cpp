
#include "BouncingCube.h"
Model* BouncingCube::getModel() {
	return ourModel;
}

BouncingCube::BouncingCube(std::string path) {
	velocity = glm::vec3(-0.25f, -0.35f, 0.0f);
	soundMan.addSound("bounce", "C:/Users/joefr/source/repos/SconchMath/assets/chime.wav");

	textShader = ShaderCollection::getInstance().getShader("Text");;

	CollisionManager& cm = CollisionManager::getInstance();

	ourModel = new Model(path);

	shader = ShaderCollection::getInstance().getShader("Model");
	tags.push_back("bcube");
	this->width = 1.0f;
	this->height = 1.0f;
	cm.addObject(this);
}

BouncingCube::~BouncingCube() {
	std::cout << "BC DESTRUCTOR CALLED\n";
	CollisionManager& cm = CollisionManager::getInstance();
	UDManager& UDMan = UDManager::getInstance();
	UDMan.removeObject(getId());
	for (UD* obj : children) {
		cm.removeObject(obj->getId());
		UDMan.removeObject(obj->getId());
		delete obj;
	}
}

void BouncingCube::Collide(Collision col) {
		
	for (auto& tag : col.obj->getTags())
	{
		
		if (tag == "bcube")
		{

			UD* obj = col.obj;

			const float dx = obj->getPos().x - pos.x;
			const float dy = obj->getPos().y - pos.y;
			const float dist = std::sqrt(dx * dx + dy * dy);

			const float nx = dx / dist;
			const float ny = dy / dist;

			const float dvx = obj->getVelocity().x - velocity.x;
			const float dvy = obj->getVelocity().y - velocity.y;
			const float dvn = dvx * nx + dvy * ny;

			if (dvn >= 0) return;  // already separating, skip

			obj->setVelocity(glm::vec3(obj->getVelocity().x - dvn * nx,
				obj->getVelocity().y - dvn * ny, .0f));
			velocity.x += dvn * nx;
			velocity.y += dvn * ny;
				

				
		}
	}
}


void BouncingCube::screenBounce() {
	float scale = 0.65f;
	float boundsX = 8.8f * scale;
	float boundsY = 16.7f * scale;

		
	pos += velocity;

	if (pos.x + width >= 6 || pos.x - width <= -6) {
			
		soundMan.playSong("bounce");
		velocity.x = -velocity.x;
		pos.x += velocity.x;

	}
	if (pos.y + height >= 7.75 || pos.y - height <= -11.25) {
		soundMan.playSong("bounce");
		velocity.y = -velocity.y;
		pos.y += velocity.y;
	}

}

void BouncingCube::lose() {
	loser = true;

	CollisionManager& cm = CollisionManager::getInstance();
	cm.removeObject(ID);


	for (UD* child : children) {
		for (auto& tag : child->getTags()) {
			if (tag == "CoinPickup") {
				cm.removeObject(child->getId());
			}
		}
	}
}

void BouncingCube::Update() {
	for(UD* child : children) {
		child->Update();
	}

	lastPos = pos;

	screenBounce();

	if (loser) {
		loserScale -= 1.0f / 60.0f;
		setScale(glm::vec3(loserScale, loserScale, loserScale));
		if (loserScale <= 0) {
			loserScale = 0;
			
			return;
		}
	}

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.3f, .7f, 0.0f));		
	model = glm::scale(model, glm::vec3(0.8f *scale.x, 0.8f *scale.y, .8f * scale.z));
		
}

void BouncingCube::Draw(){
	

	for (UD* child : children) {
		child->Draw();
	}

	if (loserScale <= 0) {
		loserScale = 0;

		return;
	}

	shader->setMat4("model", model);
	shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ourModel->Draw(*shader);
}



void BouncingCube::drawText(){
	for (UD* child : children) {
		child->drawText();
	}
	float scale = 1.0f;
	textShader->use();
}

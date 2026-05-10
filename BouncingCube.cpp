
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
	
	width = .6f;
	height = 0.6f;


	scale = glm::vec3(width);
	cm.addObject(this);
}

void BouncingCube::addDebuffTime(float f) {
	debuffTime = std::min(debuffTime + f, 2.0f);
	std::cout << debuffTime << std::endl;
}

float BouncingCube::getDebuffTime() {
	 return debuffTime; 
}
void BouncingCube::win() {
	std::cout << "WINNING\n";
	velocity = glm::vec3(1,.1,0);
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

			if (dvn >= 0 || isFrozen) return;  // already separating, skip



			obj->setVelocity(glm::vec3(obj->getVelocity().x - dvn * nx,
				obj->getVelocity().y - dvn * ny, .0f));

			

			velocity.x += dvn * nx;
			velocity.y += dvn * ny;

			if (dynamic_cast<BouncingCube*>(obj)->getFrozen())
				velocity = glm::normalize(velocity) * glm::vec3(speed);
				

				
		}
	}
}


void BouncingCube::screenBounce() {
	
	if (isSlowed)
		pos += velocity * glm::vec3(0.2, 0.2, 0.2);
	else
		pos += velocity;

	if (pos.x + width >= 6 || pos.x - width <= -6) {
			
		soundMan.playSong("bounce");
		velocity.x = -velocity.x;
		pos.x += velocity.x;

	}
	if (pos.y + height >= 8 || pos.y - height <= -5.5) {
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
			cm.removeObject(child->getId());
			for (auto& tag : child->getTags()) {
				if (tag == "Launcher")
					cm.removeObject(child->getChildren()[0]->getId());
			}
			
	}
	
}

void BouncingCube::Update() {
	for(UD* child : children) {
		child->Update();
	}

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(.3f, .7f, 0.0f));
	model = glm::scale(model, scale);

	if (isFrozen) {
		float elapsed = glfwGetTime() - freezeStartTime;
		if (elapsed >= freezeDuration) {
			isFrozen = false;
			velocity = frozenVelocity;
			color = glm::vec4(1.0f, 1.0f, 1.0f,1);
			soundMan.playSound("unfreeze", 0);
		}
		return;
	}


	if (isSlowed) {
		slowTimer += timer.getDeltaTime();
		if (slowTimer >= slowCap)
		{
			isSlowed = false;
			color = glm::vec4(1, 1, 1, 1);
			velocity = glm::normalize(velocity) * glm::vec3(speed);
		}
	}

	lastPos = pos;

	screenBounce();

	if (loser) {
		
		setScale(glm::vec3(scale.x - 0.05f));
		if (scale.x <= 0) {
			scale = glm::vec3(0);
			UDManager::getInstance().queueRemoval(getId());
			return;
		}
	}

		
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
	shader->setVec4("color", color);
	ourModel->Draw(*shader);

}

void BouncingCube::freeze(float freezeTime) {
	soundMan.playSound("freeze", 0);
	if(!isFrozen)
		frozenVelocity = velocity;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	isFrozen = true;
	freezeStartTime = glfwGetTime(); 
	freezeDuration = freezeTime;
	color = glm::vec4(0.5f, 0.5f, 1.0f,1);
}

void BouncingCube::slow(float t) {
	color = glm::vec4(0.5f, 1.0f, .5f, 1);
	
		slowCap = t;
		isSlowed = true;
		slowTimer = 0;
	
}

void BouncingCube::drawText(){
	for (UD* child : children) {
		child->drawText();
	}
	float scale = 1.0f;
	textShader->use();
}

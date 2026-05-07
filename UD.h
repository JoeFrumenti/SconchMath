#pragma once
#include "Shaders/shader.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "Collision.h"

class UD {
protected:
	int ID;
	glm::vec3 lastPos;
	glm::vec3 pos;
	std::vector<std::string> tags;
	glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
	glm::vec3 velocity;
	float width;
	float height;
	UD* Parent;
	std::vector<UD*> children;

	std::map<std::string, float> stats;

public:
	//UD();
	virtual int getId() { return ID; };
	virtual float getWidth() { return width; }
	virtual float getHeight() { return height; }
	virtual glm::vec3 getLastPos() { return this->lastPos; }
	virtual std::vector<std::string> getTags() { return this->tags; }
	virtual glm::vec3 getVelocity() { return this->velocity; }
	virtual glm::vec3 getScale() { return scale; }


	virtual void setId(int id) { ID = id; };
	virtual void setVelocity(glm::vec3 v) { this->velocity = v; }
	virtual void setScale(glm::vec3 v) { this->scale = v; }
	virtual void setParent(UD* parent) {};

	virtual void translate(glm::vec3 translation) {
		pos += translation;
	}


	virtual void addChild(UD* child) {
		this->children.push_back(child);
		child->setParent(this);
	}
	virtual void addTag(std::string s) {
		tags.push_back(s);
	}

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual glm::vec3 getPos() { return pos; };
	virtual void Collide(Collision) {};
	
	virtual std::map<std::string, float>& getStats() { return this->stats; }
	virtual void drawText() {};
	

};
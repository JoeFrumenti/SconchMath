#pragma once
#include "Shaders/shader.h"
#include <GLFW/glfw3.h>
#include <vector>

#include "Collision.h"

class UD {
protected:
	int ID;
	glm::vec3 lastPos;
	glm::vec3 pos;
	std::vector<std::string> tags;
	float width;
	float height;

public:
	//UD();
	virtual int getId() { return ID; };
	virtual void setId(int id) { ID = id; };
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual glm::vec3 getPos() = 0;
	virtual void Collide(Collision) {};
	virtual float getWidth() { return this->width; }
	virtual float getHeight() { return this->height; }
	virtual glm::vec3 getLastPos() { return this->lastPos; }
	virtual std::vector<std::string> getTags() { return this->tags; }

};
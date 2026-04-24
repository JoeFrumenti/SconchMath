#pragma once
#include "Shaders/shader.h"
#include <GLFW/glfw3.h>
class UD {
protected:
	int ID;
	glm::vec2 pos;

public:
	//UD();
	virtual int getId() { return ID; };
	virtual void setId(int id) { ID = id; };
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual glm::vec2 getPos() = 0;
	virtual void Collide() {};

};
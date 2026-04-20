#pragma once
#include "Shaders/shader.h"
#include <GLFW/glfw3.h>
class UD {
protected:
	int ID;

public:
	//UD();

	virtual void setId(int id) { ID = id; };
	virtual void Update() = 0;
	virtual void Draw(Shader* shader) = 0;
	
};
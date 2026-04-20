#pragma once
#include "Shaders/shader.h"
class UD {
public:
	//UD();
	virtual void Update() = 0;
	virtual void Draw(Shader* shader) = 0;
	
};
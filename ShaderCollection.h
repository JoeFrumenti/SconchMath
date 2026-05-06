#pragma once
#include "Shaders/shader.h"

#include <map>
#include <string>

class ShaderCollection {
private:
	std::map<std::string, Shader*> shaders;
	
public:
	static ShaderCollection& getInstance() {
		static ShaderCollection instance;
		return instance;
	}
	ShaderCollection();
	Shader* getShader(std::string s);
};
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "InputManager.h"
#include "BlockGrid.h"
#include "BasicModel.h"
#include "ModelCache.h"
#include "ShaderCollection.h"



class LevelBuilder:public UD {
private:
	Model* ourModel;
	Shader* shader;
	glm::mat4 model;
	BlockGrid* grid;

	glm::vec2 index;
	glm::vec2 origin;
	glm::vec2 dimensions = glm::vec2(13,14);
	char type = 'R';

public:
	LevelBuilder();
	void buildLevel(const std::string& filename);
	void Update() override;
	void Draw()override;


};
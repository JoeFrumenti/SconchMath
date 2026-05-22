#pragma once

#include <iostream>
#include <iomanip>

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
	glm::vec2 dimensions;

public:
	LevelBuilder();
	void buildLevel();
	void Update() override;
	void Draw()override;


};
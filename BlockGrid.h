#pragma once
#include "UD.h"
#include <vector>

class Block;

class BlockGrid :public UD {
private: 
	std::vector<std::vector<Block*>> grid;

	float blockSize = 0.5f;
	glm::vec2 origin = glm::vec2(-6, 9);
	glm::vec2 dimensions;
public:
	BlockGrid(int m, int n);
	void setBlock(int i, int j, Block* b);
	Block* getBlock(int i, int j);

	void removeBlock(int m, int n);

	void initializeGrid();

	void Update() override;
	void Draw() override;

	bool isAbove(int m, int n);

	bool isBelow(int m, int n);

	bool isLeft(int m, int n);
	bool isRight(int m, int n);

	void setIron(int m, int n);
	void addBlock(int, int);

	float getBlockSize() { return blockSize; }
	glm::vec2 getOrigin() { return origin; }
	glm::vec2 getDimensions() { return dimensions; }

};

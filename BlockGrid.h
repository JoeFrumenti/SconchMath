#pragma once
#include "Block.h"
#include <vector>

class BlockGrid :public UD {
private: 
	std::vector<std::vector<Block*>> grid;
public:
	BlockGrid(int, int);
	void setBlock(int, int, Block*);
	Block* getBlock(int, int);

	void initializeGrid();

	void Update() override;
	void Draw() override;
};

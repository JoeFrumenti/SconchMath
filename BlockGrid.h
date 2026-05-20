#pragma once
#include "UD.h"
#include <vector>

class Block;

class BlockGrid :public UD {
private: 
	std::vector<std::vector<Block*>> grid;
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
};

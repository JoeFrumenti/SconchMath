#include "BlockGrid.h"
#include "Block.h"

BlockGrid::BlockGrid(int m, int n) {
    blockSize = 0.4f;

    grid.resize(m, std::vector<Block*>(n, nullptr));  // size the grid first

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            Block* block = new Block(this);

            block->translate(glm::vec3((float)i * (blockSize * 2.0f) - 6.0f, -(float)j * (blockSize * 2.0f) + 9.0f, 0.0f));
            block->setScale(glm::vec3(blockSize));
            UDManager::getInstance().addUD(block);
            grid[i][j] = block;
            block->setCell(i, j);
        }
    }
}

void BlockGrid::addBlock(int i, int j) {
    Block* block = new Block(this);
    block->translate(glm::vec3(i - 6.0f, -j + 9.0f, 0.0f));
}

void BlockGrid::removeBlock(int m, int n) {
    UDManager::getInstance().removeObject(grid[m][n]->getId());
    CollisionManager::getInstance().removeObject(grid[m][n]->getId());
    grid[m][n] = nullptr;
}

void BlockGrid::setBlock(int m, int n, Block* block) {
    grid[m][n] = block;
}

void BlockGrid::Update() {

}

void BlockGrid::setIron(int m, int n) {
    grid[m][n]->setIron();
}

bool BlockGrid::isAbove(int m, int n) {
    if (n == 0)
        return false;
    else
        return (grid[m][n - 1] != nullptr);
}

bool BlockGrid::isBelow(int m, int n) {
    if (n + 1 >= (int)grid[m].size())
        return false;
    else
        return (grid[m][n + 1] != nullptr);
}

bool BlockGrid::isLeft(int m, int n) {
    if (m - 1 < 0)
        return false;
    return (grid[m - 1][n] != nullptr);
}

bool BlockGrid::isRight(int m, int n) {
    if (m + 1 >= (int)grid.size())
        return false;
    return (grid[m + 1][n] != nullptr);
}
void BlockGrid::Draw() {

}
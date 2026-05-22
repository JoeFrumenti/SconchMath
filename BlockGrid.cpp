#include "BlockGrid.h"
#include "Block.h"


BlockGrid::BlockGrid(int m, int n) {

    grid.resize(m, std::vector<Block*>(n, nullptr));  

}

void BlockGrid::addBlock(int i, int j) {
    Block* block = new Block(this);
    block->translate(glm::vec3(i * blockSize * 2 + origin.x, -j * blockSize * 2 + origin.y, 0.0f));
    UDManager::getInstance().addUD(block);
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
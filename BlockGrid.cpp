#include "BlockGrid.h"

BlockGrid::BlockGrid(int m, int n) {
    for (float i = 0.0f; i <= 5.0f; i += 1.0f) {
        for (int j = -4; j <= 9; j++) {

            Block* block = new Block();
            block->translate(glm::vec3(i + 1, j + 2, 0.0f));
            UDManager::getInstance().addUD(block);

            Block* block2 = new Block();
            block2->translate(glm::vec3(-i - 1, j + 2, 0.0f));
            UDManager::getInstance().addUD(block2);

        }
    }

    /*for (float i = 0.0f; i <= 3.0f; i += 1.0f) {
        for (int j = -2; j <= 2; j++) {
            Block* block = new Block();
            block->translate(glm::vec3(i + 3, j, 0.0f));
            UDMan.addUD(block);

            Block* block2 = new Block();
            block2->translate(glm::vec3(-i - 3, j, 0.0f));
            UDMan.addUD(block2);
        }
    }*/

}

void BlockGrid::Update() {

}

void BlockGrid::Draw() {

}
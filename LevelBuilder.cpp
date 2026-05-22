#include "LevelBuilder.h"

LevelBuilder::LevelBuilder() {
    UDManager::getInstance().addUD(this);
    ourModel = ModelCache::getInstance().getModel("block");
}

void LevelBuilder::buildLevel() {
    BlockGrid* grid = new BlockGrid(13, 14);
    for (int i = 0; i < 13; i++)
        grid->setIron(i, 13);

    for (int i = 0; i < 14; i++) {
        grid->removeBlock(6, i);
        grid->setIron(5, i);
        grid->setIron(7, i);
    }
}

void LevelBuilder::Update() {
    int key = InputManager::getInstance().getPressedKey();
    if (key == GLFW_KEY_P)
        std::cout << "P pressed\n";
}

void LevelBuilder::Draw() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, 3.141590f, glm::vec3(0, 1, 0));
    model = glm::scale(model, scale);


    ourModel->Draw(*ShaderCollection::getInstance().getShader("Model"));
}



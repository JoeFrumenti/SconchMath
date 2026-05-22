#include "LevelBuilder.h"

LevelBuilder::LevelBuilder() {
    grid = new BlockGrid(13, 14);

    shader = ShaderCollection::getInstance().getShader("Model");
    UDManager::getInstance().addUD(this);
    ourModel = ModelCache::getInstance().getModel("block");

    scale = glm::vec3(grid->getBlockSize());
}

void LevelBuilder::buildLevel() {
    grid->addBlock(0, 0);
    grid->addBlock(1, 3);
}

void LevelBuilder::Update() {
    int key = InputManager::getInstance().getPressedKey();
    if (key == GLFW_KEY_P)
        std::cout << "P pressed\n";
    else if (key == GLFW_KEY_RIGHT)
        pos.x += grid->getBlockSize() * 2;
    else if (key == GLFW_KEY_LEFT)
        pos.x -= grid->getBlockSize() * 2;
    else if (key == GLFW_KEY_UP)
        pos.y += grid->getBlockSize() * 2;
    else if (key == GLFW_KEY_DOWN)
        pos.y -= grid->getBlockSize() * 2;
}

void LevelBuilder::Draw() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, 3.141590f, glm::vec3(0, 1, 0));
    model = glm::scale(model, scale);

    shader->setMat4("model", model);
    shader->setVec4("color", glm::vec4(1));
    ourModel->Draw(*shader);
}



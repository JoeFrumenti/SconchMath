#include "LevelBuilder.h"

LevelBuilder::LevelBuilder() {
    grid = new BlockGrid(13, 14);

    shader = ShaderCollection::getInstance().getShader("Model");
    UDManager::getInstance().addUD(this);
    ourModel = ModelCache::getInstance().getModel("block");

    scale = glm::vec3(grid->getBlockSize());
    dimensions = grid->getDimensions();
    origin = grid->getOrigin();

    pos = glm::vec3(origin.x,origin.y, 0);
}

void LevelBuilder::buildLevel(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); int x = std::stoi(token);
        std::getline(ss, token, ','); int y = std::stoi(token);
        std::getline(ss, token, ','); char type = token[0];

        grid->addBlock(x, y);
        if (type == 'I')
            grid->setIron(x, y);
    }
}

void LevelBuilder::Update() {
    int key = InputManager::getInstance().getPressedKey();
    if (key == GLFW_KEY_P) {

        std::cout << "P pressed\n";
        std::ofstream file("C:/Users/joefr/source/repos/SconchMath/assets/Levels/TestLevel.txt", std::ios::app);  // append mode
        file << index.x << "," << index.y << "," << "R" << "\n";
        grid->addBlock(index.x, index.y);
    }
    else if (key == GLFW_KEY_RIGHT && index.x <dimensions.x - 1) {
        pos.x += grid->getBlockSize() * 2;
        index.x++;
    }
    else if (key == GLFW_KEY_LEFT && index.x > 0) {
        pos.x -= grid->getBlockSize() * 2;
        index.x--;
    }
    else if (key == GLFW_KEY_UP && index.y > 0) {
        pos.y += grid->getBlockSize() * 2;
        index.y--;
    }
    else if (key == GLFW_KEY_DOWN && index.y < dimensions.y - 1) {
        pos.y -= grid->getBlockSize() * 2;
        index.y++;
    }
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



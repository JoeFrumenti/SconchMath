#include "Block.h"

Block::Block(BlockGrid* blockGrid) {
    velocity = glm::vec3(-0.25f, -0.35f, 0.0f);
    grid = blockGrid;
    CollisionManager& cm = CollisionManager::getInstance();
    ourModel = new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/brickBlock.obj");
    shader = ShaderCollection::getInstance().getShader("Model");

    width = .5f;
    height = .5f;

    scale = glm::vec3(width);
    cm.addObject(this);
}

void Block::Update() {

}

void Block::Draw() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, 0.0f, glm::vec3(1));
    model = glm::scale(model, scale);
    shader->use();
    shader->setMat4("model", model);
    shader->setVec4("color", color);
    ourModel->Draw(*shader);

    
}

float randomFloat(float min, float max) {

    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);

}

void Block::spawnCube() {
    BouncingCube* cube = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
    cube->setScale(glm::vec3(0.2f));
    cube->addTag("bcube");
    cube->translate(glm::vec3(0,-3,0));
    cube->setVelocity(glm::normalize(glm::vec3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), 0.0f)) * glm::vec3(0.2f));
    cube->setRotationOffset(randomFloat(-1.0f, 1.0f));

    UDManager::getInstance().addUD(cube);
}


void Block::Collide(Collision col) {
	for (auto& tag : col.obj->getTags()) {
        if(tag == "bcube")
        {
        SoundManager::getInstance().playSong("bounce");
            BouncingCube* cube = dynamic_cast<BouncingCube*>(col.obj);
            if (!cube->getCollided()) {
                cube->setCollided(true);
                UD* ball = col.obj;
                glm::vec3 ballPos = ball->getPos();

                if (ballPos.x < pos.x - width || ballPos.x > pos.x + width) {
                    ball->setVelocity(ball->getVelocity() * glm::vec3(-1, 1, 1));
                }
                if (ballPos.y > pos.y + height || ballPos.y < pos.y - height) {
                    ball->setVelocity(ball->getVelocity() * glm::vec3(1, -1, 1));
                }

                ball->translate(ball->getVelocity());

                if (--hp >= 0) {
                    color -= glm::vec4(.3f, .3f, .3f, .0f);

                }
                else {
                    UDManager::getInstance().queueRemoval(ID);
                    CollisionManager::getInstance().removeObject(ID);
                    spawnCube();
                }
            }
        }
	}
}

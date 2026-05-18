#include "Block.h"

Block::Block() {
    velocity = glm::vec3(-0.25f, -0.35f, 0.0f);

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

void spawnCube() {
    BouncingCube* cube = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
    cube->setScale(glm::vec3(0.4f));
    cube->addTag("bcube");
    cube->setVelocity(glm::normalize(glm::vec3(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 0.0f), 0.0f)) * glm::vec3(0.25f));
    cube->setRotationOffset(randomFloat(-1.0f, 1.0f));

    UDManager::getInstance().addUD(cube);
}


void Block::Collide(Collision col) {
	for (auto& tag : col.obj->getTags()) {
        if(tag == "bcube")
        {
            float blockLeft = pos.x - width / 2.0f;
            float blockRight = pos.x + width / 2.0f;
            float blockTop = pos.y - height / 2.0f;
            float blockBottom = pos.y + height / 2.0f;

            UD* ball = col.obj;

            float overlapLeft = ball->getPos().x - blockLeft;
            float overlapRight = blockRight - ball->getPos().x;
            float overlapTop = ball->getPos().y - blockTop;
            float overlapBottom = blockBottom - ball->getPos().y;

            float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

            if (minOverlap == overlapLeft || minOverlap == overlapRight) {
                ball->setVelocity(glm::vec3(ball->getVelocity() * glm::vec3(-1, 1, 1)));
            }
            else {
                ball->setVelocity(glm::vec3(ball->getVelocity() * glm::vec3(1, -1, 1)));
            }


            if (--hp >= 0) {
                color -= glm::vec4(.3f, .3f, .3f,.0f);
                
            }
            else {
                UDManager::getInstance().queueRemoval(ID);
                CollisionManager::getInstance().removeObject(ID);
                spawnCube();
            }

        }
	}
}

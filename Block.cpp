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
    ourModel->Draw(*shader);

    
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
        }
	}
}

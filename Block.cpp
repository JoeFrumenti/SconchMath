#include "Block.h"
#include "InputManager.h"
static std::mt19937 rng(std::random_device{}());
static std::uniform_int_distribution<int> dist(0, 4);

Block::Block(BlockGrid* blockGrid) {
    velocity = glm::vec3(-0.25f, -0.35f, 0.0f);
    grid = blockGrid;
    CollisionManager& cm = CollisionManager::getInstance();
    ourModel = ModelCache::getInstance().getModel("block");
    shader = ShaderCollection::getInstance().getShader("Model");
    shader->use();
    pos = glm::vec3(0);
    width = .5f;
    height = .5f;

    scale = glm::vec3(width);
    cm.addObject(this);

    grid = blockGrid;
}

void Block::Update() {
    if (InputManager::getInstance().isE())
        spawnCube();
}

void Block::Draw() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, 3.141590f, glm::vec3(0,1,0));
    model = glm::scale(model, scale);
    
    shader->setMat4("model", model);
    shader->setVec4("color", color);
    ourModel->Draw(*shader);

    
}


void Block::setIron() {
    hp = -1;
    ourModel = ModelCache::getInstance().getModel("iron");
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
    cube->translate(glm::vec3(0,-4,0));
    cube->setVelocity(glm::normalize(glm::vec3(randomFloat(-1.0f, 1.0f), randomFloat(.0f, 1.0f), 0.0f)) * glm::vec3(0.2f));
    cube->setRotationOffset(randomFloat(-1.0f, 1.0f));

    UDManager::getInstance().addUD(cube);
}





bool Block::isCollide(glm::vec3 ballPos, float w, float h) {
    bool overlapX = std::abs(pos.x - ballPos.x) < (width + w);
    bool overlapY = std::abs(pos.y - ballPos.y) < (height + h);
    return (overlapX && overlapY);
}

glm::vec3 Block::getCollisionPoint(BouncingCube* ball) {
    glm::vec3 safePos = ball->getPos() - ball->getVelocity(); // last frame's position
    glm::vec3 unsafePos = ball->getPos();

    for (int i = 0; i < 10; i++) { 
        glm::vec3 mid = (safePos + unsafePos) / 2.0f;
        if (isCollide(mid, ball->getWidth(), ball->getHeight())) {
            unsafePos = mid;
        }
        else {
            safePos = mid;
        }
    }


    
    ball->setPos(safePos);
    return safePos;
}

glm::vec3 Block::getBounceDirection(BouncingCube* ball) {
    glm::vec3 safePos = getCollisionPoint(ball);
    glm::vec3 velTranslate = glm::vec3(1);
    glm::vec3 ballVel = ball->getVelocity();



    if ((pos.x + width > safePos.x - ball->getWidth()) && (pos.x - width < safePos.x + ball->getWidth())) {
        if (safePos.y > pos.y && !grid->isAbove(cell.x, cell.y)) {
            velTranslate.y = -1;
        }
        if (safePos.y < pos.y && !grid->isBelow(cell.x, cell.y)) {
            velTranslate.y = -1;
        }
        
    }

    if ((pos.y + height > safePos.y - ball->getHeight()) && (pos.y - height < safePos.y + ball->getHeight())) {
        if (safePos.x > pos.x && !grid->isRight(cell.x, cell.y)) {
            velTranslate.x = -1;
        }
        if (safePos.x < pos.x && !grid->isLeft(cell.x, cell.y)) {
            velTranslate.x = -1;
        }
    }


    return velTranslate;


}


void Block::Collide(Collision col) {
    for (auto& tag : col.obj->getTags()) {
        if (tag == "bcube")
        {
            SoundManager::getInstance().playSong("bounce");
            BouncingCube* cube = dynamic_cast<BouncingCube*>(col.obj);

            cube->setVelocity(cube->getVelocity() * getBounceDirection(cube));

                

                if (--hp >= 0) {
                    color -= glm::vec4(.5f, .5f, .5f, .0f);

                }
                else if (hp == -1) {
                    grid->removeBlock(cell.x, cell.y);
                    if (!grid->getSpawned()) {
                        grid->setSpawned(true);
                        Powerup* pUp = new Powerup(1);
                        pUp->translate(pos);
                    }
                    else {
                        static std::mt19937 rng(
                            std::chrono::steady_clock::now().time_since_epoch().count()
                        );
                        static std::uniform_int_distribution<int> dist(0, 2);

                        if ((dist(rng) == 0)  && BallContainer::getInstance().getBallSize() <= 300  && grid->getDoubles() < 8){
                            Powerup* pUp = new Powerup(1);
                            pUp->translate(pos + glm::vec3(0,0,1));
                            grid->addDouble();
                        }
                        
                    }


                }
            }
        }
    }



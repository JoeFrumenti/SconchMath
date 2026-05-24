#include "Block.h"
#include "InputManager.h"
Block::Block(BlockGrid* blockGrid) {
    velocity = glm::vec3(-0.25f, -0.35f, 0.0f);
    grid = blockGrid;
    CollisionManager& cm = CollisionManager::getInstance();
    ourModel = ModelCache::getInstance().getModel("block");
    shader = ShaderCollection::getInstance().getShader("Model");
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
    shader->use();
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

glm::vec3 Block::getBounceDirection(glm::vec3 colPoint, float w, float h, glm::vec3 velocity) {
    float overlapX = (width + w) - std::abs(colPoint.x - pos.x);
    float overlapY = (height + h) - std::abs(colPoint.y - pos.y);

    bool blockedX = (velocity.x > 0 && grid->isRight(cell.x, cell.y)) ||
        (velocity.x < 0 && grid->isLeft(cell.x, cell.y));

    bool blockedY = (velocity.y > 0 && grid->isAbove(cell.x, cell.y)) ||
        (velocity.y < 0 && grid->isBelow(cell.x, cell.y));

    // use velocity magnitude to weight which axis is more "perpendicular"
    float absVx = std::abs(velocity.x);
    float absVy = std::abs(velocity.y);

    bool bounceX, bounceY;

    if (absVy > absVx) {
        // moving more vertically  primary hit is top/bottom face
        bounceY = !blockedY;
        bounceX = (overlapX < overlapY) && !blockedX;
    }
    else if (absVx > absVy) {
        // moving more horizontally  primary hit is left/right face
        bounceX = !blockedX;
        bounceY = (overlapY < overlapX) && !blockedY;
    }
    else {
        // diagonal, fall back to overlap
        bounceX = (overlapX < overlapY) && !blockedX;
        bounceY = (overlapY < overlapX) && !blockedY;
    }

    return glm::vec3(
        bounceX ? -1 : 1,
        bounceY ? -1 : 1,
        1
    );
}


void Block::Collide(Collision col) {
    for (auto& tag : col.obj->getTags()) {
        if (tag == "bcube")
        {
            SoundManager::getInstance().playSong("bounce");
            BouncingCube* cube = dynamic_cast<BouncingCube*>(col.obj);

            float overlapX = (cube->getWidth() + width) - std::abs(cube->getPos().x - pos.x);
            float overlapY = (cube->getHeight() + height) - std::abs(cube->getPos().y - pos.y);

            glm::vec3 cubePos = cube->getPos();
            glm::vec3 cubeVel = cube->getVelocity();
            

            if (overlapX < overlapY)
            {
                // Shallower penetration on X — hit a left or right face
                float newVelX = cube->getVelocity().x;
                float depenetration = 0;
                

                if ((cubePos.x < pos.x) && !grid->isLeft(cell.x,cell.y))
                {
                    newVelX = -std::abs(cubeVel.x);  // push left
                    depenetration = -overlapX;
                }
                else if(!grid->isRight(cell.x,cell.y))
                {
                    newVelX = std::abs(cubeVel.x);   // push right
                    depenetration = overlapX;
                }

                cube->setVelocity(glm::vec3(newVelX, cubeVel.y, 0));
                cube->setPos(glm::vec3(cubePos.x + depenetration, cubePos.y, 0));
            }
            else
            {
                // Shallower penetration on Y — hit a top or bottom face
                float newVelY = cube->getVelocity().y;
                float depenetration = 0;

                if ((cubePos.y < pos.y) && !grid->isBelow(cell.x, cell.y))
                {
                    newVelY = -std::abs(cubeVel.y);  // push down
                    depenetration = -overlapY;
                }
                else if(!grid->isAbove(cell.x,cell.y))
                {
                    newVelY = std::abs(cubeVel.y);   // push up
                    depenetration = overlapY;
                }

                cube->setVelocity(glm::vec3(cubeVel.x, newVelY, 0));
                cube->setPos(glm::vec3(cubePos.x, cubePos.y + depenetration, 0));
            }
                
                

                if (--hp >= 0) {
                    color -= glm::vec4(.3f, .3f, .3f, .0f);

                }
                else if (hp == -1) {
                    grid->removeBlock(cell.x, cell.y);
                    Powerup* pUp = new Powerup(1);
                    pUp->translate(pos);

                }
            }
        }
    }



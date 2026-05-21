#include "Block.h"
#include "InputManager.h"
Block::Block(BlockGrid* blockGrid) {
    velocity = glm::vec3(-0.25f, -0.35f, 0.0f);
    grid = blockGrid;
    CollisionManager& cm = CollisionManager::getInstance();
    ourModel = ModelCache::getInstance().getModel("block");
    shader = ShaderCollection::getInstance().getShader("Model");

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

                if ((ballPos.x < pos.x - width * 0.9 && !grid->isLeft(cell.x,cell.y))
                    || (ballPos.x > pos.x + width * 0.9 && !grid->isRight(cell.x,cell.y))) {
                    ball->setVelocity(ball->getVelocity() * glm::vec3(-1, 1, 1));
                }
                else if ((ballPos.y > pos.y + height * 0.9 && !grid->isAbove(cell.x,cell.y)) 
                    || (ballPos.y < pos.y - height * 0.9 && !grid->isBelow(cell.x,cell.y))) {
                    ball->setVelocity(ball->getVelocity() * glm::vec3(1, -1, 1));
                }
                else
                    ball->setVelocity(ball->getVelocity() * glm::vec3(-1, -1, 1));

                ball->translate(ball->getVelocity());

                if (--hp >= 0) {
                    color -= glm::vec4(.3f, .3f, .3f, .0f);

                }
                else if (hp == -1) {
                    grid->removeBlock(cell.x, cell.y);
                    cube->spawnClone();
                }
                
            }
        }
	}
}

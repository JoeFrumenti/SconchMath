#include "SceneLoader.h"

void SceneLoader::loadChaos() {
    ModelCache::getInstance().addModel("cube", new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj"));
    ModelCache::getInstance().addModel("block", new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/brickBlock.obj"));
    ModelCache::getInstance().addModel("iron", new Model("C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj"));

    PrefabLoader prefabLoader = PrefabLoader();
    UDManager& UDMan = UDManager::getInstance();
    BouncingCube* cube = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
    cube->setScale(glm::vec3(0.2f));
    cube->translate(glm::vec3(0, -4, 0));
    cube->setVelocity(glm::vec3(0.1f, -0.25f, 0.0f));
    cube->addTag("bcube");
 

    UDMan.addUD(cube);



    BasicModel* bg = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundPB.obj");
    bg->translate(glm::vec3(0.0f, -10.0f, -3.0f));
    bg->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));
    UDMan.addUD(bg);

    BasicModel* powerup = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/powerup.obj");
    powerup->translate(glm::vec3(0.0f, 0.0f, .0f));
    powerup->rotate(3.14159265358979f/2, glm::vec3(1.0f, .0f, .0f));
    UDMan.addUD(powerup);

    LevelBuilder* levelBuilder = new LevelBuilder();
    levelBuilder->buildLevel("C:/Users/joefr/source/repos/SconchMath/assets/Levels/TestLevel.txt");


    using namespace std;

   


    Paddle* paddle = new Paddle();
    paddle->translate(glm::vec3(0, -10, 0));
    UDMan.addUD(paddle);


}

void SceneLoader::loadFightScene() {
    //GameObject setup & config
   

    PrefabLoader prefabLoader = PrefabLoader();

    UDManager& UDMan = UDManager::getInstance();


    BouncingCube* cube1 = prefabLoader.loadIce();
    UDMan.addUD(cube1);

    BouncingCube* cube2 = prefabLoader.loadThief();
    UDMan.addUD(cube2);

    BasicModel* bg = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundPB.obj");
    BasicModel* foreground = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundBW.obj");

    foreground->translate(glm::vec3(0.025f, 1.2f, -1.0f));
    foreground->rotate(3.14159265358979 / 2, glm::vec3(.0f, 1.0f, 0.0f));
    foreground->scale(glm::vec3(4.54999f, 4.81, 4.54999f));
    UDMan.addUD(foreground);

    bg->translate(glm::vec3(0.0f, -10.0f, -3.0f));

    bg->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));

    UDMan.addUD(bg);


    GameManager& gameMan = GameManager::getInstance();
   

    UDMan.addUD(&gameMan);


    cube1->setVelocity(glm::vec3(0.10f, -0.21f, .0f));
    cube2->setVelocity(glm::vec3(-0.23f, 0.08f, .0f));

    //SPAWN COINS
    int idNum = 10000;
    for (float i = -5.5f; i <= 5.5f; i += 1.2) {
        for (float j = -5.0f; j <= 7.5f; j += 1.35f) {
            Coin* coiny = new Coin();
            coiny->translate(glm::vec3(i, j, 0));
            UDMan.addUD(coiny);
        }
    }
}
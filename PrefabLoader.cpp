#include "PrefabLoader.h"

BouncingCube* PrefabLoader::loadSlime() {
    BouncingCube* cube1 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
    cube1->translate(glm::vec3(5.0f, .0f, 0.0f));
    cube1->addTag("bcube");

    Player1* p1 = new Player1();
    CoinPickup* coinPickup = new CoinPickup();
    SlimeBall* slimeBall = new SlimeBall();

    cube1->addChild(coinPickup);
    cube1->addChild(p1);
    Launcher* slimeLauncher = new Launcher(slimeBall);
    cube1->addChild(slimeLauncher);
    return cube1;
}

BouncingCube* PrefabLoader::loadIce() {
    BouncingCube* cube2 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere2.obj");
    cube2->translate(glm::vec3(-5.0f, .0f, 0.0f));
    cube2->addTag("bcube");

    Player2* p2 = new Player2();
    CoinPickup* coinPickup2 = new CoinPickup();
    Icey* icey = new Icey();
    cube2->addChild(p2);
    cube2->addChild(coinPickup2);
    cube2->addChild(icey);
    return cube2;
}

BouncingCube* PrefabLoader::loadMoneyBag() {
    BouncingCube* moneyBag = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/StarCube.obj");
    moneyBag->translate(glm::vec3(.0f, 5.0f, 0.0f));
    moneyBag->setVelocity(glm::vec3(-0.45f, 0.16f, .0f));
    DropCoins* dropCoins = new DropCoins();
    moneyBag->addChild(dropCoins);
    return moneyBag;
}
DebugCube* PrefabLoader::loadDebugCube() {
    DebugCube* dc = new DebugCube();
    dc->setId(9);
    dc->setScale(glm::vec3(0.1, .1, .1));
    return dc;
}
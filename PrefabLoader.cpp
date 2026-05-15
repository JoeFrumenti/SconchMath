#include "PrefabLoader.h"

BouncingCube* PrefabLoader::loadSlime() {
    BouncingCube* cube1 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/slimeball.obj");
    
    cube1->addTag("bcube");
    cube1->getStats().statColor = glm::vec3(.0f, .45f, .0f);

    Player2* p2 = new Player2();
    CoinPickup* coinPickup = new CoinPickup();

    cube1->addChild(coinPickup);
    cube1->addChild(p2);

    Launcher* slimeLauncher = Launcher::Create<SlimeBall>();
    UDManager::getInstance().addUD(slimeLauncher);
    cube1->addChild(slimeLauncher);
    slimeLauncher->setParent(cube1);

    cube1->getStats().name = "SLIME";
    cube1->getStats().winSound = "slimewins";
    cube1->getStats().statMsg = "Slime time: ";
    return cube1;
}

BouncingCube* PrefabLoader::loadThief() {
    BouncingCube* cube1 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/Thief.obj");
    cube1->getStats().statColor = glm::vec3(255.0f, 255.0f, 0.0f);
    cube1->addTag("bcube");

    Player1* p1 = new Player1();
    CoinPickup* coinPickup = new CoinPickup();

    cube1->addChild(coinPickup);
    cube1->addChild(p1);

    Launcher* thiefLauncher = Launcher::Create<Thief>();
    UDManager::getInstance().addUD(thiefLauncher);
    cube1->addChild(thiefLauncher);
    thiefLauncher->setParent(cube1);
    thiefLauncher->setLaunchRate(1.3f);

    cube1->getStats().name = "THIEF";
    cube1->getStats().winSound = "thiefwins";
    cube1->getStats().statMsg = "Coinsteal: ";
    return cube1;
}

BouncingCube* PrefabLoader::loadIce() {

    BouncingCube* cube2 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere2.obj");
    
    cube2->addTag("bcube");

    Player2* p2 = new Player2();
    CoinPickup* coinPickup2 = new CoinPickup();
    Icey* icey = new Icey();
    icey->setParent(cube2);
    cube2->addChild(p2);
    cube2->addChild(coinPickup2);
    cube2->addChild(icey);

    cube2->getStats().name = "ICE";
    cube2->getStats().winSound = "icewins";
    cube2->getStats().statMsg = "Freeze time: ";

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
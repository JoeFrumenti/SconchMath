#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <thread>

#include "ShaderCollection.h"

#include <camera.cpp>
#include "CollisionManager.h"

#include "Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "coin.h"
#include "BouncingCube.h"
#include "BasicModel.h"
#include "DebugCube.h"
#include "Player1.h"
#include "Player2.h"
#include "CoinPickup.h"
#include "DropCoins.h"
#include "PlayerManager.h"
#include "Icey.cpp"
#include "Launcher.h"
#include "SlimeBall.cpp"

#include "MyTimer.h"
#include "Window.h"


bool start = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


const unsigned int SCR_WIDTH = 450;
const unsigned int SCR_HEIGHT = 800;

Window& window = Window::getInstance();

void init();

auto& UDMan = UDManager::getInstance();

CollisionManager& cm = CollisionManager::getInstance();

const double TARGET_FPS = 60.0;
const std::chrono::duration<double> FRAME_DURATION(1.0 / TARGET_FPS);

int started = 0;
BouncingCube* cube1;
BouncingCube* cube2;


void renderLoop() {

    while (!glfwWindowShouldClose(window.get()))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        if (started == 1) {

            
            started = 2;
        }

        processInput(window.get());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if (start) {
            
            UDMan.updateUDs();
            cm.checkCollision2D();
            UDMan.drawUDs();
            UDMan.drawText();

        }

        glfwSwapBuffers(window.get());
        glfwPollEvents();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = frameEnd - frameStart;

        if (elapsed < FRAME_DURATION) {
            std::this_thread::sleep_for(FRAME_DURATION - elapsed);
        }
    }
}

void init() {
    cube1->setVelocity(glm::vec3(0.10f, -0.21f, .0f));
    cube2->setVelocity(glm::vec3(-0.23f, 0.08f, .0f));
    start = true;
    SoundManager::getInstance().playImportantSound("announce");
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !start) {
        
        init();
    }

    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void setupWindow() {

    //Game setup
    MyTimer* timer = &MyTimer::getInstance();
    UDMan.addUD(timer);

    //camera setup
    camera* cam = new camera(SCR_WIDTH, SCR_HEIGHT);
    cam->setup();

}

void addGameObjects() {
    //GameObject setup & config
    /*DebugCube* dc = new DebugCube();
    dc->setId(9);
    dc->setScale(glm::vec3(0.1, .1, .1));
    UDMan.addUD(dc);*/


    cube1 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
    cube1->translate(glm::vec3(5.0f, .0f, 0.0f));
    cube1->addTag("bcube");

    Player1* p1 = new Player1();
    CoinPickup* coinPickup = new CoinPickup();
    SlimeBall* slimeBall = new SlimeBall();

    cube1->addChild(coinPickup);
    cube1->addChild(p1);
    UDMan.addUD(cube1);



    cube2 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere2.obj");
    cube2->translate(glm::vec3(-5.0f, .0f, 0.0f));
    cube2->addTag("bcube");

    Player2* p2 = new Player2();
    CoinPickup* coinPickup2 = new CoinPickup();
    Icey* icey = new Icey();
    cube2->addChild(p2);
    cube2->addChild(coinPickup2);
    cube2->addChild(icey);
    UDMan.addUD(cube2);


    /* BouncingCube* moneyBag = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/StarCube.obj");
     moneyBag->translate(glm::vec3(.0f, 5.0f, 0.0f));
     moneyBag->setVelocity(glm::vec3(-0.45f, 0.16f, .0f));
     DropCoins* dropCoins = new DropCoins();
     moneyBag->addChild(dropCoins);*/




     //    UDMan.addUD(moneyBag);


    BasicModel* bg = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundPB.obj");
    BasicModel* foreground = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundBW.obj");



    //foreground->setInput(true);
    foreground->translate(glm::vec3(0.025f, 1.2f, -1.0f));
    foreground->rotate(3.14159265358979 / 2, glm::vec3(.0f, 1.0f, 0.0f));
    foreground->scale(glm::vec3(4.54999f, 4.81, 4.54999f));
    UDMan.addUD(foreground);

    bg->translate(glm::vec3(0.0f, -10.0f, -3.0f));

    bg->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));

    UDMan.addUD(bg);


    PlayerManager* playerMan = new PlayerManager(cube1, cube2);
    UDMan.addUD(playerMan);


    Launcher* slimeLauncher = new Launcher(slimeBall, playerMan);
    cube1->addChild(slimeLauncher);



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

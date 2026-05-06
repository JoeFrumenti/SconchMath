#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <thread>

#include "ShaderCollection.h"

#include <camera.cpp>
#include "CollisionManager.h"
#include "ObjectManager.h"

#include "Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "coin.h"
#include "BouncingCube.h"
#include "BasicModel.h"
#include "DebugCube.cpp"
#include "Player1.cpp"
#include "Player2.cpp"
#include "CoinPickup.cpp"
#include "DropCoins.cpp"
#include "PlayerManager.h"

#include "Window.h"

bool start = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

Shader* modelShader;
Shader* textShader;

// settings
const unsigned int SCR_WIDTH = 450;
const unsigned int SCR_HEIGHT = 800;

Window& window = Window::getInstance();


auto& UDMan = UDManager::getInstance();

CollisionManager& cm = CollisionManager::getInstance();

const double TARGET_FPS = 60.0;
const std::chrono::duration<double> FRAME_DURATION(1.0 / TARGET_FPS); 

void renderLoop();

int main()
{
    
    //window setup
    window.initWindow();
    modelShader = ShaderCollection::getInstance().getShader("Model");
    textShader = ShaderCollection::getInstance().getShader("Model");


    BouncingCube* cube1 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj");
    cube1->setId(3);
    cube1->setVelocity(glm::vec3(0.19f, -0.42f, .0f));

    Player1* p1 = new Player1();
    CoinPickup* coinPickup = new CoinPickup();
    coinPickup->setId(8);
    cube1->addChild(coinPickup);
    cube1->addChild(p1);


    BouncingCube* cube2 = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube2.obj");
    cube2->setId(4);
    cube2->translate(glm::vec3(.0f, -5.0f,0.0f));
    cube2->setVelocity(glm::vec3(-0.45f, 0.16f, .0f));

    Player2* p2 = new Player2();
    CoinPickup* coinPickup2 = new CoinPickup();
    coinPickup2->setId(7);
    cube2->addChild(p2);
    cube2->addChild(coinPickup2);

    BouncingCube* moneyBag = new BouncingCube("C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj");
    moneyBag->setId(5);
    moneyBag->translate(glm::vec3(.0f, 5.0f, 0.0f));
    moneyBag->setVelocity(glm::vec3(-0.45f, 0.16f, .0f));
    DropCoins* dropCoins = new DropCoins(modelShader);
    moneyBag->addChild(dropCoins);

    UDMan.addUD(cube1);
    UDMan.addUD(cube2);
    UDMan.addUD(moneyBag);


    BasicModel* bg = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundPB.obj");
    BasicModel* foreground = new BasicModel("C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundCream.obj");

    DebugCube* dc = new DebugCube(modelShader);

    bg->setId(200);
    
    foreground->setId(201);

    bg->translate(glm::vec3(0.0f, -10.0f, -3.0f));
    foreground->translate(glm::vec3(0.625f, -8.0f, -1.0f));

    bg->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));
    foreground->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));

    foreground->scale(glm::vec3(.7425f, .6575f, .3f));

    UDMan.addUD(bg);
    UDMan.addUD(foreground);

    PlayerManager* playerMan = new PlayerManager(cube1, cube2);
    playerMan->setId(6);
    UDMan.addUD(playerMan);


    char path5[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube2.obj";

    //SPAWN COINS
    int idNum = 100;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Coin* coiny = new Coin(modelShader);
            coiny->setId(idNum++);
            coiny->translate(glm::vec3((float)i * 2.6f - 5.3, (float)j * 4.1f - 10.2f, 0.0f));
           UDMan.addUD(coiny);
        }
    }

    //camera setup
    camera* cam = new camera(modelShader, SCR_WIDTH, SCR_HEIGHT);
    cam->setup();
 

    modelShader->use();
    modelShader->setVec3("lightPos", glm::vec3(.0f, 11.0f, 10.0f));
    renderLoop();


    glfwTerminate();
    return 0;
}



void renderLoop() {

    while (!glfwWindowShouldClose(window.get()))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        processInput(window.get());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        modelShader->use();

        if (start) {
            cm.checkCollision2D();
            UDMan.updateUDs();
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

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        start = true;
        
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

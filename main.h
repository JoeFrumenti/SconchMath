#pragma once
#include <iostream>
#include <chrono>
#include <thread>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "camera.cpp"
#include "CollisionManager.h"
#include "SceneLoader.h"
#include "Window.h"

bool start = false;

void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 450;
const unsigned int SCR_HEIGHT = 800;

Window& window = Window::getInstance();

void init();

UDManager& UDMan = UDManager::getInstance();

CollisionManager& cm = CollisionManager::getInstance();

const double TARGET_FPS = 60.0;
const std::chrono::duration<double> FRAME_DURATION(1.0 / TARGET_FPS);

SceneLoader sceneLoader = SceneLoader();


void renderLoop() {

    while (!glfwWindowShouldClose(window.get()))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

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
    start = true;
    //SoundManager::getInstance().playImportantSound("announce");
    UDMan.addUD(&MyTimer::getInstance());
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !start) {
        init();
    }

    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void addGameObjects() {
    camera* cam = new camera(SCR_WIDTH, SCR_HEIGHT);
    sceneLoader.loadChaos();
}
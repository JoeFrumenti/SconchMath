#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <thread>

#include <Shaders/shader.h>

#include <camera.cpp>
#include "CollisionManager.h"
#include "ObjectManager.h"

#include "Model.h"
#include "InputManager.h"
#include "UDManager.h"

#include "coin.cpp"
#include "BouncingCube.cpp"
#include "Background.cpp"
#include "DebugCube.cpp"

#include <string>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* configGL();

Shader* ourShader;
Shader* modelShader;

int scale = 50;

// settings
const unsigned int SCR_WIDTH = 9 * scale;
const unsigned int SCR_HEIGHT = 16 * scale;

GLFWwindow* window;
auto& UDMan = UDManager::getInstance();

CollisionManager& cm = CollisionManager::getInstance();

bool start = true;

const double TARGET_FPS = 60.0;
const std::chrono::duration<double> FRAME_DURATION(1.0 / TARGET_FPS); // ~16.67ms


void renderLoop();

int main()
{
    

    window = configGL();
    modelShader = new Shader("C:/Users/joefr/source/repos/SconchMath/modelShader.vs", "C:/Users/joefr/source/repos/SconchMath/modelShader.fs");



    InputManager* input = new InputManager(window);

    DebugCube* debugCube = new DebugCube(modelShader, input);
    debugCube->setId(3);
    debugCube->setInput(true);

    DebugCube* dC2 = new DebugCube(modelShader, input);
    dC2->setId(4);
    dC2->translate(glm::vec3(3.0f, 5.0f,0.0f));

    BouncingCube* bCube = new BouncingCube(modelShader);

    UDMan.addUD(debugCube);
    UDMan.addUD(dC2);

    //UDMan.addUD(bCube);

    Background* bg = new Background(modelShader);
    bg->setId(1);
    //UDMan.addUD(bg);


    int idNum = 10;


    /*for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            Coin* coiny = new Coin(modelShader);
            coiny->setId(idNum++);
            coiny->translate(glm::vec3((float)i * 3.0f - 6, (float)j * 4.3f - 10.7f, 0.0f));
           UDMan.addUD(coiny);
        }
    }*/


    camera* cam = new camera(modelShader, SCR_WIDTH, SCR_HEIGHT);

    cam->setup();
    modelShader->use();
 

    renderLoop();

    


    glfwTerminate();
    return 0;
}

void renderLoop() {



    while (!glfwWindowShouldClose(window))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        //bg.render();

        cm.checkCollision2D();


        if (start) {

            UDMan.updateUDs();
            UDMan.drawUDs();

        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto elapsed = frameEnd - frameStart;

        if (elapsed < FRAME_DURATION) {
            std::this_thread::sleep_for(FRAME_DURATION - elapsed);
        }
    }
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        start = true;
        
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

GLFWwindow* configGL() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;   
    }
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return window;
}


#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <thread>

#include <Shaders/shader.h>

#include <camera.cpp>
#include "CollisionManager.h"
#include "ObjectManager.h"

#include "Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "coin.cpp"
#include "BouncingCube.cpp"
#include "BasicModel.cpp"
#include "DebugCube.cpp"

bool start = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* configGL();

Shader* modelShader;
Shader* textShader;

// settings
const unsigned int SCR_WIDTH = 450;
const unsigned int SCR_HEIGHT = 800;

GLFWwindow* window;
auto& UDMan = UDManager::getInstance();

CollisionManager& cm = CollisionManager::getInstance();

const double TARGET_FPS = 60.0;
const std::chrono::duration<double> FRAME_DURATION(1.0 / TARGET_FPS); // ~16.67ms

void renderLoop();

int main()
{
    
    //window setup
    window = configGL();
    modelShader = new Shader("C:/Users/joefr/source/repos/SconchMath/modelShader.vs", "C:/Users/joefr/source/repos/SconchMath/modelShader.fs");
    textShader = new Shader("C:/Users/joefr/source/repos/SconchMath/textShader.vs", "C:/Users/joefr/source/repos/SconchMath/textShader.fs");
    InputManager* input = new InputManager(window);

    //object setup
    char path1[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/DiamondSphere.obj";
    char path2[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube.obj";

    BouncingCube* cube1 = new BouncingCube(modelShader, path1, textShader,input);
    cube1->setId(3);
    cube1->setVelocity(glm::vec3(0.19f, -0.42f, .0f));
    cube1->setInput(true);

    BouncingCube* cube2 = new BouncingCube(modelShader, path2, textShader,input);
    cube2->setId(4);
    cube2->translate(glm::vec3(.0f, -5.0f,0.0f));
    cube2->setVelocity(glm::vec3(0.45f, 0.16f, .0f));
    cube2->setPlayer(2);

    UDMan.addUD(cube1);
    UDMan.addUD(cube2);

    char path3[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundPB.obj";
    char path4[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/backgroundCream.obj";

    BasicModel* bg = new BasicModel(modelShader, path3,input);
    BasicModel* foreground = new BasicModel(modelShader, path4,input);

    DebugCube* dc = new DebugCube(modelShader,  input);

    bg->setId(200);
    
    foreground->setId(201);

    bg->translate(glm::vec3(0.0f, -10.0f, -3.0f));
    foreground->translate(glm::vec3(0.625f, -8.0f, -1.0f));

    bg->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));
    foreground->rotate(3.14159265358979f, glm::vec3(.0f, .0f, 1.0f));

    foreground->scale(glm::vec3(.7425f, .6575f, .3f));

    UDMan.addUD(bg);
    UDMan.addUD(foreground);


    char path5[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/starCube2.obj";

    //SPAWN COINS
    int idNum = 10;
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

    while (!glfwWindowShouldClose(window))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        modelShader->use();

        if (start) {
            cm.checkCollision2D();
            UDMan.updateUDs();
            UDMan.drawUDs();
            UDMan.drawText();
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


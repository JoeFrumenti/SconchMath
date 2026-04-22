#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shaders/shader.h>

#include <camera.cpp>
#include "CollisionManager.h"
#include "ObjectManager.h"

#include "Model.h"

#include "UDManager.h"

#include "coin.cpp"
#include "BouncingCube.cpp"
#include "Background.cpp"

#include <string>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* configGL();

Shader* ourShader;
Shader* modelShader;

int scale = 50;

// settings
const unsigned int SCR_WIDTH = 9 * scale;
const unsigned int SCR_HEIGHT = 16 * scale;

int main()
{
   

    GLFWwindow* window = configGL();
    //ourShader = new Shader("C:/Users/joefr/source/include/Shaders/shader.vs", "C:/Users/joefr/source/include/Shaders/shader.fs");
    modelShader = new Shader("C:/Users/joefr/source/repos/SconchMath/modelShader.vs", "C:/Users/joefr/source/repos/SconchMath/modelShader.fs");

   
	/*GameObject cube(ourShader,"cube", "C:/Users/joefr/source/repos/SconchMath/assets/star.png", GL_RGBA);*/
    //GameObject bg(ourShader, "square", "C:/Users/joefr/source/repos/SconchMath/assets/backgroundPB.jpg", GL_RGB);


    UDManager UDMan = UDManager::getInstance();

    BouncingCube* bCube = new BouncingCube(modelShader);

    UDMan.addUD(bCube);

    Background* bg = new Background(modelShader);
    bg->setId(1);
    UDMan.addUD(bg);

    auto& objManager = ObjectManager::getInstance();
    int idNum = 10;

   
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            Coin* coiny = new Coin(modelShader);
            coiny->setId(idNum++);
            UDMan.addUD(coiny);
            coiny->translate(glm::vec3((float)i * 3.0f - 6, (float)j * 4.3f - 10.7f, 0.0f));
        }
    }


    camera* cam = new camera(modelShader, SCR_WIDTH, SCR_HEIGHT);

    cam->setup();
    //modelShader->use();

    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        //bg.render();

        //cm->checkCollision();

        //cube.screenBounce();
        
        //objManager.renderObjects();


        //// render the loaded model
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.1f, 0.07f, .1f));	// it's a bit too big for our scene, so scale it down
        //modelShader->setMat4("model", model);
        //ourModel.Draw(*modelShader);

        UDMan.updateUDs();
        UDMan.drawUDs();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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


#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shaders/shader.h>

#include <camera.cpp>
#include <CollisionManager.cpp>
#include <ObjectManager.h>

#include "Model.h"

#include "UD.h"
#include "coin.cpp"

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

    CollisionManager* cm = new CollisionManager();
   
	/*GameObject cube(ourShader,"cube", "C:/Users/joefr/source/repos/SconchMath/assets/star.png", GL_RGBA);
    GameObject bg(ourShader, "square", "C:/Users/joefr/source/repos/SconchMath/assets/backgroundPB.jpg", GL_RGB);*/

    char path[] = "C:/Users/joefr/source/repos/SconchMath/assets/Models/coin.obj";

    Model ourModel(path);

    Coin* coin = new Coin(modelShader);
    coin->translate(glm::vec3(.7f, .7f, 0.0f));

    auto& objManager = ObjectManager::getInstance();
    int idNum = 10;

   /* cube.setId(1);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 12; j++) {
            GameObject coin(ourShader, "cube", "C:/Users/joefr/source/repos/SconchMath/assets/container.jpg", GL_RGB);
            coin.setId(idNum++);
            cm->addCoin(coin);
            objManager.addObject(coin);
            coin.translate(glm::vec3(4* (float)i - 4.0, 4*(float)j - 9.0, 0.0f));
        }
    }

    cm->addObject(cube);

    objManager.addObject(cube);

    bg.fitScreen();*/

    camera* cam = new camera(ourShader, SCR_WIDTH, SCR_HEIGHT);

    //cam->setup();
    modelShader->use();

    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        //bg.render();

        cm->checkCollision();

        //cube.screenBounce();
        
        //objManager.renderObjects();

        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        modelShader->setMat4("projection", projection);
        modelShader->setMat4("view", view);

        //// render the loaded model
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.1f, 0.07f, .1f));	// it's a bit too big for our scene, so scale it down
        //modelShader->setMat4("model", model);
        //ourModel.Draw(*modelShader);

        coin->Update();
        coin->Draw();


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


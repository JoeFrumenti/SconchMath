#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shaders/shader.h>

#include <camera.cpp>
#include <CollisionManager.cpp>
#include <ObjectManager.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* configGL();

Shader* ourShader;

int scale = 50;

// settings
const unsigned int SCR_WIDTH = 9 * scale;
const unsigned int SCR_HEIGHT = 16 * scale;

int main()
{
   

    GLFWwindow* window = configGL();
    ourShader = new Shader("C:/Users/joefr/source/include/Shaders/shader.vs", "C:/Users/joefr/source/include/Shaders/shader.fs");

    CollisionManager* cm = new CollisionManager();
   
	GameObject* cube = new GameObject(ourShader,"cube", "C:/Users/joefr/source/repos/SconchMath/assets/star.png", GL_RGBA);
    GameObject* bg = new GameObject(ourShader, "square", "C:/Users/joefr/source/repos/SconchMath/assets/backgroundPB.jpg", GL_RGB);
    GameObject* cube2 = new GameObject(ourShader, "cube", "C:/Users/joefr/source/repos/SconchMath/assets/container.jpg", GL_RGB);


    auto& objManager = ObjectManager::getInstance();

    cube->setId(1);
    cube2->setId(2);


    cm->addObject(*cube);
    cm->addCoin(*cube2);

    objManager.addObject(*cube);
    objManager.addObject(*cube2);

    bg->fitScreen();

    cube2->translate(glm::vec3(4.0f, 5.0f, .0f));

    camera* cam = new camera(ourShader, SCR_WIDTH, SCR_HEIGHT);

    cam->setup();

    

    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        bg->render();

        cm->checkCollision();

        cube->screenBounce();
        

        cube2->spin();
        
        objManager.renderObjects();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube->clear();
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


#include "main.h"

int main()
{
    glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    addGameObjects();

    //init();

    renderLoop();

    glfwTerminate();

    return 0;
}





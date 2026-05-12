#include "main.h"

int main()
{
    setupWindow();

    addGameObjects();

    init();

    renderLoop();

    glfwTerminate();

    return 0;
}





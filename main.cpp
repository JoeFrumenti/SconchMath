#include "main.h"

int main()
{
    setupWindow();

    addGameObjects();

    initCubeVel();

    renderLoop();

    glfwTerminate();

    return 0;
}





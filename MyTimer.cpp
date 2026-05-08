#include "MyTimer.h"
#include <GLFW/glfw3.h>

void MyTimer::Update() {
	deltaTime = glfwGetTime() - lastFrame;
	lastFrame = glfwGetTime();
}
void MyTimer::Draw() {

}
float MyTimer::getDeltaTime() {
	return deltaTime;
}
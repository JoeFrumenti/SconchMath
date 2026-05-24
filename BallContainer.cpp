#include "BallContainer.h"
#include "BouncingCube.h"

void BallContainer::addBall(BouncingCube* ball) {
	balls.push_back(ball);
}

void BallContainer::multiplyBalls(int mult) {
	int j = balls.size();
	for (int i = 0; i < j; i++) {
		balls[i]->spawnClone();
	}
}
void BallContainer::removeBall(BouncingCube* ball) {
	auto it = std::find(balls.begin(), balls.end(), ball);
	if (it != balls.end()) {
		balls.erase(it);
	}
}
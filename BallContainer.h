#pragma once
#include <vector>

class BouncingCube;

class BallContainer {
private:
	std::vector<BouncingCube*> balls;
	

public:
	void addBall(BouncingCube* ball);

	void multiplyBalls(int mult);
	void removeBall(BouncingCube* ball);

	static BallContainer& getInstance() {
		static BallContainer instance;
		return instance;
	}

};
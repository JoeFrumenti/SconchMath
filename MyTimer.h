#pragma once
#include "UD.h"
class MyTimer : public UD {
private: 
	float deltaTime;
	float lastFrame;
public:
	void Update() override;
	void Draw() override;
	float getDeltaTime();

	static MyTimer& getInstance() {
		static MyTimer instance;
		return instance;
	}

};
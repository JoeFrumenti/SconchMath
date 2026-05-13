#pragma once
#include "UD.h"
#include "CollisionManager.h"
#include "GameManager.h"
#include "Projectile.h"
#include <memory>
#include <functional>

class Launcher:public UD {
private:
	CollisionManager& cm = CollisionManager::getInstance();
	float launchTimer = 0;
	GameManager& playMan = GameManager::getInstance();
	using Factory = std::function<std::unique_ptr<Projectile>(BouncingCube*)>;

	explicit Launcher(Factory f) : factory_(std::move(f)) {};
	Factory factory_;
	BouncingCube* Parent;
	MyTimer& timer = MyTimer::getInstance();

public:
	
	void Update() override;
	void Draw() override;
	void setParent(BouncingCube*);

	template <typename T> 
	static Launcher* Create() 
	{
		return new Launcher([](BouncingCube* cube) { return std::make_unique<T>(cube); });
	}

	Projectile* Launch(BouncingCube* cube) {
		Projectile* p = factory_(cube).release();
		return p;
	}
		
	
};
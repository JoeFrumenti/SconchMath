#pragma once
#include "coin.h"
#include "BouncingCube.h"
#include "BasicModel.h"
#include "DebugCube.h"
#include "Player1.h"
#include "Player2.h"
#include "CoinPickup.h"
#include "DropCoins.h"
#include "GameManager.h"
#include "Icey.h"
#include "Launcher.h"
#include "SlimeBall.h"
class PrefabLoader {
private:

public:
	BouncingCube* loadSlime();
	BouncingCube* loadIce();
	BouncingCube* loadMoneyBag();
	DebugCube* loadDebugCube();
};
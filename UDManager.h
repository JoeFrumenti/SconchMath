#pragma once
#include "UD.h"
#include <map>
class UDManager {
private: 
	std::map<int, UD*> UDs;
public:
	void addUD(UD* newUD);
	void updateUDs();
	void drawUDs();

};
#pragma once
#include "UD.h"
#include <map>
class UDManager {
private: 
	std::map<int, UD*> UDs;

	UDManager() {}
public:
	static UDManager& getInstance() {
		static UDManager instance; 
		return instance;
	}
	void addUD(UD* newUD);
	void updateUDs();
	void drawUDs();

};
#pragma once
#include "UD.h"
#include <map>
#include <vector>

class UDManager {
private: 
	std::map<int, UD*> UDs;
	std::vector<int> remQ;

	UDManager() {}
public:
	static UDManager& getInstance() {
		static UDManager instance; 
		return instance;
	}
	void addUD(UD* newUD);
	void updateUDs();
	void drawUDs();
	void removeObject(int id);
	void drawText();
	void queueRemoval(int id);
};
#pragma once
#include "Model.h"
#include "UD.h"
#include <map>
class ModelCache {
private:
	std::map<std::string, Model*> models;
public:
	static ModelCache& getInstance() {
		static ModelCache instance;
		return instance;
	}
	void addModel(std::string s, Model* model) {
		models[s] = model;
	}
	Model* getModel(std::string s) {
		return models[s];
	}
};
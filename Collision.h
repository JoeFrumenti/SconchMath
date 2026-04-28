#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class UD;

struct Collision {
	std::vector<std::string> tags;
	glm::vec3 pos;
	UD* obj;

	Collision(UD* obj) : obj(obj) {}
};
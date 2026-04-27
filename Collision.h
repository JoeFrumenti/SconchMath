#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Collision {
	std::vector<std::string> tags;
	glm::vec3 pos;

	Collision(std::vector<std::string> tags, glm::vec3 pos) : tags(tags), pos(pos) {}
};
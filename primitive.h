#pragma once
#include <string>
#include <vector>
#include <iostream>
class primitive {

public:
    std::vector<float> vertices;

    primitive();

    std::vector<float> getPrimitive(std::string type);
    std::vector<float> getCube();
    std::vector<float> getSquare();

};

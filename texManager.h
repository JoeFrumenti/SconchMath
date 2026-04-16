#pragma once
#include <glad/glad.h>
#include <Textures/stb_image.h>


#include <iostream>
#include <map>
#include <string>

class TexManager {
public:
    std::map<std::string, unsigned int> textures;
    TexManager();

    void addTexture(const char* path, std::string name, GLenum format);


    unsigned int getTexture(std::string name);

    void activateDoubleTexture(std::string a, std::string b);
    void activateTexture(std::string a);
};



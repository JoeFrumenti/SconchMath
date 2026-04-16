#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include <Shaders/shader.h>
#include "primitive.h"
#include "texManager.h"
#include "transform.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject {
private:

    std::vector<float> vertices;
    TexManager* tm;
    Shader* ourShader;
    transform* trans;
    std::string texPath;




public:
    GameObject(Shader* shade, std::string type, const char* texturePath, GLenum format);

    void setShader(Shader* shade);

    void translate(glm::vec3 pos);
    glm::vec2 getCenter();

    void destroy();

    void clear();

    void fitScreen();

    void render();

    void spin();
    void screenBounce();

    void bindTextures();

};

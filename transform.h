#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

#include <vector>
#include <windows.h>

#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"



class transform {
private:
    glm::mat4 model;
    unsigned int VBO, VAO;
    std::vector<float> vertices;
    glm::vec3 velocity;
    glm::vec3 pos;

    SoundDevice* mysounddevice = SoundDevice::get();
    uint32_t sound1 = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/chime.wav");
    SoundSource mySpeaker;

public:
    transform(std::vector<float> verts);

    void spinAround();

    void scale(glm::vec3 newScale);

    void translate(glm::vec3 newScale);

    glm::vec2 getCenter();

    void screenBounce();

    void scale(float scale);

    unsigned int getVertexArray();

    glm::mat4 getTrans();

};
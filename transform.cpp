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

#include "transform.h"



transform::transform(std::vector<float> verts) {
    model = glm::mat4(1.0f);
    velocity = glm::vec3(0.1f, 0.1f, 0.0f);
    pos = glm::vec3(.0f, .0f, 0.0f);


    vertices = verts;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void transform::spinAround() {
       
    model = glm::rotate(model, /*(float)glfwGetTime()*/ .1f, velocity);

    
}

void transform::scale(glm::vec3 newScale) {
    model = glm::scale(model, newScale);
}

void transform::translate(glm::vec3 newScale) {
    pos += newScale;
    model = glm::translate(model, newScale);
}

glm::vec2 transform::getCenter() {
    return glm::vec2(pos.x, pos.y);
}

void transform::screenBounce() {
    float scale = 0.68f;
    float boundsX = 8.8f * scale;
    float boundsY = 16.7f * scale;

    pos += velocity;

    if (pos.x >= boundsX || pos.x <= -boundsX) {
        mySpeaker.Play(sound1);
        velocity.x = -velocity.x;
           
    }
    if (pos.y >= boundsY || pos.y <= -boundsY) {
        mySpeaker.Play(sound1);
        velocity.y = -velocity.y;
            
    }

    // rebuild from scratch every frame
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.43f, 1.43f, 1.43f));
        
}

void transform::scale(float scale) {
    //model = glm::scale(model, glm::vec3(scale, scale, scale));
}

unsigned int transform::getVertexArray() {
    return VAO;
}

glm::mat4 transform::getTrans() {
    return model;
}

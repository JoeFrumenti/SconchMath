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

#include <GameObject.h>


SoundDevice* mysounddevice = SoundDevice::get();
uint32_t sound2 = SoundBuffer::get()->addSoundEffect("C:/Users/joefr/source/repos/SconchMath/assets/chime2.wav");

SoundSource mySpeaker;

    GameObject::GameObject(Shader* shade, std::string type, const char* texturePath, GLenum format) {

        primitive* pm = new primitive();
        vertices = pm->getPrimitive(type);
        trans = new transform(vertices);

        texPath = texturePath;

        tm = new TexManager();
        ourShader = shade;


        tm->addTexture(texturePath, texPath, format);


        id = 0;
        




    }

    void GameObject::setShader(Shader* shade) {
        ourShader = shade;
        ourShader->use();
    }

    void GameObject::translate(glm::vec3 pos) {
        trans->translate(pos);
    }
    glm::vec2 GameObject::getCenter() {
        return glm::vec2(trans->getCenter());
    }

    void GameObject::destroy() {
        std::cout << "DESTROYED!\n";
        mySpeaker.Play(sound2);
    }

    void GameObject::clear() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        /*glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);*/
    }

    void GameObject::fitScreen() {
        int scale = 2;
        trans->translate(glm::vec3(0.0f, 0.0f, -2.0f));
        trans->scale(glm::vec3(9.0f * scale,16.0f * scale,0.0f));
    }

    void GameObject::render() {

        tm->activateTexture(texPath);

        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader->ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(trans->getTrans()));
        glBindVertexArray(trans->getVertexArray());
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }

    void GameObject::spin() {
        trans->spinAround();

    }
    void GameObject::screenBounce() {
        trans->screenBounce();
    }

    void GameObject::bindTextures() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("container"));
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("face"));

    }

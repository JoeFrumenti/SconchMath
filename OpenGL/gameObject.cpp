#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include <Shaders/shader.h>
#include <primitive.cpp>
#include <OpenGL/texManager.cpp>
#include <transform.cpp>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject {
private:

    std::vector<float> vertices;
    TexManager* tm;
    Shader* ourShader;
    transform* trans;




public:
    GameObject(Shader* shade, std::string type) {

        primitive* pm = new primitive();
        vertices = pm->getPrimitive(type);
        trans = new transform(vertices);

        tm = new TexManager();
        ourShader = shade;


        tm->addTexture("C:/Users/joefr/source/include/Textures/container.jpg", "container", GL_RGB);
        tm->addTexture("C:/Users/joefr/source/include/Textures/awesomeface.png", "face", GL_RGBA);
        tm->activateDoubleTexture("container", "face");





    }

    void setShader(Shader* shade) {
        ourShader = shade;
        ourShader->use();
    }

    void clear() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        /*glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);*/
    }


    void render() {
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader->ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(trans->getTrans()));
        glBindVertexArray(trans->getVertexArray());
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }

    void spin() {
        trans->spinAround();

    }
    void screenBounce() {
        trans->screenBounce();
    }

    void bindTextures() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("container"));
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("face"));

    }

};
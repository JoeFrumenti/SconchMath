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
    std::string texPath;




public:
    GameObject(Shader* shade, std::string type, const char* texturePath, GLenum format) {

        primitive* pm = new primitive();
        vertices = pm->getPrimitive(type);
        trans = new transform(vertices);

        texPath = texturePath;

        tm = new TexManager();
        ourShader = shade;


        tm->addTexture(texturePath, texPath, format);
        




    }

    void setShader(Shader* shade) {
        ourShader = shade;
        ourShader->use();
    }

    void translate(glm::vec3 pos) {
        trans->translate(pos);
    }

    void clear() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        /*glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);*/
    }

    void fitScreen() {
        int scale = 2;
        trans->translate(glm::vec3(0.0f, 0.0f, -2.0f));
        trans->scale(glm::vec3(9.0f * scale,16.0f * scale,0.0f));
    }

    void render() {

        tm->activateTexture(texPath);

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
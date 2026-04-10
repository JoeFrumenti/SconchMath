#include <glad/glad.h>
#include <vector>
#include <iostream>

#include <primitive.cpp>
#include <OpenGL/texManager.cpp>

class GameObject {
private:

    unsigned int VBO, VAO;
    std::vector<float> vertices;
    TexManager* tm;


public:
    GameObject() {
        tm = new TexManager();
        primitive* pm = new primitive();
        vertices = pm->getCube();
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        std::cout << "cleanered!";

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        tm->addTexture("C:/Users/joefr/source/include/Textures/container.jpg", "container", GL_RGB);
        tm->addTexture("C:/Users/joefr/source/include/Textures/awesomeface.png", "face", GL_RGBA);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("container"));
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("face"));



    }

    void clear() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void render() {

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void bindTextures() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("container"));
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tm->getTexture("face"));

    }

};
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include <Shaders/shader.h>
#include <primitive.cpp>
#include <OpenGL/texManager.cpp>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject {
private:

    unsigned int VBO, VAO;
    std::vector<float> vertices;
    TexManager* tm;
    Shader* ourShader;


    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;


public:
    GameObject() {
        ourShader = new Shader("C:/Users/joefr/source/include/Shaders/shader.vs", "C:/Users/joefr/source/include/Shaders/shader.fs");
        tm = new TexManager();
        primitive* pm = new primitive();
        vertices = pm->getCube();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
        std::cout << "cleaned!";

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

        ourShader->use();
        ourShader->setInt("texture1", 0);
        ourShader->setInt("texture2", 1);



    }

    void clear() {
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void render() {
        ourShader->use();

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader->ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader->ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader->setMat4("projection", projection);


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
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <vector>

class transform {
private:
    glm::mat4 model;
    unsigned int VBO, VAO;
    std::vector<float> vertices;

public:
    transform(std::vector<float> verts) {
        model = glm::mat4(1.0f);

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

    void spinAround() {
        model = glm::rotate(model, /*(float)glfwGetTime()*/ .1f, glm::vec3(0.05f, .1f, 0.0f));

    }

    unsigned int getVertexArray() {
        return VAO;
    }

    glm::mat4 getTrans() {
        return model;
    }

};
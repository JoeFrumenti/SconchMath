
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class transform {
private:
    glm::mat4 model;
public:
    transform() {
        model = glm::mat4(1.0f);
    }

    void spinAround() {
        model = glm::rotate(model, /*(float)glfwGetTime()*/ .1f, glm::vec3(0.05f, .1f, 0.0f));

    }

    glm::mat4 getTrans() {
        return model;
    }

};
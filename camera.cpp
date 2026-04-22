
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <Shaders/shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
class camera {
private:

	glm::mat4 view;
	glm::mat4 projection;

	Shader* ourShader;


	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
public:
	camera(Shader* shade, unsigned int width, unsigned int height) {

		ourShader = shade;
		SCR_WIDTH = width;
		SCR_HEIGHT = height;
	}

	void setup() {

		ourShader->use();


		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -30.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		unsigned int viewLoc = glGetUniformLocation(ourShader->ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		
		ourShader->setMat4("projection", projection);
	}
};
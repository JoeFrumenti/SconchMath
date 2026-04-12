
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <Shaders/shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class camera {
private:

	glm::mat4 view;
	glm::mat4 projection;

	Shader* ourShader;


	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
public:
	camera(Shader* shade) {

		ourShader = shade;
	}

	void setup() {


		ourShader->use();
		ourShader->setInt("texture1", 0);
		ourShader->setInt("texture2", 1);


		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		unsigned int viewLoc = glGetUniformLocation(ourShader->ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		
		ourShader->setMat4("projection", projection);
	}
};
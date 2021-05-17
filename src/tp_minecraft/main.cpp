#include <iostream>
#include <cmath>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <mylibs/shaderClass.h>
#include <mylibs/vao.h>
#include <mylibs/vbo.h>
#include <mylibs/ebo.h>
#include <mylibs/texture.h>
#include <mylibs/camera.h>
#include <figures.h>

// colors of rubik cube
// blue =   0.0f, 0.0f, 1.0f,
// white =  1.0f, 1.0f, 1.0f,
// yellow = 1.0f, 1.0f, 0.0f,
// green =  0.0f, 0.5f, 0.0f,
// orange = 1.0f, 0.5f, 0.0f,
// red =    1.0f, 0.0f, 0.0f,


int width = 800, height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(width, height, "Window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);


	Cube* cube = new Cube(0.5f, 0.5f, 0.5f);

	// Shader for cube
	Shader shader("shader.vert", "shader.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO;
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(cube->getVertices(), cube->getVSize() * sizeof(float));
	// Generates Element Buffer Object and links it to indices
	EBO EBO(cube->getIndices(), cube->getISize() * sizeof(int));
	// Links VBO attributes such as coordinates, colors and textures to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();


	// proj, view and model

	glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::translate(Model, Pos);

	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(Model));



	// Stone Texture for cube
	Texture stoneTexture("stone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	stoneTexture.texUnit(shader, "tex0", 0);
/*
	// x Texture for cube
	Texture otherTexture("brick.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	otherTexture.texUnit(shader, "tex0", 1);
*/

	// camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

// positions for the cube
/*
	
	std::vector<glm::vec3> positions(27);
	int n = 2, pos = 0;
	for (int i = -1; i < n; ++i) {
		for (int j = -1; j < n; ++j) {
			for (int k = -1; k < n; ++k) {
				float x = 0.25f;
				float z = 0.25f;
				float y = 0.25f;
				
				positions[(pos++)] = glm::vec3(i * x, j * y, k * z);
			}
		}
	}
*/

	glEnable(GL_DEPTH_TEST);

	float prevTime = float(glfwGetTime());
	int change = 1;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		float time = float(glfwGetTime());
		// background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.Activate();
		
		// Manage inputs for camera
		camera.Inputs(window);
		
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		camera.Matrix(shader, "camMatrix");
/*
		//stone texture bind
		if (time - prevTime >= 1.0f) {
			change = (1 - change);
			prevTime = time;
		}
		if (change == 1) stoneTexture.Bind();
		else otherTexture.Bind();
		*/

		stoneTexture.Bind();

		VAO.Bind();
		

		glDrawElements(GL_TRIANGLES, cube->getISize(), GL_UNSIGNED_INT, 0);
		// Swap the window buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	// Deletes
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	shader.Delete();
	stoneTexture.Delete();
	//otherTexture.Delete();
    delete cube;

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
/*
//draw all the cubes
for (int i = 0; i < positions.size(); ++i) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, positions[i]);

	glUniformMatrix4fv(glGetUniformLocation(Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}
*/
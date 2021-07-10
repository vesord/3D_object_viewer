#include "scop.h"
#include "shaders.h"
#include "calculations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float ft_randf() {
	return (float)rand() / (float)INT32_MAX;
}

float frustumScale = 1.f; float zFar = 3.f; float zNear = 1.f;
float perspectiveMatrix[16];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_C) {
		glClearColor(ft_randf(), ft_randf(), ft_randf(), 1.0f);
	}
	else if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_L) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (key == GLFW_KEY_S) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void reshape_callback(GLFWwindow* window, int w, int h) {
	(void)window;
	perspectiveMatrix[0] = frustumScale / ((float)w / (float)h);
	perspectiveMatrix[5] = frustumScale;

	glViewport(0, 0, w, h);
}

void initialization() {
	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL.
	//Мажорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//Установка профайла для которого создается контекст
	// CORE_PROFILE will cause errors during calls to deprecated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Something for macOS ??
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

}

int main()
{
	initialization();

	// DO WINDOW

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to create GLEW window\n");
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	// DO CALLBACK

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, reshape_callback);

	// WORK WITH BUFFERS

	// Square with indexes VAO1
	GLfloat verticesTriangleColored[] = {
		0.0f,  0.5f, 0.0f,
		0.5f, -0.366f, 0.0f,
		-0.5f, -0.366f, 0.0f,
		1.0f,  0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLfloat verticesPrismColored[] = {
		0.25f,  0.25f, -1.25f, 1.0f,
		0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,

		0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,

		0.25f,  0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,
		0.25f, -0.25f, -2.75f, 1.0f,

		0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,

		-0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,

		-0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,

		0.25f,  0.25f, -1.25f, 1.0f,
		0.25f, -0.25f, -2.75f, 1.0f,
		0.25f, -0.25f, -1.25f, 1.0f,

		0.25f,  0.25f, -1.25f, 1.0f,
		0.25f,  0.25f, -2.75f, 1.0f,
		0.25f, -0.25f, -2.75f, 1.0f,

		0.25f,  0.25f, -2.75f, 1.0f,
		0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,

		0.25f,  0.25f, -2.75f, 1.0f,
		-0.25f,  0.25f, -1.25f, 1.0f,
		-0.25f,  0.25f, -2.75f, 1.0f,

		0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,
		0.25f, -0.25f, -1.25f, 1.0f,

		0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -2.75f, 1.0f,
		-0.25f, -0.25f, -1.25f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,

		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,
		0.8f, 0.8f, 0.8f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,

		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
	};

	// Create vertex array object VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Setting up culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Setting up Depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.f, 1.f);

/*	// Making element buffer object
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPrismColored), indicesPrismColored, GL_STATIC_DRAW);*/

	// Create verticesTriangle buffer object
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPrismColored), verticesPrismColored, GL_STATIC_DRAW);

	// Say OpenGL how to interpret verticesTriangle data
	// 0 - shader argument (check vert shader layout (location = 0)
	// 3 - size of argument of shader
	// GL_FALSE - no normalize
	// 3 * sizeof(GLfloat) - step on data
	// (GLvoid*) 0 - offset in buffer
	glEnableVertexAttribArray(0); // Attrib number = 0
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(sizeof(verticesPrismColored) / 2));
	glBindVertexArray(0);

	// WORK WITH SHADERS

	GLuint shaderProgram = makeTestShaderProgram();

	// MAKE UNIFORM VARIABLES

	memset(perspectiveMatrix, 0, sizeof(float) * 16);

	perspectiveMatrix[0] = frustumScale;
	perspectiveMatrix[5] = frustumScale;
	perspectiveMatrix[10] = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[11] = -1.f;
	perspectiveMatrix[14] = (2 * zFar * zNear) / (zNear - zFar);

	GLint perspectiveMatrixUnif = glGetUniformLocation(shaderProgram, "perspectiveMatrix");
	GLint offsetUnif = glGetUniformLocation(shaderProgram, "offset");

	// DISPLAY LOOP

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.f);
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculating offsets
//		float fXOffset = 0.f, fYOffset = 0.f;
//		ComputeRotationOffsets(&fXOffset, &fYOffset);

		// We are using our shader program
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
		glUniform2f(offsetUnif, .3f, .3f);
		// Setting uniform
//		glUniform1f(elapsedTimeUniform, (float)glfwGetTime());


		// We are using our VAO for figure
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform2f(offsetUnif, 1.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);

//		glUniform1f(elapsedTimeUniform, (float)glfwGetTime() + 2.5f);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

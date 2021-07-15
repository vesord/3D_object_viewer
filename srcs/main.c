#include "scop.h"
#include "shaders.h"
#include "parsing.h"
#include "events.h"
#include "buffers.h"
#include "calculations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float ft_randf() {
	return (float)rand() / (float)INT32_MAX;
}

// Window
GLFWwindow* window;

// Buffers/Arrays
GLuint vertexBufferObject;
GLuint indexBufferObject;
GLuint vertexArrayObject;

// Shaders
GLuint shaderProgram;

// Perspective settings
float calc_frustum_scale(float fFovDeg) {
	const float degToRad = 3.14159f * 2.0f / 360.0f;
	float fFovRad = fFovDeg * degToRad;
	return 1.0f / tanf(fFovRad / 2.0f);
}

float zFar; float zNear; float fovDeg; float frustumScale;
float cameraToClipMatrix[16];
GLint cameraToClipMatrixUnif;
float modelToCameraMatrix[16];
GLint modelToCameraMatrixUnif;

// Initializations

void create_window() {
	window = glfwCreateWindow(800, 800, "3D viewer", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
}

void Initialization() {
	// Init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // CORE_PROFILE will cause errors during calls to deprecated functions
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Something for macOS TODO: check what is this
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	// Create window
	create_window();

	// Init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to create GLEW window\n");
		exit(1);
	}

	// Init viewport
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Init frustum
	zNear = 1.f; zFar = 450.f; fovDeg = 45.f;
	frustumScale = calc_frustum_scale(fovDeg);

	// Setting up culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	// Setting up Depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.f, 1.f);
}

//typedef struct	s_scop
//{
//	GLuint vbo;
//	GLuint ibo;
//	GLuint vertexArrayObject;
//}				t_scop;

int main()
{
	Initialization();
	RegisterCallbacks(window);
	shaderProgram = make_gray_shader();

//	t_obj_data *obj = parse_obj_file("./models/teapot.obj");
//	t_obj_data *obj = parse_obj_file("./models/teapot2.obj");
//	t_obj_data *obj = parse_obj_file("./models/42.obj");
//	t_obj_data *obj = parse_obj_file("./models/agalia.obj");
//	t_obj_data *obj = parse_obj_file("./models/agalia2.obj");
	t_obj_data *obj = parse_obj_file("./models/vamp_female.obj");
//	t_obj_data *obj = parse_obj_file("./models/female.obj");
//	t_obj_data *obj = parse_obj_file("./models/cube3.obj");


	glGenBuffers(1, &vertexBufferObject);
	glGenBuffers(1, &indexBufferObject);
	glGenVertexArrays(1, &vertexArrayObject);

	set_buf_data_from_obj(obj, vertexBufferObject, indexBufferObject);
	set_vao_for_obj(obj, vertexArrayObject, vertexBufferObject, indexBufferObject);

	cameraToClipMatrixUnif = glGetUniformLocation(shaderProgram, "camera_to_clip_matrix");
	modelToCameraMatrixUnif = glGetUniformLocation(shaderProgram, "model_to_camera_matrix");

	memset(cameraToClipMatrix, 0, sizeof(float) * 16);
	cameraToClipMatrix[0] = frustumScale;
	cameraToClipMatrix[5] = frustumScale;
	cameraToClipMatrix[10] = (zFar + zNear) / (zNear - zFar);
	cameraToClipMatrix[11] = -1.f;
	cameraToClipMatrix[14] = (2 * zFar * zNear) / (zNear - zFar);
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, cameraToClipMatrix);
	glUseProgram(0);

	glUseProgram(shaderProgram);
	glUseProgram(shaderProgram);
	// DISPLAY LOOP

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.f);
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vertexArrayObject);

		glUseProgram(shaderProgram);

		stationary_offset((t_mat4f *) modelToCameraMatrix);
		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, modelToCameraMatrix);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glDrawElements(GL_TRIANGLES, obj->index_count, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glDrawElements(GL_TRIANGLES, obj->index_count, GL_UNSIGNED_INT, 0);
//		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);

//		OvalOffset((float)glfwGetTime());
//		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, modelToCameraMatrix);
//		glDrawElements(GL_TRIANGLES, obj->index_count, GL_UNSIGNED_INT, 0);
//		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);

//		BottomCircleOffset((float)glfwGetTime());
//		glUniformMatrix4fv(modelToCameraMatrixUnif, 1, GL_FALSE, modelToCameraMatrix);
//		glDrawElements(GL_TRIANGLES, obj->index_count, GL_UNSIGNED_INT, 0);
//		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);

//		glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);

		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

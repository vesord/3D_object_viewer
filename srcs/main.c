#include "scop.h"
#include "shaders.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float ft_randf() {
	return (float)rand() / (float)INT32_MAX;
}

// Object data

const int numberOfVertices = 8;

#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR 	0.0f, 0.0f, 1.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f

const float vertexData[] =
	{
		+1.0f, +1.0f, +1.0f,
		-1.0f, -1.0f, +1.0f,
		-1.0f, +1.0f, -1.0f,
		+1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		+1.0f, +1.0f, -1.0f,
		+1.0f, -1.0f, +1.0f,
		-1.0f, +1.0f, +1.0f,

		GREEN_COLOR,
		BLUE_COLOR,
		RED_COLOR,
		BROWN_COLOR,

		GREEN_COLOR,
		BLUE_COLOR,
		RED_COLOR,
		BROWN_COLOR,
	};

const float vertexData2[] =
	{
		+1.0f, +1.0f, +1.0f, 1.f,
		-1.0f, -1.0f, +1.0f, 1.f,
		-1.0f, +1.0f, -1.0f, 1.f,
		+1.0f, -1.0f, -1.0f, 1.f,

		-1.0f, -1.0f, -1.0f, 1.f,
		+1.0f, +1.0f, -1.0f, 1.f,
		+1.0f, -1.0f, +1.0f, 1.f,
		-1.0f, +1.0f, +1.0f, 1.f,

		GREEN_COLOR,
		BLUE_COLOR,
		RED_COLOR,
		BROWN_COLOR,

		GREEN_COLOR,
		BLUE_COLOR,
		RED_COLOR,
		BROWN_COLOR,
	};

const GLshort indexData[] =
	{
		0, 1, 2,
		1, 0, 3,
		2, 3, 0,
		3, 2, 1,

		5, 4, 6,
		4, 5, 7,
		7, 6, 4,
		6, 7, 5,
	};

// Window
GLFWwindow* window;

// Buffers/Arrays
GLuint vertexBufferObject;
GLuint indexBufferObject;
GLuint vao;

// Shaders
GLuint shaderProgram;

// Perspective settings
float CalcFrustumScale(float fFovDeg) {
	const float degToRad = 3.14159f * 2.0f / 360.0f;
	float fFovRad = fFovDeg * degToRad;
	return 1.0f / tanf(fFovRad / 2.0f);
}

float zFar; float zNear; float fovDeg; float frustumScale;
float cameraToClipMatrix[16];
GLint cameraToClipMatrixUnif;
float modelToCameraMatrix[16];
GLint modelToCameraMatrixUnif;

// Callbacks
void key_callback(GLFWwindow* w, int key, int scancode, int action, int mode) {
	static int cull = 0;
	if (key == GLFW_KEY_C) {
		if (cull) {
			cull = !cull;
			glCullFace(GL_FRONT);
		}
		else {
			cull = !cull;
			glCullFace(GL_BACK);
		}
	}
	else if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(w, GL_TRUE);
	}
	else if (key == GLFW_KEY_L) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (key == GLFW_KEY_S) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void reshape_callback(GLFWwindow* w, int width, int height) {
	(void)w;
	cameraToClipMatrix[0] = frustumScale / ((float)width / (float)height);
	cameraToClipMatrix[5] = frustumScale;

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, cameraToClipMatrix);
	glUseProgram(0);

	glViewport(0, 0, width, height);
}

void RegisterCallbacks() {
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, reshape_callback);
}

// Initializations

void scopCreateWindow() {
	window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
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
	scopCreateWindow();

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
	frustumScale = CalcFrustumScale(fovDeg);

	// Setting up culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	// Setting up Depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.f, 1.f);
}

void InitBuffers() {
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData2), vertexData2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/// TEST FUNCTION
GLuint makeTestShaderProgram() {
	GLuint *shaderList;

	shaderList = malloc(sizeof(GLuint) * 3); // TODO: protect
	if (!shaderList) {
		exit(1);
	}
//	shaderList[0] = CreateShader(GL_VERTEX_SHADER, &vertexShaderSrcModelCameraClipTransform);
//	shaderList[1] = CreateShader(GL_FRAGMENT_SHADER, &fragmentShaderSrcSmoothColor);
	shaderList[0] = CreateShader(GL_VERTEX_SHADER, &vertex_shader_pass_vtn);
	shaderList[1] = CreateShader(GL_FRAGMENT_SHADER, &fragment_shader_pass_vtn);
	shaderList[2] = 0;

	shaderProgram = CreateShaderProgram(shaderList);

	glUseProgram(shaderProgram);
	// APPLY UNIFORMS MB
	glUseProgram(0);
	free(shaderList);
	return shaderProgram;
}

void StationaryOffset() {
	memset(modelToCameraMatrix, 0, sizeof(float) * 16);

	// Identity matrix
	modelToCameraMatrix[0] = 1.f;
	modelToCameraMatrix[5] = 1.f;
	modelToCameraMatrix[10] = 1.f;
	modelToCameraMatrix[15] = 1.f;

	// Stationary offset
	modelToCameraMatrix[12] = -0.f;
	modelToCameraMatrix[13] = -0.f;
	modelToCameraMatrix[14] = -100.f;
}

void OvalOffset(float elapsedTime) {
	const float loopDuration = 3.f;
	const float scale = 3.141592f * 2.f / loopDuration;

	float curTimeInLoop = fmodf(elapsedTime, loopDuration);

	memset(modelToCameraMatrix, 0, sizeof(float) * 16);

	// Identity matrix
	modelToCameraMatrix[0] = 1.f;
	modelToCameraMatrix[5] = 1.f;
	modelToCameraMatrix[10] = 1.f;
	modelToCameraMatrix[15] = 1.f;

	modelToCameraMatrix[12] = cosf(curTimeInLoop * scale) * 4.f;
	modelToCameraMatrix[13] = sinf(curTimeInLoop * scale) * 6.f;
	modelToCameraMatrix[14] = -20.f;
}

void BottomCircleOffset(float elapsedTime) {
	const float loopDuration = 12.f;
	const float scale = 3.141592f * 2.f / loopDuration;

	float curTimeInLoop = fmodf(elapsedTime, loopDuration);

	memset(modelToCameraMatrix, 0, sizeof(float) * 16);

	// Identity matrix
	modelToCameraMatrix[0] = 1.f;
	modelToCameraMatrix[5] = 1.f;
	modelToCameraMatrix[10] = 1.f;
	modelToCameraMatrix[15] = 1.f;

	modelToCameraMatrix[12] = cosf(curTimeInLoop * scale) * 5.f;
	modelToCameraMatrix[13] = -3.5f;
	modelToCameraMatrix[14] = sinf(curTimeInLoop * scale) * 6.f - 20.f;
}

//typedef struct	s_scop
//{
//	GLuint vbo;
//	GLuint ibo;
//	GLuint vao;
//}				t_scop;

void register_buffers(t_obj_data *obj)
{
	size_t vertex_size;

	vertex_size = sizeof(t_vec4f);
	if (obj->has_normals)
		vertex_size += sizeof(t_vec3f);
	if (obj->has_textures)
		vertex_size += sizeof(t_vec2f);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, obj->vertex_count * vertex_size, obj->vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * obj->index_count, obj->index_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int main()
{
//	t_obj_data *obj = parse_obj_file("./models/teapot.obj");
//	t_obj_data *obj = parse_obj_file("./models/teapot2.obj");
//	t_obj_data *obj = parse_obj_file("./models/42.obj");
//	t_obj_data *obj = parse_obj_file("./models/agalia.obj");
//	t_obj_data *obj = parse_obj_file("./models/agalia2.obj");
	t_obj_data *obj = parse_obj_file("./models/vamp_female.obj");
//	t_obj_data *obj = parse_obj_file("./models/female.obj");
//	t_obj_data *obj = parse_obj_file("./models/cube3.obj");

	Initialization();
	RegisterCallbacks();
	shaderProgram = makeTestShaderProgram();

	register_buffers(obj);
//	InitBuffers();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t colorDataOffset = sizeof(float) * 4 * numberOfVertices;
	size_t textures_data_offset = sizeof(t_vec4f) * obj->vertex_count * obj->has_textures;
	size_t normals_data_offset = sizeof(t_vec2f) * obj->vertex_count * obj->has_normals + textures_data_offset;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	if (obj->has_textures)
		glEnableVertexAttribArray(1);
	if (obj->has_normals)
		glEnableVertexAttribArray(2);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); // for guide
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorDataOffset); // for guide

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0); // for scop
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)textures_data_offset);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)normals_data_offset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBindVertexArray(0);

	// MAKE UNIFORM VARIABLES

//	cameraToClipMatrixUnif = glGetUniformLocation(shaderProgram, "cameraToClipMatrix");
//	modelToCameraMatrixUnif = glGetUniformLocation(shaderProgram, "modelToCameraMatrix");

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

		glBindVertexArray(vao);

		glUseProgram(shaderProgram);

		StationaryOffset();
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

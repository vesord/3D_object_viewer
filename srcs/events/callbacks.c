#include "scop.h"
#include "events_private.h"

void key_callback(GLFWwindow* w, int key, int scancode, int action, int mode) {
	int		set_value;

	set_value = 0;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		set_value = 1;
	if (key == GLFW_KEY_W)
		get_scop(NULL)->keys.forward = set_value;
	if (key == GLFW_KEY_S)
		get_scop(NULL)->keys.back = set_value;
	if (key == GLFW_KEY_A)
		get_scop(NULL)->keys.left = set_value;
	if (key == GLFW_KEY_D)
		get_scop(NULL)->keys.right = set_value;
	if (key == GLFW_KEY_LEFT_SHIFT)
		get_scop(NULL)->keys.up = set_value;
	if (key == GLFW_KEY_LEFT_CONTROL)
		get_scop(NULL)->keys.down = set_value;
	if (key == GLFW_KEY_C)
		get_scop(NULL)->keys.change_cull = set_value;
	if (key == GLFW_KEY_SPACE)
		get_scop(NULL)->keys.enable_rotation = set_value;
	if (key == GLFW_KEY_I)
		get_scop(NULL)->keys.draw_points = set_value;
	if (key == GLFW_KEY_O)
		get_scop(NULL)->keys.draw_lines = set_value;
	if (key == GLFW_KEY_P)
		get_scop(NULL)->keys.draw_triangles = set_value;
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(w, GL_TRUE);
}

void reshape_callback(GLFWwindow* w, int width, int height) {
	(void)w;
//	cameraToClipMatrix[0] = frustumScale / ((float)width / (float)height);
//	cameraToClipMatrix[5] = frustumScale;
//
//	glUseProgram(shaderProgram);
//	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, cameraToClipMatrix);
//	glUseProgram(0);

	glViewport(0, 0, width, height);
}

void register_callbacks(GLFWwindow *window)
{
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, reshape_callback);
}
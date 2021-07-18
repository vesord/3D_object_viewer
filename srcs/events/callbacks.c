#include "scop.h"
#include "events_private.h"

static void	set_moving_keys(int key, int set_value, t_keys *keys)
{
	if (key == GLFW_KEY_W)
		keys->forward = set_value;
	if (key == GLFW_KEY_S)
		keys->back = set_value;
	if (key == GLFW_KEY_A)
		keys->left = set_value;
	if (key == GLFW_KEY_D)
		keys->right = set_value;
	if (key == GLFW_KEY_LEFT_SHIFT)
		keys->up = set_value;
	if (key == GLFW_KEY_LEFT_CONTROL)
		keys->down = set_value;
}

static void	set_drawing_keys(int key, int set_value, t_keys *keys)
{
	if (key == GLFW_KEY_I)
		keys->draw_points = set_value;
	if (key == GLFW_KEY_O)
		keys->draw_lines = set_value;
	if (key == GLFW_KEY_P)
		keys->draw_triangles = set_value;
}

void 		key_callback(GLFWwindow* w, int key, int scancode,
						  int action, int mode) {
	int		set_value;

	set_value = 0;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		set_value = 1;
	set_moving_keys(key, set_value, &get_scop(NULL)->keys);
	set_drawing_keys(key, set_value, &get_scop(NULL)->keys);
	if (key == GLFW_KEY_C)
		get_scop(NULL)->keys.change_cull = set_value;
	if (key == GLFW_KEY_SPACE)
		get_scop(NULL)->keys.enable_rotation = set_value;
	if (key == GLFW_KEY_T)
		get_scop(NULL)->keys.apply_texture = set_value;
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(w, GL_TRUE);
}

void		reshape_callback(GLFWwindow* w, int width, int height) {
	(void)w;
//	cameraToClipMatrix[0] = frustumScale / ((float)width / (float)height);
//	cameraToClipMatrix[5] = frustumScale;
//
//	glUseProgram(shaderProgram);
//	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, cameraToClipMatrix);
//	glUseProgram(0);

	glViewport(0, 0, width, height);
}	// TODO: add reshape management

void		register_callbacks(GLFWwindow *window)
{
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, reshape_callback);
}
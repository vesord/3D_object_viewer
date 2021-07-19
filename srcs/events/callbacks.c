#include "scop.h"
#include "events_private.h"
#include "calculations.h"

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

static void set_rendering_keys(int key, int set_value, t_keys *keys)
{
	if (key == GLFW_KEY_T)
		get_scop(NULL)->keys.render_texture = set_value;
	if (key == GLFW_KEY_R)
		get_scop(NULL)->keys.render_triangles = set_value;
	if (key == GLFW_KEY_Y)
		get_scop(NULL)->keys.render_light = set_value;
	if (key == GLFW_KEY_U)
		get_scop(NULL)->keys.render_textured_light = set_value;
}

void 		key_callback(GLFWwindow* w, int key, int scancode,
						  int action, int mode) {
	int		set_value;

	set_value = 0;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		set_value = 1;
	set_moving_keys(key, set_value, &get_scop(NULL)->keys);
	set_drawing_keys(key, set_value, &get_scop(NULL)->keys);
	set_rendering_keys(key, set_value, &get_scop(NULL)->keys);
	if (key == GLFW_KEY_SPACE)
		get_scop(NULL)->keys.enable_rotation = set_value;
	if (key == GLFW_KEY_1)
		get_scop(NULL)->keys.move_decrease = set_value;
	if (key == GLFW_KEY_2)
		get_scop(NULL)->keys.move_increase = set_value;
	if (key == GLFW_KEY_3)
		get_scop(NULL)->keys.fill_color_decrease = set_value;
	if (key == GLFW_KEY_4)
		get_scop(NULL)->keys.fill_color_increase = set_value;
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{

	}
}

static const t_vec3f xz_normal = {.x = 0.f, .y = 1.f, .z = 0.f};
static const t_vec3f yz_normal = {.x = 1.f, .y = 0.f, .z = 0.f};

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static const double	rads_per_pixel = 2 * 3.14159265 / 800.;
	static double		prev_xpos;
	static double		prev_ypos;
	int					state;

	state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		mat_rotate_around(&get_scop(NULL)->mat.transf.rotate,
						  &xz_normal,
						  (float)((-prev_xpos + xpos) * rads_per_pixel));
		mat_rotate_around(&get_scop(NULL)->mat.transf.rotate,
						  &yz_normal,
						  (float)((-prev_ypos + ypos) * rads_per_pixel));
	}
	prev_xpos = xpos;
	prev_ypos = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	t_vec3f scroll_translation;

	scroll_translation.x = 0;
	scroll_translation.y = 0;
	scroll_translation.z = (float)yoffset * get_scop(NULL)->state.moving_step;
	translate(&get_scop(NULL)->mat.transf.translate, &scroll_translation);
}

void		register_callbacks(GLFWwindow *window)
{
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, reshape_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
}
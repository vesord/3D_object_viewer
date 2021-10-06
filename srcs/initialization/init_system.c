#include "scop.h"
#include "initialization_private.h"

void create_window(GLFWwindow **window) {
	*window = glfwCreateWindow(800, 800, "3D viewer", NULL, NULL);
	if (*window == NULL)
		init_fail("Failed to create GLFW window");
	glfwMakeContextCurrent(*window);
}

void init_glfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Something for macOS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // CORE_PROFILE will cause errors during calls to deprecated functions
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void init_glew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		init_fail("Failed to init GLEW");
}

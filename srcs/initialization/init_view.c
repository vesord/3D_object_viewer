#include "scop.h"
#include "initialization_private.h"

void init_viewport(GLFWwindow *window)
{
	int	width;
	int height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
}

void init_culling()
{
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

void init_depth()
{
	static const float z_depth_near = 0.f;
	static const float z_depth_far = 1.f;
	static const float depth_clear_value = 1.f;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(z_depth_near, z_depth_far);
	glClearDepth(depth_clear_value);
}
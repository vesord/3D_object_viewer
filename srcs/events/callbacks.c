#include "events_private.h"

void RegisterCallbacks(GLFWwindow *window) {
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, reshape_callback);
}

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
//	cameraToClipMatrix[0] = frustumScale / ((float)width / (float)height);
//	cameraToClipMatrix[5] = frustumScale;
//
//	glUseProgram(shaderProgram);
//	glUniformMatrix4fv(cameraToClipMatrixUnif, 1, GL_FALSE, cameraToClipMatrix);
//	glUseProgram(0);

	glViewport(0, 0, width, height);
}
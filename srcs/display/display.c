#include "scop.h"
#include "scop_struct.h"
#include "calculations.h"

void display(t_scop scop)
{
	while(!glfwWindowShouldClose(scop.window))
	{
		glfwPollEvents();
		// TODO: add terminal commands
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(scop.bufs.vao);
		glUseProgram(scop.shaders.cur);

		if (1) // TODO: add enable_auto_rotation
			auto_rotation(&scop.mat);
//		stationary_offset(&scop.mat.model_to_cam); // TODO: change to rotate
		glUniformMatrix4fv(scop.shaders.model_to_cam_unif, 1, GL_FALSE, (float *)&scop.mat.model_to_cam);
		glUniformMatrix4fv(scop.shaders.cam_to_clip_unif, 1, GL_FALSE, (float *)&scop.mat.cam_to_clip);
		glDrawElements(GL_TRIANGLES, scop.obj->index_count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(scop.window);
	}
}
#include "scop.h"
#include "calculations.h"
#include "events.h"

t_scop *get_scop(t_scop* scop_ptr)
{
	static t_scop *scop;

	if (!scop && scop_ptr)
		scop = scop_ptr;
	return scop;
}

void display(t_scop scop)
{
	get_scop(&scop);
	while(!glfwWindowShouldClose(scop.window))
	{
		glfwPollEvents();
		// TODO: add terminal commands
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(scop.bufs.vao);
		glUseProgram(scop.shaders.cur);

		process_keys(&scop);

		if (scop.state.enable_rotation) // TODO: add enable_auto_rotation
			auto_rotation(&scop.mat);
		update_model_to_cam(&scop.mat);

		glUniformMatrix4fv(scop.shaders.model_to_cam_unif, 1, GL_FALSE, (float *)&scop.mat.model_to_cam);
		glUniformMatrix4fv(scop.shaders.cam_to_clip_unif, 1, GL_FALSE, (float *)&scop.mat.cam_to_clip);
		glDrawElements(scop.state.draw_type, scop.obj->index_count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(scop.window);
	}
}
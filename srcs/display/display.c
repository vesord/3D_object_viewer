#include "scop.h"
#include "calculations.h"
#include "events.h"

extern GLuint g_sampler; // TODO: remove

t_scop	*get_scop(t_scop* scop_ptr)
{
	static t_scop *scop;

	if (!scop && scop_ptr)
		scop = scop_ptr;
	return scop;
}

void	display(t_scop scop)
{
	get_scop(&scop);
	while(!glfwWindowShouldClose(scop.window))
	{
		glfwPollEvents();
		poll_terminal();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		process_keys(&scop);
		if (!scop.obj)
			continue ;
		if (scop.state.enable_rotation)
			auto_rotation(&scop.mat);
		update_model_to_cam(&scop.mat);


		// VAO
		glBindVertexArray(scop.bufs.vao);
		// Shader
		glUseProgram(scop.shaders.cur);
		// Uniforms
		glUniformMatrix4fv(scop.shaders.model_to_cam_unif, 1, GL_FALSE,
						   (float *)&scop.mat.model_to_cam);
		glUniformMatrix4fv(scop.shaders.cam_to_clip_unif, 1, GL_FALSE,
						   (float *)&scop.mat.cam_to_clip);
		glUniform1i(scop.shaders.has_textures_unif, 1); // TODO: change 1 to scop.state.has_textures;

		// Textures

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scop.texture_obj);
		glDrawElements(scop.state.draw_type, scop.obj->index_count,
					   GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
		glBindVertexArray(0);
		glfwSwapBuffers(scop.window);
	}
}
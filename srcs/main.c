#include "scop.h"
#include "shaders.h"
#include "parsing.h"
#include "events.h"
#include "buffers.h"
#include "calculations.h"
#include "initialization.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float ft_randf() {
	return (float)rand() / (float)INT32_MAX;
}

//typedef struct	s_scop
//{
//	GLuint vbo;
//	GLuint ibo;
//	GLuint vertexArrayObject;
//}				t_scop;

int main()
{
	t_scop scop;

	initialization(&scop);
	RegisterCallbacks(scop.window); // TODO: move to init

//	t_obj_data *obj = parse_obj_file("./models/teapot.obj");
//	t_obj_data *obj = parse_obj_file("./models/teapot2.obj");
//	t_obj_data *obj = parse_obj_file("./models/42.obj");
//	t_obj_data *obj = parse_obj_file("./models/agalia.obj");
//	t_obj_data *obj = parse_obj_file("./models/agalia2.obj");
	t_obj_data *obj = parse_obj_file("./models/vamp_female.obj");
//	t_obj_data *obj = parse_obj_file("./models/female.obj");
//	t_obj_data *obj = parse_obj_file("./models/cube3.obj");

	// BUFFERS;
	set_buf_data_from_obj(obj, scop.bufs.vbo, scop.bufs.ibo); // Use after model change
	set_vao_for_obj(obj, scop.bufs.vao, scop.bufs.vbo, scop.bufs.ibo); // Use after on model change

	// DISPLAY LOOP

	while(!glfwWindowShouldClose(scop.window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(scop.bufs.vao);
		glUseProgram(scop.shaders.cur);

		stationary_offset(&scop.model_to_cam); // TODO: change to rotate
		glUniformMatrix4fv(scop.shaders.model_to_cam_unif, 1, GL_FALSE, (float *)&scop.model_to_cam);
		glUniformMatrix4fv(scop.shaders.cam_to_clip_unif, 1, GL_FALSE, (float *)&scop.cam_to_clip);
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
		glfwSwapBuffers(scop.window);
	}
	glfwTerminate();
	return 0;
}

#include "scop.h"
#include "shaders.h"
#include "parsing.h"
#include "buffers.h"
#include "initialization.h"
#include "calculations.h"
#include "display.h"
#include "bmp_load.h"

int main(int argc, char **argv)
{
	t_scop scop;

	initialization(&scop);

//	scop.obj = parse_obj_file("./models/teapot.obj");
//	scop.obj = parse_obj_file("./models/teapot2.obj");
	scop.obj = parse_obj_file("./models/42.obj");
//	scop.obj = parse_obj_file("./models/agalia.obj");
//	scop.obj = parse_obj_file("./models/agalia2.obj");
//	scop.obj = parse_obj_file("./models/vamp_female.obj");
//	scop.obj = parse_obj_file("./models/female.obj");
//	scop.obj = parse_obj_file("./models/cube.obj");

	if (scop.obj)
	{
		set_buf_data_from_obj(scop.obj, scop.bufs.vbo, scop.bufs.ibo); // Use after model change
		set_vao_for_obj(scop.obj, scop.bufs.vao, scop.bufs.vbo, scop.bufs.ibo); // Use after on model change
		translate(&scop.mat.transf.rotate, &scop.obj->center_offset);
	}

	scop.bmp = bmp_load("./textures/pony.bmp");
//	scop.bmp = bmp_load("./textures/cat.bmp");
//	scop.bmp = bmp_load("./textures/star.bmp");

	if (scop.bmp)
	{
		glBindTexture (GL_TEXTURE_2D, scop.texture_obj);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, scop.bmp->bmi.width,
					 scop.bmp->bmi.height, 0, GL_BGRA,
					 GL_UNSIGNED_BYTE, scop.bmp->data);
		glBindTexture(GL_TEXTURE_2D, 0);
		free_bmp(&scop.bmp);
	}

	// TODO: add help message
	display(scop);
	glfwTerminate();
	return 0;
}

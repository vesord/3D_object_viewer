#include "scop.h"
#include "shaders.h"
#include "parsing.h"
#include "buffers.h"
#include "initialization.h"
#include "calculations.h"
#include "display.h"
#include "bmp_load.h"

GLuint g_sampler; // TODO: remove
#include <stdio.h>

int main(int argc, char **argv)
{
	t_scop scop;

	initialization(&scop);


//	scop.obj = parse_obj_file("./models/teapot.obj");
//	scop.obj = parse_obj_file("./models/teapot2.obj");
//	scop.obj = parse_obj_file("./models/42.obj");
//	scop.obj = parse_obj_file("./models/agalia.obj");
//	scop.obj = parse_obj_file("./models/agalia2.obj");
//	scop.obj = parse_obj_file("./models/vamp_female.obj");
//	scop.obj = parse_obj_file("./models/female.obj");
	scop.obj = parse_obj_file("./models/cube.obj");

	if (scop.obj)
	{
		set_buf_data_from_obj(scop.obj, scop.bufs.vbo, scop.bufs.ibo); // Use after model change
		set_vao_for_obj(scop.obj, scop.bufs.vao, scop.bufs.vbo, scop.bufs.ibo); // Use after on model change
		translate(&scop.mat.transf.rotate, &scop.obj->center_offset);
	}

//	scop.bmp = bmp_load("./textures/pony.bmp");
//	scop.bmp = bmp_load("./textures/cat.bmp");
	scop.bmp = bmp_load("./textures/star.bmp");

	unsigned char *fucking_color = malloc(scop.bmp->bmi.img_size);
	for (int i = 0; i < scop.bmp->bmi.img_size; ++i)
	{
		fucking_color[i] = 174;
	}
	GLenum err;

	if (scop.bmp)
	{
		glGenTextures(1, &scop.texture_obj);
		glBindTexture (GL_TEXTURE_2D, scop.texture_obj);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, scop.bmp->bmi.width, scop.bmp->bmi.height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, scop.bmp->bmi.width, scop.bmp->bmi.height, GL_BGRA, GL_UNSIGNED_BYTE, scop.bmp->data);

//		glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA, scop.bmp->bmi.width,
//					 scop.bmp->bmi.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//					 fucking_color);
	}


	while((err = glGetError()) != GL_NO_ERROR)
	{
		// Process/log the error.
		printf("Err occured %x\n", err);
	}

	// TODO: add help message
	display(scop);
	glfwTerminate();
	return 0;
}

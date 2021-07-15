#ifndef SCOP_SCOP_STRUCT_H
#define SCOP_SCOP_STRUCT_H

#include "scop.h"
#include "parsing.h"

typedef struct	s_shaders
{
	GLuint	cur;
	GLuint	*arr;
	GLuint	count;
	GLint	model_to_cam_unif;
	GLint	cam_to_clip_unif;
}				t_shaders;

typedef struct	s_buf_objects
{
	GLuint		vbo;
	GLuint		ibo;
	GLuint		vao;
}				t_buf_objects;

typedef struct	s_scop
{
	GLFWwindow		*window;
	t_shaders		shaders;
	t_buf_objects	bufs;
	t_obj_data		*obj; // TODO: change to stack memory?
	t_mat4f			model_to_cam;
	t_mat4f			cam_to_clip;

}				t_scop;


#endif //SCOP_SCOP_STRUCT_H

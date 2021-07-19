#ifndef SCOP_SCOP_STRUCT_H
#define SCOP_SCOP_STRUCT_H

#include "scop.h"
#include "parsing.h"
#include "bmp_load.h"

typedef struct	s_shaders
{
	GLuint	cur;
	GLuint	*arr;
	GLuint	count;
	GLint	model_to_cam_unif;
	GLint	cam_to_clip_unif;
	GLint	shading_type_unif;
}				t_shaders;

typedef struct	s_buf_objects
{
	GLuint		vbo;
	GLuint		ibo;
	GLuint		vao;
}				t_buf_objects;

typedef struct	s_transform
{
	t_mat4f			strp;
	t_mat4f			rotate;
	t_mat4f			translate;
	t_mat4f			scale;
}				t_transform;

typedef struct	s_matrices
{
	t_mat4f			model_to_cam;
	t_mat4f			cam_to_clip;
	t_mat4f			center_translate;
	t_transform		transf;
}				t_matrices;

typedef struct	s_keys
{
	int up;
	int down;
	int forward;
	int back;
	int left;
	int right;
	int enable_rotation;
	int draw_triangles;
	int draw_lines;
	int draw_points;
	int render_texture;
	int render_triangles;
	int render_light;
	int render_textured_light;
	int move_increase;
	int move_decrease;
	int fill_color_increase;
	int fill_color_decrease;
	int change_cull; // TODO: add changing culling
}				t_keys;

typedef struct	s_states
{
	int		enable_rotation;
	GLenum	draw_type;
	GLenum	culling; // TODO: add changing culling
	float	moving_step;
	int		shading_type;
	t_vec3f	fill_color;
}				t_states;

typedef struct	s_scop
{
	GLFWwindow		*window;
	t_shaders		shaders;
	t_buf_objects	bufs;
	t_obj_data		*obj;
	t_bmp_data		*bmp;
	GLuint			texture_obj;
	t_matrices		mat;
	t_keys			keys;
	t_states		state;
}				t_scop;

#endif

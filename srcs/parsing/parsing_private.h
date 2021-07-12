//
// Created by vesord on 12.07.2021.
//

#ifndef PARSING_PRIVATE_H
#define PARSING_PRIVATE_H

#include "scop.h"

typedef struct	s_obj_file {
	float	*vertex_buffer_data;
	int		*index_buffer_data;
	size_t	index_count;
	size_t	vertex_count;
	int		has_textures;
	int		has_normals;
	t_err	err_type;
	size_t	vertex_buffer_size;
	size_t	textures_buffer_size;
	size_t	normals_buffer_size;
	t_vec2f	*textures_buffer;
	t_vec3f	*normals_buffer;
	size_t	textures_count;
	size_t	normals_count;
}				t_obj_file;

typedef enum	e_line_type {
	LINE_TYPE_SKIP,
	LINE_TYPE_VERTEX,
	LINE_TYPE_TEXTURE,
	LINE_TYPE_NORMAL,
	LINE_TYPE_FACE
}				t_line_type;

typedef enum	e_face_line_type {
	FACE_LINE_TYPE_NONE,
	FACE_LINE_TYPE_V,
	FACE_LINE_TYPE_VT,
	FACE_LINE_TYPE_VN,
	FACE_LINE_TYPE_VTN
}				t_face_line_type;

typedef void (*t_line_type_parser)(const char *line, t_obj_file *obj_file);

void parse_skip_line_type(const char *line, t_obj_file *obj_file);
void parse_vertex_line_type(const char *line, t_obj_file *obj_file);
void parse_texture_line_type(const char *line, t_obj_file *obj_file);
void parse_normal_line_type(const char *line, t_obj_file *obj_file);
void parse_face_line_type(const char *line, t_obj_file *obj_file);

t_obj_file *init_obj_file();
float parse_float_lt(const char *str, t_obj_file* obj_file, size_t *offset);
t_vec3i		parse_face_point(const char *str, t_face_line_type *flt_prev,
								t_obj_file *obj_file, size_t *offset);

#endif //PARSING_PRIVATE_H

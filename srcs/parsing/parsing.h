#ifndef PARSING_H
#define PARSING_H

#include "scop.h"

typedef struct	s_obj_file {
	float	*vertex_buffer_data;
	int		*index_buffer_data;
	size_t	index_count;
	size_t	vertex_count;
	int		has_textures;
	int		has_normals;
	t_err	err_type;
	t_vec3f	center_offset;
}				t_obj_data;

t_obj_data	*parse_obj_file(const char *filename);
void		free_obj(t_obj_data **obj_ptr);

#endif


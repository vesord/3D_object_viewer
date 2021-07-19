#include "parsing_private.h"
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

void parse_skip_line_type(const char *line, t_obj_data *obj_file)
{
	return ;
}

void parse_vertex_line_type(const char *line, t_obj_data *obj_file)
{
	t_vec4f vertex;
	size_t	offset;
	int		i;

	line += 2;
	i = -1;
	offset = 0;
	while (++i < 3)
		*(&(vertex.x) + i) = parse_float_lt(line + offset, obj_file, &offset);
	vertex.w = 1.f;
	push_back(&obj_file->vb, &vertex);
}

void parse_texture_line_type(const char *line, t_obj_data *obj_file)
{
	t_vec2f texture;
	size_t	offset;
	int		i;

	line += 3;
	i = -1;
	offset = 0;
	while (++i < 2)
		*(&(texture.x) + i) = parse_float_lt(line + offset, obj_file, &offset);
	push_back(&obj_file->tb, &texture);
}

void parse_normal_line_type(const char *line, t_obj_data *obj_file)
{
	t_vec3f normal;
	size_t	offset;
	int		i;

	line += 3;
	i = -1;
	offset = 0;
	while (++i < 3)
		*(&(normal.x) + i) = parse_float_lt(line + offset, obj_file, &offset);
	push_back(&obj_file->nb, &normal);
}

void parse_face_line_type(const char *line, t_obj_data *obj_file)
{
	int						points_count;
	t_vec3i					cur_index;
	size_t					offset;

	points_count = 0;
	line += 2;
	offset = 0;
	errno = 0;
	while (*(line + offset) != 0)
	{
		if (points_count > 2)
			make_triangulation(&obj_file->ib);
		cur_index = parse_face_point(line, &obj_file->flt,
									 obj_file, &offset);
		if (obj_file->err_type || errno)
			break;
		push_back(&obj_file->ib, &cur_index);
		++points_count;
		while (isspace(*(line + offset)))
			++offset;
	}
}


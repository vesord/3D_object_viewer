#include "parsing_private.h"
#include <math.h>
#include <stdio.h>

void parse_skip_line_type(const char *line, t_obj_file *obj_file)
{
	return ;
}

void parse_vertex_line_type(const char *line, t_obj_file *obj_file)
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
	save_vertex(vertex, obj_file);
}

void parse_texture_line_type(const char *line, t_obj_file *obj_file)
{
	t_vec2f texture;
	size_t	offset;
	int		i;

	line += 3;
	i = -1;
	offset = 0;
	while (++i < 2)
		*(&(texture.x) + i) = parse_float_lt(line + offset, obj_file, &offset);
	save_texture(texture, obj_file);
}

void parse_normal_line_type(const char *line, t_obj_file *obj_file)
{
	t_vec3f normal;
	size_t	offset;
	int		i;

	line += 3;
	i = -1;
	offset = 0;
	while (++i < 3)
		*(&(normal.x) + i) = parse_float_lt(line + offset, obj_file, &offset);
	save_normal(normalize_v3f(&normal), obj_file);
}

void parse_face_line_type(const char *line, t_obj_file *obj_file)
{
	int						points_count;
	t_vec3i					cur_index;
	static t_face_line_type	flt = FACE_LINE_TYPE_NONE;
	size_t					offset;

	points_count = 0;
	line += 2;
	offset = 0;
	while (*(line + offset) != 0)
	{
		if (points_count > 2)
			make_triangulation(obj_file);
		cur_index = parse_face_point(line + offset, &flt, obj_file, &offset);
		if (obj_file->err_type)
			break;
		save_index(cur_index);
		++points_count;
	}
}


#include "parsing_private.h"
#include <stdio.h>
#include <string.h>

/*
** Order of these functions must be the same as order of
** enum e_line_type in parsing_private.h
*/
const static t_line_type_parser g_lt_parsers[] = {
	parse_vertex_line_type,
	parse_texture_line_type,
	parse_normal_line_type,
	parse_face_line_type
};

t_line_type recognize_line_type(const char *line)
{
	size_t line_len;

	line_len = strlen(line);
	if (line_len < 3)
		return LINE_TYPE_SKIP;
	if (strncmp(line, "v ", 2) == 0)
		return LINE_TYPE_VERTEX;
	if (strncmp(line, "vt ", 3) == 0)
		return LINE_TYPE_TEXTURE;
	if (strncmp(line, "vn ", 3) == 0)
		return LINE_TYPE_NORMAL;
	if (strncmp(line, "f ", 2) == 0)
		return LINE_TYPE_FACE;
	return LINE_TYPE_SKIP;
}

t_err parse_line(const char *line, t_obj_file *obj_file)
{
	t_line_type line_type;

	line_type = recognize_line_type(line);
	g_lt_parsers[line_type](line, obj_file);
	return obj_file->err_type;
}

t_obj_file *parse_obj_file(const char *filename)
{
	t_obj_file	*res;
	FILE		*file;
	char		*line;

	res = init_obj_file(); // TODO: protect
	file = fopen(filename, "r"); // TODO: protect
	line = NULL;
	while (getline(&line, 0, file) >= 0)
	{
		if (parse_line(line, res) != ERR_NO_ERROR)
			break;
		free(line);
		line = NULL;
	}
	// TODO: check errno if getline fails
	if (res->err_type)
		fprintf(stderr, "Error while parsing file %s in line\n%s\n"
						"Error code: %iu\n", filename, line, res->err_type);
	free(line);
	return res;
}
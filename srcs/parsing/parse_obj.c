#include "parsing_private.h"
#include <stdio.h>
#include <string.h>

/*
** Order of these functions must be the same as order of
** enum e_line_type in parsing_private.h
*/
const static t_line_type_parser g_lt_parsers[] = {
	parse_skip_line_type,
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

t_err parse_line(const char *line, t_obj_data *obj_file)
{
	t_line_type line_type;

	line_type = recognize_line_type(line);
	g_lt_parsers[line_type](line, obj_file);
	return obj_file->err_type;
}

void parse_lines(const char *fname, FILE *file, t_obj_data *obj_file)
{
	char	*line;
	size_t	line_n;
	size_t	line_buf;

	line = NULL;
	line_buf = 0;
	line_n = 0;
	// TODO: reset errno
	while (getline(&line, &line_buf, file) >= 0)
	{
		if (parse_line(line, obj_file) != ERR_NO_ERROR)
			break;
		free(line);
		line = NULL;
		line_n++;
	}
	// TODO: check errno if getline fails
	if (obj_file->err_type)
		fprintf(stderr, "Error while parsing file %s in line %lu\n%s\n"
						"Error code: %iu\n",
						fname, line_n, line, obj_file->err_type);
	free(line);
}

t_obj_data *parse_obj_file(const char *filename)
{
	t_obj_data	*obj_data;
	FILE		*file;

	obj_data = create_obj_data(); // TODO: protect
	file = fopen(filename, "r"); // TODO: protect
	parse_lines(filename, file, obj_data);
	if (obj_data->err_type == ERR_NO_ERROR)
		fill_output_buffers(obj_data);
	return obj_data;
}
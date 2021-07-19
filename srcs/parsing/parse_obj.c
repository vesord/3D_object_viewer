#include "parsing_private.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

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
	errno = 0;
	while (getline(&line, &line_buf, file) >= 0)
	{
		if (parse_line(line, obj_file) != ERR_NO_ERROR)
			break;
		free(line);
		line = NULL;
		line_n++;
	}
	if (obj_file->err_type || errno)
		fprintf(stderr, "Error while parsing file %s in line %lu\n%s\n"
						"Error code: %i\n",
						fname, line_n, line, obj_file->err_type);
	free(line);
}

void		free_obj(t_obj_data **obj_ptr)
{
	if (!obj_ptr || !*obj_ptr)
		return ;
	buf_free(&(*obj_ptr)->vb);
	buf_free(&(*obj_ptr)->vb_out);
	buf_free(&(*obj_ptr)->tb);
	buf_free(&(*obj_ptr)->tb_out);
	buf_free(&(*obj_ptr)->nb);
	buf_free(&(*obj_ptr)->nb_out);
	buf_free(&(*obj_ptr)->ib);
	buf_free(&(*obj_ptr)->ib_out);
	free((*obj_ptr)->vertex_buffer_data);
	free((*obj_ptr)->index_buffer_data);
	free(*obj_ptr);
	*obj_ptr = NULL;
}

t_obj_data *parse_obj_file(const char *filename)
{
	t_obj_data	*obj_data;
	FILE		*file;

	errno = 0;
	if (!(obj_data = create_obj_data()))
		return NULL;
	if (!(file = fopen(filename, "r")))
	{
		fprintf(stderr, "Unable to open file: %s\n", filename);
		free_obj(&obj_data);
		return NULL;
	}
	parse_lines(filename, file, obj_data);
	if (obj_data->err_type == ERR_NO_ERROR)
		fill_output_data(obj_data);
	if (obj_data->err_type != ERR_NO_ERROR || errno)
	{
		fprintf(stderr, "Unable to read file. Error code: %d\n",
				obj_data->err_type);
		free_obj(&obj_data);
		return NULL;
	}
	fclose(file);
	return obj_data;
}
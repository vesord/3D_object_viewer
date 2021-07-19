#include "parsing_private.h"
#include <errno.h>
#include <ctype.h>
#include <string.h>

t_obj_data	*create_obj_data(void)
{
	t_obj_data *obj_data;

	if (!(obj_data = malloc(sizeof(t_obj_data))))
		return NULL;
	obj_data->vertex_buffer_data = NULL;
	obj_data->index_buffer_data = NULL;
	obj_data->index_buffer_count = 0;
	obj_data->vertex_buffer_count = 0;
	obj_data->has_normals = 0;
	obj_data->has_textures = 0;
	obj_data->err_type = ERR_NO_ERROR;
	buf_init(&obj_data->vb, sizeof(t_vec4f));
	buf_init(&obj_data->vb_out, sizeof(t_vec4f));
	buf_init(&obj_data->tb, sizeof(t_vec2f));
	buf_init(&obj_data->tb_out, sizeof(t_vec2f));
	buf_init(&obj_data->nb, sizeof(t_vec3f));
	buf_init(&obj_data->nb_out, sizeof(t_vec3f));
	buf_init(&obj_data->ib, sizeof(t_vec3i));
	buf_init(&obj_data->ib_out, sizeof(int));
	obj_data->flt = FACE_LINE_TYPE_NONE;
	return obj_data;
}

/*
**	works like strtof(), but sets obj_file->err_type if error occurs
**	rises an error if conversion did not done
**	rises an error if converting value is out of float range
*/
float		parse_float_lt(const char *str, t_obj_data *obj_file,
							size_t *offset)
{
	float	res;
	char	*end_ptr;

	errno = 0;
	res = strtof(str, &end_ptr);
	if (str == end_ptr || errno == ERANGE)
		obj_file->err_type = ERR_PARSING_OBJ_LINE_TYPE_V;
	*offset += end_ptr - str;
	return res;
}

/*
**	works like strtol(), but sets obj_file->err_type if error occurs
**	rises an error if converting value is out of int range
*/
int			parse_int_lt(const char *str, t_obj_data *obj_file, size_t *offset)
{
	long	convert_res;
	char	*end_ptr;

	convert_res = strtol(str, &end_ptr, 10);
	if (convert_res >= INT32_MAX || convert_res <= INT32_MIN || errno)
		obj_file->err_type = ERR_PARSING_OBJ_LINE_TYPE_F;
	*offset += end_ptr - str;
	return (int)convert_res;;
}

t_vec3i		parse_face_point(const char *str, t_face_line_type *flt_prev,
								t_obj_data *obj_file, size_t *offset)
{
	t_vec3i				indexes;
	t_face_line_type	flt_cur;
	int					i;

	while (isspace(*(str + *offset)))
		++*offset;
	i = -1;
	flt_cur = FACE_LINE_TYPE_NONE;
	while (++i < 3)
	{
		*(&(indexes.x) + i) = parse_int_lt(str + *offset, obj_file, offset);
		if (flt_cur == FACE_LINE_TYPE_NONE && i == 0 && *(str + *offset) != '/')
			flt_cur = FACE_LINE_TYPE_V;
		if (flt_cur == FACE_LINE_TYPE_NONE && i == 1 && *(str + *offset) != '/')
			flt_cur = FACE_LINE_TYPE_VT;
		if (flt_cur == FACE_LINE_TYPE_NONE && i == 2 && indexes.y == 0)
			flt_cur = FACE_LINE_TYPE_VN;
		if (flt_cur == FACE_LINE_TYPE_NONE && i == 2)
			flt_cur = FACE_LINE_TYPE_VTN;
		if (*(str + *offset) == '/')
			(*offset)++;
		if (isspace(*(str + *offset)))
			break ;
	}
	if (*flt_prev != FACE_LINE_TYPE_NONE && *flt_prev != flt_cur)
		obj_file->err_type = ERR_PARSING_OBJ_LINE_TYPE_F;
	*flt_prev = flt_cur;
	return indexes;
}

void		make_triangulation(t_buf *buf)
{
	void *data1;
	void *data2;

	data1 = malloc(buf->elem_size);
	data2 = malloc(buf->elem_size);
	if (errno)
		return ;
	memcpy(data1, ((char*)buf->data + (buf->count - 3) * buf->elem_size), buf->elem_size);
	memcpy(data2, ((char*)buf->data + (buf->count - 1) * buf->elem_size), buf->elem_size);

	push_back(buf, data1);
	push_back(buf, data2);
	free(data2);
	free(data1);
}


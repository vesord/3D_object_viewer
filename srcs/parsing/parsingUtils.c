//
// Created by vesord on 12.07.2021.
//

#include "parsing_private.h"
#include <errno.h>
#include <ctype.h>
#include <math.h>

t_obj_file	*init_obj_file(void)
{
	t_obj_file *obj_file;

	obj_file = malloc(sizeof(t_obj_file));	// TODO: protect
	obj_file->vertex_buffer_data = NULL;
	obj_file->index_buffer_data = NULL;
	obj_file->index_count = 0;
	obj_file->vertex_count = 0;
	obj_file->has_normals = 0;
	obj_file->has_textures = 0;
	obj_file->err_type = ERR_NO_ERROR;
	obj_file->textures_buffer = NULL;
	obj_file->normals_buffer = NULL;
}

/*
**	works like strtof(), but sets obj_file->err_type if error occurs
**	rises an error if conversion did not done
**	rises an error if converting value is out of float range
*/
float		parse_float_lt(const char *str, t_obj_file *obj_file,
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
int			parse_int_lt(const char *str, t_obj_file *obj_file, size_t *offset)
{
	long	convert_res;
	char	*end_ptr;

	convert_res = strtol(str, &end_ptr, 10);
	if (convert_res >= INT32_MAX || convert_res <= INT32_MIN)
		obj_file->err_type = ERR_PARSING_OBJ_LINE_TYPE_F;
	*offset += end_ptr - str;
	return (int)convert_res;;
}

t_vec3i		parse_face_point(const char *str, t_face_line_type *flt_prev,
						 t_obj_file *obj_file, size_t *offset)
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
	}
	if (flt_prev != FACE_LINE_TYPE_NONE && *flt_prev != flt_cur)
		obj_file->err_type = ERR_PARSING_OBJ_LINE_TYPE_F;
	*flt_prev = flt_cur;
	return indexes;
}
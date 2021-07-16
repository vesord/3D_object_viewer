#ifndef PARSING_H
#define PARSING_H

#include "scop.h"

typedef enum	e_face_line_type {
	FACE_LINE_TYPE_NONE,
	FACE_LINE_TYPE_V,
	FACE_LINE_TYPE_VT,
	FACE_LINE_TYPE_VN,
	FACE_LINE_TYPE_VTN
}				t_face_line_type;

// TODO: update obj_file_init()
typedef struct	s_obj_file {
	float				*vertex_buffer_data;
	int					*index_buffer_data;
	size_t				index_buffer_count;
	size_t				vertex_buffer_count;
	int					has_textures;
	int					has_normals;
	t_err				err_type;
	t_vec3f				center_offset;

	t_buf				vb;
	t_buf				tb;
	t_buf				nb;
	t_buf				ib;

	t_buf				vb_out;
	t_buf				tb_out;
	t_buf				nb_out;
	t_buf				ib_out;

	t_face_line_type	flt;
}				t_obj_data;

typedef enum	e_line_type {
	LINE_TYPE_SKIP,
	LINE_TYPE_VERTEX,
	LINE_TYPE_TEXTURE,
	LINE_TYPE_NORMAL,
	LINE_TYPE_FACE
}				t_line_type;

typedef void (*t_line_type_parser)(const char *line, t_obj_data *obj_file);

void parse_skip_line_type(const char *line, t_obj_data *obj_file);
void parse_vertex_line_type(const char *line, t_obj_data *obj_file);
void parse_texture_line_type(const char *line, t_obj_data *obj_file);
void parse_normal_line_type(const char *line, t_obj_data *obj_file);
void parse_face_line_type(const char *line, t_obj_data *obj_file);

t_obj_data *create_obj_data();
float parse_float_lt(const char *str, t_obj_data* obj_file, size_t *offset);
t_vec3i		parse_face_point(const char *str, t_face_line_type *flt_prev,
								t_obj_data *obj_file, size_t *offset);
void	make_triangulation(t_buf *buf);

void	fill_output_buffers(t_obj_data *od);

// VECTORS // TODO:change location??
void	push_back(t_buf *buf, void *data);
void	buf_init(t_buf *buf, size_t size);
void	*get_value(t_buf *buf, size_t index);
size_t	get_index(t_buf *buf, void *find);
void	buf_free(t_buf *buf);

#endif //PARSING_H

#include "parsing_private.h"
#include <string.h>

/*
** There could be more effective algorithm
** which takes more time but less memory
*/
static void	fill_buffers(t_obj_data *od)
{
	int i;

	i = -1;
	while (++i < od->ib.count) // TODO: check outofmemory
	{
		push_back(&od->vb_out, get_value(&od->vb, ((t_vec3i*)get_value(&od->ib, i))->x - 1));
		if (od->has_textures)
			push_back(&od->tb_out, get_value(&od->tb, ((t_vec3i*)get_value(&od->ib, i))->y - 1));
		if (od->has_normals)
			push_back(&od->nb_out, get_value(&od->nb, ((t_vec3i*)get_value(&od->ib, i))->z - 1));
		push_back(&od->ib_out, &i);
	}
	od->index_buffer_count = i;
	od->vertex_buffer_count = i;
}

static void	join_buffers(t_obj_data *od)
{
	size_t vbo_size;
	size_t tbo_size;
	size_t nbo_size;

	vbo_size = od->vb_out.elem_size * od->vb_out.count;
	tbo_size = od->tb_out.elem_size * od->tb_out.count;
	nbo_size = od->nb_out.elem_size * od->nb_out.count;

	od->vertex_buffer_data = malloc(vbo_size + tbo_size + nbo_size); // TODO: protect
	memcpy((char*)od->vertex_buffer_data, od->vb_out.data, vbo_size);
	memcpy((char*)od->vertex_buffer_data + vbo_size, od->tb_out.data, tbo_size);
	memcpy((char*)od->vertex_buffer_data + vbo_size + tbo_size, od->nb_out.data, nbo_size);
	od->index_buffer_data = od->ib_out.data;
}

/*
** od->ib_out is not freed cos of storing it's data
** into od->index_buffer_data
*/
static void	free_resourses(t_obj_data *od)
{
	buf_free(&od->vb);
	buf_free(&od->vb_out);
	buf_free(&od->tb);
	buf_free(&od->tb_out);
	buf_free(&od->nb);
	buf_free(&od->nb_out);
	buf_free(&od->ib);
}

void	fill_output_buffers(t_obj_data *od)
{
	if (od->flt == FACE_LINE_TYPE_VT || od->flt == FACE_LINE_TYPE_VTN)
		od->has_textures = 1;
	if (od->flt == FACE_LINE_TYPE_VN || od->flt == FACE_LINE_TYPE_VTN)
		od->has_normals = 1;
	fill_buffers(od);
	join_buffers(od);
	free_resourses(od);
}
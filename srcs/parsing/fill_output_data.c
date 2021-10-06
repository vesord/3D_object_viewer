#include "parsing_private.h"

#include <string.h>
#include <math.h>
#include <errno.h>

/*
** There could be more effective algorithm
** which takes more time but less memory
*/
static void	fill_buffers(t_obj_data *od)
{
	int i;

	i = -1;
	errno = 0;
	while (++i < (int)od->ib.count)
	{
		push_back(&od->vb_out, get_value(&od->vb, ((t_vec3i*)get_value(&od->ib, i))->x - 1));
		if (od->has_textures)
			push_back(&od->tb_out, get_value(&od->tb, ((t_vec3i*)get_value(&od->ib, i))->y - 1));
		if (od->has_normals)
			push_back(&od->nb_out, get_value(&od->nb, ((t_vec3i*)get_value(&od->ib, i))->z - 1));
		push_back(&od->ib_out, &i);
		if (errno)
			return ;
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

	od->vertex_buffer_data = malloc(vbo_size + tbo_size + nbo_size);
	if (errno)
		return ;
	memcpy((char*)od->vertex_buffer_data, od->vb_out.data, vbo_size);
	memcpy((char*)od->vertex_buffer_data + vbo_size, od->tb_out.data, tbo_size);
	memcpy((char*)od->vertex_buffer_data + vbo_size + tbo_size, od->nb_out.data, nbo_size);
	od->index_buffer_data = od->ib_out.data;
	buf_init(&od->ib_out, od->ib_out.elem_size);
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

static int is_perpendicular_to_xy(t_vec4f *p1, t_vec4f *p2, t_vec4f *p3)
{
	const float accur = 0.0001f;
	if ( (fabsf(p1->x - p2->x) <= accur && fabsf(p1->x - p3->x) <= accur)
			|| (fabsf(p1->y - p2->y) <= accur && fabsf(p1->y - p3->y) <= accur) )
		return 1;
	return 0;
}

static int is_perpendicular_to_yz(t_vec4f *p1, t_vec4f *p2, t_vec4f *p3)
{
	const float accur = 0.0001f;
	if ( (fabsf(p1->z - p2->z) <= accur && fabsf(p1->z - p3->z) <= accur)
		 || (fabsf(p1->y - p2->y) <= accur && fabsf(p1->y - p3->y) <= accur) )
		return 1;
	return 0;
}

static float ft_map_to_0_1(float value, float min, float max)
{
	if (min == max)
		return 0.5f;
	return (value - min) / (max - min);
}

static void map_tex_coord_to_xy(t_obj_data *od, t_vec4f *p1, t_vec4f *p2,
								t_vec4f *p3)
{
	t_vec2f tex_coord;

	tex_coord.x = ft_map_to_0_1(p1->x, od->min_coords.x, od->max_coords.x);
	tex_coord.y = ft_map_to_0_1(p1->y, od->min_coords.y, od->max_coords.y);
	push_back(&od->tb_out, &tex_coord);
	tex_coord.x = ft_map_to_0_1(p2->x, od->min_coords.x, od->max_coords.x);
	tex_coord.y = ft_map_to_0_1(p2->y, od->min_coords.y, od->max_coords.y);
	push_back(&od->tb_out, &tex_coord);
	tex_coord.x = ft_map_to_0_1(p3->x, od->min_coords.x, od->max_coords.x);
	tex_coord.y = ft_map_to_0_1(p3->y, od->min_coords.y, od->max_coords.y);
	push_back(&od->tb_out, &tex_coord);
}

static void map_tex_coord_to_yz(t_obj_data *od, t_vec4f *p1, t_vec4f *p2,
								t_vec4f *p3)
{
	t_vec2f tex_coord;

	tex_coord.x = ft_map_to_0_1(p1->z, od->min_coords.z, od->max_coords.z);
	tex_coord.y = ft_map_to_0_1(p1->y, od->min_coords.y, od->max_coords.y);
	push_back(&od->tb_out, &tex_coord);
	tex_coord.x = ft_map_to_0_1(p2->z, od->min_coords.z, od->max_coords.z);
	tex_coord.y = ft_map_to_0_1(p2->y, od->min_coords.y, od->max_coords.y);
	push_back(&od->tb_out, &tex_coord);
	tex_coord.x = ft_map_to_0_1(p3->z, od->min_coords.z, od->max_coords.z);
	tex_coord.y = ft_map_to_0_1(p3->y, od->min_coords.y, od->max_coords.y);
	push_back(&od->tb_out, &tex_coord);
}

static void map_tex_coord_to_xz(t_obj_data *od, t_vec4f *p1, t_vec4f *p2,
								t_vec4f *p3)
{
	t_vec2f tex_coord;

	tex_coord.x = ft_map_to_0_1(p1->x, od->min_coords.x, od->max_coords.x);
	tex_coord.y = ft_map_to_0_1(p1->z, od->min_coords.z, od->max_coords.z);
	push_back(&od->tb_out, &tex_coord);
	tex_coord.x = ft_map_to_0_1(p2->x, od->min_coords.x, od->max_coords.x);
	tex_coord.y = ft_map_to_0_1(p2->z, od->min_coords.z, od->max_coords.z);
	push_back(&od->tb_out, &tex_coord);
	tex_coord.x = ft_map_to_0_1(p3->x, od->min_coords.x, od->max_coords.x);
	tex_coord.y = ft_map_to_0_1(p3->z, od->min_coords.z, od->max_coords.z);
	push_back(&od->tb_out, &tex_coord);
}

static void	gen_texture_locations(t_obj_data *od)
{
    int i;
	t_vec4f *p1;
	t_vec4f *p2;
	t_vec4f *p3;

	od->has_textures = 1;
	i = -3;
	while ((i += 3) < (int)od->vertex_buffer_count)
	{
		p1 = get_value(&od->vb_out, i);
		p2 = get_value(&od->vb_out, i + 1);
		p3 = get_value(&od->vb_out, i + 2);
		if (is_perpendicular_to_xy(p1, p2, p3))
		{
			if (is_perpendicular_to_yz(p1, p2, p3))
			{
				map_tex_coord_to_xz(od, p1, p2, p3);
				continue ;
			}
			map_tex_coord_to_yz(od, p1, p2, p3);
			continue ;
		}
		map_tex_coord_to_xy(od, p1, p2, p3);
	}
}

void	fill_output_data(t_obj_data *od)
{
	if (od->flt == FACE_LINE_TYPE_VT || od->flt == FACE_LINE_TYPE_VTN)
		od->has_textures = 1;
	if (od->flt == FACE_LINE_TYPE_VN || od->flt == FACE_LINE_TYPE_VTN)
		od->has_normals = 1;
	fill_buffers(od);
	if (errno == ENOMEM)
		return ;
	calc_center_offset(od);
	if (od->has_textures == 0)
		gen_texture_locations(od);
	if (errno == ENOMEM)
		return ;
	join_buffers(od);
	if (errno == ENOMEM)
		return ;
	free_resourses(od);
	if (errno == EINVAL)
	    errno = 0;
}
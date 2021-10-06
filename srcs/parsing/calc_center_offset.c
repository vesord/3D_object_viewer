#include "parsing_private.h"
#include "types.h"

#include <math.h>

static void	check_mins(t_vec4f *val, t_vec3f *mins)
{
	if (val->x < mins->x)
		mins->x = val->x;
	if (val->y < mins->y)
		mins->y = val->y;
	if (val->z < mins->z)
		mins->z = val->z;
}

static void	check_maxs(t_vec4f *val, t_vec3f *maxs)
{
	if (val->x > maxs->x)
		maxs->x = val->x;
	if (val->y > maxs->y)
		maxs->y = val->y;
	if (val->z > maxs->z)
		maxs->z = val->z;
}

void		calc_center_offset(t_obj_data *obj)
{
	size_t i;

	obj->min_coords.x = HUGE_VALF;
	obj->min_coords.y = HUGE_VALF;
	obj->min_coords.z = HUGE_VALF;
	obj->max_coords.x = -HUGE_VALF;
	obj->max_coords.y = -HUGE_VALF;
	obj->max_coords.z = -HUGE_VALF;
	i = -1;
	while (++i < obj->vertex_buffer_count)
	{
		check_mins(((t_vec4f *)obj->vb_out.data + i), &obj->min_coords);
		check_maxs(((t_vec4f *)obj->vb_out.data + i), &obj->max_coords);
	}

	obj->center_offset.x = -(obj->min_coords.x + obj->max_coords.x) / 2;
	obj->center_offset.y = -(obj->min_coords.y + obj->max_coords.y) / 2;
	obj->center_offset.z = -(obj->min_coords.z + obj->max_coords.z) / 2;
}
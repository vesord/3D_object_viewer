#include "parsing.h"
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
	t_vec3f mins;
	t_vec3f maxs;
	int i;

	mins.x = HUGE_VALF;
	mins.y = HUGE_VALF;
	mins.z = HUGE_VALF;
	maxs.x = -HUGE_VALF;
	maxs.y = -HUGE_VALF;
	maxs.z = -HUGE_VALF;
	i = -1;
	while (++i < obj->vertex_count)
	{
		check_mins(((t_vec4f *)obj->vertex_buffer_data + i), &mins);
		check_maxs(((t_vec4f *)obj->vertex_buffer_data + i), &maxs);
	}
	obj->center_offset.x = -(mins.x + maxs.x) / 2;
	obj->center_offset.y = -(mins.y + maxs.y) / 2;
	obj->center_offset.z = -(mins.z + maxs.z) / 2;
}
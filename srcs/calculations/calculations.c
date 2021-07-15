#include "scop.h"
#include "scop_struct.h"
#include <math.h>
#include <string.h>

void stationary_offset(t_mat4f *model_to_cam) {
	memset(model_to_cam, 0, sizeof(*model_to_cam));

	// Identity matrix
	model_to_cam->x.x = 1.f;
	model_to_cam->y.y = 1.f;
	model_to_cam->z.z = 1.f;
	model_to_cam->w.w = 1.f;

	// Stationary offset
	model_to_cam->w.x = 0.f;
	model_to_cam->w.y = 0.f;
	model_to_cam->w.z = -100.f;
}

static t_mat4f get_auto_rotation_matrix()
{
	static const float	deg_per_frame = 1.f;
	static const float	rad_to_deg = 3.14159265f * 2.f / 360.f;
	t_mat4f				rot_y_mat;

	memset(&rot_y_mat, 0, sizeof(rot_y_mat));
	rot_y_mat.x.x = cosf(rad_to_deg * deg_per_frame);
	rot_y_mat.z.x = -sinf(rad_to_deg * deg_per_frame);
	rot_y_mat.x.z = sinf(rad_to_deg * deg_per_frame);
	rot_y_mat.z.z = cosf(rad_to_deg * deg_per_frame);
	rot_y_mat.y.y = 1.f;
	rot_y_mat.w.w = 1.f;
	return rot_y_mat;
}

t_mat4f mat_mult_m4_m4(t_mat4f *m1, t_mat4f *m2)
{
	t_mat4f res;

	res.x.x = m1->x.x * m2->x.x + m1->y.x * m2->x.y + m1->z.x * m2->x.z + m1->w.x * m2->x.w;
	res.x.y = m1->x.y * m2->x.x + m1->y.y * m2->x.y + m1->z.y * m2->x.z + m1->w.y * m2->x.w;
	res.x.z = m1->x.z * m2->x.x + m1->y.z * m2->x.y + m1->z.z * m2->x.z + m1->w.z * m2->x.w;
	res.x.w = m1->x.w * m2->x.x + m1->y.w * m2->x.y + m1->z.w * m2->x.z + m1->w.w * m2->x.w;

	res.y.x = m1->x.x * m2->y.x + m1->y.x * m2->y.y + m1->z.x * m2->y.z + m1->w.x * m2->y.w;
	res.y.y = m1->x.y * m2->y.x + m1->y.y * m2->y.y + m1->z.y * m2->y.z + m1->w.y * m2->y.w;
	res.y.z = m1->x.z * m2->y.x + m1->y.z * m2->y.y + m1->z.z * m2->y.z + m1->w.z * m2->y.w;
	res.y.w = m1->x.w * m2->y.x + m1->y.w * m2->y.y + m1->z.w * m2->y.z + m1->w.w * m2->y.w;

	res.z.x = m1->x.x * m2->z.x + m1->y.x * m2->z.y + m1->z.x * m2->z.z + m1->w.x * m2->z.w;
	res.z.y = m1->x.y * m2->z.x + m1->y.y * m2->z.y + m1->z.y * m2->z.z + m1->w.y * m2->z.w;
	res.z.z = m1->x.z * m2->z.x + m1->y.z * m2->z.y + m1->z.z * m2->z.z + m1->w.z * m2->z.w;
	res.z.w = m1->x.w * m2->z.x + m1->y.w * m2->z.y + m1->z.w * m2->z.z + m1->w.w * m2->z.w;

	res.w.x = m1->x.x * m2->w.x + m1->y.x * m2->w.y + m1->z.x * m2->w.z + m1->w.x * m2->w.w;
	res.w.y = m1->x.y * m2->w.x + m1->y.y * m2->w.y + m1->z.y * m2->w.z + m1->w.y * m2->w.w;
	res.w.z = m1->x.z * m2->w.x + m1->y.z * m2->w.y + m1->z.z * m2->w.z + m1->w.z * m2->w.w;
	res.w.w = m1->x.w * m2->w.x + m1->y.w * m2->w.y + m1->z.w * m2->w.z + m1->w.w * m2->w.w;
	return res;
}

void update_model_to_cam(t_matrices *mat)
{
	mat->transf.strp = mat_mult_m4_m4(&mat->transf.translate, &mat->transf.rotate);
	mat->transf.strp = mat_mult_m4_m4(&mat->transf.scale, &mat->transf.strp);
	mat->model_to_cam = mat->transf.strp;
}

void auto_rotation(t_matrices *mat)
{
	t_mat4f rot_mat;

	rot_mat = get_auto_rotation_matrix();
	mat->transf.rotate = mat_mult_m4_m4(&rot_mat, &mat->transf.rotate);
}


float calc_frustum_scale(float fov_deg) {
	const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
	float fov_rad = fov_deg * deg_to_rad;
	return 1.0f / tanf(fov_rad / 2.0f);
}

void check_mins(t_vec4f *val, t_vec3f *mins)
{
	if (val->x < mins->x)
		mins->x = val->x;
	if (val->y < mins->y)
		mins->y = val->y;
	if (val->z < mins->z)
		mins->z = val->z;
}

void check_maxs(t_vec4f *val, t_vec3f *maxs)
{
	if (val->x > maxs->x)
		maxs->x = val->x;
	if (val->y > maxs->y)
		maxs->y = val->y;
	if (val->z > maxs->z)
		maxs->z = val->z;
}

void calc_center_offset(t_obj_data *obj)
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

void translate(t_mat4f *mat, t_vec3f *offset)
{
	mat->w.x += offset->x;
	mat->w.y += offset->y;
	mat->w.z += offset->z;
}

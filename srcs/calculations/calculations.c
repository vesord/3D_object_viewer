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

void update_srtp(t_transform *tr)
{
	tr->strp = mat_mult_m4_m4(&tr->translate, &tr->rotate);
	tr->strp = mat_mult_m4_m4(&tr->scale, &tr->strp);
}

void auto_rotation(t_matrices *mat)
{
	t_mat4f rot_mat;

	rot_mat = get_auto_rotation_matrix();
	mat->transf.rotate = mat_mult_m4_m4(&rot_mat, &mat->transf.rotate);
	update_srtp(&mat->transf);
	mat->model_to_cam = mat->transf.strp;
}


float calc_frustum_scale(float fov_deg) {
	const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
	float fov_rad = fov_deg * deg_to_rad;
	return 1.0f / tanf(fov_rad / 2.0f);
}

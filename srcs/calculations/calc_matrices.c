#include "scop.h"
#include "types.h"
#include "scop_struct.h"

#include <string.h>
#include <math.h>

static const t_mat4f g_identity_matrix = {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};

void get_rot_mat(t_mat4f *rot_mat, t_vec3f vec, GLfloat angle) {
	memcpy(rot_mat, &g_identity_matrix, sizeof(g_identity_matrix));
	GLfloat cos_ang = cosf(angle);
	GLfloat sin_ang = sinf(angle);

//	rot_mat->r1.x = cos_ang + (1 - cos_ang) * vec.x * vec.x;
//	rot_mat->r1.y = (1 - cos_ang) * vec.x * vec.y - sin_ang * vec.z;
//	rot_mat->r1.z = (1 - cos_ang) * vec.x * vec.z + sin_ang * vec.y;

	rot_mat->x.x = cos_ang + (1 - cos_ang) * vec.x * vec.x;
	rot_mat->y.x = (1 - cos_ang) * vec.x * vec.y - sin_ang * vec.z;
	rot_mat->z.x = (1 - cos_ang) * vec.x * vec.z + sin_ang * vec.y;
	rot_mat->x.y = (1 - cos_ang) * vec.y * vec.x + sin_ang * vec.z;
	rot_mat->y.y = cos_ang + (1 - cos_ang) * vec.y * vec.y;
	rot_mat->z.y = (1 - cos_ang) * vec.y * vec.z - sin_ang * vec.x;
	rot_mat->x.z = (1 - cos_ang) * vec.z * vec.x - sin_ang * vec.y;
	rot_mat->y.z	= (1 - cos_ang) * vec.z * vec.y + sin_ang * vec.x;
	rot_mat->z.z = cos_ang + (1 - cos_ang) * vec.z * vec.z;
}

t_mat4f			mat_mult_m4_m4(t_mat4f *m1, t_mat4f *m2)
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

void			mat_rotate_around(t_mat4f *mat, const t_vec3f *vec, float angle)
{
	t_mat4f rot_mat;

	get_rot_mat(&rot_mat, *vec, angle);
	*mat = mat_mult_m4_m4(&rot_mat, mat);
}

void			auto_rotation(t_matrices *mat)
{
	static const float	deg_per_frame = 1.f;
	static const float	rad_to_deg = 3.14159265f * 2.f / 360.f;
	t_vec3f xz_normal;

	xz_normal.x = 0.f;
	xz_normal.y = 1.f;
	xz_normal.z = 0.f;
	mat_rotate_around(&mat->transf.rotate, &xz_normal, deg_per_frame * rad_to_deg);
}

void			translate(t_mat4f *mat, t_vec3f *offset)
{
	mat->w.x += offset->x;
	mat->w.y += offset->y;
	mat->w.z += offset->z;
}
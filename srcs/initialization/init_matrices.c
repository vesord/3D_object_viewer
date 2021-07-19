#include "scop.h"
#include "scop_struct.h"
#include "calculations.h"

#include <string.h>

static const t_mat4f g_identity_matrix = {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};

static void	init_cam_to_clip_matrix(t_mat4f *cam_to_clip)
{
	static const float	z_near = 1.f;
	static const float	z_far = 4500.f;
	static const float	fov_deg = 45.f;
	float 				frustum_scale;

	frustum_scale = calc_frustum_scale(fov_deg);
	memcpy(cam_to_clip, &g_identity_matrix, sizeof(t_mat4f));
	cam_to_clip->x.x = frustum_scale;
	cam_to_clip->y.y = frustum_scale;
	cam_to_clip->z.z = (z_far + z_near) / (z_near - z_far);
	cam_to_clip->z.w = -1;
	cam_to_clip->w.z = (2 * z_far * z_near) / (z_near - z_far);
}

static void	init_model_to_cam_matrix(t_mat4f *model_to_cam)
{
	memcpy(model_to_cam, &g_identity_matrix, sizeof(t_mat4f));
}

void		init_transform(t_transform *transform)
{
	memcpy(&transform->scale, &g_identity_matrix, sizeof(t_mat4f));
	memcpy(&transform->translate, &g_identity_matrix, sizeof(t_mat4f));
	memcpy(&transform->rotate, &g_identity_matrix, sizeof(t_mat4f));
	memcpy(&transform->strp, &g_identity_matrix, sizeof(t_mat4f));
	transform->translate.w.z = -10.f;
	transform->strp.w.z = -10.f;
}

void init_matrices(t_matrices *mat)
{
	init_cam_to_clip_matrix(&mat->cam_to_clip);
	init_model_to_cam_matrix(&mat->model_to_cam);
	init_transform(&mat->transf);
	memcpy(&mat->center_translate, &g_identity_matrix, sizeof(t_mat4f));
}
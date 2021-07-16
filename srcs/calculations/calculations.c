#include "calculations.h"
#include "scop_struct.h"

#include <math.h>

void	update_model_to_cam(t_matrices *mat)
{
	mat->transf.strp = mat_mult_m4_m4(&mat->transf.translate,
									  &mat->transf.rotate);
	mat->transf.strp = mat_mult_m4_m4(&mat->transf.scale, &mat->transf.strp);
	mat->model_to_cam = mat->transf.strp;
}

float	calc_frustum_scale(float fov_deg) {
	const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
	float fov_rad = fov_deg * deg_to_rad;
	return 1.0f / tanf(fov_rad / 2.0f);
}

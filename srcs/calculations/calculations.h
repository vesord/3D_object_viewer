#ifndef CALCULATIONS_H
# define CALCULATIONS_H

# include "scop_struct.h"

void	auto_rotation(t_matrices *mat);
float	calc_frustum_scale(float fov_deg);
void	update_model_to_cam(t_matrices *mat);
void	translate(t_mat4f *mat, t_vec3f *offset);
t_mat4f	mat_mult_m4_m4(t_mat4f *m1, t_mat4f *m2);
void	mat_rotate_around(t_mat4f *mat, const t_vec3f *vec, float angle);

#endif

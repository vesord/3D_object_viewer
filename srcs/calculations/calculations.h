#ifndef SCOP_CALCULATIONS_H
#define SCOP_CALCULATIONS_H

#include "scop_struct.h"

void stationary_offset(t_mat4f *model_to_cam);
void auto_rotation(t_matrices *mat);
float calc_frustum_scale(float fov_deg);

#endif //SCOP_CALCULATIONS_H

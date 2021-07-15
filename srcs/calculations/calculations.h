#ifndef SCOP_CALCULATIONS_H
#define SCOP_CALCULATIONS_H

#include "scop_struct.h"

void auto_rotation(t_matrices *mat);
float calc_frustum_scale(float fov_deg);
void update_model_to_cam(t_matrices *mat);
void calc_center_offset(t_obj_data *obj);
void translate(t_mat4f *mat, t_vec3f *offset);

#endif //SCOP_CALCULATIONS_H

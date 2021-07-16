#ifndef INITIALIZATION_PRIVATE_H
# define INITIALIZATION_PRIVATE_H

#include "scop_struct.h"

void init_fail(const char *err_msg);

void create_window(GLFWwindow **window);
void init_glfw();
void init_glew();
void init_viewport(GLFWwindow *window);
void init_culling();
void init_depth();
void init_matrices(t_matrices *mat);
void init_transform(t_transform *transform);
void init_scop(t_scop *scop);

#endif

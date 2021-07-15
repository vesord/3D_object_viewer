#ifndef SCOP_EVENTS_PRIVATE_H
#define SCOP_EVENTS_PRIVATE_H

#include "scop.h"
#include "scop_struct.h"

t_scop *get_scop(t_scop* scop_ptr);
void key_callback(GLFWwindow* w, int key, int scancode, int action, int mode);
void reshape_callback(GLFWwindow* w, int width, int height);

#endif //SCOP_EVENTS_PRIVATE_H

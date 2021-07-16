#ifndef SCOP_INITIALIZATION_H
#define SCOP_INITIALIZATION_H

#include "scop_struct.h"

void init_fail(const char *err_msg);
void initialization(t_scop *scop);
void init_transform(t_transform *transform);

#endif //SCOP_INITIALIZATION_H

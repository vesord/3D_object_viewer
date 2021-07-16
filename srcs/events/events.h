#ifndef SCOP_EVENTS_H
#define SCOP_EVENTS_H

void register_callbacks(GLFWwindow *window);
void process_keys(t_scop *scop);
void poll_terminal();

#endif //SCOP_EVENTS_H

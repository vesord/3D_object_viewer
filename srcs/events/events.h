#ifndef EVENTS_H
# define EVENTS_H

void register_callbacks(GLFWwindow *window);
void process_keys(t_scop *scop);
void poll_terminal();

#endif

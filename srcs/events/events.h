#ifndef EVENTS_H
# define EVENTS_H

void register_callbacks(GLFWwindow *window);
void process_keys(t_scop *scop);
void poll_terminal();
void term_show_help();
void term_open_obj(const char *filename);
void term_open_texture(const char *filename);

#endif

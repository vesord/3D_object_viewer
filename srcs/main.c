#include "scop.h"
#include "initialization.h"
#include "display.h"
#include "events.h"

t_scop		*get_scop(t_scop* scop_ptr)
{
	static t_scop *scop;

	if (!scop && scop_ptr)
		scop = scop_ptr;
	return scop;
}

int			main(int argc, char **argv)
{
	t_scop scop;

	// todo: remove it
	(void)argc;
	(void)argv;

	initialization(&scop);
	get_scop(&scop);
	term_open_obj("./models/42.obj");
	term_open_texture("./textures/pony.bmp");
	term_show_help();
	display(&scop);
	glfwTerminate();
	return 0;
}

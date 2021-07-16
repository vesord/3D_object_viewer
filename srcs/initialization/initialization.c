#include "scop.h"
#include "scop_struct.h"
#include "initialization_private.h"
#include "events.h"

#include <stdio.h>
#include <fcntl.h>

void	init_fail(const char *err_msg)
{
	fprintf(stderr, "%s\n", err_msg);
	glfwTerminate();
	exit(1);
}

int		try_init_terminal(void)
{
	static const int	stdin_fd = 0;
	int					flags;

	flags = fcntl(stdin_fd, F_GETFL, 0);
	if (flags < 0)
		return 0;
	flags = flags | O_NONBLOCK;
	if (fcntl(stdin_fd, F_SETFL, flags) == 0)
		return 1;
	return 0;
}

void	initialization(t_scop *scop)
{
	init_glfw();
	create_window(&scop->window);
	init_glew();
	init_viewport(scop->window);
	init_culling();
	init_depth();
	register_callbacks(scop->window);
	init_scop(scop);
	if (!try_init_terminal())
		init_fail("Failed to set terminal nonblocking");
}

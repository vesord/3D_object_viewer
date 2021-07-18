#include "events_private.h"

static void	process_keys_moving(t_scop *scop)
{
	if (scop->keys.up)
		scop->mat.transf.translate.w.y -= scop->state.moving_step;
	if (scop->keys.down)
		scop->mat.transf.translate.w.y += scop->state.moving_step;
	if (scop->keys.right)
		scop->mat.transf.translate.w.x -= scop->state.moving_step;
	if (scop->keys.left)
		scop->mat.transf.translate.w.x += scop->state.moving_step;
	if (scop->keys.forward)
		scop->mat.transf.translate.w.z += scop->state.moving_step;
	if (scop->keys.back)
		scop->mat.transf.translate.w.z -= scop->state.moving_step;
}

static void	process_keys_drawing(t_scop *scop)
{
	if (scop->keys.draw_triangles)
	{
		scop->keys.draw_triangles = 0;
		scop->state.draw_type = GL_TRIANGLES;
	}
	if (scop->keys.draw_lines)
	{
		scop->keys.draw_lines = 0;
		scop->state.draw_type = GL_LINES;
	}
	if (scop->keys.draw_points)
	{
		scop->keys.draw_points = 0;
		scop->state.draw_type = GL_POINTS;
	}
}

void		process_keys(t_scop *scop)
{
	process_keys_moving(scop);
	process_keys_drawing(scop);
	if (scop->keys.enable_rotation)
	{
		scop->keys.enable_rotation = 0;
		scop->state.enable_rotation = !scop->state.enable_rotation;
	}
	if (scop->keys.apply_texture)
	{
		scop->keys.apply_texture = 0;
		scop->state.shading_type = !scop->state.shading_type;
	}
	// TODO: culling
}
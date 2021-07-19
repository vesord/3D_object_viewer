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

static void	process_render_type(t_scop *scop)
{
	if (scop->keys.render_triangles)
	{
		scop->keys.render_triangles = 0;
		scop->state.shading_type = 0;
	}
	if (scop->keys.render_texture)
	{
		scop->keys.render_texture = 0;
		scop->state.shading_type = 1;
	}
	if (scop->keys.render_light)
	{
		scop->keys.render_light = 0;
		scop->state.shading_type = 2;
	}
	if (scop->keys.render_textured_light)
	{
		scop->keys.render_textured_light = 0;
		scop->state.shading_type = 3;
	}
}


void		process_keys(t_scop *scop)
{
	process_keys_moving(scop);
	process_keys_drawing(scop);
	process_render_type(scop);
	if (scop->keys.enable_rotation)
	{
		scop->keys.enable_rotation = 0;
		scop->state.enable_rotation = !scop->state.enable_rotation;
	}
	if (scop->keys.move_increase)
	{
		scop->keys.move_increase = 0;
		scop->state.moving_step *= 2;
	}
	if (scop->keys.move_decrease)
	{
		scop->keys.move_decrease = 0;
		scop->state.moving_step /= 2;
		if (scop->state.moving_step < 0.01f)
			scop->state.moving_step = 0.01f;
	}
	// TODO: culling
}
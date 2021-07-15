#include "events_private.h"

void process_keys(t_scop *scop)
{
	const float step = 0.1f;

	if (scop->keys.up)
		scop->mat.transf.translate.w.y -= step;
	if (scop->keys.down)
		scop->mat.transf.translate.w.y += step;
	if (scop->keys.right)
		scop->mat.transf.translate.w.x -= step;
	if (scop->keys.left)
		scop->mat.transf.translate.w.x += step;
	if (scop->keys.forward)
		scop->mat.transf.translate.w.z += step;
	if (scop->keys.back)
		scop->mat.transf.translate.w.z -= step;
	if (scop->keys.enable_rotation)
	{
		scop->keys.enable_rotation = 0;
		scop->state.enable_rotation = !scop->state.enable_rotation;
	}
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
	// TODO: culling
}
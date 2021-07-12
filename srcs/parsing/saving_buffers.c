#include "parsing_private.h"

void save_vertex(t_vec4f vertex, t_obj_file *of)
{
	if (of->vertex_buffer_data == NULL)
	{
		of->vertex_buffer_data = malloc(sizeof(vertex) * 1024); // TODO: protect
		of->vertex_buffer_size = 1024;
	}
	if (of->vertex_buffer_size == of->vertex_count)
	{
		of->vertex_buffer_data = realloc(of->vertex_buffer_data,
										 of->vertex_buffer_size * 2); // TODO: protect
		of->vertex_buffer_size *= 2;
	}
	((t_vec4f*)of->vertex_buffer_data)[of->vertex_count++] = vertex;
}

void save_texture(t_vec2f texture, t_obj_file *of)
{
	if (of->textures_buffer == NULL)
	{
		of->textures_buffer = malloc(sizeof(texture) * 1024); // TODO: protect
		of->textures_buffer_size = 1024;
	}
	if (of->textures_buffer_size == of->textures_count)
	{
		of->textures_buffer = realloc(of->textures_buffer,
									  of->textures_buffer_size * 2);
		of->textures_buffer_size *= 2;
	}
	of->textures_buffer[of->textures_count++] = texture;
}

void save_normal(t_vec3f normal, t_obj_file *of)
{
	if (of->normals_buffer == NULL)
	{
		of->normals_buffer = malloc(sizeof(normal) * 1024); // TODO: protect
		of->normals_buffer_size = 1024;
	}
	if (of->normals_buffer_size == of->normals_count)
	{
		of->normals_buffer = realloc(of->normals_buffer,
									  of->normals_buffer_size * 2);
		of->normals_buffer_size *= 2;
	}
	of->normals_buffer[of->normals_count++] = normal;
}

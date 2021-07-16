#include "scop.h"
#include "parsing.h"

void set_buf_data_from_obj(t_obj_data *obj, GLuint vbo, GLuint ibo)
{
	size_t vertex_size;

	vertex_size = sizeof(t_vec4f);
	if (obj->has_normals)
		vertex_size += sizeof(t_vec3f);
	if (obj->has_textures)
		vertex_size += sizeof(t_vec2f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, obj->vertex_count * vertex_size,
				 obj->vertex_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * obj->index_count,
				 obj->index_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void set_vao_for_obj(t_obj_data *obj, GLuint vao, GLuint vbo, GLuint ibo)
{
	glBindVertexArray(vao);
	size_t tex_data_offset = sizeof(t_vec4f) * obj->vertex_count
							 * obj->has_textures;
	size_t norm_data_offset = sizeof(t_vec2f) * obj->vertex_count
							  * obj->has_normals + tex_data_offset;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	if (obj->has_textures)
		glEnableVertexAttribArray(1);
	if (obj->has_normals)
		glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)tex_data_offset);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)norm_data_offset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindVertexArray(0);
}
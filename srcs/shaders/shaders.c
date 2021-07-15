#include "scop.h"
#include "scop_struct.h"
#include "shader_private.h"
#include "initialization.h"

void	update_uniforms_locations(t_shaders *shaders)
{
	shaders->cam_to_clip_unif = glGetUniformLocation(shaders->cur, "camera_to_clip_matrix");
	shaders->model_to_cam_unif = glGetUniformLocation(shaders->cur, "model_to_camera_matrix");
}

GLuint create_shader(GLenum shader_type, const GLchar** strShaderFile)
{
	GLuint shader;

	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, strShaderFile, NULL);
	glCompileShader(shader);
	if (!is_shader_ok(shader, shader_type))
		init_fail("Failed to create shader");
	return shader;
}

GLuint create_shader_program(GLuint *shader_list) {
	GLuint shader_program;

	shader_program = glCreateProgram();
	attach_shaders(shader_program, shader_list);
	glLinkProgram(shader_program);
	if (!is_shader_program_ok(shader_program))
		init_fail("Failed to create shader program");
	free_shaders(shader_program, shader_list);
	return shader_program;
}

GLuint create_shader_program_vert_frag(const char *vert_shader_src,
									 const char *frag_shader_src) {
	GLuint *shader_list;
	GLuint shader_program;

	if (! (shader_list = malloc(sizeof(GLuint) * 3)))
		init_fail("Not enough memory");
	shader_list[0] = create_shader(GL_VERTEX_SHADER, &vert_shader_src);
	shader_list[1] = create_shader(GL_FRAGMENT_SHADER, &frag_shader_src);
	shader_list[2] = 0;
	shader_program = create_shader_program(shader_list);
	free(shader_list);
	return shader_program;
}

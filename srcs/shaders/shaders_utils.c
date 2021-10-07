#include "scop.h"
#include "initialization.h"

#include <stdio.h>
#include <string.h>

static const char *g_vertex_shader_type_str = "vertex";
static const char *g_geometry_shader_type_str = "geometry";
static const char *g_fragment_shader_type_str = "fragment";

void	attach_shaders(GLuint shader_program, GLuint *shader_list)
{
	while (*shader_list)
	{
		glAttachShader(shader_program, *shader_list);
		++shader_list;
	}
}

void	free_shaders(GLuint shader_program, GLuint *shader_list)
{
	while (*shader_list)
	{
		glDetachShader(shader_program, *shader_list);
		glDeleteShader(*shader_list);
		++shader_list;
	}
}

int		is_shader_ok(GLuint shader, GLenum shader_type)
{
	GLint status;
	GLint infoLogLength;
	GLchar *str_info_log;
	const char *str_shader_type;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (! (str_info_log = malloc(infoLogLength)) )
			init_fail("Not enough memory\n");
		glGetShaderInfoLog(shader, infoLogLength, NULL, str_info_log);
		if (shader_type == GL_VERTEX_SHADER)
			str_shader_type = g_vertex_shader_type_str;
		if (shader_type == GL_GEOMETRY_SHADER)
			str_shader_type = g_geometry_shader_type_str;
		if (shader_type == GL_FRAGMENT_SHADER)
			str_shader_type = g_fragment_shader_type_str;
		fprintf(stderr, "Compile failure in %s shader:\n%s\n",
				str_shader_type, str_info_log);
		free(str_info_log);
		return 0;
	}
	return 1;
}

int		is_shader_program_ok(GLuint shader_program)
{
	GLint	success;
	GLint	info_log_len;
	char	*info_log;

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_log_len);
		if (! (info_log = malloc(info_log_len)))
			init_fail("Not enough memory");
		glGetProgramInfoLog(shader_program, info_log_len, NULL, info_log);
		printf("Linker failure: %s", info_log);
		free(info_log);
		return 0;
	}
	return 1;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = strlen(s1) + strlen(s2);
	newstr = (char *)malloc(sizeof(*newstr) * (len + 1));
	if (!newstr)
		return (NULL);
	newstr[len] = 0;
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	return (newstr);
}

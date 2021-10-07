#ifndef SHADER_PRIVATE_H
# define SHADER_PRIVATE_H

# include "scop.h"

void	attach_shaders(GLuint shader_program, GLuint *shader_list);
void	free_shaders(GLuint shader_program, GLuint *shader_list);
int		is_shader_ok(GLuint shader, GLenum shader_type);
int		is_shader_program_ok(GLuint shader_program);
char	*ft_strjoin(char const *s1, char const *s2);

#endif

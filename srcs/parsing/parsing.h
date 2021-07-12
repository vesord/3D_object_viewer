#ifndef PARSING_H
#define PARSING_H

#include "scop.h"

typedef struct	s_objFile {
	float	*vertexBufferData;
	int		*indexBufferData;
	int		hasTextures;
	int		hasNormals;
	size_t	indexCount;
	size_t	vertexCount;
	t_err	wasError;
}				t_obj_file;

#endif


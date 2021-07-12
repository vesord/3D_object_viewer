//
// Created by vesord on 12.07.2021.
//

#ifndef TYPES_H
#define TYPES_H

typedef struct	s_vec3i {
	int x;
	int y;
	int z;
}				t_vec3i;

typedef struct	s_vec2f {
	float x;
	float y;
}				t_vec2f;

typedef struct	s_vec3f {
	float x;
	float y;
	float z;
}				t_vec3f;

typedef struct	s_vec4f {
	float x;
	float y;
	float z;
	float w;
}				t_vec4f;

typedef enum	e_error_codes {
	ERR_NO_ERROR,
	ERR_PARSING_OBJ_LINE_TYPE_V,
	ERR_PARSING_OBJ_LINE_TYPE_F
}				t_err;

#endif //TYPES_H

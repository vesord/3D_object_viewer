//
// Created by vesord on 10.07.2021.
//

#ifndef SCOP_SHADERS_H
#define SCOP_SHADERS_H

#include "scop.h"

GLuint makeTestShaderProgram();	/// TEST FUNCTION

// Defs for moving makeShaderProgram to main.c
#include "vertexShaders.h"
#include "fragmentShaders.h"
GLuint CreateShaderProgram(GLuint *shaderList);
GLuint CreateShader(GLenum eShaderType, const GLchar** strShaderFile);


#endif //SCOP_SHADERS_H

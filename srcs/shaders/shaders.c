//
// Created by vesord on 10.07.2021.
//

#include "scop.h"
//#include "vertexShaders.h"
//#include "fragmentShaders.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

GLuint CreateShader(GLenum eShaderType, const GLchar** strShaderFile)
{
	GLuint shader = glCreateShader(eShaderType);
	glShaderSource(shader, 1, strShaderFile, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = malloc(infoLogLength);
		if (!strInfoLog) {
			exit(1);
		}
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(eShaderType)
		{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			default: ;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		free(strInfoLog);
	}
	return shader;
}

GLuint CreateShaderProgram(GLuint *shaderList) {
	// Make shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	// Attaching shader program
	GLuint *shaderListIter = shaderList;
	while (*shaderListIter) {
		glAttachShader(shaderProgram, *shaderListIter);
		++shaderListIter;
	}

	// Linking shaders
	glLinkProgram(shaderProgram);

	// Check if program attached and linked successfully
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = malloc(infoLogLength);
		if (!infoLog) {
			exit(1);
		}
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog);
		printf("Linker failure: %s", infoLog);
		free(infoLog);
	}
	shaderListIter = shaderList;
	while (*shaderListIter) {
		glDetachShader(shaderProgram, *shaderListIter);
		glDeleteShader(*shaderListIter);
		++shaderListIter;
	}
	return shaderProgram;
}

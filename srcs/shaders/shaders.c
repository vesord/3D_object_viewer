//
// Created by vesord on 10.07.2021.
//

#include "scop.h"
#include "vertexShaders.h"
#include "fragmentShaders.h"
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

/// TEST FUNCTION
GLuint makeTestShaderProgram() {
	GLuint *shaderList;

	shaderList = malloc(sizeof(GLuint) * 3);
	if (!shaderList) {
		exit(1);
	}
	shaderList[0] = CreateShader(GL_VERTEX_SHADER, &vertexShaderSrcManualPerspective);
	shaderList[1] = CreateShader(GL_FRAGMENT_SHADER, &fragmentShaderSrcSmoothColor);
	shaderList[2] = 0;

	float frustumScale = 1.f; float zFar = 3.f; float zNear = 1.f;
	float perspectiveMatrix[16];
	memset(perspectiveMatrix, 0, sizeof(float) * 16);

	perspectiveMatrix[0] = frustumScale;
	perspectiveMatrix[5] = frustumScale;
	perspectiveMatrix[10] = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[11] = -1.f;
	perspectiveMatrix[14] = (2 * zFar * zNear) / (zNear - zFar);

	GLuint shaderProgram = CreateShaderProgram(shaderList);

	GLint perspectiveMatrixUnif = glGetUniformLocation(shaderProgram, "perspectiveMatrix");
	GLint offsetUnif = glGetUniformLocation(shaderProgram, "offset");

	glUseProgram(shaderProgram);
	glUniform2f(offsetUnif, 1.0f, 1.0f);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, perspectiveMatrix);
	glUseProgram(0);
	free(shaderList);
	return shaderProgram;
}

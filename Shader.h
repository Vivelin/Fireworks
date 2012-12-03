#pragma once
#ifndef _SHADER
#define _SHADER

#include "Libs.h"

class Shader {
public:
	// Initializes a new shader of the specified type.
	Shader(const char *fileName, const GLenum type);

	// Cleans up this instance.
	~Shader();

	// Returns the GLuint that represents this shader.
	GLuint GetRef() const;

	// Returns whether the shader compiled successfully.
	bool IsCompiled() const;

	// Compiles the shader.
	bool Compile();

private:
	const char *fileName;
	GLenum type;
	GLuint shader;

	// Reads the shader source into the GLchar array pointed at by `source`. Returns the size of the 
	// file, -1 if fopen failed, and -2 if fread failed.
	int Load(GLchar **source) const;
};

#endif
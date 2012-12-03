#include "Libs.h"
#include "Shader.h"

// Initializes a new shader of the specified type.
Shader::Shader(const char *fileName, const GLenum type) : fileName(fileName), type(type) { }

// Cleans up this instance.
Shader::~Shader() { }

// Returns the GLuint that represents this shader.
GLuint Shader::GetRef() const {
	return this->shader;
}

// Returns whether the shader compiled successfully.
bool Shader::IsCompiled() const {
	GLint status;
	glGetShaderiv(this->shader, GL_COMPILE_STATUS, &status);
	return (status == GL_TRUE);
}

// Compiles the shader.
bool Shader::Compile() {
	GLchar *source;
	if (Load(&source) < 0) 
		return false;

	this->shader = glCreateShader(this->type);
	glShaderSource(this->shader, 1, (const GLchar **)&source, NULL);
	free(source);

	glCompileShader(this->shader);
	if (!IsCompiled()) 
	{
		char buffer[513];
		glGetShaderInfoLog(this->shader, 512, NULL, buffer);
		fprintf(stderr, "Shader %s failed to compile:\n%s\n", this->fileName, buffer);
		return false;
	}

	fprintf(stdout, "Shader %s compiled successfully.\n", this->fileName);
	return true;
}

// Reads the shader source into the GLchar array pointed at by `source`. Returns the size of the 
// file, -1 if fopen failed, and -2 if fread failed.
int Shader::Load(GLchar **source) const {
	int fileSize = 0;
	FILE *file = fopen(this->fileName, "rb");
	if (!file)
	{
		fprintf(stderr, "Failed to open \"%s\"\n", this->fileName);
		*source = NULL;
		return -1;
	}

	// Seek to the end determine length of the file
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);

	// Read the file
	fseek(file, 0, SEEK_SET);
	*source = (GLchar *)malloc(fileSize + 1);
	if (fileSize != fread(*source, sizeof(GLchar), fileSize, file))
	{
		fprintf(stderr, "Failed to read \"%s\"\n", fileName);
		free(*source);
		return -2;
	}


	fclose(file);
	(*source)[fileSize] = 0;
	return fileSize;
}

#ifndef _FIREWORKS
#define _FIREWORKS

#include "Libs.h"
#include "Geometry.h"
#include "Shader.h"

class Fireworks {
public:
	struct Particle {
		Vector2 pos;
		Color color;
	};

	Fireworks();
	~Fireworks();

	unsigned int width;
	unsigned int height;
	bool fullscreen;

	bool Load();
	void Run();
	void Update(float frametime);
	void Render();

private:
	sf::Window *window;

	Shader *vertexShader;
	Shader *fragmentShader;
	GLuint shaderProgram;

	Vector3 viewpoint;
	Vector3 viewtarget;
	Matrix4 viewmatrix;
	Matrix4 projectionmatrix;

	void DoEvents();
};


#endif
#ifndef _FIREWORKS
#define _FIREWORKS

#include "Libs.h"
#include "ParticleSystem.h"

class Fireworks {
public:
	Fireworks(unsigned int width, unsigned int height, bool fullscreen);
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
	ParticleSystem *particles;

	void DoEvents();
};


#endif
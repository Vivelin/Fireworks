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

    void SetParticleLimit(size_t maxParticles);
    size_t GetParticleLimit() const;

	void AddRandomParticle();
	void AddSpawner();

private:
	sf::Window *window;
	ParticleSystem *particles;
    size_t maxParticles;

	void DoEvents();
};


#endif
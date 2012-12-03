#ifndef _PARTICLESYSTEM
#define _PARTICLESYSTEM

#include "Libs.h"

struct Particle {
	Vector2 position;
	Color color;
	float size;

	Particle() : 
		position(0, 0), color(255, 255, 255), size(1.0f) {	}

	Particle(Vector2 position) : 
		position(position), color(255, 255, 255), size(1.0f) { }

	Particle(Vector2 position, Color color) : 
		position(position), color(color), size(1.0f) { }

	Particle(Vector2 position, Color color, float size) : 
		position(position), color(color), size(size) { }
};

class ParticleSystem {
public:
	ParticleSystem(unsigned int width, unsigned int height);
	~ParticleSystem();

	void Update(float frametime);
	void Render();

	void Add(const Particle &p);
	void AddRandom();

	size_t Count() const;

private:
	std::vector<Particle> list;
	unsigned int width;
	unsigned int height;

	void RenderParticle(Particle &p);
};

#endif
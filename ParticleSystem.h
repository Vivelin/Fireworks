#ifndef _PARTICLESYSTEM
#define _PARTICLESYSTEM

#include "Libs.h"
#include "Particle.h"

class ParticleSystem {
public:
	ParticleSystem(unsigned int width, unsigned int height);
	~ParticleSystem();

	void Update(float frametime);
	void Render();

	void Add(Particle *p);

	size_t Count() const;

protected:
	std::vector<Particle*> list;
	unsigned int width;
	unsigned int height;
};

#endif
#ifndef _PARTICLESYSTEM
#define _PARTICLESYSTEM

#include "Libs.h"
#include "Particle.h"

class ParticleSystem {
public:
	ParticleSystem(unsigned int width, unsigned int height);
	~ParticleSystem();

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	void Update(float frametime);
	void Render() const;

	void Clear();

	void Add(Particle *p);

	size_t Count() const;

protected:
	std::vector<Particle*> list;
	unsigned int width;
	unsigned int height;
};

#endif
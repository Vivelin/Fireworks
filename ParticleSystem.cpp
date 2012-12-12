#include "Libs.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int width, unsigned int height) : width(width), height(height) {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::Update(float frametime) {
	for (auto i = list.begin(); i != list.end();) {
		Particle &p = *i;
		p.Update(frametime);

		if (p.GetColor().Lightness < 0.0f || p.GetSize() < 0.5f) {
			i = list.erase(i);
			if (i == list.end())
				break;
		} 
		else {
			i++;
		}
	}
}


void ParticleSystem::Render() {
    for (Particle &p : list) {
		p.Render();
	}
}

void ParticleSystem::Add(const Particle &p) {
	list.push_back(p);
}

void ParticleSystem::AddRandom() {
	Vector2 pos((float)(rand() % this->width), (float)(rand() % this->height));

	static double h = (rand() % 6) * 60; // Pick one of 6 random colors
	Color color(h, 1.0f, 1.0f);			 // Particles start with a "flash"
    float size = rand() % 4 + 4.0f;		 // Give a varied size
    if (rand() % 100 == 0)				 // 1% chance of an even bigger particle
        size += 12.0f;

	Vector2 initialSpeed = Vector2(0.0f, -20.0f); // Particles have some initial speed
	Vector2 force = Vector2(-2.0f, -15.0f);  // Particles move downwards
	Add(Particle(pos, color, size, initialSpeed, force));
}

size_t ParticleSystem::Count() const {
	return list.size();
}
#include "Libs.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int width, unsigned int height) : width(width), height(height) {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::Update(float frametime) {
	for (auto i = list.begin(); i != list.end(); i++) {
		Particle &p = *i;
		p.Update(frametime);

		if (p.GetSize() < 0.5f) {
			i = list.erase(i);
			if (i == list.end())
				break;
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

	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	Color color(r, g, b);
    float size = rand() % 4 + 4;
    if (rand() % 100 == 0)
        size += 12.0f;
	Add(Particle(pos, color, size));
}

size_t ParticleSystem::Count() const {
	return list.size();
}
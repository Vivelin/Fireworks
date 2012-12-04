#include "Libs.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int width, unsigned int height) : width(width), height(height) {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::Update(float frametime) {
	for (auto i = list.begin(); i != list.end(); i++) {
		Particle &p = *i;
		p.position -= Vector2(0.0f, -frametime * 30.0f);
		p.size -= frametime;

		if (p.size < 0.5f) {
			i = list.erase(i);
			if (i == list.end())
				break;
		}
	}
}

void ParticleSystem::Render() {
    for (Particle &p : list) {
		RenderParticle(p);
	}
}

void ParticleSystem::RenderParticle(Particle &p) {
	glPointSize(p.size);
	glBegin(GL_POINTS);

	glColor4b(p.color.r(), p.color.g(), p.color.b(), p.color.a());
	glVertex2f(p.position.x(), p.position.y());

	glEnd();
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
	Add(Particle(pos, color, 6.0f));
}

size_t ParticleSystem::Count() const {
	return list.size();
}
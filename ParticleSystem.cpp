#include "Libs.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(unsigned int width, unsigned int height) : 
	width(width), height(height) { }

ParticleSystem::~ParticleSystem() { 
	auto i = list.begin();
	while (i != list.end()) {
		delete *i;
		i = list.erase(i);
	}
}

unsigned int ParticleSystem::GetWidth() const {
	return this->width;
}
unsigned int ParticleSystem::GetHeight() const {
	return this->height;
}

void ParticleSystem::Update(float frametime) {
	for (auto i = list.begin(); i != list.end();) {
		Particle *p = *i;
		p->Update(frametime);

		if (!p->IsAlive() || !p->GetPosition().within(this->height, 0.0f, 0.0f, this->width)) {
			delete p;
			i = list.erase(i);
			if (i == list.end())
				break;
		} 
		else {
			i++;
		}
	}
}

void ParticleSystem::Render() const {
    for (Particle *p : list) {
		p->Render();
	}
}

void ParticleSystem::Add(Particle *p) {
	p->SetParent(this);
	list.push_back(p);
}

size_t ParticleSystem::Count() const {
	return list.size();
}
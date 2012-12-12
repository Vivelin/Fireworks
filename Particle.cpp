#include "Libs.h"
#include "Particle.h"
#include "ParticleSystem.h"

Particle::Particle() : 
	position(0, 0), color(0.0f, 0.0f, 0.0f), size(1.0f), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position) : 
	position(position), color(0.0f, 0.0f, 0.0f), size(1.0f), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color) : 
	position(position), color(color), size(1.0f), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color, float size) : 
	position(position), color(color), size(size), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color, float size, Vector2 speed) : 
	position(position), color(color), size(size), speed(speed), force(Vector2(0.0f, -15.0f)), lifetime(0.0f) { }
Particle::Particle(Vector2 position, Color color, float size, Vector2 speed, Vector2 force) : 
	position(position), color(color), size(size), speed(speed), force(force), lifetime(0.0f) { }

ParticleType Particle::GetType() const {
	return ParticleType::Spark;
}

void Particle::SetParent(ParticleSystem *parent) {
	this->parent = parent;
}

Vector2 Particle::GetPosition() const {
    return this->position;
}

void Particle::SetPosition(const Vector2 &v) {
    this->position = v;
}

Color Particle::GetColor() const {
    return this->color;
}

void Particle::SetColor(const Color &c) {
    this->color = c;
}

float Particle::GetSize() const {
    return this->size;
}

void Particle::SetSize(const float &f) {
    this->size = f;
}

bool Particle::IsAlive() const {
	return (this->size > 0.5f && this->color.Lightness > 0.0f);
}

void Particle::DoPhysics(float frametime) {
	this->lifetime += frametime;

	this->acceleration = this->force * this->size;
	this->speed += acceleration * frametime;
	this->position -= this->speed * frametime;
}

void Particle::Update(float frametime) {
	DoPhysics(frametime);

	if (this->size > 2.0f)
		this->size -= 6 * frametime;
	else
		this->size -= 2 * frametime;

	if (this->color.Lightness > 0.66f)
		this->color.Lightness -= frametime;
	else
		this->color.Lightness -= 0.33 * frametime;
}

void Particle::Render() const {
    glPointSize(this->size);
	glBegin(GL_POINTS);

	RgbColor rgb = this->color.ToRGB();
	glColor3d(rgb.Red, rgb.Green, rgb.Blue);
	glVertex2f(this->position.x(), this->position.y());

	glEnd();
}

SpawnerParticle::SpawnerParticle() : 
	Particle(), maxLifetime(5.0f), particles(NULL) { }
SpawnerParticle::SpawnerParticle(Vector2 position) :
	Particle(position), maxLifetime(5.0f), particles(NULL) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color) :
	Particle(position, color), maxLifetime(5.0f), particles(NULL) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color, float size) :
	Particle(position, color, size), maxLifetime(5.0f), particles(NULL) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color, float size, Vector2 speed) : 
	Particle(position, color, size, speed), maxLifetime(5.0f), particles(NULL) { }
SpawnerParticle::SpawnerParticle(Vector2 position, Color color, float size, Vector2 speed, Vector2 force) :
	Particle(position, color, size, speed, force), maxLifetime(5.0f), particles(NULL) { }

SpawnerParticle::~SpawnerParticle() {
	if (particles != NULL) {
		delete particles;
		particles = NULL;
	}
}

ParticleType SpawnerParticle::GetType() const { 
	return ParticleType::Spawner;
}

float SpawnerParticle::GetMaxLifetime() const {
	return this->maxLifetime;
}

void SpawnerParticle::SetMaxLifetime(float maxLifetime) {
	this->maxLifetime = maxLifetime;
}

float SpawnerParticle::GetFuseTime() const {
	return this->fuseTime;
}

void SpawnerParticle::SetFuseTime(float time) {
	this->fuseTime = time;
}

bool SpawnerParticle::IsAlive() const {
	return (lifetime < maxLifetime);
}

void SpawnerParticle::Update(float frametime) {
	DoPhysics(frametime);

	if (lifetime > fuseTime && particles == NULL) {
		Explode();
	}
	else if (particles != NULL) {
		if (particles->Count() < maxParticles && lifetime < (maxLifetime - 2.0f))
			SpawnParticle();

		particles->Update(frametime);
	}
}

void SpawnerParticle::Render() const {
	Particle::Render();

	if (particles != NULL) {
		particles->Render();
	}
}

void SpawnerParticle::Explode() {
	if (particles == NULL) {
		assert(parent != NULL);

		particles = new ParticleSystem(parent->GetWidth(), parent->GetHeight());
		this->color.Lightness = 0.0f;
		this->force = Vector2();
		this->acceleration = Vector2();
		this->speed = Vector2();
	}
}

void SpawnerParticle::SpawnParticle() {
	if (particles != NULL && IsAlive()) {
		Vector2 pos((float)(rand() % this->width), (float)(rand() % this->height));
		pos += this->position - Vector2(this->width / 2.0f, this->height / 2.0f);

		Color color(this->color.Hue, 1.0f, 1.0f);

		float size = rand() % 4 + 4.0f;		 // Give a varied size
		if (rand() % 100 == 0)				 // 1% chance of an even bigger particle
			size += 12.0f;

		Vector2 initialSpeed = Vector2(0.0f, 20.0f); // Particles have some initial speed
		Vector2 force = Vector2(0.0f, 15.0f); // Particles move downwards

		Particle *p = new Particle(pos, color, size, initialSpeed, force);
		particles->Add(p);
	}
}